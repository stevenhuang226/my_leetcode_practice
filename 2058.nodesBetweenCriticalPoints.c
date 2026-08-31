#include "shdstd.h"

struct ListNode {
	int val;
	struct ListNode *next;
};

#define MAX(x, y) (((x) > (y)) ? (x) : (y))
#define MIN(x, y) (((x) < (y)) ? (x) : (y))
int *nodesBetweenCriticalPoints(struct ListNode *head, int *ret_size)
{
	struct ListNode *curr;
	curr = head;

	int min_dis = INT32_MAX;
	int max_dis = 0;

	int prev = -1;
	int count = 0;
	int prev_critical = 0;
	int first_critical = 0;
	while (curr->next) {
		int next = curr->next->val;

		if ((curr->val > next && curr->val > prev) ||
		(curr->val < next && curr->val < prev)) {
			if (prev_critical) {
				min_dis = MIN(min_dis, count - prev_critical);
				max_dis = MAX(max_dis, count - first_critical);
			}

			if (!first_critical) {
				first_critical = count;
			}

			prev_critical = count;
		}

		prev = curr->val;

		++count;
		curr = curr->next;
	}

	int *res = malloc(2 * sizeof(int));
	res[0] = min_dis == INT32_MAX ? -1 : min_dis;
	res[1] = max_dis == 0 ? -1 : max_dis;
	*ret_size = 2;

	return res;
}
