#pragma once

#include <vector>
#include <thread>
#include "safe_queue.h"

template <typename T>

class thread_pool
{
public:
    thread_pool()
    {
        processor_count = std::thread::hardware_concurrency();

        // Заполняем Вектор потоков
        for (size_t i = 0; i < processor_count - 2; i++)
        {
            vecOfThreads.push_back(std::thread(&thread_pool::work, this));
        }
    };
    ~thread_pool()
    {
        for (auto& el : vecOfThreads)
        {
            el.join();
        }
    }

    void work()
    {
        std::cout << "Start working thread id " << std::this_thread::get_id() << std::endl;

        // while (!s_queue.is_empty())
        // {
        //     auto task = s_queue.pop();
        //     task;
        // }

        while (flag_done)
        {
            // std::function<void()> task;
            if (!s_queue.is_empty())
            {
                // s_queue.try_pop();
                
                auto task = s_queue.pop();
                try
                {
                    task;
                }
                catch (...)
                {
                    std::cout << std::this_thread::get_id() << std::endl;
                }
            }
            else
            {
                std::this_thread::yield();
            }
        }
    };

    void submit(T&& f)
    {
        s_queue.push(std::move(f));
    };

    void set_done()
    {
        flag_done = true;
    }

private:
    std::vector<std::thread> vecOfThreads;
    int processor_count;
    safe_queue<T> s_queue;
    std::atomic<bool> flag_done{ false };
};