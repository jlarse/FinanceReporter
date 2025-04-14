// Date.cpp
// Justin Larsen
//
// Implementation file for Date class (Date.h)
// Visual Studio 2022

#include <cmath>
#include <cctype>
#include "Date.h"

namespace datelarsen
{

	Date::Date(): month(0), day(0), year(0)
	//Default value for date is a null date where all value set to 0
	{
		
	}

	Date::Date(const char* day): month(0), day(0), year(0)
	{
		if (day == "Today" || day == "today")
		{
			time_t currentTime = time(nullptr);
			tm localTime;

			if (localtime_s(&localTime, &currentTime) == 0)
			{
				this->day = localTime.tm_mday;
				this->month = localTime.tm_mon + 1;
				this->year = localTime.tm_year + 1900;
			}
		}
	}

	Date::Date(const short month, const short day, const short year)
	{
		if (validateDate(month, day, year))
		{
			this->month = month;
			this->day = day;
			this->year = year;
		}
		else
		{
			cout << "[From Date constructor] Improper value used for Date object. Date set to null date\n";
			this->month = 0;
			this->day = 0;
			this->year = 0;
		}
	}

	bool Date::validateDate(const short month, const short day, const short year)
	{
		if (day <= 0 || day > 31 || month <= 0 || month > 12) //check baisic month and day requirements
			return false;
		else if (month == 2 && ((year % 400 == 0) || (year % 4 == 0 && year % 100 != 0)))// check bounds for day on leapyear in febuary
		{
			if (day > 29)
				return false;
			else
				return true;
		}
		else
		{
			switch (month)              //check specific day requirements based on month
			{
			case 1:
			case 3:
			case 5:
			case 7:
			case 8:
			case 10:
			case 12:
				if (day > 31)
					return false;
				break;

			case 4:
			case 6:
			case 9:
			case 11:
				if (day > 30)
					return false;
				break;
			case 2:
				if (day > 28)
					return false;
				break;
			}
		}
		return true;
	}

	int charToInt(const char c)
	{
		return static_cast<int>(c) - static_cast<int>('0');
	}

	int Date::dayOfWeek() const
	{
		if (year == 0 && month == 0 && day == 0)
			return -1;
		else
		{
			int lastTwo, yearValue, centuryValue, wholeYearValue, monthValue;

			lastTwo = year - ((year / 100) * 100);
			yearValue = lastTwo / 4 + lastTwo;

			centuryValue = (3 - ((year / 100) % 4)) * 2;

			wholeYearValue = yearValue + centuryValue;

			switch (month)
			{
				case 1:
				{
					if (this->isLeapYear())
						monthValue = 6;
					else
						monthValue = 0;
					break;
				}
				case 2:
				{
					if (this->isLeapYear())
						monthValue = 2;
					else
						monthValue = 3;
					break;
				}
				case 3:
					monthValue = 3;
					break;
				case 4:
					monthValue = 6;
					break;
				case 5:
					monthValue = 1;
					break;
				case 6:
					monthValue = 4;
					break;
				case 7:
					monthValue = 6;
					break;
				case 8:
					monthValue = 2;
					break;
				case 9:
					monthValue = 5;
					break;
				case 10:
					monthValue = 0;
					break;
				case 11:
					monthValue = 3;
					break;
				case 12:
					monthValue = 5;
					break;
				default:
				{
					cout << "\n Invalid month used in calculation. \n";
					return -1;
				}

			}

			return (day + wholeYearValue + monthValue) % 7;
		}
	}

	short Date::getDay() const
	{
		return day;
	}

	short Date::getMonth() const
	{
		return month;
	}

	short Date::getYear() const
	{
		return year;
	}

	string Date::getMonthName()
	{
		switch (month)
		{
		case 1:
			return "January";
			break;
		case 2:
			return "Febuary";
			break;
		case 3:
			return "March";
			break;
		case 4:
			return "April";
			break;
		case 5:
			return "May";
			break;
		case 6:
			return "June";
			break;
		case 7:
			return "July";
			break;
		case 8:
			return "August";
			break;
		case 9:
			return "September";
			break;
		case 10:
			return "October";
			break;
		case 11:
			return "November";
			break;
		case 12:
			return "December";
			break;
		default:
			return "Null";
		}
	}

