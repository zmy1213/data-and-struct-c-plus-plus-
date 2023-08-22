#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <queue>
#include <variant>
#include <chrono>
#include <random>

using namespace std;

mutex mtx;
condition_variable cv;

const int bufferSize = 5;
queue<variant<int, double>> mixedBuffer;

void producer(int id) {
    while (true) {
        variant<int, double> item;
        if (rand() % 2 == 0) {
            item = rand() % 100;
        }
        else {
            item = static_cast<double>(rand()) / RAND_MAX * 100.0;
        }

        unique_lock<mutex> lock(mtx);
        cv.wait(lock, [] { return mixedBuffer.size() < bufferSize; });

        mixedBuffer.push(item);
        cout << "Producer " << id << " produces item: ";
        if (holds_alternative<int>(item)) {
            cout << "Int value: " << get<int>(item);
        }
        else if (holds_alternative<double>(item)) {
            cout << "Double value: " << get<double>(item);
        }
        cout << ", Buffer size: " << mixedBuffer.size() << endl;

        lock.unlock();
        cv.notify_all();

        this_thread::sleep_for(chrono::milliseconds(rand() % 1000)); // Producing time
    }
}

void consumer(int id) {
    while (true) {
        unique_lock<mutex> lock(mtx);
        cv.wait(lock, [] { return !mixedBuffer.empty(); });

        variant<int, double> item = mixedBuffer.front();
        mixedBuffer.pop();

        cout << "Consumer " << id << " consumes item: ";
        if (holds_alternative<int>(item)) {
            cout << "Int value: " << get<int>(item);
        }
        else if (holds_alternative<double>(item)) {
            cout << "Double value: " << get<double>(item);
        }
        cout << ", Buffer size: " << mixedBuffer.size() << endl;

        lock.unlock();
        cv.notify_all();

        this_thread::sleep_for(chrono::milliseconds(rand() % 1000)); // Consuming time
    }
}

int main() {
    srand(time(0));

    thread producers[2];
    thread consumers[4];

    for (int i = 0; i < 2; ++i) {
        producers[i] = thread(producer, i);
    }
    for (int i = 0; i < 4; ++i) {
        consumers[i] = thread(consumer, i);
    }

    for (int i = 0; i < 2; ++i) {
        producers[i].join();
    }
    for (int i = 0; i < 4; ++i) {
        consumers[i].join();
    }

    return 0;
}
