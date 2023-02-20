#include "iodefine.h"
#include "mytypedef.h"
#include "portdef.h"
#include "parameters.h"
#include "macro.h"
#include "glob_var.h"
#include "DataFlash.h"
#include "run.h"

int exec_by_mode_adjust(int mode);

extern void _LED(int led_data);
extern void wait_ms(int wtime);
extern void USB_PRINTF(char *format, ...);

void view_adc(void)		//ADコンバータの値を見る
{
	unsigned int i;
	unsigned int ref_sen_r_c,ref_sen_l_c,th_sen_r_c,th_sen_l_c,th_sen_fr_c,th_sen_fl_c;
	unsigned int ref_sen_r_n,ref_sen_l_n,th_sen_r_n,th_sen_l_n,th_sen_fr_n,th_sen_fl_n;
	char change_mode=0;
	
	MOT_POWER_OFF;		// ステッピングモータを励磁する
	
	//FlashRomに保存されているデータを呼び出す。
	ref_sen_r_n=ref_sen_r_c= *(unsigned short *)REF_SEN_R_ADD;//マウスを迷路中央に置いた時のセンサの値
	ref_sen_l_n=ref_sen_l_c= *(unsigned short *)REF_SEN_L_ADD;//マウスを迷路中央に置いた時のセンサの値
	th_sen_r_n =th_sen_r_c = *(unsigned short *)TH_SEN_R_ADD;//壁があるか否かの閾値
	th_sen_l_n =th_sen_l_c = *(unsigned short *)TH_SEN_L_ADD;//壁があるか否かの閾値
	th_sen_fr_n=th_sen_fr_c= *(unsigned short *)TH_SEN_FR_ADD;//壁があるか否かの閾値
	th_sen_fl_n=th_sen_fl_c= *(unsigned short *)TH_SEN_FL_ADD;//壁があるか否かの閾値
	
	while(1)
	{
		USB_PRINTF("r_sen  is\t%d\r\n",(sen_r.value));	//右センサの値
		USB_PRINTF("fr_sen is\t%d\r\n",(sen_fr.value));	//右前センサの値
		USB_PRINTF("fl_sen is\t%d\r\n",(sen_fl.value));	//左前センサの値
		USB_PRINTF("l_sen  is\t%d\r\n",(sen_l.value));	//左センサの値
		USB_PRINTF("VDD    is\t%dmV\r\n",((10+51)/10*3300*S12AD.ADDR8/4095));//電圧を表示
		
		USB_PRINTF("\n\r");//改行
		USB_PRINTF("        Current New  \n\r");
		USB_PRINTF("REF_SEN_R= %4d  %4d\n\r",ref_sen_r_c,ref_sen_r_n);
		USB_PRINTF("REF_SEN_L= %4d  %4d\n\r",ref_sen_l_c,ref_sen_l_n);
		USB_PRINTF("TH_SEN_R = %4d  %4d\n\r",th_sen_r_c,th_sen_r_n);
		USB_PRINTF("TH_SEN_L = %4d  %4d\n\r",th_sen_l_c,th_sen_l_n);
		USB_PRINTF("TH_SEN_FR= %4d  %4d\n\r",th_sen_fr_c,th_sen_fr_n);
		USB_PRINTF("TH_SEN_FL= %4d  %4d\n\r",th_sen_fl_c,th_sen_fl_n);

		USB_PRINTF("\n\r");//改行
		switch(change_mode){
			case 0:
				USB_PRINTF("Changing REF_SEN_R value ? Yes:Right button,No:Left button");
				if(!(SW_L & SW_R)){					//スイッチが離されるまで待つ
					wait_ms(CHATTERING_WAIT);		//チャタリング防止の待ち時間
					while( (SW_L & SW_R));			//何れかのスイッチが押されるまで待つ
					if(SW_L == SW_ON)				//左スイッチが押されていたら次のモードに進む
					{
						SET_BUZZER_FREQ(INC_FREQ);	//値が増加した時の周波数を設定				
						ENABLE_BUZZER;				//ブザーを発振させる
						change_mode++;
					}
					if(SW_R == SW_ON)				//右スイッチが押されていたら値を書き換える
					{
						SET_BUZZER_FREQ(DEC_FREQ);	//値が減少した時の周波数を決定
						ENABLE_BUZZER;				//ブザーを発振させる						
						ref_sen_r_n=sen_r.value;
						change_mode++;
					}
				}
				break;
			case 1:
				USB_PRINTF("Changing REF_SEN_L value ? Yes:Right button,No:Left button");
				if(!(SW_L & SW_R)){					//スイッチが離されるまで待つ
					wait_ms(CHATTERING_WAIT);		//チャタリング防止の待ち時間
					while( (SW_L & SW_R));			//何れかのスイッチが押されるまで待つ
					if(SW_L == SW_ON)				//左スイッチが押されていたら次のモードに進む
					{
						SET_BUZZER_FREQ(INC_FREQ);	//値が増加した時の周波数を設定				
						ENABLE_BUZZER;				//ブザーを発振させる
						change_mode++;
					}
					if(SW_R == SW_ON)				//右スイッチが押されていたら値を書き換える
					{
						SET_BUZZER_FREQ(DEC_FREQ);	//値が減少した時の周波数を決定
						ENABLE_BUZZER;				//ブザーを発振させる						
						ref_sen_l_n=sen_l.value;
						change_mode++;
					}
				}
				break;				
			case 2:
				USB_PRINTF("Changing TH_SEN_R value ? Yes:Right button,No:Left button");
				if(!(SW_L & SW_R)){					//スイッチが離されるまで待つ
					wait_ms(CHATTERING_WAIT);		//チャタリング防止の待ち時間
					while( (SW_L & SW_R));			//何れかのスイッチが押されるまで待つ
					if(SW_L == SW_ON)				//左スイッチが押されていたら次のモードに進む
					{
						SET_BUZZER_FREQ(INC_FREQ);	//値が増加した時の周波数を設定				
						ENABLE_BUZZER;				//ブザーを発振させる
						change_mode++;
					}
					if(SW_R == SW_ON)				//右スイッチが押されていたら値を書き換える
					{
						SET_BUZZER_FREQ(DEC_FREQ);	//値が減少した時の周波数を決定
						ENABLE_BUZZER;				//ブザーを発振させる						
						th_sen_r_n=sen_r.value;
						change_mode++;
					}
				}
				break;
			case 3:
				USB_PRINTF("Changing TH_SEN_L value ? Yes:Right button,No:Left button");
				if(!(SW_L & SW_R)){					//スイッチが離されるまで待つ
					wait_ms(CHATTERING_WAIT);		//チャタリング防止の待ち時間
					while( (SW_L & SW_R));			//何れかのスイッチが押されるまで待つ
					if(SW_L == SW_ON)				//左スイッチが押されていたら次のモードに進む
					{
						SET_BUZZER_FREQ(INC_FREQ);	//値が増加した時の周波数を設定				
						ENABLE_BUZZER;				//ブザーを発振させる
						change_mode++;
					}
					if(SW_R == SW_ON)				//右スイッチが押されていたら値を書き換える
					{
						SET_BUZZER_FREQ(DEC_FREQ);	//値が減少した時の周波数を決定
						ENABLE_BUZZER;				//ブザーを発振させる						
						th_sen_l_n=sen_l.value;
						change_mode++;
					}
				}
				break;	
			case 4:
				USB_PRINTF("Changing TH_SEN_FR value ? Yes:Right button,No:Left button");
				if(!(SW_L & SW_R)){					//スイッチが離されるまで待つ
					wait_ms(CHATTERING_WAIT);		//チャタリング防止の待ち時間
					while( (SW_L & SW_R));			//何れかのスイッチが押されるまで待つ
					if(SW_L == SW_ON)				//左スイッチが押されていたら次のモードに進む
					{
						SET_BUZZER_FREQ(INC_FREQ);	//値が増加した時の周波数を設定				
						ENABLE_BUZZER;				//ブザーを発振させる
						change_mode++;
					}
					if(SW_R == SW_ON)				//右スイッチが押されていたら値を書き換える
					{
						SET_BUZZER_FREQ(DEC_FREQ);	//値が減少した時の周波数を決定
						ENABLE_BUZZER;				//ブザーを発振させる						
						th_sen_fr_n=sen_fr.value;
						change_mode++;
					}
				}
				break;
			case 5:
				USB_PRINTF("Changing TH_SEN_FL value ? Yes:Right button,No:Left button");
				if(!(SW_L & SW_R)){					//スイッチが離されるまで待つ
					wait_ms(CHATTERING_WAIT);		//チャタリング防止の待ち時間
					while( (SW_L & SW_R));			//何れかのスイッチが押されるまで待つ
					if(SW_L == SW_ON)				//左スイッチが押されていたら次のモードに進む
					{
						SET_BUZZER_FREQ(INC_FREQ);	//値が増加した時の周波数を設定				
						ENABLE_BUZZER;				//ブザーを発振させる
						change_mode++;
					}
					if(SW_R == SW_ON)				//右スイッチが押されていたら値を書き換える
					{
						SET_BUZZER_FREQ(DEC_FREQ);	//値が減少した時の周波数を決定
						ENABLE_BUZZER;				//ブザーを発振させる						
						th_sen_fl_n=sen_fl.value;
						change_mode++;
					}
				}
				break;
			case 6:
				USB_PRINTF("Changing value write? Yes:Right button,No:Left button");
				if(!(SW_L & SW_R)){					//スイッチが離されるまで待つ
					wait_ms(CHATTERING_WAIT);		//チャタリング防止の待ち時間
					while( (SW_L & SW_R));			//何れかのスイッチが押されるまで待つ
					if(SW_L == SW_ON)				//左スイッチが押されていたら次のモードに進む
					{
						SET_BUZZER_FREQ(INC_FREQ);	//値が増加した時の周波数を設定				
						ENABLE_BUZZER;				//ブザーを発振させる
						change_mode=0;
					}
					if(SW_R == SW_ON)				//右スイッチが押されていたら値を書き換える
					{
						SET_BUZZER_FREQ(DEC_FREQ);	//値が減少した時の周波数を決定
						ENABLE_BUZZER;				//ブザーを発振させる	
						
						ref_sen_r_c=ref_sen_r_n;	//マウスを迷路中央に置いた時のセンサの値
						ref_sen_l_c=ref_sen_l_n;	//マウスを迷路中央に置いた時のセンサの値
						th_sen_r_c =th_sen_r_n;		//壁があるか否かの閾値
						th_sen_l_c =th_sen_l_n;		//壁があるか否かの閾値
						th_sen_fr_c=th_sen_fr_n;	//壁があるか否かの閾値
						th_sen_fl_c=th_sen_fl_n;	//壁があるか否かの閾値
						
						erase((unsigned short *)REF_SEN_R_ADD);
						write_eeflash((unsigned short *)REF_SEN_R_ADD,ref_sen_r_n );
						write_eeflash((unsigned short *)REF_SEN_L_ADD,ref_sen_l_n );
						write_eeflash((unsigned short *)TH_SEN_R_ADD,th_sen_r_n );
						write_eeflash((unsigned short *)TH_SEN_L_ADD,th_sen_l_n );
						write_eeflash((unsigned short *)TH_SEN_FR_ADD,th_sen_fr_n );
						write_eeflash((unsigned short *)TH_SEN_FL_ADD,th_sen_fl_n );
		
						change_mode=0;
					}
				}
				break;				
				
				
		}
		wait_ms(CHATTERING_WAIT*3);		//チャタリング防止の待ち時間
		DISABLE_BUZZER;					//ブザーを止める
		
		for(i = 0; i < 0xfffff; i++);	//表示間隔を設定
		
		//画面クリアシーケンス
		USB_PRINTF("\x1b[2J");			//クリアスクリーン[CLS]
		USB_PRINTF("\x1b[0;0H");		//カーソルを0,0に移動
	}
}


