

#include <bits/stdc++.h>
using namespace std;

static const string AA_ORDER = "ACDEFGHIKLMNPQRSTVWY";

static const int BLOSUM62[20][20] = {
    { 4, 0,-2,-1,-2, 0,-2,-1,-1,-1,-1,-2,-1,-1,-1, 1, 0, 0,-3,-2}, // A
    { 0, 9,-3,-4,-2,-3,-3,-1,-3,-1,-1,-3,-3,-3,-3,-1,-1,-1,-2,-2}, // C
    {-2,-3, 6, 2,-3,-1,-1,-3,-1,-4,-3, 1,-1, 0,-2, 0,-1,-3,-4,-3}, // D
    {-1,-4, 2, 5,-3,-2, 0,-3, 1,-3,-2, 0,-1, 2, 0, 0,-1,-2,-3,-2}, // E
    {-2,-2,-3,-3, 6,-3,-1, 0,-3, 0, 0,-3,-4,-3,-3,-2,-2,-1, 1, 3}, // F
    { 0,-3,-1,-2,-3, 6,-2,-4,-2,-4,-3, 0,-2,-2,-2, 0,-2,-3,-2,-3}, // G
    {-2,-3,-1, 0,-1,-2, 8,-3,-1,-3,-2, 1,-2, 0, 0,-1,-2,-3,-2, 2}, // H
    {-1,-1,-3,-3, 0,-4,-3, 4,-3, 2, 1,-3,-3,-3,-3,-2,-1, 3,-3,-1}, // I
    {-1,-3,-1, 1,-3,-2,-1,-3, 5,-2,-1, 0,-1, 1, 2, 0,-1,-2,-3,-2}, // K
    {-1,-1,-4,-3, 0,-4,-3, 2,-2, 4, 2,-3,-3,-2,-2,-2,-1, 1,-2,-1}, // L
    {-1,-1,-3,-2, 0,-3,-2, 1,-1, 2, 5,-2,-2, 0,-1,-1,-1, 1,-1,-1}, // M
    {-2,-3, 1, 0,-3, 0, 1,-3, 0,-3,-2, 6,-2, 0, 0, 1, 0,-3,-4,-2}, // N
    {-1,-3,-1,-1,-4,-2,-2,-3,-1,-3,-2,-2, 7,-1,-2,-1,-1,-2,-4,-3}, // P
    {-1,-3, 0, 2,-3,-2, 0,-3, 1,-2, 0, 0,-1, 5, 1, 0,-1,-2,-2,-1}, // Q
    {-1,-3,-2, 0,-3,-2, 0,-3, 2,-2,-1, 0,-2, 1, 5,-1,-1,-3,-3,-2}, // R
    { 1,-1, 0, 0,-2, 0,-1,-2, 0,-2,-1, 1,-1, 0,-1, 4, 1,-2,-3,-2}, // S
    { 0,-1,-1,-1,-2,-2,-2,-1,-1,-1,-1, 0,-1,-1,-1, 1, 5, 0,-2,-2}, // T
    { 0,-1,-3,-2,-1,-3,-3, 3,-2, 1, 1,-3,-2,-2,-3,-2, 0, 4,-3,-1}, // V
    {-3,-2,-4,-3, 1,-2,-2,-3,-3,-2,-1,-4,-4,-2,-3,-3,-2,-3,11, 2}, // W
    {-2,-2,-3,-2, 3,-3, 2,-1,-2,-1,-1,-2,-3,-1,-2,-2,-2,-1, 2, 7}  // Y
};

inline int aa_index(char c) {
    if (c >= 'a' && c <= 'z') c = c - 'a' + 'A';
    for (int k = 0; k < 20; ++k) if (AA_ORDER[k] == c) return k;
    return -1;
}

