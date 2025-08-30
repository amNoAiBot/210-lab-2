/**********************************************************************
* Name: Sunny Anand
*
* Course: Previously taken course
*
* Assignment: Lab 5: Tracking Expenses with Arrays & Strings
*
* IDE/Compiler(s) used: CodeBlocks/G++
*
* Description:
* Lab 5: Tracking Expenses with Arrays and Strings
*
Requirements:
1. The program must produce a similar output as the example below. The output should be formatted
nicely.
2. The program must use array of structs
3. The program must not use global variables. In another words, it must use local variables
and pass-by-value or pass-by-reference parameters.
4. The program must define the maximum number of entries such as 100 and keeps track of the
actual count of the current number of expenses entered by the user. You’re not allowed to use vectors.
5. You should not use data file to save or read from. All operations should be done through
the use of arrays and array indices.
6. You must write at least 2 functions to get the minimum design score. The more functions
you have, the higher score you get for the design criteria.
Required error handling:
The program MUST perform the following checks:
1. Check for invalid amount (negative or 0 number)
2. Description cannot be empty.
3. Search is case-insensitive (ignore case, but the user may type in any case).
**********************************************************************/




/*********************************************************************
*               Importing C++ Built-in Library Functions
**********************************************************************/

// Importing iostream which has all the necessary I/O functions such as cin & cout
// Previous line "using namespace std" is commented, as it will import
// all the 100s or 1000s of built-in libraries available. Instead, we
// import only relevant libraries as shown right below.
#include <iostream>
using std::cin;
using std::cout;
using std::cerr;
using std::endl;

// There are two ways to do output formatting:
// 1. Using std:ios - E.g. setf(ios::left); cout.width(20); cout.setf(ios::fixed); cout.precision(1);
using std::ios;
// 2. Using iomanip - E.g. cout << fixed << setprecision(2); cout << setw(20);
// #include <iomanip>

// Importing string libraries
#include <string>
using std::string;
using std::getline;

// Importing cstdlib libraries for atoi and atof
#include <cstdlib>

// Importing sstream libraries for stringstream, istringstream, and ostringstream.
#include <sstream>
// The following "using namespace std;" is needed for stringstream to work. Else, it won't work.
using namespace std;

// Importing cctype libraries for toupper and tolower.
#include <cctype>




/*********************************************************************
*                  User defined data types (struct) are
*                      defined here before main().
**********************************************************************/

struct Expense {
  string expenseDescription;
  double expenseAmount;
};




/*********************************************************************
*             User Defined Function Prototypes are defined
*               here as the actual functions are defined
*                             below main().
**********************************************************************/

// Declaring function prototypes. Function definitions must precede function calls,
// or you can use the following workaround of defining prototypes instead of having
// to define the functions before main().
void printIdentification(string);
int getUserMenuSelectionInteger();
int menuFunctions(int, Expense [], int, int);
void printWarningIfUserEnteredWrongInput(int);
void printOutputStringStream(int, Expense [], int, int, string findString = "nulll", double findAmount = -1);
string toSmallLetters(string aCppString);




/*********************************************************************
*
*                           The main() function
*
**********************************************************************/

int main() {

  const int ARRAY_CAPACITY = 100;
  Expense expenseInfo[ARRAY_CAPACITY];          // Array of size 100. Each element is of user defined struct data type Expense

  // Identifying information in comment form is included at the top of this file.
  // Here, identifying information in cout form similar to sample-comment.cpp is provided.
  printIdentification("Lab 05: Tracking Expenses with Arrays & Strings\n");

  // Initialize with a -ve amount, so if the user has entered nothing yet, we can print an appropriate message
  // when the user selects "show all" from the menu options.
  expenseInfo[0].expenseAmount = -100;

  // User menu selection function is called here from which user menu selection is returned.
  // Then based on the user menu selection, menuFunctions function is called.
  int userMenuInt = 0;
  int expenseInfoArrayIndex = 0;
  while (userMenuInt != 5) {
    userMenuInt = getUserMenuSelectionInteger();     // Call the user menu selection function
    expenseInfoArrayIndex = menuFunctions(userMenuInt, expenseInfo, expenseInfoArrayIndex, ARRAY_CAPACITY);
  }

  return 0;

}






