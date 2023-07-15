#define PROBLEM "https://judge.yosupo.jp/problem/pow_of_formal_power_series"
#include "../../../other/template.hpp"
#include "../../../math/poly/FormalPowerSeries.hpp"
#include "../../../math/ModInt.hpp"
using namespace std;
using mint = modint998244353;
int main() {
    int n; scan >> n;
    ll m; scan >> m;
    FormalPowerSeries<mint> a(n); scan >> a;
    prints(a.pow(m));
}
