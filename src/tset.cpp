// ННГУ, ВМК, Курс "Методы программирования-2", С++, ООП
//
// tset.cpp - Copyright (c) Гергель В.П. 04.10.2001
//   Переработано для Microsoft Visual Studio 2008 Сысоевым А.В. (19.04.2015)
//
// Множество - реализация через битовые поля

#include "tset.h"

TSet::TSet(int mp)// : BitField(mp)
{
	BitField = TBitField(mp);
	MaxPower = mp;
}

// конструктор копирования
TSet::TSet(const TSet &s) //: BitField(s.BitField)
{
	BitField = TBitField(s.BitField);
	MaxPower = s.MaxPower;
}

// конструктор преобразования типа
TSet::TSet(const TBitField &bf) //: BitField(bf)
{
	BitField = TBitField(bf);
}

TSet::operator TBitField()
{
	return BitField;
}

int TSet::GetMaxPower(void) const // получить макс. к-во эл-тов
{
	int temp;
	temp = MaxPower;
	return temp;
}

int TSet::IsMember(const int Elem) const // элемент множества?
{
	int temp;
	temp = BitField.GetBit(Elem);
	return temp;
}

void TSet::InsElem(const int Elem) // включение элемента множества
{
	BitField.SetBit(Elem);
}

void TSet::DelElem(const int Elem) // исключение элемента множества
{
	BitField.ClrBit(Elem);
}

// теоретико-множественные операции

TSet& TSet::operator=(const TSet &s) // присваивание
{
	MaxPower = s.MaxPower;
	BitField = s.BitField;
	return *this;
}

int TSet::operator==(const TSet &s) const // сравнение
{
	if (BitField != s.BitField)
	{
		return 0;
	}
	else
	{
		return BitField == s.BitField;
	}
}

int TSet::operator!=(const TSet &s) const // сравнение
{
	if (BitField != s.BitField)
	{
		return BitField != s.BitField;
	}
	else
	{
		return 0;
	}
}

TSet TSet::operator+(const TSet &s) // объединение
{
	int len = s.BitField.GetLength();
	TSet c(len);
	for (int i = 0; i < len; i++)
	{
		if (s.BitField.GetBit(i))
		{
			c.InsElem(i);
		}
	}
	for (int i = 0; i < len; i++)
	{
		if (BitField.GetBit(i))
		{
			c.InsElem(i);
		}
	}
	return c;
}

TSet TSet::operator+(const int Elem) // объединение с элементом
{
	return 0;
}

TSet TSet::operator-(const int Elem) // разность с элементом
{
	TSet tmp(BitField);
	tmp.DelElem(Elem);
	return tmp;
}

TSet TSet::operator*(const TSet &s) // пересечение
{
	TSet tmp(BitField & s.BitField);
	return tmp;
}

TSet TSet::operator~(void) // дополнение
{
	TSet tmp(~BitField);
	return tmp;
}

// перегрузка ввода/вывода

istream &operator>>(istream &istr, TSet &s) // ввод
{
	return istr;
}

ostream& operator<<(ostream &ostr, const TSet &s) // вывод
{
	return ostr;
}
