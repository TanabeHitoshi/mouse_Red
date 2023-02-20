
#include "run.h"
#include "glob_var.h"

int wall_value[4][100];
int x_axis[100];
int y_axis[100];
int iMem;

extern void wait_ms(int wtime);

void straight(int len, float init_speed, float max_sp, float tar_speed)			//直線走行
{
	int obj_step;						//目標ステップ数

	max_speed = max_sp;
	r_accel = accel;					//加速度

	if(init_speed < MIN_SPEED){
		speed = MIN_SPEED;
	}else{
		speed=init_speed;
	}
	
	//目標速度が最低速度を下回らないようにする
	if(tar_speed < MIN_SPEED)
	{
		tar_speed = MIN_SPEED;
	}
	if(init_speed < tar_speed){
		min_speed = MIN_SPEED;
	}else{
		min_speed = tar_speed;
	}
	
	step_r = step_l = 0;						//ステップ数カウントのリセット
	
	con_wall.enable = true;						//壁制御を有効にする

	obj_step = LEN2STEP(len);					//目標ステップ数を算出

	MOT_CWCCW_R = MOT_CWCCW_L = MOT_FORWARD;	//前方に進む

	MTU.TSTR.BIT.CST3 = MTU.TSTR.BIT.CST4 = 1;	//カウントスタート
		
	//減速を開始し始めるところまで待つ(あと走るべき距離が減速するべき距離より短くなったら・・・)
	while( (len - STEP2LEN(step_r + step_l) ) > ( ( (tar_speed*tar_speed) - (speed*speed) ) / (-2*1000*accel) ));

	r_accel = -accel;						//減速する
	
	while((step_r + step_l) < obj_step)	;	//目標地点まで走行
	
	MTU.TSTR.BIT.CST3 = 0;					//モータのカウントをストップ
	MTU.TSTR.BIT.CST4 = 0;					//モータのカウントをストップ
	
}

void straight_slalom(int len, float init_speed, float max_sp, float tar_speed)			//直線走行
{
	int obj_step;						//目標ステップ数

	max_speed = max_sp;
	r_accel = accel;					//加速度

	if(init_speed < MIN_SPEED){
		speed = MIN_SPEED;
	}else{
		speed=init_speed;
	}
	
	//目標速度が最低速度を下回らないようにする
	if(tar_speed < MIN_SPEED)
	{
		tar_speed = MIN_SPEED;
	}
	if(init_speed < tar_speed){
		min_speed = MIN_SPEED;
	}else{
		min_speed = tar_speed;
	}
	
	step_r = step_l = 0;						//ステップ数カウントのリセット
	
	con_wall.enable = true;						//壁制御を有効にする

	obj_step = LEN2STEP(len);					//目標ステップ数を算出

	MOT_CWCCW_R = MOT_CWCCW_L = MOT_FORWARD;	//前方に進む

	MTU.TSTR.BIT.CST3 = MTU.TSTR.BIT.CST4 = 1;	//カウントスタート
		
	//減速を開始し始めるところまで待つ(あと走るべき距離が減速するべき距離より短くなったら・・・)
	while( (len - STEP2LEN(step_r + step_l) ) > ( ( (tar_speed*tar_speed) - (speed*speed) ) / (-2*1000*accel) ));

	r_accel = -accel;						//減速する
	
	while((step_r + step_l) < obj_step)	;	//目標地点まで走行
	
//	MTU.TSTR.BIT.CST3 = 0;					//モータのカウントをストップ
//	MTU.TSTR.BIT.CST4 = 0;					//モータのカウントをストップ
	
}


void straight_for_search(int len, float max_sp,float tar_speed)	//直線走行、探索用にリセットは外部に任せる
{
	//走行距離len[mm] と 目標速度tar_speed[mm/s] を指定する。
	//最高速度は変数max_speedに予め代入すること
	
	int obj_step;					//目標ステップ数

	max_speed  = max_sp;	
	r_accel = accel;				//加速度
	
	//目標速度が最低速度を下回らないようにする
	if(tar_speed < MIN_SPEED)
	{
		tar_speed = MIN_SPEED;
	}

	if(speed < tar_speed){
		min_speed = MIN_SPEED;
	}else{
		min_speed = tar_speed;
	}	

	con_wall.enable = true;						//壁制御を有効にする
	
	obj_step = LEN2STEP(len);					//目標ステップ数を算出

	MOT_CWCCW_R = MOT_CWCCW_L = MOT_FORWARD;	//前方に進む

	MTU.TSTR.BIT.CST3 = MTU.TSTR.BIT.CST4 = 1;	//カウントスタート
	
	
	//減速を開始し始めるところまで待つ(あと走るべき距離が減速するべき距離より短くなったら・・・)
	while( (len - STEP2LEN(step_r + step_l) ) > ( ( (tar_speed*tar_speed) - (speed*speed) ) / (-2*1000*accel) ));

	r_accel = -accel -0.2;						//減速する
	
	while((step_r + step_l) < obj_step)	;	//目標地点まで走行
	
	MTU.TSTR.BIT.CST3 = 0;					//モータのカウントをストップ
	MTU.TSTR.BIT.CST4 = 0;					//モータのカウントをストップ
	
}

