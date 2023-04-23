#include <iostream>
#include <vector>
#include <thread>
#include <chrono>
#include <semaphore>
#include<mutex>

const int kNumReaders = 5;
const int kNumWriters = 3;

using namespace std;
using namespace std::chrono_literals;

mutex m;

vector<int> datas = { 1, 2, 3, 4, 5 };
atomic<int> num_readers = 0;

binary_semaphore rw_sem(1);
binary_semaphore w_sem(1);

void writer()
{
	srand(time(NULL));
	while (1)
	{
		w_sem.acquire();
		rw_sem.acquire();
		datas.push_back(rand() % 20);
		rw_sem.release();
		w_sem.release();
	}
}
void reader()
{
	while (1)
	{
		w_sem.acquire();
		unique_lock<mutex> lc(m);
		if (num_readers == 0)
			rw_sem.acquire();
		
		num_readers++;
		lc.unlock();

		w_sem.release();

		for (const auto& val : datas)
		{
			cout << val << " ";
		}


		lc.lock();
		num_readers--;
		if (num_readers == 0)
			rw_sem.release();
		lc.unlock();
	}
}
int main() {
    std::vector<std::thread> threads;
    for (int i = 0; i < kNumReaders; ++i) {
        threads.emplace_back(reader);
    }
    for (int i = 0; i < kNumWriters; ++i) {
        threads.emplace_back(writer);
    }
    for (auto& t : threads) {
        t.join();
    }
    return 0;
}