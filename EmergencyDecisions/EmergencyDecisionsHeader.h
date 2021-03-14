#pragma once

#include <iostream>
#include <iomanip>

using namespace std;

/* Main Driver Module */
void emergencyDecisionsMenu();

/* Output Modules */
void comFaliureOption0();
void engFailureOption1();
void icingOption2();

/* Processing Modules */
void emergencyDecisionHandler(char choice, bool &quit);