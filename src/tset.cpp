//tset
// ННГУ, ВМК, Курс "Методы программирования-2", С++, ООП
//
// tset.cpp - Copyright (c) Гергель В.П. 04.10.2001
//   Переработано для Microsoft Visual Studio 2008 Сысоевым А.В. (19.04.2015)
//
// Множество - реализация через битовые поля

#include "tset.h"

// Fake variables used as placeholders in tests
static const int FAKE_INT = -1;
static TBitField FAKE_BITFIELD(1);
static TSet FAKE_SET(1);

TSet::TSet(int mp) : BitField(mp), MaxPower(mp){}


// конструктор копирования
TSet::TSet(const TSet &s) : BitField(s.BitField), MaxPower(s.GetMaxPower()){}

// конструктор преобразования типа
TSet::TSet(const TBitField &bf) : BitField(bf), MaxPower(bf.GetLength()){}

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
    if (this != &s) {
        BitField = s.BitField;
        MaxPower = s.MaxPower;
    }
    return *this;
}

int TSet::operator==(const TSet &s) const // сравнение
{
    return BitField == s.BitField;
}// пропускает некоторые положительные случаи, при разных BitLen?

int TSet::operator!=(const TSet &s) const // сравнение
{
    return !(*this == s);
}

TSet TSet::operator+(const TSet &s) // объединение
{
    TSet Result(BitField | s.BitField);
    return Result;
}

TSet TSet::operator+(const int Elem) // объединение с элементом
{
    TSet Result(*this);
    Result.BitField.SetBit(Elem);
    return Result;
}

TSet TSet::operator-(const int Elem) // разность с элементом
{
    TSet Result(*this);
    Result.BitField.ClrBit(Elem);
    return Result;
}

TSet TSet::operator*(const TSet &s) // пересечение
{
    TSet Result(BitField & s.BitField);
    return Result;
}

TSet TSet::operator~(void) // дополнение
{
    TSet Result(~BitField);
    return Result;
}

// перегрузка ввода/вывода

istream &operator>>(istream &istr, TSet &s) // ввод
{
    //int n;
    //istr >> n;
    //for (int i = 0; i < s.MaxPower; i++)
       // s.BitField.ClrBit(i);
    //for (int i = 0; i < n; i++) {
        //int x;
        //istr >> x;
       // s.BitField.SetBit(x);
    //}
    istr >> s.BitField;
    return istr;
}

ostream& operator<<(ostream &ostr, const TSet &s) // вывод
{
    //int n = 0;
    //for (int i = 0; i < s.MaxPower; i++)
       // if (s.IsMember(i))
            //n++;
    //ostr << n << endl;
    //for (int i = 0; i < s.MaxPower; i++)
        //if (s.IsMember(i))
            //ostr << i << " ";
    ostr << s.BitField;
    return ostr;
}
