struct Trie {
    char a_init;
    ll D;
    ll INVALID = -1;
    std::vector<std::vector<ll>> child;
    std::vector<ll> par;

    //最長共通接頭辞の合計
    ll ret = 0;

    //必ずresizeする(1LL<<21)とかでいい
    vector<ll> dp;

    using T_NODE = ll;
    std::vector<T_NODE> v_info;

    //Trieを構築
    Trie(char a_init = 'a', ll D = 26)
        : a_init(a_init), D(D), child(1, std::vector<ll>(D, INVALID)), par(1, -1), v_info(1) {}

    //ノードnowから文字cへ移動する    
    ll step(ll now, char c) const {
        if (now == INVALID) return INVALID;
        return child.at(now).at(c - a_init);
    }

    //文字列を追加
    ll add_word(const std::string &str, T_NODE info) {
        ll now = 0;
        for (auto &c : str) {
            if (child[now][c - a_init] == INVALID) {
                par.push_back(now);
                child[now][c - a_init] = child.size();
                child.emplace_back(D, INVALID);
                v_info.resize(child.size());
            }
            now = child[now][c - a_init];
            ret += dp.at(now);
            dp.at(now) += 1;
        }
        v_info[now] += info;
        return now;
    }
};
