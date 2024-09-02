#include <iostream>
#include <chrono>
#include <random>
#include <fstream>
using namespace std;

typedef long long ll;
template <typename T>
T rand(T min, T max) {
  unsigned seed = chrono::steady_clock::now().time_since_epoch().count();
  static default_random_engine e(seed);
  uniform_int_distribution<T> d(min, max);
  return d(e);
}

double get_time() {
  return chrono::duration_cast<chrono::microseconds>
(chrono::steady_clock::now().time_since_epoch()).count()/1e6;
}

template <typename T>
void n21 (T *m, ll n) {
  for (int i = 0; i < n; ++i) {
    for (int j = i + 1; j < n; ++j) {
      if (m[i] > m[j]) {
        T t = m[i];
        m[i] = m[j];
        m[j] = t;
      }
    }
  }
} 
template <typename T>
void n22 (T *m, ll n) {

}
int main() {
  ofstream f("1.csv", ios::out);
  ll n = 100;
  int *m = new int[n];
  for (int i = 0; i < n; ++i) {
    m[i] = rand<int>(0,100);
  }
  n21<int>(m,n);
  for (int i = 0; i < n; ++i) f << m[i] << ' ';
  delete [] m;
  return 0;
}
