def lcs_length(S, T):
    n, m = len(S), len(T)
    dp = [[0]*(m+1) for _ in range(n+1)]
    for i in range(1, n+1):
        for j in range(1, m+1):
            if S[i-1] == T[j-1]:
                dp[i][j] = dp[i-1][j-1] + 1
            else:
                dp[i][j] = max(dp[i-1][j], dp[i][j-1])
    return dp[n][m]

def max_gaps(S, T):
    ell = lcs_length(S, T)
    return len(S) + len(T) - 2 * ell


s1 = str(input())
s2 = str(input())
print(max_gaps(s1,s2))