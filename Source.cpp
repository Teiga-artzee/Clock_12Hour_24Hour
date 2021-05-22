/*
Alexandrea Teigeler
May 19th, 2021

Program Clock:

	This program displays a 12 hour clock as well as a 24 hour clock
	----------------------------------------------------------------
	A menu gives the user 4 options to choose from in order to interact with the program.
	The user will be able to add an additional hour, minute, and second to these clocks
	----------------------------------------------------------------
	The user can also exit the program from the menu that is printed to the console
	----------------------------------------------------------------
	NOTE: The clocks are static and ONLY update IF the program is first turned on to get the time
		  OR
		  if the clocks are updated by the user within the menuOptionControl function


*/
#include <iostream>
#include <iomanip>
#include <cstring>
#include <string>
#include <time.h>

using namespace std;

//global variables
// hour, minute, second used in the clocks
int hour;
int minute;
int second;

//The string time frame will hold either AM or PM depending on the time of day it is for the user
string timeFrame;


void getTime() {
	
	//Called only once when program begins
	//Gets the current time for the user
	//Format for getTime retrieved from Professor Linda Noss Youtube Channel--accessed May 18th,2021

	time_t ttime = time(0);
	//Added to avoid Warnings and use local time
	#pragma warning(suppress : 4996). 
	tm* local_time = localtime (&ttime); 

	//sets the global variables to the local time
	//useful to be altered later
	hour   = local_time->tm_hour;
	minute = local_time->tm_min;
	second = local_time->tm_sec;

}


int clock12() {
	
	//local variable used to return int when creating 12-hour clock
	
	int my_hour = hour;
	//Function used to adjust for the 12-hour clock
	//if the hour is past noon (1 pm or later) it gets reset.
	//To account for the actual time, hour12 is set to take the current hour
	//and subtract from 12 for proper format

	if (hour > 12) {
		my_hour = hour - 12;
	}

	return my_hour;
}

void clock24() {

	//adjusts clock if the hour/minute/second are changed
	//will also check to see if AM or PM

	if (second == 60) {
		//reset second and add a minute
		second = 0;
		minute += 1;
	}
	if (minute == 60) {
		//reset minute and add an hour
		minute = 0;
		hour += 1;
	}
	if (hour == 25) {
		//everything resets--done for extra measure of redundancy to prevent errors
		hour = 0;
		minute = 0;
		second = 0;
	}

	//Checks if Morning or Afternoon
	if (hour <= 11) {
		//Checks to see if it is morning
		timeFrame = "AM";
	}
	else {
		//if it is noon, will change to PM
		timeFrame = "PM";

	}

}

/*
Adjust hour, Adjust Minute, Adjust Second--are to add to the global variables hour, minute, second
-----------------------------------------------------------------------------------------------------
Functions could be adjusted slightly to allow user to enter in a new integer to change clock time easier than
adjusting by 1 hour/minute/second
-----------------------------------------------------------------------------------------------------
This would be done either within the function, or through menuOptionControl that gets an input from user and sends
that int as an argument for these functions
*/

void adjustHour() {

	//adds 1 hour 
	hour += 1;
	//Calls the clock 24-hour function to update the clock
	clock24();
}

void adjustMinute() {

	//adds 1 minute
	minute += 1;
	//Calls the clock 24-hour function to update the clock
	clock24();
}

void adjustSecond() {

	//adds 1 second
	second += 1;
	//Calls the clock 24-hour function to update the clock
	clock24();
}

string time_formatting(int my_time) {
	//changes numbers for proper format
	//my_time is the int representation for hour, min, or seconds
	//Example: if the time is 1:05:03 pm, then this changes the single digits (which are currently integers) to strings
	//so it prints to console as 01:05:03--otherwise would print as 1:5:3 

	//string to be sent back for proper format
	string my_Format = "0";
	//converts my_time to a string
	

	if (my_time >= 0 && my_time <= 9) {
		//Adding the single digit integar within my_time to the end of my_Format, which has a string of 0 at the front
		//Simultainously converts the integer to a string so this is possible
		my_Format.append(to_string(my_time));
		
	}
	else {
		//writes over "0" base of my_format, allowing double digits without 0 in front
		my_Format = to_string(my_time);
	}

	return my_Format;
}