void straight_check(int section_check)	//タイヤ直径チェック用
{
	max_speed = SEARCH_SPEED;			//探索の速度を指定
	accel = SEARCH_ACCEL;				//加速度を指定

	wait_ms(1000);
	straight(SECTION * section_check,0,SEARCH_SPEED,0);//section_check区画進む
	
}


void go_and_turn_right(void)			//タイヤトレッド径チェック用
{
	int i;
	max_speed = SEARCH_SPEED;			//探索の速度を指定
	accel = SEARCH_ACCEL;			//加速度を指定

	wait_ms(1000);					//1秒待つ
	
/*
	for(i=0;i<8;i++){
		rotate(right,1);				//その場で90度右ターン
	}
*/	
	while(1){
		straight_check(2);			//2区画進む
		rotate(right,2);				//その場で180度右ターン
		straight_check(2);			//2区画進む	
		rotate(right,2);				//その場で180度右ターン
	}

}


void adjust_menu(void)	//調整用メニュー
{
	int mode = 1;		//メニュー用変数
	

	while(1)			//モード選択
	{

		wait_ms(CHATTERING_WAIT*3);							//チャタリング防止の待ち時間
		DISABLE_BUZZER;
		while( !(SW_L & SW_C & SW_R) ) ;
		wait_ms(CHATTERING_WAIT);							//チャタリング防止の待ち時間

		_LED(mode);											//現在のモードを車体前方のＬＥＤに表示する
		
		while( SW_L & SW_C & SW_R )							//何れかのスイッチが押されるまで待つ
		{
			wait_ms(33);
			LED3 ^= 1;										//反転(チカチカさせる)
			
		}
		LED3 = 0;
		//以降で、どのスイッチが押されたか判断

		if(SW_L == SW_ON)									//左スイッチが押されていたら次のモードに進む
		{
			mode++;
			if(mode > 7)									//モードは15番までなので、それを超えないようにする
			{
				mode = 7;
			}else{
				SET_BUZZER_FREQ(INC_FREQ);				
				ENABLE_BUZZER;
			}
		}
		else if(SW_R == SW_ON)								//右スイッチが押されていたら前のモードに戻る
		{
			mode--;
			if(mode < 1)									//モードは1番からなので、それ以下にならないようにする
			{
				mode = 1;
			}else{
				SET_BUZZER_FREQ(DEC_FREQ);					//ブザーの周波数を決定
				ENABLE_BUZZER;								//ブザーを発振させる
			}
		}
		else if(SW_C == SW_ON)								//中央スイッチが押されていたら、現在のモードを実行する
		{
			SET_BUZZER_FREQ(DEC_FREQ);						//決定スイッチが押されたときの音を鳴らす
			ENABLE_BUZZER;									//ブザーを発振させる
			wait_ms(CHATTERING_WAIT*8);
			SET_BUZZER_FREQ(INC_FREQ);						//音(周波数)を変更する
			wait_ms(CHATTERING_WAIT*8);
			DISABLE_BUZZER;									//ブザーの発振を停止させる
			if(exec_by_mode_adjust(mode) == 1)
			{
				return;										//現在のモードを実行する

			}
		}
	}
}

