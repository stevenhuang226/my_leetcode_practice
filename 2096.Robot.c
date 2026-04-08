#include "shdstd.h"

typedef struct {
	int8_t dir_x;
	int8_t dir_y;

	int width;
	int height;

	int curr_x;
	int curr_y;

	int steps;
} Robot;

Robot *robotCreate(int width, int height)
{
	Robot *robot = malloc(sizeof(Robot));

	robot->width = width;
	robot->height = height;

	robot->curr_x = robot->curr_y = 0;
	robot->dir_x = 1;
	robot->dir_y = 0;

	robot->steps = 0;

	return robot;
}

void robotStep(Robot *robot, int num)
{
	robot->steps += num;
}

void robotMoveStep(Robot *robot, int step)
{
	int new_pos_x = robot->curr_x + robot->dir_x * step;
	int new_pos_y = robot->curr_y + robot->dir_y * step;

	if (new_pos_x < robot->width && new_pos_x >= 0 &&
		new_pos_y < robot->height && new_pos_y >= 0) {
		robot->curr_x = new_pos_x;
		robot->curr_y = new_pos_y;
		return;
	}

	int new_dir_x = -(robot->dir_y);
	int new_dir_y = robot->dir_x;
	robot->dir_x = new_dir_x;
	robot->dir_y = new_dir_y;

	int new_step;
	if (new_pos_x >= robot->width) {
		robot->curr_x = robot->width - 1;
		new_step = new_pos_x - robot->width + 1;
	} else if (new_pos_x < 0) {
		robot->curr_x = 0;
		new_step = - new_pos_x;
	} else if (new_pos_y >= robot->height) {
		robot->curr_y = robot->height - 1;
		new_step = new_pos_y - robot->height + 1;
	} else if (new_pos_y < 0) {
		robot->curr_y = 0;
		new_step = - new_pos_y;
	}

	robotMoveStep(robot, new_step);
}

void robotMove(Robot *robot)
{
	int four_side = (robot->width + robot->height - 2) * 2;

	int step = (robot->steps - 1) % four_side + 1;

	robotMoveStep(robot, step);
	robot->steps = 0;
}

int *robotGetPos(Robot *robot, int *ret_size)
{
	if (robot->steps) {
		robotMove(robot);
	}

	int *pos = malloc(2 * sizeof(int));
	pos[0] = robot->curr_x;
	pos[1] = robot->curr_y;
	*ret_size = 2;
	return pos;
}

char *robotGetDir(Robot *robot)
{
	if (robot->steps) {
		robotMove(robot);
	}

	if (robot->dir_x == 1) {
		return "East";
	} else if (robot->dir_x == -1) {
		return "West";
	} else if (robot->dir_y == 1) {
		return "North";
	} else if (robot->dir_y == -1) {
		return "South";
	} else {
		return "ERR";
	}
}

void robotFree(Robot *robot)
{
	free(robot);
}
