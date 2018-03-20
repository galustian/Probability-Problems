#include <cmath>
#include <ctime>
#include <iostream>

using namespace std;

unsigned long long gen_seed() {
    return (unsigned long long)time(0);
}

// implementation of a simple linear congruential generator (LGC)
double random_number(unsigned long long seed = 234454034, unsigned short modulus_bit = 32) {
    // parameters
    unsigned long long a = 84756;  // multiplier
    unsigned long long c = 345435; // constant
    unsigned long long m = pow(2, modulus_bit);

    static unsigned long long prev_rand = -1;
    
    unsigned long long new_rand = 0;
    if (prev_rand == -1) {
        new_rand = (a * seed + c) % m;
        prev_rand = new_rand;
        new_rand = (a * prev_rand + c) % m;
        prev_rand = new_rand;
    } else {
        new_rand = (a * prev_rand + c) % m;
        prev_rand = new_rand;
    }

    return (double)new_rand / m;
}

int main() {
    cout << random_number(gen_seed()) << endl;

    cout << random_number() << endl;
    cout << random_number() << endl;
    cout << random_number() << endl;
    cout << random_number() << endl;
    cout << random_number() << endl;
    cout << random_number() << endl;
    cout << random_number() << endl;
    cout << random_number() << endl;

    return 0;
}