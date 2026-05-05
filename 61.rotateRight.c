#include "shdstd.h"

struct ListNode {
	int val;
	struct ListNode *next;
};

struct ListNode *rotateRight(struct ListNode *head, int neg_off)
{
	if (head==NULL) {
		return NULL;
	}

	struct ListNode *next = head;
	struct ListNode *prev = NULL;

	int size = 0;
	while (next != NULL) {
		prev = next;
		next = next->next;
		++size;
	}

	prev->next = head;

	int off = size - (neg_off % size);

	prev = NULL;
	next = head;
	for (int i = 0; i < off; ++i) {
		prev = next;
		next = next->next;
	}

	prev->next = NULL;
	return next;
}
