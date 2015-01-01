#pragma once

#define NO_FILL			-1
#define ALL_FILL		-2

#define DIGITAL_ERROR	101
#define BIN_ERROR		102
#define POS_ERROR		103

int GetBin(int digital);
int GetDigital(int bin);

class CUnit
{
public:
	int m_fill;			//��ʾ�����������һ��9λ��������
	int m_dig;			//���������0��ʾʲô��û��

	CUnit();

	CUnit &operator =(int dig);
	bool operator ==(int dig);
};