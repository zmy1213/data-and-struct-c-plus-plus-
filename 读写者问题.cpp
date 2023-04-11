//#include <iostream>
//#include <vector>
//#include <thread>
//#include <chrono>
//#include <semaphore>
//
//using namespace std::chrono_literal
//
//const int kNumReaders = 5;
//const int kNumWriters = 3;
//
//std::vector<int> data = { 1, 2, 3, 4, 5 };
//std::atomic<int> num_readers = 0;
//
//std::binary_semaphore rw_sem(1);
//std::counting_semaphore<kNumReaders> read_sem;
//
//void reader(int id) {
//    while (true) {
//        // Allow other readers to enter
//        read_sem.release();
//
//        // Acquire the reader-writer lock
//        rw_sem.auire();
//
//        // Increment the number of readers
//        num_readers++;
//
//        // Release the reader-writer lock
//        rw_sem.release();
//
//        // Read data
//        {
//            std::lock_guard<std::mutex> cout_lk(cout_mtx);
//            std::cout << "Reader " << id << " reads data: ";
//            for (auto d : data) {
//                std::cout << d << " ";
//            }
//            std::cout << std::endl;
//        }
//
//        // Acquire the reader-writer lock
//        rw_sem.acquire();
//
//        // Decrement the number of readers
//        num_readers--;
//
//        // Check if there are no more readers
//        if (num_readers == 0) {
//            // Allow a writer to enter
//            rw_sem.release();
//        }
//
//        // Allow other readers to enter
//        read_sem.release();
//
//        // Sleep for some time
//        std::this_thread::sleep_for(1s);
//    }
//}
//
//void writer(int id) {
//    while (true) {
//        // Acquire the reader-writer lock
//        rw_sem.acquire();
//
//        // Wait for all readers to exit
//        while (num_readers > 0) {
//            rw_sem.release();
//            rw_sem.acquire();
//        }
//
//        // Write data
//        {
//            std::lock_guard<std::mutex> cout_lk(cout_mtx);
//            std::cout << "Writer " << id << " writes data" << std::endl;
//            for (int i = 0; i < data.size(); ++i) {
//                data[i] = (i + 1) * (id + 1);
//            }
//        }
//
//        // Release the reader-writer lock
//        rw_sem.release();
//
//        // Sleep for some time
//        std::this_thread::sleep_for(2s);
//    }
//}
//
////int main() {
////    std::vector<std::thread> threads;
////    for (int i = 0; i < kNumReaders; ++i) {
////        threads.emplace_back(reader, i);
////    }
////    for (int i = 0; i < kNumWriters; ++i) {
////        threads.emplace_back(writer, i);
////    }
////    for (auto& t : threads) {
////        t.join();
////    }
////    return 0;
////}
