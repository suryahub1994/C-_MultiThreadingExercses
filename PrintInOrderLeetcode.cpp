class Foo {
public:
    int turn = 0;  // Indicates whose turn it is: 0 for first(), 1 for second(), 2 for third()
    std::mutex Mutex;  // Mutex to protect shared state
    std::condition_variable conditionVariable;  // Condition variable for synchronization
    
    Foo() {
        // Constructor
    }

    void first(std::function<void()> printFirst) {
        std::unique_lock<std::mutex> lock(Mutex);
        // Wait until it's this thread's turn
        conditionVariable.wait(lock, [this] { return turn == 0; });
        
        // printFirst() outputs "first". Do not change or remove this line.
        printFirst();
        
        // Update turn to allow second() to run
        turn = 1;
        conditionVariable.notify_all();  // Notify all waiting threads
    }

    void second(std::function<void()> printSecond) {
        std::unique_lock<std::mutex> lock(Mutex);
        // Wait until it's this thread's turn
        conditionVariable.wait(lock, [this] { return turn == 1; });
        
        // printSecond() outputs "second". Do not change or remove this line.
        printSecond();
        
        // Update turn to allow third() to run
        turn = 2;
        conditionVariable.notify_all();  // Notify all waiting threads
    }

    void third(std::function<void()> printThird) {
        std::unique_lock<std::mutex> lock(Mutex);
        // Wait until it's this thread's turn
        conditionVariable.wait(lock, [this] { return turn == 2; });
        
        // printThird() outputs "third". Do not change or remove this line.
        printThird();
        
        // Reset turn to allow first() to run again (or exit if necessary)
        turn = 0;
        conditionVariable.notify_all();  // Notify all waiting threads
    }
};
