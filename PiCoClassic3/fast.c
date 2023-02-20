
#include "portdef.h"
#include "iodefine.h"
#include "parameters.h"
#include "mytypedef.h"
#include "glob_var.h"
#include "run.h"

extern int get_nextdir(int x, int y, int mask, t_direction *dir);

void fast_run(int x, int y)
{
//引数の座標x,yに向かって最短走行する

#define MAX_SP 1800//最短走行のトップスピード
	t_direction glob_nextdir;
	int straight_count=0;

	//現在の向きから、次に行くべき方向へ向く
	switch(get_nextdir(x,y,MASK_SECOND,&glob_nextdir))	//次に行く方向を戻り値とする関数を呼ぶ
	{
		case front:
			straight_count++;							//前向きだった場合は直線を走る距離を伸ばす
			break;
		
		case right:										//右に向く
			rotate(right,1);
			straight_count = 1;
			break;
		
		case left:										//左に向く
			rotate(left,1);
			straight_count = 1;
			break;
		
		case rear:										//後ろに向く
			rotate(left,2);
			straight_count = 1;
			break;
	}

	mypos.dir = glob_nextdir;							//自分の向きを更新


	//向いた方向によって自分の座標を更新する
	switch(mypos.dir)
	{
		case north:
			mypos.y++;	//北を向いた時はY座標を増やす
			break;
			
		case east:
			mypos.x++;	//東を向いた時はX座標を増やす
			break;
			
		case south:
			mypos.y--;	//南を向いた時はY座標を減らす
			break;
		
		case west:
			mypos.x--;	//西を向いたときはX座標を減らす
			break;

	}



	
	while((mypos.x != x) || (mypos.y != y)){				//ゴールするまで繰り返す
		switch(get_nextdir(x,y,MASK_SECOND,&glob_nextdir))	//次に行く方向を戻り値とする関数を呼ぶ
		{
			case front:										//直線をまとめて走るようにする
				straight_count++;
				break;
			
			case right:
				straight(straight_count*SECTION,0,MAX_SP,0);//直線を走る
				rotate(right,1);							//右に曲がる
				straight_count = 1;							//走る直線の距離をリセット
				break;
			
			case left:
				straight(straight_count*SECTION,0,MAX_SP,0);//直線を走る
				rotate(left,1);								//左に曲がる
				straight_count = 1;							//走る直線の距離をリセット
				break;
			
			case rear:
				straight(straight_count*SECTION,0,MAX_SP,0);//直線を走る	
				rotate(left,2);								//後ろに向く
				straight_count = 1;							//走る直線の距離をリセット
				break;
		}
	
		mypos.dir = glob_nextdir;							//自分の向きを修正
		
		//向いた方向によって自分の座標を更新する
		switch(mypos.dir)
		{
			case north:
				mypos.y++;	//北を向いた時はY座標を増やす
				break;
				
			case east:
				mypos.x++;	//東を向いた時はX座標を増やす
				break;
				
			case south:
				mypos.y--;	//南を向いた時はY座標を減らす
				break;
			
			case west:
				mypos.x--;	//西を向いたときはX座標を減らす
				break;

		}
	}
	straight(straight_count*SECTION,0,MAX_SP,0);						//直線を消化する
}

void fast_slalom_run(int x, int y, int max_slalom_sp)
{
//引数の座標x,yに向かって最短走行する

#define MAX_SLALOM_SP 2000//最短走行のトップスピード
	t_direction glob_nextdir;
	int straight_count=0;
	int HALF_straight_count = 0;
	int slalom = 0;
	
	
	//現在の向きから、次に行くべき方向へ向く
	switch(get_nextdir(x,y,MASK_SECOND,&glob_nextdir))	//次に行く方向を戻り値とする関数を呼ぶ
	{
		case front:
			HALF_straight_count +=1;
			break;
		
		case right:										//右に向く
			rotate(right,1);
			HALF_straight_count = 1;
			break;
		
		case left:										//左に向く
			rotate(left,1);
			HALF_straight_count = 1;
			break;
		
		case rear:										//後ろに向く
			rotate(left,2);
			HALF_straight_count = 1;
			break;
	}

	mypos.dir = glob_nextdir;							//自分の向きを更新


	//向いた方向によって自分の座標を更新する
	switch(mypos.dir)
	{
		case north:
			mypos.y++;	//北を向いた時はY座標を増やす
			break;
			
		case east:
			mypos.x++;	//東を向いた時はX座標を増やす
			break;
			
		case south:
			mypos.y--;	//南を向いた時はY座標を減らす
			break;
		
		case west:
			mypos.x--;	//西を向いたときはX座標を減らす
			break;

	}
//	for(int k = 0;k<3;k++){
	while((mypos.x != x) || (mypos.y != y)){				//ゴールするまで繰り返す
		switch(get_nextdir(x,y,MASK_SECOND,&glob_nextdir))	//次に行く方向を戻り値とする関数を呼ぶ
		{
			case front:										//直線をまとめて走るようにする
				HALF_straight_count +=2;
				slalom = 0;
			break;
			
			case right:
				if(slalom < 10){
					straight_slalom(HALF_SECTION*HALF_straight_count+SLALOM_OFFSETL,200,max_slalom_sp,SLALOM_MIN_SPEED);
//					while(1);
					turn_slalom(right,max_slalom_sp);							//右に曲がる
//					while(1);
					HALF_straight_count = 0;
					straight_slalom(HALF_SECTION*HALF_straight_count+SLALOM_OFFSETL,200,max_slalom_sp,SLALOM_MIN_SPEED);
					slalom++;
//					while(1);
//					while(slalom >11);
					
				}else{
					straight((HALF_straight_count+1)*HALF_SECTION,0,max_slalom_sp,0);//直線を走る
//			while(1);
					rotate(right,1);							//右に曲がる
					HALF_straight_count = 1;							//走る直線の距離をリセット
					slalom = 0;
				}
				
				break;
			
			case left:
				if(slalom < 10){
					straight_slalom(HALF_SECTION*HALF_straight_count+SLALOM_OFFSETL,200,max_slalom_sp,SLALOM_MIN_SPEED);
					turn_slalom(left,max_slalom_sp);							//右に曲がる
//					while(1);
					HALF_straight_count = 0;
					straight_slalom(HALF_SECTION*HALF_straight_count+SLALOM_OFFSETL,200,max_slalom_sp,SLALOM_MIN_SPEED);
					slalom++;
//					while(1);
					while(slalom > 11);

				}else{
					straight((HALF_straight_count+1)*HALF_SECTION,0,max_slalom_sp,0);//直線を走る
//			while(1);
					rotate(left,1);							//右に曲がる
					HALF_straight_count = 1;							//走る直線の距離をリセット	
					slalom = 0;
				}
				
				break;
			
			case rear:
				rotate(left,2);								//後ろに向く
				HALF_straight_count = 1;
				break;
		}
	
		mypos.dir = glob_nextdir;							//自分の向きを修正
		
		//向いた方向によって自分の座標を更新する
		switch(mypos.dir)
		{
			case north:
				mypos.y++;	//北を向いた時はY座標を増やす
				break;
				
			case east:
				mypos.x++;	//東を向いた時はX座標を増やす
				break;
				
			case south:
				mypos.y--;	//南を向いた時はY座標を減らす
				break;
			
			case west:
				mypos.x--;	//西を向いたときはX座標を減らす
				break;

		}
	}
//	straight(straight_count*SECTION,0,MAX_SP,0);//直線を消化する
	straight((HALF_straight_count + 1)*HALF_SECTION,0,max_slalom_sp,0);//直線を消化する
}



