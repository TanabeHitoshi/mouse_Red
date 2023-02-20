#ifndef _PARAMETER

#include "static_parameters.h"
//坂下
//物理的なパラメータ
#define TIRE_DIAMETER	(48.0 -0.1)				//タイヤの直径
#define TREAD_WIDTH	(64.0 +6.2)					//トレッド幅
#define TREAD_CIRCUIT	(TREAD_WIDTH*PI/4)	//超信地旋回の時にタイヤが動く距離

//センサ関連パラメータ                                              
#define WAITLOOP_SLED 300					//LEDを光らせてからAD変換を開始するまでの時間稼ぎ用定数
#define REF_SEN_R	468//526//584	 				//マウスを迷路中央に置いた時のセンサの値
#define REF_SEN_L	741//693//604						//マウスを迷路中央に置いた時のセンサの値
                                                                                                                                                                  
#define TH_SEN_R	198//172//160//302//295//153							//壁があるか否かの閾値
#define TH_SEN_L	252//241//262//211//221//153							//壁があるか否かの閾値
#define TH_SEN_FR	171//188//186//250//254//143							//壁があるか否かの閾値
#define TH_SEN_FL	291//301//315//308//343//94	

#define CONTH_SEN_R	TH_SEN_R				//制御をかけるか否かの閾値
#define CONTH_SEN_L	TH_SEN_L				//制御をかけるか否かの閾値

#define CON_WALL_KP	(0.16)					//壁センサによる姿勢制御の比例制御の比例定数
#define con_wall_KD	0.1						//壁センサによる姿勢制御の微分制御の比例定数

//走行パラメータ
#define SEARCH_SPEED	(430)				//探索の速度
#define SEARCH_ACCEL	(1.6)				//探索の加速度

#define TURN_ACCEL	(0.5)					//超信地旋回の加速度
#define	TURN_SPEED	(364)					//超信地旋回の最高速度のリミット

#define SLALOM_DEFF		(0.417 - 0.09)//(0.02)//(0.04)			//スラローム走行の内輪差
#define SLALOM_ACCEL	(0.4)					//スラローム走行の加速度
#define SLALOM_OFFSETL	(15.0)					//スロー
#define SLALOM_ANGLE	(2.0*70.0/4.0)				//スラロームの走行距離
#define SLALOM_MIN_SPEED	(300)				//スラローム走行の初速度
//#define SLALOM_MAX_SPEED	(500)
#define SLALOM_SPEED	(400)//(408)
#define MAX_SLALOM_SP1	(550)					//スラローム走行の走行速度
#define MAX_SLALOM_SP2	(600)					//スラローム走行の走行速度      
#define MAX_SLALOM_SP3	(650)					//スラローム走行の走行速度

//迷路関連パラメータ
#define GOAL_X	7							//ゴール座標(x)
#define GOAL_Y	7							//ゴール座標(y)

#define _PARAMETER

#endif
