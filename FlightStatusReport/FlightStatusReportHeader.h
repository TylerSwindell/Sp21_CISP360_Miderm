#pragma once

#include <iostream>  // cout, cin, string
#include <iomanip>   // setw
#include <fstream>   // ifstream
#include <string>    // stoi

using namespace std; // "std::" prefix

#define FLIGHT_FIELDS   5                             // Fields of data for each flight


/* Main Driver Module */
void flightStatusReportMenu();

/* Output Modules */
void displayFlightInfoHeader();
void displayFlightInfo(string flightData[FLIGHT_FIELDS], int delay);

/* Processing Modules */
void decisionHandler(char choice, bool &quit);
void arrivalOption0();
void departureOption1();
void fileInput(string filename);
bool openFile(string filename, ifstream &inFile);
bool checkFile(ifstream &inFile);
void dataInput(ifstream &inFile, string flightData[FLIGHT_FIELDS]);
int calculateActual(int scheduled, int actual);