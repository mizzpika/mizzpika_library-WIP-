//suffix_array
struct suffix_array{
    vector<ll> sa, rank, tmp;
    ll n;
    string base;

    //suffix_arrayを構築
    suffix_array(const string s){
        n = s.size();
        base = s;
        sa.resize(n);
        rank.resize(n);
        tmp.resize(n);

        for(ll i = 0; i < n; i++){
            sa[i] = i;
            rank[i] = s[i];
        }

        for(ll k = 1; k < n; k *= 2){
            auto compare_sa = [&](ll i, ll j){
                if(rank[i] != rank[j])return rank[i] < rank[j];
                ll ri = (i + k < n) ? rank[i + k] : -1;
                ll rj = (j + k < n) ? rank[j + k] : -1;
                return ri < rj;
            };
            sort(sa.begin(), sa.end(), compare_sa);

            tmp[sa[0]] = 0;
            for(ll i = 1; i < n; i++){
                tmp[sa[i]] = tmp[sa[i - 1]] + (compare_sa(sa[i - 1], sa[i])? 1 : 0);
            }
            rank = tmp;
        }
    }

    //部分文字列の個数を求める
    ll get_counts(string t){
        string u = t + "彁";
        ll num1, num2;
        {
            ll m = t.size();
            ll ng = -1, ok = n;
            while(ok - ng > 1){
                ll mid = (ng + ok) / 2;
                ll l = sa[mid];
                if(base.substr(l, m) >= t){
                    ok = mid;
                }else{
                    ng = mid;
                }
            }
            num1 = ok;
        }
        {
            ll m = u.size();
            ll ng = -1, ok = n;
            while(ok - ng > 1){
                ll mid = (ng + ok) / 2;
                ll l = sa[mid];
                if(base.substr(l, m) >= u){
                    ok = mid;
                }else{
                    ng = mid;
                }
            }
            num2 = ok;
        }
        return num2 - num1;
    }
};
