// CashValue.h
// Justin Larsen
// Description: Interface for a cash for a CashValue object which represents an amount of US currency in dollars
//				and cents. 
// 
// Visual Studio 2022

#pragma once

#include <iostream>
using namespace std;

namespace cashvaluelarsen
{ 
	class CashValue
	{
	public:
		CashValue();
		//default constructor, 0 dollars, 0 cents

		CashValue(const long dollars, const short cents);
		//constructor for exact values of dollars and cents.
		//If dollars is negative and cents positie they will be counted against each other
		// EX.(dollars= -1, cents= 99 : cash value will be -$0.01)
		//The opposite is true for cents.

		CashValue(const CashValue& other);
		//copy constructor

		CashValue operator +(const CashValue& right) const;
		CashValue& operator +=(const CashValue& right);

		void operator =(const CashValue& right);

		friend istream& operator >>(istream& in, CashValue& cashValue);
		friend ostream& operator <<(ostream& out, const CashValue& cashValue);

		bool isNull() const;
		bool isNegative() const;

	private:
		long dollars;
		short cents;
		bool negative = false;

		short dollarValue(short& centValue);
		// takes a number of cents and returns amount of dollars from those cents and changes centValue 
		// to remaining cents

		static int charToInt(const char c);
		//returns integer value of v
	};
}

