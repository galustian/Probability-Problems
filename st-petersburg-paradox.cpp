#include <iostream>
#include <random>
#include <cmath>
#include <map>

using namespace std;

const unsigned long kSimulations = 100000000;

int main() {
    random_device rd;
    mt19937 gen(rd());  // Standard mersenne_twister_engine seeded with rd()
    binomial_distribution<> binomial(1, 0.5);
    
    unsigned long long total_win = 0;
    map<long, long> win_list;
    
    for (int i = 1; i <= kSimulations; i++) {
    
        int nth_flip = 0;
        short heads = 0;
        
        do {
            heads = binomial(gen);
            ++nth_flip;
            
            if (heads == 1) {
                total_win += pow(2, nth_flip);
            } else if (heads == 0 && nth_flip > 1) {
                long last_flip_win = pow(2, nth_flip-1);
                
                // append win to win_list
                if (win_list.count(last_flip_win) > 0) {
                    win_list[last_flip_win] += 1;
                } else {
                    win_list[last_flip_win] = 1;
                }
            }
        }
        while (heads == 1);
    }
    
    double expected_win = (double)total_win / (double)kSimulations;
    
    cout << "Expected Winnings: " << expected_win << endl << endl;
    
    for (auto &win: win_list) {
        cout << "Won " << win.first << "$ " << win.second << " times" << endl;
    }
    
    return 0;
}
