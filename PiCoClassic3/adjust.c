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

void view_adc(void)		//AD�R���o�[�^�̒l������
{
	unsigned int i;
	unsigned int ref_sen_r_c,ref_sen_l_c,th_sen_r_c,th_sen_l_c,th_sen_fr_c,th_sen_fl_c;
	unsigned int ref_sen_r_n,ref_sen_l_n,th_sen_r_n,th_sen_l_n,th_sen_fr_n,th_sen_fl_n;
	char change_mode=0;
	
	MOT_POWER_OFF;		// �X�e�b�s���O���[�^��㎥����
	
	//FlashRom�ɕۑ�����Ă���f�[�^���Ăяo���B
	ref_sen_r_n=ref_sen_r_c= *(unsigned short *)REF_SEN_R_ADD;//�}�E�X����H�����ɒu�������̃Z���T�̒l
	ref_sen_l_n=ref_sen_l_c= *(unsigned short *)REF_SEN_L_ADD;//�}�E�X����H�����ɒu�������̃Z���T�̒l
	th_sen_r_n =th_sen_r_c = *(unsigned short *)TH_SEN_R_ADD;//�ǂ����邩�ۂ���臒l
	th_sen_l_n =th_sen_l_c = *(unsigned short *)TH_SEN_L_ADD;//�ǂ����邩�ۂ���臒l
	th_sen_fr_n=th_sen_fr_c= *(unsigned short *)TH_SEN_FR_ADD;//�ǂ����邩�ۂ���臒l
	th_sen_fl_n=th_sen_fl_c= *(unsigned short *)TH_SEN_FL_ADD;//�ǂ����邩�ۂ���臒l
	
	while(1)
	{
		USB_PRINTF("r_sen  is\t%d\r\n",(sen_r.value));	//�E�Z���T�̒l
		USB_PRINTF("fr_sen is\t%d\r\n",(sen_fr.value));	//�E�O�Z���T�̒l
		USB_PRINTF("fl_sen is\t%d\r\n",(sen_fl.value));	//���O�Z���T�̒l
		USB_PRINTF("l_sen  is\t%d\r\n",(sen_l.value));	//���Z���T�̒l
		USB_PRINTF("VDD    is\t%dmV\r\n",((10+51)/10*3300*S12AD.ADDR8/4095));//�d����\��
		
		USB_PRINTF("\n\r");//���s
		USB_PRINTF("        Current New  \n\r");
		USB_PRINTF("REF_SEN_R= %4d  %4d\n\r",ref_sen_r_c,ref_sen_r_n);
		USB_PRINTF("REF_SEN_L= %4d  %4d\n\r",ref_sen_l_c,ref_sen_l_n);
		USB_PRINTF("TH_SEN_R = %4d  %4d\n\r",th_sen_r_c,th_sen_r_n);
		USB_PRINTF("TH_SEN_L = %4d  %4d\n\r",th_sen_l_c,th_sen_l_n);
		USB_PRINTF("TH_SEN_FR= %4d  %4d\n\r",th_sen_fr_c,th_sen_fr_n);
		USB_PRINTF("TH_SEN_FL= %4d  %4d\n\r",th_sen_fl_c,th_sen_fl_n);

		USB_PRINTF("\n\r");//���s
		switch(change_mode){
			case 0:
				USB_PRINTF("Changing REF_SEN_R value ? Yes:Right button,No:Left button");
				if(!(SW_L & SW_R)){					//�X�C�b�`���������܂ő҂�
					wait_ms(CHATTERING_WAIT);		//�`���^�����O�h�~�̑҂�����
					while( (SW_L & SW_R));			//���ꂩ�̃X�C�b�`���������܂ő҂�
					if(SW_L == SW_ON)				//���X�C�b�`��������Ă����玟�̃��[�h�ɐi��
					{
						SET_BUZZER_FREQ(INC_FREQ);	//�l�������������̎��g����ݒ�				
						ENABLE_BUZZER;				//�u�U�[�𔭐U������
						change_mode++;
					}
					if(SW_R == SW_ON)				//�E�X�C�b�`��������Ă�����l������������
					{
						SET_BUZZER_FREQ(DEC_FREQ);	//�l�������������̎��g��������
						ENABLE_BUZZER;				//�u�U�[�𔭐U������						
						ref_sen_r_n=sen_r.value;
						change_mode++;
					}
				}
				break;
			case 1:
				USB_PRINTF("Changing REF_SEN_L value ? Yes:Right button,No:Left button");
				if(!(SW_L & SW_R)){					//�X�C�b�`���������܂ő҂�
					wait_ms(CHATTERING_WAIT);		//�`���^�����O�h�~�̑҂�����
					while( (SW_L & SW_R));			//���ꂩ�̃X�C�b�`���������܂ő҂�
					if(SW_L == SW_ON)				//���X�C�b�`��������Ă����玟�̃��[�h�ɐi��
					{
						SET_BUZZER_FREQ(INC_FREQ);	//�l�������������̎��g����ݒ�				
						ENABLE_BUZZER;				//�u�U�[�𔭐U������
						change_mode++;
					}
					if(SW_R == SW_ON)				//�E�X�C�b�`��������Ă�����l������������
					{
						SET_BUZZER_FREQ(DEC_FREQ);	//�l�������������̎��g��������
						ENABLE_BUZZER;				//�u�U�[�𔭐U������						
						ref_sen_l_n=sen_l.value;
						change_mode++;
					}
				}
				break;				
			case 2:
				USB_PRINTF("Changing TH_SEN_R value ? Yes:Right button,No:Left button");
				if(!(SW_L & SW_R)){					//�X�C�b�`���������܂ő҂�
					wait_ms(CHATTERING_WAIT);		//�`���^�����O�h�~�̑҂�����
					while( (SW_L & SW_R));			//���ꂩ�̃X�C�b�`���������܂ő҂�
					if(SW_L == SW_ON)				//���X�C�b�`��������Ă����玟�̃��[�h�ɐi��
					{
						SET_BUZZER_FREQ(INC_FREQ);	//�l�������������̎��g����ݒ�				
						ENABLE_BUZZER;				//�u�U�[�𔭐U������
						change_mode++;
					}
					if(SW_R == SW_ON)				//�E�X�C�b�`��������Ă�����l������������
					{
						SET_BUZZER_FREQ(DEC_FREQ);	//�l�������������̎��g��������
						ENABLE_BUZZER;				//�u�U�[�𔭐U������						
						th_sen_r_n=sen_r.value;
						change_mode++;
					}
				}
				break;
			case 3:
				USB_PRINTF("Changing TH_SEN_L value ? Yes:Right button,No:Left button");
				if(!(SW_L & SW_R)){					//�X�C�b�`���������܂ő҂�
					wait_ms(CHATTERING_WAIT);		//�`���^�����O�h�~�̑҂�����
					while( (SW_L & SW_R));			//���ꂩ�̃X�C�b�`���������܂ő҂�
					if(SW_L == SW_ON)				//���X�C�b�`��������Ă����玟�̃��[�h�ɐi��
					{
						SET_BUZZER_FREQ(INC_FREQ);	//�l�������������̎��g����ݒ�				
						ENABLE_BUZZER;				//�u�U�[�𔭐U������
						change_mode++;
					}
					if(SW_R == SW_ON)				//�E�X�C�b�`��������Ă�����l������������
					{
						SET_BUZZER_FREQ(DEC_FREQ);	//�l�������������̎��g��������
						ENABLE_BUZZER;				//�u�U�[�𔭐U������						
						th_sen_l_n=sen_l.value;
						change_mode++;
					}
				}
				break;	
			case 4:
				USB_PRINTF("Changing TH_SEN_FR value ? Yes:Right button,No:Left button");
				if(!(SW_L & SW_R)){					//�X�C�b�`���������܂ő҂�
					wait_ms(CHATTERING_WAIT);		//�`���^�����O�h�~�̑҂�����
					while( (SW_L & SW_R));			//���ꂩ�̃X�C�b�`���������܂ő҂�
					if(SW_L == SW_ON)				//���X�C�b�`��������Ă����玟�̃��[�h�ɐi��
					{
						SET_BUZZER_FREQ(INC_FREQ);	//�l�������������̎��g����ݒ�				
						ENABLE_BUZZER;				//�u�U�[�𔭐U������
						change_mode++;
					}
					if(SW_R == SW_ON)				//�E�X�C�b�`��������Ă�����l������������
					{
						SET_BUZZER_FREQ(DEC_FREQ);	//�l�������������̎��g��������
						ENABLE_BUZZER;				//�u�U�[�𔭐U������						
						th_sen_fr_n=sen_fr.value;
						change_mode++;
					}
				}
				break;
			case 5:
				USB_PRINTF("Changing TH_SEN_FL value ? Yes:Right button,No:Left button");
				if(!(SW_L & SW_R)){					//�X�C�b�`���������܂ő҂�
					wait_ms(CHATTERING_WAIT);		//�`���^�����O�h�~�̑҂�����
					while( (SW_L & SW_R));			//���ꂩ�̃X�C�b�`���������܂ő҂�
					if(SW_L == SW_ON)				//���X�C�b�`��������Ă����玟�̃��[�h�ɐi��
					{
						SET_BUZZER_FREQ(INC_FREQ);	//�l�������������̎��g����ݒ�				
						ENABLE_BUZZER;				//�u�U�[�𔭐U������
						change_mode++;
					}
					if(SW_R == SW_ON)				//�E�X�C�b�`��������Ă�����l������������
					{
						SET_BUZZER_FREQ(DEC_FREQ);	//�l�������������̎��g��������
						ENABLE_BUZZER;				//�u�U�[�𔭐U������						
						th_sen_fl_n=sen_fl.value;
						change_mode++;
					}
				}
				break;
			case 6:
				USB_PRINTF("Changing value write? Yes:Right button,No:Left button");
				if(!(SW_L & SW_R)){					//�X�C�b�`���������܂ő҂�
					wait_ms(CHATTERING_WAIT);		//�`���^�����O�h�~�̑҂�����
					while( (SW_L & SW_R));			//���ꂩ�̃X�C�b�`���������܂ő҂�
					if(SW_L == SW_ON)				//���X�C�b�`��������Ă����玟�̃��[�h�ɐi��
					{
						SET_BUZZER_FREQ(INC_FREQ);	//�l�������������̎��g����ݒ�				
						ENABLE_BUZZER;				//�u�U�[�𔭐U������
						change_mode=0;
					}
					if(SW_R == SW_ON)				//�E�X�C�b�`��������Ă�����l������������
					{
						SET_BUZZER_FREQ(DEC_FREQ);	//�l�������������̎��g��������
						ENABLE_BUZZER;				//�u�U�[�𔭐U������	
						
						ref_sen_r_c=ref_sen_r_n;	//�}�E�X����H�����ɒu�������̃Z���T�̒l
						ref_sen_l_c=ref_sen_l_n;	//�}�E�X����H�����ɒu�������̃Z���T�̒l
						th_sen_r_c =th_sen_r_n;		//�ǂ����邩�ۂ���臒l
						th_sen_l_c =th_sen_l_n;		//�ǂ����邩�ۂ���臒l
						th_sen_fr_c=th_sen_fr_n;	//�ǂ����邩�ۂ���臒l
						th_sen_fl_c=th_sen_fl_n;	//�ǂ����邩�ۂ���臒l
						
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
		wait_ms(CHATTERING_WAIT*3);		//�`���^�����O�h�~�̑҂�����
		DISABLE_BUZZER;					//�u�U�[���~�߂�
		
		for(i = 0; i < 0xfffff; i++);	//�\���Ԋu��ݒ�
		
		//��ʃN���A�V�[�P���X
		USB_PRINTF("\x1b[2J");			//�N���A�X�N���[��[CLS]
		USB_PRINTF("\x1b[0;0H");		//�J�[�\����0,0�Ɉړ�
	}
}


void straight_check(int section_check)	//�^�C�����a�`�F�b�N�p
{
	max_speed = SEARCH_SPEED;			//�T���̑��x���w��
	accel = SEARCH_ACCEL;				//�����x���w��

	wait_ms(1000);
	straight(SECTION * section_check,0,SEARCH_SPEED,0);//section_check���i��
	
}


void go_and_turn_right(void)			//�^�C���g���b�h�a�`�F�b�N�p
{
	int i;
	max_speed = SEARCH_SPEED;			//�T���̑��x���w��
	accel = SEARCH_ACCEL;			//�����x���w��

	wait_ms(1000);					//1�b�҂�
	
/*
	for(i=0;i<8;i++){
		rotate(right,1);				//���̏��90�x�E�^�[��
	}
*/	
	while(1){
		straight_check(2);			//2���i��
		rotate(right,2);				//���̏��180�x�E�^�[��
		straight_check(2);			//2���i��	
		rotate(right,2);				//���̏��180�x�E�^�[��
	}

}


void adjust_menu(void)	//�����p���j���[
{
	int mode = 1;		//���j���[�p�ϐ�
	

	while(1)			//���[�h�I��
	{

		wait_ms(CHATTERING_WAIT*3);							//�`���^�����O�h�~�̑҂�����
		DISABLE_BUZZER;
		while( !(SW_L & SW_C & SW_R) ) ;
		wait_ms(CHATTERING_WAIT);							//�`���^�����O�h�~�̑҂�����

		_LED(mode);											//���݂̃��[�h���ԑ̑O���̂k�d�c�ɕ\������
		
		while( SW_L & SW_C & SW_R )							//���ꂩ�̃X�C�b�`���������܂ő҂�
		{
			wait_ms(33);
			LED3 ^= 1;										//���](�`�J�`�J������)
			
		}
		LED3 = 0;
		//�ȍ~�ŁA�ǂ̃X�C�b�`�������ꂽ�����f

		if(SW_L == SW_ON)									//���X�C�b�`��������Ă����玟�̃��[�h�ɐi��
		{
			mode++;
			if(mode > 7)									//���[�h��15�Ԃ܂łȂ̂ŁA����𒴂��Ȃ��悤�ɂ���
			{
				mode = 7;
			}else{
				SET_BUZZER_FREQ(INC_FREQ);				
				ENABLE_BUZZER;
			}
		}
		else if(SW_R == SW_ON)								//�E�X�C�b�`��������Ă�����O�̃��[�h�ɖ߂�
		{
			mode--;
			if(mode < 1)									//���[�h��1�Ԃ���Ȃ̂ŁA����ȉ��ɂȂ�Ȃ��悤�ɂ���
			{
				mode = 1;
			}else{
				SET_BUZZER_FREQ(DEC_FREQ);					//�u�U�[�̎��g��������
				ENABLE_BUZZER;								//�u�U�[�𔭐U������
			}
		}
		else if(SW_C == SW_ON)								//�����X�C�b�`��������Ă�����A���݂̃��[�h�����s����
		{
			SET_BUZZER_FREQ(DEC_FREQ);						//����X�C�b�`�������ꂽ�Ƃ��̉���炷
			ENABLE_BUZZER;									//�u�U�[�𔭐U������
			wait_ms(CHATTERING_WAIT*8);
			SET_BUZZER_FREQ(INC_FREQ);						//��(���g��)��ύX����
			wait_ms(CHATTERING_WAIT*8);
			DISABLE_BUZZER;									//�u�U�[�̔��U���~������
			if(exec_by_mode_adjust(mode) == 1)
			{
				return;										//���݂̃��[�h�����s����

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
	
	USB_PRINTF("\x1b[0;0H");								//�J�[�\����0,0�Ɉړ�
	USB_PRINTF("\n\r+");
	for(i = 0 ; i < MAZESIZE_X; i++){
		switch(wall[i][MAZESIZE_Y-1].north){				//���F��"[30m"
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
//����mode������A���̃��[�h�ɓ���B
//�߂�l��1�̏ꍇ�́A��{�̃��j���[�ɖ߂�

	switch(mode)
	{
		case 1:
			view_adc();				//A/D�ϊ��̌��ʂ�USB�ɏo�͂���
			break;
			
		case 2:
			straight_check(4);  	//9��撼���𑖂�
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
			return 1;				//���[�h�V�͌��̃��j���[�ɖ߂�
			break;
	}
	
	return 0;
}
