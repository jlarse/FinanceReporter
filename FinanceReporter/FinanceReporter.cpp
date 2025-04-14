// FinanceReporter.cpp
// Justin Larsen
// 
// The main purpose of this program is to store cash flows comming in or going out and showing how much
// is gained or lost during a month, year, or overall. This application stores a users cash flows 
// (money comming in or going out) in files. Then the user may then choose to view a report for a 
// month, year, or overall to view money gained or lost based on the cash flows entries the person
// has made.
//
//Visual Studio 2022

#include <cstdio>
#include <direct.h>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>
#include <sys/stat.h>
#include <vector>

#include "Date.h"
#include "CashFlow.h"
#include "CashValue.h"


using namespace std;
using namespace datelarsen;
using namespace cashflowlarsen;
using namespace cashvaluelarsen;

struct MasterFileData    //this struct is used for storing from and writing to the master file
{
    Date earliestDate;  //earliest stored cash flow entered by user
    Date mostRecentDate;
};

struct YearReport  //this struct is represents data for individual year report totals
{
    short year;
    CashValue cashIn, cashOut, gainOrLoss;
};

struct MonthReport  //this struct represents data for individual month report totals
{
    short month;
    CashValue cashIn, cashOut, gainOrLoss;
};

//-------------------------overall program helperr functions-------------------------
inline bool fileExists(const string& name)
//checks if a file of name exists
{
    struct stat buffer;
    return (stat(name.c_str(), &buffer) == 0);
}

int getIntFromString(const string& source);
//returns first integer found in source, if no integer is found returns 0

double getDoubleFromString(const string& source);
//returns first double found in source, if no numerical value is found return 0

void clearLine(istream& in);
//clears additoinal input until new line

int charToInt(const char c);
//Precondition: c is a digit
//Postcondition: Returns integer value of c

bool wantsToStop(istream& in, const char stop1, const char stop2);
//checks if stop1 followd by stop2 have been enterd in input stream, returns true if they have
//false otherwise. Input stream is left the same after this funcation as when function is called.

Date getDateFromString(const string& source);
//Precondition: Year may be more than 4 digits but no larger than the short data type maximum.
//Postocondition: Returns first occurrence of a date (mm/dd/yyyy), in source. 
//                Returns null date if no date is found or if date is in incorrect format in source.

CashValue getCashValueFromString(const string& source); //impliment this
// Returns first CashValue found in string if none is found returns null CashValue

bool masterFileVerify();
//Checks if master file and master directory exist if not create them. Returns true when these
//are created and succesfully opened, false otherwise. If these are created earliest date
//at top of master file will be todays date.

void loadMasterFileData(MasterFileData& masterFileData);
//retrieves master file data and stores them in masterFileData 

int printMainMenuAndSelect();
//Prints options for main menu. Prompts user for a their selection based on the menu options and
//returns that selection, user may enter exit key to exit the program.

//-----main menu functions--------------------------------------------
void viewMonthlyReport(MasterFileData& masterFileData);
//Allows user to view a monthly reports of their choosing

void addCashFlow(MasterFileData& masterFileData);
//Allows user to add cash flow records to the file storage.  

void removeCashFlow(MasterFileData& masterFileData);
//Allows user to remove cash flows from a specific month-year files

void viewFullReport(MasterFileData& masterFileData);
//Displays a report for each year followed by the total cash in,out, and gain or loss for all records

void viewYearlyReport(MasterFileData& masterFileData);
//allows user to view a year report of their choice which shows the totals for each month of that year
//and a total for the entire year

void viewCustomReport(MasterFileData& masterFileData);

//----------main menu helper functions--------------------------------
void storeCashFlow(const CashFlow& cashFlow, MasterFileData& masterFileData);
//If cashFlow is from an earlier date than the earliest date of flow on record in the master file,
//it replaces that date with passed cash flow date. Then, stores cash flow in the file with the name based
//on the month-year of that cash flow. If the file does not exist for that month-year creates a new 
//one. All cash flows are stored in latest-newest order by date.Also calculates cash gain or loss for that
//month-year and stores at bottom of file. 

int displayMonthReport(const string& fileName);
//returns integer of # of cash flows in month-year report, 0 if there are no cash reports in file
//displays a report of cash flows in fileName in table format.

void displayYearReport(const short year);
//displays a year report of year in a table. Displays totals for each month report in that year

YearReport retrieveYearReport(const short year);
//retrieves data for a specific year

void deleteCashFlow(int selection, const string& fileName, MasterFileData& masterData);
// Precondition: selection must be > 1 and <= the number of cash flows in file
// Deletes the selection number cash flow in file (ex. if selection = 3, delete 3rd cash flow in file)

Date findNextEarliestCashFlowDate(const Date& date, const Date& mostRecent);
//searches files for next earliest Cash Flow Date after date

Date findNextMostRecentCashFlowDate(const Date& date, const Date& mostRecent);
//searches files for next most recent Cash Flow Date previous to date

//EXIT1 and EXIT2 are the exit keys used throughout the program that when typed in sequence allow the
//user to exit back to the main menu,or if at the main menue, exit the program. EXIT1 followed by
//EXIT2. 
const char EXIT1 = '-'; 
const char EXIT2 = 'e';

const string RECORDDIRECTORYNAME = "Records"; //The directory name for storing program data files
const string MASTERFNAME = "Master.txt";      //Master file name for storing program data

int main()
{
    int selection;
    MasterFileData masterFileData;

    /*
    bool stop = false;
    do
    {
        Date test;
        string testString;
        cout << "Enter a date: ";
        stop = wantsToStop(cin, EXIT1, EXIT2);

        if (!stop)
        {
            getline(cin, testString);
            test = getDateFromString(testString);
        }
        else
            clearLine(cin);

        test.setDayToLastOfMonth();
        cout << test << endl;

    } while (!stop);
    */

    /*
    for (int i = 0; i < 12; i++)
    {
        test = test - 'm';
        cout << test << endl;
    }*/
    

    /*
    while (true)
    {

        long dollars;
        short cents;
        cout << "Dollars: ";
        cin >> dollars;
        cout << "Cents: ";
        cin >> cents;
        CashValue cash(dollars, cents);
        cout << cash << endl;
    }*/


    /*
    // TEst cashvalue
    bool stop = false;
    int dollars, cents;
    do
    {
        CashValue test;

        /*
        cout << "Dollars: ";
        cin >> dollars;
        cout << "Cents: ";
        cin >> cents;

        CashValue test2(dollars, cents);
        cout << test2 << endl;
        */
        /*
        cout << "Write input: ";
        stop = wantsToStop(cin, EXIT1, EXIT2);
        if (!stop)
        {
            string inputline;
            getline(cin, inputline);
            test = getCashValueFromString(inputline);
        }
        else
            clearLine(cin);

        cout << "Cash Value is: " << test << endl;
        cout << "Stop is: " << stop << endl;
        
    } while (!stop);
    */
     

    if (masterFileVerify())
    {
        loadMasterFileData(masterFileData);
        cout 
            << "********************************************************************************\n"
            << "*****************************|My Finance Reporter|******************************\n"
            << "*****************************|        by         |******************************\n"
            << "*****************************|   Justin Larsen   |******************************\n"
            << "********************************************************************************\n";


        //The following code displays the main menu and allows user to choose a menu selection. Then 
        //runs that menu selection. 
        do
        {
            selection = printMainMenuAndSelect();
            switch (selection)
            {
            case 1:
                cout << "\n*____________________________|View Monthly Report|_____________________________\n";
                viewMonthlyReport(masterFileData);
                break;
            case 2:
                cout << "\n*______________________________|Yearly Report|_________________________________\n";
                viewYearlyReport(masterFileData);
                break;
            case 3:
                cout << "\n*______________________________|View Full Report|______________________________\n";
                viewFullReport(masterFileData);
                break;
            case 4:
                cout << "\n*_______________________________|Add Cash Flow|________________________________\n";
                addCashFlow(masterFileData);
                break;
            case 5:
                cout << "\n*____________________________|Remove Cash Flow|________________________________\n";
                removeCashFlow(masterFileData);
                break;
            case 6:
                cout << "\n*_________________________|View Custom Report|_________________________________\n";
                viewCustomReport(masterFileData);
                break;
            default:
                break;
            };

        } while (selection != -1);
    }

    cout << "\n\nExiting program....\n";
}
int getIntFromString(const string& source)
{
    bool firstDigit = false, isNegative = false;
    int amount = 0;
    if (source.length() == 0)
        return 0;
    else
    {
        for (int i = 0; i < source.length(); i++)
        {
            if (firstDigit)
            {
                if (isdigit(source[i]))
                {
                    if (isNegative)
                        amount = amount * 10 - charToInt(source[i]);
                    else
                        amount = amount * 10 + charToInt(source[i]);
                }
                else
                    return amount;
            }
            
            if (isNegative && !firstDigit)
            {
                if (isdigit(source[i]) && !firstDigit)
                {
                    firstDigit = true;
                    amount += -1 * charToInt(source[i]);
                }
                else
                    return amount;
            }
            else
            {
                if (isdigit(source[i]) && !firstDigit)
                {
                    firstDigit = true;
                    amount += charToInt(source[i]);
                }
            }

            if (source[i] == '-')
                isNegative = true;
        }
        return amount;
    }
}

