#include <iostream>
#include <string>
#include <cmath>
#include <vector>
#include <set>
#include <algorithm>
#include <list>
#include <thread>
#include <mutex>

 
using namespace std;

mutex m;

void f(){
    for (int i = 0; i < 1000; i++){
        m.lock();
        cout << i << " " << this_thread::get_id() << "\n";
        m.unlock();
    }
}

int main() {
    thread a(f), b(f), c(f);

    a.join(); b.join(); c.join();
}