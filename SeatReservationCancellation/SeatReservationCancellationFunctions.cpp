/* Header Files */
#include "SeatReservationCancellationHeader.h" // this file's function prototypes 
#include "../Utils/utilsTS.h"                  // custom utils file

/* Symbolic Constants */
#define PADDING         2
#define CHAR_ONE        49
#define CHAR_A          65
#define MENU_TITLE      "Seat Reservation and Cancellation Menu"  // Title for menu
#define DISPLAY_0       "Display Avaliable Seats"                 // First option on menu
#define RESERVE_1       "Reserve Seat"                            // Second option on menu
#define CANCEL_2        "Cancel Seat"                             // Third option on menu
#define INVALID_ENTRY   "Invalid Entry!"                          // Invalid entry text
#define EMPTY_SEAT      ' '                                       // Symbol used to indicate an empty seat
#define BOOKED_SEAT     'X'                                       // Symbol used to indicate an empty seat

/*******************************************************************************
 * Main Driver Module:
 * Called in 'SeatReservationCancellation.cpp'
 *******************************************************************************/
void seatReservationCancellationMenu()
{
   // After adding value to symbolic constant add 'OPTION#' to array
   // Program will automatically grab first letter of option and use it as command
   string optionPrompts[] = { 
      DISPLAY_0, 
      RESERVE_1,
      CANCEL_2,
      QUIT
   };

   // Calculates and stores quantity of menu options
   short optionCount = sizeof(optionPrompts)/sizeof(optionPrompts[0]);
   // Stores menu option key value pairs
   char optionKeys[optionCount];
   // Pushes first char of each option string to be the menu key value
   for (short i = 0; i < optionCount; i++) {
      optionKeys[i] = toupper(optionPrompts[i].at(0));
   }
   // Stores Row Indicators
   char seatingRows[ROWS];
   for (short row = 0; row < ROWS; row++)
      seatingRows[row] = ' ';
   // Stores Column Indicators
   char seatingColumns[COLUMNS];
   for (short col = 0; col < COLUMNS; col++)
      seatingColumns[col] = ' ';
   // 2D Array that stores reserved seating indicators
   char seatingArr[ROWS][COLUMNS];
   for (short row = 0; row < ROWS; row++) {
      for (short col = 0;  col < COLUMNS; col++)
         seatingArr[row][col] = ' ';
   }
   // populates seating arrays
   setupSeats(seatingRows, seatingColumns, seatingArr);
   // calculates total seat count
   short totalSeats = ROWS * COLUMNS;
   // Controls looping of current menu
   bool quitMenu = false;
   // Main loop continues until 'Q' quit option is chosen
   do {
      // Display main menu options
      decisionsDisplay(MENU_TITLE, optionPrompts, optionKeys, optionCount);
      // User input's menu option
      char menuChoice = enterChoice();
      // Verifys user input was valid menu option
      bool validChoice = checkChoice(menuChoice, optionPrompts, optionCount);
      // Tests for valid entry
      if (validChoice) { 
         decisionHandler(menuChoice, seatingRows, seatingColumns, 
            seatingArr, totalSeats, quitMenu); 
      } else { inputError(INVALID_ENTRY); }
   } while (!quitMenu);
}

/*******************************************************************************
 * Driver Module:
 * Calls modules to setup initial seating setting based
 * on predetermined symbolic constants
 *******************************************************************************/
void setupSeats(char seatingRows[ROWS], char seatingColumns[COLUMNS], char seatingArr[ROWS][COLUMNS])
{
   // Creates Row Indicators / Parallel to seatingArr's 'ROWS' array
   linearCounter(CHAR_ONE, (CHAR_ONE + (ROWS-1)), seatingRows);
   // Creates Column Indicators / Parallel to seatingArr's 'COLUMNS' arrayZ
   linearCounter(CHAR_A, (CHAR_A + (COLUMNS-1)), seatingColumns);
   // Sets all seats to avaliable
   seatGenerator(seatingArr);
}

/*******************************************************************************
 * Processing Module:
 * Populates main seating array with empty seats
 *******************************************************************************/
void seatGenerator(char seatingOutput[ROWS][COLUMNS])
{
   for (short row = 0; row < ROWS; row++) {
      for (short col = 0; col < COLUMNS; col++)
         seatingOutput[row][col] = EMPTY_SEAT;
   }   
}

/*******************************************************************************
 * Processing Module:
 * creates array of chars from a specified starting ascii
 * to a specified ending in linear order
 *******************************************************************************/
void linearCounter(short start, short finish, char countOutput[])
{
   short count = 0;
   for (short current = start; current <= finish; current++, count++)
      countOutput[count] = static_cast <char> (current);
}

/*******************************************************************************
 * Output Module:
 * Main menu options, displays input prompt/options
 *******************************************************************************/
