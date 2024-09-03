#pragma once
#include <iostream>
typedef long long ll;
namespace sortes {
// n2 sortes
template <typename T> void bubble(T *m, ll n) {
  ll i, j;
  for (i = 0; i < n; ++i) {
    for (j = i + 1; j < n; ++j) {
      if (m[i] > m[j]) {
        T t = m[i];
        m[i] = m[j];
        m[j] = t;
      }
    }
  }
}

template <typename T> void selection(T *m, ll n) {
  ll i, j;
  for (i = 0; i < n - 1; ++i) {
    ll jMin = i;
    for (j = i + 1; j < n; ++j)
      if (m[j] < m[jMin])
        jMin = j;

    if (jMin != i) {
      T t = m[i];
      m[i] = m[jMin];
      m[jMin] = t;
    }
  }
}
template <typename T> void insertion(T *m, ll n) {
  ll i, j;
  for (i = 1; i < n; ++i) {
    for (j = i; j > 0 && m[j - 1] > m[j]; --j) {
      T t = m[j];
      m[j] = m[j - 1];
      m[j - 1] = t;
    }
  }
}
// nlogn sortes
template <typename T> void merge(T *m, ll n) {
  if (n <= 1)
    return;
  // if (m[0] == m[1] && n == 2)
  //   return;
  merge<T>(m, n / 2);
  merge<T>(m + n / 2, n - n / 2);
  ll i = 0, j = n / 2;
  T r[n];
  for (ll k = 0; k < n; ++k)
    r[k] = m[k];
  for (ll k = 0; k < n; ++k)
    if (i < n / 2 && (j >= n || (r[i] <= r[j])))
      m[k] = r[i++];
    else
      m[k] = r[j++];
}

template <typename T> void heap(T *m, ll n) {
  ll L = n / 2, R = n, k, ch;
  bool f;
  while (R > 0) {
    if (L > 0) {
      L--;
    } else {
      R--;
      T t = m[R];
      m[R] = m[0];
      m[0] = t;
    }
    k = L;
    f = true;
    while (2 * k + 1 < R && f) {
      ch = 2 * k + 1;
      if (ch + 1 < R && m[ch] < m[ch + 1])
        ch++;
      if (m[k] < m[ch]) {
        T t = m[k];
        m[k] = m[ch];
        m[ch] = t;
        k = ch;
      } else {
        f = false;
      }
    }
  }
}
template <typename T> void quick(T *m, ll n) {
  if (n <= 1)
    return;
  T pivot = m[n - 1];
  ll p = 0;
  for (ll j = 0; j < n - 1; ++j) {
    if (m[j] <= pivot) {
      T t = m[p];
      m[p] = m[j];
      m[j] = t;
      p++;
    }
  }
  T t = m[p];
  m[p] = m[n - 1];
  m[n - 1] = t;
  quick<T>(m, p);
  quick<T>(m + p + 1, n - p - 1);
}
} // namespace sortes
