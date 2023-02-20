#include "iodefine.h"
#include "portdef.h"
#include "parameters.h"
#include "interrupt.h"
#include "static_parameters.h"
#include "macro.h"
#include "glob_var.h"

void int_cmt0(void)
{
	float spd_r, spd_l;				//最終的な速度
		
	speed+=r_accel; 				//加速処理

	if(speed > max_speed)			//最高速度を制限
	{
		speed = max_speed;
	}
	
	if(speed < min_speed){			//最低速度を制限(MTUの周期設定レジスタの値が～0xffffまでであるため)
		speed = min_speed;
	}

		//センサ制御
	if(con_wall.enable == true)		//壁制御が許可されているかチェック
	{
		
		con_wall.p_error = con_wall.error;	//過去の偏差を保存
		
		
		//左右のセンサが、それぞれ使える状態であるかどうかチェックして、姿勢制御の偏差を計算
		if( ( sen_r.is_control == true ) && ( sen_l.is_control == true ) )
		{									//両方とも有効だった場合の偏差を計算
			con_wall.error = sen_r.error - sen_l.error;
		}
		else								//片方もしくは両方のセンサが無効だった場合の偏差を計算
		{
			con_wall.error = 2.0 * (sen_r.error - sen_l.error);	//片方しか使用しないので2倍する
		}
		
		
		//DI制御計算
		con_wall.diff = con_wall.error - con_wall.p_error;	//偏差の微分値を計算
		con_wall.sum += con_wall.error;						//偏差の積分値を計算
		
		if(con_wall.sum > con_wall.sum_max)					//偏差の積分値の最大値を制限
		{
			con_wall.sum = con_wall.sum_max;
		}
		else if(con_wall.sum < (-con_wall.sum_max))			//偏差の積分値の最低値を制限
		{
			con_wall.sum = -con_wall.sum_max;
		}
		
//		con_wall.control = 0.001 * speed * con_wall.kp * con_wall.error;	//制御量を計算
		con_wall.control = 0.001 * speed * con_wall.kp * con_wall.error - 0.001 * speed * con_wall_KD * con_wall.diff;	//制御量を計算
		
		spd_r = speed + con_wall.control;					//制御を左右モータの速度差という形で反映
		spd_l = speed - con_wall.control;					//制御を左右モータの速度差という形で反映

	}else{
		spd_r = speed - slalom_r;
		spd_l = speed - slalom_l;
	}	

	if(spd_r < MIN_SPEED)spd_r = MIN_SPEED;
	if(spd_l < MIN_SPEED)spd_l = MIN_SPEED;	

	MTU3.TGRC = SPEED2GREG(spd_r);	//右速度(mm/s)からジェネラルレジスタの値に変換して、バッファレジスタに代入
	MTU4.TGRC = SPEED2GREG(spd_l);	//左速度(mm/s)からジェネラルレジスタの値に変換して、バッファレジスタに代入

}		