/*********************************************************************
* Function: User Menu Selection Function: Ask user for input about menu.
*           Return integer signifying which menu option was selected by the user.
*
* Print out the 5 options the user has and ask the user to enter a number.
* If the user did not enter a number, print warning.
* Return the user menu selection integer back to the calling function.
*
* Parameter:
*   None
*
* Return:
*   User menu selection:    Data type: Integer.
*                           Return the int that corresponds to the menu selection by the user.
**********************************************************************/

int getUserMenuSelectionInteger() {

  cout << "\nExpense Tracking Menu:\n";
  cout << "1. show all\n";
  cout << "2. spend\n";
  cout << "3. search expenses containing this string\n";
  cout << "4. search expenses with greater than or equal to this amount\n";
  cout << "5. exit\n";
  cout << "Enter your option: ";

  string buf;
  cin >> buf;
  int userMenuSelectionInt = atoi(buf.c_str());
  // If the user did not enter a number, print out a message warning the user.
  printWarningIfUserEnteredWrongInput(atoi(buf.c_str()));

  return userMenuSelectionInt;

}




/*********************************************************************
* Function: User Menu Functions Function: Based on the user's menu selection integer
*           previously, get user input and store into array or perform other
*           (based on user input selection).
*
* Based on the user menu selection, perform one of the following functions:
* o Display all elements in the array
* o Get user input
* o Search for a string in the array
* o Search for a number in the array
* o Exit
*
* Parameter:
*   1) User menu selection  Data type: int
*                           Integer signifying which menu option was selected by the user.
*                           Pass-By-Value
*
*   2) Expense struct array Data type: User defined struct array
*                           Array elements are of the user defined data type Expense struct
*                           Pass-By-Reference (as arrays are always pass-by-ref)
*
*   3) Array index          Data type: int
*                           Current array index
*                           Pass-By-Value
*
*   4) Array capacity       Data type: int
*                           Max array capacity is passed to the function.
*                           Pass-By-Value
*
* Return:
*   Current array index:    Data type: Int.
*                           Return the int that corresponds to the current array index.
*                           From this index onwards, the on coming elements will be stored into the array.
*
* Why return only array index and not the whole array?:
* ----------------------------------------------------
* I am getting user input and storing it into the array. Since array in C++ always Pass-By-Reference,
* I don't have to return the array back to main(), returning only the current array index suffices.
**********************************************************************/

