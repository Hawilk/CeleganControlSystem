/******************************************************************************/
/* Copyright (C) Teledyne Photometrics. All rights reserved.                  */
/******************************************************************************/
#include "Task.h"

// Local
#include "Semaphore.h"

// System
#include <cassert>

Task::Task(std::shared_ptr<Semaphore> semaphore, size_t taskIndex, size_t totalTaskCount)
    : m_semaphore(semaphore),
    m_taskIndex(taskIndex),
    m_totalTaskCount(totalTaskCount),
    m_usedTaskCount(totalTaskCount)
{
    assert(semaphore != nullptr);
    assert(totalTaskCount > 0);
    assert(taskIndex < totalTaskCount);
}

Task::~Task()
{
}

void Task::Done()
{
    m_semaphore->Release();
}
