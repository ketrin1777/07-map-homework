#include <iostream>
#include <chrono>
#include <thread>
#include <algorithm>
#include <vector>
#include <random>
#include <execution>
#include <Windows.h>
#pragma execution_character_set("utf-8")

void sum_tread(const std::vector<int> &one, const std::vector<int> &twoo, std::vector<int> &summ, size_t shift, size_t count_tread)
{
    double siz_double = one.size();
    double count_double = one.size() / count_tread;

    size_t count = ceil(count_double); // Количество просчета
    size_t start = shift * count;      // Стартовый индекс

    if (one.size() == twoo.size() && twoo.size() == summ.size())
    {
        if ((count + start) > one.size()) // Если за пределы вектора
        {
            count = count - ((count + start) - count);
        }
        for (size_t i = start; i < count; i++)
        {
            summ[i] = one[i] + twoo[i];
        }
    }
}

void summ_vect(std::vector<int> &one, std::vector<int> &twoo, std::vector<int> &summ, const int &count_tread)
{

    auto start = std::chrono::steady_clock::now();
    // BEGIN
    std::vector<std::thread> readerThreads;
    for (size_t i = 0; i < count_tread; i++)
    {
        std::thread tr(sum_tread, std::ref(one), std::ref(twoo), std::ref(summ), i, count_tread);
        readerThreads.push_back(std::move(tr));
    }

    for (size_t i = 0; i < count_tread; i++)
    {
        readerThreads[i].join();
    }

    // END
    // std::sort(std::execution::par, one.begin(), one.end());
    auto end = std::chrono::steady_clock::now();
    auto diff = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
    double time_shift = static_cast<double>(diff) / 1000000;

    std::cout << time_shift << "s\t";
}

void generate_random(std::vector<int> &one, std::vector<int> &twoo, const size_t &size)
{
    one.clear();
    one.resize(size);
    twoo.clear();
    twoo.resize(size);
    std::mt19937 rand;
    std::uniform_int_distribution<int> dist(0, 1000);
    std::generate(std::execution::par, one.begin(), one.end(), [&]()
                  { return dist(rand); });

    std::generate(std::execution::par, twoo.begin(), twoo.end(), [&]()
                  { return dist(rand); });
}
int main()
{
    setlocale(LC_ALL, ".UTF-8");

    SetConsoleCP(CP_UTF8);
    SetConsoleOutputCP(CP_UTF8);
    setvbuf(stdout, nullptr, _IOFBF, 1000);

    int cores_count = std::thread::hardware_concurrency(); // Узнаем к-во ядер
    std::cout << "Количество аппаратных ядер - " << cores_count << "\n\n";

    std::vector<int> one, twoo, summ;
    for (size_t i = 1000; i < 1000001; i *= 10)
    {
        std::cout << "\t" << i << "\t";
    }
    std::cout << "\n";
    for (int x = 1; x < 17; x *= 2)
    {
        std::cout << x << " потоков ";
        for (size_t i = 1000; i < 1000001; i *= 10)
        {
            generate_random(one, twoo, i);
            summ.clear();
            summ.resize(i);
            summ_vect(one, twoo, summ, x);
        }
        std::cout << "\n";
    }

    return 0;
}
