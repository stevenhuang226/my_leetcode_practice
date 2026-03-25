#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

/* have some idea, but not that much
 * select k different from 0~numSize into k_diff
 * value in k_diff x, x can become 2 x-1
 * keep dfs untile k_diff.size == m
 * calculating value according problem
 */

#define MOD 1000000007

int arr[51];
int ans;

int k;
int m;
int numSize;

int *nums;

void dfs(int len) {
	if (len == m) {
		int64_t sum = 1;
		for (int i = 0; i < 51; i++) {
			for (int ii = 0; ii < arr[i]; ii++) {
				sum *= nums[i];
			}
		}
		ans += sum % MOD;
		return;
	}

	// 對每個 i 嘗試拆分
	for (int i = 0; i <= 50; i++) {
		if (arr[i] > 0) {
			arr[i]--;
			arr[i-1] += 2;   // 拆 x -> x-1, x-1
			dfs(len + 1);
			arr[i-1] -= 2;   // 回溯
			arr[i]++;
		}
	}

	// 沒有可以拆分的，補 0
	if (len < m) {
		int add = m - len;
		arr[0] += add;
		dfs(m);
		arr[0] -= add;
	}
}

void combine(int start, int depth)
{
	if (depth == k) {
		dfs(depth);
		return;
	}

	for (int i = start; i < numSize; i++) {
		arr[i] = 1;
		combine(i+1, depth+1);
		arr[i] = 0;
	}

	if (start == numSize) {
		int remain = k - depth;
		arr[0] = remain;
		dfs(k);
		arr[0] = 0;
	}
}


int magicalSum(int m_, int k_, int *num, int numSize_)
{
	m = m_;
	k = k_;
	ans = 0;
	nums = num;
	numSize = numSize_;
	combine(0, numSize);
	return (int)(ans % MOD);
}
// ---------- 測試 ----------
int main(void) {
	int num[] = {63};
	int numSize = 1;
	int m = 2;
	int k = 1;
	printf("%d\n", magicalSum(m, k, num, numSize));
	return 0;
}

