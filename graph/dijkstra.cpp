template<typename T>vector<T> dijkstra(graph<T> &g,ll s){
    const auto INF = numeric_limits<T>::max();
    vector<T> d(g.size(), INF);
    using P = pair<T, ll>;
    priority_queue<P, vector<P>, greater<P>> pq;
    d[s] = 0;
    pq.emplace(0, s);
    while(!pq.empty()){
        auto[cost, now] = pq.top();
        pq.pop();
        if(d[now] < cost)continue;
        for(auto &e : g[now]){
            if(d[e] <= d[now] + e.cost)continue;
            d[e] = d[now] + e.cost;
            pq.emplace(d[e], e.to);
        }
    }
    return d;
}