double getDoubleFromString(const string& source)
{
    bool firstDigit = false, foundDecimal = false, isNegative = false;
    int numDecimals = 0;
    long double amount = 0;

    if (source.length() == 0)
        return 0;
    else
    {
        for (int i = 0; i < source.length(); i++)
        {
            if (foundDecimal)
            {
                if (isdigit(source[i]))
                {
                    if(isNegative)
                        amount = amount - charToInt(source[i]) * pow(.10, ++numDecimals);
                    else
                        amount = amount + charToInt(source[i]) * pow(.10, ++numDecimals);

                }
                else
                    return amount;
            }

            if (firstDigit && !foundDecimal)
            {
                if (isdigit(source[i]))
                {
                    if (isNegative)
                        amount = amount * 10 - charToInt(source[i]);
                    else
                        amount = amount * 10 + charToInt(source[i]);
                }
                else if (source[i] == '.')
                    foundDecimal = true;
                else
                    return amount;
            }

            if (isNegative && !foundDecimal)
            {
                if (isdigit(source[i]) && !firstDigit)
                {
                    firstDigit = true;
                    amount -= charToInt(source[i]);
                }
            }
            else if(!foundDecimal)
            {
                if (isdigit(source[i]) && !firstDigit)
                {
                    firstDigit = true;
                    amount += charToInt(source[i]);
                }
            }

            if (source[i] == '-')
                isNegative = true;
            else if (source[i] == '.')
                foundDecimal = true;
        }
        return amount;
    }
}

void clearLine(istream& in)
{
    char c;
    
    do
    {
        c = in.get();

    } while (c != '\n');
}

int charToInt(const char c)
{
    return static_cast<int>(c) - static_cast<int>('0');
}

bool wantsToStop(istream& in, const char stop1, const char stop2)
{
    char in1 , in2;

    in1 = in.get();               //peek ahead to see if user wants to stop
    in2 = in.get();
    in.putback(in2);             //put back into stream
    in.putback(in1);

    return (in1 == stop1 && in2 == stop2);
}

Date getDateFromString(const string& source)
{
    size_t delimiterFirst = source.find('/');
    short month = 0, day = 0, year = 0;
    char digitOne, digitTwo;

    if (delimiterFirst != string::npos && delimiterFirst >= 1) //if first delimiter is in string, and atleast has enough room for 1 month before it
    {
        size_t delimiterSecond = source.find('/', delimiterFirst + 1);

        if (delimiterSecond != string::npos && (delimiterSecond == delimiterFirst + 2 || delimiterSecond == delimiterFirst + 3)) //if second delimiter found after first, and is 2 or 3 spaces to the right of delimiterOne
        {
            if (delimiterFirst == 1)
            {
                digitOne = source[0];
                if (isdigit(digitOne))
                {
                    month = charToInt(digitOne);
                }
            }
            else
            {
                digitOne = source[delimiterFirst - 2];
                digitTwo = source[delimiterFirst - 1];

                if (isdigit(digitTwo))
                {
                    month = charToInt(digitTwo);

                    if (isdigit(digitOne))
                    {
                        month = month + charToInt(digitOne) * 10;
                    }
                }
            }

            digitOne = source[delimiterSecond - 2];
            digitTwo = source[delimiterSecond - 1];

            if (isdigit(digitTwo))
            {
                day = charToInt(digitTwo);

                if (isdigit(digitOne))
                {
                    day = day + charToInt(digitOne) * 10;
                }
            }

            short pos = delimiterSecond + 1;
            while (pos < source.length() && isdigit(source[pos]))
            {
                year = year * 10 + charToInt(source[pos]);
                pos++;
            }
        }
    }

    if (month == 0 || day == 0 || year == 0)
    {
        cout << "* Invalid date entered. Please re-enter date.\n";
        Date returnDate;
        return returnDate;
    }
    else
    {
        Date returnDate(month, day, year);
        return returnDate;
    }

}

CashValue getCashValueFromString(const string& source)
{
    bool firstDigit = false, foundDecimal = false, isNegative = false, tensCent = false;
    int numDecimals = 0;
    long int dollars = 0;
    short cents = 0;


    if (source.length() == 0)
        return CashValue();
    else
    {
        for (int i = 0; i < source.length(); i++)
        {
            if(tensCent && !isdigit(source[i]))
                return CashValue(dollars,cents);

            if (foundDecimal)
            {
                if (isdigit(source[i]))
                {
                    if (isNegative)
                    {
                        if (!tensCent)
                        {
                            cents = cents - charToInt(source[i]) * 10;
                            tensCent = true;
                        }
                        else
                        {
                            cents = cents - charToInt(source[i]);
                            return CashValue(dollars, cents);
                        }
                    }
                    else
                    {
                        if (!tensCent)
                        {
                            cents = cents + charToInt(source[i]) * 10;
                            tensCent = true;
                        }
                        else
                        {
                            cents = cents + charToInt(source[i]);
                            return CashValue(dollars, cents);
                        }
                    }

                }
                else
                    return CashValue(dollars, cents);
            }

            if (firstDigit && !foundDecimal)
            {
                if (isdigit(source[i]))
                {
                    if (isNegative)
                        dollars = dollars * 10 - charToInt(source[i]);
                    else
                        dollars = dollars * 10 + charToInt(source[i]);
                }
                else if (source[i] == '.')
                    foundDecimal = true;
                else
                    return CashValue(dollars, cents);
            }

            if (isNegative && !foundDecimal)
            {
                if (isdigit(source[i]) && !firstDigit)
                {
                    firstDigit = true;
                    dollars -= charToInt(source[i]);
                }
            }
            else if (!foundDecimal)
            {
                if (isdigit(source[i]) && !firstDigit)
                {
                    firstDigit = true;
                    dollars += charToInt(source[i]);
                }
            }

            if (source[i] == '-')
                isNegative = true;
            else if (source[i] == '.')
                foundDecimal = true;
        }

        return CashValue(dollars,cents);
    }
}

bool masterFileVerify()
{
    ifstream inStream;
    ofstream outStream;

    //the following code checks to see if records directory with the master file exists in it
    //if not, creates them
    if (!fileExists(RECORDDIRECTORYNAME + "/" + MASTERFNAME)) // if master file does not exist in the Record directory, create Record directory with master file in it.
    {
        if (!_mkdir(RECORDDIRECTORYNAME.c_str()))
        {
            cout << "Record directory created.";
        }
        else
        {
            cout << "Record directory failed to create.\n Exiting program.\n";
            return false;
            exit(1);
        }

        outStream.open((RECORDDIRECTORYNAME + "/" + MASTERFNAME).c_str()); //create master file

        if (outStream.fail())
        {
            cout << "[A] Master file failed to open.\n Exiting Program.\n";
            return false;
            exit(1);
        }
        else  //stores today's date as earliest date and most recent date as today in master record when program is first run-- redesign so that earliest flow entry rewrites this.
        {
            Date today("Today");
            outStream << today << endl;
            outStream << today << endl;
            outStream.close();
            cout << "Master file created.\n";
        }

        inStream.open((RECORDDIRECTORYNAME + "/" + MASTERFNAME).c_str());  //double check to see if master file opens corerectly

        if (inStream.fail())
        {
            cout << "[B] Master file failed to open.\n Exiting program.\n";
            return false;
            exit(1);
        }
        else
        {
            cout << "Master file created successufully.\n";
            return true;
        }
        inStream.close();
    }
    else
    {
        cout << "Master file and record directory exits.\n";
        return true;
    }
}

