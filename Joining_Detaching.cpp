/*
When a thread is joined, the parent thread waits for its execution to complete.
When a thread is detached, the parent thread seperates it child from execution.
Once the parent, thread terminates, the child thread's resources are lost.
In the below example, thread t2 is created from t1 and is detached.
Even after detaching t2, we can see the output because, the main thread is still running
because of this, t1's resources are maintained and because of which t3 is running.
once the 7secs timer is done, t1's resources are deallocated and thus t2 terminates.

In main function, if t1 is joined, then total 10 nos of t2 are printed because main waits for t1 to complete(3secs) \
and then waits for 7 secs.

In man function, if t1 is detached, and if there is no wait, there is no output, since main is waiting for 7 secs before deallocating \
t1's resources, t1 output comes and simultaneously t2 output comes for 7 nos.

Never Join or Detach a thread for 2 times. It leads to program termination.
Use Joinable function to check the status of the thread.
*/

#include<bits/stdc++.h>
using namespace std;

void func2() {
    int x = 100;
    while(x<110) {
        cout << " " << x << endl;
        x++;
        this_thread::sleep_for(chrono::seconds(1));
    }
}
void func1(int x) { 
    thread t2(func2);
    t2.detach();
    while(x --> 0)
        cout << " " << x;
    
    this_thread::sleep_for(chrono::seconds(3));
}

int main() {
    
    thread t1(func1,10);
    
    if(t1.joinable())
        t1.detach();

    this_thread::sleep_for(chrono::seconds(7));
    
    return 0;
}
