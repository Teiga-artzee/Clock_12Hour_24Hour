/*
 * Calculator.cpp
 *
 *  Date: May 13th, 2021
 *  Author: Alexandrea Teigeler
 *  This application should take in 2 numbers and perform simple arthmetic using +, -, *, /
 *  performs these functions using a do-while loop which allows the program to run at least once before prompting 
 *  the user if they wish to continue
 */

#include <iostream>

using namespace std;

void main() {

	//Integers used for the arthmetic operations in the do-while loop
	int op1, op2;

	//Character that user will choose to input for the type of arthmetic they wish to perform
	char operation;

	//Changed the declaration as the do while will perform at least once, so assigning answer a value before the first iteration is redundant
	//added ; to end of statement
	char answer;

	//Changed the while loop to a do-while, so the program runs at least once
	//Also works better for checking the variable answer for a different input to compare
	do {
		cout << "Enter expression" << endl;
		//If incorrect input, the program automatically ends
		cin >> op2 >> operation >> op1;
		//Evaluates operation if user wants addition
		//Fixed the wrong orientation of >> to  <<
		//Changed "+" to '+' as the quotes don't work for character types
		//Added {} braces to all the bodies of the if-elseif statements and removed unneccesary ; from code
		//Fixed spacing for if-elseif statement bodies
		if (operation == '+') {
			cout << op1 << " + " << op2 << " = " << op1 + op2 << endl;
		}
		//Evaluates operation if user wants subtraction
		//Fixed the wrong orientation of >> to <<
		else if (operation == '-') {
			cout << op1 << " - " << op2 << " = " << op1 - op2 << endl;
		}
		//Evaluates operation if user wants multiplication
		//Changed the cout where it orignially printed that it was dividing the two values but performed multiplication
		//Now prints out * symbol
		else if (operation == '*') {
			cout << op1 << " * " << op2 << " = " << op1 * op2 << endl;
		}
		//Evaluates operation if user wants division
		else if (operation == '/') {
			cout << op1 << " * " << op2 << " = " << op1 / op2 << endl;
		}
		//Prompts user if they want to perform more arthmetic 
		cout << "Do you wish to evaluate another expression?" << endl;
		cin >> answer;
		//While added the OR operator so if the user types a capital OR a lower case y, the program will still run as intended
	} while (answer == 'Y' || answer == 'y');

	//Prints to console when the program has exited the do-while loop
	cout << "Program Finished." << endl;
}



