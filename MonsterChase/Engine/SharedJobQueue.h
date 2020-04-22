#pragma once

#include <Windows.h>
#include <queue>

#include "INamed.h"

namespace Engine
{
	namespace JobSystem
	{
		struct JobData;

		class SharedJobQueue
#ifdef _DEBUG
			: public INamed
#endif
		{
		public:
			SharedJobQueue();

			inline void Shutdown()
			{
				EnterCriticalSection(&m_QueueAccess);
				m_ShutdownRequested = true;
				LeaveCriticalSection(&m_QueueAccess);

				WakeAllConditionVariable(&m_WakeAndCheck);
			}

			inline bool ShutdownRequested() const
			{
				return m_ShutdownRequested;
			}

			bool Add(struct JobData* i_JobData);
			bool HasJobs() const;
			struct JobData* GetWhenAvailable();
			void JobFinished();
		private:
			SharedJobQueue(const SharedJobQueue&) = delete;
			SharedJobQueue& operator=(const SharedJobQueue&) = delete;

			std::queue<struct JobData*>	m_Jobs;
			CONDITION_VARIABLE m_WakeAndCheck;
			mutable CRITICAL_SECTION m_QueueAccess;

			bool m_bJobRunning;
			bool m_ShutdownRequested;
		};

	} // namespace JobSystem
} // namespace Engine