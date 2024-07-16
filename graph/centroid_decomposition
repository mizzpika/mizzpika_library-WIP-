//centroid_decomposition
struct centroid_decomposition{
    Graph g;
    ll n;
    vector<ll> size;
    ll centroid;
    centroid_decomposition(Graph f) : g(f){
        g = f;
        n = g.size();
        size.resize(n, 1);
        stack<tuple<ll, ll, ll>> st;
        st.push({0, 0, 0});
        while (!st.empty()) {
            ll v, p, t;
            tie(v, p, t) = st.top();
            st.pop();

            if (t == 0) {
                st.push({v, p, 1});
                for (auto [c, d] : g[v]) {
                    if (c != p) {
                        st.push({c, v, 0});
                    }
                }
            } else {
                bool is_centroid = true;
                for (auto [c, d] : g[v]) {
                    if (c != p) {
                        size[v] += size[c];
                        if (size[c] > n / 2) {
                            is_centroid = false;
                        }
                    }
                }
                if (is_centroid && n - size[v] <= n / 2) {
                    centroid = v;
                }
            }
        }
    }
    
    //木の重心を求める
    ll get_centroid(){
        return centroid;
    }

    //重心によって分解された部分木を求める
    vector<vector<ll>> get_subtree(){
        vector<vector<ll>> comp(n);
        stack<tuple<ll, ll, ll>> st;
        for(auto [v, w] : g[centroid]){
            st.push({v, centroid, v});
        }

        while(!st.empty()){
            auto[v, p, i] = st.top();
            st.pop();
            comp[i].push_back(v);
            for(auto [c, d] : g[v]){
                if(c != p){
                    st.push({c, v, i});
                }
            }
        }

        return comp;
    }
};
