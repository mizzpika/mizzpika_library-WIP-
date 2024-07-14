//warshall_floyd
struct warshall_floyd{
    vector<vector<ll>> d;
    vector<vector<ll>> next;
    bool cl = false;

    //warshall_floydを構築
    warshall_floyd(Graph &g){
        ll n = g.size();
        d.resize(n, vector<ll>(n, 1LL << 60));
        next.resize(n, vector<ll>(n, -1));

        for(ll i = 0; i < n; i++){
            d[i][i] = 0;
        }

        for(ll i = 0; i < n; i++){
            for(auto e : g[i]){
                d[i][e.to] = e.cost;
                next[i][e.to] = e.to;
            }
        }

        for(ll k = 0; k < n; ++k){
            for(ll i = 0; i < n; ++i){
                for(ll j = 0; j < n; ++j){
                    if(d[i][k] == 1LL << 60 || d[k][j] == 1LL << 60)continue;
                    if(d[i][j] > d[i][k] + d[k][j]){
                        d[i][j] = d[i][k] + d[k][j];
                        next[i][j] = next[i][k];
                    }
                }
            }
        }

        for(ll i = 0; i < n; i++){
            if(d[i][i] < 0){
                cl = true;
                break;
            }
        }
    }
    
    //最小コストを求める
    ll get_cost(ll from, ll to){
        return d[from][to];
    }

    //最短経路を求める
    vector<ll> get_path(ll from, ll to) {
        if (d[from][to] == 1LL << 60) return {};
        vector<ll> path;
        for(ll at = from; at != to; at = next[at][to]){
            if (at == -1) return {};
            path.push_back(at);
        }
        path.push_back(to);
        return path;
    }

    //到達可能か調べる
    bool cango(ll from, ll to){
        return d[from][to] != 1LL << 60;
    }

    //負の閉路の有無を調べる
    bool closed(){
        return cl;
    }
};
