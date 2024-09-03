#pragma once
typedef long long ll;

namespace sortes {

template <typename T> void bubble(T *m, ll n) {
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

template <typename T> void n22(T *m, ll n) {}
} // namespace sortes
