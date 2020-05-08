#pragma once

#include <functional>
#include <string>
#include <map>

#include "HashedString.h"
#include "JobRunner.h"
#include "SharedJobQueue.h"

namespace Engine
{
	namespace JobSystem
	{
		struct JobData
		{
			std::string				Name;
			std::function<void()>	Function;

			JobData(const std::string& i_Name, std::function<void()> i_Function) :
				Name(i_Name),
				Function(i_Function)
			{}
		};

		typedef struct JobRunnerData
		{
			HANDLE				m_ThreadHandle;
			DWORD				m_ThreadID;
			JobRunnerInput		m_Input;
		} JobRunnerData;

		typedef struct JobQueueData
		{
			SharedJobQueue		m_SharedQueue;
			std::vector<JobRunnerData*>	m_Runners;
		} JobQueueData;

		typedef struct AllQueues
		{
			std::map<HashedString, JobQueueData*> m_Queues;
		} AllQueues;

		void CreateQueue(const char* i_pName, unsigned int i_numRunners);
		bool HasJobs(const HashedString& i_QueueName);
		void AddRunner(const HashedString& i_QueueName);

		void RunJob(const std::string& i_JobName, std::function<void()> i_JobFunction, const HashedString& i_QueueName);
		void RequestShutdown();
		bool ShutdownRequested();

	} // namespace JobSystem
} // namespace Engine
