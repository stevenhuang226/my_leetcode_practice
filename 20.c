#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <stdbool.h>
#include <inttypes.h>

bool isValid(char *s);
int main()
{
	char *s = "()";
	isValid(s);

	return 0;
}

bool isValid(char *s)
{
	int len = strlen(s);
	if (len % 2 != 0) {
		return false;
	}
	int half = len / 2;
	char stk[half+1];
	int top = -1;

	for (int i = 0; i < len && top < half; i++) {
		if (s[i] == '(' || s[i] == '[' || s[i] == '{') {
			stk[++top] = s[i];
		}
		else if (top <= -1) {
			return false;
		}
		else if (s[i] - stk[top] < 3 && s[i] = stk[top] > 0) {
			top--;
		}
		else {
			return false;
		}
	}
	if (top != -1) {
		return false;
	}
	
	return true;
}
