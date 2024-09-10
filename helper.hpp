#pragma once
#include "json.hpp"
#include "sortes.hpp"
#include <chrono>
#include <iostream>
#include <random>
using namespace std;
using namespace nlohmann;
namespace helper {
const int SORTSCOUNT = 6;
string sorts[] = {"bubble", "selection", "insertion", "quick", "heap", "merge"};
string bases[] = {"sort", "rand", "rsort"};
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

template <typename T> struct functions {
  long long n;
  void (*arr[SORTSCOUNT])(T *, long long);
  functions()
      : arr{sortes::bubble, sortes::selection, sortes::insertion,
            sortes::quick,  sortes::heap,      sortes::merge},
        n(SORTSCOUNT) {}
};
template <typename T>
void create_data_of_type(json &config, json &output, string type_str,
                         int used_funcs[SORTSCOUNT], int min = -1000,
                         int max = 1000) {
  functions<T> FUNCS;
  int itk = 0;
  for (long long sort_id = 0; sort_id < FUNCS.n; ++sort_id) {
    if (sort_id != used_funcs[itk]) {
      continue;
    }
    itk++;
    for (long long item_number = config["itemNumber"]["start"];
         item_number < config["itemNumber"]["end"];
         item_number += (long long)config["itemNumber"]["step"]) {
      cout << item_number << '\n';
      for (long long accuracy_id = 0; accuracy_id < config["accuracy"];
           ++accuracy_id) {
        for (char base_arr = 0; base_arr < 3; ++base_arr) {
          double delta = -1;
          delta =
              sort_time<T>(FUNCS.arr[sort_id], item_number, base_arr, min, max);
          json r;
          r["type"] = type_str;
          r["itemNumber"] = item_number;
          r["sort"] = sorts[sort_id];
          r["accuracyId"] = accuracy_id;
          r["base"] = bases[base_arr];
          r["time"] = delta;
          output.push_back(r);
        }
      }
    }
  }
}
// del
struct mystruct {
  long bigboy[100];
  bool operator>(mystruct A) { return bigboy[0] > A.bigboy[0]; }
  mystruct() {}
  mystruct(int A) { bigboy[0] = A; }
};
} // namespace helper
