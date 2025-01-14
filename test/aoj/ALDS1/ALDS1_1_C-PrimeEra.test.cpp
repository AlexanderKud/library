#define PROBLEM "https://onlinejudge.u-aizu.ac.jp/problems/ALDS1_1_C"
#include "../../../other/template.hpp"
#include "../../../math/num/PrimeFactor.hpp"
using namespace std;
int main() {
    int n; scan >> n;
    PrimeFactor PF(100000000);
    int ans = 0;
    rep (n) {
        int a; scan >> a;
        if (PF.is_prime(a)) ans++;
    }
    print << ans << endl;
}
