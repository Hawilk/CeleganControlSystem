/******************************************************************************/
/* Copyright (C) Teledyne Photometrics. All rights reserved.                  */
/******************************************************************************/
#include "TaskSet_CopyMemory.h"

// System
#include <algorithm>
#include <cassert>
#include <cstring> // std::memcpy

TaskSet_CopyMemory::ATask::ATask(std::shared_ptr<Semaphore> semDone,
        size_t taskIndex, size_t totalTaskCount)
    : Task(semDone, taskIndex, totalTaskCount)
{
}

void TaskSet_CopyMemory::ATask::SetUp(void* dst, const void* src, size_t bytes,
        size_t usedTaskCount)
{
    m_dst = dst;
    m_src = src;
    m_bytes = bytes;
    m_usedTaskCount = usedTaskCount;
}

void TaskSet_CopyMemory::ATask::Execute()
{
    if (m_taskIndex >= m_usedTaskCount)
        return;

    size_t chunkBytes = m_bytes / m_usedTaskCount;
    const size_t chunkOffset = m_taskIndex * chunkBytes;
    if (m_taskIndex == m_usedTaskCount - 1)
    {
        chunkBytes += m_bytes % m_usedTaskCount;
    }

    void* dst = static_cast<char*>(m_dst) + chunkOffset;
    const void* src = static_cast<const char*>(m_src) + chunkOffset;

    memcpy(dst, src, chunkBytes);
}

TaskSet_CopyMemory::TaskSet_CopyMemory(std::shared_ptr<ThreadPool> pool)
    : TaskSet(pool)
{
    CreateTasks<ATask>();
}

void TaskSet_CopyMemory::SetUp(void* dst, const void* src, size_t bytes)
{
    assert(dst != nullptr);
    assert(src != nullptr);
    assert(bytes > 0);

    // Call memcpy directly without threading for small frames up to 1MB
    // Otherwise do parallel copy and add one thread for each 1MB
    // The limits were found experimentally
    m_usedTaskCount = std::min<size_t>(1 + bytes / 1000000, m_tasks.size());
    if (m_usedTaskCount == 1)
    {
        memcpy(dst, src, bytes);
        return;
    }

    for (auto task : m_tasks)
    {
        static_cast<ATask*>(task)->SetUp(dst, src, bytes, m_usedTaskCount);
    }
}

void TaskSet_CopyMemory::Execute()
{
    if (m_usedTaskCount == 1)
        return; // Already done in SetUp, nothing to execute

    TaskSet::Execute();
}

void TaskSet_CopyMemory::Wait()
{
    if (m_usedTaskCount == 1)
        return; // Already done in SetUp, nothing to wait for

    TaskSet::Wait();
}

void TaskSet_CopyMemory::MemCopy(void* dst, const void* src, size_t bytes)
{
    SetUp(dst, src, bytes);
    Execute();
    Wait();
}
