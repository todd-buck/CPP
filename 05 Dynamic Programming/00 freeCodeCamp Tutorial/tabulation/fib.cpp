/*
Description:
    Given a number i, return the ith number in the fibonnaci sequence

Time Complexity:
    O(n), iterative solution
    
Space Complexity:
    O(1), only store local copies of constant variables
*/

#include <iostream>
#include <deque>

using namespace std;

long long fib(int target) {
    long long lastLast = 0;
    long long last = 1;
    long long temp;

    for(int i = 2; i <= target; i++) {
        temp = last + lastLast;
        lastLast = last;
        last = temp;
    }

    return last;
}

int main() {

    cout << "Fib(6): " << fib(6) << endl;
    cout << "Fib(7): " << fib(7) << endl;
    cout << "Fib(8): " << fib(8) << endl;
    cout << "Fib(50): " << fib(50) << endl;

    return 0;
}