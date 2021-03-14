#pragma once

#include <iostream>
#include <iomanip>
using namespace std;

#define LINE_WIDTH      40                // Longest line + DELIMITER
#define FLIGHT_TITLE    56                // Width of menu option tables
#define YES             'Y'               // for 'Yes' option
#define NO              'N'               // for 'No' option
#define QUIT            "Quit"            // Fourth option on menu   
#define QUIT_MSG        "Good Bye!"       // Easily changable exit text
#define INVALID_ENTRY   "Invalid Entry!"  // Invalid entry text
#define DELIMITER       " : "             // Symbol seperator
#define BORDER_SYM      '*'               // Symbols used for borders
#define BLANK_CHAR      ' '               // Space ascii

void decisionsDisplay(string title, string optionPrompts[], char optionKeys[], int count);
char enterChoice();
void displayOptionHeader(string menuTitle);
char enterChoice();
bool checkChoice(char choice, string options[], int count);
void inputError(string errMessage);
void print(string message, bool endLine = false, int count = 1);
void print(char ch, bool endLine = false, int count = 1);
void print(int data, bool endLine = false, int count = 1);
void print(double data, bool endLine = false, int count = 1);
void newLine(int count = 1);
bool quitOption();

/* Utils */
void resetStreamBuffer();
bool yesOrNo(string prompt);