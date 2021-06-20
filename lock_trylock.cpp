/*
Mutex will either lock or unlock the critical section for a thread.
If the resource is locked by one thread, then encountering mutex_var.lock() by the other thread makes it wait \
till the lock is released.
In case of mutex_var.try_lock(), if the value is false, then the thread wont wait for it anymore. It continues \
its execution.
*/

#include <bits/stdc++.h>
using namespace std;

mutex m;

void func1() {
    m.lock();
    cout << "T1 got the lock" << endl;
    this_thread::sleep_for(chrono::seconds(2));
    m.unlock();
}

void func2() {
    bool key = false;
    // while(!key) {                // If you want to wait till T1 releases lock uncomment this.
        if(m.try_lock()) {
            cout << "T2 got the lock" << endl;
            key = true;
            m.unlock();
        } else {
            this_thread::sleep_for(chrono::seconds(1));
            cout << "T2 is waiting for the lock" << endl;
        }
    // }
}

int main() {
    thread t1(func1);
    thread t2(func2);
    
    t1.join();
    t2.join();
    
    return 0;
}
