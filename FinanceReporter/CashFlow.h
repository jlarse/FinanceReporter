// CashFlow.h
// Justin Larsen
// Description: Interface for a cash flow class, representing an entity of money flowing in or out.
// Visual Studio 2022

#ifndef CASHFLOW_H
#define CASHFLOW_H

#include <string>
#include <iostream>
#include "Date.h"
#include "CashValue.h"

using namespace cashvaluelarsen;
using namespace datelarsen;
using namespace std;

namespace cashflowlarsen
{


	class CashFlow
	{
	public:
		CashFlow();
		//default or null cashflow type
		CashFlow(const Date& date, const CashValue& amount, const char type, const string& description);
		//constructs a cash flow with all values

		CashValue getAmount() const;
		//returns cash flow's amount
		Date getDate() const;
		//returns cash flow's date
		string getTypeString() const;
		//returns string of cash flows type
		string getDescription() const;
		//returns description of cash flow

		void setAmount(const CashValue& amount);
		//sets amount of cash flow
		void setDate(const Date& date);
		//sets date of cash flow
		void setType(const char type);
		//sets type of cash flow.
		void setDescription(const string& description);
		//sets description of cash flow


		string getOutFlowTypes();
		//returns a string of possible out flow types, the character to store each type is in single quotes.
		string getInFlowTypes();
		//returns a string of possible in flow types, the character to store each type is in single quotes.
		
		bool checkTypeExists(const char type);
		//returns true of type of cash flow exists for current cash flow, false otherwise.

		friend istream& operator >>(istream& in, CashFlow& cashflow);
		friend ostream& operator <<(ostream& out, const CashFlow& cashflow);

	private:
		Date date;
		//double amount;
		CashValue amount;
		char type;
		string description;

		char assignType(const char type);

	};

}

#endif