	string Date::getDayOfWeek() const
	{
		switch(this->dayOfWeek())
		{
			case 0:
				return "Sunday";
				break;
			case 1:
				return "Monday";
				break;
			case 2:
				return "Tuesday";
				break;
			case 3:
				return "Wednesday";
				break;
			case 4:
				return "Thursday";
				break;
			case 5:
				return "Friday";
				break;
			case 6:
				return "Saturday";
				break;
			default:
				return "Invalid day of week number used";

		};
	}

	void Date::setDay(const short newDay)
	{
		if (validateDate(month, newDay, year))
		{
			day = newDay;
		}
		else
			cout << "Improper day used when trying to change the date. Date not changed.\n";
	}

	void Date::setDayToLastOfMonth()
	{
		switch (month)
		{
		case 1:
		case 3:
		case 5:
		case 7:
		case 8:
		case 10:
		case 12:
			setDay(31);
			break;

		case 2:
			if (isLeapYear())
				setDay(29);
			else
				setDay(28);
			break;

		case 4:
		case 6:
		case 9:
		case 11:
			setDay(30);
			break;
		}
	}

	bool Date::isLeapYear() const
	{
		if ((year % 400 == 0) || (year % 4 == 0 && year % 100 != 0))
			return true;
		else
			return false;
	}

	bool Date::isLeapYear(const short year) const
	{
		if ((year % 400 == 0) || (year % 4 == 0 && year % 100 != 0))
			return true;
		else
			return false;
	}

	bool Date::isNull() const
	{
		return month == 0 && day == 0 && year == 0;
	}

	ostream& operator <<(ostream& out, const Date& date)
	{
		return out << date.getMonth() << "/" << date.getDay() << "/" << date.getYear();
	}

	istream& operator >>(istream& in, Date& date)
	{
		char numOne, numTwo, test;
		short day, month, year = 0;
		bool isValid = true;

		test = in.peek();

		while (test == ' ' ) // clears whitespace before an entered date
		{
			test = in.get();
			test = in.peek(); 
		}
		
		numOne = in.get();

		if (numOne == '\n')
			isValid = false;
		
		if (isValid)
		{
			numTwo = in.get();
			if (numTwo == '\n')
				isValid == false;
			
		}

		if (isdigit(numOne) && numTwo == '/')  //test for valid month entry
		{
			month = charToInt(numOne);
			test = numTwo;
		}
		else if (isdigit(numOne) && isdigit(numTwo))
		{
			month = charToInt(numOne) * 10 + charToInt(numTwo);
			test = in.get();
		}
		else
			isValid = false;

		if (test == '/') // make sure first slash is there
		{
			
			numOne = in.get();
			if (numOne == '\n')
				isValid = false;

			if (isValid)
			{
				numTwo = in.get();
				if (numTwo == '\n')
					isValid == false;
			}


			if (isdigit(numOne) && numTwo == '/') //test for valid day entry
			{
				day = charToInt(numOne);
				test = numTwo;
			}
			else if (isdigit(numOne) && isdigit(numTwo))
			{
				day = charToInt(numOne) * 10 + charToInt(numTwo);
				in >> test;
			}
			else
				isValid = false;

			if (test == '/' && isValid) //make sure second slash is there and input so far is valid
			{
				bool first = true;
				test = in.peek();
				
				while(isdigit(test))  //create year while next char is a digit
				{
					numOne = in.get();

					if (first)
					{
						year += charToInt(numOne);
						first = false;
					}
					else
						year = year * 10 + charToInt(numOne);
					
					test = in.peek();
				}

				if (year == 0)
					isValid = false;
			}
			else
				isValid = false;
		}
		else
			isValid = false;


		if (isValid)
		{
			date = Date(month, day, year);
		}
		else
		{
			test = in.peek();

			while (test != ' ' && test != '\n') // clears all other errenous input characters until white space
			{
				test = in.get();
				test = in.peek();
			}

			cout << "[From overloaded >>] Improper format used for Date object. Date set to null date.\n";
			date = Date();
		}

		return in;
	}

	bool operator <(const Date& left, const Date& right)
	{
		if (left.year < right.year)
			return true;
		else if (left.year == right.year)
		{
			if (left.month < right.month)
				return true;
			else if (left.month == right.month)
			{
				if (left.day < right.day)
					return true;
				else
					return false;
			}
			else
				return false;
		}
		else
			return false;
	}

