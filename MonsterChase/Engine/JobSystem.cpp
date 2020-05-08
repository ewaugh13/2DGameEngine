#include "JobSystem.h"

#include <Windows.h>

#include "ConsolePrint.h"
#include "HashedString.h"

namespace Engine
{
	HANDLE ghMutex = CreateMutex(
		NULL,              // default security attributes
		FALSE,             // initially not owned
		NULL);             // unnamed mutex
	namespace JobSystem
	{
		bool bShutdownRequested = false;
		AllQueues * CurrentQueues = new AllQueues();;

		void RequestShutdown()
		{
			DEBUG_PRINT("Job System: Shutting down.\n");

			bShutdownRequested = true;

			std::vector<HANDLE>	AllThreads;

			std::map<HashedString, JobQueueData*>::iterator iter = CurrentQueues->m_Queues.begin();
			while (iter != CurrentQueues->m_Queues.end())
			{
				if (iter->second)
				{
					iter->second->m_SharedQueue.Shutdown();
					const size_t count = iter->second->m_Runners.size();
					for (size_t i = 0; i < count; i++)
					{
						JobRunnerData* pRunner = iter->second->m_Runners[i];
						if (pRunner && pRunner->m_ThreadHandle != NULL)
							AllThreads.push_back(pRunner->m_ThreadHandle);
					}
				}
				++iter;
			}

			DEBUG_PRINT("Job System: Waiting for Queue runner threads to shut down.\n");
			if (AllThreads.size() != 0)
			{
				DWORD result = WaitForMultipleObjects(static_cast<DWORD>(AllThreads.size()), &AllThreads[0], TRUE, INFINITE);
				assert(result == WAIT_OBJECT_0);
			}

			iter = CurrentQueues->m_Queues.begin();
			while (iter != CurrentQueues->m_Queues.end())
			{
				if (iter->second)
				{
					const size_t count = iter->second->m_Runners.size();
					for (size_t i = 0; i < count; i++)
					{
						JobRunnerData* pRunner = iter->second->m_Runners[i];
						if (pRunner)
							delete pRunner;
					}

					delete iter->second;
				}

				++iter;
			}

			delete CurrentQueues;
		}

		bool ShutdownRequested()
		{
			return bShutdownRequested;
		}

		void AddRunner(JobQueueData& i_QueueData)
		{
			size_t runners = i_QueueData.m_Runners.size();

			JobRunnerData* pNewRunner = new JobRunnerData;

			pNewRunner->m_Input.i_pQueue = &i_QueueData.m_SharedQueue;
#ifdef _DEBUG
			const size_t	sizeThreadName = 32;
			char			ThreadName[sizeThreadName];
			sprintf_s(ThreadName, sizeThreadName, "%s %d", i_QueueData.m_SharedQueue.GetName(), int(runners + 1));
			pNewRunner->m_Input.m_ThreadName = ThreadName;
#endif

			pNewRunner->m_ThreadHandle = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)JobRunner, &pNewRunner->m_Input, CREATE_SUSPENDED, &pNewRunner->m_ThreadID);
			assert(pNewRunner->m_ThreadHandle != NULL);

			i_QueueData.m_Runners.push_back(pNewRunner);
			ResumeThread(pNewRunner->m_ThreadHandle);
		}

		void AddRunner(const HashedString& i_QueueName)
		{
			std::map<HashedString, JobQueueData*>::iterator existing = CurrentQueues->m_Queues.find(i_QueueName);
			assert(existing != CurrentQueues->m_Queues.end());
			assert(existing->second);

			AddRunner(*existing->second);
		}

		void CreateQueue(const char* i_pName, unsigned int i_numRunners)
		{
			assert(i_pName);

			HashedString	HashedName(i_pName);

			assert(CurrentQueues->m_Queues.find(HashedName) == CurrentQueues->m_Queues.end());

			JobQueueData* pNewJobQueueData = new JobQueueData;
#ifdef _DEBUG
			pNewJobQueueData->m_SharedQueue.SetName(i_pName);
#endif

			CurrentQueues->m_Queues[HashedName] = pNewJobQueueData;

			for (unsigned int i = 0; i < i_numRunners; i++)
				AddRunner(*pNewJobQueueData);
		}

		bool HasJobs(const HashedString& i_QueueName)
		{
			std::map<HashedString, JobQueueData*>::iterator existing = CurrentQueues->m_Queues.find(i_QueueName);
			if (existing != CurrentQueues->m_Queues.end())
			{
				if (existing->second)
					return existing->second->m_SharedQueue.HasJobs();
			}

			return false;
		}

		void RunJob(const std::string& i_JobName, std::function<void()> i_JobFunction, const HashedString& i_QueueName)
		{
			std::map<HashedString, JobQueueData*>::iterator existing = CurrentQueues->m_Queues.find(i_QueueName);
			assert(existing != CurrentQueues->m_Queues.end());
			assert(existing->second);

			DEBUG_PRINT("Job System: Adding Job to Queue \"%s\".\n", existing->second->m_SharedQueue.GetName());
			existing->second->m_SharedQueue.Add(new JobData(i_JobName, i_JobFunction));
		}

	} // namespace JobSystem
} // namespace Engine

