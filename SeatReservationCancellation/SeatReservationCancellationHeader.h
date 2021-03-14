#pragma once

#include <iostream>  // cout, cin
#include <iomanip>   // setw

using namespace std;    // std:: prefix

/* Symbolic Constants */
#define COLUMNS         4
#define ROWS            7

/* Main Driver Module */
void seatReservationCancellationMenu();

/* Sub Driver Modules */
void setupSeats(char seatingRows[ROWS], char seatingColumns[COLUMNS], char seatingArr[ROWS][COLUMNS]);
void displaySeatsOption0(char seatingRows[ROWS], char seatingColumns[COLUMNS], char seatingArr[ROWS][COLUMNS]);
void seatReservation1(char seatingRows[ROWS], char seatingColumns[COLUMNS], char seatingArr[ROWS][COLUMNS]);
void seatCancellation2(char seatingRows[ROWS], char seatingColumns[COLUMNS], char seatingArr[ROWS][COLUMNS]);

/* Input Modules */
short getSeatRow(char seatingRows[ROWS]);
char getSeatColumn(char seatingColumns[COLUMNS]);

/* Processing Modules */
void linearCounter(short start, short finish, char countOutput[]);
void seatGenerator(char seatingOutput[ROWS][COLUMNS]);
void decisionHandler(char choice, char seatingRows[], char seatingColumns[], 
   char seatingArr[ROWS][COLUMNS], short totalSeats, bool &quit);
short  calculateAvaliableSeats(char seatingArr[ROWS][COLUMNS]);
void seatCheck(char seatingArr[ROWS][COLUMNS], short rowNum, short colNum, string seatId);
string getSeat(short rowNum, char columnLetter);
void bookSeat(char seatingArr[ROWS][COLUMNS], short rowNum, short colNum, string seat);
void cancelSeat(char seatingArr[ROWS][COLUMNS], short rowNum, short colNum, string seat);
bool seatCheck(char seatingArr[ROWS][COLUMNS], short rowNum, short colNum);

/* Output Modules */
void displayColumnHeader(char seatingColumns[]);
void displayRows(char seatingRows[], char seatingArr[ROWS][COLUMNS]);
void displayCurrentSeating(short currentRow, char seatingArr[ROWS][COLUMNS]);
void displayAvaliableSeats(char seatingArr[ROWS][COLUMNS], short totalSeats);