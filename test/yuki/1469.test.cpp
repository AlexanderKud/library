#define PROBLEM "https://yukicoder.me/problems/no/1469"
#include "../../other/template.hpp"
#include "../../string/RunLength.hpp"
using namespace std;
int main() {
    string S; cin >> S;
    for (const auto& p : RunLength(S)) cout << p.first;
    cout << endl;
}
