// ННГУ, ВМК, Курс "Методы программирования-2", С++, ООП
//
// tset.cpp - Copyright (c) Гергель В.П. 04.10.2001
//   Переработано для Microsoft Visual Studio 2008 Сысоевым А.В. (19.04.2015)
//
// Множество - реализация через битовые поля

#include "tset.h"

TSet::TSet(int mp) : BitField(mp),MaxPower(mp)
{
}

// конструктор копирования
TSet::TSet(const TSet &s) : BitField(s.BitField),MaxPower(s.MaxPower)
{
}

// конструктор преобразования типа
TSet::TSet(const TBitField &bf) : BitField(bf),MaxPower(bf.GetLength())
{
}

TSet::operator TBitField()
{
	return BitField;
}

int TSet::GetMaxPower(void) const // получить макс. к-во эл-тов
{
	return MaxPower;
}

int TSet::IsMember(const int Elem) const // элемент множества?
{
    return BitField.GetBit(Elem);
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
	BitField = s.BitField;
	MaxPower = s.MaxPower;
	return *this;
}

int TSet::operator==(const TSet &s) const // сравнение
{
   if(BitField==s.BitField) return 1;
   return 0;
}

int TSet::operator!=(const TSet &s) const // сравнение
{
	if (BitField != s.BitField) return 1;
	return 0;
}

TSet TSet::operator+(const TSet &s) // объединение
{
	TBitField tmp = BitField | s.BitField;
	TSet res(tmp);
	return res;
}

TSet TSet::operator+(const int Elem) // объединение с элементом
{
	TSet res(BitField);
	res.InsElem(Elem);
	return res;
}

TSet TSet::operator-(const int Elem) // разность с элементом
{
	TSet res(BitField);
	res.DelElem(Elem);
	return res;
}

TSet TSet::operator*(const TSet &s) // пересечение
{
	TBitField tmp = BitField & s.BitField;
	TSet res(tmp);
	return res;
}

TSet TSet::operator~(void) // дополнение
{
	return ~BitField;
}

// перегрузка ввода/вывода

istream &operator>>(istream &istr, TSet &s) // ввод
{
	int i;
	istr >> i;
	while (i >= 0) {
		s.InsElem(i);
		istr >> i;
	}
	return istr;
}

ostream& operator<<(ostream &ostr, const TSet &s) // вывод
{
	for (int i = 0; i < s.MaxPower; i++) {
		if (s.IsMember(i)) ostr << i << " ";
	}
	return ostr;
}
