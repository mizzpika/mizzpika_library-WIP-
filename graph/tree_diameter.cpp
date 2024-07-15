//木の直径を求める
ll tree_diameter(Graph g){
    ll n = g.size();
    dijkstra d(g, 0);
    ll mx = 0, idx = -1;
    for(ll i = 0; i < n; i++){
        if(mx < d.get_cost(i)){
            mx = d.get_cost(i);
            idx = i;
        }
    }

    dijkstra d2(g, idx);
    ll mx2 = 0;
    for(ll i = 0; i < n; i++){
        if(mx2 < d2.get_cost(i)){
            mx2 = d2.get_cost(i);
        }
    }

    return mx2;
}
