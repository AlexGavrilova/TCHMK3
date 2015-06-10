#include "class.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fstream>
#include <vector>
using std::ifstream;
using std::ofstream;

#define DIV_BY_ZERO 1

LongNum::LongNum()							
{
	this->size = 1;
	this->sign = 0;
	this->index = new unsigned char[1];
	this->index[0] = 0;
}

LongNum::LongNum(const char* string)		
{
	int strLen = strlen(string);
	int strSign = 0;
	if (string[0] == '-')
	{
		strSign = 1;
		strLen--;
	}

	LongNum Result; 	

	LongNum pow10 = 1; 
	for (int i = strLen + strSign - 1; i >= strSign; i--)		
	{
		int rI = string[i] - '0';
		Result = Result + pow10 * rI;
		pow10 = pow10 * 10;
	}
	Result.sign = strSign;		

	this->size = 0;
	*this = Result; 			
}

LongNum::LongNum(const LongNum &right)		
{
	this->size = right.size;
	this->index = new unsigned char[this->size];
	this->sign = right.sign;
	memcpy(index, right.index, this->size * sizeof(unsigned char));
	return;
}

LongNum::LongNum(int value)					
{
	this->index = new unsigned char[11]();
	this->size = 0;
	this->sign = 0;
	if (value < 0)
	{
		this->sign = 1;
		value = -value;
	}
	do
	{
		this->size++;
		this->index[this->size - 1] = value % 256;
		value = value / 256;
	} while (value > 0);

	this->DelZero();
}

LongNum::~LongNum()							
{
	delete[] index;
}

char* LongNum::TakeStr()					
{
	LongNum temp = *this;
	temp.sign = 0;

	std::vector<char> tmpStr; 


	while (temp != (int)0)
	{
		LongNum remainder;
		temp = Divide(temp, 10, remainder); 
		char ost = remainder[0] + '0'; 	   
		tmpStr.push_back(ost);
	}

	if (this->sign)							
		tmpStr.push_back('-');

	int strSize = tmpStr.size();		
	char* string = new char[strSize + 1]();

	for (int i = 0; i < tmpStr.size(); i++)
	{
		string[strSize - i - 1] = tmpStr[i];
	}

	return string;
}


bool LongNum::OutFile(const char* filename)		
{
	ifstream TextF(filename);
	if (TextF.fail())
		return false;


	TextF.seekg(0, std::ios::end);
	int File_size = TextF.tellg();
	TextF.seekg(0, std::ios::beg);

	char* string = new char[File_size + 1]();
	TextF >> string;
	TextF.close();

	*this = LongNum(string);
	delete[] string;
	return true;
}

bool LongNum::InFile(const char* filename)			
{
	ofstream Res_file(filename);
	if (Res_file.fail())
		return false;

	char* string = this->TakeStr();
	Res_file << string;
	delete[] string;
	Res_file.close();

	return true;
}

bool LongNum::InBinFile(const char* filename)	
{
	ofstream outBinFile(filename, std::ios::binary);
	if (outBinFile.fail())
		return false;

	outBinFile.write((char*) this->index, this->size);

	outBinFile.close();
	return true;
}

bool LongNum::OutBinFile(const char* filename)	
{
	ifstream inBinFile(filename, std::ios::binary);
	if (inBinFile.fail())
		return false;


	inBinFile.seekg(0, std::ios::end);
	int File_size = inBinFile.tellg();
	inBinFile.seekg(0, std::ios::beg);

	delete[] this->index;
	this->index = new unsigned char[File_size];
	this->size = File_size;
	this->sign = 0;

	//Ñ÷èòûâàåì ñîäåðæèìîå áèíàðíîãî ôàéëà.
	inBinFile.read((char*)this->index, File_size);
	inBinFile.close();

	return true;
}


void LongNum::Size_Set(int newSize)		
{
	if (this->size)
		delete[] this->index;
	this->size = newSize;
	this->sign = 0;
	this->index = new unsigned char[this->size]();
}

