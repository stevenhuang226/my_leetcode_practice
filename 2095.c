#include "shdstd.h"
struct ListNode {
	int val;
	struct ListNode *next;
};

struct ListNode *deleteMiddle(struct ListNode *head)
{
	if (head->next == NULL) {
		return NULL;
	}

	struct ListNode *mid = head;
	struct ListNode *front = head;
	struct ListNode *prev = NULL;

	while (front != NULL && front->next != NULL) {
		front = front->next->next;
		prev = mid;
		mid = mid->next;
	}

	prev->next = mid->next;
	free(mid);
	return head;
}
