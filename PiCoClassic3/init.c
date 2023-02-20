
#include "init.h"
#include "glob_var.h"
#include "DataFlash.h"

extern void init_usb(void);
extern void wait_ms(int wtime); 

void init_clock(void)
{

	SYSTEM.PRCR.WORD = 0xa50b;		//クロックソース選択の保護の解除

	SYSTEM.PLLWTCR.BYTE = 0x0F;		/* 4194304cycle(Default) */
	SYSTEM.PLLCR.WORD = 0x0F00;		/* PLL 逓倍×16 入力1分周 (12.000MHz * 16 = 192MHz)*/
	SYSTEM.PLLCR2.BYTE = 0x00;		/* PLL ENABLE */
	
	
	
	// ICK   : 192/2 = 96MHz 		// システムクロック CPU DMAC DTC ROM RAM
	// PCLKA : 192/2 = 96MHz 		// 周辺モジュールクロックA ETHERC、EDMAC、DEU
	// PCLKB : 192/4 = 48MHz 		// 周辺モジュールクロックB 上記以外 PCLKB=PCLK
/*	
	SYSTEM.SCKCR.BIT.FCK=0x02;		//FCLK MAX 50MHz  192/4
	SYSTEM.SCKCR.BIT.ICK=0x01;		//ICLK MAX 100MHz 192/2
	SYSTEM.SCKCR.BIT.PSTOP1=0x01;	//BCLK 出力停止
	SYSTEM.SCKCR.BIT.PSTOP0=0x01;	//SDCLK 出力停止
	SYSTEM.SCKCR.BIT.BCK=0x02;		//BCLK MAX 100MHz ICLK以下にする必要がある192/4
	SYSTEM.SCKCR.BIT.PCKA=0x01;		//PCLKA MAX 100MHz 192/2
	SYSTEM.SCKCR.BIT.PCKB=0x02;		//PCLKB MAX 50MHz 192/4
	//上記の設定では正しくclock設定ができないため下記のように一括で設定すること
*/
	SYSTEM.SCKCR.LONG = 0x21C21211;	//FCK1/4 ICK1/2 BCLK停止 SDCLK停止 BCK1/4 PCLKA1/2 PCLKB1/4
/*
	SYSTEM.SCKCR2.BIT.UCK=0x03;		//UCLK MAX 48MHz 192/4
	SYSTEM.SCKCR2.BIT.IEBCK=0x02;	//IECLK MAX 50MHz 192/4
*/
	SYSTEM.SCKCR2.WORD = 0x0032;	/* UCLK1/4 IEBCK1/4 */
	SYSTEM.BCKCR.BYTE = 0x01;		/* BCLK = 1/2 */
	
	SYSTEM.SCKCR3.WORD = 0x0400;	//PLL回路選択

}

void init_io(void)
{
	//LED
	PORTB.PDR.BIT.B0 = IO_OUT;//LED0
	PORTA.PDR.BIT.B6 = IO_OUT;//LED1
	PORTA.PDR.BIT.B4 = IO_OUT;//LED2
	PORTA.PDR.BIT.B0 = IO_OUT;//LED3
	PORTB.PDR.BIT.B1 = IO_OUT;//BLED0
	PORTA.PDR.BIT.B3 = IO_OUT;//BLED1
	//Sensor
	PORT5.PDR.BIT.B4 = IO_OUT;//SLED_L
	PORT0.PDR.BIT.B5 = IO_OUT;//SLED_R
	PORT2.PDR.BIT.B7 = IO_OUT;//SLED_FL
	PORTB.PDR.BIT.B5 = IO_OUT;//SLED_FR
	//MOT_POWER
	PORT1.PDR.BIT.B5 = IO_OUT;//motor Enable
	//MOT_CWCCW
	PORTC.PDR.BIT.B5 = IO_OUT;//Rmotor
	PORTC.PDR.BIT.B6 = IO_OUT;//Lmotor

	//Buzzerのポートの初期化
	PORTB.PDR.BIT.B3 = IO_OUT;
	BUZZER = 1;
	
	MPC.PWPR.BIT.B0WI=0;
	MPC.PWPR.BIT.PFSWE=1;
	MPC.PB3PFS.BIT.PSEL=1;	//MTIOC0A
	MPC.P17PFS.BIT.PSEL=1;	//MTIOC3Aとして使用
	MPC.PE2PFS.BIT.PSEL=1;	//MTIOC4A

	MPC.PE0PFS.BIT.ASEL=1;	//A/D 電源
	MPC.PE1PFS.BIT.ASEL=1;	//A/D SEN_FR
	MPC.P44PFS.BIT.ASEL=1;	//A/D SEN_FL
	MPC.P46PFS.BIT.ASEL=1;	//A/D SEN_R
	MPC.P42PFS.BIT.ASEL=1;	//A/D SEN_L
	MPC.PWPR.BYTE=0x80;
	
	PORTB.PMR.BIT.B3=1;		//SP PWM
	PORT1.PMR.BIT.B7=1;		//右PWM
	PORTE.PMR.BIT.B2=1;		//左PWM
	
	PORTE.PMR.BIT.B0=1;		//A/D
	PORTE.PMR.BIT.B1=1;		//A/D
	PORT4.PMR.BIT.B4=1;		//A/D
	PORT4.PMR.BIT.B6=1;		//A/D
	PORT4.PMR.BIT.B2=1;		//A/D
}

