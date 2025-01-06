#include <iostream>
#include <chrono>
#include <thread>
#include <atomic>
#include <mutex>
#include <windows.h>

std::mutex mt;

void setProgress(int position, int ms)
{
    for (size_t i = 0; i < position + 2; i++)
    {
        std::cout << "\n";
    }

    float progress = 0.0;
    COORD coord;

    // std::cout << position << "; ";
    auto start = std::chrono::steady_clock::now();

    while (progress <= 1.0)
    {
        int barWidth = 70;
        std::this_thread::sleep_for(std::chrono::milliseconds(ms));
        mt.lock();

        coord.X = 0;
        coord.Y = position + 2;
        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);

        std::cout << position << "\t" << std::this_thread::get_id() << "\t";
        int pos = barWidth * progress;

        for (int i = 0; i < barWidth; ++i)
        {
            if (i <= pos)
                std::cout << char(219);
            else
                std::cout << " ";
        }
        std::cout << "\r";

        std::cout.flush();
        mt.unlock();

        progress += 0.01; // for demonstration only
    }
    auto end = std::chrono::steady_clock::now();
    auto diff = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
    double time_shift = static_cast<double>(diff) / 1000000;

    mt.lock();
    coord.X = 95;
    coord.Y = position + 2;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);

    std::cout << time_shift << "s";
    mt.unlock();
    coord.X = 0;
    coord.Y = position + 4;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

int main()
{

    std::cout << "#\t id\t\t\t Progress bar \t\t\t\t\t\t\t time" << std::endl;

    std::thread j1(setProgress, 1, 50);
    std::thread j2(setProgress, 2, 30);
    std::thread j3(setProgress, 3, 20);
    std::thread j4(setProgress, 4, 80);

    j1.join();
    j2.join();
    j3.join();
    j4.join();

    std::cout << std::endl;

    return 0;
}
