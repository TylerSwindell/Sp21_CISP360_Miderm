/* Header Files */
#include "EmergencyDecisionsHeader.h"   // this file's function prototypes
#include "../Utils/utilsTS.h"                    // custom utils file

/* Symbolic Constants */
#define MENU_TITLE      "Emergency Decisions Menu" // Title for menu
#define COM_FAIL_0      "Communications Failure"   // First option on menu
#define ENG_FAIL_1      "Engine Failure"           // Second option on menu
#define ICING_2         "Inflight Icing"           // Third option on menu

/********************************************************
 * Main Driver Module:
 * Called in 'EmergencyDecisions.cpp'
 *******************************************************/
void emergencyDecisionsMenu()
{
   // After adding value to symbolic constant add 'OPTION#' to array
   // Program will automatically grab first letter of option and use it as command
   string optionPrompts[] = { 
      COM_FAIL_0, 
      ENG_FAIL_1, 
      ICING_2, 
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
      (validChoice) ? emergencyDecisionHandler(menuChoice, quitMenu) : inputError(INVALID_ENTRY);
   } while (!quitMenu);
}

/********************************************************
 * Processing Function:
 * Determines which input was entered, after validation
 *******************************************************/
void emergencyDecisionHandler(char choice, bool &quit)
{
   // Matches input to 
   switch(choice) {
      case 'C':
         comFaliureOption0();
         break;
      case 'E':
         engFailureOption1();
         break;
      case 'I':
         icingOption2();
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

/********************************************************
 * Output Module:
 * Prints message for 'Communication Failure' option
 *******************************************************/
void comFaliureOption0()
{
   print("Switch to alternate radio.", true, 2);
}

/********************************************************
 * Input/Processing/Output Module:
 * Issues a series of questions for user to determine 
 * solution to 'Engine Faliure' menu option
 *******************************************************/
void engFailureOption1()
{
   bool airborne = yesOrNo("Are you airborne?");
   if (airborne) { // airborne == true
      bool electrical = yesOrNo("Is the electrical working?");
      if (electrical) { // electrical == true
         bool engineRunning = yesOrNo("Has the engine stopped?");
         if (engineRunning) { // engineRunning == true
            bool overMountains = yesOrNo("Are you over mountains?");
            if (overMountains) { // overMountains == true
               bool isNight = yesOrNo("Are you flying at night?");
               if (isNight) { // isNight == true
                  print("Turn on the landing light.", true);
                  bool canEmergencyLand = yesOrNo("Do you like what you see?");
                  if (canEmergencyLand) { // canEmergencyLand == true
                     print("Make emergency landing.", true, 2);
                  } else { // canEmergencyLand == false
                     print("Turn off the landing light.", true, 2);
                  }
               } else { // isNight == false
                  print("Make emergency landing.", true, 2);
               } 
            } else {  // overMountains == false
               bool overWater = yesOrNo("Are you over water?");
               if (overWater) { // overWater == true
                  print("Inflate your life vest, make emergency landing.", true, 2);
               } else { // overWater == false
                  print("Make emergency landing on a road.", true, 2);
               }
            }
         } else { // engineRunning == false
            bool isFreezing = yesOrNo("Is the outside temperature below 32 degrees?");
            if (isFreezing) { // isFreezing == true
               print("Turn on Carburator Heat.", true, 2);
            } else { // isFreezing == false
               print("Switch to other fuel tank.", true, 2);
            }
         }
      } else { // electrical == false
         print("Turn on the Master Switch.", true, 2);
      }
   } else { // airborne == false
      print("Have a drink and call a mechanic.", true, 2);
   }
}

/********************************************************
 * Input/Processing/Output Module:
 * Based on user estimated amount of ice module 
 * determines recommended power level
 *******************************************************/
void icingOption2()
{
   bool validInput;
   double estimate;

   // Loop that prompts user for estimated ice depth input 
   do {
      print("How much ice estimated on wings? (0-10mm)", true);
      cin >> estimate;
      // Checks if none double is entered
      if (cin.fail()) {
         (validInput = false);
      } else {
         // If double is entered check if input is in range
         validInput = (estimate >= 0 && estimate <= 10) ? true : false;
      }
      // Displays error if input is determined invalid
      if (!validInput) inputError(INVALID_ENTRY);
      // Restart loop if input is invalid
   } while(!validInput);
   
   // To use switch in this instance the value must be an integer
   // Rounding 
   int roundedEstimate;
   (estimate < 1) ? roundedEstimate = floor(estimate) : roundedEstimate = ceil(estimate);

   // Switch used over if else for readability
   switch (roundedEstimate) {
      // If input is between 0.0 & 0.9
      case 0: print("5% Power", true, 2);
         break;
      // If input is between 1.0 & 5.0
      case 1 ... 5: print("20% Power", true, 2);
         break;
      // If input is between 5.1 & 9.0
      case 6 ... 9: print("65% Power", true, 2);
         break;
      // If input is between 9.1 & 10.0
      case 10: print("100% Power", true, 2);
         break;
      // If another value is evaluated somehow, 
      // a custom error message is output to help track error
      default: print("ERROR INVALID ENTRY IN ICING");
         exit(EXIT_FAILURE);
         break;
   }
}