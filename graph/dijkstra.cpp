//dijkstra
struct dijkstra{
    vector<ll> dis;
    vector<ll> prev;

    //dijkstraを構築
    dijkstra(Graph &G, ll s){
        ll N = G.size();
        dis.assign(N, 1LL << 60);
        prev.assign(N, -1);
        priority_queue<pair<ll, ll>, vector<pair<ll, ll>>, greater<pair<ll, ll>>> pq;
        dis[s] = 0;
        pq.emplace(dis[s], s);
        while (!pq.empty()){
            auto p = pq.top();
            pq.pop();
            ll v = p.second;
            if(dis[v] < p.first)continue;
            for (auto &e : G[v]){
                if (dis[e.to] > dis[v] + e.cost){
                    dis[e.to] = dis[v] + e.cost;
                    prev[e.to] = v;
                    pq.emplace(dis[e.to], e.to);
                }
            }
        }
    }

    //最小コストを求める
    ll get_cost(ll to){
        return dis[to];
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
};
