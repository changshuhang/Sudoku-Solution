#include "Sudoku.h"

#define FLAG_SWITCH(flag) switch(flag){
#define CASE_NORMAL case CSudoku::normal:{
#define CASE_NOTONLY break;} case CSudoku::notonly:{
#define CASE_NOSLN break;} case CSudoku::nosln:{
#define END_SWITCH break; }default: break;}

CSudoku::CSudoku(int lattice[9][9])
{
	for (int i = 0; i < 9; i++)
	{
		for (int j = 0; j < 9; j++)
		{
			m_lattice[i][j] = lattice[i][j];
		}
	}
	for (int i = 0; i < 9; i++)
	{
		for (int j = 0; j < 9; j++)
		{
			if (m_lattice[i][j] == 0)
			{updataFill(i, j);}
		}
	}
}

void CSudoku::getStartPos(int i, int j, int &s_i, int &s_j)
{
	bool isSuccess = true;

	/**
	j 
	i| 0 1 2 | 3 4 5 | 6 7 8 |
	-+-------+-------+-------+
	0|       |       |       |
	1|   1   |   4   |   7   |
	2|       |       |       |
	-+-------+-------+-------+
	3|       |       |       |
	4|   2   |   5   |   8   |
	5|       |       |       |
	-+-------+-------+-------+
	6|       |       |       |
	7|   3   |   6   |   9   |
	8|       |       |       |
	-+-------+-------+-------+
	*/
	if ( (i >= 0 && i <= 2) && (j >= 0 && j <= 2) )					//1
	{
		s_i = 0;
		s_j = 0;
	}
	else if ( (i >= 3 && i <= 5) && (j >= 0 && j <= 2) )			//2
	{
		s_i = 3;
		s_j = 0;
	}
	else if ( (i >= 6 && i <= 8) && (j >= 0 && j <= 2) )			//3
	{
		s_i = 6;
		s_j = 0;
	}
	else if ( (i >= 0 && i <= 2) && (j >= 3 && j <= 5) )			//4
	{
		s_i = 0;
		s_j = 3;
	}
	else if ( (i >= 3 && i <= 5) && (j >= 3 && j <= 5) )			//5
	{
		s_i = 3;
		s_j = 3;
	}
	else if ( (i >= 6 && i <= 8) && (j >= 3 && j <= 5) )			//6
	{
		s_i = 6;
		s_j = 3;
	}
	else if ( (i >= 0 && i <= 2) && (j >= 6 && j <= 8) )			//7
	{
		s_i = 0;
		s_j = 6;
	}
	else if ( (i >= 3 && i <= 5) && (j >= 6 && j <= 8) )			//8
	{
		s_i = 3;
		s_j = 6;
	}
	else if ( (i >= 6 && i <= 8) && (j >= 6 && j <= 8) )			//9
	{
		s_i = 6;
		s_j = 6;
	}
	else
	{
		isSuccess = false;
	}

	if(!isSuccess)
	{
		throw POS_ERROR;
	}
}

int CSudoku::BitCount(int bit)
{
	int count;
	for (count = 0; bit != 0; bit >>= 1)
	{
		count += bit & 1;
	}
	return count;
}

void CSudoku::updataFill(int i, int j)
{
	if (m_lattice[i][j] == 0)
	{
		for (int _i = 0; _i < 9; _i++)		//��
		{
			m_lattice[i][j].m_fill = m_lattice[i][j].m_fill & ~GetBin(m_lattice[_i][j].m_dig);
		}
		for (int _j = 0; _j < 9; _j++)		//��
		{
			m_lattice[i][j].m_fill = m_lattice[i][j].m_fill & ~GetBin(m_lattice[i][_j].m_dig);
		}
		/*�Ź���*/
		int s_i, s_j;
		getStartPos(i, j, s_i, s_j);

		for (int _i = s_i; _i < s_i+3; _i++)
		{
			for (int _j = s_j; _j < s_j+3; _j++)
			{
				m_lattice[i][j].m_fill = m_lattice[i][j].m_fill & ~GetBin(m_lattice[_i][_j].m_dig);
			}
		}
	}
	else
	{
		m_lattice[i][j].m_fill = GetBin(NO_FILL);
	}
}