static string strip_whitespace_and_upper(const string& s) {
    string out;
    out.reserve(s.size());
    for (char c : s) {
        if (!isspace((unsigned char)c)) {
            if (c >= 'a' && c <= 'z') out.push_back(c - 'a' + 'A');
            else out.push_back(c);
        }
    }
    return out;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    string a_raw, b_raw;
    if (!getline(cin, a_raw)) return 0;
    if (!getline(cin, b_raw)) return 0;
    string a = strip_whitespace_and_upper(a_raw);
    string b = strip_whitespace_and_upper(b_raw);

    const int alpha = -11;
    const int beta  = -1;

    const int n = (int)a.size();
    const int m = (int)b.size();
    const int W = m + 1;
    const int H = n + 1;
    auto idx = [W](int i, int j){ return i * W + j; };

    vector<int> M(H*W, 0), Ix(H*W, 0), Iy(H*W, 0);

    int BEST = 0, end_i = 0, end_j = 0, end_state = 0;

    for (int i = 1; i <= n; ++i) {
        int ai = aa_index(a[i-1]);
        for (int j = 1; j <= m; ++j) {
            int bj = aa_index(b[j-1]);

            int ix_open = M[idx(i-1,j)] + alpha;
            int ix_ext  = Ix[idx(i-1,j)] + beta;
            Ix[idx(i,j)] = max(0, max(ix_open, ix_ext));

            int iy_open = M[idx(i,j-1)] + alpha;
            int iy_ext  = Iy[idx(i,j-1)] + beta;
            Iy[idx(i,j)] = max(0, max(iy_open, iy_ext));

            int s = (ai >= 0 && bj >= 0) ? BLOSUM62[ai][bj] : -4;

            int m_fromM  = M[idx(i-1,j-1)] + s;
            int m_fromIx = Ix[idx(i-1,j-1)] + s;
            int m_fromIy = Iy[idx(i-1,j-1)] + s;
            M[idx(i,j)] = max(0, max(m_fromM, max(m_fromIx, m_fromIy)));

            int cell_best = M[idx(i,j)];
            int cell_state = 0;
            if (Ix[idx(i,j)] > cell_best) { cell_best = Ix[idx(i,j)]; cell_state = 1; }
            if (Iy[idx(i,j)] > cell_best) { cell_best = Iy[idx(i,j)]; cell_state = 2; }
            if (cell_best > BEST) {
                BEST = cell_best;
                end_i = i; end_j = j; end_state = cell_state;
            }
        }
    }

    int i = end_i, j = end_j, state = end_state;
    while (i > 0 && j > 0) {
        int Mij = M[idx(i,j)], Ixij = Ix[idx(i,j)], Iyij = Iy[idx(i,j)];
        if (max({Mij, Ixij, Iyij}) <= 0) break;

        if (state == 0) {
            int ai = aa_index(a[i-1]);
            int bj = aa_index(b[j-1]);
            int s = (ai >= 0 && bj >= 0) ? BLOSUM62[ai][bj] : -4;

            int fromM  = M[idx(i-1,j-1)] + s;
            int fromIx = Ix[idx(i-1,j-1)] + s;
            int fromIy = Iy[idx(i-1,j-1)] + s;

            if (Mij == max(0, fromM) && fromM > 0) { --i; --j; state = 0; }
            else if (Mij == max(0, fromIx) && fromIx > 0) { --i; --j; state = 1; }
            else if (Mij == max(0, fromIy) && fromIy > 0) { --i; --j; state = 2; }
            else { --i; --j; state = 0; } // defensive
        } else if (state == 1) {
            int ix_open = M[idx(i-1,j)] + alpha;
            int ix_ext  = Ix[idx(i-1,j)] + beta;
            if (Ixij == max(0, ix_open) && ix_open > 0) { --i; state = 0; }
            else if (Ixij == max(0, ix_ext)  && ix_ext  > 0) { --i; state = 1; }
            else { --i; state = 1; }
        } else {
            int iy_open = M[idx(i,j-1)] + alpha;
            int iy_ext  = Iy[idx(i,j-1)] + beta;
            if (Iyij == max(0, iy_open) && iy_open > 0) { --j; state = 0; }
            else if (Iyij == max(0, iy_ext)  && iy_ext  > 0) { --j; state = 2; }
            else { --j; state = 2; }
        }
    }
    int start_i = i, start_j = j;

    cout << BEST << '\n'
         << a.substr(start_i, end_i - start_i) << '\n'
         << b.substr(start_j, end_j - start_j) << '\n';

    return 0;
}