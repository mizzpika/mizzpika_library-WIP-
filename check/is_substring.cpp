//tがsの部分文字列かどうかをO(n)で判定
bool IsSubstring(string s,string t/*s > t*/){
    int cnt=0;
    for(int i=0;i<(int)s.size();i++){
        if(s[i]==t[cnt])cnt++;
        if(cnt==t.size())return true;
    }
    return false;
}
