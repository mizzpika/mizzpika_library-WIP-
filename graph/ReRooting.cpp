template< typename sum_t, typename key_t >
struct ReRooting {
    struct Edge {
        ll to;
        key_t data;
        sum_t dp, ndp;
    };

    using F = function< sum_t(sum_t, sum_t) >;
    using G = function< sum_t(sum_t, key_t) >;

    vector< vector< Edge > > g;
    vector< sum_t > subdp, dp;
    vector< sum_t > init;
    const sum_t ident;
    const F f;
    const G gg;

    //1.頂点の数、2,DPと関数gの結果をマージする(dp, g)関数f、3.頂点同士の計算結果をdpに反映する(dp, 結果)関数g、4.単位元（大体0でいい）
    ReRooting(ll V, const F f, const G g, const sum_t &ident)
            : g(V), f(f), gg(g), ident(ident), subdp(V, ident), dp(V, ident), init(V, ident) {}

    //無向辺を両方向同時に追加する
    void add_edge(ll u, ll v, const key_t &d) {
        g[u].emplace_back((Edge) {v, d, ident, ident});
        g[v].emplace_back((Edge) {u, d, ident, ident});
    }

    void add_edge_bi(ll u, ll v, const key_t &d, const key_t &e) {
        g[u].emplace_back((Edge) {v, d, ident, ident});
        g[v].emplace_back((Edge) {u, e, ident, ident});
    }

    //i番目の頂点をsにsetする
    void set(ll idx, sum_t s){
        subdp[idx] = s;
        init[idx] = s;
    }
    void dfs_sub(ll idx, ll par) {
        for(auto &e : g[idx]) {
            if(e.to == par) continue;
            dfs_sub(e.to, idx);
            subdp[idx] = f(subdp[idx], gg(subdp[e.to], e.data));
        }
    }

    void dfs_all(ll idx, ll par, const sum_t &top) {
        sum_t buff{init[idx]};
        for(ll i = 0; i < (ll) g[idx].size(); i++) {
            auto &e = g[idx][i];
            e.ndp = buff;
            e.dp = gg(par == e.to ? top : subdp[e.to], e.data);
            buff = f(buff, e.dp);
        }
        dp[idx] = buff;
        buff = ident;
        for(ll i = (ll) g[idx].size() - 1; i >= 0; i--) {
            auto &e = g[idx][i];
            if(e.to != par) dfs_all(e.to, idx, f(e.ndp, buff));
            e.ndp = f(e.ndp, buff);
            buff = f(buff, e.dp);
        }
    }

    //ReRootingの情報が入ったdp配列を返す
    vector< sum_t > build() {
        dfs_sub(0, -1);
        dfs_all(0, -1, ident);
        return dp;
    }
};
