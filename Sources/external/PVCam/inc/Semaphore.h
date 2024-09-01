/******************************************************************************/
/* Copyright (C) Teledyne Photometrics. All rights reserved.                  */
/******************************************************************************/
#pragma once
#ifndef SEMAPHORE_H
#define SEMAPHORE_H

// System
#include <chrono>
#include <condition_variable>
#include <mutex>

class Semaphore final
{
public:
    explicit Semaphore();
    explicit Semaphore(size_t initCount);

    void Wait(size_t count = 1);
    template<typename Rep, typename Period>
    bool Wait(const std::chrono::duration<Rep, Period>& timeout, size_t count = 1);
    void Release(size_t count = 1);

private:
    size_t m_count{ 0 };
    std::mutex m_mutex{};
    std::condition_variable m_cond{};
};

#endif
