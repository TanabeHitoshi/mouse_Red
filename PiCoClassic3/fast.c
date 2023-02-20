
#include "portdef.h"
#include "iodefine.h"
#include "parameters.h"
#include "mytypedef.h"
#include "glob_var.h"
#include "run.h"

extern int get_nextdir(int x, int y, int mask, t_direction *dir);

void fast_run(int x, int y)
{
//�����̍��Wx,y�Ɍ������čŒZ���s����

#define MAX_SP 1800//�ŒZ���s�̃g�b�v�X�s�[�h
	t_direction glob_nextdir;
	int straight_count=0;

	//���݂̌�������A���ɍs���ׂ������֌���
	switch(get_nextdir(x,y,MASK_SECOND,&glob_nextdir))	//���ɍs��������߂�l�Ƃ���֐����Ă�
	{
		case front:
			straight_count++;							//�O�����������ꍇ�͒����𑖂鋗����L�΂�
			break;
		
		case right:										//�E�Ɍ���
			rotate(right,1);
			straight_count = 1;
			break;
		
		case left:										//���Ɍ���
			rotate(left,1);
			straight_count = 1;
			break;
		
		case rear:										//���Ɍ���
			rotate(left,2);
			straight_count = 1;
			break;
	}

	mypos.dir = glob_nextdir;							//�����̌������X�V


	//�����������ɂ���Ď����̍��W���X�V����
	switch(mypos.dir)
	{
		case north:
			mypos.y++;	//�k������������Y���W�𑝂₷
			break;
			
		case east:
			mypos.x++;	//��������������X���W�𑝂₷
			break;
			
		case south:
			mypos.y--;	//�������������Y���W�����炷
			break;
		
		case west:
			mypos.x--;	//�����������Ƃ���X���W�����炷
			break;

	}



	
	while((mypos.x != x) || (mypos.y != y)){				//�S�[������܂ŌJ��Ԃ�
		switch(get_nextdir(x,y,MASK_SECOND,&glob_nextdir))	//���ɍs��������߂�l�Ƃ���֐����Ă�
		{
			case front:										//�������܂Ƃ߂đ���悤�ɂ���
				straight_count++;
				break;
			
			case right:
				straight(straight_count*SECTION,0,MAX_SP,0);//�����𑖂�
				rotate(right,1);							//�E�ɋȂ���
				straight_count = 1;							//���钼���̋��������Z�b�g
				break;
			
			case left:
				straight(straight_count*SECTION,0,MAX_SP,0);//�����𑖂�
				rotate(left,1);								//���ɋȂ���
				straight_count = 1;							//���钼���̋��������Z�b�g
				break;
			
			case rear:
				straight(straight_count*SECTION,0,MAX_SP,0);//�����𑖂�	
				rotate(left,2);								//���Ɍ���
				straight_count = 1;							//���钼���̋��������Z�b�g
				break;
		}
	
		mypos.dir = glob_nextdir;							//�����̌������C��
		
		//�����������ɂ���Ď����̍��W���X�V����
		switch(mypos.dir)
		{
			case north:
				mypos.y++;	//�k������������Y���W�𑝂₷
				break;
				
			case east:
				mypos.x++;	//��������������X���W�𑝂₷
				break;
				
			case south:
				mypos.y--;	//�������������Y���W�����炷
				break;
			
			case west:
				mypos.x--;	//�����������Ƃ���X���W�����炷
				break;

		}
	}
	straight(straight_count*SECTION,0,MAX_SP,0);						//��������������
}