void int_cmt1(void)				//センサ読み込み用り込み
{
	static int state = 0;		//読み込むセンサのローテーション管理用変数
	int i;
	
	switch(state)
	{
		case 0:										//右センサ読み込み

			SLED_R = 1;								//LED点灯
			for(i = 0; i < WAITLOOP_SLED; i++)	;	//フォトトランジスタの応答待ちループ
			S12AD.ADANS0.BIT.ANS0=0x0040;			//AN006
			S12AD.ADCSR.BIT.ADST=1;					//AD変換開始
			while(S12AD.ADCSR.BIT.ADST);			//AD変換終了まで待つ
			SLED_R = 0;								//LED消灯

			sen_r.p_value = sen_r.value;			//過去の値を保存
			sen_r.value = S12AD.ADDR6;				//値を保存

			if(sen_r.value > sen_r.th_wall)			//壁の有無を判断
			{
				sen_r.is_wall = true;				//右壁あり
			}
			else
			{
				sen_r.is_wall = false;				//右壁なし
			}
			
			if(sen_r.value > sen_r.th_control)		//制御をかけるか否かを判断
			{
				sen_r.error = sen_r.value - sen_r.ref;	//制御をかける場合は偏差を計算
				sen_r.is_control = true;			//右センサを制御に使う
			}
			else
			{
				sen_r.error = 0;					//制御に使わない場合は偏差を0にしておく
				sen_r.is_control = false;			//右センサを制御に使わない
			}			
			break;


		case 1:		//前左センサ読み込み

			SLED_FL = 1;							//LED点灯
			for(i = 0; i < WAITLOOP_SLED; i++)	;	//フォトトランジスタの応答待ちループ
			S12AD.ADANS0.BIT.ANS0=0x0010;			//AN004
			S12AD.ADCSR.BIT.ADST=1;					//AD変換開始
			while(S12AD.ADCSR.BIT.ADST);			//AD変換終了まで待つ
			SLED_FL = 0;							//LED消灯

			sen_fl.p_value = sen_fl.value;			//過去の値を保存
			sen_fl.value = S12AD.ADDR4;				//値を保存

			if(sen_fl.value > sen_fl.th_wall)		//壁の有無を判断
			{
				sen_fl.is_wall = true;				//左前壁あり
			}
			else
			{
				sen_fl.is_wall = false;				//左前壁なし
			}
			break;


		case 2:		//前右センサ読み込み
		
			SLED_FR = 1;							//LED点灯
			for(i = 0; i < WAITLOOP_SLED; i++)	;	//フォトトランジスタの応答待ちループ
			S12AD.ADANS0.BIT.ANS0=0x0200;			//AN009
			S12AD.ADCSR.BIT.ADST=1;					//AD変換開始
			while(S12AD.ADCSR.BIT.ADST);			//AD変換終了まで待つ
			SLED_FR = 0;							//LED消灯

			sen_fr.p_value = sen_fr.value;			//過去の値を保存
			sen_fr.value = S12AD.ADDR9;				//値を保存

			if(sen_fr.value > sen_fr.th_wall)		//壁の有無を判断
			{
				sen_fr.is_wall = true;				//右前壁あり
			}
			else
			{
				sen_fr.is_wall = false;				//右前壁なし
			}			
			break;


		case 3:		//左センサ読み込み
		
			SLED_L = 1;					//LED点灯
			for(i = 0; i < WAITLOOP_SLED; i++)	;	//フォトトランジスタの応答待ちループ
			S12AD.ADANS0.BIT.ANS0=0x0004;			//AN002
			S12AD.ADCSR.BIT.ADST=1;					//AD変換開始
			while(S12AD.ADCSR.BIT.ADST);			//AD変換終了まで待つ
			SLED_L = 0;					//LED消灯

			sen_l.p_value = sen_l.value;			//過去の値を保存
			sen_l.value = S12AD.ADDR2;				//値を保存
			
			if(sen_l.value > sen_l.th_wall)			//壁の有無を判断
			{
				sen_l.is_wall = true;				//左壁あり
			}
			else
			{
				sen_l.is_wall = false;				//左壁なし
			}
			
			if(sen_l.value > sen_l.th_control)		//制御をかけるか否かを判断
			{
				sen_l.error = sen_l.value - sen_l.ref;	//制御をかける場合は偏差を計算する
				sen_l.is_control = true;			//左センサを制御に使う
			}
			else
			{
				sen_l.error = 0;					//制御に使わない場合は偏差を0にしておく
				sen_l.is_control = false;			//左センサを制御に使わない
			}

			break;
	}
	
	state++;		//４回ごとに繰り返す
	if(state > 3)
	{
		state = 0;
	}
		
}


void int_cmt2(void)		//1msタイマー用
{
	timer++;							//1mSごとにカウントアップ
	battery_save(getBatteryVolt());		//バッテリ監視
	
}


void int_mot_r(void)		//右モータが１ステップ進む毎の割り込み
{
	step_r++;				//ステップ数をカウント
}



void int_mot_l(void)		//左モータが１ステップ進む毎の割り込み
{
	step_l++;				//ステップ数をカウント
}

unsigned short getBatteryVolt(void)
{
	S12AD.ADANS0.BIT.ANS0=0x0100;		//AN008
	S12AD.ADCSR.BIT.ADST=1;				//AD変換開始
	while(S12AD.ADCSR.BIT.ADST);		//AD変換終了まで待つ
	return S12AD.ADDR8;
}

void battery_save(unsigned short v_value)
{
	static int bled_cnt = 0;	//バッテリ電圧監視用LEDのPWM用変数
	
	//バッテリ電圧表示
	bled_cnt++;


	if(bled_cnt > 10){
		bled_cnt= 0;
	}
	
	if( (10.0 * (v_value - BATT_MIN) / (BATT_MAX - BATT_MIN)) > bled_cnt ){
		BLED0 = 1;
		BLED1 = 0;
	}else{
		BLED0 = 0;
		BLED1 = 1;
	}
	
	if(v_value < BATT_MIN){
		SET_BUZZER_FREQ(400);	//値が増加した時の周波数を設定				
		ENABLE_BUZZER;			//ブザーを発振する
		MOT_POWER_OFF;			//モータを停止する
		LED0 = LED1 = LED2 = LED3 = SLED_L = SLED_FL = SLED_FR = SLED_R = 0;	//LEDを停止する
	}
}

