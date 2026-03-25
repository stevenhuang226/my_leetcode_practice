#include "shdstd.h"

struct ListNode {
	int val;
	struct ListNode *next;
};

struct ListNode *reverseList(struct ListNode *head)
{
	if (head == NULL) {
		return NULL;
	}

	if (head->next == NULL) {
		return head;
	}

	struct ListNode *prev = NULL;
	struct ListNode *curr = head;
	struct ListNode *next = curr->next;

	while (next != NULL) {
		next = curr->next;
		curr->next = prev;

		prev = curr;
		curr = next;
	}

	return prev;
}
