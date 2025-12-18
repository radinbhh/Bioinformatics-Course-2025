def score(a, b, c):
    if a != '_' and a == b == c:
        return 1
    return 0


def solve():
    import sys
    sys.setrecursionlimit(10**7)

    A = sys.stdin.readline().strip()
    B = sys.stdin.readline().strip()
    C = sys.stdin.readline().strip()

    n, m, k = len(A), len(B), len(C)

    dp = [[[0]*(k+1) for _ in range(m+1)] for _ in range(n+1)]
    parent = [[[None]*(k+1) for _ in range(m+1)] for _ in range(n+1)]

    for i in range(n+1):
        for j in range(m+1):
            for l in range(k+1):
                if i == 0 and j == 0 and l == 0:
                    continue

                best = -1
                move = None

                if i > 0 and j > 0 and l > 0:
                    val = dp[i-1][j-1][l-1] + score(A[i-1], B[j-1], C[l-1])
                    if val > best:
                        best = val
                        move = (i-1, j-1, l-1, A[i-1], B[j-1], C[l-1])

                if i > 0 and j > 0:
                    val = dp[i-1][j-1][l]
                    if val > best:
                        best = val
                        move = (i-1, j-1, l, A[i-1], B[j-1], '_')

                if i > 0 and l > 0:
                    val = dp[i-1][j][l-1]
                    if val > best:
                        best = val
                        move = (i-1, j, l-1, A[i-1], '_', C[l-1])

                if j > 0 and l > 0:
                    val = dp[i][j-1][l-1]
                    if val > best:
                        best = val
                        move = (i, j-1, l-1, '_', B[j-1], C[l-1])

                # 5) A, gap, gap
                if i > 0:
                    val = dp[i-1][j][l]
                    if val > best:
                        best = val
                        move = (i-1, j, l, A[i-1], '_', '_')

                # 6) gap, B, gap
                if j > 0:
                    val = dp[i][j-1][l]
                    if val > best:
                        best = val
                        move = (i, j-1, l, '_', B[j-1], '_')

                # 7) gap, gap, C
                if l > 0:
                    val = dp[i][j][l-1]
                    if val > best:
                        best = val
                        move = (i, j, l-1, '_', '_', C[l-1])

                dp[i][j][l] = best
                parent[i][j][l] = move

    # Reconstruct alignment
    i, j, l = n, m, k
    A_al, B_al, C_al = [], [], []

    while parent[i][j][l] is not None:
        pi, pj, pl, ca, cb, cc = parent[i][j][l]
        A_al.append(ca)
        B_al.append(cb)
        C_al.append(cc)
        i, j, l = pi, pj, pl

    A_al.reverse()
    B_al.reverse()
    C_al.reverse()

    # Output
    print(dp[n][m][k])
    print("".join(A_al))
    print("".join(B_al))
    print("".join(C_al))


if __name__ == "__main__":
    solve()
