/******************************************************************************/
/* Copyright (C) Teledyne Photometrics. All rights reserved.                  */
/******************************************************************************/
#include "TaskSet.h"

// Local
#include "Task.h"

// System
#include <cassert>

TaskSet::TaskSet(std::shared_ptr<ThreadPool> pool)
    : m_pool(pool),
    m_semaphore(std::make_shared<Semaphore>())
{
    assert(pool != nullptr);
    assert(m_semaphore != nullptr);
}

TaskSet::~TaskSet()
{
    for (auto task : m_tasks)
    {
        delete task;
    }
}

size_t TaskSet::GetUsedTaskCount() const
{
    return m_usedTaskCount;
}

void TaskSet::Execute()
{
   m_pool->Execute(std::vector<Task*>(m_tasks.cbegin(), m_tasks.cbegin() + m_usedTaskCount));
}

void TaskSet::Wait()
{
    m_semaphore->Wait(m_usedTaskCount);
}

template<typename Rep, typename Period>
bool TaskSet::Wait(const std::chrono::duration<Rep, Period>& timeout)
{
    return m_semaphore->Wait(timeout, m_usedTaskCount);
}
