#include <bits/stdc++.h>
using namespace std;

mutex m;
condition_variable cv;
queue<int> q;
int x = 10;

void queue_push() {
    while(x>0) {
        this_thread::sleep_for(chrono::seconds(1));
        lock_guard<mutex> lock(m);
        q.push(x);
        cout << "Pushed: " << x << endl;
        x--;
        cv.notify_one();
    }
    
}

void queue_pop() {
    while(x > 0) {
    unique_lock<mutex> lock(m);
    cv.wait(lock, []{ return !q.empty();});
    auto itr = q.front();
    cout << "Popped: " << itr << endl;
    q.pop();
    }
}

int main() {
    thread t1(queue_push);
    thread t2(queue_pop);
    
    t1.join();
    t2.join();
    
    return 0;
}
