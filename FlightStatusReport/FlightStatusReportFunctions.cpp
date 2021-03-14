/* Header Files */
#include "FlightStatusReportHeader.h"   // this file's function prototypes
#include "../Utils/utilsTS.h"                    // custom utils file

/* Symbolic Constants */
#define MENU_TITLE      "Flight Status Report Menu"   // Title for menu
#define ARRIVALS_0      "Arrivals Report"             // First option on menu
#define DEPARTURES_1    "Departures Report"           // Second option on menu
#define ARRIVALS        "Data/Arrivals.txt"                // Arrival Data
#define DEPARTURES      "Data/Departures.txt"              // Departure Data
#define DEPARTURE_TITLE "AA Airlines Departure Information Into LAX Los Angeles"
#define ARRIVAL_TITLE   "AA Airlines Arrival Information Into LAX Los Angeles"


/********************************************************
 * Main Driver Module:
 * Called in 'FlightSatusReport.cpp'
 *******************************************************/
void flightStatusReportMenu()
{
   // After adding value to symbolic constant add 'OPTION#' to array
   // Program will automatically grab first letter of option and use it as command
   string optionPrompts[] = { 
      ARRIVALS_0, 
      DEPARTURES_1, 
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
      (validChoice) ? decisionHandler(menuChoice, quitMenu) : inputError(INVALID_ENTRY);
   } while (!quitMenu);

}

/********************************************************
 * Processing Function:
 * Determines which input was entered, after validation
 *******************************************************/
void decisionHandler(char choice, bool &quit)
{
   // Manages menu options
   switch(choice) {
      case 'A':
         arrivalOption0();
         break;
      case 'D':
         departureOption1();
         break;
      case 'Q':
         quit = quitOption();
         break;
      default:
      print("ERROR INVALID ENTRY IN D.H.");
         exit(EXIT_FAILURE);
         break;
   }
   // Resets any extra inputs after he single char required
   if (choice != 'Q') resetStreamBuffer();
}

/********************************************************
 * Processing Module:
 * Calls processing / output modules 
 * for "Arrivals" option
 *******************************************************/
void arrivalOption0()
{
   displayOptionHeader(ARRIVAL_TITLE);
   // Handles Depature file input reading / processing
   fileInput(ARRIVALS);
}

/********************************************************
 * Processing Module:
 * Calls processing / output modules 
 * for "Departures" option
 *******************************************************/
void departureOption1()
{
   // Displays menu option header
   displayOptionHeader(DEPARTURE_TITLE);
   // Handles Depature file input reading / processing
   fileInput(DEPARTURES);
}

/********************************************************
 * Processing Module:
 * Handles file input
 *******************************************************/
void fileInput(string filename) 
{
   // stores in stream file
   ifstream inFile;
   // flight#, gate#, airport location, scheduled time, actual time
   string flightData[FLIGHT_FIELDS];
   // Calculated delay   
   int delay;               
   //open the file 
   bool ok = openFile(filename, inFile);
   //if open successfully
   if (ok) {
      displayFlightInfoHeader();
      //while there are data sets
      string line;
      while (getline(inFile, line)) {
         // Reads all input within a given file
         dataInput(inFile, flightData);
         //calculate delay
         delay = calculateActual(stoi(flightData[3]), stoi(flightData[4]));
         // displays all flight info
         displayFlightInfo(flightData, delay);
      }
      inFile.close();
      newLine();
   }
}

/*******************************************************************************
 * Processing Function:
 * Checks if file is available
 ******************************************************************************/
bool openFile(string filename, ifstream &inFile)
{
   inFile.open(filename);
   if (inFile.fail()) {
      print("File Error: Please exit the application", true, 2);
      return false;
   }
   return true;
}

/*******************************************************************************
 * Processing Function
 * 
 * Checks the status of the file being processed
 ******************************************************************************/
bool checkFile(ifstream &inFile)
{
   if (inFile.fail() || inFile.eof()) return false;
   else return true;
}

/*******************************************************************************
 * Input Module: 
 * Assigns data from input file to corresponding variable
 ******************************************************************************/
void dataInput(ifstream &inFile, string flightData[])
{
   for (short i = 0; i < FLIGHT_FIELDS; i++) {
      inFile >> flightData[i];
   }
}

/*******************************************************************************
 * Processing Function
 * 
 * Calculates actual based on the 'scheduled' time of arrival compared to the 
 * 'actual' time
 ******************************************************************************/
int calculateActual(int scheduled, int actual)
{
   int diff = 0;
   int timeData[2] = { scheduled, actual };
   int tempData[2];

   if (scheduled != actual) {
      for (int i = 0; i < 2; i++) {
         //divide tempActual by 100
         tempData[i] = timeData[i] / 100;
         // if tempActual equals 12, set it to 0
         if (i) {
            if (tempData[1] == 12 && tempData[0] >= 1200) tempData[1] = 0; 
         } else {
            if (tempData[0] == 12) tempData[0] = 0; 
         }
         // multiply tempActual by 60 and add actual%100
         tempData[i] = (tempData[i] * 60) + (timeData[i] % 100);
         //calculate difference between tempActual and tempScheduled
      }

      //calculate difference between tempActual and tempScheduled
      diff = tempData[1] - tempData[0];
   }
   return diff;
}

/*******************************************************************************
 * Output Module:
 * Displays the flight data column headers
 ******************************************************************************/
void displayFlightInfoHeader()
{
   const string columns[] = {
      "Flight#", "Gate#", "Airport", 
      "Scheduled", "Expected", "Delay"
   };
   short columnCount = sizeof(columns)/sizeof(columns[0]);
   for (int col = 0; col < columnCount; col++) {
      short len = columns[col].length();
      // adds extra space for airport column
      if (col == 2) len += 10;
      // prints 
      cout << setw(len) << right << columns[col];
      // empty space after each header
      print(BLANK_CHAR);
   }
   newLine(2);
}

/*******************************************************************************
 * Output Module:
 * Displays the flight data column headers
 ******************************************************************************/
void displayFlightInfo(string flightData[], int delay)
{  
   cout << setw(7) << right << flightData[0] // flight#
        << setw(6) << right << flightData[1] // gate#  
        << setw(18)  << flightData[2] // airport location  
        << setw(10)  << flightData[3] // scheduled time
        << setw(9)   << flightData[4] // actual time
        << setw(6)   << delay;
   newLine();
}