// ННГУ, ВМК, Курс "Методы программирования-2", С++, ООП
//
// tbitfield.cpp - Copyright (c) Гергель В.П. 07.05.2001
//   Переработано для Microsoft Visual Studio 2008 Сысоевым А.В. (19.04.2015)
//
// Битовое поле

#include "tbitfield.h"

TBitField::TBitField() //конструктор без параметров
{
	BitLen = 0;
	pMem = 0;
}

TBitField::TBitField(int len)
{
	BitLen = len;
	MemLen = (len + 31) >> 5;
	pMem = new TELEM[MemLen];
	if (pMem == NULL)
	{
	for (int i = 0; i < MemLen; i++)
	{
			pMem[i] = 0;
		}
	}
}

TBitField::TBitField(const TBitField &bf) // конструктор копирования
{
	this -> BitLen = bf.BitLen;
	this -> MemLen = bf.MemLen;
	this -> pMem = new TELEM[MemLen];
	if (pMem == NULL)
	{
	for (int i = 0; i < MemLen; i++)
	{
			this -> pMem[i] = bf.pMem[i];
		}
	}
}

TBitField::~TBitField()
{
	delete[] pMem;
}

int TBitField::GetMemIndex(const int n) const // индекс Мем для бита n
{

}

TELEM TBitField::GetMemMask(const int n) const // битовая маска для бита n
{
}

// доступ к битам битового поля

int TBitField::GetLength(void) const // получить длину (к-во битов)
{
  return BitLen;
}

void TBitField::SetBit(const int n) // установить бит
{

}

void TBitField::ClrBit(const int n) // очистить бит
{
}

int TBitField::GetBit(const int n) const // получить значение бита
{
  return 0;
}

// битовые операции

TBitField& TBitField::operator=(const TBitField &bf) // присваивание
{
	if (pMem != 0)
	{
		delete[] pMem;
	}
	this -> BitLen = bf.BitLen;
	if (MemLen != bf.MemLen)
	{
		this -> MemLen = bf.MemLen;
	}

	this -> pMem = new TELEM[MemLen];
	for (int i = 0; i < MemLen; i++)
	{
		this->pMem[i] = bf.pMem[i];
	}
	return *this;
}

int TBitField::operator==(const TBitField &bf) const // сравнение
{

  return 0;
}

int TBitField::operator!=(const TBitField &bf) const // сравнение
{
  return 0;
}

TBitField TBitField::operator|(const TBitField &bf) // операция "или"(объединение)
{
	TBitField t;
	for (int i = 0; i < MemLen; i++)
	{
		t.pMem[i] = pMem[i] | bf.pMem[i];
	}

	return t;
}

TBitField TBitField::operator&(const TBitField &bf) // операция "и"
{
	TBitField t;
	for (int i = 0; i < MemLen; i++)
	{
		t.pMem[i] = pMem[i] & bf.pMem[i];
	}

	return t;
}

TBitField TBitField::operator~(void) // отрицание
{
	TBitField t;
	for (int i = 0; i < MemLen; i++)
	{
		t.pMem[i] = ~pMem[i];
	}

	return t;
}

// ввод/вывод

istream &operator>>(istream &istr, TBitField &bf) // ввод
{
}

ostream &operator<<(ostream &ostr, const TBitField &bf) // вывод
{

}