int CSudoku::getDigit(int i, int j)
{
	return m_lattice[i][j].m_dig;
}

bool CSudoku::StartCount()
{
	Flag flag = normal;

	int c_fblank = 0;			//Ϊ�ж��Ƿ��ҵ��հ׵�Ԫ��
	int c_fsingle = 0;			//Ϊ�ж��Ƿ��ҵ�Ψһ����Ԫ��
	int c_fnosln = 0;			//Ϊ�ж��Ƿ��ҵ��޽ⵥԪ��

	do
	{
		c_fblank = 0;
		c_fsingle = 0;
		c_fnosln = 0;

		FLAG_SWITCH(flag)
		CASE_NORMAL
		for (int i = 0; i < 9; i++)
		{
			for (int j = 0; j < 9; j++)
			{
				if (m_lattice[i][j] == 0)			//�ҿհ׵�Ԫ��
				{
					updataFill(i, j);
					if ( BitCount(m_lattice[i][j].m_fill) == 1 )		//��Ψһ��Ԫ��
					{
						m_lattice[i][j] = GetDigital(m_lattice[i][j].m_fill);
						c_fsingle++;
						c_fblank--;
					}
					else if ( BitCount(m_lattice[i][j].m_fill) == 0 )	//���޽ⵥԪ��
					{
						c_fnosln++;
					}
					c_fblank++;
				}
			}//end for
		}
		if (c_fblank == 0) return true;		//ѭ������
		CASE_NOTONLY

		int _numfill = 999;
		int _i, _j;

		for (int i = 0; i < 9; i++)			//�ҵ�һ�����������ٵĵ�Ԫ��
		{
			for (int j = 0; j < 9; j++)
			{
				if ( BitCount(m_lattice[i][j].m_fill) < _numfill && m_lattice[i][j] == 0 )
				{
					_numfill = BitCount(m_lattice[i][j].m_fill);
					_i = i; _j = j;
				}
			}
		}
		int _count = 1;
		int _bin = m_lattice[_i][_j].m_fill;

		while ((_bin & 1) != 1)
		{
			_bin = _bin >> 1;
			_count++;
			if (_count > 9) _Debug_message(L"��ѭ��",L"Sudoku.cpp",209);
		}
		/*����״̬*/
		CCache _cache(m_lattice, _i, _j, _count);
		m_cache.push(_cache);
		/*����*/
		m_lattice[_i][_j] = _count;

		flag = CSudoku::normal;
		continue;

		CASE_NOSLN
		do
		{
			if (m_cache.empty()) return false;

			for (int i = 0; i < 9; i++)
			{
				for (int j = 0; j < 9; j++)
				{
					m_lattice[i][j] = m_cache.top().m_lattice[i][j];
				}
			}
			int _count = 1;
			int _bin = m_lattice[m_cache.top().m_i][m_cache.top().m_j].m_fill;

			while ( ((_bin & 1) != 1) || (_count <= m_cache.top().m_digit) )
			{
				_bin = _bin >> 1;
				_count++;
				if (_count > 9) break; //_Debug_message(L"��ѭ��",L"Sudoku.cpp",239);
			}
			if (_count <= 9)
			{
				/*����������*/
				CCache _cache(m_lattice, m_cache.top().m_i, m_cache.top().m_j, _count);
				m_lattice[m_cache.top().m_i][m_cache.top().m_j] = _count;

				m_cache.pop();
				m_cache.push(_cache);
				break;			//ѭ������
			}
			else
			{
				m_cache.pop();
			}

		}while(true);

		flag = CSudoku::normal;
		continue;

		END_SWITCH

		if (c_fsingle == 0)
		{
			//������Ψһ����Ԫ��
			flag = CSudoku::notonly;
		}
		if (c_fnosln != 0)
		{
			//�����޽ⵥԪ��
			flag = CSudoku::nosln;
		}

	}while (true);

	return true;
}

CSudoku::CCache::CCache(CUnit lattice[9][9], int i, int j, int digit)
	: m_i(i), m_j(j), m_digit(digit)
{
	for (int i = 0; i < 9; i++)
	{
		for (int j = 0; j < 9; j++)
		{
			m_lattice[i][j] = lattice[i][j];
		}
	}
}