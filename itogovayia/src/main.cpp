#include "thread_pool.h"

thread_pool<std::function<void(void)>> tr_p; 

void func1()
{
    std::cout << "Working " << __FUNCTION__ << "…\n";
}

void func2()
{
    std::cout << "Working " << __FUNCTION__ << "…\n";
}

void addF1()
{
    for (size_t i = 0; i < 5; i++)
    {
        std::this_thread::sleep_for(std::chrono::milliseconds(500));
        tr_p.submit(func1);
    }
}

void addF2()
{
    for (size_t i = 0; i < 5; i++)
    {
        std::this_thread::sleep_for(std::chrono::milliseconds(500));
        tr_p.submit(func2);
    }
}

void work()
{
    // tr_p.work();
}

int main(int, char**)
{
    std::thread t1(addF1);
    std::thread t2(addF2);
    
    t1.join();
    t2.join();
    tr_p.set_done();

}