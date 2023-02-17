#include <iostream>
#include <string>
#include <cmath>
#include <vector>
#include <set>
#include <algorithm>
#include <list>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <random>
#include <future>

 
using namespace std;

void f1(shared_future<string> sf){
    string x = sf.get();
    cout << "\nWelcome, " + x + " !\n";
}

void f2(promise<string> p){
    string username;
    cin >> username;
    p.set_value(username);
}

int main(){
    promise < string > prm;

    shared_future < string > sf = prm.get_future().share();

    thread t1(f1, sf), t2(f2, std::move(prm));
    t1.join(); t2.join();
}