void loadMasterFileData(MasterFileData& masterFileData)
{
    ifstream inStream;
    string temp;

    inStream.open((RECORDDIRECTORYNAME + "/" + MASTERFNAME).c_str()); 

    if (inStream.fail())
    {
        cout << "Master file failed to open.\n Exiting Program.\n";
        exit(1);
    }
    else  //stores today's date as earliest date in master record when program is first run-- redesign so that earliest flow entry rewrites this.
    {
        getline(inStream, temp);
        masterFileData.earliestDate = getDateFromString(temp);
        
        getline(inStream, temp);
        masterFileData.mostRecentDate = getDateFromString(temp);

        inStream.close();
        cout << "Master file data loaded succesfully.\n";
    }
}

int printMainMenuAndSelect()
{
    int selection = '-1';
    bool stop;
    cout << endl 
        << "*********************************| Main Menu |**********************************\n"
        << "* [1] View Monthly Report  [2] View Yearly Report      [3] View FullReport     *\n"
        << "* [4] Add a Cash Flow      [5] Remove a Cash Flow      [6] View Custom Report  *\n"
        << "****************************** [" << EXIT1 << EXIT2 << "] Exit Program *******************************\n";

    do
    {
        cout << "* Selection: ";

        stop = wantsToStop(cin, EXIT1, EXIT2);
        if (!stop)
        {
            string inputline;
            getline(cin, inputline);
            selection = getIntFromString(inputline);
        }
        else
            clearLine(cin);

        if (selection >= 1 && selection <= 6)
            return selection;
        else if (stop)
            return -1;
        else
            cout << "* Invalid selection, select from one of the options above.\n";

    } while (!stop);

    return selection;
}

//-----------------------------------------------Main Menu Functions-------------------------------------//

void viewMonthlyReport(MasterFileData& masterFileData)
{
    bool stop;
    ifstream inStream;
    short selection = 0;
    vector<Date> selections; //stores month and year in format month-year
    Date startDate = masterFileData.earliestDate, today("Today");

    // add each valid month-year file to selections vector
    startDate.setDay(1); 
    for (Date currentDate = startDate; currentDate <= today;  currentDate = currentDate + 'm')
    {
        string fileName = RECORDDIRECTORYNAME + "/" + to_string(currentDate.getMonth()) +
                            "-" + to_string(currentDate.getYear()) + ".txt";
        if (fileExists(fileName))
        {
            selections.push_back(currentDate);
        }   
    }

    if (selections.size() == 0)
    {
        cout << "* There are no reports available please enter a cash flow to create a record.\n";
    }
    else
    {
        do
        {
            cout << "* Enter number in brackets to select from following monthly reports           *\n";
            cout << "*------------------------------------------------------------------------------\n";

            for (size_t i = 0; i < selections.size(); i++)
            {
                cout << "* [" << i + 1 << "]  " << selections[i].getMonthName() << " " << selections[i].getYear() << endl;
            }
            cout << "* [" << EXIT1 << EXIT2 << "] To exit.\n";

            cout << "* Selection:";

            stop = wantsToStop(cin, EXIT1, EXIT2);
            if (!stop)
            {
                string inputline;
                getline(cin, inputline);
                selection = getIntFromString(inputline);
            }
            else
                clearLine(cin);

            if (!stop) 
            {
                if(selection >= 1 && selection <= selections.size())
                {
                                 
                    cout << "\n| Monthly report for " << selections[selection - 1].getMonthName() << " " 
                        << selections[selection - 1].getYear() << " |" << endl;
                    int numCashFlows = displayMonthReport(to_string(selections[selection - 1].getMonth()) + "-" +
                                    to_string(selections[selection - 1].getYear()) + ".txt");
                }
                else
                {
                    cout << "> Invalid selection. Please select a month by the number in brackets.\n\n";
                }
                
            }
        } while (!stop);

    }
}

void addCashFlow(MasterFileData& masterFileData)
{
    Date dateOfFlow;  //data for current cash flow
    CashValue amount = CashValue();
    char type;
    string description;

    vector<CashFlow> cashFlows;

    string inputLine; 
    short count = 0;
    char again = 'n';

    bool stop = false, isValid = false;
    
    cout << "* Enter date of when cash flow took place. Enter the amount of the cash flowing\n"
        << "* in or out (a possitive number represents cash in while negative out). Enter the \n"
        << "* type of cash flow from provided types to label the cash flow. Finnaly a \n"
        << "* description may be entered for personal notes on the cash flow. Type \"" << EXIT1 << EXIT2 << "\" to exit\n"
        << "* at anytime.\n";
       
    char addCashFlow = 'Y';
    do
    {
        CashFlow flow;

        cout << "*------------------------------------------------------------------------------\n";

        if(addCashFlow == 'Y' || addCashFlow == 'y')
            cout << setw(45) << "Cash Flow #" << ++count << endl; 
        else
            cout << setw(45) << "Cash Flow #" << count << endl;
        
        //------------------------------Input date------------------------//
        bool isNull = false; 
        bool dateTooEarly = false, isFutureDate = false;
        do
        {
            if (isNull)
                cout << "> Null date cannot be stored.\n";
            if (dateTooEarly)
                cout << "> A date before 1950 may not be used.\n";
            if (isFutureDate)
                cout << "> Future dates may not be used.\n";

            cout << "* Enter Date (mm/dd/yyyy): ";

            stop = wantsToStop(cin, EXIT1, EXIT2);
            if (!stop)
            {
                getline(cin, inputLine);
                dateOfFlow = getDateFromString(inputLine);
               
                isNull = dateOfFlow.isNull(); 
                
                if (!isNull) 
                {
                    Date today("Today");

                    if (dateOfFlow > today)
                        isFutureDate = true;
                    else
                        isFutureDate = false;
                    
                    if (dateOfFlow.getYear() < 1950)
                        dateTooEarly = true;
                    else
                        dateTooEarly = false;

                    flow.setDate(dateOfFlow);
                }
            }
            else
                clearLine(cin);

        } while (!stop && (isNull || isFutureDate || dateTooEarly));

        if (!stop)
        {
            //------------------------------Input Amount------------------------//
            do
            {
                cout << "* Enter amount: $";

                stop = wantsToStop(cin, EXIT1, EXIT2);
                if (!stop)
                {
                    string inputline;
                    getline(cin, inputline);
                    amount = getCashValueFromString(inputline);

                    if (amount.isNull())
                        cout << "> Amount may not be 0. Please enter any numerical value besides 0.\n";
                    else
                    {
                        flow.setAmount(amount);
                    }
                }
                else
                    clearLine(cin);

            } while (amount.isNull() && !stop);
        }

        if(!stop)
        {
            //------------------------------Input Type------------------------//
            do
            {
                if (!amount.isNegative())
                {
                    cout << "* Types for cash inflow: " << flow.getInFlowTypes() << endl;
                }
                else
                {
                    cout << "* Types for cash outflow: " << flow.getOutFlowTypes() << endl;
                }

                cout << "* Enter cash flow type: ";

                stop = wantsToStop(cin, EXIT1, EXIT2);
                if (!stop)
                {
                    cin >> type; //change to getline and include getline functionality
                    clearLine(cin);

                    if (flow.checkTypeExists(type))
                    {
                        flow.setType(type);
                        isValid = true;
                    }
                    else
                    {
                        cout << "> Type entered is not a valid type. Enter one of the characters in\n"
                            << "> single quotes in the type description.\n";
                    }
                }
                else
                    clearLine(cin);

            } while (!isValid && !stop);
        }

        isValid = false;
        if (!stop)
        {
            //------------------------------Input description------------------------//
            do
            {
                cout << "* Enter a description: ";
                
                stop = wantsToStop(cin, EXIT1, EXIT2);
                if (!stop)
                {
                    getline(cin, description);

                    char ok = 'N';
                    do
                    {
                        cout << "* Description: \"" << description << "\"" << endl
                            << "* Description ok?(Y/N): ";

                        stop = wantsToStop(cin, EXIT1, EXIT2);
                        if (!stop)
                        {
                            cin >> ok;
                            clearLine(cin);
                        }
                        else
                            clearLine(cin);

                        if (ok != 'Y' && ok != 'y' && ok != 'N' && ok != 'n')
                        {
                            cout << "> Invalid entry. Please enter on of the letters in parenthesis.\n"
                                << "> May be upper or lower case.\n";
                        }

                    } while (ok != 'Y' && ok != 'y' && ok != 'N' && ok != 'n' && !stop);

                    if (ok == 'Y' || ok == 'y')
                    {
                        flow.setDescription(description);
                        isValid = true;
                    }
                    else
                        isValid = false;
                }
                else
                    clearLine(cin);

            } while (!stop && !isValid);

        }

        //------------------------------Verify cash flow------------------------//
        
        if (!stop)
        {
            cout << endl << "* Cash Flow #" << count << ": " << flow.getDate() << " "
                 << flow.getAmount() << " " << flow.getTypeString() << " " << flow.getDescription() << endl;
            do
            {
                cout << "* Add this cash flow? (Y/N):";

                stop = wantsToStop(cin, EXIT1, EXIT2);
                if (!stop)
                {
                    cin >> addCashFlow;
                    clearLine(cin);
                }
                else
                    clearLine(cin);

                if (addCashFlow != 'Y' && addCashFlow != 'y' && addCashFlow != 'N' && addCashFlow != 'n')
                {
                    cout << "> Invalid entry. Please enter on of the letters in parenthesis.\n"
                        << "> May be upper or lower case.\n";
                }

            } while (addCashFlow != 'Y' && addCashFlow != 'y' && addCashFlow != 'N' && addCashFlow != 'n' && !stop);

            if ((addCashFlow == 'Y' || addCashFlow == 'y') && !stop)
            {
                cashFlows.push_back(flow);
                storeCashFlow(flow,masterFileData);  //record cash flow in proper text file----------!
            }
        }

        if (cashFlows.size() > 0)
        {
            cout << "*------------------------------------------------------------------------------\n"
                 << endl << "* List of Cash Flows added: \n"
                 << "*------------------------------------------------------------------------------\n";
            for (size_t i = 0; i < cashFlows.size(); i++)
            {
                cout << "* #" << i + 1 << " " << ": " << cashFlows[i].getDate() << " "
                    << cashFlows[i].getAmount() << " " << cashFlows[i].getTypeString() << " " << cashFlows[i].getDescription() << endl;
            }
            cout << endl;
        }

        if (!stop)
        {
            do
            {
                again = 'n';
                cout << "* Add another cash flow? (Y/N):";
             
                stop = wantsToStop(cin, EXIT1, EXIT2);
                if (!stop)
                {
                    cin >> again;
                    clearLine(cin);
                }
                else
                    clearLine(cin);

                if (again != 'Y' && again != 'y' && again != 'N' && again != 'n')
                {
                    cout << "> Invalid entry. Please enter on of the letters in parenthesis.\n"
                         << "> May be upper or lower case.\n";
                }

            } while (again != 'Y' && again != 'y' && again != 'N' && again != 'n' && !stop);
        }
        else
            again = 'n';

    } while (again != 'N' && again != 'n');
}

