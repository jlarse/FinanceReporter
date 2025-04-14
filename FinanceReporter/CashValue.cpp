// Date.cpp
// Justin Larsen
//
// Implementation file for CashValue class(CashValue.h)
// Visual Studio 2022

#include "CashValue.h"

namespace cashvaluelarsen
{
	int charToInt(const char c)
	{
		return static_cast<int>(c) - static_cast<int>('0');
	}

	CashValue::CashValue() : dollars(0), cents(0)
	{

	}

	CashValue::CashValue(const long dollars, const short cents) //test this function
	{
		short centValue = cents;
		this->dollars = dollars + dollarValue(centValue);
		this->cents = centValue;


		if (this->dollars > 0 && this->cents < 0)
		{
			this->dollars -= 1;
			this->cents = centValue + 100;
		}
		else if (this->dollars < 0 && this->cents > 0)
		{
			this->dollars += 1;
			this->cents = centValue - 100;
		}
		
		if((this-> dollars <= 0 && this->cents <= 0) && (this->dollars != 0 || this->cents != 0) && !(this->dollars == 0 && this->cents == 0))
		{
			negative = true;
			this->dollars *= -1;
			this->cents *= -1;
		}
	}

	CashValue::CashValue(const CashValue& other)
	{
		dollars = other.dollars;
		cents = other.cents;
		negative = other.negative;
	}

	short CashValue::dollarValue(short& centValue)
	{	
		short temp = centValue;
		centValue %= 100;
		return temp / 100;
	}

	void CashValue::operator =(const CashValue& right)
	{
		this->dollars = right.dollars;
		this->cents = right.cents;
		this->negative = right.negative;
	}

	ostream& operator <<(ostream& out, const CashValue& cashValue)
	{
		if (cashValue.negative)
			out << "-";
		out << "$";
		out << cashValue.dollars << ".";
		if (cashValue.cents < 10)
			out << "0";

		out << cashValue.cents;

		return out;
	}

	istream& operator >>(istream& in, CashValue& cashValue)
	{
		char inChar = in.get();
		bool isNeg = false;
		long dollars = 0;
		short cents = 0;

		//cout << "In Char: " << inChar << endl;
		while(inChar == ' ')
		{
			inChar = in.get();
		}

		if (inChar == '-')
		{
			isNeg = true;
			inChar = in.get();
		}

		//cout << "inchar " << inChar << endl;
		if (inChar == '$')
		{
			inChar = in.get();
			if (isdigit(inChar))
			{
				if (isNeg)
					dollars -= charToInt(inChar);
				else
					dollars += charToInt(inChar);
				
				inChar = in.get();
				while (isdigit(inChar))
				{
					if (isNeg)
						dollars = dollars * 10 - charToInt(inChar);
					else
						dollars = dollars * 10 + charToInt(inChar);
					inChar = in.get();
				}

				if (inChar == '.')
				{
					inChar = in.get();
					if (isdigit(inChar))
					{
						if (isNeg)
							cents = -10 * charToInt(inChar);
						else
							cents = 10 * charToInt(inChar);

						inChar = in.get();

						if (isdigit(inChar))
						{
							if (isNeg)
								cents -= charToInt(inChar);
							else
								cents += charToInt(inChar);
						}
					}
				}
			}
		}
		//cout << "end" << endl;
		cashValue = CashValue(dollars, cents);
		return in;
	}

	CashValue CashValue::operator +(const CashValue& right) const
	{
		long tempDLeft = dollars, tempDRight = right.dollars;
		short tempCLeft = cents, tempCRight = right.cents;

		if (negative)
		{
			tempDLeft *= -1;
			tempCLeft *= -1;
		}

		if (right.negative)
		{
			tempDRight *= -1;
			tempCRight *= -1;
		}
		CashValue temp(tempDLeft + tempDRight, tempCLeft + tempCRight);

		return temp;
	}

	CashValue& CashValue::operator +=(const CashValue& right)
	{
		long tempDLeft = dollars, tempDRight = right.dollars;
		short tempCLeft = cents, tempCRight = right.cents;

		if (negative)
		{
			tempDLeft *= -1;
			tempCLeft *= -1;
		}

		if (right.negative)
		{
			tempDRight *= -1;
			tempCRight *= -1;
		}
		CashValue temp(tempDLeft + tempDRight, tempCLeft + tempCRight);

		*this = temp;
		return *this;
	}

	bool CashValue::isNull() const
	{
		return dollars == 0 && cents == 0;
	}

	bool CashValue::isNegative() const
	{
		return negative;
	}
}