
#include "iodefine.h"
#include "parameters.h"
#include "macro.h"
#include "mytypedef.h"

extern int wall_value[4][100];
extern int x_axis[100];
extern int y_axis[100];
extern int iMem;

void straight(int len, float init_speed, float max_sp, float tar_speed);
void straight_slalom(int len, float init_speed, float max_sp, float tar_speed);
void straight_for_search(int len, float max_sp,float tar_speed);
void back(int len);
void rotate(t_local_dir dir, int times);
void turn_slalom(t_local_dir dir, float SL_speed);