void init_cmt(void)
{
	SYSTEM.PRCR.WORD = 0xA502;
	MSTP(CMT0) = 0;
	MSTP(CMT1) = 0;
	MSTP(CMT2) = 0;
    SYSTEM.PRCR.WORD = 0xA500;	
	
	//CMT0は制御割り込み用タイマとして使用
	CMT0.CMCR.BIT.CKS=1;	// PCLK/32 1.5MHz
	CMT0.CMCR.BIT.CMIE=1;	//割り込みを許可
	CMT0.CMCNT=0;			//カウンターのクリア
	CMT0.CMCOR=1500-1;		//1kHz

	IEN(CMT0,CMI0) = 1;		//割り込み要求を許可 
	IPR(CMT0,CMI0) = 15;	//割り込み優先度 15が最高
	IR(CMT0,CMI0)=0;		//割り込みステータフラグをクリア
	
	//CMT1はセンサー制御用タイマとして使用
	CMT1.CMCR.BIT.CKS=1;	// PCLK/32 1.5MHz
	CMT1.CMCR.BIT.CMIE=1;	//割り込みを許可
	CMT1.CMCNT=0;			//カウンターのクリア
	CMT1.CMCOR=(1500/4)-1;	//4kHz

	IEN(CMT1,CMI1) = 1;		//割り込み要求を許可 
	IPR(CMT1,CMI1) = 14;	//割り込み優先度を次点に設定
	IR(CMT1,CMI1)=0;		//割り込みステータフラグをクリア

	//CMT2は1msのタイマーカウンタ用タイマとして使用
	CMT2.CMCR.BIT.CKS=1;	// PCLK/32 1.5MHz
	CMT2.CMCR.BIT.CMIE=1;	//割り込みを許可
	CMT2.CMCNT=0;			//カウンターのクリア
	CMT2.CMCOR=1500-1;		//1kHz

	IEN(CMT2,CMI2) = 1;		//割り込み要求を許可 
	IPR(CMT2,CMI2) = 10;	//割り込み優先度 15が最高
	IR(CMT2,CMI2)=0;		//割り込みステータフラグをクリア

	CMT.CMSTR0.BIT.STR0=1;	//カウントスタート
	CMT.CMSTR0.BIT.STR1=1;	//カウントスタート
	CMT.CMSTR1.BIT.STR2=1;	//カウントスタート
	
}


