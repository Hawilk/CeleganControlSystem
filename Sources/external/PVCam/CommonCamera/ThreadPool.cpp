/******************************************************************************/
/* Copyright (C) Teledyne Photometrics. All rights reserved.                  */
/******************************************************************************/
#include "ThreadPool.h"

// Local
#include "Task.h"

// System
#include <algorithm>
#include <cassert>

ThreadPool::ThreadPool()
{
    const size_t hwThreadCount = std::max<size_t>(1, std::thread::hardware_concurrency());
    m_threads.reserve(hwThreadCount);
    for (size_t n = 0; n < hwThreadCount; ++n)
    {
        auto thread = std::make_unique<std::thread>(&ThreadPool::ThreadFunc, this);
        m_threads.push_back(std::move(thread));
    }
}

ThreadPool::~ThreadPool()
{
    {
        std::lock_guard<std::mutex> lock(m_queueMutex);
        m_abortFlag = true;
    }
    m_queueCond.notify_all();

    for (auto& thread : m_threads)
    {
        thread->join();
    }
}

size_t ThreadPool::GetSize() const
{
    return m_threads.size();
}

void ThreadPool::Execute(Task* task)
{
    assert(task != nullptr);

    {
        std::lock_guard<std::mutex> lock(m_queueMutex);
        if (m_abortFlag)
            return;
        m_queue.push(task);
    }
    m_queueCond.notify_one();
}

void ThreadPool::Execute(const std::vector<Task*>& tasks)
{
    assert(!tasks.empty());

    if (tasks.size() == 1)
    {
        Execute(tasks[0]);
    }
    else
    {
        {
            std::lock_guard<std::mutex> lock(m_queueMutex);
            if (m_abortFlag)
                return;
            for (auto task : tasks)
            {
                assert(task != nullptr);
                m_queue.push(task);
            }
        }
        m_queueCond.notify_all();
    }
}

void ThreadPool::ThreadFunc()
{
    for (;;)
    {
        Task* task = nullptr;
        {
            std::unique_lock<std::mutex> lock(m_queueMutex);

            m_queueCond.wait(lock, [this] {
                return (!m_queue.empty() || m_abortFlag);
            });
            if (m_abortFlag)
                break;

            task = m_queue.front();
            m_queue.pop();
        }

        task->Execute();
        task->Done();
    }
}
