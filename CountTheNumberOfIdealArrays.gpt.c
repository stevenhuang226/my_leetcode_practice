#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define MOD 1000000007
#define MAX_N 10001
#define MAX_V 10001

// 組合數 C(n, k)，使用 Pascal 三角形預先計算
int comb[MAX_N][MAX_N];

// 記錄質因數分解表（每個數的質因數及其次方）
int prime[MAX_V];

// 初始化組合數 C(n, k)
void init_comb() {
    for (int i = 0; i < MAX_N; i++) {
        comb[i][0] = comb[i][i] = 1;
        for (int j = 1; j < i; j++) {
            comb[i][j] = (comb[i - 1][j - 1] + comb[i - 1][j]) % MOD;
        }
    }
}

// 線性篩法找出 1 ~ maxValue 的最小質因數（用於質因數分解）
void init_prime() {
    for (int i = 2; i < MAX_V; i++) {
        if (prime[i] == 0) {
            for (int j = i; j < MAX_V; j += i) {
                if (prime[j] == 0) prime[j] = i;
            }
        }
    }
}

// 主函式：計算有幾個合法的 ideal array
int idealArrays(int n, int maxValue) {
    init_comb();
    init_prime();

    long long result = 0;

    // 每個初始數 1 ~ maxValue 試一次
    for (int val = 1; val <= maxValue; val++) {
        int temp = val;
        int exponents[20] = {0}; // 每個質因數的次方數
        int cnt = 0;

        // 分解質因數，記錄每個質因數的次方
        while (temp > 1) {
            int p = prime[temp];
            exponents[cnt] = 1;
            temp /= p;
            while (temp % p == 0) {
                exponents[cnt]++;
                temp /= p;
            }
            cnt++;
        }

        // 計算所有質因數次方分配到 (n-1) 個空格的方式
        long long ways = 1;
        for (int i = 0; i < cnt; i++) {
            ways = (ways * comb[n - 1 + exponents[i]][exponents[i]]) % MOD;
        }

        result = (result + ways) % MOD;
    }

    return (int)result;
}

int main() {
    int n = 184;
    int maxValue = 389;
    printf("%d\n", idealArrays(n, maxValue));
    return 0;
}

