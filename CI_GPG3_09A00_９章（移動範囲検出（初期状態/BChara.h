#pragma warning(disable:4996)
#pragma once
//-----------------------------------------------------------------------------
//�L�����N�^�ėp�X�[�p�[�N���X
//-----------------------------------------------------------------------------
#include "GameEngine_Ver3_83.h"

class BChara : public BTask
{
	//�ύX�s����������������������������������������������������
public:
	typedef shared_ptr<BChara>		SP;
	typedef weak_ptr<BChara>		WP;
public:
	//�ύX������������������������������������������������������
	//�L�����N�^���ʃ����o�ϐ�
	ML::Vec2	    pos;			//�L�����N�^�ʒu
	int				moveStep;		//	����
};