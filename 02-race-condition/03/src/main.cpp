#include <iostream>
#include <chrono>
#include <thread>
#include <atomic>
#include <mutex>

class Data
{
public:
    Data(const long &n = 0) { numb = n; };
    Data(const Data &val)
    {
        this->numb = val.numb;
    };
    std::mutex mut;
    long numb{};
};

void swap_lock(Data &a, Data &b)
{
    std::lock(a.mut, b.mut);
    std::lock_guard(a.mut, std::adopt_lock);
    Data c(std::move(a));
    a.numb = b.numb;
    std::lock_guard(b.mut, std::adopt_lock);
    b.numb = c.numb;
};

void swap_unique_lock(Data &a, Data &b)
{
    std::unique_lock(a.mut, std::defer_lock);
    Data c(std::move(a));
    a.numb = b.numb;
    std::unique_lock(b.mut, std::defer_lock);
    b.numb = c.numb;
    std::lock(a.mut, b.mut);
};

void swap_scoped_lock(Data &a, Data &b)
{
    std::scoped_lock(a.mut, b.mut);
    Data c(std::move(a));
    a.numb = b.numb;
    b.numb = c.numb;
};

int main()
{
    Data a{5};
    Data b{8};

    Data a1{5};
    Data b1{8};

    Data a2{5};
    Data b2{8};
    std::cout << "a: " << a.numb << "; b: " << b.numb << std::endl;
    std::cout << "a: " << a1.numb << "; b: " << b1.numb << std::endl;
    std::cout << "a: " << a2.numb << "; b: " << b2.numb << std::endl;
    std::cout << "================" << std::endl;


    std::thread sw_l(swap_lock, std::ref(a), std::ref(b));
    std::thread sw_ul(swap_unique_lock, std::ref(a1), std::ref(b1));
    std::thread sw_sl(swap_scoped_lock, std::ref(a2), std::ref(b2));

    sw_l.join();
    sw_ul.join();
    sw_sl.join();

    std::cout << "a: " << a.numb << "; b: " << b.numb << std::endl;
    std::cout << "a: " << a1.numb << "; b: " << b1.numb << std::endl;
    std::cout << "a: " << a2.numb << "; b: " << b2.numb << std::endl;
    return 0;
}
