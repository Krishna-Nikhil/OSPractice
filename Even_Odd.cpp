#include<bits/stdc++.h>
using namespace std;

mutex m;
condition_variable cv;
int i =100;

void printEven() {
    while(i >= 0) {
        unique_lock<mutex> lock(m);
        cv.wait(lock, []{return (i%2==0);});
        cout << "Even: " << i << endl;
        i--;
        cv.notify_one();
    }
}

void printOdd() {
    while(i >0) {
        unique_lock<mutex> lock(m);
        cv.wait(lock, []{return (i%2==1);});
        cout << "Odd: " << i << endl;
        i--;
        cv.notify_one();
    }
}

int main() {
    thread t1(printEven);
    thread t2(printOdd);
    t1.join();
    t2.join();

    return 0;
}
