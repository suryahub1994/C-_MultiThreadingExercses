#include <iostream>
#include <vector>
#include <utility>
#include <mutex>

int counter = 0;

int main()
{
    std::mutex Mutex;
    auto funct = [](int& counter, std::mutex &Mutex) 
    {
        while (true)
        {
            std::lock_guard<std::mutex> lockGuard(Mutex);
            counter++;
            std::cout << counter << std::endl;
        }
    };
    std::thread t1(funct, std::ref(counter), std::ref(Mutex));
    std::thread t2(funct, std::ref(counter), std::ref(Mutex));
    t1.join();
    t2.join();
    return 0;
}
