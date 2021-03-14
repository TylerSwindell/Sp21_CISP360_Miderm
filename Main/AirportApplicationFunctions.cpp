/* Header Files */
#include "AirportApplicationHeader.h"
#include "../SeatReservationCancellation/SeatReservationCancellationHeader.h"
#include "../EmergencyDecisions/EmergencyDecisionsHeader.h"
#include "../FlightStatusReport/FlightStatusReportHeader.h"
#include "../MovieSelection/MovieSelectionHeader.h"
#include "../Utils/utilsTS.h"

/* Symbolic Constants */
/* Symbolic Constants */
#define MENU_TITLE        "Airport Application Main Menu"  // Title for menu
#define EMERGENCY_0       "Emergency Decisions in Flight"  // First option on menu
#define FLIGHTSTATUS_1    "Flight Status Report"           // Second option on menu
#define SEATRESERVATION_2 "Seat Reservation/Cancellation"  // Third option on menu
#define MOVIE_SELECT_3     "Movie Selection in Flight"  // Fourth option on menu

/*******************************************************************************
 * Main Driver Module:
 * TODO: Desc
 *******************************************************************************/
void airportApplicationMenu()
{   
   // After adding value to symbolic constant add 'OPTION#' to array
   // Program will automatically grab first letter of option and use it as command
   string optionPrompts[] = { 
      EMERGENCY_0,
      FLIGHTSTATUS_1,
      SEATRESERVATION_2,
      MOVIE_SELECT_3,
      QUIT
   };

   // Calculates and stores quantity of menu options
   int optionCount = sizeof(optionPrompts)/sizeof(optionPrompts[0]);
   // Stores menu option key value pairs
   char optionKeys[optionCount];

   // Pushes first char of each option string to be the menu key value
   for (int i = 0; i < optionCount; i++) {
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
      (validChoice) ? airportDecisionHandler(menuChoice, quitMenu) : inputError(INVALID_ENTRY);
   } while (!quitMenu);
   if (quitMenu) exit(EXIT_SUCCESS);
}

/*******************************************************************************
 * Driver Module:
 * TODO: Desc
 *******************************************************************************/

/*******************************************************************************
 * Input Function:
 * TODO: Desc
 *******************************************************************************/

/********************************************************
 * Processing Function:
 * Determines which input was entered, after validation
 *******************************************************/
void airportDecisionHandler(char choice, bool &quit)
{
   //displayOptionHeader(MENU_TITLE);
   // Matches input to 
   switch(choice) {
      case 'E':
         emergencyDecisionsMenu();
         break;
      case 'F':
         flightStatusReportMenu();
         break;
      case 'S':
         seatReservationCancellationMenu();
         break;
      case 'M':
         movieSelectionMenu();
         break;
      case 'Q':
         quit = quitOption();
         break;
      default:
      print("ERROR INVALID ENTRY IN D.H.");
         exit(EXIT_FAILURE);
         break;
   }
   if (choice != 'Q') resetStreamBuffer();
}