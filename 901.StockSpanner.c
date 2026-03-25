#include "shdstd.h"

#define LEETCODE_MAX_SIZE 100005

typedef struct {
	int id;
	int price;
} Day;

typedef struct {
	Day *stack;
	int top;
	int day_id;
} StockSpanner;

StockSpanner *stockSpannerCreate() {
	StockSpanner *obj = malloc(sizeof(StockSpanner));
	obj->stack = malloc(LEETCODE_MAX_SIZE * sizeof(Day));
	obj->top = -1;
	obj->day_id = 1;
	return obj;
}

int stockSpannerNext(StockSpanner *obj, int curr_price)
{
	Day *stack = obj->stack;
	while (obj->top >= 0 && stack[obj->top].price <= curr_price) {
		--(obj->top);
	}
	int prev_n_day;

	if (obj->top >= 0) {
		prev_n_day = obj->day_id - stack[obj->top].id;
	} else {
		prev_n_day = obj->day_id;
	}

	++(obj->top);
	stack[obj->top].id = (obj->day_id)++;
	stack[obj->top].price = curr_price;

	return prev_n_day;
}

void stockSpannerFree(StockSpanner *obj)
{
	free(obj->stack);
	free(obj);
}
