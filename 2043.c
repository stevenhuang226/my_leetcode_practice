#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <stdbool.h>
#include <inttypes.h>

typedef struct {
	int64_t *balance;
	int size;
} Bank;


Bank *bankCreate(long long *balance, int balanceSize)
{
	Bank *obj = malloc(sizeof(Bank));
	obj->balance = malloc(balanceSize * sizeof(int64_t));
	obj->size = balanceSize;

	int i;
	for (i = 0; i < obj->size; ++i) {
		obj->balance[i] = balance[i];
	}

	return obj;
}

bool bankTransfer(Bank *obj, int src_acc, int dest_acc, int64_t money)
{
	--src_acc;
	--dest_acc;
	if (src_acc > obj->size || dest_acc > obj->size || obj->balance[src_acc] < money) {
		return false;
	}
	obj->balance[src_acc] -= money;

	obj->balance[dest_acc] += money;

	return true;
}

bool bankDeposit(Bank *obj, int dest_acc, int64_t money)
{
	--dest_acc;
	if (dest_acc > obj->size) {
		return false;
	}

	obj->balance[dest_acc] += money;

	return true;
}

bool bankWithdraw(Bank *obj, int src_acc, int64_t money)
{
	--src_acc;
	if (src_acc > obj->size || obj->balance[src_acc] < money) {
		return false;
	}

	obj->balance[src_acc] -= money;

	return true;
}

void bankFree(Bank *obj)
{
	free(obj->balance);
	free(obj);
}

/**
 * Your Bank struct will be instantiated and called as such:
 * Bank* obj = bankCreate(balance, balanceSize);
 * bool param_1 = bankTransfer(obj, account1, account2, money);
 
 * bool param_2 = bankDeposit(obj, account, money);
 
 * bool param_3 = bankWithdraw(obj, account, money);
 
 * bankFree(obj);
*/
