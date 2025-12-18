def needleman_wunsch(seq1: str, seq2: str):
    seq1 = "".join(seq1.split())
    seq2 = "".join(seq2.split())

    gap = -1

    score = {
        ('A', 'A'): 3, ('A', 'T'): -2, ('A', 'C'): -1, ('A', 'G'): 0,
        ('T', 'A'): -2, ('T', 'T'): 3, ('T', 'C'): 0, ('T', 'G'): -1,
        ('C', 'A'): -1, ('C', 'T'): 0, ('C', 'C'): 3, ('C', 'G'): -2,
        ('G', 'A'): 0, ('G', 'T'): -1, ('G', 'C'): -2, ('G', 'G'): 3,
    }

    len1, len2 = len(seq1), len(seq2)

    dp = [[0] * (len2 + 1) for _ in range(len1 + 1)]

    for i in range(1, len1 + 1):
        dp[i][0] = i * gap
    for j in range(1, len2 + 1):
        dp[0][j] = j * gap

    for i in range(1, len1 + 1):
        c1 = seq1[i - 1]
        row = dp[i]
        prev_row = dp[i - 1]
        for j in range(1, len2 + 1):
            c2 = seq2[j - 1]
            row[j] = max(
                prev_row[j - 1] + score[(c1, c2)],
                prev_row[j] + gap,
                row[j - 1] + gap
            )

    aligned1 = []
    aligned2 = []
    i, j = len1, len2

    while i > 0 or j > 0:
        c1 = seq1[i - 1] if i > 0 else None
        c2 = seq2[j - 1] if j > 0 else None

        if i > 0 and j > 0 and dp[i][j] == dp[i - 1][j - 1] + score[(c1, c2)]:
            aligned1.append(c1)
            aligned2.append(c2)
            i -= 1
            j -= 1
        elif i > 0 and dp[i][j] == dp[i - 1][j] + gap:
            aligned1.append(c1)
            aligned2.append('_')
            i -= 1
        else:
            aligned1.append('_')
            aligned2.append(c2)
            j -= 1

    aligned1.reverse()
    aligned2.reverse()

    return dp[len1][len2], "".join(aligned1), "".join(aligned2)


if __name__ == "__main__":
    seq1 = input().strip()
    seq2 = input().strip()

    score, a1, a2 = needleman_wunsch(seq1, seq2)
    print(score)
    print(a1)
    print(a2)