void LongNum::DelZero()			
{
	while ((size - 1) && index && index[size - 1] == 0)
		this->size--;

	if (this->size == 1 && index[0] == 0)
		this->sign = 0;
}

int LongNum::Compare(const LongNum& B)	
{
	int thisSign = 1;
	if (this->sign == 1)
		thisSign = -1;

	if (this->sign != B.sign)
		return thisSign;

	if (this->size > B.size)
		return thisSign;

	if (this->size < B.size)
		return -thisSign;

	int i = this->size - 1;

	while (this->index[i] == B[i] && i > 0)
	{
		i--;
	}
	return ((int) this->index[i] - (int)B[i]) * thisSign;
}

void LongNum::Shift(int s)				
{
	unsigned char* newindex = new unsigned char[this->size + s]();
	for (int i = 0; i < this->size; i++)
	{
		newindex[i + s] = this->index[i];
	}

	delete[] this->index;
	this->index = newindex;
	this->size += s;
	this->DelZero();
}


LongNum LongNum::AddSub(const LongNum& left, const LongNum& right) const				
{
	LongNum A = left, B = right; 	
	A.sign = 0;
	B.sign = 0;
	if (A > B)
	{
		A.sign = left.sign;
		B.sign = right.sign;
	}
	else
	{
		A = right;
		B = left;
	}

	if (A.sign == B.sign)		
	{
		LongNum Result;
		Result.Size_Set(A.size + 1);

		int carry = 0;

		for (int i = 0; i < A.size; i++)
		{
			int tmp = A[i] + carry;
			if (i < B.size)
				tmp += B[i];

			Result[i] = tmp % 256;
			carry = tmp / 256;
		}

		Result[A.size] = carry;
		Result.sign = A.sign;
		Result.DelZero();
		return Result;
	}
	else						
	{
		LongNum Result;
		Result.Size_Set(A.size);

		int carry = 0;
		for (int i = 0; i < A.size; i++)
		{
			int tmp = A[i] - carry;
			if (i < B.size)
				tmp -= B[i];

			carry = 0;
			if (tmp < 0)
			{
				carry = 1;
				tmp += 256;
			}
			Result[i] = tmp;
		}

		Result.sign = A.sign;
		Result.DelZero();
		return Result;
	}
}

LongNum LongNum::Multiply(const LongNum A, const LongNum B) const						
{
	LongNum Result;
	Result.Size_Set(A.size + B.size);
	int carry = 0;
	for (int i = 0; i < B.size; i++)
	{
		carry = 0;
		for (int j = 0; j < A.size; j++)
		{
			int tmp = (int)B[i] * (int)A[j] + (int)carry + (int)Result[i + j];
			carry = tmp / 256;
			Result[i + j] = tmp % 256;
		}
		Result[i + A.size] = carry;
	}

	Result.sign = (A.sign != B.sign);
	Result.DelZero();
	return Result;
}

LongNum LongNum::Divide(const LongNum& A, const LongNum& B, LongNum &remainder) const	
{
	remainder = A;
	remainder.sign = 0;

	LongNum divider = B;
	divider.sign = 0;

	if (divider == LongNum((int)0))
	{
		throw DIV_BY_ZERO;
	}

	if (remainder < divider)
	{
		remainder = A;
		return LongNum((int)0);
	}

	LongNum Result;
	Result.Size_Set(A.size - B.size + 1);

	for (int i = A.size - B.size + 1; i; i--)
	{
		int Max = 256;
		int Min = 0;
		int Mid = Max;

		while (Max - Min > 1)
		{
			Mid = (Max + Min) / 2;

			LongNum tmp = divider * Mid;
			tmp.Shift(i - 1);	
			if (tmp > remainder)
				Max = Mid;
			else
				Min = Mid;
		}
		LongNum tmp = divider * Min;
		tmp.Shift(i - 1); 			
		remainder = remainder - tmp;
		Result[i - 1] = Min;
	}

	Result.sign = (A.sign != B.sign);
	remainder.sign = (A.sign != B.sign);
	remainder.DelZero();
	Result.DelZero();

	return Result;
}

