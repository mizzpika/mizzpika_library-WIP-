template<typename T>struct edge{
    ll src, to; T cost;
    edge(ll to, T cost) : src(-1), to(to), cost(cost){}
    edge(ll src, ll to, T cost) : src(src), to(to), cost(cost){}
    edge &operator=(const ll &x){
        to = x;
        return *this;
    }
    operator ll() const {return to;}
};
template<typename T>using edges = vector<edge<T>>;
template<typename T>using graph = vector<edges<T>>;