int menuFunctions(int userMenuSelectionInteger, Expense expenseData[], int expenseDataArrayIndex, int arrayCapacity) {

  //-----------------------------------------------------------------------
  // User menu selection # 1:
  // Print everything when the user selects option 1 from the menu.
  //-----------------------------------------------------------------------
  if (userMenuSelectionInteger == 1) {
    if (expenseData[0].expenseAmount == -100)
      cout << "\nThere is no expense entry available.\n";
    else
      printOutputStringStream(userMenuSelectionInteger, expenseData, expenseDataArrayIndex, arrayCapacity);
  }



  //-----------------------------------------------------------------------
  // User menu selection # 2:
  // Get input from the user about the expenses when the user selects option 2 from the menu.
  //-----------------------------------------------------------------------
  if (userMenuSelectionInteger == 2 && expenseDataArrayIndex < arrayCapacity) {
    // Ignore 200 chars max, or newline is read
    // use cin.ignore after every cin >> and before getline()
    // Because during the next call to this function, getline() would follow the cin above,
    // so the following cin.ignore is needed.
    cin.ignore(200, '\n');

    // Keep asking the user to enter a description if user did not enter any description.
    do {
      cout << "\nPlease enter the description for the expense: ";
      getline(cin, expenseData[expenseDataArrayIndex].expenseDescription);

      if (expenseData[expenseDataArrayIndex].expenseDescription == "") {
        cout << "Description cannot be empty.\n";
      }
    } while (expenseData[expenseDataArrayIndex].expenseDescription == "");

    // Keep asking the user to enter a valid # if the user did not enter one.
    do {
      cout << "Please enter the amount: ";
      string buf;
      cin >> buf;
      expenseData[expenseDataArrayIndex].expenseAmount = atof(buf.c_str());
      // If the user did not enter a number, print out a message warning the user.
      printWarningIfUserEnteredWrongInput(atof(buf.c_str()));
      if (expenseData[expenseDataArrayIndex].expenseAmount <= 0) {
        cout << "Invalid amount. Amount cannot be negative or string. Please try it again.\n\n";
      }
    } while (expenseData[expenseDataArrayIndex].expenseAmount <= 0);


    // Ignore 200 chars max, or newline is read
    // use cin.ignore after every cin >> and before getline()
    // Because during the next call to this function, getline() would follow the cin above,
    // so the following cin.ignore is needed.
    cin.ignore(200, '\n');

    // Increment the array index by 1, so that the next array entry can be stored in the next array index.
    expenseDataArrayIndex++;

    // Print only the current entry.
    printOutputStringStream(userMenuSelectionInteger, expenseData, expenseDataArrayIndex, arrayCapacity);
  }



  //-----------------------------------------------------------------------
  // User menu selection # 3:
  // Get input from the user about the string to search for, when the user selects option 3 from the menu.
  //-----------------------------------------------------------------------
  if (userMenuSelectionInteger == 3) {
    // Ignore 200 chars max, or newline is read
    // use cin.ignore after every cin >> and before getline()
    // Because during the next call to this function, getline() would follow the cin above,
    // so the following cin.ignore is needed.
    cin.ignore(200, '\n');

    // Ask the user for a string to search in the array.
    string searchString;
    cout << "\nPlease enter the search string: ";
    getline(cin, searchString);

    // The search must be case insensitive. So, the user entry must be converted to either upper
    // or lowercase. Here, it's converted to lowercase.
    searchString = toSmallLetters(searchString);

    // Print all array elements that match the string entered by the user.
    printOutputStringStream(userMenuSelectionInteger, expenseData, expenseDataArrayIndex, arrayCapacity, searchString);
  }



  //-----------------------------------------------------------------------
  // User menu selection # 4:
  // Get input from the user about the # to search for, when the user selects option 4 from the menu.
  //-----------------------------------------------------------------------
  if (userMenuSelectionInteger == 4) {
    string buf;
    cout << "\nPlease enter the amount: ";
    cin >> buf;
    double searchAmount = atof(buf.c_str());
    // If the user did not enter a number, print out a message warning the user.
    printWarningIfUserEnteredWrongInput(atof(buf.c_str()));

    // Print all array elements that match the # entered by the user.
    printOutputStringStream(userMenuSelectionInteger, expenseData, expenseDataArrayIndex, arrayCapacity, "nulll", searchAmount);
  }

  // Return that array index, so that the next array entry can be stored in the that array index.
  return expenseDataArrayIndex;

} // menuFunctions







/*********************************************************************
* Function: Print warning is user entered string instead of number
*           for courseYear and courseUnits.
*
* Previously, cin was used to get string buffer input which are later converted to numbers.
* Previously, atoi() and/or atof() were used to convert string buffers into numbers.
* If the user did not enter a number, here, this function prints out a message warning the user.
*
*
* Parameter:
*   User input result:      Data type: int. Success or failure result of atoi(buf.c_str()).
*                           Pass-by-Value
*
* Return:
*   None.
**********************************************************************/

void printWarningIfUserEnteredWrongInput(int resultOfUserInput) {

  if (!resultOfUserInput) {
    cout << "! ! ! ! ! ! ! ! ! ! ! ! ! ! ! ! ! ! ! ! ! ! ! ! ! ! ! ! ! ! ! ! ! ! ! ! ! ! ! ! ! ! ! !\n";
    cout << "You entered zero or a non-number, so your input will be considered as if you entered a zero.\n";
    cout << "! ! ! ! ! ! ! ! ! ! ! ! ! ! ! ! ! ! ! ! ! ! ! ! ! ! ! ! ! ! ! ! ! ! ! ! ! ! ! ! ! ! ! !\n\n";
  }

}







/*********************************************************************
* Function: Print output string stream based on user menu selection.
*
* Based on the user menu selection, perform one of the following functions:
* o Print all elements in the array.
* o Print just the current user entry.
* o Search for a string in the array and print all elements that match that string.
* o Search for a number in the array and print all elements that match that #.
*
* Parameter:
*   1) User menu selection  Data type: int
*                           Integer signifying which menu option was selected by the user.
*                           Pass-By-Value
*
*   2) Expense struct array Data type: User defined struct array
*                           Array elements are of the user defined data type Expense struct
*                           Pass-By-Reference (as arrays are always pass-by-ref)
*
*   3) Array index          Data type: int
*                           Current array index
*                           Pass-By-Value
*
*   4) Array capacity       Data type: int
*                           Max array capacity is passed to the function.
*                           Pass-By-Value
*
*   5) String to be found   Data type: string
*                           String to be found is passed to the function.
*                           Pass-By-Value
*
*   4) $ Amount to be found Data type: double
*                           Dollar amount to be found is passed to the function.
*                           Pass-By-Value
*
* Return:
*   None
**********************************************************************/

