/******************************************************************************/
/* Copyright (C) Teledyne Photometrics. All rights reserved.                  */
/******************************************************************************/
#pragma once
#ifndef TASKSET_H
#define TASKSET_H

// Local
#include "Semaphore.h"
#include "ThreadPool.h"

// System
#include <chrono>
#include <memory> // std::shared_ptr
#include <vector>

class Task;

class TaskSet
{
public:
    explicit TaskSet(std::shared_ptr<ThreadPool> pool);
    virtual ~TaskSet();

    TaskSet(const TaskSet&) = delete;
    TaskSet& operator=(const TaskSet&) = delete;

    size_t GetUsedTaskCount() const;

    virtual void Execute();
    virtual void Wait();
    // Member function templates cannot be virtual
    template<typename Rep, typename Period>
    bool Wait(const std::chrono::duration<Rep, Period>& timeout);

protected:
    template<class T,
        // Private param to enforce the type T derives from Task class
        typename std::enable_if<std::is_base_of<Task, T>::value, int>::type = 0>
    void CreateTasks()
    {
        const size_t taskCount = m_pool->GetSize();
        m_tasks.reserve(taskCount);
        for (size_t n = 0; n < taskCount; ++n)
        {
            auto task = new(std::nothrow) T(m_semaphore, n, taskCount);
            if (!task)
                continue;
            m_tasks.push_back(task);
        }
        m_usedTaskCount = m_tasks.size();
    }

protected:
    const std::shared_ptr<ThreadPool> m_pool;
    const std::shared_ptr<Semaphore> m_semaphore;
    std::vector<Task*> m_tasks{};
    size_t m_usedTaskCount{ 0 };
};

#endif