void fast_slalom_run(int x, int y, int max_slalom_sp)
{
//�����̍��Wx,y�Ɍ������čŒZ���s����

#define MAX_SLALOM_SP 2000//�ŒZ���s�̃g�b�v�X�s�[�h
	t_direction glob_nextdir;
	int straight_count=0;
	int HALF_straight_count = 0;
	int slalom = 0;
	
	
	//���݂̌�������A���ɍs���ׂ������֌���
	switch(get_nextdir(x,y,MASK_SECOND,&glob_nextdir))	//���ɍs��������߂�l�Ƃ���֐����Ă�
	{
		case front:
			HALF_straight_count +=1;
			break;
		
		case right:										//�E�Ɍ���
			rotate(right,1);
			HALF_straight_count = 1;
			break;
		
		case left:										//���Ɍ���
			rotate(left,1);
			HALF_straight_count = 1;
			break;
		
		case rear:										//���Ɍ���
			rotate(left,2);
			HALF_straight_count = 1;
			break;
	}

	mypos.dir = glob_nextdir;							//�����̌������X�V


	//�����������ɂ���Ď����̍��W���X�V����
	switch(mypos.dir)
	{
		case north:
			mypos.y++;	//�k������������Y���W�𑝂₷
			break;
			
		case east:
			mypos.x++;	//��������������X���W�𑝂₷
			break;
			
		case south:
			mypos.y--;	//�������������Y���W�����炷
			break;
		
		case west:
			mypos.x--;	//�����������Ƃ���X���W�����炷
			break;

	}
//	for(int k = 0;k<3;k++){
	while((mypos.x != x) || (mypos.y != y)){				//�S�[������܂ŌJ��Ԃ�
		switch(get_nextdir(x,y,MASK_SECOND,&glob_nextdir))	//���ɍs��������߂�l�Ƃ���֐����Ă�
		{
			case front:										//�������܂Ƃ߂đ���悤�ɂ���
				HALF_straight_count +=2;
				slalom = 0;
			break;
			
			case right:
				if(slalom < 10){
					straight_slalom(HALF_SECTION*HALF_straight_count+SLALOM_OFFSETL,200,max_slalom_sp,SLALOM_MIN_SPEED);
//					while(1);
					turn_slalom(right,max_slalom_sp);							//�E�ɋȂ���
//					while(1);
					HALF_straight_count = 0;
					straight_slalom(HALF_SECTION*HALF_straight_count+SLALOM_OFFSETL,200,max_slalom_sp,SLALOM_MIN_SPEED);
					slalom++;
//					while(1);
//					while(slalom >11);
					
				}else{
					straight((HALF_straight_count+1)*HALF_SECTION,0,max_slalom_sp,0);//�����𑖂�
//			while(1);
					rotate(right,1);							//�E�ɋȂ���
					HALF_straight_count = 1;							//���钼���̋��������Z�b�g
					slalom = 0;
				}
				
				break;
			
			case left:
				if(slalom < 10){
					straight_slalom(HALF_SECTION*HALF_straight_count+SLALOM_OFFSETL,200,max_slalom_sp,SLALOM_MIN_SPEED);
					turn_slalom(left,max_slalom_sp);							//�E�ɋȂ���
//					while(1);
					HALF_straight_count = 0;
					straight_slalom(HALF_SECTION*HALF_straight_count+SLALOM_OFFSETL,200,max_slalom_sp,SLALOM_MIN_SPEED);
					slalom++;
//					while(1);
					while(slalom > 11);

				}else{
					straight((HALF_straight_count+1)*HALF_SECTION,0,max_slalom_sp,0);//�����𑖂�
//			while(1);
					rotate(left,1);							//�E�ɋȂ���
					HALF_straight_count = 1;							//���钼���̋��������Z�b�g	
					slalom = 0;
				}
				
				break;
			
			case rear:
				rotate(left,2);								//���Ɍ���
				HALF_straight_count = 1;
				break;
		}
	
		mypos.dir = glob_nextdir;							//�����̌������C��
		
		//�����������ɂ���Ď����̍��W���X�V����
		switch(mypos.dir)
		{
			case north:
				mypos.y++;	//�k������������Y���W�𑝂₷
				break;
				
			case east:
				mypos.x++;	//��������������X���W�𑝂₷
				break;
				
			case south:
				mypos.y--;	//�������������Y���W�����炷
				break;
			
			case west:
				mypos.x--;	//�����������Ƃ���X���W�����炷
				break;

		}
	}
//	straight(straight_count*SECTION,0,MAX_SP,0);//��������������
	straight((HALF_straight_count + 1)*HALF_SECTION,0,max_slalom_sp,0);//��������������
}



