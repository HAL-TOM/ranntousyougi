#pragma once
enum ACTION_TYPE
{
	ACTION_TYPE_MOVEPIECE = 0,
	ACTION_TYPE_TAKEPIECE,
	ACTION_TYPE_USEHAND
};

class CAction
{
protected:
	//���̍s���ɕK�v�ȃp�����[�^�i�}�X�Ƃ��j



	ACTION_TYPE m_type;//���̃A�N�V������
	int m_value = 0;

public:
	//���̍s���ɕK�v�ȃp�����[�^���Z�b�g����
	//void�@Setting();//�������N���X���ƂɈقȂ邩�牼�z�֐��ɂł��Ȃ��i�炢�j
	
	
	//���̍s���̌��ʗL���ɂȂ邩�ǂ����A�{�̒l�������قǗL���iAction�N���X���]������ׂ��Ȃ̂��H�j
	virtual int CreateValue()=0;
	//�]���l���擾
	int GetValue() { return m_value; }
	ACTION_TYPE GetType() { return m_type; }
};

