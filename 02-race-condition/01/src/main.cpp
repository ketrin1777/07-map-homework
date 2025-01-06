#include <iostream>
#include <chrono>
#include <thread>
#include <atomic>



void client(std::atomic<int> &count, int max_count)
{
    while (true)
    {
        std::this_thread::sleep_for(std::chrono::seconds(1));
        if (count < max_count)
        {
            std::atomic_fetch_add(&count, 1);
            std::cout << "Count client: " << count << std::endl;
        }
    }
}

void operators(std::atomic<int> &count)
{
    while (true)
    {
        std::this_thread::sleep_for(std::chrono::seconds(2));
        if (count > 0)
        {
            std::atomic_fetch_add(&count, -1);
            std::cout << "Count operator: " << count << std::endl;
        }
    }
}

int main()
{
    std::atomic<int> count_client{0};
    std::thread t1(client, std::ref(count_client), 5);
	std::thread t2(operators, std::ref(count_client));

    t1.join();
    t2.join();

    return 0;
}
