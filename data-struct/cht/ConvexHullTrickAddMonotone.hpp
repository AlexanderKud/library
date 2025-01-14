#pragma once

#include "../../other/template.hpp"

template<class T = ll, bool is_max = false,
         class largeT = typename double_size_int<T>::type>
class ConvexHullTrickAddMonotone {
private:
    struct Line {
        T a, b;
        int idx;
        bool is_query;
        mutable T nxt_a, nxt_b;
        mutable bool has_nxt;
        T get(T x) const { return a * x + b; }
        T get_nxt(T x) const { return nxt_a * x + nxt_b; }
        Line() = default;
        Line(T a, T b, int id, bool i = false)
            : a(a), b(b), idx(id), is_query(i), has_nxt(false) {}
        friend bool operator<(const Line& lhs, const Line& rhs) {
            assert(!lhs.is_query || !rhs.is_query);
            if (lhs.is_query) {
                if (!rhs.has_nxt) return true;
                return rhs.get(lhs.a) < rhs.get_nxt(lhs.a);
            }
            if (rhs.is_query) {
                if (!lhs.has_nxt) return false;
                return lhs.get(rhs.a) > lhs.get_nxt(rhs.a);
            }
            return lhs.a == rhs.a ? lhs.b < rhs.b : lhs.a < rhs.a;
        }
    };
    int line_count = 0;
    std::deque<Line> que;
    bool is_necessary(const typename std::deque<Line>::iterator& itr) {
        if (itr != que.begin() && itr->a == prev(itr)->a)
            return itr->b < prev(itr)->b;
        if (itr != prev(que.end()) && itr->a == next(itr)->a)
            return itr->b < next(itr)->b;
        if (itr == que.begin() || itr == prev(que.end())) return true;
        return static_cast<largeT>(itr->b - prev(itr)->b) *
                   static_cast<largeT>(next(itr)->a - itr->a) <
               static_cast<largeT>(itr->b - next(itr)->b) *
                   static_cast<largeT>(prev(itr)->a - itr->a);
    }

public:
    ConvexHullTrickAddMonotone() = default;
    int add_line(T a, T b) {
        if IF_CONSTEXPR (is_max) a = -a, b = -b;
        typename std::deque<Line>::iterator itr;
        if (que.empty() || que.back().a <= a) {
            que.emplace_back(a, b, line_count);
            itr = prev(que.end());
        }
        else {
            assert(a <= que.front().a);
            que.emplace_front(a, b, line_count);
            itr = que.begin();
        }
        if (!is_necessary(itr)) {
            que.erase(itr);
            return line_count++;
        }
        while (itr != que.begin() && !is_necessary(prev(itr))) {
            que.pop_back();
            que.pop_back();
            que.emplace_back(a, b, line_count);
            itr = prev(que.end());
        }
        while (itr != prev(que.end()) && !is_necessary(next(itr))) {
            que.pop_front();
            que.pop_front();
            que.emplace_front(a, b, line_count);
            itr = que.begin();
        }
        if (itr != que.begin()) {
            prev(itr)->nxt_a = itr->a;
            prev(itr)->nxt_b = itr->b;
            prev(itr)->has_nxt = true;
        }
        if (itr != prev(que.end())) {
            itr->nxt_a = next(itr)->a;
            itr->nxt_b = next(itr)->b;
            itr->has_nxt = true;
        }
        else itr->has_nxt = false;
        return line_count++;
    }
    struct line {
        T a, b;
        int idx;
    };
    line get_min_line(T x) const {
        auto itr = lower_bound(all(que), Line{x, 0, -1, true});
        Line res{*itr};
        return line{is_max ? -res.a : res.a, is_max ? -res.b : res.b, res.idx};
    }
    T get_min(T x) const {
        const auto& l = get_min_line(x);
        return l.a * x + l.b;
    }
    line dec_get_min_line(T x) {
        while (que.size() > 1 &&
               que.begin()->get(x) > next(que.begin())->get(x))
            que.pop_front();
        Line res{que.front()};
        return line{is_max ? -res.a : res.a, is_max ? -res.b : res.b, res.idx};
    }
    T dec_get_min(T x) {
        const auto& l = dec_get_min_line(x);
        return l.a * x + l.b;
    }
    line inc_get_min_line(T x) {
        while (que.size() > 1 &&
               prev(que.end())->get(x) > prev(que.end(), 2)->get(x))
            que.pop_back();
        Line res{que.back()};
        return line{is_max ? -res.a : res.a, is_max ? -res.b : res.b, res.idx};
    }
    T inc_get_min(T x) {
        const auto& l = inc_get_min_line(x);
        return l.a * x + l.b;
    }
    bool empty() const { return que.empty(); }
};

/**
 * @brief ConvexHullTrickAddMonotone
 * @docs docs/data-struct/cht/ConvexHullTrickAddMonotone.md
 */
