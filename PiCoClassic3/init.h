
#include "portdef.h"
#include "iodefine.h"
#include "parameters.h"
#include "mytypedef.h"


extern t_sensor sen_r,sen_l,sen_fr,sen_fl;	//外部宣言のセンサ構造体
extern t_control con_wall;					//外部宣言の制御構造体

void init_all(void);						//全部初期化(全部を呼び出す)
void init_clock(void);						//CPUの動作周波数を設定
void init_io(void);							//IOポート初期化
void init_cmt(void);						//CMT初期化
void init_mtu(void);						//MTU設定
void init_adc(void);						//AD初期化
//void init_sci(void);						//SCI初期化
void init_parameters(void);					//パラメータ初期化
void init_maze(void);						//迷路情報の初期
