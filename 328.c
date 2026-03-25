#include "shdstd.h"

struct ListNode {
	int val;
	struct ListNode *next;
};

struct ListNode *oddEvenList(struct ListNode *head)
{
	if (head == NULL || head->next == NULL) {
		return head;
	}

	struct ListNode *even_head = head->next;
	struct ListNode *even = even_head;

	struct ListNode *odd = head;

	while (odd->next->next != NULL && even->next->next != NULL) {
		odd->next = odd->next->next;
		even->next = even->next->next;

		odd = odd->next;
		even = even->next;
	}

	if (odd->next->next != NULL) {
		odd->next = odd->next->next;
		odd = odd->next;
	}

	even->next = NULL;

	odd->next = even_head;

	return head;
}
