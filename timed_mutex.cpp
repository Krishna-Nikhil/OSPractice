/*
timed_mutex is used for making the mutex wait for a specific time.
Normal mutex lock keeps on waiting and try_lock instantaneously stops.
try_lock_for and try_lock_until can be used in such cases.
They take input as time, try_lock_until takes reference time.
*/

#include <bits/stdc++.h>
using namespace std;

timed_mutex m;

void func1() {
    m.lock();
    cout << "T1 got the lock" << endl;
    this_thread::sleep_for(chrono::seconds(2));
    m.unlock();
}

void func2() {
        if(m.try_lock_for(chrono::seconds(3))) { // if(m.try_lock_until(chrono::steady_clock::now() + chrono::seconds(3))) {
            cout << "T2 got the lock" << endl;
            m.unlock();
        } else {
            this_thread::sleep_for(chrono::seconds(1));
            cout << "T2 is waiting for the lock" << endl;
        }
}

int main() {
    thread t1(func1);
    thread t2(func2);
    
    t1.join();
    t2.join();
    
    return 0;
}
