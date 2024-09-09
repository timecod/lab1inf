#pragma once
#include <chrono>
#include <random>
using namespace std;
namespace helper {
int rand(int min, int max) {
  unsigned seed = chrono::steady_clock::now().time_since_epoch().count();
  static default_random_engine e(seed);
  uniform_int_distribution<int> d(min, max);
  return d(e);
}

double get_time() {
  return chrono::duration_cast<chrono::microseconds>(
             chrono::steady_clock::now().time_since_epoch())
             .count() /
         1e6;
}
template <typename T>
double sort_time(void (*func)(T *, long long), long long n, char base_arr,
                 int min = -1000, int max = 1000) {
  T *m = new T[n];
  if (base_arr == 0) {
    for (long long i = 0; i < n; ++i) {
      m[i] = (int)i;
    }
  } else if (base_arr == 1) {
    for (long long i = 0; i < n; ++i) {
      m[i] = rand(min, max);
    }
  } else {
    for (long long i = 0; i < n; ++i) {
      m[n - i - 1] = (int)i;
    }
  }
  double start, end;
  start = get_time();
  func(m, n);
  end = get_time();
  delete[] m;
  return end - start;
}

} // namespace helper
