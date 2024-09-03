#include "json.hpp"
#include "sortes.hpp"
#include <chrono>
#include <fstream>
#include <iostream>
#include <random>
using namespace std;
using namespace nlohmann;
typedef long long ll;
template <typename T> T rand(T min, T max) {
  unsigned seed = chrono::steady_clock::now().time_since_epoch().count();
  static default_random_engine e(seed);
  uniform_int_distribution<T> d(min, max);
  return d(e);
}

double get_time() {
  return chrono::duration_cast<chrono::microseconds>(
             chrono::steady_clock::now().time_since_epoch())
             .count() /
         1e6;
}

int main() {
  // ofstream f("1.csv", ios::out);
  json data;
  ll n = 100;
  int *m = new int[n];
  for (int i = 0; i < n; ++i) {
    m[i] = rand<int>(0, 100);
  }
  sortes::merge<int>(m, n);
  for (int i = 0; i < n; ++i)
    cout << m[i] << ' ';
  delete[] m;
  return 0;
}
