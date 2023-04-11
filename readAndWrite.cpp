#include <iostream>
#include <vector>
#include <thread>
#include <chrono>
#include <semaphore>
#include<mutex>
using namespace std;
using namespace std::chrono_literals;

const int kNumReaders = 5;
const int kNumWriters = 3;

mutex m;
vector<int> datas= { 1, 2, 3, 4, 5 };
atomic<int> num_readers = 0;

binary_semaphore rw_sem(1);
counting_semaphore read_sem(5);


void reader()
{
	while (true)
	{
		std::unique_lock<std::mutex> lc(m);
		if (num_readers == 0)
			rw_sem.acquire();
		num_readers++;
		lc.unlock();

		for (auto val:datas)
		{
			cout << val << " ";
		}
		cout << endl;

		lc.lock();
		num_readers--;
		if (num_readers == 0)
			rw_sem.release();
		lc.unlock();
	}
}

void writer()
{
	while(true)
	{
		rw_sem.acquire();
		for (int i = 0; i < datas.size(); ++i)
			datas.push_back(i) ;
		rw_sem.release();
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