/******************************************************************************/
/* Copyright (C) Teledyne Photometrics. All rights reserved.                  */
/******************************************************************************/
#pragma once
#ifndef TASK_H
#define TASK_H

// System
#include <memory> // std::shared_ptr

class Semaphore;

class Task
{
public:
    explicit Task(std::shared_ptr<Semaphore> semaphore, size_t taskIndex, size_t totalTaskCount);
    virtual ~Task();

    Task(const Task&) = delete;
    Task& operator=(const Task&) = delete;

    virtual void Execute() = 0;
    void Done();

private:
    std::shared_ptr<Semaphore> m_semaphore;

protected:
    const size_t m_taskIndex;
    const size_t m_totalTaskCount;
    size_t m_usedTaskCount;
};

#endif
