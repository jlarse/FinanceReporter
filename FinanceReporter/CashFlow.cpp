// CashFlow.cpp
// Justin Larsen
//
// Implementation file forl CashFlow class (CashFlow.h)
// Visual Studio 2022

#include <cmath>
#include "CashFlow.h"

namespace cashflowlarsen
{

	CashFlow::CashFlow() : type('X'), description("NULL")
	// default or null Cash flow type
	{
		Date nonValue;
		date = nonValue;
		CashValue zeroValue;
		amount = zeroValue;
	}

	CashFlow::CashFlow(const Date& date, const CashValue& amount, const char type, const string& description)
	{
		if (!amount.isNull())
		{
			
			this->amount = amount;
			this->date = date;
			this->type = assignType(type);
			this->description = description;
		}
		else
		{
			cout << "Cash flow amount may not be 0. Cash flow set to default\n";
			
			this->amount = amount;
			Date temp;
			this->date = date;
			this->type = 'X';
			this->description = "NULL";	
		}
	}

	CashValue CashFlow::getAmount() const
	{
		return amount;
	}

	Date CashFlow::getDate() const
	{
		return date;
	}

	void CashFlow::setAmount(const CashValue& amount)
	{
		this->amount = amount;
	}	

	void CashFlow::setDate(const Date& date)
	{
		this->date = date;
	}

	void CashFlow::setType(const char type)
	{
		this->type = assignType(type);
	}

	void CashFlow::setDescription(const string& description)
	{
		this->description = description;
	}

	char CashFlow::assignType(const char type)
	{
		if (amount.isNegative())
		{
			switch (type)
			{
			case 'E':  //Expense
			case 'e':
				return 'E';
			case 'L':  //Luxurie
			case 'l':
				return 'L';
			default:
				return NULL;
			}
		}
		else
		{
			switch (type)
			{
			case 'E':  //Earnings
			case 'e':
				return 'E';
			case 'G':  //Gifts
			case 'g':
				return 'G';
			default:
				return NULL;
			}
		}
	}

	string CashFlow::getTypeString() const
	{
		if (amount.isNegative())
		{
			switch (type)
			{
			case 'E':
				return "Expense";
			case 'L':
				return "Luxurie";
			default:
				return "No Type";
			}
		}
		else
		{
			switch (type)
			{
			case 'E':
				return "Earning";
			case 'G':
				return "Gift";
			default:
				return "No Type";
			}
		}
	}
	string CashFlow::getDescription() const
	{
		return description;
	}

	string CashFlow::getOutFlowTypes()
	{
		return "'E'(Expense), 'L'(Luxurie)";
	}

	string CashFlow::getInFlowTypes()
	{
		return "'E'(Earning), 'G' (Gift)";
	}

	bool CashFlow::checkTypeExists(const char type)
	{
		char test = assignType(type);
		if (test == NULL)
			return false;
		else
			return true;
		
	}

	istream& operator >>(istream& in, CashFlow& flow)
	{
		bool isValid = true;
		char test, type;
		CashValue amount;
		Date date;
		string description;

		test = in.peek();

		in >> date;

		test = in.peek();
		while (test == ' ')
		{
			test = in.get();
			test = in.peek();
		}

		in >> amount;

		if(amount.isNull())
			isValid = false;

		test = in.peek();
		while (test == ' ')
		{
			test = in.get();
			test = in.peek();
		}
		
		in >> type;

		test = in.peek();
		while (test == ' ')
		{
			test = in.get();
			test = in.peek();
		}

		test = in.peek();
		while (test != '\n')
		{
			test = in.get();
			description += test;
			test = in.peek();
		}


		if (isValid)
			flow = CashFlow(date, amount, type, description);
		else
			cout << "Invalid value used for CashFlow object.\n";
		
		return in;
	}

	ostream& operator <<(ostream& out, const CashFlow& cashflow)
	{
		CashValue value = cashflow.amount;
		out << cashflow.date << " " << value << " " << cashflow.type << " " << cashflow.description;

		return out;
	}
}