void removeCashFlow(MasterFileData& masterFileData)
{
    bool stop, lastCashFlowDeleted = false;
    ifstream inStream;
    short selection = 0;
    vector<Date> selections; //stores month and year in format month-year
    Date startDate = masterFileData.earliestDate, today("Today");

    // add each valid month-year file to selections vector
    startDate.setDay(1);
    for (Date currentDate = startDate; currentDate <= today; currentDate = currentDate + 'm')
    {
        string fileName = RECORDDIRECTORYNAME + "/" + to_string(currentDate.getMonth()) +
            "-" + to_string(currentDate.getYear()) + ".txt";
        if (fileExists(fileName))
        {
            selections.push_back(currentDate);
        }
    }

    if (selections.size() == 0)
    {
        cout << "* There are no month-year files in the directory. Please add a cash flow to create a file.\n";
    }
    else
    {
        do
        {
            cout << "* Select a monthly report you wish to delete a cash flow from                 *\n";
            cout << "*------------------------------------------------------------------------------\n";

            for (size_t i = 0; i < selections.size(); i++)
            {
                cout << "* [" << i + 1 << "]  " << selections[i].getMonthName() << " " << selections[i].getYear() << endl;
            }
            cout << "* [" << EXIT1 << EXIT2 << "] To exit.\n";

            cout << "* Selection:";

            stop = wantsToStop(cin, EXIT1, EXIT2);
            if (!stop)
            {
                string inputline;
                getline(cin, inputline);
                selection = getIntFromString(inputline);
                
            }
            else
                clearLine(cin);

            if (!stop)
            {
                if (selection >= 1 && selection <= selections.size())
                {
                    int cashFlowSelection = 0, numCashFlows = 0;
                    bool showMonthReport = true, cashFlowDelted = false;

                    do
                    {
                        string fileToDeleteFrom;
                        if (showMonthReport)
                        {
                            fileToDeleteFrom = to_string(selections[selection - 1].getMonth()) + "-" + to_string(selections[selection - 1].getYear()) + ".txt";

                            cout << "\n| Delete cash flow from record " << selections[selection - 1].getMonthName() << " "
                                << selections[selection - 1].getYear() << " |" << endl;

                            numCashFlows = displayMonthReport(fileToDeleteFrom);
                            
                        }
                        else
                            cout << "> Invalid selection.\n";

                        cout << "* Number to Delete (" << EXIT1 << EXIT2 << " to exit):";

                        stop = wantsToStop(cin, EXIT1, EXIT2);
                        if (!stop)
                        {
                            string inputline;
                            getline(cin, inputline);
                            cashFlowSelection = getDoubleFromString(inputline);
                        }
                        else
                            clearLine(cin);
                        
                        if (!stop)
                        {
                            if (cashFlowSelection < 1 || cashFlowSelection > numCashFlows)
                                showMonthReport = false;
                            else
                            {
                                char verifyDelete = 'n';
                                bool confirmDelete = false, invalidInputConfirm = false;
                                do
                                {
                                    cout << "* Are you sure (y/n): ";
                                    stop = wantsToStop(cin, EXIT1, EXIT2);
                                    if (!stop)
                                    {
                                        string verifyString;
                                        getline(cin, verifyString);
                                        if (verifyString[0] == 'y' || verifyString[0] == 'Y')
                                        {
                                            confirmDelete = true;
                                            invalidInputConfirm = false;
                                        }
                                        else if (verifyString[0] != 'n' && verifyString[0] != 'N')
                                            invalidInputConfirm = true;
                                        else
                                            invalidInputConfirm = false;
                                    }
                                    else
                                        clearLine(cin);

                                    if (invalidInputConfirm)
                                        cout << "* Invalid input. Enter y or n.\n";

                                } while (!stop && invalidInputConfirm);

                                if (confirmDelete)
                                {
                                    deleteCashFlow(cashFlowSelection, fileToDeleteFrom, masterFileData);
                                    cout << "*Cash Flow [" << cashFlowSelection << "] deleted.";
                                    if (numCashFlows == 1)
                                    {
                                        selections.erase(selections.begin() + (selection - 1)); //remove deleted cash flow from user selections
                                        lastCashFlowDeleted = true;
                                    }
                                }
                                else
                                    cout << "* Nothing Deleted.";
                                cout << endl;
                                showMonthReport = true;
                            }
                        }
                    } while (!stop && !lastCashFlowDeleted);
                }
                else
                {
                    cout << "> Invalid selection. Please select a month by the number in brackets.\n";
                }
            }
            cout << endl;
        } while (!stop);
    }
}

