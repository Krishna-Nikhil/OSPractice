/*
Promise can be set by using set_value of set_value_at_thread_exit funcitons

An Async task can be created on a seperate thread, made to execute on main thread or can be left to the compiler \
to decide in run time.
If is made to launch as async, it immediately creates a new thread.

If it is made to launch as deferred, it doesnt create a new thread instantaneosuly, but it leads to \
lazy execution and when get method is called the execution happens in the current thread itself.

*/

#include <bits/stdc++.h>
using namespace std;

void func(promise<int>&& value, int count) {
    value.set_value_at_thread_exit(count);
    this_thread::sleep_for(chrono::seconds(2));
}

int main() {
    cout << "Main thread: " << this_thread::get_id() << endl;
    promise<int> prom_value;
    future<int> f1 = prom_value.get_future();
    thread t1(func, move(prom_value), 8);
    cout << "Waiting...!!!" << endl;
    cout << f1.get() << endl;
    t1.join();
    
    packaged_task<int()> task ([]{return 9;});
    future<int> f2 = task.get_future();
    thread t2(move(task)); // or task(); to run in current thread.
    cout << f2.get() << endl;
    t2.join();
    
    future<int> f3 = async(launch::async, []{cout << "Async Thread ID: " << this_thread::get_id() << endl; return 10;});
    cout << f3.get() << endl;
    
    future<int> f4 = async(launch::deferred, []{cout << "Deferred Thread ID: " << this_thread::get_id() << endl; return 11;});
    cout << f4.get() << endl;
    
    return 0;
}