void printOutputStringStream(int userMenuSelection, Expense expenseArray[], int arrayIndex, int arrCap, string findString, double findAmount) {

  // Instead of just directly using cout, output string stream is used here to first store the
  // output and then finally print out the string stream.
  ostringstream outString;
  outString.clear();

  // for loop to print the array.
  for (int i = 0; i < arrayIndex && arrayIndex <= arrCap; i++) {

    bool shouldPrint = false;

    // If the user enters 1, print all non-empty array elements.
    if (userMenuSelection == 1)
      shouldPrint = true;

    // If the user enters 2, print only the currently entered array element.
    if (userMenuSelection == 2) {
      i = arrayIndex - 1;
      shouldPrint = true;
    }

    // If the user enters 3, print all array elements that match the search string entered by the user.
    if (findString != "nulll") {
      // BOTH array element description string and the target string are converted to lowercase, so that
      // mixed cases such as "SEarch" can be caught.
      string arrayElementInLowerCase = toSmallLetters(expenseArray[i].expenseDescription);
      int searchIndex = arrayElementInLowerCase.find(findString);
      // Test for findString match
      if (searchIndex != string::npos)
        shouldPrint = true;
    }

    // If the user enters 4, print all array elements that match the # entered by the user.
    if (findAmount != -1) {
      // Test for findAmount match
      if (expenseArray[i].expenseAmount >= findAmount)
        shouldPrint = true;
    }

    // Common output string stream which will be printed if any of the 'if condition' above is met.
    if (shouldPrint) {
      outString << "AMOUNT(" << expenseArray[i].expenseAmount << ") DESC("
                << expenseArray[i].expenseDescription << ")" << "\n";
      if (userMenuSelection == 2)
        break;
    }

  } // for loop

  cout << outString.str();

}







/*********************************************************************
* Function: Converts a string to a string of all lower case letters.
*
* Takes a string as a parameter, converts it to a lower case string, and returns.
*
* Parameter:
*   String               Data type: string
*                        A string that's to be converted to a string of all lower case letters.
*                        Pass-By-Value
*
* Return:
*   String:             Data type: string
*                       Return the string that's been converted to a string of all lower case letters.
**********************************************************************/

string toSmallLetters(string aString) {

  int stringLength = aString.length( );
  for (int i = 0; i < stringLength; i++)
    // Convert the characters of the string to lowercase, one character by one character.
    aString[i] = tolower(aString[i]);
  return aString;

}






/*********************************************************************
* Function: Identifying information in cout form similar to
* sample-comment.cpp is provided here.
*
* Parameters:
*   labDescription: Data type: string.
*                   Pass-by-Value.
*                   Lab description is passed as the string parameter.
*
* Return: None.
**********************************************************************/

// Identifying information in comment form is included at the top of this file.
// Here, identifying information in cout form similar to sample-comment.cpp is provided.

void printIdentification(string labDescription) {

  cout << "######################################################################\n";
  cout << "\t\t\tIdentifying Information\n";
  cout << "######################################################################\n";

  // Width of 20 and left alignment are set here, so the output will be nicely aligned.
  cout.setf(ios::left);
  cout.width(20); cout << "Name:" << "Sunny Anand\n";
  cout.width(20); cout << "Course: " << "Previously taken course\n";
  cout.width(20); cout << "Lab Description: " << labDescription;
  cout.width(20); cout << "Editor(s) used: " << "CodeBlocks\n";
  cout.width(20); cout << "Compiler(s) used: " << "G++\n";
  cout.width(20); cout << "File: " << __FILE__ << "\n";
  cout.width(20); cout << "Compiled: " << __DATE__ << " at " << __TIME__ << "\n\n";

  cout << "______________________________________________________________________\n\n";
  cout << "\t\tNow the actual program execution\n";
  cout << "______________________________________________________________________\n\n";

}
