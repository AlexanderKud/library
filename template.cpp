#pragma once

#include<bits/stdc++.h>

#define rep(i, n) for(int i = 0; i < (int)(n); i++)
#define all(v) (v).begin(), (v).end()

using ll = long long;
using ull = unsigned long long;
using ld = long double;
using PLL = std::pair<ll, ll>;

constexpr int inf = 1e9;
constexpr ll INF = 1e18;
constexpr ld EPS = 1e-8;
constexpr ld PI = 3.1415926535897932384626;

template<class T, class U> inline constexpr bool chmin(T &a, const U &b) noexcept {
    if (a > b) {
        a = b;
        return true;
    }
    return false;
}
template<class T, class U> inline constexpr bool chmax(T &a, const U &b) noexcept {
    if (a < b) {
        a = b;
        return true;
    }
    return false;
}

inline constexpr ll gcd(ll a, ll b) noexcept {
    while (b) {
        const ll c = a;
        a = b;
        b = c % b;
    }
    return a;
}
inline constexpr ll lcm(ll a, ll b) noexcept {
    return a / gcd(a, b) * b;
}

inline constexpr ll my_pow(ll a, ll b) noexcept {
    ll res = 1;
    while (b) {
        if (b & 1) res *= a;
        b >>= 1;
        a *= a;
    }
    return res;
}
inline constexpr ll mod_pow(ll a, ll b, ll mod) noexcept {
    a %= mod;
    ll res = 1;
    while (b) {
        if (b & 1) (res *= a) %= mod;
        b >>= 1;
        (a *= a) %= mod;
    }
    return res;
}

template<class F> class rec_lambda {
  private:
    F f;
  public:
    explicit constexpr rec_lambda(F&& f_) : f(std::forward<F>(f_)) {}
    template<class... Args> constexpr auto operator()(Args&&... args) const {
        return f(*this, std::forward<Args>(args)...);
    }
};

template<class T, class Arg> constexpr std::vector<T> make_vec(size_t n, Arg&& arg) {
    return std::vector<T>(n, arg);
}
template<class T, class... Args> constexpr auto make_vec(size_t n, Args&&... args) {
    return std::vector<decltype(make_vec<T>(args...))>
               (n, make_vec<T>(std::forward<Args>(args)...));
}

inline constexpr int popcnt(ull x) {
#if __cplusplus >= 202002L
    return std::popcount(x);
#endif
    x = (x & 0x5555555555555555) + ((x >> 1 ) & 0x5555555555555555);
    x = (x & 0x3333333333333333) + ((x >> 2 ) & 0x3333333333333333);
    x = (x & 0x0f0f0f0f0f0f0f0f) + ((x >> 4 ) & 0x0f0f0f0f0f0f0f0f);
    x = (x & 0x00ff00ff00ff00ff) + ((x >> 8 ) & 0x00ff00ff00ff00ff);
    x = (x & 0x0000ffff0000ffff) + ((x >> 16) & 0x0000ffff0000ffff);
    return (x & 0x00000000ffffffff) + ((x >> 32) & 0x00000000ffffffff);
}

template<class T> class presser : public std::vector<T> {
  private:
    using size_type = size_t;
    using Base = std::vector<T>;
  public:
    using Base::Base;
    presser(const std::vector<T>& vec) : Base(vec) {}
    void push(const std::vector<T>& vec) {
        size_type n = this->size();
        this->resize(n + vec.size());
        std::copy(vec.begin(), vec.end(), this->begin() + n);
    }
    size_type build() {
        std::sort(this->begin(), this->end());
        this->erase(std::unique(this->begin(), this->end()), this->end());
        return this->size();
    }
    size_type get_index(const T& val) const {
        return std::lower_bound(this->begin(), this->end(), val) - this->begin();
    }
    std::vector<size_type> pressed(const std::vector<T>& vec) const {
        std::vector<size_type> res(vec.size());
        rep(i, vec.size()) res[i] = this->get_index(vec[i]);
        return res;
    }
    void press(std::vector<T>& vec) const {
        static_assert(std::is_integral<T>::value);
        rep(i, vec.size()) vec[i] = this->get_index(vec[i]);
    }
};
