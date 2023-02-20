
#define IO_OUT	(1)				//PFCのInput/Output レジスタに1を設定すると出力になる
#define IO_IN	(0)				//PFCのInput/Output レジスタに0を設定すると入力になる


#define BATT_MAX	2552		//12.4V
#define BATT_MIN	2034		//10V

#define SW_OFF	(1)				//スイッチがOFFの時に取る値
#define SW_ON	(0)				//スイッチがONの時に取る値

#define CHATTERING_WAIT	(50)	//チャタリング回避用待ち時間

#define INC_FREQ	(2000)		//モードが増加した時に鳴らす音の周波数
#define DEC_FREQ	(1000)		//モードが減少した時に鳴らす音の周波数

#define MOT_FORWARD	(0)			//モータドライバのCWCCW端子にLOWを出力すると前進する
#define MOT_BACK	(1)			//モータドライバのCWCCW端子にHIGHを出力するとバックする

#define MIN_SPEED	(30)		//最低速度.ジェネラルレジスタが16bitであることと、MTUの動作周波数から求められる値がおおよそ18mm/sなので、余裕を持って30mm/s

#define PI (3.141592653589793)	//円周率


#define HALF_SECTION	(90)	//半区画の距離
#define SECTION		(180)		//一区画の距離

#define MAZESIZE_X	(16)		//迷路の大きさ(MAZESIZE_X * MAZESIZE_Y)迷路
#define MAZESIZE_Y	(16)		//迷路の大きさ(MAZESIZE_X * MAZESIZE_Y)迷路

#define UNKNOWN	2				//壁があるかないか判らない状態の場合の値
#define NOWALL	0				//壁がないばあいの値
#define WALL	1				//壁がある場合の値
#define VWALL	3				//仮想壁の値(未使用)

#define MASK_SEARCH	0x01		//探索走行用マスク値.壁情報とこの値のAND値が０（NOWALL）なら壁なしor未探索区間
#define MASK_SECOND	0x03		//最短走行用マスク値.壁情報とこの値のAND値が０（NOWALL）なら壁なし

