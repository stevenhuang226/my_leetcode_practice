#include "shdstd.h"

char **fullJustify(char **words, int words_size, int max_width, int *ret_size)
{
	int *lines_words = malloc(words_size * sizeof(int));
	int line_count = 0;

	for (int i = 0; i < words_size; ) {
		int word_count = 0;
		int slot_count = 0;

		int len;

		while (i < words_size && slot_count + (len = strlen(words[i])) <= max_width) {
			slot_count += len + 1;
			++word_count;
			++i;
		}

		lines_words[line_count++] = word_count;
	}

	char **ret = malloc(line_count * sizeof(char *));
	char *ret_flat = malloc(line_count * (max_width + 1) * sizeof(char));
	for (int i = 0; i < line_count; ++i) {
		ret[i] = ret_flat + i * (max_width + 1);
	}

	int words_ptr = 0;
	for (int i = 0; i < line_count - 1; ++i) {
		memset(ret[i], ' ', max_width * sizeof(char));
		int word_count = lines_words[i];

		if (word_count == 1) {
			memcpy(ret[i], words[words_ptr], strlen(words[words_ptr]));
			++words_ptr;
			ret[i][max_width] = '\0';
			continue;
		}

		int text_count = 0;
		int tmp = word_count;
		while (tmp--) {
			text_count += strlen(words[words_ptr + tmp]);
		}

		int gap_count = word_count - 1;
		int spaces = max_width - text_count;

		int gap_size = spaces / gap_count;
		int add_before = spaces % gap_count;

		int gap_ptr = 0;
		int offset = 0;
		while (offset < max_width) {
			int word_len = strlen(words[words_ptr]);

			memcpy(ret[i] + offset, words[words_ptr], word_len);
			++words_ptr;

			offset += word_len + gap_size + (gap_ptr < add_before);
			++gap_ptr;
		}
		ret[i][max_width] = '\0';
	}

	memset(ret[line_count - 1], ' ', max_width * sizeof(char));
	int offset = 0;
	for (; words_ptr < words_size; ++words_ptr) {
		int word_len = strlen(words[words_ptr]);

		memcpy(ret[line_count - 1] + offset, words[words_ptr], word_len);
		offset += word_len + 1;
	}
	ret[line_count-1][max_width] = '\0';

	(*ret_size) = line_count;

	free(lines_words);
	return ret;
}

int main()
{
	char *words[7];
	words[0] = "This";
	words[1] = "is";
	words[2] = "an";
	words[3] = "example";
	words[4] = "of";
	words[5] = "text";
	words[6] = "justification.";

	int max_width = 16;
	int size = 7;

	int ret_size;

	char **res = fullJustify(words, size, max_width, &ret_size);
	for (int i = 0; i < ret_size; ++i) {
		printf("%s\n", res[i]);
	}
	free(res);


	return 0;
}