void mem_view(void){
	int i;
	USB_PRINTF("\n\r\n\r\n\r LOG \n\r");
	for(i=0; i < 100; i++){
		USB_PRINTF("%4d %3d%3d sen_fl=%4d sen_l=%4d sen_r=%4d sen_fr=%4d\n\r",i,x_axis[i],y_axis[i],wall_value[3][i],wall_value[2][i],wall_value[1][i],wall_value[0][i]);
	}
}

void map_view(void){
	signed char i,j;
	
	USB_PRINTF("\x1b[0;0H");								//カーソルを0,0に移動
	USB_PRINTF("\n\r+");
	for(i = 0 ; i < MAZESIZE_X; i++){
		switch(wall[i][MAZESIZE_Y-1].north){				//黒色は"[30m"
			case NOWALL:	USB_PRINTF("\x1b[37m  +");		//NOWALL
				break;
			case WALL:	USB_PRINTF("\x1b[37m--+");			//WALL
				break;
			case UNKNOWN:	USB_PRINTF("\x1b[31m--+");		//UNNOWN
				break;
			default:	USB_PRINTF("\x1b[33m--+");			//VWALL
				break;
		}
	}

	USB_PRINTF("\n\r");
	for(j=(MAZESIZE_Y-1);j>-1;j--){
		switch(wall[0][j].west){
			case NOWALL:	USB_PRINTF("\x1b[37m ");		//NOWALL
				break;
			case WALL:	USB_PRINTF("\x1b[37m|");			//WALL
				break;
			case UNKNOWN:	USB_PRINTF("\x1b[31m|");		//UNNOWN
				break;
			default:	USB_PRINTF("\x1b[33m|");			//VWALL
				break;
		}	
		for(i=0;i<MAZESIZE_X; i++){
			switch(wall[i][j].east){
				case NOWALL:	USB_PRINTF("\x1b[37m   ");	//NOWALL
					break;
				case WALL:	USB_PRINTF("\x1b[37m  |");		//WALL
					break;
				case UNKNOWN:	USB_PRINTF("\x1b[31m  |");	//UNNOWN
					break;
				default:	USB_PRINTF("\x1b[33m  |");		//VWALL
					break;
			}
		}
		USB_PRINTF("\n\r+");
		for(i=0;i<MAZESIZE_X; i++){
			switch(wall[i][j].south){
				case NOWALL:	USB_PRINTF("\x1b[37m  +");	//NOWALL
					break;
				case WALL:	USB_PRINTF("\x1b[37m--+");		//WALL
					break;
				case UNKNOWN:	USB_PRINTF("\x1b[31m--+");	//UNNOWN
					break;
				default:	USB_PRINTF("\x1b[33m--+");		//VWALL
					break;
			}
		}
		USB_PRINTF("\n\r");
	}
	return;

}




int exec_by_mode_adjust(int mode)
{
//引数modeを受取り、そのモードに入る。
//戻り値が1の場合は、大本のメニューに戻る

	switch(mode)
	{
		case 1:
			view_adc();				//A/D変換の結果をUSBに出力する
			break;
			
		case 2:
			straight_check(4);  	//9区画直線を走る
			break;
		
		case 3:
			go_and_turn_right();
			break;
			
		case 4:
			map_copy();
			map_view();
			break;
			
		case 5:
			break;
			
		case 6:
			break;
			
		case 7:
			return 1;				//モード７は元のメニューに戻る
			break;
	}
	
	return 0;
}