void viewFullReport(MasterFileData& masterFileData)
{
    ifstream inStream;
    Date today("Today"), startDate = masterFileData.earliestDate;
    short curYear = 0, nextYear = 0;
    vector<Date> selections;
    vector<YearReport> yearReports;
    bool stop = false;

    short maxSYearIn = 0, maxSYearOut = 0, maxSGainLoss = 0;
    stringstream ssCalcCollumnTemp;
    string sCalcCollumnTemp;
    CashValue totalIn, totalOut, totalGainOrLoss;

    startDate.setDay(1);
    for (Date currentDate = startDate; currentDate <= today; currentDate = currentDate + 'm')
    {
        string fileName = RECORDDIRECTORYNAME + "/" + to_string(currentDate.getMonth()) +
            "-" + to_string(currentDate.getYear()) + ".txt";
        if (fileExists(fileName))
        {
            curYear = currentDate.getYear();

            if (curYear != nextYear)
            {
                nextYear = curYear;
                selections.push_back(currentDate);
            } 
        }
    }

    if(selections.size() == 0)
    {
        cout << "* There are no yearly reports available add a cash flow to create a repot.\n";
    }
    else
    {
        YearReport current;
        for (size_t i = 0; i < selections.size(); i++)
        {
            current = retrieveYearReport(selections[i].getYear());

            ssCalcCollumnTemp.str("");
            ssCalcCollumnTemp << current.cashIn;
            sCalcCollumnTemp = ssCalcCollumnTemp.str();
            if (maxSYearIn < sCalcCollumnTemp.length())
                maxSYearIn = sCalcCollumnTemp.length();

            ssCalcCollumnTemp.str("");
            ssCalcCollumnTemp << current.cashOut;
            sCalcCollumnTemp = ssCalcCollumnTemp.str();

            if (maxSYearOut < sCalcCollumnTemp.length())
                maxSYearOut = sCalcCollumnTemp.length();

            ssCalcCollumnTemp.str("");
            ssCalcCollumnTemp << current.gainOrLoss;
            sCalcCollumnTemp = ssCalcCollumnTemp.str();

            if (maxSGainLoss < sCalcCollumnTemp.length())
                maxSGainLoss = sCalcCollumnTemp.length();

            totalIn += current.cashIn;
            totalOut += current.cashOut;
            totalGainOrLoss += current.gainOrLoss;

            yearReports.push_back(current);
        }

        cout << "*------------------------------------------------------------------------------*\n"
            << "*|" << setw(6) << " Year "
            << "| " << setw(maxSYearIn) << "Cash In"
            << " | " << setw(maxSYearOut) << "Cash Out";
        cout << " | ";

        cout << setw(maxSGainLoss) << "Gain/Loss |\n"
            << "*------------------------------------------------------------------------------*\n";

        for (size_t i = 0; i < yearReports.size(); i++)
        {
            cout << "*| " << setw(4) << yearReports[i].year;

            ssCalcCollumnTemp.str("");
            ssCalcCollumnTemp << yearReports[i].cashIn;

            cout << " | " << setw(maxSYearIn) << ssCalcCollumnTemp.str();

            ssCalcCollumnTemp.str("");
            ssCalcCollumnTemp << yearReports[i].cashOut;

            cout << " | " << setw(maxSYearOut) << ssCalcCollumnTemp.str();

            ssCalcCollumnTemp.str("");
            ssCalcCollumnTemp << yearReports[i].gainOrLoss;

            if (maxSGainLoss > 9)
                cout << " | " << setw(maxSGainLoss) << ssCalcCollumnTemp.str() << " |\n";
            else
                cout << " | " << setw(9) << ssCalcCollumnTemp.str() << " |\n";
        }
        cout << "*--------------------------------|Totals|--------------------------------------*\n";

        ssCalcCollumnTemp.str("");
        ssCalcCollumnTemp << totalIn;
        cout << "| Cash In: " << setw(15) << ssCalcCollumnTemp.str();
        
        ssCalcCollumnTemp.str("");
        ssCalcCollumnTemp << totalOut;
        cout << " | Cash Out: " << setw(15) << ssCalcCollumnTemp.str();

        ssCalcCollumnTemp.str("");
        ssCalcCollumnTemp << totalGainOrLoss;

        if(totalGainOrLoss.isNull())
            cout << " | Broke Even: " << setw(9) << ssCalcCollumnTemp.str();
        else if(!totalGainOrLoss.isNegative())
            cout << " | Gain: " << setw(15) << ssCalcCollumnTemp.str();
        else
            cout << " | Loss: " << setw(15) << ssCalcCollumnTemp.str();
        
        cout << "\n*------------------------------------------------------------------------------*\n\n";
    }
}

void viewYearlyReport(MasterFileData& masterFileData)
{
    Date startDate = masterFileData.earliestDate, today("Today");
    short curYear = 0, nextYear = 0;
    vector<Date> selections;
    bool stop = false;
    int selection = 0;

    cout << "* Select a yearly report you wish to view                                    *\n";
    cout << "*------------------------------------------------------------------------------\n";

    startDate.setDay(1);
    for (Date currentDate = startDate; currentDate <= today; currentDate = currentDate + 'm')
    {
        string fileName = RECORDDIRECTORYNAME + "/" + to_string(currentDate.getMonth()) +
            "-" + to_string(currentDate.getYear()) + ".txt";
        if (fileExists(fileName))
        {
            curYear = currentDate.getYear();

            if (curYear != nextYear)
            {
                nextYear = curYear;
                selections.push_back(currentDate);
            }
        }
    }

    do
    {
        for (size_t i = 0; i < selections.size(); i++)
        {
            cout << "[" << i + 1 << "] " << selections[i].getYear() << endl;
        }
        cout << "[" << EXIT1 << EXIT2 << "] To Exit\n";

        cout << "* Selection:";

        stop = wantsToStop(cin, EXIT1, EXIT2);
        if (!stop)
        {
            string inputline;
            getline(cin, inputline);
            selection = getIntFromString(inputline);
        }
        else
            clearLine(cin);

        if (!stop)
        {
            if (selection >= 1 && selection <= selections.size())
            {
                cout << "\n| Yearly report for " << selections[selection - 1].getYear() << " |" << endl;
                displayYearReport(selections[selection - 1].getYear());
            }
            else
                cout << "> Invalid selection. Try again.\n";
        }
       
    } while (!stop);
} 

