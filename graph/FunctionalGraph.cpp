struct FunctionalGraph {
    struct Doubling;
    template <typename T, T(*)(T, T), T(*)()>
    struct DoublingSum;
    friend struct Doubling;
    template <typename T, T(*op)(T, T), T(*e)()>
    friend struct DoublingSum;

    FunctionalGraph() : FunctionalGraph(0) {}//頂点数0で初期化
    FunctionalGraph(ll n) : _n(n), _nxt(n) {}//頂点数nで初期化
    FunctionalGraph(const std::vector<ll>& nxt) : _n(nxt.size()), _nxt(nxt) {}//配列で初期化

    const ll& operator[](ll u) const {//頂点uの次の頂点を取得または設定
        return _nxt[u];
    }
    ll& operator[](ll u) {
        return _nxt[u];
    }

    struct Doubling {
        friend struct FunctionalGraph;

        ll query(ll u, long long d) const {//uからdステップ後の頂点
            for (ll l = _log; l >= 0; --l) if ((d >> l) & 1) u = _nxt[l][u];
            return u;
        }

        struct BinarySearchResult {
            ll v;
            long long step;
            operator std::pair<ll, long long>() const { return std::pair<ll, long long>{ v, step }; }
        };

        template <typename Pred>
        auto max_step(ll u, Pred &&f) const {//uから、命題fが真になるまでの最大ステップ数
            assert(f(u));
            long long step = 0;
            for (ll l = _log; l >= 0; --l) if (ll nxt_u = _nxt[l][u]; f(nxt_u)) {
                u = nxt_u, step |= 1LL << l;
            }
            return BinarySearchResult{ u, step };
        }

        template <typename Pred>
        std::optional<BinarySearchResult> step_until(ll u, Pred &&f) const {//先ほどに加え、真にならない場合は"nullopt"を返す
            if (f(u)) return BinarySearchResult { u, 0 };
            auto [v, step] = max_step(u, [&](ll v) { return not f(v); });
            v = _nxt[0][v], ++step;
            if (not f(v)) return std::nullopt;
            return BinarySearchResult{ v, step };
        }

    private:
        ll _n, _log;
        std::vector<std::vector<ll>> _nxt;

        Doubling(const std::vector<ll>& nxt, long long max_step) : _n(nxt.size()), _log(floor_log2(max_step)), _nxt(_log + 1, std::vector<ll>(_n)) {
            _nxt[0] = nxt;
            for (ll i = 1; i <= _log; ++i) for (ll j = 0; j < _n; ++j) {
                _nxt[i][j] = _nxt[i - 1][_nxt[i - 1][j]];
            }
        }
    };

    template <typename T, T(*op)(T, T), T(*e)()>
    struct DoublingSum : private Doubling {
        friend struct FunctionalGraph;

        struct Result {
            ll v;
            T sum;
            operator std::pair<ll, T>() const { return std::pair<ll, T>{ v, sum }; }
        };

        auto query(ll u, long long d) const {//uからdステップ後の頂点と累積和
            T sum = e();
            for (ll l = _log; l >= 0; --l) if ((d >> l) & 1) sum = op(sum, _dat[l][std::exchange(u, _nxt[l][u])]);
            return Result{ u, sum };
        }

        struct BinarySearchResult {//累積和が命題fを満たす最大ステップ数
            ll v;
            T sum;
            long long step;
            operator std::tuple<ll, T, long long>() const { return std::tuple<ll, T, long long>{ v, sum, step }; }
        };

        template <typename Pred>
        auto max_step(ll u, Pred &&f) const {//累積和がfを満たすまでのステップ数
            assert(f(e()));
            long long step = 0;
            T sum = e();
            for (ll l = _log; l >= 0; --l) {
                if (T nxt_sum = op(sum, _dat[l][u]); f(nxt_sum)) {
                    sum = std::move(nxt_sum), u = _nxt[l][u], step |= 1LL << l;
                }
            }
            return BinarySearchResult{ u, sum, step };
        }
        template <typename Pred>
        std::optional<BinarySearchResult> step_until(ll u, Pred &&f) const {
            if (f(e())) return BinarySearchResult { u, e(), 0 };
            auto [v, sum, step] = max_step(u, [&](const T& v) { return not f(v); });
            sum = op(sum, _dat[0][v]), v = _nxt[0][v], ++step;
            if (not f(sum)) return std::nullopt;
            return BinarySearchResult{ v, sum, step };
        }

    private:
        std::vector<std::vector<T>> _dat;

        DoublingSum(const std::vector<ll>& nxt, long long max_step, const std::vector<T>& dat) : Doubling(nxt, max_step), _dat(_log + 1, std::vector<T>(_n, e())) {
            _dat[0] = dat;
            for (ll i = 1; i <= _log; ++i) for (ll j = 0; j < _n; ++j) {
                _dat[i][j] = op(_dat[i - 1][j], _dat[i - 1][_nxt[i - 1][j]]);
            }
        }
    };

    Doubling doubling(long long max_step) const {
        return Doubling(_nxt, max_step);
    }

    template <typename T, T(*op)(T, T), T(*e)()>
    DoublingSum<T, op, e> doubling(long long max_step, const std::vector<T>& dat) const {
        return DoublingSum<T, op, e>(_nxt, max_step, dat);
    }

    struct InfinitePath {
        ll head_v;//無限ループに入る前のパスの開始頂点
        ll head_len;//無限ループに入る前のパスの長さ
        ll loop_v;// 無限ループの開始頂点
        ll loop_len;//無限ループの長さ(自らが無限ループにいない時は0を返す)
        InfinitePath() = default;
        InfinitePath(ll head_v, ll head_len, ll loop_v, ll loop_len) : head_v(head_v), head_len(head_len), loop_v(loop_v), loop_len(loop_len) {}
    };

    std::vector<InfinitePath> infinite_paths() const {//無限ループパスを検出し、各頂点の無限ループの情報を返す(auto paths = )
        std::vector<InfinitePath> res(_n);

        std::vector<ll> vis(_n, _n);
        std::vector<ll> dep(_n, 0);

        ll time = 0;
        auto dfs = [&](auto dfs, ll u) -> ll {
            vis[u] = time;
            ll v = _nxt[u];
            if (vis[v] == vis[u]) { // found cycle
                ll loop_len = dep[u] - dep[v] + 1;
                res[u] = { u, 0, u, loop_len };
                return loop_len - 1;
            } else if (vis[v] < vis[u]) {
                res[u] = { u, res[v].head_len + 1, res[v].loop_v, res[v].loop_len };
                return 0;
            } else {
                dep[v] = dep[u] + 1;
                ll c = dfs(dfs, v);
                if (c > 0) { // in cycle
                    res[u] = { u, 0, u, res[v].loop_len };
                    return c - 1;
                } else { // out of cycle
                    res[u] = { u, res[v].head_len + 1, res[v].loop_v, res[v].loop_len };
                    return 0;
                }
            }
        };
        for (ll i = 0; i < _n; ++i, ++time) if (vis[i] == _n) dfs(dfs, i);
        return res;
    }

    /**
     * Calculates k'th iterate: f(f(f(...f(i)))) for all 0 <= i < N in O(N) time.
     * Reference: https://noshi91.hatenablog.com/entry/2019/09/22/114149
     */
    std::vector<ll> kth_iterate(const long long k) const {//各頂点からkステップ後の頂点を計算
        assert(k >= 0);
        std::vector<ll> res(_n);
        std::vector<ll> forest_roots;
        std::vector<std::vector<ll>> forest(_n);
        std::vector<std::vector<std::pair<long long, ll>>> qs(_n);
        for (const auto& path : infinite_paths()) {
            const ll v = path.head_v;
            (path.head_len == 0 ? forest_roots : forest[_nxt[v]]).push_back(v);
            if (path.head_len >= k) continue;
            qs[path.loop_v].emplace_back(k - path.head_len, v);
        }
        std::vector<ll> dfs_path(_n);
        auto dfs = [&](auto dfs, ll u, ll d) -> void {
            dfs_path[d] = u;
            if (d >= k) res[u] = dfs_path[d - k];
            for (ll v : forest[u]) dfs(dfs, v, d + 1);
        };
        for (ll root : forest_roots) dfs(dfs, root, 0);
        std::vector<int8_t> seen(_n, false);
        for (ll root : forest_roots) {
            if (seen[root]) continue;
            std::vector<ll> cycle{ root };
            for (ll v = _nxt[root]; v != root; v = _nxt[v]) cycle.push_back(v);
            const ll len = cycle.size();
            for (ll i = 0; i < len; ++i) {
                const ll s = cycle[i];
                seen[s] = true;
                for (const auto& [rem, res_index] : qs[s]) {
                    res[res_index] = cycle[(i + rem) % len];
                }
            }
        }
        return res;
    }

private:
    ll _n;
    std::vector<ll> _nxt;

    static ll floor_log2(long long v) {//与えられた値vの底が2の対数の床を計算
        ll l = 0;
        while (1LL << (l + 1) <= v) ++l;
        return l;
    }
};
