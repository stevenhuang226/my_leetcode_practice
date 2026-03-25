// LeetCode 3539 - Find Sum of Array Product of Magical Sequences
// 暴力 + 去重 + 排列補權重版本
// 作者思路：Steven Huang (stevenhuang.dog@gmail.com)

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

#define MOD 1000000007

// ---------- bitcount 模組 ----------
// O(numSize)，不需實際組合 2^x
int bitcount_seq(int *seq, int seqSize, int numSize)
{
    int cnt[64] = {0};
    for (int i = 0; i < seqSize; i++)
        cnt[seq[i]]++;

    int bits = 0;
    for (int i = 0; i < numSize; i++) {
        bits += cnt[i] % 2;
        cnt[i + 1] += cnt[i] / 2;
    }
    return bits;
}

// ---------- 階乘模組 ----------
long long fact[1001];
long long invfact[1001];

long long modpow(long long a, long long e)
{
    long long r = 1;
    while (e) {
        if (e & 1) r = r * a % MOD;
        a = a * a % MOD;
        e >>= 1;
    }
    return r;
}

void init_fact()
{
    fact[0] = 1;
    for (int i = 1; i <= 1000; i++)
        fact[i] = fact[i - 1] * i % MOD;
    invfact[1000] = modpow(fact[1000], MOD - 2);
    for (int i = 999; i >= 0; i--)
        invfact[i] = invfact[i + 1] * (i + 1) % MOD;
}

// ---------- 排列數 ----------
long long permutationCount(int *cnt, int len)
{
    int total = 0;
    for (int i = 0; i < len; i++)
        total += cnt[i];

    long long res = fact[total];
    for (int i = 0; i < len; i++)
        res = res * invfact[cnt[i]] % MOD;

    return res;
}

// ---------- hash 模組（去重） ----------
typedef struct {
    int *arr;
    int len;
} SeqKey;

int cmpSeq(const void *a, const void *b)
{
    const SeqKey *A = (const SeqKey *)a;
    const SeqKey *B = (const SeqKey *)b;
    if (A->len != B->len) return A->len - B->len;
    return memcmp(A->arr, B->arr, A->len * sizeof(int));
}

// ---------- 主遞迴 ----------
int nums[10];
int numSize, k, m;
long long ans = 0;

void dfs(int *seq, int seqSize)
{
    if (seqSize == m) {
        if (bitcount_seq(seq, seqSize, numSize) == k) {
            // 統計數量
            int cnt[10] = {0};
            for (int i = 0; i < seqSize; i++)
                cnt[seq[i]]++;

            long long perm = permutationCount(cnt, numSize);

            long long prod = 1;
            for (int i = 0; i < seqSize; i++)
                prod = prod * nums[seq[i]] % MOD;

            ans = (ans + prod * perm) % MOD;
        }
        return;
    }

    for (int i = 0; i < numSize; i++) {
        seq[seqSize] = i;
        dfs(seq, seqSize + 1);
    }
}

// ---------- 主函式 ----------
int findSumOfArrayProductOfMagicalSequences(int* num, int numSize_, int m_, int k_)
{
    numSize = numSize_;
    m = m_;
    k = k_;
    memcpy(nums, num, sizeof(int) * numSize);
    init_fact();

    int seq[10];
    ans = 0;
    dfs(seq, 0);
    return (int)ans;
}

// ---------- 測試 ----------
int main(void)
{
    int num[] = {5,4,3,2,1};
    int numSize = 5;
    int m = 2;
    int k = 2;
    printf("%d\n", findSumOfArrayProductOfMagicalSequences(num, numSize, m, k));
    return 0;
}

