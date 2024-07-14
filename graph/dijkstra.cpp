//dijkstra
struct dijkstra{
    vector<ll> dist;
    vector<ll> prev;

    //dijkstraを構築
    dijkstra(Graph &G, ll s){
        ll N = G.size();
        dist.assign(N, 1LL << 60);
        prev.assign(N, -1);
        priority_queue<pair<ll, ll>, vector<pair<ll, ll>>, greater<pair<ll, ll>>> pq;
        dist[s] = 0;
        pq.emplace(dist[s], s);
        while (!pq.empty()){
            auto p = pq.top();
            pq.pop();
            ll v = p.second;
            if(dist[v] < p.first)continue;
            for (auto &e : G[v]){
                if (dist[e.to] > dist[v] + e.cost){
                    dist[e.to] = dist[v] + e.cost;
                    prev[e.to] = v;
                    pq.emplace(dist[e.to], e.to);
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
        vector<ll> get_path;
        for (ll i = to; i != -1; i = prev[i]){
            get_path.push_back(i);
        }
        reverse(get_path.begin(), get_path.end());
        return get_path;
    }

    //到達可能か調べる
    bool cango(ll to){
        return dist[to] != 1LL << 60;
    }
};
