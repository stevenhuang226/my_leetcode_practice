#include "shdstd.h"

typedef struct {
	int capacity;

	int loff;
	int roff;

	int dptr;
	char data[];
} String;

static int string_len(String *str)
{
	return str->roff - str->loff + 1;
}

String *string_new(int capacity)
{
	String *str = malloc(sizeof(String) + capacity * sizeof(char));

	str->capacity = capacity;
	str->loff = capacity / 2;
	str->roff = str->loff - 1;
	str->dptr = 1;

	return str;
}

String *string_realloc(String *str)
{
	int capacity = str->capacity;

	int len = string_len(str);

	str = realloc(str, sizeof(String) + capacity * 3 * sizeof(char));

	memmove(str->data + str->loff + capacity,
			str->data + str->loff,
			len);

	str->loff = str->loff + capacity;
	str->roff = str->roff + capacity;
	str->capacity = capacity * 3;

	return str;
}

String *string_append(String *str, char new)
{
	if (str->dptr == 1) {
		if (str->roff+1 >= str->capacity) {
			str = string_realloc(str);
		}

		++str->roff;
		str->data[str->roff] = new;
	} else {
		if (str->loff-1 < 0) {
			str = string_realloc(str);
		}

		--str->loff;
		str->data[str->loff] = new;
	}

	return str;
}

void string_reverse(String *str)
{
	if (str->dptr == 1) {
		str->dptr = -1;
	} else {
		str->dptr = 1;
	}
}

void string_dellast(String *str)
{
	int len = string_len(str);
	if (len <= 0)
		return;

	if (str->dptr == 1) {
		--str->roff;
	} else {
		++str->loff;
	}
}

String *string_duplicate(String *str)
{
	int len = string_len(str);

	if (str->dptr == 1) {
		if (str->roff + len >= str->capacity) {
			str = string_realloc(str);
		}

		memcpy(str->data + str->roff + 1,
				str->data + str->loff,
				len);
		str->roff += len;
	} else {
		if (str->loff - len < 0) {
			str = string_realloc(str);
		}

		memcpy(str->data + str->loff - len,
				str->data + str->loff,
				len);
		str->loff -= len;
	}

	return str;
}

char *string_c2c(String *str)
{
	int len = string_len(str);

	char *res = malloc((len+1) * sizeof(char));

	int w = 0;
	if (str->dptr == 1) {
		for (int i = str->loff; i <= str->roff; ++i) {
			res[w++] = str->data[i];
		}
	} else {
		for (int i = str->roff; i >= str->loff; --i) {
			res[w++] = str->data[i];
		}
	}

	res[w++] = '\0';
	return res;
}

#define DUPLICATE '#'
#define REVERSE '%'
#define REMOVELAST '*'

char *processStr(char *s)
{
	int src_len = strlen(s);

	String *str = string_new(src_len * 4);

	for (int i = 0; i < src_len; ++i) {

		char ch = s[i];
		if (ch == DUPLICATE) {
			str = string_duplicate(str);
		} else if (ch == REVERSE) {
			string_reverse(str);
		} else if (ch == REMOVELAST) {
			string_dellast(str);
		} else {
			str = string_append(str, ch);
		}
	}

	char *res = string_c2c(str);

	free(str);

	return res;
}
