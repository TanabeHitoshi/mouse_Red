//グローバル変数を一箇所で宣言する。
//glob_var.cで実体を作り(_GLOB_VARをdefine)、他のグローバル変数を使用するファイルからはglob_var.hをincludeする。

#include "mytypedef.h"
#include "parameters.h"

//global変数を一括で実体とextern宣言する。
//include元で_GLOB_VARが定義されていれば実体宣言、定義されていなければ外部宣言となる。
#ifdef _GLOB_VAR
#define GLOBAL
#else
#define GLOBAL extern
#endif

GLOBAL t_sensor			sen_r, sen_l, sen_fr, sen_fl;	//センサ構造体
GLOBAL t_control		con_wall;						//制御構造体
GLOBAL unsigned int		step_r, step_l;					//ステップ数(割り込み内でカウントアップ)
GLOBAL float			accel;							//加速度(設定値→符号なし)
GLOBAL float			r_accel;						//加速度(実際の値→符号あり)
GLOBAL float			max_speed,min_speed;			//最高速度(設定値)
GLOBAL float			speed;							//速度(現在の値)
GLOBAL int				slalom_r;						//スラローム走行時の内輪差　右
GLOBAL int				slalom_l;						//スラローム走行時の内輪差　左
GLOBAL t_position		mypos;							//自己座標
GLOBAL t_wall			wall[MAZESIZE_X][MAZESIZE_Y];	//壁の情報を格納する構造体配列
GLOBAL unsigned char	map[MAZESIZE_X][MAZESIZE_Y];	//歩数マップ
GLOBAL unsigned int		timer;							//1mSごとにカウントアップされる変数.
GLOBAL unsigned short	voltage;						//電圧のAD変換値