void init_mtu(void)
{
	SYSTEM.PRCR.WORD = 0xA502;
	MSTP(MTU) = 0;			//MTUモジュールON
    SYSTEM.PRCR.WORD = 0xA500;	
	
	MTU.TSTR.BYTE=0;		//タイマ動作ストップ
	
	//スピーカー用MTU
	MTU0.TCR.BIT.CCLR=2;	//PWM TGRBのコンペアマッチでTCNTクリア 
	MTU0.TCR.BIT.TPSC=1;	//PCLK/4 12MHz
	MTU0.TMDR.BIT.MD=2;		//PWM1
	MTU0.TIORH.BIT.IOA=5;	//コンベアマッチてlow初期はhigh
	MTU0.TIORH.BIT.IOB=2;	//コンベアマッチでhigh
	MTU0.TGRA = 6000;		//1kHz
	MTU0.TGRB = (12000-1);
		
	//右モータ用MTU設定
	MTU3.TCR.BIT.TPSC=2;	//PCLK/16 3MHz
	MTU3.TCR.BIT.CCLR=1;	//PWM TGRAのコンペアマッチでTCNTクリア
	MTU3.TIORH.BIT.IOA=1;	//初期出力0ンペアマッチ0出力
	MTU3.TIORH.BIT.IOB=2;	//初期出力0コンペアマッチ1出力
	MTU3.TGRA = 12000;
	MTU3.TGRB = 50;
	MTU3.TGRC = 48000;
	MTU3.TMDR.BIT.MD=2;		//PWM1
	MTU3.TMDR.BIT.BFA = 1;	//バッファーモードに設定
	MTU3.TIER.BIT.TGIEB = 1;//GRBコンペアマッチでの割り込み許可
	IEN(MTU3,TGIB3) = 1;	//割り込み要求を許可 
	IPR(MTU3,TGIB3) = 13;	//割り込み優先度を次点に設定
	IR(MTU3,TGIB3)=0;		//割り込みステータフラグをクリア
	
	
	//左モータ用MTU設定
	MTU.TOER.BIT.OE4A=1;	//MTU出力端子を出力許可する
	MTU4.TCR.BIT.TPSC=2;	//PCLK/16 3MHz

	MTU4.TCR.BIT.CCLR=1;	//PWM TGRAのコンペアマッチでTCNTクリア
	MTU4.TIORH.BIT.IOA=1;	//初期出力0ンペアマッチ0出力
	MTU4.TIORH.BIT.IOB=2;	//初期出力0コンペアマッチ1出力
	MTU4.TGRA = 12000;
	MTU4.TGRB = 50;
	MTU4.TGRC = 48000;
	MTU4.TMDR.BIT.MD=2;		//PWM1
	MTU4.TMDR.BIT.BFA = 1;	//バッファーモードに設定
	MTU4.TIER.BIT.TGIEB = 1;//GRBコンペアマッチでの割り込み許可
	IEN(MTU4,TGIB4) = 1;	//割り込み要求を許可 
	IPR(MTU4,TGIB4) = 12;	//割り込み優先度を次点に設定
	IR(MTU4,TGIB4)=0;		//割り込みステータフラグをクリア


	MTU.TSTR.BIT.CST0 = 0;	//タイマストップ
	MTU.TSTR.BIT.CST3 = 0;	//タイマストップ
	MTU.TSTR.BIT.CST4 = 0;	//タイマストップ
}

void init_adc(void)
{
	SYSTEM.PRCR.WORD = 0xA502;
	MSTP(S12AD) = 0;
    SYSTEM.PRCR.WORD = 0xA500;	
	
	S12AD.ADCER.BIT.ADRFMT=0;//右づめ
	S12AD.ADCSR.BIT.CKS=0x03;//PCLKの分周なし
//	S12AD.ADSSTR01.BIT.SST1=20;//Default 20ステート 0.417us 0.4us以上が推奨
}
void init_sci(void){
	SYSTEM.PRCR.WORD = 0xA502;
    MSTP(SCI1) = 0;
	SYSTEM.PRCR.WORD = 0xA500;

	SCI1.SCR.BYTE = 0x00;
	while (0x00 != (SCI1.SCR.BYTE & 0xF0));//割り込み要求が禁止されるまで待つ
	PORT2.PODR.BIT.B6 = 1;			//TXDのDirctionの切り替え後の値をhigh
   	PORT2.PDR.BIT.B6 = 1;			//出力に設定
   	PORT3.PDR.BIT.B0 = 0;			//入力に設定
	PORT2.PMR.BIT.B6 = 0;			//汎用ポートに設定
   	PORT3.PMR.BIT.B0 = 0;			//汎用ポートに設定
   	MPC.PWPR.BIT.B0WI  = 0;
   	MPC.PWPR.BIT.PFSWE = 1;
   	MPC.P26PFS.BIT.PSEL = 0x0A;		//TXD1
   	MPC.P30PFS.BIT.PSEL = 0x0A;		//RXD1
   	MPC.PWPR.BIT.PFSWE = 0;
   	MPC.PWPR.BIT.B0WI  = 1;
   	PORT3.PMR.BIT.B0 = 1;			//周辺機能(RXD1)として使用
    SCI1.SCR.BIT.CKE = 0;
   	SCI1.SMR.BYTE = 0x00;			//1stopbit parityなし　8bit 調歩同期
	SCI1.SCMR.BYTE = 0xF2;			//S=32clock
   	SCI1.SEMR.BYTE = 0x00;
   	SCI1.BRR =38; 					//@48MHz 38400bps
   	SCI1.SCR.BYTE =0x30;			//送信割り込み禁止
	PORT2.PMR.BIT.B6 = 1;			//周辺機能(TXD1)として使用
	SCI1.SCR.BIT.TE = 1;
	SCI1.SCR.BIT.RE = 1;
}	

