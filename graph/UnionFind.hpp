#pragma once

#include "../template.hpp"

class UnionFind {
  protected:
    int n;
    std::vector<int> par_vec;
  public:
    UnionFind() : UnionFind(0) {}
    UnionFind(int n) : n(n), par_vec(n, -1) {}
    int find(int x) {
        assert(0 <= x && x < n);
        return par_vec[x] < 0 ? x : par_vec[x] = find(par_vec[x]);
    }
    bool merge(int x, int y) {
        x = find(x);
        y = find(y);
        if (x == y) return false;
        if (par_vec[x] > par_vec[y]) std::swap(x, y);
        par_vec[x] += par_vec[y];
        par_vec[y] = x;
        return true;
    }
    bool same(int x, int y) {
        return find(x) == find(y);
    }
    int size(int x) {
        return -par_vec[find(x)];
    }
    std::vector<std::vector<int>> groups() {
        std::vector<std::vector<int>> res(n);
        rep(i, n) res[find(i)].push_back(i);
        res.erase(
            remove_if(res.begin(), res.end(),
                      [](const std::vector<int>& v) { return v.empty(); }),
            res.end());
        return res;
    }
    bool is_root(int x) const {
        assert(0 <= x && x < n);
        return par_vec[x] < 0;
    }
};

/**
 * @brief UnionFind
 * @docs docs/UnionFind.md
 */