void viewCustomReport(MasterFileData& masterFileData)
{

    cout << "* Enter a start and end date to view a custom report.                         *\n"
         << "*------------------------------------------------------------------------------\n"
         << "* Enter start and end dates in range from " << masterFileData.earliestDate << " to " << masterFileData.mostRecentDate << endl;

    bool isNull = false, dateTooEarly = false, dateTooLate = false, stop, invalidDateRange = false;
    string inputLine;
    Date startDate, endDate;
    vector<CashFlow> cashFlows;
    ifstream inStream;
    ofstream outStream;
    CashValue inFlow, outFlow, gainOrLoss;
    short maxAmntSize = 8, maxTypeSize = 6, maxCountSize = 3;
    stringstream ssUseForSetW;
    string sUseForSetW;
    short cashFlowCount = 0;

    //the following code accepts input for a start and end date
    do
    {
        if (isNull)
            isNull = false;

        if (dateTooEarly)
        {
            cout << "> Start date may not be earlier than earliest cash flow on record.\n";
            dateTooEarly = false;
        }
        if (dateTooLate)
        {
            cout << "> Start date must be no later than most recent cash flow on record.\n";
            dateTooLate = false;
        }
        cout << "* Enter a start Date (mm/dd/yyyy): ";

        stop = wantsToStop(cin, EXIT1, EXIT2);
        if (!stop)
        {
            getline(cin, inputLine);
            startDate = getDateFromString(inputLine);

            isNull = startDate.isNull();

            if (!isNull)
            {
                if (startDate < masterFileData.earliestDate)
                    dateTooEarly = true;
                else if(startDate > masterFileData.mostRecentDate)
                    dateTooLate = true;
            }
        }
        else
            clearLine(cin);

    } while (!stop && (isNull || dateTooLate || dateTooEarly));

    isNull = false;
    dateTooEarly = false;
    dateTooLate = false;

    if (!stop)
    {
        do
        {
            if (isNull)
                isNull = false;

            if (dateTooEarly)
            {
                cout << "> End date must be no earlier than earliest cash flow on record.\n";
                dateTooEarly = false;
            }
            if (dateTooLate)
            {
                cout << "> End date must be no later than most recent cash flow on record.\n";
            }
            if (invalidDateRange)
            {
                cout << "> End Date must be on or after the start date.\n";
                invalidDateRange = false;
            }
            cout << "* Enter an end Date (mm/dd/yyyy): ";

            stop = wantsToStop(cin, EXIT1, EXIT2);
            if (!stop)
            {
                getline(cin, inputLine);
                endDate = getDateFromString(inputLine);

                isNull = endDate.isNull();

                if (!isNull)
                {
                    if (endDate < masterFileData.earliestDate)
                        dateTooEarly = true;
                    else if (endDate > masterFileData.mostRecentDate)
                        dateTooLate = true;
                    if (endDate < startDate)
                        invalidDateRange = true;
                }
            }
            else
                clearLine(cin);

        } while (!stop && (isNull || dateTooLate || dateTooEarly || invalidDateRange));
    }

    cout << endl;

    //the following code prints cash flows on record from start date to end date
    for (Date currentDate = startDate; currentDate <= endDate; currentDate = currentDate + 'm')
    {
        string fileName = RECORDDIRECTORYNAME + "/" + to_string(currentDate.getMonth()) +
            "-" + to_string(currentDate.getYear()) + ".txt";
        if (fileExists(fileName))
        {
            
            CashFlow current;

            inStream.open(fileName);

            if (inStream.fail())
            {
                cout << "Month-year file failed to open.\n Exiting program.\n";
                exit(1);
            }
            else
            {
                do
                {
                    stop = wantsToStop(inStream, EXIT1, EXIT2);
                    if (!stop)
                    {
                        inStream >> current;
                        clearLine(inStream);

                        if (current.getDate() >= startDate && current.getDate() <= endDate)
                        {
                            ssUseForSetW.str("");
                            ssUseForSetW << "[" << ++cashFlowCount << "]";
                            sUseForSetW = ssUseForSetW.str();

                            if (maxCountSize < sUseForSetW.length())
                                maxCountSize = sUseForSetW.length();

                            ssUseForSetW.str("");
                            ssUseForSetW << current.getAmount();
                            sUseForSetW = ssUseForSetW.str();

                            if (maxAmntSize < sUseForSetW.length())
                                maxAmntSize = sUseForSetW.length();

                            if (maxTypeSize < current.getTypeString().length())
                                maxTypeSize = current.getTypeString().length();

                            cashFlows.push_back(current);

                            if (current.getAmount().isNegative())
                                outFlow += current.getAmount();
                            else
                                inFlow += current.getAmount();
                        }       
                    }
                    else
                        clearLine(inStream);
                } while (!stop);
                inStream.close();
            }
        }
    }
    gainOrLoss = inFlow + outFlow;

    cout << "| Cash flows from " << startDate << " to " << endDate << " |\n"
        << "*------------------------------------------------------------------------------\n"
        << "*|" << setw(maxCountSize) << "[#]"
        << "|    Date   "
        << " | " << setw(maxAmntSize) << "Amount"
        << " | " << setw(maxTypeSize) << "Type"
        << " | Description\n"
        << "*------------------------------------------------------------------------------\n";

    for (size_t i = 0; i < cashFlows.size(); i++)
    {
        ssUseForSetW.str("");
        ssUseForSetW << "[" << i + 1 << "]";
        sUseForSetW = ssUseForSetW.str();

        cout << "*|" << setw(maxCountSize) << sUseForSetW;

        ssUseForSetW.str("");
        ssUseForSetW << cashFlows[i].getDate();
        sUseForSetW = ssUseForSetW.str();

        cout << "| " << right << setw(10) << sUseForSetW;

        ssUseForSetW.str("");
        ssUseForSetW << cashFlows[i].getAmount();
        sUseForSetW = ssUseForSetW.str();

        cout << " | " << right << setw(maxAmntSize) << sUseForSetW;
        cout << " | " << setw(maxTypeSize) << cashFlows[i].getTypeString();
        cout << " | " << cashFlows[i].getDescription() << endl; //edit for description wrapping to next line(s)
    }



    cout << "*--------------------------------|Totals|--------------------------------------\n"
        << "*| In Flow: ";

    ssUseForSetW.str("");
    ssUseForSetW << inFlow;
    sUseForSetW = ssUseForSetW.str();

    cout << right << setw(15) << sUseForSetW << " | Out Flow: ";

    ssUseForSetW.str("");
    ssUseForSetW << outFlow;
    sUseForSetW = ssUseForSetW.str();


    cout << right << setw(15) << sUseForSetW;

    if (gainOrLoss.isNull())
        cout << " | Broke Even: ";
    else if (!gainOrLoss.isNegative())
        cout << " | Gain: ";
    else if (gainOrLoss.isNegative())
        cout << " | Loss: ";


    ssUseForSetW.str("");
    ssUseForSetW << gainOrLoss;
    sUseForSetW = ssUseForSetW.str();

    if (gainOrLoss.isNull())
        cout << right << setw(10) << sUseForSetW << endl;
    else
        cout << right << setw(15) << sUseForSetW << endl
        << "*------------------------------------------------------------------------------\n\n";

}
//-----------------------------------------End of main menu functions----------------------------------------//

//-----------------------------------------Main Menu Helper Functions-----------------------------------------//

void storeCashFlow(const CashFlow& cashFlow, MasterFileData& masterFileData)
{
    ifstream inStream;
    ofstream outStream;
    Date date = cashFlow.getDate(), earliest = masterFileData.earliestDate, mostRecent = masterFileData.mostRecentDate;
    bool stop;
    vector<CashFlow> sortedCashFlows;
    bool isEarlier = false;

    //fileSource is file name to create or open for the month-year of cash flow
    string fileSource = RECORDDIRECTORYNAME + "/" + to_string(date.getMonth()) + "-" + to_string(date.getYear()) + ".txt";

    //The following code tests to see if the date of cashFlow is earlier than earliest date stored
    //in master file, if so it replaces the date of cashFlow with that date in the master file
    if (date < earliest || date > mostRecent)
    {
        outStream.open((RECORDDIRECTORYNAME + "/" + MASTERFNAME).c_str(), ofstream::out | ofstream::trunc); //erase maste file

        if (outStream.fail())
        {
            cout << "> Failed to open master file. Exiting Program. \n";
            exit(1);
        }
        else
        {
            //-------------------------------store Data in master file-------------------------------// re-write master file
            if(date < earliest)
            { 
                outStream << date << endl;
                outStream << mostRecent << endl;
                masterFileData.earliestDate = date;
                cout << "Changed earliest cash flow on record to: " << date << endl;
            }
            else if (date > mostRecent)
            {
                outStream << earliest << endl;
                outStream << date << endl;
                masterFileData.mostRecentDate = date;
                cout << "Changed most recent cash flow on record to: " << date << endl;
            }

        }
        outStream.close();


 
        //-------------Add any other data for master file here because it just got erased
    }
   

    //The following code checks if a month-year file exists for the date of cashFlow. If it doesnt exist, it creates
    //the month-year file and outputs cashFlow to that file. If it does exist, it recreates the file so all existing
    //CashFlows' including cashFlow are written to file in earliest to latest order.
    if (!fileExists(fileSource)) // file does not exist for the month and year
    {
        outStream.open(fileSource); //create file for the month and year of cash flow

        if (outStream.fail())
        {
            cout << "> Record file \"" << fileSource << "\" failed to create.\n Exiting Program.\n";
            outStream.close();
            exit(1);
        }
        else
        {
            cout << "File: " << fileSource << " created.\n";
            //---------------------- write to month-year file if it doesnt exist-----------------------//
            outStream << cashFlow << endl << EXIT1 << EXIT2 << endl;
          
            if (!cashFlow.getAmount().isNegative())
            {
                outStream << cashFlow.getAmount() << " " << 0 << " " << cashFlow.getAmount();
            }
            else
            {
                outStream << 0 << " " << cashFlow.getAmount() << " " << cashFlow.getAmount();
            }
            outStream.close();
        }
    }
    else
    {
        inStream.open(fileSource);

        if (inStream.fail())
        {
            cout << "> Record file \"" << fileSource << "\" failed to open when attempting read from.\n Exiting Program.\n";
            outStream.close();
            exit(1);
        }
        else
        {
            CashFlow inCashFlow;
            bool stored = false;
            do
            {
                stop = wantsToStop(inStream, EXIT1, EXIT2);
                if (!stop)
                {
                    inStream >> inCashFlow; 
                    clearLine(inStream);

                    if (inCashFlow.getDate() <= cashFlow.getDate())
                    {
                        sortedCashFlows.push_back(inCashFlow);
                    }
                    else
                    {
                        if (!stored)
                        {
                            stored = true;
                            sortedCashFlows.push_back(cashFlow);
                            sortedCashFlows.push_back(inCashFlow);
                        }
                        else
                        {
                            sortedCashFlows.push_back(inCashFlow);
                        }
                    }
                }
                else
                {
                    if (!stored)
                        sortedCashFlows.push_back(cashFlow);

                    clearLine(inStream);
                }
            } while (!stop);
            inStream.close();

            outStream.open(fileSource, ofstream::out | ofstream::trunc); //delete contents of file (truncate)
            if (!outStream.fail())
            {
                CashValue cashIn, cashOut, cashGainOrLoss;
                //--------------------------------write to month-year file----------------------------------//
                for (size_t i = 0; i < sortedCashFlows.size(); i++) //record all cash flows in file
                {
                    outStream << sortedCashFlows[i] << endl;
                    if (!sortedCashFlows[i].getAmount().isNegative())
                        cashIn += sortedCashFlows[i].getAmount();
                    else
                        cashOut += sortedCashFlows[i].getAmount();
                }
                cashGainOrLoss = cashIn + cashOut;
                outStream << EXIT1 << EXIT2 << endl; //record exit marker
                outStream << cashIn << " " << cashOut << " " << cashGainOrLoss;
                outStream.close();
            }
            else
            {
                cout << "> Failed to erase contents and open \"" << fileSource << "\". Exiting program.\n";
                exit(1);
            }
        }
    }
}

