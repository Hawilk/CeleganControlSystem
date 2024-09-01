/******************************************************************************/
/* Copyright (C) Teledyne Photometrics. All rights reserved.                  */
/******************************************************************************/
#pragma once
#ifndef TASKSET_COPYMEMORY_H
#define TASKSET_COPYMEMORY_H

// Local
#include "Task.h"
#include "TaskSet.h"

class TaskSet_CopyMemory : public TaskSet
{
private:
    class ATask : public Task
    {
    public:
        explicit ATask(std::shared_ptr<Semaphore> semDone, size_t taskIndex, size_t totalTaskCount);

    public:
        void SetUp(void* dst, const void* src, size_t bytes, size_t usedTaskCount);

    public: // Task
        virtual void Execute() override;

    private:
        void* m_dst{ nullptr };
        const void* m_src{ nullptr };
        size_t m_bytes{ 0 };
    };

public:
    explicit TaskSet_CopyMemory(std::shared_ptr<ThreadPool> pool);

    void SetUp(void* dst, const void* src, size_t bytes);

public: // TaskSet
    virtual void Execute() override;
    virtual void Wait() override;

    // Helper blocking method calling SetUp, Execute and Wait
    void MemCopy(void* dst, const void* src, size_t bytes);
};

#endif
