/*
relocking a resource might lead to deadlock ccondition. In case of recursive functions we need to use \
recursive_mutex which allows to re-lock the resource and also maintains a count.
once the critical section is executed, it unlocks it for the same no of times it is locked.
*/

#include <bits/stdc++.h>
using namespace std;

recursive_mutex m;

void func1(int x) {
    if(x >0) {
        m.lock();
        cout << "T1 got the lock:" << x << endl;
        this_thread::sleep_for(chrono::seconds(1));
        func1(--x);
    }
    m.unlock();
    cout << "T1 unlocked" << endl;
}

void func2(int x) {
    if(x >0) {
        m.lock();
        cout << "T2 got the lock:" << x << endl;
        this_thread::sleep_for(chrono::seconds(1));
        func2(--x);
    }
    m.unlock();
    cout << "T2 unlocked" << endl;
}

int main() {
    thread t1(func1,10);
    thread t2(func2,10);

    t1.join();
    t2.join();
    
    return 0;
}
