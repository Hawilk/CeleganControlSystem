/******************************************************************************/
/* Copyright (C) Teledyne Photometrics. All rights reserved.                  */
/******************************************************************************/
#pragma once
#ifndef THREADPOOL_H
#define THREADPOOL_H

// System
#include <condition_variable>
#include <memory> // std::unique_ptr
#include <mutex>
#include <queue>
#include <thread>
#include <vector>

class Task;

class ThreadPool final
{
public:
    explicit ThreadPool();
    ~ThreadPool();

    size_t GetSize() const;

    void Execute(Task* task);
    void Execute(const std::vector<Task*>& tasks);

private:
    void ThreadFunc();

private:
    std::vector<std::unique_ptr<std::thread>> m_threads{};
    bool m_abortFlag{ false };

    std::queue<Task*>       m_queue{};
    std::mutex              m_queueMutex{};
    std::condition_variable m_queueCond{};
};

#endif
