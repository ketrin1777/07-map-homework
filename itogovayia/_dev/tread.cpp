#pragma once

#include <iostream>
#include <queue>
#include <mutex>
#include <vector>
#include <functional>
#include <algorithm>
#include <thread>
#include <atomic>

std::mutex m;

std::queue<std::function<void(void)>> wor_queue;
std::vector<std::thread> VecThread;

std::atomic<bool> falg_done{ false };

void func1()
{
    std::this_thread::sleep_for(std::chrono::milliseconds(200));
    std::lock_guard(m);
    std::cout << "Working " << __FUNCTION__ << "...\n";
}

void func2()
{
    std::this_thread::sleep_for(std::chrono::milliseconds(200));
    std::lock_guard(m);
    std::cout << "Working " << __FUNCTION__ << "...\n";
}

void addF1()
{
    for (size_t i = 0; i < 5; i++)
    {
        std::this_thread::sleep_for(std::chrono::milliseconds(500));
        std::lock_guard(m);
        wor_queue.push(func1);
    }
}

void addF2()
{
    for (size_t i = 0; i < 5; i++)
    {
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
        std::lock_guard(m);
        wor_queue.push(func2);
    }
    falg_done = true;
}

void work()
{
    m.lock();
    std::cout << "Start working thread id " << std::this_thread::get_id() << std::endl;
    m.unlock();

    while (falg_done)
    {
        if (!wor_queue.empty())
        {
            auto task = wor_queue.front();
            task();
            wor_queue.pop();
        }
    }
    while (!wor_queue.empty())
    {
        auto task = wor_queue.front();
        task();
        wor_queue.pop();
    }
}

int main()
{
    int cores = std::thread::hardware_concurrency();

    // Заполняем очередь задачами
    std::thread th1(addF1);
    std::thread th2(addF2);

    // Заполняем Вектор потоков
    for (size_t i = 0; i < cores - 2; i++)
    {
        VecThread.push_back(std::thread(work));
    }

    // Подключаем потоки
    for (auto &el : VecThread)
    {
        el.join();
    }
    th1.join();
    th2.join();
    
}