#ifndef _PARAMETER

#include "static_parameters.h"
//�≺
//�����I�ȃp�����[�^
#define TIRE_DIAMETER	(48.0 -0.1)				//�^�C���̒��a
#define TREAD_WIDTH	(64.0 +6.2)					//�g���b�h��
#define TREAD_CIRCUIT	(TREAD_WIDTH*PI/4)	//���M�n����̎��Ƀ^�C������������

//�Z���T�֘A�p�����[�^                                              
#define WAITLOOP_SLED 300					//LED�����点�Ă���AD�ϊ����J�n����܂ł̎��ԉ҂��p�萔
#define REF_SEN_R	468//526//584	 				//�}�E�X����H�����ɒu�������̃Z���T�̒l
#define REF_SEN_L	741//693//604						//�}�E�X����H�����ɒu�������̃Z���T�̒l
                                                                                                                                                                  
#define TH_SEN_R	198//172//160//302//295//153							//�ǂ����邩�ۂ���臒l
#define TH_SEN_L	252//241//262//211//221//153							//�ǂ����邩�ۂ���臒l
#define TH_SEN_FR	171//188//186//250//254//143							//�ǂ����邩�ۂ���臒l
#define TH_SEN_FL	291//301//315//308//343//94	

#define CONTH_SEN_R	TH_SEN_R				//����������邩�ۂ���臒l
#define CONTH_SEN_L	TH_SEN_L				//����������邩�ۂ���臒l

#define CON_WALL_KP	(0.16)					//�ǃZ���T�ɂ��p������̔�ᐧ��̔��萔
#define con_wall_KD	0.1						//�ǃZ���T�ɂ��p������̔�������̔��萔

//���s�p�����[�^
#define SEARCH_SPEED	(430)				//�T���̑��x
#define SEARCH_ACCEL	(1.6)				//�T���̉����x

#define TURN_ACCEL	(0.5)					//���M�n����̉����x
#define	TURN_SPEED	(364)					//���M�n����̍ō����x�̃��~�b�g

#define SLALOM_DEFF		(0.417 - 0.09)//(0.02)//(0.04)			//�X�����[�����s�̓��֍�
#define SLALOM_ACCEL	(0.4)					//�X�����[�����s�̉����x
#define SLALOM_OFFSETL	(15.0)					//�X���[
#define SLALOM_ANGLE	(2.0*70.0/4.0)				//�X�����[���̑��s����
#define SLALOM_MIN_SPEED	(300)				//�X�����[�����s�̏����x
//#define SLALOM_MAX_SPEED	(500)
#define SLALOM_SPEED	(400)//(408)
#define MAX_SLALOM_SP1	(550)					//�X�����[�����s�̑��s���x
#define MAX_SLALOM_SP2	(600)					//�X�����[�����s�̑��s���x      
#define MAX_SLALOM_SP3	(650)					//�X�����[�����s�̑��s���x

//���H�֘A�p�����[�^
#define GOAL_X	7							//�S�[�����W(x)
#define GOAL_Y	7							//�S�[�����W(y)

#define _PARAMETER

#endif
