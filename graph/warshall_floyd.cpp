template<typename T>void warshall_floyd(vector<vector<T>> &g){
    const auto INF = numeric_limits<T>::max();
    for(ll k = 0; k < g.size(); ++k){
        for(ll i = 0; i < g.size(); ++i){
            for(ll j = 0; j < g.size(); ++j){
                if(g[i][k] == INF || g[k][j] == INF)continue;
                chmin(g[i][j] , g[i][k] + g[k][j]);
            }
        }
    }
}
