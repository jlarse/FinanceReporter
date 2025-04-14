// Date.h
// Justin Larsen
// Description: Interface of a date class used to store a date object month/day/year
// Visual Studio 2022


#ifndef DATE_H
#define DATE_H

#include <ctime>
#include <cstdlib>
#include <iostream>
#include <string>


using namespace std;

namespace datelarsen
{
	class Date
	{
	public:
		Date();
		// Default constructor, sets to date 0/0/0 (A null Date)
		Date(const char *day);//implement
		//perecondition, day is a c-string containing the day of the week or abreviatoin for day of the week. 
		//(Ex. "Mon","Monday","Tue","Tuesday","Thur","Thursday","Fri","Friday","Sat","Saturday","Sun","Sunday", or "Today") Any of these values will work.
		// Postcondition instantiates a date object with the date of the day of the week for the current week week, a week begins on sunday
		// and ends on saturday. 
		Date(const short month, const short day, const short year);
		// Sets date object as month, day , year. If the date is not on the calandar date will be set to null date and error message will be printed (0/0/0)

		short getDay() const;
		// Returns short value of the day
		short getMonth() const;
		// Returns short value of the month
		short getYear() const;
		// Returns short value of the year
		string getMonthName();
		// Returns string of month written out ex. January
		string getDayOfWeek() const; 
		// Returns string value of the day of the week. Ex. "Saturday"


		void setDay(const short newDay);
		// Sets day of date must be in range of possible days for that month, year combination of the date
		void setDayToLastOfMonth();
		//sets day to last day of the current month

		bool isLeapYear() const; 
		// Returns true of this dates year is a leapyear, false otherwise
		bool isLeapYear(const short year) const;
		//returns true if year passed is leap year
		bool isNull() const;
		// Returns true if date is a null date, otherwise false

		friend ostream& operator <<(ostream& out,const Date& date);
		// Outputs date in format month/day/year
		friend istream& operator >>(istream& in, Date& date);
		// Accepts input for month in format month/day/year, clears whitespace before the date, stops reading after the last digit for year.
		// Incorrect format will result in the date being stored as a null date (0/0/0), will read until last consecutive non-space,non-end of line character.

		friend bool operator <(const Date& left, const Date& right);
		// Returns true if left date is earlier than right. False otherwise.
		friend bool operator >(const Date& left, const Date& right);
		// Returns true if left date is later than right date, False otherwise.
		friend bool operator <=(const Date& left, const Date& right);
		// Returns true if left is a earlier date than right, or the same date as right. False otherwise.
		friend bool operator >=(const Date& left, const Date& right);
		// Returns true if left is a later date than right, or the same date as right. False otherwise.
		friend bool operator ==(const Date& left, const Date& right);
		// Retruns true if left and right are for the same month, day, and year. False otherwise.

		Date operator+(const char amount);
		// Overaloaded addition operator
		//Used to increment a date by a month,day, or year. To specify use 'd' for day , 'm' for mont, and 'y' for year.
		//When using addition next available calendar date will be the result when adding a day, month, or year.
		//When adding a month, if the current months day is on the last day of the month and the next month has fewer days the 
		//in the month the new date will be on the last day of that next month (ex 1/31/2020 + 'm' = 2/29/2020).
		//In the situation where the current day is less than or equal to the next months day the next months day will be the same day 
		//(ex. 2/29/2020 + 'm' = 3/29/2020).
		//-----Key----------------------------------------------------//
		//Months with 31 days are 1,3,5,7,8,10,12
		//Febuary has 29 days on leap year, and 28 days on other years
		//Months with 30 days 4, 6, 9, 11

		Date operator-(const char amount);
		// Overaloaded subtraction operator
		// Decrements date by a day, month, or year when amount = 'd', 'm', 'y' respectiveley
		// When decrementing month if the day is the last day of the current month and has more days than previous month, day set to last day of previous month
		//-----Key----------------------------------------------------//
		//Months with 31 days are 1,3,5,7,8,10,12
		//Febuary has 29 days on leap year, and 28 days on other years
		//Months with 30 days 4, 6, 9, 11


		void operator =(const Date& date);
		//Overloaded asignment operator, all date values copied

	private:
		short day;
		short month;
		short year;

		bool validateDate(const short month, const short day, const short year);
		//checks to see if a date based on month/day/year is an actual calandar date, if so return true, otherwise return false

		int charToInt(const char c);
		//precondition c is a digit, converts c to its integer value

		int dayOfWeek() const;
		// returns value for day of week 0 = sunday , 6 = saturday
	};
}

#endif
