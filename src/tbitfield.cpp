// ННГУ, ВМК, Курс "Методы программирования-2", С++, ООП
//
// tbitfield.cpp - Copyright (c) Гергель В.П. 07.05.2001
//   Переработано для Microsoft Visual Studio 2008 Сысоевым А.В. (19.04.2015)
//
// Битовое поле

#include "tbitfield.h"

TBitField::TBitField()
{
	BitLen = 0;
	MemLen = 0;
	pMem = 0;
}
TBitField::TBitField(int len)
{
	if (len <= 0)                       //Исключение.
	{
		throw "negative_length";
	}
	BitLen = len;
	MemLen = (len + 31) >> 5;
	pMem = new TELEM[MemLen];
	if (pMem != NULL)
	{
		for (int i = 0; i < MemLen; i++)
		{
			pMem[i] = 0;
		}
	}
}

TBitField::TBitField(const TBitField &bf) // конструктор копирования
{
	if (bf.BitLen <= 0)
	{
		throw "negative_length";
	}
	this->BitLen = bf.BitLen;
	this->MemLen = bf.MemLen;
	pMem = new TELEM[MemLen];
	if (pMem != NULL){
		for (int i = 0; i < MemLen; i++)
		{
			this->pMem[i] = bf.pMem[i];
		}
	}
}

TBitField::~TBitField()
{
	delete[] pMem;
}

int TBitField::GetMemIndex(const int n) const // индекс Мем для бита n
{
	return n >> 5; // >> деление на 2^5. Например берем 45-ый элемент , он находится в первом инте. (0 ой инт и 1 ый инт) и его индекс 14. 
	// при делении на цело, получаем 45/32=1, мы получили, что первый инт. Чтобы найти его индекс, берем остаток, т.е. 45/32=14.
}

TELEM TBitField::GetMemMask(const int n) const // битовая маска для бита n
{
	return 1 << (n & 31); /* пусть на пример дано битовое множество из 0 и 1. 011101, и мы хотим третий элемент сделать 1, т.е. берем маску 001000
						  и делаем операцию логического умножения "&", результатом будет   011101 & 001000 = 001000. Теперь сдвигаем нашу маску
						  на 1 индекс влево, т.е. будет 1<<001000=010000 */

}

// доступ к битам битового поля

int TBitField::GetLength(void) const // получить длину (к-во битов)
{
	return BitLen;
}

void TBitField::SetBit(const int n) // установить бит
{
	if ((n < 0) || (n >= BitLen))     //проверяем, чтобы не выходило за границы заданного поля.
	{
		throw "incorrect_set_index"; //проверяем на отрицательный индекс и исключаем
	}
	pMem[GetMemIndex(n)] = pMem[GetMemIndex(n)] | GetMemMask(n); // наш массив с индексом n складываем с маской, т.е. 01101 | 00010 = 011(1)1  мы установили бит.
}

void TBitField::ClrBit(const int n) // очистить бит
{
	if ((n < 0) || (n >= BitLen))     //проверяем, чтобы не выходило за границы заданного поля.
	{
		throw "incorrect_clr_index";
	}
	pMem[GetMemIndex(n)] = pMem[GetMemIndex(n)] & ~GetMemMask(n); // наш массив с индексом n умножаем на нашу (~маску)
	// и потом применяем операцию "&", т.е. было 01101 & (~00010) => 01101 & 11101= 01101

}

int TBitField::GetBit(const int n) const // получить значение бита
{
	if ((n < 0) || (n >= BitLen))     //проверяем, чтобы не выходило за границы заданного поля.
	{
		throw "incorrect_get_index";
	}
	return pMem[GetMemIndex(n)] & GetMemMask(n); //получаем значение 0 или 1

	return 0;
}

// битовые операции

TBitField& TBitField::operator=(const TBitField &bf) // присваивание
{
	BitLen = bf.BitLen;
	if (MemLen != bf.MemLen)
	{
		MemLen = bf.MemLen;
	}
	if (pMem != NULL){
		delete[] pMem;
	}
	pMem = new TELEM[MemLen];

	for (int i = 0; i < MemLen; i++)
	{
		pMem[i] = bf.pMem[i];
	}
	return *this;
}

int TBitField::operator==(const TBitField &bf) const // сравнение
{
	int temp = 1;
	if (BitLen != bf.BitLen)
	{
		temp = 0;
	}
	else
	{
		for (int i = 0; i < MemLen; i++)
		{
			if (pMem[i] != bf.pMem[i])
			{
				temp = 0;
				break;
			}
		}
	}
	return temp;
}

int TBitField::operator!=(const TBitField &bf) const // сравнение
{
	int temp = 0;
	if (BitLen != bf.BitLen)
	{
		temp = 1;
	}
	else
	{
		for (int i = 0; i < MemLen; i++)
		{
			if (pMem[i] != bf.pMem[i])
			{
				temp = 1;
				break;
			}
		}
	}
	return temp;
}

TBitField TBitField::operator|(const TBitField &bf) // операция "или"(объединение)
{
	if (BitLen != bf.BitLen)     //проверяем, чтобы не выходило за границы заданного поля.
	{
		throw "non_equal_size";
	}

	TBitField tmp(BitLen);
	for (int i = 0; i < tmp.MemLen; i++)
	{
		tmp.pMem[i] = bf.pMem[i];
	}

	for (int i = 0; i < tmp.MemLen; i++)
	{
		tmp.pMem[i] = tmp.pMem[i] | pMem[i];
	}
	return tmp;
}

TBitField TBitField::operator&(const TBitField &bf) // операция "и"
{
	if (BitLen != bf.BitLen)     //проверяем, чтобы не выходило за границы заданного поля.
	{
		throw "non_equal_size";
	}
	TBitField tmp(BitLen);
	for (int i = 0; i < tmp.MemLen; i++)
	{
		tmp.pMem[i] = bf.pMem[i];
	}
	for (int i = 0; i < tmp.MemLen; i++)
	{
		tmp.pMem[i] = tmp.pMem[i] & pMem[i];
	}
	return tmp;
}

TBitField TBitField::operator~(void) // отрицание
{
	int n;
	n = BitLen;
	TBitField tmp(n);
	/*for (int i = 0; i < MemLen; i++)
	{
	tmp.pMem[i] = ~pMem[i];
	}*/
	for (int i = 0; i < n; i++)
	{
		if (GetBit(i))
		{
			tmp.ClrBit(i);
		}
		else
		{
			tmp.SetBit(i);
		}
	}
	return tmp;
}

// ввод/вывод

istream &operator>>(istream &istr, TBitField &bf) // ввод
{
	// вводить мы должны числа 0 или 1, без пробелов.
	// Если на вход получили число !=0 или !=1, то прекращается ввод.
	char a = '\0';
	while (a != ' ')
	{
		istr >> a;
	}
	int i = 0;
	while (1)    //бесконечный цикл
	{
		istr >> a;
		if (a == '0')
		{
			bf.ClrBit(i++);
		}
		if (a == '1')
		{
			bf.SetBit(i++);
		}
		else
		{
			break;
		}
	}
	return istr;
}

ostream &operator<<(ostream &ostr, const TBitField &bf) // вывод
{
	return ostr;
}