	bool operator >(const Date& left, const Date& right)
	{
		if (left.year > right.year)
			return true;
		else if (left.year == right.year)
		{
			if (left.month > right.month)
				return true;
			else if (left.month == right.month)
			{
				if (left.day > right.day)
					return true;
				else
					return false;
			}
			else
				return false;
		}
		else
			return false;	
	}

	bool operator <=(const Date& left, const Date& right)
	{
		if (left.year < right.year)
			return true;
		else if (left.year == right.year)
		{
			if (left.month < right.month)
				return true;
			else if (left.month == right.month)
			{
				if (left.day <= right.day)
					return true;
				else
					return false;
			}
			else
				return false;
		}
		else
			return false;
	}

	bool operator >=(const Date& left, const Date& right)
	{
		if (left.year > right.year)
			return true;
		else if (left.year == right.year)
		{
			if (left.month > right.month)
				return true;
			else if (left.month == right.month)
			{
				if (left.day >= right.day)
					return true;
				else
					return false;
			}
			else
				return false;
		}
		else
			return false;
	}

	bool operator ==(const Date& left, const Date& right)
	{
		return left.year == right.year && left.month == right.month && left.day == right.day;
	}

	void Date::operator =(const Date& date)
	{
		this->month = date.month;
		this->day = date.day;
		this->year = date.year;
	}

	Date Date::operator+(const char amount)
	{
		short tempM = 0, tempD = 0, tempY = 0;

		if (day == 0 && month == 0 && year == 0)
		{
			cout << "Cannot perform operatoins on a null date.\n";
		}
		else if (amount == 'd' || amount == 'D')
		{
			//for adding a day to a date, if day is on last day of the month the day will roll over to first of next month
			//months with 31 days 1,3,5,7,8,10,12
			//febuary has 29 days on leap year, and 28 days on other years
			//months with 30 days 4, 6, 9, 11

			switch (month)              
			{
			case 1:                       //months with 31 days
			case 3:
			case 5:
			case 7:
			case 8:
			case 10:
				if (day == 31)
				{
					tempD = 1;
					tempM = month + 1;
				}
				else
				{
					tempD = day + 1;
					tempM = month;
				}
				tempY = year;
				break;

			case 4:                //months with 30 days
			case 6:
			case 9:
			case 11:
				if (day == 30)
				{
					tempD = 1;
					tempM = month + 1;
				}
				else
				{
					tempD = day + 1;
					tempM = month;
				}
				tempY = year;
				break;

			case 2:                     //febuary 29 days on leap year, 28 on other years
				if (isLeapYear())
				{
					if (day == 29)
					{
						tempD = 1;
						tempM = 3;
					}
					else
					{
						tempD = day + 1;
						tempM = 2;
					}
					tempY = year;
				}
				else
				{
					if (day == 28)
					{
						tempD = 1;
						tempM = 3;
					}
					else
					{
						tempD = day + 1;
						tempM = 2;
					}
					tempY = year;
				}
				break;

			case 12:            //december for rolling over into the next year
				if (day == 31)
				{
					tempD = 1;
					tempM = 1;
					tempY = year + 1;
				}
				else
				{
					tempD = day + 1;
					tempM = 12;
					tempY = year;
				}
				break;
			default:
				cout << "Error adding day, month of date used is not a real month\n";
			}

		}
		else if (amount == 'm' || amount == 'M')
		{
			//Adds a month without exeeding the last day of the next month.
			//months with 31 days 1,3,5,7,8,10,12
			//febuary has 29 days on leap year, and 28 days on other years
			//months with 30 days 4, 6, 9, 11
			switch (month)             
			{
			case 1:             //for changing to febuary
				if (day >= 28)  
				{
					if (day >= 29 && isLeapYear())
					{
						tempD = 29;
					}
					else
					{
						tempD = 28;
					}
				}
				else
				{
					tempD = day;
				}

				tempM = 2;
				tempY = year;
				break;
			case 3:      //for 31 day months whose next month has 30 days
			case 5:
			case 8:
			case 10:
				if (day > 30)
					tempD = 30;
				else
					tempD = day;
				tempM = month + 1;
				tempY = year;
				break;   
			
			case 2:  //for months whose next month has an equal or less than amount of days
			case 4:
			case 6:
			case 7:
			case 9:
			case 11:
				tempD = day;
				tempM = month + 1;
				tempY = year;
				break;

			case 12:            //for december making it a new year
				tempD = day;
				tempM = 1;
				tempY = year + 1;
				break;
			}
		}
		else if (amount == 'y' || amount == 'Y')
		{
			//if year is a leap year and is febuary and day is 29th donwsize the day to a non leapyear day for febuary
			if (isLeapYear() && month == 2 && day == 29)
			{
				tempD = 28;
				tempM = month;
				tempY = year + 1;
			}
			else
			{
				tempD = day;
				tempM = month;
				tempY = year + 1;
			}
		}
		else
		{
			cout << "Improper value used in addition to date. No value added.\n";
		}

		return Date(tempM, tempD, tempY);
	}