void back(int len)	//直線走行
{
	int obj_step;									//目標ステップ数
			
	r_accel = accel;								//加速度
	
	speed = 100;
		
	step_r = step_l = 0;							//ステップ数カウントのリセット
	
	con_wall.enable = false;							//壁制御を有効にする

	obj_step = LEN2STEP(len);						//目標ステップ数を算出

	MOT_CWCCW_R = MOT_CWCCW_L = MOT_BACK;			//後方に進む

	MTU.TSTR.BIT.CST3 = MTU.TSTR.BIT.CST4 = 1;		//カウントスタート
	
	while((step_r + step_l) < obj_step)	;			//目標地点まで走行
	
	MTU.TSTR.BIT.CST3 = 0;							//モータのカウントをストップ
	MTU.TSTR.BIT.CST4 = 0;							//モータのカウントをストップ
	
}

void rotate(t_local_dir dir, int times){		//超信地旋回
//引数dir[right or left]方向に、90度×times度回転する

	int obj_step;					//目標ステップ
	int tar_speed = MIN_SPEED;		//目標速度(固定)
	
	con_wall.enable = false;		//超信地旋回中は制御を切る
	
	switch(dir)						//右まわりか左まわりかで、モータのCWCCWを切り替える
	{
		case front:
		case rear:
			return;					//超信地旋回なので、前や後ろは無い.

		case right:					//右に回るように設定
			MOT_CWCCW_R = MOT_BACK;
			MOT_CWCCW_L = MOT_FORWARD;
			break;

		case left:					//左に回るように設定
			MOT_CWCCW_R = MOT_FORWARD;
			MOT_CWCCW_L = MOT_BACK;
			break;
	}


	//最低速度を設定
	if(tar_speed < MIN_SPEED)
	{
		tar_speed = MIN_SPEED;
	}

	r_accel = TURN_ACCEL;				//回転の加速度を決定
	max_speed = TURN_SPEED;
	min_speed = MIN_SPEED;	
	speed = MIN_SPEED;					//速度をリセット
	step_r = step_l = 0;				//ステップ数をリセット
	
	obj_step = LEN2STEP(times*TREAD_CIRCUIT);	//目標ステップ数算出

	wait_ms(250);					//いきなり回ると姿勢が乱れるので、少し待機

	MTU.TSTR.BIT.CST3 = MTU.TSTR.BIT.CST4 = 1;	//カウントスタート
	
	//減速開始すべき位置に達するまで待つ
	while( ((times*TREAD_CIRCUIT) - STEP2LEN(step_r + step_l) ) > ( ( (tar_speed*tar_speed) - (speed*speed) ) / (-2*1000*TURN_ACCEL) ));

	r_accel = -TURN_ACCEL;	//減速開始
	
	//停止する位置に達するまで待つ
	while((step_r + step_l) < obj_step)	;
	
	
	//モータ停止
	MTU.TSTR.BIT.CST3 = 0;					//モータのカウントをストップ
	MTU.TSTR.BIT.CST4 = 0;					//モータのカウントをストップ


	//ターン後少し待つ
	wait_ms(250);
	
}

//マイクロマウス研修(hara)
void turn_slalom(t_local_dir dir, float SL_speed)
{
	if (dir == front || dir == rear) return;

	int turn_sp_diff;
	int obj_step;							//目標ステップ
	r_accel=0;
	con_wall.enable = false;				//スラローム旋回中は制御を切る
	obj_step = LEN2STEP(PI*SLALOM_ANGLE);			//目標ステップ数算出
//	obj_step = LEN2STEP(SLALOM_ANGLE);			//目標ステップ数算出

	r_accel = SLALOM_ACCEL;							//回転の加速度を決定
//	max_speed = SLALOM_SPEED;
	max_speed = SL_speed;
	min_speed = MIN_SPEED;
	speed = SLALOM_MIN_SPEED;
	
	step_r = step_l = 0;								//ステップ数をリセット
	MOT_CWCCW_R = MOT_CWCCW_L = MOT_FORWARD;
	MTU.TSTR.BIT.CST3 = MTU.TSTR.BIT.CST4 = 1;		//カウントスタート

	while((step_r + step_l) < obj_step){
	turn_sp_diff = speed -  speed *  SLALOM_DEFF;     //0.417
//	turn_sp_diff = speed * SLALOM_DEFF; 	//0.417 
	switch(dir){
	    case right:
	      slalom_r = turn_sp_diff;
	      break;
	    case left:
	      slalom_l = turn_sp_diff;
	      break;
	}
	}  

	MTU.TSTR.BIT.CST3 = MTU.TSTR.BIT.CST4 = 0;

	con_wall.enable = true;
	slalom_r = slalom_l = 0;
	
	return;
}