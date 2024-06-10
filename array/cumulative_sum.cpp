//配列の累積和を1-indexedで求める
template<typename T> vector<T> cumulative_sum(vector<T> &v){
    ll n = v.size();
    vector<T> res(n + 1);
    for(ll i = 0; i < n; ++i){
        res[i + 1] = res[i] + v[i];
    }
    return res;
}
