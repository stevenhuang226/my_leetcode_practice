#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <inttypes.h>

#define MOD 1000000007

uint64_t numTilings(uint64_t n)
{
	uint64_t *dp;
	dp = malloc(1000 * sizeof(uint64_t));
	dp[0] = 1;
	dp[1] = 1;
	dp[2] = 2;
	dp[3] = 5;
	dp[4] = 11;
	/*
	dp[98] = 281662181;
	dp[100] = 190242381;
	dp[198] = 217735243;
	dp[200] = 627399438;
	dp[298] = 179071158;
	dp[300] = 768506587;
	dp[398] = 983139963;
	dp[400] = 517656200;
	dp[498] = 925543699;
	dp[500] = 47028916;
	dp[598] = 70133467;
	dp[600] = 89132445;
	dp[698] = 484623430;
	dp[700] = 515244819;
	dp[798] = 391441774;
	dp[800] = 462397033;
	dp[898] = 236823523;
	dp[900] = 630089845;
	*/

	if (n < 5 && n > -1) {
		return dp[n];
	}

	int ptr = 5;
	/*
	if ( n > 900) ptr = 901;
	else if ( n > 800) ptr = 801;
	else if ( n > 700) ptr = 701;
	else if ( n > 600) ptr = 601;
	else if ( n > 500) ptr = 501;
	else if ( n > 400) ptr = 401;
	else if ( n > 300) ptr = 301;
	else if ( n > 200) ptr = 201;
	else if (n > 100) ptr = 101;
	*/
	while (ptr <= n) {
		dp[ptr] = (dp[ptr-1] * 2 %MOD + dp[ptr-3]) % MOD;
		++ptr;
	}
	uint64_t ret = dp[n];
	free(dp);
	return ret;
}

int main()
{
	uint64_t n = 699;
	uint64_t ans = numTilings(n);
	printf("%" PRIu64 "\n", ans);
	n = 598;
	ans = numTilings(n);
	printf("%" PRIu64 "\n", ans);
	n = 600;
	ans = numTilings(n);
	printf("%" PRIu64 "\n", ans);
	return 0;
}
