/******************************************************************************/
/* Copyright (C) Teledyne Photometrics. All rights reserved.                  */
/******************************************************************************/
#include "Semaphore.h"

Semaphore::Semaphore()
{
}

Semaphore::Semaphore(size_t initCount)
    : m_count(initCount)
{
}

void Semaphore::Wait(size_t count)
{
    std::unique_lock<std::mutex> lock(m_mutex);
    m_cond.wait(lock, [&]() { return m_count >= count; });
    m_count -= count;
}

template<typename Rep, typename Period>
bool Semaphore::Wait(const std::chrono::duration<Rep, Period>& timeout, size_t count)
{
    std::unique_lock<std::mutex> lock(m_mutex);
    const bool timedOut = !m_cond.wait_for(lock, timeout, [&]() { return m_count >= count; });
    if (timedOut)
        return false;
    m_count -= count;
    return true;
}

void Semaphore::Release(size_t count)
{
    {
        std::unique_lock<std::mutex> lock(m_mutex);
        m_count += count;
    }
    m_cond.notify_one();
}
