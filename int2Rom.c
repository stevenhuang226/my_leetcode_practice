#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <inttypes.h>
void int2Rom(int64_t num);
int8_t* inverter(int8_t num);
int64_t main()
{
	int2Rom(2);
	return EXIT_SUCCESS;
}

void int2Rom(int64_t num)
{
	int8_t **rom_array[4];
	*rom_array[4] = malloc(4 * sizeof(int8_t *));
	printf("malloc OK\n");
	int8_t ptr = 0;
	char rom_level[] = {'I', 'V', 'X', 'L', 'C', 'D', 'M'};
	while (num > 0) {
		*rom_array[ptr] = inverter(num%10);
		printf("asign to array OK\n");
		ptr += 1;
		num/=10;
	}
	printf("while OK\n");
	for (int i = 0; i < ptr; i += 1) {
		for (int ii = 0; ii < 4; ii += 1) {
			printf("%" SCNd8, *rom_array[ptr][ii]);
		}
		ptr -= 1;
	}
}

int8_t* inverter(int8_t num)
{
	static int8_t rt_array[4] = {0x02, 0x00, 0x00, 0x00};
	switch (num)
	{
		case 0x03:
			rt_array[2] = 0x01;
		case 0x02:
			rt_array[1] = 0x01;
		case 0x01:
			rt_array[0] = 0x01;
			break;
		case 0x04:
			rt_array[0] = 0x01;
			rt_array[1] = 0x02;
			break;
		case 0x08:
			rt_array[3] = 0x02;
		case 0x07:
			rt_array[2] = 0x02;
		case 0x06:
			rt_array[1] = 0x02;
			break;
		case 0x09:
			rt_array[0] = 0x01;
			rt_array[1] = 0x03;
			break;
		default:
			rt_array[0] = 0x00;
	}
	return rt_array;
}
