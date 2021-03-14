#include "utilsTS.h"

/********************************************************
 * Output Module:
 * Displays chosen option header
 *******************************************************/
void displayOptionHeader(string menuTitle)
{
   // Stores length of line for border width
   unsigned short int lineWidth;
   // Stores the value of the menu length
   unsigned short int menuTitleLength = menuTitle.length();
   // Determines how long the line must be based on which menu is entered
   (menuTitleLength > LINE_WIDTH) ? lineWidth = FLIGHT_TITLE : lineWidth = LINE_WIDTH;
   // Calculates total margin char length
   unsigned short int totalMargin = (lineWidth - menuTitleLength);
   // Initial margin which prefix's menutitle
   unsigned short int marginPrefix = ( totalMargin / 2);
   // Creates string for each menu border length with constant border char
   string menuBorder(lineWidth, BORDER_SYM);
   // Creates a margin to prefix menu title
   string menuMargin(marginPrefix, BLANK_CHAR);

   print(menuBorder, true);
   print(menuMargin);
   print(menuTitle, true);
   print(menuBorder, true, 2);
}
/********************************************************
 * Output Module:
 * Main menu options, displays input prompt/options
 *******************************************************/
void decisionsDisplay(string title, string optionPrompts[], char optionKeys[], int count)
{
   // Displays menu title to screen
   displayOptionHeader(title);

   // Loops through the menu options and prints for user selection
   for (int i = 0; i < count; i++) {
      print(optionPrompts[i]);
      int optionLen = optionPrompts[i].size();
      cout << setw(LINE_WIDTH - optionLen);
      print(DELIMITER);
      print(optionKeys[i], true);
   }
}


/********************************************************
 * Input Function:
 * User's choice from main menu
 *******************************************************/
char enterChoice()
{
   // Created variable to get size for output temaplate
   const string prompt = "Enter your choice";
   // User char input
   char choice;
   // Displays prompt
   print(prompt);
   // Sets output template
   cout << setw(LINE_WIDTH - prompt.size());
   // Prints preset delimiter
   print(DELIMITER);
   cin >> choice;
   newLine();

   return toupper(choice);
}

/********************************************************
 * Processing Function:
 * Determines if user entered correct key from menu
 *******************************************************/
bool checkChoice(char choice, string options[], int count)
{
   for (int i = 0; i < count; i++) {
      if (choice == toupper(options[i].at(0))) return true;
   }
   return false;
}

/******************************************************************************
 * Output Module:
 * Manages input errors / outputs err messages
 *****************************************************************************/
void inputError(string errMessage)
{
   print(errMessage, true, 2);
   cin.clear();
   resetStreamBuffer();
}

/******************************************************************************
 * Overloaded Output Modules:
 * Short hand for outputting single line strings and the ability to add 
 * single/multiple line breaks as optional parameters. 
 * endLine = false by default; true will add a single line break
 * count = 1 by default; any number(count) will skip (count - 1) lines.
 * Only passing a string arg will output the string with no line breaks.
 *****************************************************************************/
void print(string message, bool endLine, int count)
{
   cout << message;
   if (endLine) newLine(count);
}

void print(char ch, bool endLine, int count)
{
   cout << ch;
   if (endLine) newLine(count);
}

void print(int data, bool endLine, int count)
{
   cout << data;
   if (endLine) newLine(count);
}

void print(double data, bool endLine, int count)
{
   cout << data;
   if (endLine) newLine(count);
}

/******************************************************************************
 * Output Module:
 * Calling newLine() without parameters results in a single endl.
 * count = 1 by default; any number(count) will skip (count - 1) lines.
 *****************************************************************************/
void newLine(int count)
{
   if (count > 1) {
      for (int i = 0; i < count; i++) {
         cout << endl;
      }
      return;
   }
   if (count == 1) cout << endl;
}

void resetStreamBuffer()
{
   cin.ignore(10000,'\n');
}

bool yesOrNo(string prompt)
{
   char answer;
   do {
      print(prompt, true);
      cin >> answer;
      answer = tolower(answer);
      if (answer != 'y' && answer != 'n') inputError("Invalid Entry!");
   } while(answer != 'y' && answer != 'n');

   return tolower(answer) == 'y' ? true : false;
}

/********************************************************
 * Processing Module:
 * Exits program with successful exit code.
 *******************************************************/
bool quitOption()
{
   print(QUIT_MSG, true, 2);
   return true;
}