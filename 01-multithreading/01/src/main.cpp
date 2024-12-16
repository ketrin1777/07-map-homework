#include <iostream>
#include <chrono>
#include <thread>

void client(int &count, int max_count)
{
    while (true)
    {
        std::this_thread::sleep_for(std::chrono::seconds(1));
        if (count < max_count)
        {
            count++;
            std::cout << "Count client: " << count << std::endl;
        }
    }
}

void operators(int &count)
{
    while (true)
    {
        std::this_thread::sleep_for(std::chrono::seconds(2));
        if (count > 0)
        {
            count--;
            std::cout << "Count operator: " << count << std::endl;
        }
    }
}

int main()
{
    int count_client{0};
    std::thread t1(client, std::ref(count_client), 5);
	std::thread t2(operators, std::ref(count_client));

    t1.join();
    t2.join();

    return 0;
}
