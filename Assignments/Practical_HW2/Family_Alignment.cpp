#include <bits/stdc++.h>
using namespace std;

static inline int matchScore(char a, char b){ return (a==b?1:-1); }

vector<int> nw_prefix(const string &w, const string &s){
    int n=w.size(), m=s.size();
    vector<int> prev(m+1), cur(m+1), result(m+1);

    for(int j=0;j<=m;j++) prev[j] = -j;
    result[0] = -n;

    for(int i=1;i<=n;i++){
        cur[0] = -i;
        for(int j=1;j<=m;j++){
            int ms = matchScore(w[i-1], s[j-1]);
            cur[j] = max({ prev[j-1] + ms, prev[j] - 1, cur[j-1] - 1 });
        }
        result[0] = cur[0];
        for(int j=1;j<=m;j++) result[j] = cur[j];
        swap(prev, cur);
    }
    return result;
}


vector<int> nw_suffix(const string &w, const string &s){
    string rw = w;
    string rs = s;
    reverse(rw.begin(), rw.end());
    reverse(rs.begin(), rs.end());

    vector<int> pref = nw_prefix(rw, rs);
    vector<int> result(s.size()+1);

    for(int k=0;k<= (int)s.size(); k++){
        result[s.size() - k] = pref[k];
    }
    return result;
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    string s;
    int n;
    cin >> s >> n;

    vector<string> w(n);
    for(int i=0;i<n;i++) cin >> w[i];

    vector<vector<int>> pref(n), suff(n);
    int m = s.size();

    for(int i=0;i<n;i++){
        pref[i] = nw_prefix(w[i], s);
        suff[i] = nw_suffix(w[i], s);
    }

    int best = INT_MIN;
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            const auto &A = pref[i];
            const auto &B = suff[j];
            for(int k=0;k<=m;k++){
                best = max(best, A[k] + B[k]);
            }
        }
    }

    cout << best;
}