void init_parameters(void)
{
	if(blank_check((unsigned short *)REF_SEN_R_ADD)==0){//ブランク状態
  		write_eeflash((unsigned short *)REF_SEN_R_ADD,REF_SEN_R );
  		write_eeflash((unsigned short *)REF_SEN_L_ADD,REF_SEN_L );
  		write_eeflash((unsigned short *)TH_SEN_R_ADD,TH_SEN_R );
  		write_eeflash((unsigned short *)TH_SEN_L_ADD,TH_SEN_L );
  		write_eeflash((unsigned short *)TH_SEN_FR_ADD,TH_SEN_FR );
  		write_eeflash((unsigned short *)TH_SEN_FL_ADD,TH_SEN_FL );
	}else if( PORTC.PIDR.BIT.B2 == 0){							//強制的にdefineに指示した値に戻したいとき
  		erase((unsigned short *)REF_SEN_R_ADD);
  		write_eeflash((unsigned short *)REF_SEN_R_ADD,REF_SEN_R );
  		write_eeflash((unsigned short *)REF_SEN_L_ADD,REF_SEN_L );
  		write_eeflash((unsigned short *)TH_SEN_R_ADD,TH_SEN_R );
  		write_eeflash((unsigned short *)TH_SEN_L_ADD,TH_SEN_L );
  		write_eeflash((unsigned short *)TH_SEN_FR_ADD,TH_SEN_FR );
  		write_eeflash((unsigned short *)TH_SEN_FL_ADD,TH_SEN_FL );
	 }
	
	sen_r.ref = *(unsigned short *)REF_SEN_R_ADD;		//右センサのリファレンス値を初期化
	sen_l.ref = *(unsigned short *)REF_SEN_L_ADD;		//左センサのリファレンス値を初期化
	
	sen_r.th_wall = *(unsigned short *)TH_SEN_R_ADD;	//右センサの壁有無判断の閾値を初期化
	sen_l.th_wall = *(unsigned short *)TH_SEN_L_ADD;	//左センサの壁有無判断の閾値を初期化
	
	sen_fr.th_wall = *(unsigned short *)TH_SEN_FR_ADD;	//右前センサの壁有無判断の閾値を初期化
	sen_fl.th_wall = *(unsigned short *)TH_SEN_FL_ADD;	//左前センサの壁有無判断の閾値を初期化

	sen_r.th_control = CONTH_SEN_R;						//右センサの壁制御かけるか否かの閾値を初期化
	sen_l.th_control = CONTH_SEN_L;						//左センサの壁制御かけるか否かの閾値を初期化
	
	con_wall.kp = CON_WALL_KP;							//壁比例制御の比例定数を初期化
}


void init_maze(void)	//迷路情報の初期化
{
	int i,j;
	
	for(i = 0; i < MAZESIZE_X; i++)
	{
		for(j = 0; j < MAZESIZE_Y; j++)
		{
			wall[i][j].north = wall[i][j].east = wall[i][j].south = wall[i][j].west = UNKNOWN;	//迷路の全体がわからない事を設定する
		}
	}
	
	for(i = 0; i < MAZESIZE_X; i++)
	{
		wall[i][0].south = WALL;			//四方の壁を追加する(南)
		wall[i][MAZESIZE_Y-1].north = WALL;	//四方の壁を追加する(北)
	}
	
	for(j = 0; j < MAZESIZE_Y; j++)
	{
		wall[0][j].west = WALL;				//四方の壁を追加する(西)
		wall[MAZESIZE_X-1][j].east = WALL;	//四方の壁を追加する(東)
	}
	
	wall[0][0].east = wall[1][0].west = WALL;	//スタート地点の右の壁を追加する
	
}

void init_all(void)
{
	init_clock();		//CPUの動作周波数を設定
	init_io();			//I/O(Input / Output)ポートを設定
	init_cmt();			//CMT(Compare Match Timer)を設定(センサ割り込み、時間待ち用。)
	init_mtu();			//MTU(Multi Function Timer Pulse Unit)
	init_adc();			//ADC(Analog Digital Converter)初期化
//	init_sci();			//SCI(Serial Communication Interface)初期化
	hw_dflash_init();
	init_parameters();	//パラメータの初期化
	init_maze();		//迷路情報の初期化

	SET_BUZZER_FREQ(INC_FREQ);	//値が増加した時の周波数を設定				
	ENABLE_BUZZER;		//ブザーを発振させる
	wait_ms(80);		//適当な待ち時間
	DISABLE_BUZZER;		//ブザーの発振を停止させる	

	init_usb();
}
