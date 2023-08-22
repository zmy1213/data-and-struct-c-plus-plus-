#include <iostream>
#include <thread>
#include <mutex>
#include <chrono>
#include <random>

using namespace std;

mutex proandcon;
bool tobacco = false, paper = false, match = false;

void agent() {
    while (true) {
        this_thread::sleep_for(chrono::milliseconds(1000)); // Agent thinks

        proandcon.lock();
        cout << "Agent places tobacco, paper, and matches on the table." << endl;
        tobacco = true;
        paper = true;
        match = true;
        proandcon.unlock();
    }
}

void smokerWithTobacco() {
    while (true) {
        proandcon.lock();
        if (paper && match) {
            cout << "Smoker with tobacco is making a cigarette." << endl;
            paper = false;
            match = false;
            proandcon.unlock();

            this_thread::sleep_for(chrono::milliseconds(500)); // Smoking time

            cout << "Smoker with tobacco is done smoking." << endl;
        }
        else {
            proandcon.unlock();
        }
    }
}

void smokerWithPaper() {
    while (true) {
        proandcon.lock();
        if (tobacco && match) {
            cout << "Smoker with paper is making a cigarette." << endl;
            tobacco = false;
            match = false;
            proandcon.unlock();

            this_thread::sleep_for(chrono::milliseconds(500)); // Smoking time

            cout << "Smoker with paper is done smoking." << endl;
        }
        else {
            proandcon.unlock();
        }
    }
}

void smokerWithMatches() {
    while (true) {
        proandcon.lock();
        if (tobacco && paper) {
            cout << "Smoker with matches is making a cigarette." << endl;
            tobacco = false;
            paper = false;
            proandcon.unlock();

            this_thread::sleep_for(chrono::milliseconds(500)); // Smoking time

            cout << "Smoker with matches is done smoking." << endl;
        }
        else {
            proandcon.unlock();
        }
    }
}

//int main() {
//    thread t_agent(agent);
//    thread t_smoker_tobacco(smokerWithTobacco);
//    thread t_smoker_paper(smokerWithPaper);
//    thread t_smoker_matches(smokerWithMatches);
//
//    t_agent.join();
//    t_smoker_tobacco.join();
//    t_smoker_paper.join();
//    t_smoker_matches.join();
//
//    return 0;
//}
