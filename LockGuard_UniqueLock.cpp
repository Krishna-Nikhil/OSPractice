/*
lock_guard owns the mutex on scoped basis
No need to unlock them. & should not unlock them
unique_lock without locking strategy = lock_guard
Strategies in locking for unique_lock are:
defer_lock, try_to_lock, adopt_lock
*/

#include <bits/stdc++.h>
using namespace std;

mutex m;

void func1(int x, int y) {
    lock_guard<mutex> lock(m); // = unique_lock<mutex> lock(m);
    while(x --> 0) {
        cout << "T" << y << " got the lock:" << x << endl;
    }
} // Destructor of mutex called here

void func2(int x, int y) {
    unique_lock<mutex> lock_this(m,defer_lock); // not locked here
    lock_this.lock(); // Locked here
    cout << "Aquired the lock now for T" << y << endl;
    while(x --> 0) {
        cout << "T" << y << " got the lock:" << x << endl;
    }
} // Destructor of mutex called here

int main() {
    thread t1(func1,10,1);
    thread t2(func1,10,2);

    t1.join();
    t2.join();
    
    thread t3(func2,10,3);
    thread t4(func2,10,4);
    
    t3.join();
    t4.join();
    
    return 0;
}