int displayMonthReport(const string& fileName)
{
    ifstream inStream;
    CashValue inFlow, outFlow, gainOrLoss;
    vector<CashFlow> cashFlows;
    CashFlow current;
    bool stop;
    short maxAmntSize = 8, maxTypeSize = 6, maxCountSize = 3;
    stringstream ssUseForSetW;
    string sUseForSetW;
    int cashFlowCount = 0;

    inStream.open(RECORDDIRECTORYNAME + "/" + fileName); 

    if (inStream.fail())
    {
        cout << "Month-year file failed to open.\n Exiting program.\n";
        exit(1);
    }
    else
    {
        do
        {
            stop = wantsToStop(inStream, EXIT1, EXIT2);
            if (!stop)
            {
                ssUseForSetW.str("");
                ssUseForSetW << "[" << ++cashFlowCount << "]";
                sUseForSetW = ssUseForSetW.str();

                if (maxCountSize < sUseForSetW.length())
                    maxCountSize = sUseForSetW.length();

                inStream >> current;
                clearLine(inStream);

                ssUseForSetW.str("");
                ssUseForSetW << current.getAmount();
                sUseForSetW = ssUseForSetW.str();

                if(maxAmntSize < sUseForSetW.length())
                    maxAmntSize = sUseForSetW.length();

                if (maxTypeSize < current.getTypeString().length())
                    maxTypeSize = current.getTypeString().length();
                
                cashFlows.push_back(current);  
            }
            else
                clearLine(inStream);
        } while (!stop);

        inStream >> inFlow >> outFlow >> gainOrLoss;
        inStream.close();


        cout << "*------------------------------------------------------------------------------\n"
            << "*|" << setw(maxCountSize) << "[#]"
             << "|    Date   "
             << " | " << setw(maxAmntSize) << "Amount"
             << " | " << setw(maxTypeSize) << "Type"
             << " | Description\n"
             << "*------------------------------------------------------------------------------\n";

        for (size_t i = 0; i < cashFlows.size(); i++)
        {
            ssUseForSetW.str("");
            ssUseForSetW << "[" << i + 1 << "]";
            sUseForSetW = ssUseForSetW.str();

            cout << "*|" << setw(maxCountSize) << sUseForSetW;

            ssUseForSetW.str("");
            ssUseForSetW << cashFlows[i].getDate();
            sUseForSetW = ssUseForSetW.str();

            cout << "| " << right << setw(10) << sUseForSetW;
            
            ssUseForSetW.str("");
            ssUseForSetW << cashFlows[i].getAmount();
            sUseForSetW = ssUseForSetW.str();

            cout << " | " << right << setw(maxAmntSize) << sUseForSetW;
            cout << " | " << setw(maxTypeSize) << cashFlows[i].getTypeString();
            cout << " | " << cashFlows[i].getDescription() << endl; //edit for description wrapping to next line(s)
        }



        cout << "*--------------------------------|Totals|--------------------------------------\n"
            << "*| In Flow: ";

        ssUseForSetW.str("");
        ssUseForSetW << inFlow;
        sUseForSetW = ssUseForSetW.str();

        cout << right << setw(15) << sUseForSetW << " | Out Flow: ";

        ssUseForSetW.str("");
        ssUseForSetW << outFlow;
        sUseForSetW = ssUseForSetW.str();


        cout << right << setw(15) << sUseForSetW;
        
        if(gainOrLoss.isNull())
            cout << " | Broke Even: ";
        else if (!gainOrLoss.isNegative())
            cout << " | Gain: ";
        else if (gainOrLoss.isNegative())
            cout << " | Loss: ";


        ssUseForSetW.str("");
        ssUseForSetW << gainOrLoss;
        sUseForSetW = ssUseForSetW.str();

        if (gainOrLoss.isNull())
            cout << right << setw(10) << sUseForSetW << endl;
        else
            cout << right << setw(15) << sUseForSetW << endl
             << "*------------------------------------------------------------------------------\n\n";
    }


    return cashFlowCount;
}

void displayYearReport(const short year)
{
    Date startDate(1, 1, year), endDate(12, 1, year);
    vector<Date> dateOfExistingFile;
    vector<MonthReport> reports;
    ifstream inStream;
    CashValue totalIn, totalOut, totalGL;
    int maxSizeIn = 7, maxSizeOut = 8, maxSizeGL = 9;
    stringstream ssSizeCalc;
    string sSizeCalc;
    bool stop = false;

    //this code aquires a vector of filenames that exist for year
    startDate.setDay(1);
    for (Date currentDate = startDate; currentDate <= endDate; currentDate = currentDate + 'm')
    {
        string fileName = RECORDDIRECTORYNAME + "/" + to_string(currentDate.getMonth()) +
            "-" + to_string(currentDate.getYear()) + ".txt";
        if (fileExists(fileName))
        {
            dateOfExistingFile.push_back(currentDate);
        }
    }

    for (size_t i = 0; i < dateOfExistingFile.size(); i++)
    {
        MonthReport current;
        string fileName = RECORDDIRECTORYNAME + "/" + to_string(dateOfExistingFile[i].getMonth()) +
            "-" + to_string(dateOfExistingFile[i].getYear()) + ".txt";
        inStream.open(fileName);
        if (inStream.fail())
        {
            cout << "> Failed to open " << fileName << " during display of yearly report.\n Exiting Program.\n";
            exit(1);
        }
        else
        {
            current.month = dateOfExistingFile[i].getMonth();
            do
            {
                stop = wantsToStop(inStream, EXIT1, EXIT2);
                if (!stop)
                {
                    string temp;
                    getline(inStream, temp);
                }
                else
                    clearLine(inStream);

            } while (!stop);
            inStream >> current.cashIn >> current.cashOut >> current.gainOrLoss;
            totalIn += current.cashIn;
            totalOut += current.cashOut;
            totalGL += current.gainOrLoss;

            ssSizeCalc.str("");
            ssSizeCalc << current.cashIn;
            sSizeCalc = ssSizeCalc.str();
            if (maxSizeIn < sSizeCalc.length())
                maxSizeIn = sSizeCalc.length();

            ssSizeCalc.str("");
            ssSizeCalc << current.cashOut;
            sSizeCalc = ssSizeCalc.str();
            if (maxSizeOut < sSizeCalc.length())
                maxSizeOut = sSizeCalc.length();

            ssSizeCalc.str("");
            ssSizeCalc << current.gainOrLoss;
            sSizeCalc = ssSizeCalc.str();
            if (maxSizeGL < sSizeCalc.length())
                maxSizeGL = sSizeCalc.length();


            reports.push_back(current);
        }
        inStream.close();
    }

    cout << "*------------------------------------------------------------------------------*\n"
        << "*| " << setw(5) << "Month"
        << " | " << setw(maxSizeIn) << "Cash In"
        << " | " << setw(maxSizeOut) << "Cash Out";
    cout << " | " << setw(maxSizeGL) << "Gain/Loss |\n"
        << "*------------------------------------------------------------------------------*\n";

    for (size_t i = 0; i < reports.size(); i++)
    {
        cout << "*| " << setw(5) << reports[i].month;

        ssSizeCalc.str("");
        ssSizeCalc << reports[i].cashIn;

        cout << " | " << setw(maxSizeIn) << ssSizeCalc.str();

        ssSizeCalc.str("");
        ssSizeCalc << reports[i].cashOut;

        cout << " | " << setw(maxSizeOut) << ssSizeCalc.str();

        ssSizeCalc.str("");
        ssSizeCalc << reports[i].gainOrLoss;

        if (maxSizeGL > 9)
            cout << " | " << setw(maxSizeGL) << ssSizeCalc.str() << " |\n";
        else
            cout << " | " << setw(9) << ssSizeCalc.str() << " |\n";

    }
    cout << "*-----------------------------|Totals|-----------------------------------------\n";

    ssSizeCalc.str("");
    ssSizeCalc << totalIn;
    cout << "| Cash In: " << setw(15) << ssSizeCalc.str();

    ssSizeCalc.str("");
    ssSizeCalc << totalOut;
    cout << " | Cash Out: " << setw(15) << ssSizeCalc.str();

    ssSizeCalc.str("");
    ssSizeCalc << totalGL;

    if(totalGL.isNull())
        cout << " | Broke Even: " << setw(9) << ssSizeCalc.str();
    else if (!totalGL.isNegative())
        cout << " | Gain: " << setw(15) << ssSizeCalc.str();
    else
        cout << " | Loss: " << setw(15) << ssSizeCalc.str();

    cout << "\n*------------------------------------------------------------------------------*\n\n";
}

