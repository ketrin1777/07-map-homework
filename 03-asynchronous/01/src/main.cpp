#include <iostream>
#include <chrono>
#include <thread>
#include <vector>
#include <future>

int find_min(const std::vector<int> &numb, const int &i)
{
    size_t N = numb.size();
    int min = i;

    for (int j = i + 1; j < N; j++)
    {
        if (numb[j] < numb[min])
        {
            min = j;
        }
    }
    return min;
}

void sort_vector(const std::vector<int> &val, std::promise<std::vector<int>> barrier)
{
    std::vector<int> numb = val;
    int min = 0; // для записи минимального значения
    int buf = 0; // для обмена значениями

    size_t N = numb.size();

    /*********** Начало сортировки **************/
    for (int i = 0; i < N; i++)
    {
        // в цикле найдем реальный номер ячейки с минимальным значением

        auto m_f = std::async(find_min, numb, i);

        min = m_f.get();
        // std::cout << min << std::endl;

        // cделаем перестановку этого элемента, поменяв его местами с текущим
        if (i != min)
        {
            buf = numb[i];
            numb[i] = numb[min];
            numb[min] = buf;
        }
    }
    barrier.set_value(numb);
}

int main()
{
    std::vector<int> number{1, 5, 9, 4, 16, 87};

    std::promise<std::vector<int>> barrier;
    std::future<std::vector<int>> barrier_future = barrier.get_future();
    std::thread new_work_thread(sort_vector, number, std::move(barrier));
    number = barrier_future.get();
    new_work_thread.join();

    for (const auto & item : number)
    {
        std::cout << item << ", ";
    }
    std::cout << std::endl;
    

    return 0;
}
