//bellman_ford
struct bellman_ford{
    vector<ll> dist;
    vector<ll> prev;
    ll start;
    ll size;
    bool cl = false;

    //bellman_fordを構築
    bellman_ford(Graph &g, ll s){
        start = s;
        ll n = g.size();
        size = n;
        dist.assign(n, 1LL << 60);
        prev.assign(n, -1);
        vector<ll> counts(n);
        vector<bool> inqueue(n);

        queue<ll> q;
        dist[s] = 0;
        q.push(s);
        inqueue[s] = true;

        while(!q.empty()){
            ll from = q.front();
            q.pop();
            inqueue[from] = false;

            for(auto &e : g[from]){
                ll d = dist[from] + e.cost;
                if(d < dist[e.to]){
                    dist[e.to] = d;
                    prev[e.to] = from;
                    if(!inqueue[e.to]){
                        q.push(e.to);
                        inqueue[e.to] = true;
                        ++counts[e.to];
                        
                        if(n < counts[e.to])cl = true;
                    }
                }
            }
        }
    }

    //最小コストを求める
    ll get_cost(ll to){
        return dist[to];
    }

    //最短経路を求める
    vector<ll> get_path(ll to){
        vector<ll> path;
        if(dist[to] != 1LL << 60){
            for(ll i = to; i != -1; i = prev[i]){
                path.push_back(i);
            }
            reverse(path.begin(), path.end());
        }
        return path;
    }

    //到達可能か調べる
    bool cango(ll to){
        return (dist[to] != 1LL << 60);
    }

    //負の閉路の有無を調べる
    bool closed(){
        return cl;
    }
};