YearReport retrieveYearReport(const short year)
{
    YearReport report;
    ifstream inStream;

    report.year = year;

    for (int m = 1; m <= 12; m++)
    {
        string monthYearReport = to_string(m) + "-" + to_string(year) + ".txt";
        if (fileExists(RECORDDIRECTORYNAME + "/" + monthYearReport))
        {
            inStream.open(RECORDDIRECTORYNAME + "/" + monthYearReport);
            if (inStream.fail())
            {
                cout << "> Failed opening " << RECORDDIRECTORYNAME + "/" + monthYearReport << " when calculating year report.\n";
            }
            else
            {
                bool stop = false;
                CashValue cashIn, cashOut, gainLoss;

               
                do 
                {
                    string trash;
                    stop = wantsToStop(inStream, EXIT1, EXIT2);
                    if (!stop)
                        getline(inStream, trash);
                    else
                        clearLine(inStream);

                } while (!stop);

                inStream >> cashIn >> cashOut >> gainLoss;
                report.cashIn += cashIn;
                report.cashOut += cashOut;
                report.gainOrLoss += gainLoss;
            }
            inStream.close();
        }
    }

    return report;
}

void deleteCashFlow(int selection, const string& fileName, MasterFileData& masterData)
{
    int count = 0;
    ifstream inStream;
    ofstream outStream;
    vector<CashFlow> cashFlows;
    CashFlow current, toBeDeleted;
    bool stop;
    string fileAndPath = RECORDDIRECTORYNAME + "/" + fileName;

    //The following code stores all cash flows in file in a vector except the one
    //that is to be deleted (the selection)
    inStream.open(fileAndPath);
    if (inStream.fail())
    {
        cout << "Month-year file failed to open.\n Exiting program.\n";
        exit(1);
    }
    else
    {
        do
        {
            stop = wantsToStop(inStream, EXIT1, EXIT2);
            if (!stop)
            {
                inStream >> current;
                clearLine(inStream);
                count++;

                if (count != selection)
                    cashFlows.push_back(current);
                else
                    toBeDeleted = current;
            }
            else
                clearLine(inStream);
        } while (!stop);
    }
    inStream.close();

    if (count == 1)
    {
        if (remove(fileAndPath.c_str()) == 0)
            cout << "* Last cash flow in file, file " << fileName << " has been deleted.\n";
        else
            cout << "> Last Cash Flow in file, error deleting Cash Flow and " << fileAndPath << ".\n";
    }
    else
    {

        //the following code writes all cash flows from vector to file including final cash in, out , and gain or loss.
        outStream.open((RECORDDIRECTORYNAME + "/" + fileName), ofstream::out | ofstream::trunc);
        if (!outStream.fail())
        {
            CashValue cashIn, cashOut, cashGainOrLoss;
            //--------------------------------write to month-year file----------------------------------//
            for (size_t i = 0; i < cashFlows.size(); i++)
            {
                outStream << cashFlows[i] << endl;
                if (!cashFlows[i].getAmount().isNegative())
                    cashIn += cashFlows[i].getAmount();
                else
                    cashOut += cashFlows[i].getAmount();
            }
            cashGainOrLoss = cashIn + cashOut;
            outStream << EXIT1 << EXIT2 << endl; //record exit marker
            outStream << cashIn << " " << cashOut << " " << cashGainOrLoss;
            outStream.close();
        }
        else
        {
            cout << "> Failed to erase cashflow and open \"" << RECORDDIRECTORYNAME + "/" + fileName << "\". Exiting program.\n";
            exit(1);
        }
    }

    //the following sets a new earliest record date in master file if earliest record is deleted and Also it sets a new most recent date if most recent record is deleted.
    if (toBeDeleted.getDate() == masterData.earliestDate || toBeDeleted.getDate() == masterData.mostRecentDate)
    {
        ofstream outStream;

        if (toBeDeleted.getDate() == masterData.earliestDate)
        {
            masterData.earliestDate = findNextEarliestCashFlowDate(toBeDeleted.getDate(), masterData.mostRecentDate);
            cout << "Changed earliest cash flow on record to: " << masterData.earliestDate << endl;
        }
        else if (toBeDeleted.getDate() == masterData.mostRecentDate)
        {
            masterData.mostRecentDate = findNextMostRecentCashFlowDate(toBeDeleted.getDate(), masterData.earliestDate);
            cout << "Changed most recent cash flow on record to : " << masterData.mostRecentDate << endl;
        }

        outStream.open((RECORDDIRECTORYNAME + "/" + MASTERFNAME), ofstream::out | ofstream::trunc);
        if (outStream.fail())
        {
            cout << "> Failed opening and truncating master file in remove Cash Flow.\n Exiting program.\n";
            exit(1);
        }
        else
        {
            outStream << masterData.earliestDate << endl;
            outStream << masterData.mostRecentDate << endl;
        }
        outStream.close();
    }
}

Date findNextEarliestCashFlowDate(const Date& date, const Date& mostRecent)
{
    Date nextEarliest;
    ifstream inFileStream;

    for (Date d = date; d <= mostRecent; d = d + 'm')
    {
        string fileName = RECORDDIRECTORYNAME + "/" + to_string(d.getMonth()) + "-" + to_string(d.getYear()) + ".txt";

        if (fileExists(fileName))
        {
            inFileStream.open(fileName);
            if (inFileStream.fail())
            {
                cout << "> Opening file " << fileName << " failed when trying to find next earliest cash flow.\n"
                    << "Exiting Program.\n";
                exit(1);
            }
            else
            {
                CashFlow earliest;
                inFileStream >> earliest;
                return earliest.getDate();
            }
            inFileStream.close();
        }
    }

    cout << "> Earliest date not found.\n";
    return date;
}

Date findNextMostRecentCashFlowDate(const Date& date, const Date& earliest)
{
    CashFlow nextMostRecent;
    ifstream inFileStream;
    bool foundMostRecentFile = false;
    Date d = date;

    if (date == earliest)
        return date;
    else if (date > earliest)
    {
        do
        {
            string fileName = RECORDDIRECTORYNAME + "/" + to_string(d.getMonth()) + "-" + to_string(d.getYear()) + ".txt";

            if (fileExists(fileName))
            {
                foundMostRecentFile = true;
                inFileStream.open(fileName);
                if (inFileStream.fail())
                {
                    cout << "> Opening file " << fileName << " failed when trying to find next earliest cash flow.\n"
                        << "Exiting Program.\n";
                    exit(1);
                }
                else
                {
                    bool stop;
                    do
                    {
                        stop = wantsToStop(inFileStream, EXIT1, EXIT2);
                        if (!stop)
                            inFileStream >> nextMostRecent;
                        clearLine(inFileStream);

                    } while (!stop);

                    inFileStream.close();
                }
            }
            else
                d = d - 'm';

        } while (d >= earliest && !foundMostRecentFile);

        return nextMostRecent.getDate();
    }
    else
    {
        cout << "> Next most recent date not found.\n";
        return earliest;
    }    
}

//----------------------------------------------------------------------------------------------------//

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
