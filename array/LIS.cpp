template<typename T> vector<T> LIS(const vector<T> &x) {
    const T n = (T)x.size();
    vector<T> dp(n, numeric_limits<T>::max()), ret(n);
    // ret[i] : 最後の要素が x[i] である条件下の LIS の長さ
    for (ll i = 0; i < n; ++i) {
        auto itr = lower_bound(dp.begin(), dp.end(), x[i]);
        *itr = x[i];
        ret[i] = itr - dp.begin() + 1;
    }
    return ret;
}
