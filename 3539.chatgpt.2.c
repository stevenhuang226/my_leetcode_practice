#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

#define MOD 1000000007

long long fact[1001], invfact[1001];
long long nums[20];
int numSize, m, k;

long long modpow(long long a, long long e) {
    long long r = 1;
    while (e) {
        if (e & 1) r = r * a % MOD;
        a = a * a % MOD;
        e >>= 1;
    }
    return r;
}

void init_fact() {
    fact[0] = 1;
    for (int i = 1; i <= 1000; i++)
        fact[i] = fact[i - 1] * i % MOD;
    invfact[1000] = modpow(fact[1000], MOD - 2);
    for (int i = 999; i >= 0; i--)
        invfact[i] = invfact[i + 1] * (i + 1) % MOD;
}

long long permutationCount(int *cnt, int len) {
    int total = 0;
    for (int i = 0; i < len; i++)
        total += cnt[i];
    long long res = fact[total];
    for (int i = 0; i < len; i++)
        res = res * invfact[cnt[i]] % MOD;
    return res;
}

// ---------- DFS 拆分模型 ----------

long long ans = 0;

void dfs(int *arr, int len) {
    if (len == m) {
        // 計算排列數 * 元素乘積
        int cnt[20] = {0};
        long long prod = 1;
        for (int i = 0; i < len; i++) {
            cnt[arr[i]]++;
            prod = prod * nums[arr[i]] % MOD;
        }
        long long perm = permutationCount(cnt, numSize);
        ans = (ans + prod * perm) % MOD;
        return;
    }

    for (int i = 0; i < len; i++) {
        if (arr[i] > 0) {
            int newArr[20];
            memcpy(newArr, arr, sizeof(int) * len);
            newArr[i]--;
            newArr[len] = arr[i] - 1; // 新增一個 x-1
            dfs(newArr, len + 1);
        }
    }
}

// ---------- 組合選取 ----------

void comb(int *chosen, int start, int depth) {
    if (depth == k) {
        dfs(chosen, k);
        return;
    }
    for (int i = start; i < numSize; i++) {
        chosen[depth] = i;
        comb(chosen, i + 1, depth + 1);
    }
}

// ---------- 主函式 ----------
int magicalSum(int* num, int numSize_, int m_, int k_) {
    numSize = numSize_;
    m = m_;
    k = k_;
    for (int i = 0; i < numSize; i++) nums[i] = num[i];
    init_fact();

    ans = 0;
    int chosen[20];
    comb(chosen, 0, 0);
    return (int)ans;
}

// ---------- 測試 ----------
int main(void) {
    int num[] = {5,4,3,2,1};
    int numSize = 5;
    int m = 2;
    int k = 2;
    printf("%d\n", magicalSum(num, numSize, m, k));
    return 0;
}