void clockDisplay() {

	//This function will print to the console in the 12 hour and 24 hour format

	//Called to ensure the clock has been updated for redundancy
	clock24();

	/*
	Calls the clock 12 hour function to get the correct time format that specific clock--This also makes sure it is updated correctly and is stored
	in the local variable hour_12
	*/

	int hour_12;
	hour_12 = clock12();

	/*
	Called to ensure formatting is correct if value is 0 - 9
	in this case, if time is 11:01:09, without function, it prints as 11:1:9
	-------------------------------------------------------------------------
	string f12 hour is the formatted hour for the 12 hour clock
	string f24 hour is the formmated hour for the 24 hour clock
	------------------------------------------------------------------------
	string min is the formatted minute
	string sec is the formatted second
	*/
	
	string f12_hour;
	string f24_hour;
	string min;
	string sec;

	//calls the formatting function for each string
	
	f24_hour = time_formatting(hour);
	f12_hour = time_formatting(hour_12);
	min = time_formatting(minute);
	sec = time_formatting(second);
	

	//Top Boarder
	cout << setw(26) << left << "****************************" << "     ";
	cout << setw(26) << right << "****************************" << endl;
	//Clock Print to Console
	cout << "*" << "       12-Hour Clock      *" << "     " << "*      24-Hour Clock       *" << endl;
	cout << "*        " << f12_hour << ":" << min << ":" << sec << " " << timeFrame << "       *" << "     " << "*        " << f24_hour << ":" << min << ":" << sec << "          *" << endl;
	//Bottom Boarder
	cout << setw(26) << left << "****************************" << "     ";
	cout << setw(26) << right << "****************************" << endl;
}

void menuPrint() {

	//Prints the menu for the user to interact with

	cout << setw(26) << left << "****************************" << endl;
	cout << "* 1 - Add One Hour         *" << endl;
	cout << "* 2 - Add One Minute       *" << endl;
	cout << "* 3 - Add One Second       *" << endl;
	cout << "* 4 - Exit Program         *" << endl;
	cout << setw(26) << left << "****************************" << endl;

}

void menuOptionControl() {

	//functionality for menu function controls
	//Variable used for user to make a choice from the menu option
	int userChoice;

	//used in do-while loop to continue checking input until a correct one is used
	//switches to true when correct choice is used

	bool correct_Menu_select = false;

	//Try block to check if user input the allowed menu options
	//will catch anything that isn't 1,2,3,4 and ask them to retry a new entry
	do {
		try {
			std::cin >> userChoice;

			//To catch error if userChoice gets input that IS NOT an integer
			//Retrieved from http://www.cplusplus.com/reference/istream/istream/ignore/
			while (std::cin.fail()) {
				std::cin.clear();
				std::cin.ignore(256, '\n');
				cout << "Unknown Menu Option. Please try again." << endl;
				menuPrint();
				std::cin >> userChoice;
			}
			if (userChoice == 1 || userChoice == 2 || userChoice == 3 || userChoice == 4) {
				//Passes the try test
				//exits the do-while
				correct_Menu_select = true;
			}
			else {
				throw (userChoice);
				//if the input is NOT 1-4, prompts user to choose the correct option calls
			}
		}
		catch (...) {
			cout << "Unknown Menu Option. Please try again." << endl;
			menuPrint();
		}
	} while (correct_Menu_select == false);

	/*
	Branches from the menu choices
	At the end of each branch, the clock will display, and then the menu
	this will repeat UNTIL the user Exits the program, selecting '4'
	*/
	
	if (userChoice == 1) {
		//Adds 1 hour to the clocks

		adjustHour();

		//After hour is adjusted according to users choice, these functions are called:
		//to print the clock to the console
		//to print the menu
		//and then to start the function over again--effectively making a simple loop
		clockDisplay();
		menuPrint();
		menuOptionControl();
	}
	else if (userChoice == 2) {
		//Adds 1 minute to the clocks

		adjustMinute();

		//After hour is adjusted according to users choice, these functions are called:
		//to print the clock to the console
		//to print the menu
		//and then to start the function over again--effectively making a simple loop
		clockDisplay();
		menuPrint();
		menuOptionControl();
	}
	else if (userChoice == 3) {
		//Adds 1 second to the clocks

		adjustSecond();

		//After hour is adjusted according to users choice, these functions are called:
		//to print the clock to the console
		//to print the menu
		//and then to start the function over again--effectively making a simple loop
		clockDisplay();
		menuPrint();
		menuOptionControl();
	}
	else {
		// Exits program--userChoice was 4
		cout << "The program is being shut down." << endl;

		//should return to main and exit the program
		//returning to main is the cleanest and safest way to exit the program
		return;
		
	}
	
}


int main() {
	
	/*
	Begins the program
	first, get time will assign the clocks (12 hour and 24 hour) with their
	appropriate values for hour, min, sec
	Clock display will then display the clocks and the associated values
	then menuPrint will print the menu to console
	*/
	
	getTime();
	clockDisplay();
	menuPrint();
	menuOptionControl();

}