	Date Date::operator-(const char amount)
	{
		short tempM = 0, tempD = 0, tempY = 0;

		if (day == 0 && month == 0 && year == 0)
		{
			cout << "Cannot perform operatoins on a null date.\n";
		}
		else if (amount == 'd' || amount == 'D')
		{
			//for subtracting a day from the date, if day is on first day of the month the day will roll back to last of the previous month month
			//months with 31 days 1,3,5,7,8,10,12
			//febuary has 29 days on leap year, and 28 days on other years
			//months with 30 days 4, 6, 9, 11

			switch (month)
			{
			case 2:                       //months after those with 31 days
			case 4:
			case 6:
			case 8:
			case 9:
			case 11:
				if (day == 1)
				{
					tempD = 31;
					tempM = month - 1;
				}
				else
				{
					tempD = day - 1;
					tempM = month;
				}
				tempY = year;
				break;

			case 5:                //months after those with 30 days
			case 7:
			case 10:
			case 12:
				if (day == 1)
				{
					tempD = 30;
					tempM = month - 1;
				}
				else
				{
					tempD = day - 1;
					tempM = month;
				}
				tempY = year;
				break;

			case 3:                     //febuary 29 days on leap year, 28 on other years
				if (day == 1)
				{
					if (isLeapYear())
						tempD = 29;
					else
						tempD = 28;

					tempM = month - 1;
				}
				else
				{
					tempD = day - 1;
					tempM = month;
				}
				tempY = year;
				break;

			case 1:            //january rolling back to previous year 31st december
				if (day == 1)
				{
					tempD = 31;
					tempM = 12;
					tempY = year - 1;
				}
				else
				{
					tempD = day - 1;
					tempM = 1;
					tempY = year;
				}
				break;
			default:
				cout << "Error adding day, month of date used is not a real month\n";
			}

		}
		else if (amount == 'm' || amount == 'M')
		{
			//subtracts a month. if last day of curret month exceeds number of days of previous month set day to last day of previous month 
			//otherwise set day to equivelent day of previous month 
			// NOTE_____:
			//months with 31 days are 1,3,5,7,8,10,12
			//febuary has 29 days on leap year, and 28 days on other years
			//months with 30 days are 4, 6, 9, 11
			switch (month)
			{
			case 1:             //to previous year
				tempD = day;
				tempM = 12;
				tempY = year - 1;
				break;

			case 3:             //for from march to febuary
				if (day >= 28)
				{
					if (day >= 29 && isLeapYear())
					{
						tempD = 29;
					}
					else
						tempD = 28;
				}
				else
					tempD = day;
				tempM = 2;
				tempY = year;
				break;

			case 5:      //31 to 30 day month
			case 7:
			case 10:
			case 12:
				if (day == 31)
					tempD = 30;
				else
					tempD = day;
				tempM = month - 1;
				tempY = year;
				break;

			case 2: //months with number of days <= next previous months number of days
			case 4: 
			case 6:
			case 8:
			case 9:
			case 11:
				tempD = day;
				tempM = month - 1;
				tempY = year;
				break;
			}
		}
		else if (amount == 'y' || amount == 'Y')
		{
			if (month == 2 && day == 29 && isLeapYear())
			{
				tempD = 28;
				tempM = month;
				tempY = year - 1;
			}
			else
			{
				tempD = day;
				tempM = month;
				tempY = year - 1;
			}
		}
		else
		{
			cout << "Improper value used in addition to date. No value added.\n";
		}
		return Date(tempM, tempD, tempY);
	}
}
