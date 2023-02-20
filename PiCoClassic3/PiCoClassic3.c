/***********************************************************************/
/*                                                                     */
/*  FILE        :Main.c or Main.cpp                                    */
/*  DATE        :Tue, Oct 31, 2006                                     */
/*  DESCRIPTION :Main Program                                          */
/*  CPU TYPE    :                                                      */
/*                                                                     */
/*  NOTE:THIS IS A TYPICAL EXAMPLE.                                    */
/*                                                                     */
/***********************************************************************/
//#include "typedefine.h"

#include "iodefine.h"
#include "portdef.h"
#include "macro.h"
#include "mytypedef.h"
#include "parameters.h"
#include "init.h"
#include "glob_var.h"
#include "DataFlash.h"
#include "run.h"

#ifdef __cplusplus
//#include <ios>                        // Remove the comment when you use ios
//_SINT ios_base::Init::init_cnt;       // Remove the comment when you use ios
#endif

void main(void);
#ifdef __cplusplus
extern "C" {
void abort(void);
}
#endif

void exec_by_mode(int mode);

extern void init_all(void);
extern void wait_ms(int wtime);
extern void search_lefthand(void);
extern void search_adachi(int gx, int gy);
extern void goal_appeal(void);
extern void fast_run(int x, int y);
extern void fast_slalom_run(int x, int y, int max_slalom_sp);
extern void adjust_menu(void);
extern void USB_CHECK(void);

void _LED(int led_data)
{
	LED0 = led_data&0x01;
	LED1 = (led_data>>1)&0x01;
	LED2 = (led_data>>2)&0x01;
	LED3 = (led_data>>3)&0x01;
}

void main(void)
{
	int mode;
	
	init_all();				//初期化

	DISABLE_BUZZER;				//ブザーを止める

	mode = 1;

	while(1)				//モード選択スイッチ
	{
		MOT_POWER_OFF;		

		wait_ms(CHATTERING_WAIT*3);			//チャタリング防止の待ち時間
		DISABLE_BUZZER;						//ブザーを止める

		while( !(SW_L & SW_C & SW_R) );		//スイッチが離されるまで待つ

		wait_ms(CHATTERING_WAIT);			//チャタリング防止の待ち時間

		_LED(mode);							//現在のモードを車体前方のＬＥＤに表示する

		while( (SW_L & SW_C & SW_R))		//何れかのスイッチが押されるまで待つ
		{
			USB_CHECK();
		}		
	
	//以降で、どのスイッチが押されたか判断

		if(SW_L == SW_ON)					//左スイッチが押されていたら次のモードに進む
		{
			mode++;
			if(mode > 15)					//モードは15番までなので、それを超えないようにする
			{
				mode = 15;
			}else{
				SET_BUZZER_FREQ(INC_FREQ);	//値が増加した時の周波数を設定				
				ENABLE_BUZZER;				//ブザーを発振させる
			}
		}
		else if(SW_R == SW_ON)				//右スイッチが押されていたら前のモードに戻る
		{
			mode--;
			if(mode < 1)					//モードは1番からなので、それ以下にならないようにする
			{
				mode = 1;
			}else{
				SET_BUZZER_FREQ(DEC_FREQ);	//値が減少した時の周波数を決定
				ENABLE_BUZZER;				//ブザーを発振させる
			}
		}
		else if(SW_C == SW_ON)				//中央スイッチが押されていたら、現在のモードを実行する
		{
			SET_BUZZER_FREQ(DEC_FREQ);		//決定スイッチが押されたときの音を鳴らす
			ENABLE_BUZZER;					//ブザーを発振させる
			wait_ms(80);					//適当な待ち時間
			SET_BUZZER_FREQ(INC_FREQ);		//音(周波数)を変更する
			wait_ms(80);					//適当な待ち時間
			DISABLE_BUZZER;					//ブザーの発振を停止させる
			exec_by_mode(mode);				//現在のモードを実行する

			}
	}
}

