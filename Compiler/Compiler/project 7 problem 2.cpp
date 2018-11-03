// Compiler.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <stack>
#include <iostream>
#include <map>
#include <string>
using namespace std;
enum Symbols
{
	//terminal symbols:
	A = 1,	//a
	PLUS,	//+
	MINUS,	//-
	MULT,	//*
	DIVI, // /
	L_PARENS,	//(
	R_PARENS,	//)
	CASH,	//$
	EQUAL,	// =
	B, // b
	// Non-terminal symbols:
	E,
	Q,
	T,
	R,
	F,
	S,
	INVALID,	// invalid token
};
// convert a valid token to a terminal symbol
Symbols Equivalent(char c)
{
	switch (c)
	{
	case 'a': return A;
	case '+': return PLUS;
	case '-': return MINUS;
	case '*': return MULT;
	case '/': return DIVI;
	case '(': return L_PARENS;
	case ')': return R_PARENS;
	case '$': return CASH;
	case '=': return EQUAL;
	case'b': return B;
	default: return INVALID;

	}
};

int main()
{
	// parser table, map <non-terminal, terminal>
	map<Symbols, map<Symbols, int>> table;
	stack<Symbols> SStack;
	int walker = 0;

	// initialize the stack
	SStack.push(CASH);
	SStack.push(S);
	// ask for input
	string Input;
	cout << "Please enter input: ";
	cin >> Input;

	//set up parsing table
	table[E][A] = 1;
	table[E][L_PARENS] = 2;
	table[Q][PLUS] = 3;
	table[Q][MINUS] = 4;
	table[Q][R_PARENS] = 5;
	table[Q][CASH] = 6;
	table[T][A] = 7;
	table[T][L_PARENS] = 8;
	table[R][PLUS] = 9;
	table[R][MINUS] = 10;
	table[R][MULT] = 11;
	table[R][DIVI] = 12;
	table[R][R_PARENS] = 13;
	table[R][CASH] = 14;
	table[F][A] = 15;
	table[F][L_PARENS] = 16;
	table[S][A] = 17;
	table[E][B]= 18;
	table[T][B] = 19;
	table[F][B] = 20;

	while (SStack.size() > 0)
	{	// if match show stack
		if (Equivalent(Input[walker]) == SStack.top())
		{
			walker++;
			SStack.pop();
			stack<Symbols>tempstack = SStack;
			while (!tempstack.empty())
			{
				if (tempstack.top() == 1)
					cout << "a";
				else if (tempstack.top() == 2)
					cout << "+";
				else if (tempstack.top() == 3)
					cout << "-";
				else if (tempstack.top() == 4)
					cout << "*";
				else if (tempstack.top() == 5)
					cout << "/";
				else if (tempstack.top() == 6)
					cout << "(";
				else if (tempstack.top() == 7)
					cout << ")";
				else if (tempstack.top() == 8)
					cout << "$";
				else if (tempstack.top() == 9)
					cout << "=";
				else if (tempstack.top() == 10)
					cout << "b";
				else if (tempstack.top() == 11)
					cout << "E";
				else if (tempstack.top() == 12)
					cout << "Q";
				else if (tempstack.top() == 13)
					cout << "T";
				else if (tempstack.top() == 14)
					cout << "R";
				else if (tempstack.top() == 15)
					cout << "F";
				else if (tempstack.top() == 16)
					cout << "S";
				tempstack.pop();
			}
			cout << endl;
		}
		else
		{
			// correspond with parsing table
			switch (table[SStack.top()][Equivalent(Input[walker])])
			{
				//E-> TQ
			case 1: //E a
				SStack.pop();
				SStack.push(Q);
				SStack.push(T);
				break;
			case 2:// E (
				SStack.pop();
				SStack.push(Q);
				SStack.push(T);
				break;
				//Q-> +TQ	Q-> -TQ		Q->lambda
			case 3: // Q +
				SStack.pop();
				SStack.push(Q);
				SStack.push(T);
				SStack.push(PLUS);
				break;
			case 4: //Q -
				SStack.pop();
				SStack.push(Q);
				SStack.push(T);
				SStack.push(MINUS);
				break;
			case 5: // Q )
				SStack.pop();
				break;
			case 6:		// Q $
				SStack.pop();
				break;
			case 7:		// T a
				SStack.pop();
				SStack.push(R);
				SStack.push(F);
				break;
			case 8:		// T (
				SStack.pop();
				SStack.push(R);
				SStack.push(F);
				break;
			case 9:		// R +
				SStack.pop();
				break;
			case 10:	// R -
				SStack.pop();
				break;
			case 11:	// R *
				SStack.pop();
				SStack.push(R);
				SStack.push(F);
				SStack.push(MULT);
				break;
			case 12:	// R /
				SStack.pop();
				SStack.push(R);
				SStack.push(F);
				SStack.push(DIVI);
				break;
			case 13:	// R )
				SStack.pop();
				break;
			case 14:	// R $
				SStack.pop();
				break;
			case 15:	// F a
				SStack.pop();
				SStack.push(A);
				break;
			case 16:	// F (
				SStack.pop();
				SStack.push(R_PARENS);
				SStack.push(E);
				SStack.push(L_PARENS);
				break;
			case 17: // S a
				SStack.pop();
				SStack.push(E);
				SStack.push(EQUAL);
				SStack.push(A);
				break;
			case 18:	// E b
				SStack.pop();
				SStack.push(Q);
				SStack.push(T);
				break;
			case 19: // T b
				SStack.pop();
				SStack.push(R);
				SStack.push(F);
				break;
			case 20:
				SStack.pop();
				SStack.push(B);
				break;

			default:
				cout << "Input is not accepted" << endl;
				char restart;
				cout << "restart? y or n \0";
				cin >> restart;
				if (restart == 'y')
					return main();
				else
					return 0;
			}
		}
	}
	cout << "Input is Accepted" << endl;
	char restart;
	cout << "restart? y or n \0";
	cin >> restart;
	if (restart == 'y')
		return main();
	else
		return 0;
}