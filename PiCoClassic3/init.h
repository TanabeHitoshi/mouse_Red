
#include "portdef.h"
#include "iodefine.h"
#include "parameters.h"
#include "mytypedef.h"


extern t_sensor sen_r,sen_l,sen_fr,sen_fl;	//�O���錾�̃Z���T�\����
extern t_control con_wall;					//�O���錾�̐���\����

void init_all(void);						//�S��������(�S�����Ăяo��)
void init_clock(void);						//CPU�̓�����g����ݒ�
void init_io(void);							//IO�|�[�g������
void init_cmt(void);						//CMT������
void init_mtu(void);						//MTU�ݒ�
void init_adc(void);						//AD������
//void init_sci(void);						//SCI������
void init_parameters(void);					//�p�����[�^������
void init_maze(void);						//���H���̏���