void exec_by_mode(int mode)	//モード番号に従って実行する
{

	MOT_POWER_ON;
	wait_ms(1000);
	
	switch(mode)
	{
		case 1:		//左手法
			search_lefthand();
			break;
			
		case 2:		//足立法
			mypos.x = mypos.y = 0;							//座標を初期化
			mypos.dir = north;								//方角を初期化
			search_adachi(GOAL_X,GOAL_Y);					//ゴールまで足立法
			rotate(right,2);								//ゴールしたら180度回転する
			mypos.dir = (t_direction)((mypos.dir+6) % 4);	//方角を更新
			map_write();
			search_adachi(0,0);								//スタート地点まで足立法で帰ってくる
			map_write();
			goal_appeal();
			break;
		
		case 3:		//最短走行
			map_copy();
			mypos.x = mypos.y = 0;							//座標を初期化
			mypos.dir = north;								//方角を初期化
			accel = 1.7;									//加速度を設定
			fast_run(GOAL_X,GOAL_Y);						//ゴールまで最短走行
			mypos.dir = (t_direction)((mypos.dir+6) % 4);	//方角を更新
			rotate(right,2);								//ゴールしたら180度回転
			goal_appeal();									//ゴールしたことをアピール
			fast_run(0,0);									//スタート地点まで最短走行
//			rotate(right,2);								//帰ってきたら180度回転
			break;
			
			//以下モード15以外は空き。自分でいろいろ作ってみてください。
			
		case 4:
			_LED(15);
//			mypos.x = mypos.y = 0;			//座標を初期化
//			mypos.dir = north;				//方角を初期化
			accel = 1.5;					//加速度を設定
//			fast_slalom_run(GOAL_X,GOAL_Y);		//ゴールまで最短走行
//			mypos.dir = (t_direction)((mypos.dir+6) % 4);		//方角を更新
//			rotate(right,2);				//ゴールしたら180度回転
//			goal_appeal();					//ゴールしたことをアピール
//			fast_run(0,0);					//スタート地点まで最短走行
//			rotate(right,2);				//帰ってきたら180度回転
		straight(HALF_SECTION*5,0,800,0);
//		straight(HALF_SECTION*5,SEARCH_SPEED,500,SEARCH_SPEED);
		turn_slalom(right,300);	
		for(int i=0;i<1;i++){
			straight(HALF_SECTION*4,0,800,0);
			turn_slalom(right,300);	
		}
//		straight(HALF_SECTION*5,SEARCH_SPEED,SEARCH_SPEED,SEARCH_SPEED);
//		turn_slalom(right);		
//			map_copy();
//			mypos.x = mypos.y = 0;			//座標を初期化
//			mypos.dir = north;				//方角を初期化
//			_LED(15);
//			rotate(right,1);
//			accel = 1.5;					//加速度を設定
//			straight(HALF_SECTION,SEARCH_SPEED,SEARCH_SPEED,SEARCH_SPEED);
//			turn_slalom(left);		//ゴールまで最短走行
//			straight(HALF_SECTION,SEARCH_SPEED,SEARCH_SPEED,SEARCH_SPEED);
//			mypos.dir = (t_direction)((mypos.dir+6) % 4);		//方角を更新
//			rotate(right,2);				//ゴールしたら180度回転
//			goal_appeal();					//ゴールしたことをアピール
//			fast_run(0,0);					//スタート地点まで最短走行
//			rotate(right,2);				//帰ってきたら180度回転
			break;			break;
			
		case 5:		//スラローム走行
			map_copy();
			mypos.x = mypos.y = 0;			//座標を初期化
			mypos.dir = north;				//方角を初期化
			accel = 1.0;					//加速度を設定

			fast_slalom_run(GOAL_X,GOAL_Y,MAX_SLALOM_SP1);		//ゴールまで最短走行
			rotate(right,2);				//ゴールしたら180度回転

			back(50);						//壁にぶつけて姿勢を整える
			wait_ms(1000);					//少し待機
			straight(30,0,200,0);
			
			back(100);						//壁にぶつけて姿勢を整える
			wait_ms(1000);					//少し待機
			straight(30,0,200,0);
			
			mypos.dir = (t_direction)((mypos.dir+6) % 4);		//方角を更新
//			goal_appeal();					//ゴールしたことをアピール
//			fast_run(0,0);

			break;
			
		case 6:		//スラローム走行
			map_copy();
			mypos.x = mypos.y = 0;			//座標を初期化
			mypos.dir = north;				//方角を初期化
			accel = 1.0;					//加速度を設定

			fast_slalom_run(GOAL_X,GOAL_Y,MAX_SLALOM_SP2);		//ゴールまで最短走行
			rotate(right,2);				//ゴールしたら180度回転

			back(50);						//壁にぶつけて姿勢を整える
//			wait_ms(1000);					//少し待機
			straight(30,0,200,0);
			
			back(100);						//壁にぶつけて姿勢を整える
			wait_ms(1000);					//少し待機
			straight(30,0,200,0);
			
			mypos.dir = (t_direction)((mypos.dir+6) % 4);		//方角を更新
//			goal_appeal();					//ゴールしたことをアピール
//			fast_run(9,1);

			break;
			
		case 7:		//スラローム走行
			map_copy();
			mypos.x = mypos.y = 0;			//座標を初期化
			mypos.dir = north;				//方角を初期化
			accel = 1.0;					//加速度を設定

			fast_slalom_run(GOAL_X,GOAL_Y,MAX_SLALOM_SP3);		//ゴールまで最短走行
			rotate(right,2);				//ゴールしたら180度回転

			back(50);						//壁にぶつけて姿勢を整える
			wait_ms(1000);					//少し待機
			straight(30,0,200,0);
			
			back(100);						//壁にぶつけて姿勢を整える
			wait_ms(1000);					//少し待機
			straight(30,0,200,0);
			
			mypos.dir = (t_direction)((mypos.dir+6) % 4);		//方角を更新
			fast_run(0,0);

//			goal_appeal();					//ゴールしたことをアピール
			break;
			
		case 8:
			_LED(15);
			while(SW_C != SW_ON);
			mem_view(); //壁センサの読み込み
			break;
			
		case 9:
			break;
			
		case 10:
			break;
			
		case 11:
			break;
			
		case 12:
			break;
			
		case 13:
			break;
			
		case 14:
			break;
			
		case 15:
			adjust_menu();	//調整メニューに行く
			break;
					
	}
	
	MOT_POWER_OFF;
}

#ifdef __cplusplus
void abort(void)
{

}
#endif