void seatReservationAndCancellationMenuDisplay(string optionPrompts[], char optionKeys[], short count)
{
   // Displays menu title to screen
   displayOptionHeader(MENU_TITLE);

   // Loops through the menu options and prints for user selection
   for (short i = 0; i < count; i++) {
      print(optionPrompts[i]);
      short optionLen = optionPrompts[i].size();
      cout << setw(LINE_WIDTH - optionLen);
      print(DELIMITER);
      print(optionKeys[i], true);
   }
}

/*******************************************************************************
 * Processing Function:
 * Determines which input was entered, after validation
 *******************************************************************************/
void decisionHandler(char choice, char seatingRows[], char seatingColumns[], 
   char seatingArr[ROWS][COLUMNS], short totalSeats, bool &quit)
{
   
   // Manages menu options
   switch(choice) {
      case 'D':
         displaySeatsOption0(seatingRows, seatingColumns, seatingArr);
         break;
      case 'R':
         seatReservation1(seatingRows, seatingColumns, seatingArr);
         break;
      case 'C':
         seatCancellation2(seatingRows, seatingColumns, seatingArr);
         break;
      case 'Q':
         quit = quitOption();
         break;
      default:
         print("ERROR INVALID ENTRY IN D.H.");
         exit(EXIT_FAILURE);
         break;
   }
   // Resets any extra inputs after the single char required
   if (!quit) { 
      resetStreamBuffer();
      displayAvaliableSeats(seatingArr, totalSeats);
      newLine(2); 
   }
}

/*******************************************************************************
 * Driver Module:
 * Manages/calls the modules that display 
 * current seating statuses 
 *******************************************************************************/
void displaySeatsOption0(char seatingRows[], char seatingColumns[], char seatingArr[ROWS][COLUMNS])
{
   displayOptionHeader("Seat Chart");
   displayColumnHeader(seatingColumns);
   displayRows(seatingRows, seatingArr);
   newLine();
}

/*******************************************************************************
 * Driver Module:
 * Manages/calls the functions that set reservations
 *******************************************************************************/
void seatReservation1(char seatingRows[], char seatingColumns[], char seatingArr[ROWS][COLUMNS])
{
   if (calculateAvaliableSeats(seatingArr) == 0)
   {
      print("This flight is full!", true);
   } else {
      // user indicated row
      short  rowInput = getSeatRow(seatingRows);                       
      // user indicated column
      char columnInput = getSeatColumn(seatingColumns);              
      // tracks column number
      short columnNumber = static_cast <short> (columnInput) - CHAR_A;  
      newLine(); 
      // generates seat ID
      string seat = getSeat(rowInput, columnInput);
      // reserves seat if it is avaliable
      bookSeat(seatingArr, rowInput, columnNumber, seat);
   }
}

/*******************************************************************************
 * Driver Module:
 * Manages/calls the functions that cancel reservations
 *******************************************************************************/
void seatCancellation2(char seatingRows[], char seatingColumns[], char seatingArr[ROWS][COLUMNS])
{
   if (calculateAvaliableSeats(seatingArr) == (ROWS * COLUMNS))
   {
      print("This flight is empty!", true);
   } else {
      // user indicated row
      short  rowInput = getSeatRow(seatingRows);                       
      // user indicated column
      char columnInput = getSeatColumn(seatingColumns);              
      // tracks column number
      short columnNumber = static_cast <short> (columnInput) - CHAR_A;   
      newLine();
      // generates seat ID
      string seat = getSeat(rowInput, columnInput);
      // reserves seat if it is avaliable
      cancelSeat(seatingArr, rowInput, columnNumber, seat);
   }
}

/*******************************************************************************
 * Processing Module:
 * Exits program with successful exit code
 *******************************************************************************/
void quitOption3()
{
   print(QUIT_MSG, true, 2);
   exit(EXIT_SUCCESS);
}

/*******************************************************************************
 * Output Module:
 * Displays/formats column indicators
 *******************************************************************************/
void displayColumnHeader(char seatingColumns[])
{
   // Prints column indicators
   for (short col = 0; col < COLUMNS; col++) {
      if (col == 0) print("  ");
      
      char seatCol = seatingColumns[col];
      print(seatCol);
   }
   newLine();
}

/*******************************************************************************
 * Output Module:
 * Displays/formats current rows indicator as well as 
 * seat avaliablity for eachg column in the row
 *******************************************************************************/
void displayRows(char seatingRows[], char seatingArr[ROWS][COLUMNS])
{
   for (short row = 0; row < ROWS; row++) {
      char seatRow = seatingRows[row];
      // labels each row
      print(seatRow);
      // prints seperator
      print(' ');
      // Displays the current column/row intersection's availablity
      displayCurrentSeating(row, seatingArr);
      // breaks line after the last column per row
      // until the end of the last row
      if (row < ROWS-1) newLine();
   }
}

