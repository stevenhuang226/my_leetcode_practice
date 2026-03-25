#include "shdstd.h"

struct ListNode {
	int val;
	struct ListNode *next;
};

#define MAX(x, y) (((x) > (y)) ? (x) : (y))
#define MAX_SIZE 100004

int pairSum(struct ListNode *head)
{
	int *val_arr = malloc(MAX_SIZE * sizeof(int));
	int ptr = 0;

	struct ListNode *curr = head;

	while (curr != NULL) {
		val_arr[ptr++] = curr->val;
		curr = curr->next;
	}


	int max = INT_MIN;

	int half = ptr / 2;
	for (int i = 0; i < half; ++i) {
		int sum = val_arr[i] + val_arr[ptr - i - 1];
		max = MAX(max, sum);
	}
	free(val_arr);
	return max;
}