LongNum Pow(const LongNum& A, const LongNum& B, LongNum& Mod)							
{
	if (Mod <= (int)0)
		return A ^ B;

	LongNum base = A % Mod;
	LongNum Result = 1;

	for (LongNum i = B; i > (int)0; i = i - 1)
		Result = (Result * base) % Mod;

	return Result;
}


unsigned char & LongNum::operator[](int i)
{
	if (i < 0)
		return this->index[this->size + i];
	return this->index[i];
}

unsigned char LongNum::operator[](int i) const
{
	if (i < 0)
		return this->index[this->size + i];
	return this->index[i];
}

LongNum& LongNum::operator=(const LongNum& rhv)
{
	if (this->size)
		delete[] this->index;

	this->size = rhv.size;
	this->index = new unsigned char[size];
	this->sign = rhv.sign;
	memcpy(index, rhv.index, size);
	return *this;
}
//Óíàðíûé ìèíóñ.
{
	LongNum Result = *this;
	Result.sign = !Result.sign;
	return Result;
}

LongNum LongNum::operator^(const LongNum& right) const	
{
	LongNum Result = 1;
	LongNum base = *this;
	for (LongNum i = right; i > (int)0; i = i - 1)
		Result = Result * base;
	return Result;
}

LongNum LongNum::operator+(const LongNum& right) const
{
	return AddSub(*this, right);
}

LongNum LongNum::operator-(const LongNum& right) const
{
	return *this + (-right);
}

LongNum LongNum::operator*(const LongNum& right) const
{
	return Multiply(*this, right);
}

LongNum LongNum::operator/(const LongNum& right) const
{
	LongNum rem;
	return Divide(*this, right, rem);
}

LongNum LongNum::operator%(const LongNum& right) const
{
	LongNum rem;
	Divide(*this, right, rem);
	return rem;
}


bool LongNum::operator>(const LongNum& B)
{
	return this->Compare(B) > 0;
}

bool LongNum::operator>=(const LongNum& B)
{
	return this->Compare(B) >= 0;
}

bool LongNum::operator<(const LongNum& B)
{
	return this->Compare(B) < 0;
}

bool LongNum::operator<=(const LongNum& B)
{
	return this->Compare(B) <= 0;
}

bool LongNum::operator==(const LongNum& B)
{
	return this->Compare(B) == 0;
}

bool LongNum::operator!=(const LongNum& B)
{
	return this->Compare(B) != 0;
}



//Python

LongNum LongNum::operator+(const int& right) const
{
	return AddSub(*this, (LongNum)right);
}

LongNum LongNum::operator-(const int& right) const
{
	return *this + (LongNum)(-right);
}

LongNum LongNum::operator*(const int& right) const
{
	return Multiply(*this, (LongNum)right);
}

LongNum LongNum::operator/(const int& right) const
{
	LongNum rem;
	return Divide(*this, (LongNum)right, rem);
}

LongNum LongNum::operator%(const int& right) const
{
	LongNum rem;
	Divide(*this, (LongNum)right, rem);
	return rem;
}


bool LongNum::operator>(const int& B)
{
	return this->Compare((LongNum)B) > 0;
}

bool LongNum::operator>=(const int& B)
{
	return this->Compare((LongNum)B) >= 0;
}

bool LongNum::operator<(const int& B)
{
	return this->Compare((LongNum)B) < 0;
}

bool LongNum::operator<=(const int& B)
{
	return this->Compare((LongNum)B) <= 0;
}

bool LongNum::operator==(const int& B)
{
	return this->Compare((LongNum)B) == 0;
}

bool LongNum::operator!=(const int& B)
{
	return this->Compare((LongNum)B) != 0;
}

char* LongNum::__repr__()
{
	return TakeStr();
}

char* LongNum::__str__()
{
	return TakeStr();
}
