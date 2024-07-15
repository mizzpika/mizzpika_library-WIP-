struct kruskal{
    ll n;
    vector<Edge2> edges;
    //kruskalの構築
    kruskal(Graph &g){
        n = g.size();
        for(ll i = 0; i < n; i++){
            for(auto e : g[i]){
                edges.emplace_back(i, e.to, e.cost);
            }
        }
    }

    //最小全域木のコストを求める
    ll get_mincost(){
        sort(edges.begin(), edges.end());
        UnionFind uf(n);
        ll ret = 0;
        for(auto e : edges){
            if(uf.unite(e.from, e.to))ret += e.cost;
        }
        return ret;
    }

    //最大全域木のコストを求める
    ll get_maxcost(){
        sort(edges.rbegin(), edges.rend());
        UnionFind uf(n);
        ll ret = 0;
        for(auto e : edges){
            if(uf.unite(e.from, e.to))ret += e.cost;
        }
        return ret;
    }
};
