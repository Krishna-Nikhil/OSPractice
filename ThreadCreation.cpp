#include<bits/stdc++.h>
using namespace std;

void func(int x) { 
    while(x --> 0)
        cout << " " << x;
}

auto fun = [](int x) { 
    while(x --> 0)
        cout << " " << x;
    };
    
class base { 
    public:
    void operator () (int x) {
        while(x --> 0)
        cout << " " << x;
    }
};

class Thread {
    public:
    void print1(int x) {
        while(x --> 0)
        cout << " " << x;
    }
    
    static void print2(int x) {
        while(x --> 0)
        cout << " " << x;
    }
};

int main() {
    
    thread t1(fun,10); // Using Function Pointers
    t1.join();
    
    thread t2([](int x) { // Using Lambda
        while(x --> 0)
        cout << " " << x;
    },10);
    t2.join();
    
    thread t3(base(),10); // Using Functors
    t3.join();
    
    Thread t; 
    thread t4(&Thread::print1, &t, 10); // Using Non-static Member Functions
    t4.join();
    
    thread t5(&Thread::print2, 10); // Using static Member Functions
    t5.join();    
    
    return 0;
}
