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
#include <chrono>

// Не работает, но я не знаю почему //

using namespace std;

int n = 10;
const int mod = 1e9 + 7;

vector < int > storage;
mt19937 rng;
mutex m;
//unique_lock<mutex> lk(m);
condition_variable cv;
condition_variable cv_r;
int last_size = 0;
int mx = -1;


void writer()
{
    while(n != 0)
    {
        n--;

        unique_lock<mutex> lk(m);
        cv_r.wait(lk);
        //cout << "WRITE\n";
        int r = rng() / mod;
        cout << "r = " << r << "\n";

        storage.push_back(r);
        lk.unlock();
        cv.notify_all();
        //cout << "END WRITE\n";
    }
}

void reader()
{
    while (n != 0)
    {
        unique_lock<mutex> lk(m);
        cv.wait(lk/*, [] { return last_size != storage.size(); }*/);
        cout << "READ\n";
        if (storage.size() == 0)
        {
            lk.unlock();
            cv_r.notify_all();
            continue;
        }
        if (storage[storage.size() - 1] > mx)
        {
            mx = storage[storage.size() - 1];
            cout << "max = " << mx << "\n";
            //cout << "MESSAGE\n";
        }
        last_size++;
        lk.unlock();
        cv_r.notify_all();
    }
}


int main()
{
    rng.seed(std::chrono::high_resolution_clock::now().time_since_epoch().count());
    thread thr1(reader);
    thread thr2(writer);
    cv.notify_all();

    thr1.join();
    thr2.join();
}