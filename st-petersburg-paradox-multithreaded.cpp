#include <iostream>
#include <random>
#include <cmath>
#include <vector>
#include <map>
#include <thread>
#include <mutex>

using namespace std;

const long kSimulations = 600000; // num. simulations in each thread
const long kThreads = 100; // simulate on num. threads

// Shared Data of Threads
mutex mutex_expected_wins;
mutex mutex_win_list;
vector<double> thread_expected_wins;
map<long, long> win_list;

double simulate() {
    random_device rd;
    mt19937 gen(rd());  // Standard mersenne_twister_engine seeded with rd()
    binomial_distribution<> binomial(1, 0.5);
    
    unsigned long long total_win = 0;

    for (int i = 1; i <= kSimulations; i++) {
    
        int nth_flip = 0;
        short heads = 0;
        
        do {
            heads = binomial(gen);
            ++nth_flip;
            
            if (heads == 1) {
                total_win += pow(2, nth_flip);
            } else if (heads == 0) {
                long last_flip_win = pow(2, nth_flip-1);
                if (nth_flip-1 == 0) last_flip_win = 0;
                
                // append win to win_list
                mutex_win_list.lock();
                if (win_list.count(last_flip_win) > 0) {
                    win_list[last_flip_win] += 1;
                } else {
                    win_list[last_flip_win] = 1;
                }
                mutex_win_list.unlock();
            }
        }
        while (heads == 1);
    }
    
    double expected_win = (double)total_win / (double)kSimulations;
    
    mutex_expected_wins.lock();
    thread_expected_wins.push_back(expected_win);
    mutex_expected_wins.unlock();
}

int main() {
    double expected_winning = 0;
    
    for (long i = 0; i < kThreads; i++) {
        thread t(simulate);
        t.join();
    }
    
    for (auto& win: thread_expected_wins) {
        expected_winning += win;
    }
    expected_winning /= (double)kThreads;
    
    cout << "Expected Winnings: " << expected_winning << endl << endl;
    
    long long largest_win = 0;
    for (auto &win: win_list) {
        cout << "Won " << win.first << "$ " << win.second << " times" << endl;
        if (win.first > largest_win) {
            largest_win = win.first;
        }
    }
    
    cout << "\n" << "Record: " << log2(largest_win) << " times heads in a row." << endl;
    
    return 0;
}