/*******************************************************************************
 * Output Module:
 * Displays current seat in interation's avaliability
 *******************************************************************************/
void displayCurrentSeating(short currentRow, char seatingArr[ROWS][COLUMNS])
{
   // iterates through each column of the currentRow
   for (short col = 0; col < COLUMNS; col++) {
      char current = seatingArr[currentRow][col];
      // prints the current assignment of the indicated seat
      print(current);
   }
}

/*******************************************************************************
 * Output Module:
 * Displays current seat availability count
 *******************************************************************************/
void displayAvaliableSeats(char seatingArr[ROWS][COLUMNS], short totalSeats)
{
   cout << "There are " << calculateAvaliableSeats(seatingArr) 
        << " out of " << totalSeats << " seats avaliable";
}

/*******************************************************************************
 * Processing Module:
 * Counts how many seats are empty
 *******************************************************************************/
short calculateAvaliableSeats(char seatingArr[ROWS][COLUMNS])
{
   short seatCount = 0;
   for (short row = 0; row < ROWS; row++)
      for (short col = 0; col < COLUMNS; col++)
         if (seatingArr[row][col] == EMPTY_SEAT) 
            seatCount++;
   return seatCount;
}

/*******************************************************************************
 * Processing Module:
 * Returns a specified seat ID in the format [RowColumn]
 *******************************************************************************/
string getSeat(short rowNum, char colLtr) 
{
   string seat = "";
   seat += static_cast <char>(rowNum+CHAR_ONE-1);
   return seat += colLtr;
}

/*******************************************************************************
 * Input Module:
 * Prompts and validates user row input
 *******************************************************************************/
short getSeatRow(char seatingRows[])
{
   bool validInput = false;                   // tracks if input is in bounds
   short row;
   // converts first row number from chat val to short val
   short  firstRow = seatingRows[0] - CHAR_ONE + 1;
   // converts last row number from chat val to short val
   short  lastRow = seatingRows[ROWS-1] - CHAR_ONE + 1;

   do {
      cout << "Please enter the row number " << firstRow << '-' << lastRow << ": ";
      cin >> row;
      if (!cin.fail()) validInput = (row < firstRow || row > lastRow) ? false : true;
      if (!validInput) inputError(INVALID_ENTRY);
   } while (!validInput);
   return row;
}

/*******************************************************************************
 * Input Module:
 * Prompts and validates user column input
 *******************************************************************************/
char getSeatColumn(char seatingColumns[])
{
   bool validInput = false;                              // tracks if input is in bounds
   char column;                                          // stores user column input
   char firstColumn = seatingColumns[0];                 // reference to first column
   char lastColumn = seatingColumns[COLUMNS-1];          // reference to last column

   do {
      cout << "Please enter the column number " << firstColumn << '-' << lastColumn << ": ";
      cin >> column;
      column = toupper(column);
 
      if (cin.fail()) {
         validInput = false;
      } else {
         for (short i = 0; i < COLUMNS; i++) {
            validInput = (seatingColumns[i] == column);
            if (validInput) i = COLUMNS;
         }
      }
      if (!validInput) inputError(INVALID_ENTRY);       
   } while (!validInput);

   return column;
}

/*******************************************************************************
 * Processing Module:
 * Reserves seat if available
 *******************************************************************************/
void bookSeat(char seatingArr[ROWS][COLUMNS], short rowNum, short colNum, string seat)
{
   if (seatCheck(seatingArr, rowNum, colNum)) {
      seatingArr[rowNum-1][colNum] = BOOKED_SEAT;
      cout << "Congratulations! You've successfully booked seat: " << seat;
   } else {
      cout << "Sorry, seat " << seat << " is not avaliable.";
   }
   newLine();
}

/*******************************************************************************
 * Processing Module:
 * Cancels seat if reserved
 *******************************************************************************/
void cancelSeat(char seatingArr[ROWS][COLUMNS], short rowNum, short colNum, string seat)
{
   if (!seatCheck(seatingArr, rowNum, colNum)) {
      seatingArr[rowNum-1][colNum] = EMPTY_SEAT;
      cout << "Congratulations! You've successfully cancelled seat: " << seat;
   } else {
      cout << "Sorry, seat " << seat << " has not been booked.";
   }
   newLine();
}

/*******************************************************************************
 * Processing Module:
 * Determines if seat is avaliable or not
 * Returns false is unavailable, true is available
 *******************************************************************************/
bool seatCheck(char seatingArr[ROWS][COLUMNS], short rowNum, short colNum)
{
   if (seatingArr[rowNum-1][colNum] == EMPTY_SEAT) return true;
   return false;
}