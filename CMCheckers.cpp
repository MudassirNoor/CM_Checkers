/**
* Author: Mudassir Noor, Harsh Behal
* @brief: Cylindrical Mule Checkers game
* @Date: 30th November, 2017
*/

#include <iostream>
#include <iomanip>
#include <cmath>
#include <sstream>
#include <string>

using namespace std;

//Declared global constants
const int MAX_ARRAY_SIZE = 18;
const int MIN_ARRAY_SIZE = 8;
const int MAX_PIECES = 72;
const int NOPLAYER = 0;
const int WHITEWINS = 1;
const int REDWINS = 2;
const int NOONEWINS = 0;
const int WHITESOLDIER = 1;
const int WHITEMULE = 2;
const int WHITEKING = 3;
const int REDSOLDIER = 4;
const int REDMULE = 5;
const int REDKING = 6;
const int WHITEPLAYER = 1;
const int REDPLAYER = 2;

//All functions//
void InitializeBoard(int CMCheckersBoard[MAX_ARRAY_SIZE][MAX_ARRAY_SIZE], int numRowsInBoard);

void DisplayBoard(int CMCheckersBoard[MAX_ARRAY_SIZE][MAX_ARRAY_SIZE], int numRowsInBoard);

int CountJumps(int CMCheckersBoard[MAX_ARRAY_SIZE][MAX_ARRAY_SIZE], int numRowsInBoard, int player, int xLocArray[], int yLocArray[]);

int CountMove1Squares(int CMCheckersBoard[MAX_ARRAY_SIZE][MAX_ARRAY_SIZE], int numRowsInBoard, int player, int xLocArray[], int yLocArray[]);

bool IsMove1Square(int CMCheckersBoard[MAX_ARRAY_SIZE][MAX_ARRAY_SIZE], int numRowsInBoard, int player, int xLoc, int yLoc);

bool CheckList(int inArray1[], int inArray2[], int xIndex, int yindex);

bool IsJump(int CMCheckersBoard[MAX_ARRAY_SIZE][MAX_ARRAY_SIZE], int numRowsInBoard, int player, int xLoc, int yLoc);

bool MakeMove(int CMCheckersBoard[MAX_ARRAY_SIZE][MAX_ARRAY_SIZE], int numRowsInBoard, int player, int fromSquareNum, int toSquareNum, bool &jumped);

bool CheckWin(int CMCheckersBoard[MAX_ARRAY_SIZE][MAX_ARRAY_SIZE], int numRowsInBoard);

int main()
{
	bool jumped = false;
	int MoveTo = 0;
	int maxSquaresPermitted = 0;
	int squareNumber = 0;
	char Character = NULL;
	int turnCounter = 0;
	int movesAvail = 0;
	int jumpsAvail = 0;
	int xLoc = 0;
	int yLoc = 0;
	int xLocChecker = 0;
	int yLocChecker = 0;
	int ydistance = 0;
	int xdistance = 0;
	int player = 0;
	int myCMCheckersBoard[MAX_ARRAY_SIZE][MAX_ARRAY_SIZE] = { { 0 },{ 0 } };

	int xIndicesMove[MAX_PIECES] = { 0 };
	int yIndicesMove[MAX_PIECES] = { 0 };

	int xIndicesJump[MAX_PIECES] = { 0 };
	int yIndicesJump[MAX_PIECES] = { 0 };

	// constants //
	int numRowsInBoard = 0;
	const int NUM_ROWS_MAX = 18;
	const int NUM_ROWS_MIN = 8;
	const int ZERO = 0;
	const int ONE = 1;
	const int TWO = 2;
	// tries //
	int Tries = 0;
	int MaxTries = 3;

	int i = 0;
	int k = 0;


	//Checks if you have entered the correct amount of //
	// rows if they're int or in limit                 //

	while (true)
	{
		Tries++;
		if (Tries>MaxTries)  //If user exceeds maximum number of tries allowed
		{
			cerr << "ERROR:  Too many errors entering the size of the board" << endl;
			return 1;
		}
		cout << "Enter the number of squares along each edge of the board" << endl;

		if (!(cin >> numRowsInBoard)) //Checks to see if the value input is of type integer
		{
			cerr << "ERROR: Board is not an integer" << endl;
			cout << "8 <= number of squares <= 18" << endl;
			cin.clear();
			cin.ignore(numeric_limits <streamsize>::max(), '\n');
			continue;
		}

		//The following set of codes checks whether the value satisfies the condition in generating the table
		if (numRowsInBoard % 2 != 0)
		{
			cerr << "ERROR:  Board size odd" << endl;
			cout << "8 <= number of squares <= 18" << endl;
			continue;
		}
		if (numRowsInBoard < NUM_ROWS_MIN)
		{
			cerr << "ERROR:  Board size too small" << endl;
			cout << "8 <= number of squares <= 18" << endl;
			continue;
		}
		else if (numRowsInBoard > NUM_ROWS_MAX)
		{
			cerr << "ERROR:  Board size too large" << endl;
			cout << "8 <= number of squares <= 18" << endl;
			continue;
		}
		else
		{
			break;
		}
	}

	InitializeBoard(myCMCheckersBoard, numRowsInBoard); //Calls the initialize board function
	
	while(1)
	{
		turnCounter++;                      //Checks to see which player's turn it is
		if(turnCounter%2 != ZERO)           //For the white player's turn, the counter has to be odd
		{
			player = WHITEPLAYER;
		}
		else
		{
			player = REDPLAYER;
		}

		movesAvail = CountMove1Squares(myCMCheckersBoard, numRowsInBoard, player, xIndicesMove, yIndicesMove);
		jumpsAvail = CountJumps(myCMCheckersBoard, numRowsInBoard, player, xIndicesJump, yIndicesJump);
		CheckWin(myCMCheckersBoard, numRowsInBoard);

		cout << endl << endl;

		//Conditions for winning the game based on moves available and jumps availabe
		if(movesAvail == ZERO && jumpsAvail == ZERO)
		{
			if(player == WHITEPLAYER)
			{
				cout << "White is unable to move" << endl << "GAME OVER, Red has won" << endl << "Enter any character to close the game";
				cin >> Character;
				return 1;
			}
			else
			{
				cout << "Red is unable to move" << endl << "GAME OVER, White has won" << endl << "Enter any character to close the game";
				cin >> Character;
				return 2;
			}
		}
		else
		{
			if(player == WHITEPLAYER)
			{
				cout << "White takes a turn" << endl;
			}
			else
			{
				cout << "Red takes a turn" << endl;
			}
		}

		StartE: //The players take the turn
		while(1) // part E //
		{
			maxSquaresPermitted = (numRowsInBoard*numRowsInBoard) - ONE;
			cout << "Enter the square number of the checker you want to move" << endl;
			if(!(cin >> squareNumber))                          //Checks to see if the square number is of type integer
			{
				cerr << "ERROR: you did not enter an integer";
				cerr << endl << "Try again" << endl;
				cin.clear();
				cin.ignore(numeric_limits <streamsize>::max(), '\n');   //Clears the input stream
				continue;
			}

			//The following two functions checks if the square is in the board and if there is a checker present in the square
			else if(squareNumber > maxSquaresPermitted || squareNumber < ZERO)
			{
				cerr << "ERROR:  that square is not on the board." << endl << "Try again" << endl;
				continue;
			}	

			//Calculates the row and column for the square number input by the player
			xLocChecker = (squareNumber/numRowsInBoard);
			yLocChecker = (squareNumber%numRowsInBoard);

			if(myCMCheckersBoard[xLocChecker][yLocChecker] == ZERO)
			{
					cerr << "ERROR: that square is empty" << endl << "Try again" << endl;
					continue;
			}

			if(player == REDPLAYER)
			{	
				//Checks to see if the player input the square number of the opponent checker, if so the player is prompted again
				if(myCMCheckersBoard[xLocChecker][yLocChecker] == WHITEKING || myCMCheckersBoard[xLocChecker][yLocChecker] == WHITESOLDIER || myCMCheckersBoard[xLocChecker][yLocChecker] == WHITEMULE)
				{
					cerr << "ERROR: that square contains an opponents checker" << endl << "Try again" << endl;
					continue;
				}

				//This function calculates the jumps availabe before asking where to move the checker
				jumpsAvail = CountJumps(myCMCheckersBoard, numRowsInBoard, player, xIndicesJump, yIndicesJump);
				if(jumpsAvail != ZERO)
				{
					//If the current checker can't jump but another can, the program requests the user to move the checker that can jump as per game rules
					if(IsJump(myCMCheckersBoard, numRowsInBoard, player, xLocChecker, yLocChecker) != true)
					{
						cerr << "ERROR: You can jump with another checker, you may not move your chosen checker" << endl << "You can jump using checkers on the following squares: ";
						for(i = 0; i < numRowsInBoard; i++)
						{
							for(k = 0; k < numRowsInBoard; k++)
							{
								//Checks to see which of the checkers can jump and prints the square number of that checker
								if(IsJump(myCMCheckersBoard, numRowsInBoard, player, i, k) == true)
								{	
									cout << i*numRowsInBoard + k << " ";
								}
							}
						}
						cout << endl;
						continue;
					}

				}

				//If neither moving the checker nor jumping with the checker is possible, the player is prompted again
				else if(IsJump(myCMCheckersBoard, numRowsInBoard, player, xLocChecker, yLocChecker) != true && IsMove1Square(myCMCheckersBoard, numRowsInBoard, player, xLocChecker, yLocChecker) != true)
				{
					cerr << "ERROR: There is no legal move for this checker"<<endl << "Try again" << endl;
					continue;
				}
				
				break;
			}

			else if(player == WHITEPLAYER)
			{
				//Checks to see if the player input the square number of the opponent checker, if so the player is prompted again
				if(myCMCheckersBoard[xLocChecker][yLocChecker] == REDKING || myCMCheckersBoard[xLocChecker][yLocChecker] == REDSOLDIER || myCMCheckersBoard[xLocChecker][yLocChecker] == REDMULE)
				{
					cerr << "ERROR: that square contains an opponents checker" << endl << "Try again" << endl;
					continue;
				}

				//This function calculates the jumps availabe before asking where to move the checker
				jumpsAvail = CountJumps(myCMCheckersBoard, numRowsInBoard, player, xIndicesJump, yIndicesJump);
				if(jumpsAvail != ZERO)
				{
					if(IsJump(myCMCheckersBoard, numRowsInBoard, player, xLocChecker, yLocChecker) != true)
					{
						//If the current checker can't jump but another can, the program requests the user to move the checker that can jump as per game rules
						cerr << "ERROR: You can jump with another checker, you may not move your chosen checker" << endl << "You can jump using checkers on the following squares: ";
						for(i = 0; i < numRowsInBoard; i++)
						{
							for(k = 0; k < numRowsInBoard; k++)
							{
								//Checks to see which of the checkers can jump and prints the square number of that checker
								if(IsJump(myCMCheckersBoard, numRowsInBoard, player, i, k) == true)
								{
									cout << i*numRowsInBoard + k << " ";
								}
							}
						}
						cout << endl;
						continue;
					}
				}

				//If neither moving the checker nor jumping with the checker is possible, the player is prompted again
				else if(IsJump(myCMCheckersBoard, numRowsInBoard, player, xLocChecker, yLocChecker) != true && IsMove1Square(myCMCheckersBoard, numRowsInBoard, player, xLocChecker, yLocChecker) == false)
				{
					cerr << "ERROR: There is no legal move for this checker"<<endl << "Try again" << endl;
					continue;
				}
					break;
			}
			
		}

		//Moving the requested checker
		while(1) // 10 f //
		{
			cout <<  "Enter the square number of the square you want to move your checker to" << endl;

			stepf:   //Reprompt if the checker can jump again

			if(!(cin >> MoveTo))                 //Checks to see if the input if of the corrected data type
			{
				cerr << "ERROR: you did not enter an integer" << endl << "Try again" << endl;
				cin.clear();
				cin.ignore(numeric_limits <streamsize>::max(), '\n');
				continue;
			}
			else if(MoveTo > maxSquaresPermitted || MoveTo < ZERO)   //Checks to see if the square is present in the board
			{
				cerr << "ERROR: It is not possible to move to a square that is not on the board" << endl << "Try again" << endl;
				continue;
			}

			//Calculates the position of the square
			xLoc = (MoveTo/numRowsInBoard);
			yLoc = (MoveTo%numRowsInBoard);

			//The following functions check whether there is a checker already present in that square in which case the move woud be invalid
			if(player == WHITEPLAYER)
			{
				if(myCMCheckersBoard[xLoc][yLoc] == WHITEKING || myCMCheckersBoard[xLoc][yLoc] == WHITESOLDIER || myCMCheckersBoard[xLoc][yLoc] == WHITEMULE || myCMCheckersBoard[xLoc][yLoc] == REDSOLDIER || myCMCheckersBoard[xLoc][yLoc] == REDMULE || myCMCheckersBoard[xLoc][yLoc] == REDKING)
				{
					cerr << "ERROR: It is not possible to move to a square that is already occupied" << endl << "Try again" << endl;
					continue;
				}
			}

			//The following functions check whether there is a checker already present in that square in which case the move woud be invalid
			if(player == REDPLAYER)
			{
				if(myCMCheckersBoard[xLoc][yLoc] == WHITEKING || myCMCheckersBoard[xLoc][yLoc] == WHITESOLDIER || myCMCheckersBoard[xLoc][yLoc] == WHITEMULE || myCMCheckersBoard[xLoc][yLoc] == REDSOLDIER || myCMCheckersBoard[xLoc][yLoc] == REDMULE || myCMCheckersBoard[xLoc][yLoc] == REDKING)
				{
					cerr << "ERROR: It is not possible to move to a square that is already occupied" << endl << "Try again" << endl;
					continue;
				}
			}

			//If a jump and move is possible with the checker but the player does not jump, it asks the player to jump as per rules
			if(IsMove1Square(myCMCheckersBoard, numRowsInBoard, player, xLocChecker, yLocChecker) == true)
			{
				if(abs(xLoc-xLocChecker) == ONE && abs(yLoc-yLocChecker) == ONE)
				{
					if(IsJump(myCMCheckersBoard, numRowsInBoard, player , xLocChecker, yLocChecker) == true)
					{
						cerr << "ERROR: You can jump with this checker, you must jump not move 1 space" << endl << "Try again" << endl;
						continue;
					}
				}
			}

			//The followng function makes the move, if the move returns false, an error message is printed
			if (MakeMove(myCMCheckersBoard, numRowsInBoard, player, squareNumber, MoveTo, jumped) == false)
			{
				cerr << "ERROR: Moving to that square is not legal, Try again" << endl;
				goto StartE; 
			}

			//The function displays the board after the move has been made
			DisplayBoard(myCMCheckersBoard, numRowsInBoard);

			//After each move, the checkwin function is called to see if any of the player has won. If true the game will end at that point.
			if(CheckWin(myCMCheckersBoard,numRowsInBoard) == true)
			{
				cout << "Enter any character to terminate the game then press the enter key" << endl;
				cin >> Character;

				return 3;
			}

			//Calculates the distance moved by the checker in x-coordinate and y-coordinate
			xdistance = abs(xLoc-xLocChecker);
			ydistance = abs(yLoc-yLocChecker);

			//If the vertical displacement is equal to the number of columns present, that means the piece has moved to the other other end of the row
			//hence the displacement is measured to be 1 in this case
			if(ydistance == numRowsInBoard - ONE)
			{
				ydistance = ONE;
			}
			if(ydistance == numRowsInBoard - TWO)
			{
				ydistance = TWO;
			}

			//If the square can move 1 square again, then it checks if it can jump, if not, the turn is switched.
			if(xdistance == TWO && ydistance == TWO)
			{
				//Checks to see if another jump is possible with same checker
				if(IsJump(myCMCheckersBoard, numRowsInBoard, player, xLoc, yLoc) == true )
				{
					cout << "You can jump again, Please enter the next square you wish to move your checker to" << endl;
					squareNumber = MoveTo;
					goto stepf;
				}
			}
			
			break;
		}
	}
	return 0;
}
/**
* @brief: Initializes the game
* @param1 The board array
* @param2 number of rows
* @returns void
*/
void InitializeBoard(int CMCheckersBoard[MAX_ARRAY_SIZE][MAX_ARRAY_SIZE], int numRowsInBoard) 
{																							  
	int i = 0;																				  
	int k = 0;
	const int ZERO = 0;
	const int EMPTYSPACE = 0;

	int numRowsInBoardEmpty1 = 0;
	int numRowsInBoardEmpty2 = 0;
	int NumrowsMinusOne = 0;

	//The first row that will be empty will be 8/2 which is 4  
	//Second one is 4 - 1                                     

	numRowsInBoardEmpty1 = numRowsInBoard / 2;
	numRowsInBoardEmpty2 = (numRowsInBoardEmpty1 - 1);
	NumrowsMinusOne = numRowsInBoard - 1;

	//For loop to set the pieces up
	for (i = 0; i <= numRowsInBoard; i++)
	{
		for (k = 0; k<numRowsInBoard; k++)
		{
			if (i == ZERO)
			{
				if (k % 2 == ZERO)
				{
					CMCheckersBoard[i][k] = 0;
					continue;
				}
				else
				{
					CMCheckersBoard[i][k] = 2;
					continue;
				}
			}
			if (i == NumrowsMinusOne)
			{
				if (k % 2 == ZERO)
				{
					CMCheckersBoard[i][k] = 5;
					continue;
				}
				else
				{
					CMCheckersBoard[i][k] = 0;
					continue;
				}
			}
			if (i == numRowsInBoardEmpty1 || i == numRowsInBoardEmpty2)
			{
				CMCheckersBoard[i][k] = 0;
				continue;
			}
			if (i < numRowsInBoardEmpty1 && i % 2 == ZERO)
			{
				if (k % 2 == ZERO)
				{
					CMCheckersBoard[i][k] = 0;
					continue;
				}
				else
				{
					CMCheckersBoard[i][k] = 1;
					continue;
				}
			}
			else if (i < numRowsInBoardEmpty1 && i % 2 != ZERO)
			{
				if (k % 2 == ZERO)
				{
					CMCheckersBoard[i][k] = 1;
					continue;
				}
				else
				{
					CMCheckersBoard[i][k] = 0;
					continue;
				}
			}
			if (i % 2 == ZERO && i > numRowsInBoardEmpty2)
			{
				if (k % 2 == ZERO)
				{
					CMCheckersBoard[i][k] = 0;
					continue;
				}
				else
				{
					CMCheckersBoard[i][k] = 4;
					continue;
				}
			}
			else
			{
				if (k % 2 == ZERO)
				{
					CMCheckersBoard[i][k] = 4;
					continue;
				}
				else
				{
					CMCheckersBoard[i][k] = 0;
					continue;
				}
			}
		}
	}

	//Calls the display board function to display the initial board
	DisplayBoard(CMCheckersBoard, numRowsInBoard);
}
/**
* @brief: Displays the game board
* @returns void
*/
void DisplayBoard(int CMCheckersBoard[MAX_ARRAY_SIZE][MAX_ARRAY_SIZE], int numRowsInBoard)
{
	//local variables//
	int i = 0;
	int k = 0;
	int NumrowsMinusOne = 0;
	NumrowsMinusOne = numRowsInBoard - 1;
	int squareCounter = 0;
	//local constants//
	const int EMPTY = 0;
	const string DISPLAYWK = "WK";
	const string DISPLAYWM = "WM";
	const string DISPLAYRS = "RS";
	const string DISPLAYRM = "RM";
	const string DISPLAYWS = "WS";
	const string DISPLAYRK = "RK";
	const int WIDTH = 4;
	const int ZERO = 0;

	//For loop to initialize board with correct properties//
	//and display to screen YAY							  //
	for (i = 0; i < numRowsInBoard; i++)
	{
		for (k = 0; k < numRowsInBoard; k++)
		{
			if (CMCheckersBoard[i][k] == EMPTY)
			{
				cout << setw(WIDTH) << squareCounter;
				squareCounter++;
				continue;
			}
			if (CMCheckersBoard[i][k] == REDSOLDIER)
			{
				cout << setw(WIDTH) << DISPLAYRS;
				squareCounter++;
				continue;
			}
			if (CMCheckersBoard[i][k] == WHITEMULE)
			{
				cout << setw(WIDTH) << DISPLAYWM;
				squareCounter++;
				continue;
			}
			if (CMCheckersBoard[i][k] == WHITESOLDIER)
			{
				cout << setw(WIDTH) << DISPLAYWS;
				squareCounter++;
				continue;
			}
			if (CMCheckersBoard[i][k] == REDMULE)
			{
				cout << setw(WIDTH) << DISPLAYRM;
				squareCounter++;
				continue;
			}
			if(CMCheckersBoard[i][k] == WHITEKING)
			{
				cout << setw(WIDTH) << DISPLAYWK;
				squareCounter++;
				continue;
			}
			if(CMCheckersBoard[i][k] == REDKING)
			{
				cout << setw(WIDTH) << DISPLAYRK;
				squareCounter++;
				continue;
			}
		}
		cout << endl;
	}
}
/**
* @brief: Determines the number of moves the selected piece can make
* @param1 The board array
* @param2 Rows in board
* @param3 Player
* @param4 Horizontal position of the piece
* @param5 Vertcal position of the piece4
* @returns int
*/
int CountJumps(int CMCheckersBoard[MAX_ARRAY_SIZE][MAX_ARRAY_SIZE], int numRowsInBoard, int player, int xLocArray[], int yLocArray[])
{
	//Declaring and initializing variables.
	int i = 0;
	int j = 0;
	int xindex = 0;
	int yindex = 0;
	int xLoc = 0;
	int yLoc = 0;
	int countjumps = 0;
	const int ZERO = 0;

	//Initializing both the arrays to -1.
	for (i = 0; i < numRowsInBoard; i++);
	{
		xLocArray[i] = -1;
	}

	for (i = 0; i < numRowsInBoard; i++);
	{
		yLocArray[i] = -1;
	}

	//If its the white player, the functon will check the white players checkers.
	//The fucntion IsJump will be called to check if the checker in question can jump
	//If it returns true, the countjumps will be incremented and the position of the 
	//checker will be stored in the unused location of the xLocArray and yLocArray respectively.
	if (player == WHITEPLAYER)
	{
		for (xindex = 0; xindex < numRowsInBoard; xindex++)
		{
			for (yindex = 0; yindex < numRowsInBoard; yindex++)
			{
				if (CMCheckersBoard[xindex][yindex] == WHITESOLDIER || CMCheckersBoard[xindex][yindex] == WHITEMULE || CMCheckersBoard[xindex][yindex] == WHITEKING)
				{
					IsJump(CMCheckersBoard, numRowsInBoard, player, xindex, yindex);
					if (IsJump(CMCheckersBoard, numRowsInBoard, player, xindex, yindex) == true)
					{
						countjumps++;
						xLocArray[xindex] = ZERO;
						yLocArray[yindex] = ZERO;
					}
				}
			}
		}
	}

	//If the player is red, the funcion will check the red players checkers.
	//The same sequence of logic is carried out.
		if (player == REDPLAYER)
		{
			for (xindex = 0; xindex < numRowsInBoard; xindex++)
			{
				for (yindex = 0; yindex < numRowsInBoard; yindex++)
				{
					if (CMCheckersBoard[xindex][yindex] == REDSOLDIER || CMCheckersBoard[xindex][yindex] == REDMULE || CMCheckersBoard[xindex][yindex] == REDKING)
					{
						IsJump(CMCheckersBoard, numRowsInBoard, player, xindex, yindex);
						if (IsJump(CMCheckersBoard, numRowsInBoard, player, xindex, yindex) == true)
						{
							countjumps++;
							xLocArray[xindex] = ZERO;
							yLocArray[yindex] = ZERO;
						}

					}
				}
			}
		}
	return countjumps;
}

bool CheckList(int inArray1[], int inArray2[], int xIndex, int yindex)
{
	int i = 0;
	int j = 0;

	for( i = 0; i < MAX_ARRAY_SIZE; i++)
	{
		for(j = 0; j < MAX_ARRAY_SIZE; j++)
		{
			if(inArray1[i] == xIndex && inArray2[j] == yindex)
			{
				return true;
			}
		}
	}
		return false;
}

int CountMove1Squares(int CMCheckersBoard[MAX_ARRAY_SIZE][MAX_ARRAY_SIZE], int numRowsInBoard, int player, int xLocArray[], int yLocArray[])
{
	int yLoc = 0;
	int xLoc = 0;
	int i = 0;
	int movesAvial = 0;
	int falsecounter = 0;

	if (player == REDPLAYER)
	{
		for (xLoc = 0; xLoc < numRowsInBoard; xLoc++)
		{
			for (yLoc = 0; yLoc < numRowsInBoard; yLoc++)
			{
				if (CMCheckersBoard[xLoc][yLoc] == REDSOLDIER || CMCheckersBoard[xLoc][yLoc] == REDMULE || CMCheckersBoard[xLoc][yLoc] == REDKING)
				{
					IsMove1Square(CMCheckersBoard, numRowsInBoard, player, xLoc, yLoc);
					if (IsMove1Square(CMCheckersBoard, numRowsInBoard, player, xLoc, yLoc) == true)
					{
						movesAvial++;
					}
				}
			}
		}
	}

	if (player == WHITEPLAYER)
	{
		for (xLoc = 0; xLoc < numRowsInBoard; xLoc++)
		{
			for (yLoc = 0; yLoc < numRowsInBoard; yLoc++)
			{
				if (CMCheckersBoard[xLoc][yLoc] == WHITESOLDIER || CMCheckersBoard[xLoc][yLoc] == WHITEMULE || CMCheckersBoard[xLoc][yLoc] == WHITEKING)
				{
					IsMove1Square(CMCheckersBoard, numRowsInBoard, player, xLoc, yLoc);
					if (IsMove1Square(CMCheckersBoard, numRowsInBoard, player, xLoc, yLoc) == true)
					{
						movesAvial++;
					}
				}
			}
		}
	}
	return movesAvial;
}

bool IsMove1Square(int CMCheckersBoard[MAX_ARRAY_SIZE][MAX_ARRAY_SIZE], int numRowsInBoard, int player, int xLoc, int yLoc)
{
	//local variables//
	int i = 0;
	int k = 0;
	//const locals  //
	const int ONE = 1;
	const int ZERO = 0;

	if (player == WHITEPLAYER)
	{
		if (CMCheckersBoard[xLoc][yLoc] == WHITESOLDIER || CMCheckersBoard[xLoc][yLoc] == WHITEMULE)
		{
			i = (xLoc + ONE);
			k = (yLoc + ONE);
			if (i > numRowsInBoard - ONE) // checks to see if i is off board//
			{
				return false;
			}
			if (k > (numRowsInBoard - ONE)) // checks to see if k is off board right side //
			{
				k = ZERO;
				if (CMCheckersBoard[i][k] != WHITEKING && CMCheckersBoard[i][k] != WHITESOLDIER && CMCheckersBoard[i][k] != WHITEMULE && CMCheckersBoard[i][k] != REDSOLDIER && CMCheckersBoard[i][k] != REDMULE && CMCheckersBoard[i][k] != REDKING)
				{
					return true;
				}
			}
			if (CMCheckersBoard[i][k] != WHITEKING && CMCheckersBoard[i][k] != WHITESOLDIER && CMCheckersBoard[i][k] != WHITEMULE && CMCheckersBoard[i][k] != REDSOLDIER && CMCheckersBoard[i][k] != REDMULE && CMCheckersBoard[i][k] != REDKING)
			{ // if k is not off board //
				return true;
			}
			k = (yLoc - ONE); // k is moved to the other diagonal //
			if (k < ZERO) // if k is off board left side //
			{
				k = numRowsInBoard - ONE;
				if (CMCheckersBoard[i][k] != WHITEKING && CMCheckersBoard[i][k] != WHITESOLDIER && CMCheckersBoard[i][k] != WHITEMULE && CMCheckersBoard[i][k] != REDSOLDIER && CMCheckersBoard[i][k] != REDMULE && CMCheckersBoard[i][k] != REDKING)
				{
					return true;
				}

			}
			if (CMCheckersBoard[i][k] != WHITEKING && CMCheckersBoard[i][k] != WHITESOLDIER && CMCheckersBoard[i][k] != WHITEMULE && CMCheckersBoard[i][k] != REDSOLDIER && CMCheckersBoard[i][k] != REDMULE && CMCheckersBoard[i][k] != REDKING)
			{ // if k is not off board left side //
				return true;
			}
			else // if nothing is met //
			{
				return false;
			}
		}
		if (CMCheckersBoard[xLoc][yLoc] == WHITEKING)
		{
			i = xLoc + ONE;
			k = yLoc + ONE;
			if (i > (numRowsInBoard - ONE)) //i off the board from top //
			{
				i = xLoc - ONE;
				if (k > (numRowsInBoard - ONE)) 
				{
					k = ZERO;
					if (CMCheckersBoard[i][k] != WHITEKING && CMCheckersBoard[i][k] != WHITESOLDIER && CMCheckersBoard[i][k] != WHITEMULE && CMCheckersBoard[i][k] != REDSOLDIER && CMCheckersBoard[i][k] != REDMULE && CMCheckersBoard[i][k] != REDKING)
					{
						return true;
					}
				}
				if (CMCheckersBoard[i][k] != WHITEKING && CMCheckersBoard[i][k] != WHITESOLDIER && CMCheckersBoard[i][k] != WHITEMULE && CMCheckersBoard[i][k] != REDSOLDIER && CMCheckersBoard[i][k] != REDMULE && CMCheckersBoard[i][k] != REDKING)
				{
					return true;
				}
				k = yLoc - ONE;
				if (k < ZERO)
				{
					if (CMCheckersBoard[i][k] != WHITEKING && CMCheckersBoard[i][k] != WHITESOLDIER && CMCheckersBoard[i][k] != WHITEMULE && CMCheckersBoard[i][k] != REDSOLDIER && CMCheckersBoard[i][k] != REDMULE && CMCheckersBoard[i][k] != REDKING)
					{
						return true;
					}
				}
				if (CMCheckersBoard[i][k] != WHITEKING && CMCheckersBoard[i][k] != WHITESOLDIER && CMCheckersBoard[i][k] != WHITEMULE && CMCheckersBoard[i][k] != REDSOLDIER && CMCheckersBoard[i][k] != REDMULE && CMCheckersBoard[i][k] != REDKING)
				{
					return true;
				}
				else
				{
					return false;
				}
			}
			i = xLoc - ONE;
			if (i < ZERO) // i off the board from bottom //
			{
				i = xLoc + ONE;
				if (k >(numRowsInBoard - ONE))
				{
					k = ZERO;
					if (CMCheckersBoard[i][k] != WHITEKING && CMCheckersBoard[i][k] != WHITESOLDIER && CMCheckersBoard[i][k] != WHITEMULE && CMCheckersBoard[i][k] != REDSOLDIER && CMCheckersBoard[i][k] != REDMULE && CMCheckersBoard[i][k] != REDKING)
					{
						return true;
					}
				}
				if (CMCheckersBoard[i][k] != WHITEKING && CMCheckersBoard[i][k] != WHITESOLDIER && CMCheckersBoard[i][k] != WHITEMULE && CMCheckersBoard[i][k] != REDSOLDIER && CMCheckersBoard[i][k] != REDMULE && CMCheckersBoard[i][k] != REDKING)
				{
					return true;
				}
				k = yLoc - ONE;
				if (k < ZERO)
				{
					if (CMCheckersBoard[i][k] != WHITEKING && CMCheckersBoard[i][k] != WHITESOLDIER && CMCheckersBoard[i][k] != WHITEMULE && CMCheckersBoard[i][k] != REDSOLDIER && CMCheckersBoard[i][k] != REDMULE && CMCheckersBoard[i][k] != REDKING)
					{
						return true;
					}
				}
				if (CMCheckersBoard[i][k] != WHITEKING && CMCheckersBoard[i][k] != WHITESOLDIER && CMCheckersBoard[i][k] != WHITEMULE && CMCheckersBoard[i][k] != REDSOLDIER && CMCheckersBoard[i][k] != REDMULE && CMCheckersBoard[i][k] != REDKING)
				{
					return true;
				}
				else
				{
					return false;
				}
			}
			i = xLoc + ONE;
			if (k > (numRowsInBoard - ONE)) //i(+) k off board right //
			{
				k = ZERO;
				if (CMCheckersBoard[i][k] != WHITEKING && CMCheckersBoard[i][k] != WHITESOLDIER && CMCheckersBoard[i][k] != WHITEMULE && CMCheckersBoard[i][k] != REDSOLDIER && CMCheckersBoard[i][k] != REDMULE && CMCheckersBoard[i][k] != REDKING)
				{
					return true;
				}
			}
			if (CMCheckersBoard[i][k] != WHITEKING && CMCheckersBoard[i][k] != WHITESOLDIER && CMCheckersBoard[i][k] != WHITEMULE && CMCheckersBoard[i][k] != REDSOLDIER && CMCheckersBoard[i][k] != REDMULE && CMCheckersBoard[i][k] != REDKING)
			{ // if k isnt off the board right //
				return true;
			}
			k = yLoc - ONE; // left diagonal //
			if (k < ZERO) // i(+) k off the board left //
			{
				k = numRowsInBoard - ONE;
				if (CMCheckersBoard[i][k] != WHITEKING && CMCheckersBoard[i][k] != WHITESOLDIER && CMCheckersBoard[i][k] != WHITEMULE && CMCheckersBoard[i][k] != REDSOLDIER && CMCheckersBoard[i][k] != REDMULE && CMCheckersBoard[i][k] != REDKING)
				{
					return true;
				}
			}
			if (CMCheckersBoard[i][k] != WHITEKING && CMCheckersBoard[i][k] != WHITESOLDIER && CMCheckersBoard[i][k] != WHITEMULE && CMCheckersBoard[i][k] != REDSOLDIER && CMCheckersBoard[i][k] != REDMULE && CMCheckersBoard[i][k] != REDKING)
			{ // if k isnt off the board left //
				return true;
			}
			i = xLoc - ONE; // i moved down //
			if(k < ZERO) // i(-) and k off the board left //
			{
				k = numRowsInBoard-ONE;
				if (CMCheckersBoard[i][k] != WHITEKING && CMCheckersBoard[i][k] != WHITESOLDIER && CMCheckersBoard[i][k] != WHITEMULE && CMCheckersBoard[i][k] != REDSOLDIER && CMCheckersBoard[i][k] != REDMULE && CMCheckersBoard[i][k] != REDKING)
				{
					return true;
				}
			}
			if (CMCheckersBoard[i][k] != WHITEKING && CMCheckersBoard[i][k] != WHITESOLDIER && CMCheckersBoard[i][k] != WHITEMULE && CMCheckersBoard[i][k] != REDSOLDIER && CMCheckersBoard[i][k] != REDMULE && CMCheckersBoard[i][k] != REDKING)
			{ // if k is not off the board //
				return true;
			}
			k = yLoc + ONE;
			if (k > numRowsInBoard - ONE) // if i(-) and k off the board right //
			{
				k = ZERO; // k is reset to 0 //
				if (CMCheckersBoard[i][k] != WHITEKING && CMCheckersBoard[i][k] != WHITESOLDIER && CMCheckersBoard[i][k] != WHITEMULE && CMCheckersBoard[i][k] != REDSOLDIER && CMCheckersBoard[i][k] != REDMULE && CMCheckersBoard[i][k] != REDKING)
				{
					return true;
				}
			}
			if (CMCheckersBoard[i][k] != WHITEKING && CMCheckersBoard[i][k] != WHITESOLDIER && CMCheckersBoard[i][k] != WHITEMULE && CMCheckersBoard[i][k] != REDSOLDIER && CMCheckersBoard[i][k] != REDMULE && CMCheckersBoard[i][k] != REDKING)
			{ // if i(-) and k not off the board //
				return true;
			}
			else // if nothing is met returns false //
			{
				return false;

			}
		}
	}

	if (player == REDPLAYER)
	{
		if (CMCheckersBoard[xLoc][yLoc] == REDMULE || CMCheckersBoard[xLoc][yLoc] == REDSOLDIER)
		{
			i = (xLoc - ONE);
			k = (yLoc - ONE);
			if (i < ZERO) // checks if i is off the board automatic false//
			{
				return false;
			}
			if (k < ZERO) // if k is off of board to the left //
			{
				k = numRowsInBoard- ONE;
				if (CMCheckersBoard[i][k] != WHITEKING && CMCheckersBoard[i][k] != WHITESOLDIER && CMCheckersBoard[i][k] != WHITEMULE && CMCheckersBoard[i][k] != REDSOLDIER && CMCheckersBoard[i][k] != REDMULE && CMCheckersBoard[i][k] != REDKING)
				{
					return true;
				}
			}
			if (CMCheckersBoard[i][k] != WHITEKING && CMCheckersBoard[i][k] != WHITESOLDIER && CMCheckersBoard[i][k] != WHITEMULE && CMCheckersBoard[i][k] != REDSOLDIER && CMCheckersBoard[i][k] != REDMULE && CMCheckersBoard[i][k] != REDKING)
			{ // if k isnt off the board to the left //
				return true;
			}
			k = (yLoc + ONE); // k is incremented one right //
			if (k > numRowsInBoard- ONE) // if k is off the board right //
			{
				k = ZERO; // k is sent to the other end and checks spot//
				if (CMCheckersBoard[i][k] != WHITEKING && CMCheckersBoard[i][k] != WHITESOLDIER && CMCheckersBoard[i][k] != WHITEMULE && CMCheckersBoard[i][k] != REDSOLDIER && CMCheckersBoard[i][k] != REDMULE && CMCheckersBoard[i][k] != REDKING)
				{
					return true;
				}

			}
			if (CMCheckersBoard[i][k] != WHITEKING && CMCheckersBoard[i][k] != WHITESOLDIER && CMCheckersBoard[i][k] != WHITEMULE && CMCheckersBoard[i][k] != REDSOLDIER && CMCheckersBoard[i][k] != REDMULE && CMCheckersBoard[i][k] != REDKING)
			{ // if k is not off board //
				return true;
			}
			else // if everything is not met //
			{
				return false;
			}
		}
		if (CMCheckersBoard[xLoc][yLoc] == REDKING)
		{
			i = xLoc - ONE;
			k = yLoc - ONE;
			if (i < ZERO) // if i is off the board top //
			{
				i = xLoc + ONE; // checks the bottom instead of the top //
				if (k < ZERO) // if k is off the board left side //
				{
					k = numRowsInBoard-ONE; // sents to the right side //
					if (CMCheckersBoard[i][k] != WHITEKING && CMCheckersBoard[i][k] != WHITESOLDIER && CMCheckersBoard[i][k] != WHITEMULE && CMCheckersBoard[i][k] != REDSOLDIER && CMCheckersBoard[i][k] != REDMULE && CMCheckersBoard[i][k] != REDKING)
					{
						return true;
					}
				}
				if (CMCheckersBoard[i][k] != WHITEKING && CMCheckersBoard[i][k] != WHITESOLDIER && CMCheckersBoard[i][k] != WHITEMULE && CMCheckersBoard[i][k] != REDSOLDIER && CMCheckersBoard[i][k] != REDMULE && CMCheckersBoard[i][k] != REDKING)
				{ // if k is not off the board left side //
					return true;
				}
				k = yLoc + ONE; // k is changed to the other diagonal //
				if (k > numRowsInBoard-ONE) // if k is off the board right side //
				{
					if (CMCheckersBoard[i][k] != WHITEKING && CMCheckersBoard[i][k] != WHITESOLDIER && CMCheckersBoard[i][k] != WHITEMULE && CMCheckersBoard[i][k] != REDSOLDIER && CMCheckersBoard[i][k] != REDMULE && CMCheckersBoard[i][k] != REDKING)
					{
						return true;
					}
				}
				if (CMCheckersBoard[i][k] != WHITEKING && CMCheckersBoard[i][k] != WHITESOLDIER && CMCheckersBoard[i][k] != WHITEMULE && CMCheckersBoard[i][k] != REDSOLDIER && CMCheckersBoard[i][k] != REDMULE && CMCheckersBoard[i][k] != REDKING)
				{ // if k is not off board right side //
					return true;
				}
				else // if everything is false //
				{
					return false;
				}
			}
			if (k < ZERO) // if i is not off the board top side but k is off leftside //
			{
				k = numRowsInBoard-ONE; // sents k to right side to check for empty space //
				if (CMCheckersBoard[i][k] != WHITEKING && CMCheckersBoard[i][k] != WHITESOLDIER && CMCheckersBoard[i][k] != WHITEMULE && CMCheckersBoard[i][k] != REDSOLDIER && CMCheckersBoard[i][k] != REDMULE && CMCheckersBoard[i][k] != REDKING)
				{
					return true;
				}
			}
			if (CMCheckersBoard[i][k] != WHITEKING && CMCheckersBoard[i][k] != WHITESOLDIER && CMCheckersBoard[i][k] != WHITEMULE && CMCheckersBoard[i][k] != REDSOLDIER && CMCheckersBoard[i][k] != REDMULE && CMCheckersBoard[i][k] != REDKING)
			{ // if k is not off the board leftside
				return true;
			}
			k = yLoc + ONE; // k is changed to the other diagonal //
			if (k > numRowsInBoard-ONE) // checks to see if k is off the board rigt side //
			{
				if (CMCheckersBoard[i][k] != WHITEKING && CMCheckersBoard[i][k] != WHITESOLDIER && CMCheckersBoard[i][k] != WHITEMULE && CMCheckersBoard[i][k] != REDSOLDIER && CMCheckersBoard[i][k] != REDMULE && CMCheckersBoard[i][k] != REDKING)
				{
					return true;
				}
			}
			if (CMCheckersBoard[i][k] != WHITEKING && CMCheckersBoard[i][k] != WHITESOLDIER && CMCheckersBoard[i][k] != WHITEMULE && CMCheckersBoard[i][k] != REDSOLDIER && CMCheckersBoard[i][k] != REDMULE && CMCheckersBoard[i][k] != REDKING)
			{ // if k is not off the board right side //
				return true;
			}
			i = xLoc + ONE; // checks behind the pieces diagonally //
			if (k > numRowsInBoard - ONE) // checks if k is off the board from the right side //
			{
				k = ZERO; // changes to the other side //
				if (CMCheckersBoard[i][k] != WHITEKING && CMCheckersBoard[i][k] != WHITESOLDIER && CMCheckersBoard[i][k] != WHITEMULE && CMCheckersBoard[i][k] != REDSOLDIER && CMCheckersBoard[i][k] != REDMULE && CMCheckersBoard[i][k] != REDKING)
				{
					return true;
				}
			}
			if (CMCheckersBoard[i][k] != WHITEKING && CMCheckersBoard[i][k] != WHITESOLDIER && CMCheckersBoard[i][k] != WHITEMULE && CMCheckersBoard[i][k] != REDSOLDIER && CMCheckersBoard[i][k] != REDMULE && CMCheckersBoard[i][k] != REDKING)
			{ // if not off board from the right side //
				return true;
			}
			k = yLoc - ONE;
			if (k < ZERO) // if off board left side //
			{
				k = numRowsInBoard - ONE; // sends to other side //
				if (CMCheckersBoard[i][k] != WHITEKING && CMCheckersBoard[i][k] != WHITESOLDIER && CMCheckersBoard[i][k] != WHITEMULE && CMCheckersBoard[i][k] != REDSOLDIER && CMCheckersBoard[i][k] != REDMULE && CMCheckersBoard[i][k] != REDKING)
				{
					return true;
				}
			}
			if (CMCheckersBoard[i][k] != WHITEKING && CMCheckersBoard[i][k] != WHITESOLDIER && CMCheckersBoard[i][k] != WHITEMULE && CMCheckersBoard[i][k] != REDSOLDIER && CMCheckersBoard[i][k] != REDMULE && CMCheckersBoard[i][k] != REDKING)
			{ // if not off board left side //
				return true;
			}
			else // if nothing is met //
			{
				return false;

			}
		}
	}
	return 0;
}

bool IsJump(int CMCheckersBoard[MAX_ARRAY_SIZE][MAX_ARRAY_SIZE], int numRowsInBoard, int player, int xLoc, int yLoc)
{
	//local variables//
	int i = 0;
	int k = 0;
	int counter = 0;
	//local constants//
	const int ZERO = 0;
	const int ONE = 1;
	const int TWO = 2;
	if (player == WHITEPLAYER)
	{
		if (CMCheckersBoard[xLoc][yLoc] == WHITEMULE || CMCheckersBoard[xLoc][yLoc] == WHITESOLDIER)
		{
			i = xLoc + ONE;
			k = yLoc + ONE;
			if (i > numRowsInBoard - ONE) // if i is off board automatic false //
			{
				return false;
			}
			if (k > numRowsInBoard - ONE) // if k is off board right side //
			{
				k = ZERO; // k is sent to the other side //
			}
			if (CMCheckersBoard[i][k] == REDMULE || CMCheckersBoard[i][k] == REDSOLDIER || CMCheckersBoard[i][k] == REDKING)
			{ // checks if there is an enemy piece //
				i = i + ONE; // diagonally one more step forward //
				k = k + ONE; // diagonally one more step forward //
				if (i > numRowsInBoard - ONE) // if i is off board automatic false //
				{
					return false; // cause it cannot check the other side it will go off board there too //
				}
				if (k > numRowsInBoard - ONE)
				{
					k = ZERO; // goes to the other side to see if there is an empty piece //
				}
				if (CMCheckersBoard[i][k] != WHITEKING && CMCheckersBoard[i][k] != WHITESOLDIER && CMCheckersBoard[i][k] != WHITEMULE && CMCheckersBoard[i][k] != REDSOLDIER && CMCheckersBoard[i][k] != REDMULE && CMCheckersBoard[i][k] != REDKING)
				{ // if k doesnt go to the other side if it is jumpable //
					return true;
				}
			}
			k = yLoc - ONE; // reset k value //
			i = xLoc + ONE; // reset i value //
			if (k < ZERO) // if k is off board left side //
			{
				k = numRowsInBoard - ONE;
			}
			if (CMCheckersBoard[i][k] == REDMULE || CMCheckersBoard[i][k] == REDSOLDIER || CMCheckersBoard[i][k] == REDKING)
			{// see if the piece is jumpable //
				i = i + ONE; // increment diagonally //
				k = k - ONE; 
				if (i > numRowsInBoard - ONE) // if i is off board automatic false //
				{
					return false;
				}
				if (k < ZERO) // checks off the board left side //
				{
					k = numRowsInBoard - ONE; // k reset to other end //
				}
				if (CMCheckersBoard[i][k] != WHITEKING && CMCheckersBoard[i][k] != WHITESOLDIER && CMCheckersBoard[i][k] != WHITEMULE && CMCheckersBoard[i][k] != REDSOLDIER && CMCheckersBoard[i][k] != REDMULE && CMCheckersBoard[i][k] != REDKING)
				{ // if there is an emty space there //
					return true;
				}
			}
			else // if everything is unmet up to this //
			{
				return false;
			}
		}
		if (CMCheckersBoard[xLoc][yLoc] == WHITEKING)
		{
			i = xLoc + ONE; // off board increment, will be reset just incase //
			k = yLoc + ONE;
			if (i > numRowsInBoard-ONE) // if i is off board bottom side //
			{
				i = xLoc - ONE; // checks behind piece //
				if(k > numRowsInBoard - ONE) // if k is off board right side //
				{
					k = ZERO; // sent to other side //
				}
				if (CMCheckersBoard[i][k] == REDMULE || CMCheckersBoard[i][k] == REDSOLDIER || CMCheckersBoard[i][k] == REDKING)
				{ // if there is an enemy piece //
					i = i - ONE; // moved diagonally one space behind //
					k = k + ONE;
					if(k>numRowsInBoard -ONE)
					{ // k off board rightside //
						k = ZERO; // k value sent to other side //
					}
					if (CMCheckersBoard[i][k] != WHITEKING && CMCheckersBoard[i][k] != WHITESOLDIER && CMCheckersBoard[i][k] != WHITEMULE && CMCheckersBoard[i][k] != REDSOLDIER && CMCheckersBoard[i][k] != REDMULE && CMCheckersBoard[i][k] != REDKING)
					{ // checks to see if there is a piece there //
						return true;
					}
				}
				i = xLoc - ONE; // reset i value //
				k = yLoc - ONE; // checking other diagonal //
				if(k < ZERO) // off board left side //
				{ 
					k = numRowsInBoard - ONE; // send to the other side //
				}
				if (CMCheckersBoard[i][k] == REDMULE || CMCheckersBoard[i][k] == REDSOLDIER || CMCheckersBoard[i][k] == REDKING)
				{ // checks if there is enemy peice there //
					i = i - ONE;
					k = k - ONE;
					if(k < ZERO)
					{
						k = numRowsInBoard - ONE;
					}
					if (CMCheckersBoard[i][k] != WHITEKING && CMCheckersBoard[i][k] != WHITESOLDIER && CMCheckersBoard[i][k] != WHITEMULE && CMCheckersBoard[i][k] != REDSOLDIER && CMCheckersBoard[i][k] != REDMULE && CMCheckersBoard[i][k] != REDKING)
					{ // checks if there is a diagonal empty space behind the enemy piece //
						return true;
					}
				}
				else // if everything is false up to this point //
				{
					return false;
				}

			}
			i = xLoc - ONE; // off board increment will be reset(LATER) it check other side //
			k = yLoc - ONE;
			if (i < ZERO) // if i is off board top side //
			{
				i = xLoc + ONE; // i is now checking front of the piece //
				if(k < ZERO) // checks if k is off board //
				{
					k = numRowsInBoard - ONE;
				}
				if (CMCheckersBoard[i][k] == REDMULE || CMCheckersBoard[i][k] == REDSOLDIER || CMCheckersBoard[i][k] == REDKING)
				{ // checks if there is an enemy piece there //
					i = i + ONE; 
					k = k - ONE;
					if ( k < ZERO) // if k is out left side //
					{
						k = numRowsInBoard - ONE;
					}
					if (CMCheckersBoard[i][k] != WHITEKING && CMCheckersBoard[i][k] != WHITESOLDIER && CMCheckersBoard[i][k] != WHITEMULE && CMCheckersBoard[i][k] != REDSOLDIER && CMCheckersBoard[i][k] != REDMULE && CMCheckersBoard[i][k] != REDKING)
					{ // checks if there is a piece diagonally behind the enemy piece //
						return true;
					}
					
				}
				i = xLoc + ONE;
				k = yLoc + ONE;
				if(k > numRowsInBoard - ONE) // checks if k is off board right side //
				{
					k = ZERO; // sents k to other side //
				}
				if (CMCheckersBoard[i][k] == REDMULE || CMCheckersBoard[i][k] == REDSOLDIER || CMCheckersBoard[i][k] == REDKING)
				{ // checks if there is an enemy pice //
					i = i + ONE; // increments diagonally // 
					k = k + ONE;
					if(k > numRowsInBoard - ONE) // checks if k is off the board //
					{
						k = ZERO; // resets the value of k to 0 //
					}
					if (CMCheckersBoard[i][k] != WHITEKING && CMCheckersBoard[i][k] != WHITESOLDIER && CMCheckersBoard[i][k] != WHITEMULE && CMCheckersBoard[i][k] != REDSOLDIER && CMCheckersBoard[i][k] != REDMULE && CMCheckersBoard[i][k] != REDKING)
					{ // checks if there is an empty space behind the piece diagonally //
						return true;
					}
				}
				else // if everything up to this is false then there is no jump avail //
				{
					return false;
				}
			}
			counter = ZERO;
			i = xLoc + ONE; // reset  i and k values //
			k = yLoc + ONE;
			if( k > numRowsInBoard - ONE) // sees if k is off board //
			{
				k = ZERO; // k is sent to other side //
			}
			if (CMCheckersBoard[i][k] == REDMULE || CMCheckersBoard[i][k] == REDSOLDIER || CMCheckersBoard[i][k] == REDKING)
			{ // checks if there is an enemy piece there //
				i = i + ONE; // increments diagonally //
				k = k + ONE;
				if( i > numRowsInBoard - ONE) // checks if i is off board //
				{
					counter++; // counter if i is off board so we dont use goto statements //
				}
				if(k > numRowsInBoard - ONE) // k is off board right side //
				{ 
					k = ZERO; // reset k to 0 //
				}
				if (CMCheckersBoard[i][k] != WHITEKING && CMCheckersBoard[i][k] != WHITESOLDIER && CMCheckersBoard[i][k] != WHITEMULE && CMCheckersBoard[i][k] != REDSOLDIER && CMCheckersBoard[i][k] != REDMULE && CMCheckersBoard[i][k] != REDKING)
				{ // checks if there is an empty space //
					if(counter != ONE) // check if i went off board //
					{
						return true;
					}
					counter = ZERO; // resets counter so it can be used again //
				}
			}
			counter = ZERO;
			i = xLoc + ONE; // reset i value //
			k = yLoc - ONE; // checks other side //
			if ( k < ZERO) // checks iff k is oof board left side //
			{
				k = numRowsInBoard - ONE; // sends to the other side //
			}
			if (CMCheckersBoard[i][k] == REDMULE || CMCheckersBoard[i][k] == REDSOLDIER || CMCheckersBoard[i][k] == REDKING)
			{
				i = i + ONE;
				k = k - ONE;
				if(i > numRowsInBoard - ONE)
				{
					counter++;
				}
				if(k < ZERO)
				{
					k = numRowsInBoard - ONE;
				}
				if (CMCheckersBoard[i][k] != WHITEKING && CMCheckersBoard[i][k] != WHITESOLDIER && CMCheckersBoard[i][k] != WHITEMULE && CMCheckersBoard[i][k] != REDSOLDIER && CMCheckersBoard[i][k] != REDMULE && CMCheckersBoard[i][k] != REDKING)
				{
					if(counter != ONE)
					{
						return true;
					}
					counter = ZERO;
				}
			}
			counter = ZERO;
			i = xLoc - ONE; // reset i value //
			k = yLoc + ONE; // checks other side //
			if ( k > numRowsInBoard - ONE) // checks iff k is off board right side //
			{
				k = ZERO; // sends to the other side //
			}
			if (CMCheckersBoard[i][k] == REDMULE || CMCheckersBoard[i][k] == REDSOLDIER || CMCheckersBoard[i][k] == REDKING)
			{ // checks if there is an enemy piece there //
				i = i - ONE; // increments diagonally //
				k = k + ONE;
				if(i < ZERO) // checks if i is 0 and therefore always empty off board //
				{
					counter++;
				}
				if (k > numRowsInBoard-ONE) // checks if k is off board //
				{
					k = ZERO; // sends k to other side //
				}
				if (CMCheckersBoard[i][k] != WHITEKING && CMCheckersBoard[i][k] != WHITESOLDIER && CMCheckersBoard[i][k] != WHITEMULE && CMCheckersBoard[i][k] != REDSOLDIER && CMCheckersBoard[i][k] != REDMULE && CMCheckersBoard[i][k] != REDKING)
				{ // checks if it is empty //
					if(counter != ONE) // checks if i is not off board //
					{
						return true;
					}
					counter = ZERO;
				}
			}
			counter = ZERO;
			i = xLoc - ONE; // reset i value //
			k = yLoc - ONE; // checks other side //
			if ( k < ZERO) // checks if k is oof board left side //
			{
				k = numRowsInBoard - ONE; // sends to the other side //
			}
			if (CMCheckersBoard[i][k] == REDMULE || CMCheckersBoard[i][k] == REDSOLDIER || CMCheckersBoard[i][k] == REDKING)
			{
				i = i - ONE;
				k = k - ONE;
				if(i < ZERO) // checks if i is off board //
				{
					counter++;
				}
				if( k < ZERO) // checks if k is off board left side //
				{
					k = numRowsInBoard - ONE; // sends k to other side //
				}
				if (CMCheckersBoard[i][k] != WHITEKING && CMCheckersBoard[i][k] != WHITESOLDIER && CMCheckersBoard[i][k] != WHITEMULE && CMCheckersBoard[i][k] != REDSOLDIER && CMCheckersBoard[i][k] != REDMULE && CMCheckersBoard[i][k] != REDKING)
				{ // checks if there is an empty spot //
					if(counter != ONE) // checks if i went off board //
					{
						return true;
					}
					counter = ZERO; // reset counter //
				}
			}
			else
			{
				return false;
			}
	    }
	}
	if ( player == REDPLAYER )
	{
		if (CMCheckersBoard[xLoc][yLoc] == REDMULE || CMCheckersBoard[xLoc][yLoc] == REDSOLDIER)
		{
			i = xLoc - ONE;
			k = yLoc - ONE;
			if (i < ZERO) // if i is off board automatic false //
			{
				return false;
			}
			if (k < ZERO) // if k is off board LEFT side //
			{
				k = numRowsInBoard-ONE; // k is 0 //
			}
			if (CMCheckersBoard[i][k] == WHITEMULE || CMCheckersBoard[i][k] == WHITESOLDIER || CMCheckersBoard[i][k] == WHITEKING)
			{ // checks if there is an enemy piece //
				i = i - ONE; // diagonally one more step forward //
				k = k - ONE; // diagonally one more step forward //
				if (i < ZERO) // if i is off board automatic false //
				{
					return false;
				}
				if (k < ZERO)
				{
					k = numRowsInBoard - ONE; // goes to the other side to see if there is an empty piece //
				}
				if (CMCheckersBoard[i][k] != WHITEKING && CMCheckersBoard[i][k] != WHITESOLDIER && CMCheckersBoard[i][k] != WHITEMULE && CMCheckersBoard[i][k] != REDSOLDIER && CMCheckersBoard[i][k] != REDMULE && CMCheckersBoard[i][k] != REDKING)
				{ // if k doesnt go to the other side if it is jumpable //
					return true;
				}
			}
			k = yLoc + ONE; // reset k value //
			i = xLoc - ONE; // reset i value //
			if (k > numRowsInBoard - ONE) // if k is off board RIGHT side //
			{
				k = ZERO;
			}
			if (CMCheckersBoard[i][k] == WHITEMULE || CMCheckersBoard[i][k] == WHITESOLDIER || CMCheckersBoard[i][k] == WHITEKING)
			{// see if the piece is jumpable //
				i = i - ONE; // increment diagonally //
				k = k + ONE; 
				if (i < ZERO) // if i is off board automatic false //
				{
					return false;
				}
				if (k > numRowsInBoard - ONE) // checks off the board left side //
				{
					k = ZERO; // k reset to other end //
				}
				if (CMCheckersBoard[i][k] != WHITEKING && CMCheckersBoard[i][k] != WHITESOLDIER && CMCheckersBoard[i][k] != WHITEMULE && CMCheckersBoard[i][k] != REDSOLDIER && CMCheckersBoard[i][k] != REDMULE && CMCheckersBoard[i][k] != REDKING)
				{ // if there is an emty space there //
					return true;
				}
			}
			else // if everything is unmet up to this //
			{
				return false;
			}
		}
		if (CMCheckersBoard[xLoc][yLoc] == REDKING)
		{
			i = xLoc + ONE; // off board increment, will be reset just incase //
			k = yLoc + ONE;
			if (i > numRowsInBoard-ONE) // if i is off board bottom side //
			{
				i = xLoc - ONE; // checks behind piece //
				if(k > numRowsInBoard - ONE) // if k is off board right side //
				{
					k = ZERO; // sent to other side //
				}
				if (CMCheckersBoard[i][k] == WHITEMULE || CMCheckersBoard[i][k] == WHITESOLDIER || CMCheckersBoard[i][k] == WHITEKING)
				{ // if there is an enemy piece //
					i = i - ONE; // moved diagonally one space behind //
					k = k + ONE;
					if(k>numRowsInBoard -ONE)
					{ // k off board rightside //
						k = ZERO; // k value sent to other side //
					}
					if (CMCheckersBoard[i][k] != WHITEKING && CMCheckersBoard[i][k] != WHITESOLDIER && CMCheckersBoard[i][k] != WHITEMULE && CMCheckersBoard[i][k] != REDSOLDIER && CMCheckersBoard[i][k] != REDMULE && CMCheckersBoard[i][k] != REDKING)
					{ // checks to see if there is a piece there //
						return true;
					}
				}
				i = xLoc - ONE; // reset i value //
				k = yLoc - ONE; // checking other diagonal //
				if(k < ZERO) // off board left side //
				{ 
					k = numRowsInBoard - ONE; // send to the other side //
				}
				if (CMCheckersBoard[i][k] == WHITEMULE || CMCheckersBoard[i][k] == WHITESOLDIER || CMCheckersBoard[i][k] == WHITEKING)
				{ // checks if there is enemy peice there //
					i = i - ONE;
					k = k - ONE;
					if(k < ZERO)
					{
						k = numRowsInBoard - ONE;
					}
					if (CMCheckersBoard[i][k] != WHITEKING && CMCheckersBoard[i][k] != WHITESOLDIER && CMCheckersBoard[i][k] != WHITEMULE && CMCheckersBoard[i][k] != REDSOLDIER && CMCheckersBoard[i][k] != REDMULE && CMCheckersBoard[i][k] != REDKING)
					{ // checks if there is a diagonal empty space behind the enemy piece //
						return true;
					}
				}
				else // if everything is false up to this point //
				{
					return false;
				}

			}
			i = xLoc - ONE; // off board increment will be reset(LATER) it check other side //
			k = yLoc - ONE;
			if (i < ZERO) // if i is off board top side //
			{
				i = xLoc + ONE; // i is now checking front of the piece //
				if(k < ZERO) // checks if k is off board //
				{
					k = numRowsInBoard - ONE;
				}
				if (CMCheckersBoard[i][k] == WHITEMULE || CMCheckersBoard[i][k] == WHITESOLDIER || CMCheckersBoard[i][k] == WHITEKING)
				{ // checks if there is an enemy piece there //
					i = i + ONE; 
					k = k - ONE;
					if ( k < ZERO) // if k is out left side //
					{
						k = numRowsInBoard - ONE;
					}
					if (CMCheckersBoard[i][k] != WHITEKING && CMCheckersBoard[i][k] != WHITESOLDIER && CMCheckersBoard[i][k] != WHITEMULE && CMCheckersBoard[i][k] != REDSOLDIER && CMCheckersBoard[i][k] != REDMULE && CMCheckersBoard[i][k] != REDKING)
					{ // checks if there is a piece diagonally behind the enemy piece //
						return true;
					}
					
				}
				i = xLoc + ONE;
				k = yLoc + ONE;
				if(k > numRowsInBoard - ONE) // checks if k is off board right side //
				{
					k = ZERO; // sents k to other side //
				}
				if (CMCheckersBoard[i][k] == WHITEMULE || CMCheckersBoard[i][k] == WHITESOLDIER || CMCheckersBoard[i][k] == WHITEKING)
				{ // checks if there is an enemy pice //
					i = i + ONE; // increments diagonally // 
					k = k + ONE;
					if(k > numRowsInBoard - ONE) // checks if k is off the board //
					{
						k = ZERO; // resets the value of k to 0 //
					}
					if (CMCheckersBoard[i][k] != WHITEKING && CMCheckersBoard[i][k] != WHITESOLDIER && CMCheckersBoard[i][k] != WHITEMULE && CMCheckersBoard[i][k] != REDSOLDIER && CMCheckersBoard[i][k] != REDMULE && CMCheckersBoard[i][k] != REDKING)
					{ // checks if there is an empty space behind the piece diagonally //
						return true;
					}
				}
				else // if everything up to this is false then there is no jump avail //
				{
					return false;
				}
			}
			counter = ZERO;
			i = xLoc + ONE; // reset  i and k values //
			k = yLoc + ONE;
			if( k > numRowsInBoard - ONE) // sees if k is off board //
			{
				k = ZERO; // k is sent to other side //
			}
			if (CMCheckersBoard[i][k] == WHITEMULE || CMCheckersBoard[i][k] == WHITESOLDIER || CMCheckersBoard[i][k] == WHITEKING)
			{ // checks if there is an enemy piece there //
				i = i + ONE; // increments diagonally //
				k = k + ONE;
				if( i > numRowsInBoard - ONE) // checks if i is off board //
				{
					counter++; // counter if i is off board so we dont use goto statements //
				}
				if(k > numRowsInBoard - ONE) // k is off board right side //
				{ 
					k = ZERO; // reset k to 0 //
				}
				if (CMCheckersBoard[i][k] != WHITEKING && CMCheckersBoard[i][k] != WHITESOLDIER && CMCheckersBoard[i][k] != WHITEMULE && CMCheckersBoard[i][k] != REDSOLDIER && CMCheckersBoard[i][k] != REDMULE && CMCheckersBoard[i][k] != REDKING)
				{ // checks if there is an empty space //
					if(counter != ONE) // check if i went off board //
					{
						return true;
					}
					counter = ZERO; // resets counter so it can be used again //
				}
			}
			counter = ZERO;
			i = xLoc + ONE; // reset i value //
			k = yLoc - ONE; // checks other side //
			if ( k < ZERO) // checks iff k is oof board left side //
			{
				k = numRowsInBoard - ONE; // sends to the other side //
			}
			if (CMCheckersBoard[i][k] == WHITEMULE || CMCheckersBoard[i][k] == WHITESOLDIER || CMCheckersBoard[i][k] == WHITEKING)
			{
				i = i + ONE;
				k = k - ONE;
				if(i > numRowsInBoard - ONE)
				{
					counter++;
				}
				if(k < ZERO)
				{
					k = numRowsInBoard - ONE;
				}
				if (CMCheckersBoard[i][k] != WHITEKING && CMCheckersBoard[i][k] != WHITESOLDIER && CMCheckersBoard[i][k] != WHITEMULE && CMCheckersBoard[i][k] != REDSOLDIER && CMCheckersBoard[i][k] != REDMULE && CMCheckersBoard[i][k] != REDKING)
				{
					if(counter != ONE)
					{
						return true;
					}
					counter = ZERO;
				}
			}
			counter = ZERO;
			i = xLoc - ONE; // reset i value //
			k = yLoc + ONE; // checks other side //
			if ( k > numRowsInBoard - ONE) // checks iff k is off board right side //
			{
				k = ZERO; // sends to the other side //
			}
			if (CMCheckersBoard[i][k] == WHITEMULE || CMCheckersBoard[i][k] == WHITESOLDIER || CMCheckersBoard[i][k] == WHITEKING)
			{ // checks if there is an enemy piece there //
				i = i - ONE; // increments diagonally //
				k = k + ONE;
				if(i < ZERO) // checks if i is 0 and therefore always empty off board //
				{
					counter++;
				}
				if (k > numRowsInBoard-ONE) // checks if k is off board //
				{
					k = ZERO; // sends k to other side //
				}
				if (CMCheckersBoard[i][k] != WHITEKING && CMCheckersBoard[i][k] != WHITESOLDIER && CMCheckersBoard[i][k] != WHITEMULE && CMCheckersBoard[i][k] != REDSOLDIER && CMCheckersBoard[i][k] != REDMULE && CMCheckersBoard[i][k] != REDKING)
				{ // checks if it is empty //
					if(counter != ONE) // checks if i is not off board //
					{
						return true;
					}
					counter = ZERO;
				}
			}
			counter = ZERO;
			i = xLoc - ONE; // reset i value //
			k = yLoc - ONE; // checks other side //
			if ( k < ZERO) // checks if k is oof board left side //
			{
				k = numRowsInBoard - ONE; // sends to the other side //
			}
			if (CMCheckersBoard[i][k] == WHITEMULE || CMCheckersBoard[i][k] == WHITESOLDIER || CMCheckersBoard[i][k] == WHITEKING)
			{
				i = i - ONE;
				k = k - ONE;
				if(i < ZERO) // checks if i is off board //
				{
					counter++;
				}
				if( k < ZERO) // checks if k is off board left side //
				{
					k = numRowsInBoard - ONE; // sends k to other side //
				}
				if (CMCheckersBoard[i][k] != WHITEKING && CMCheckersBoard[i][k] != WHITESOLDIER && CMCheckersBoard[i][k] != WHITEMULE && CMCheckersBoard[i][k] != REDSOLDIER && CMCheckersBoard[i][k] != REDMULE && CMCheckersBoard[i][k] != REDKING)
				{ // checks if there is an empty spot //
					if(counter != ONE) // checks if i went off board //
					{
						return true;
					}
					counter = ZERO; // reset counter //
				}
			}
			else
			{
				return false;
			}
		}

	}

	return 0;
}

bool MakeMove(int CMCheckersBoard[MAX_ARRAY_SIZE][MAX_ARRAY_SIZE], int numRowsInBoard, int player, int fromSquareNum, int toSquareNum, bool &jumped)
{
	//Declared necessary variables and constants
	int x = 0;
	int y = 0;
	int Xinitial = 0;
	int Yinitial = 0;
	int Xfinal = 0;
	int Yfinal = 0;
	int xdistance = 0;
	int ydistance = 0;
	int Yopponent = 0;
	int Xopponent = 0;

	//Input character to terminate the game if an oppoenent mule has become king
	char endgame[80] = {'\0'};

	const int ONE = 1;
	const int ZERO = 0;
	const int TWO = 2;

	//Conveting the square numbers to rows and columns
	//The row is the ineteger digit obtained from dividing the square number with number of rows
	//The column is the remainder MINUS ONE (as the array starts from position 0)
	Xinitial = (fromSquareNum/numRowsInBoard);
	Xfinal = (toSquareNum/numRowsInBoard);
	Yinitial = (fromSquareNum % numRowsInBoard);
	Yfinal = (toSquareNum % numRowsInBoard);

	//The following calculates the magnitude of the displacement of the checker diagonally
	xdistance = abs(Xfinal - Xinitial);
	ydistance = abs(Yfinal - Yinitial);

	//If the vertical displacement is equal to the number of columns present, that means the piece has moved to the other other end of the row
	//hence the displacement is measured to be 1 in this case                       
	if(ydistance == numRowsInBoard - ONE)
	{
		ydistance = ONE;
	}
	if(ydistance == numRowsInBoard - TWO)
	{
		ydistance = TWO;
	}

	
	//If the displacement is more than 2 rows, the move is invalid and so the function returns an automatic false
	if(xdistance > TWO)
	{
		cerr << "Error; illegal move" << endl;
		return false;
	}

	//If the displacement is more than 2 columns, the move is invalid and so the function returns an automatic false
	if(ydistance > TWO)
	{
		cerr << "Error; illegal move" << endl;
		return false;
	}


	if(xdistance != ydistance)
	{
		cerr << "Error; illegal move" << endl;
		return false;
	}

	if(xdistance == TWO && ydistance == TWO)
	{
		//These formulae calculates the position of an opponent checker if the players checker were to jump over.
		Yopponent = (Yfinal + Yinitial)/ TWO;
		Xopponent = (Xfinal + Xinitial)/ TWO;

		//If a jump is possible and an opponent's checker is on the edge of the board
		//the opponent's y coordinate has to be modified to either the final column or the first column
		if(Yinitial == (numRowsInBoard - TWO) && Yfinal == ZERO)
		{
			Yopponent = numRowsInBoard - ONE;
		}
		else if(Yinitial == ZERO && Yfinal == (numRowsInBoard - TWO))
		{
			Yopponent =  numRowsInBoard - ONE;
		}
		else if(Yinitial == ONE && Yfinal == (numRowsInBoard - ONE)) 
		{
		Yopponent = ZERO;
		}
		else if(Yinitial == (numRowsInBoard - ONE) && Yfinal == ONE)
		{
		Yopponent = ZERO;
		}
	}

	if(player == WHITEPLAYER) //WHITE PLAYER
	{
		if(xdistance == TWO && ydistance == TWO)
		{//Checks if the vertical and horizontal displacement is two

			if(CMCheckersBoard[Xopponent][Yopponent] != REDMULE && CMCheckersBoard[Xopponent][Yopponent] != REDKING && CMCheckersBoard[Xopponent][Yopponent] != REDSOLDIER)
			{//If so, then it further checks if there is an opponent checker in between the squares, if no, then the function returns a false

				cerr << "Error; illegal move blaa" << endl;
				return false;
			}
		}

		if(CMCheckersBoard[Xinitial][Yinitial] == WHITEMULE || CMCheckersBoard[Xinitial][Yinitial] == WHITESOLDIER)
		{//Checks if a mule or soldier is trying ot move behind, if so then the move is invalid and the function returns a false
			if(Xfinal < Xinitial)
			{
				cerr << "Error; illegal move" <<  endl;
				return false;
			}
		}
	
		if(xdistance == TWO && ydistance == TWO)
		{//If the checker is able to move 2 squares, that must mean the checker has jumped over an opponent
		 //the opponent checker is then reset to zero and the move is made

			CMCheckersBoard[Xfinal][Yfinal] = CMCheckersBoard[Xinitial][Yinitial];
			CMCheckersBoard[Xinitial][Yinitial] = ZERO;
			CMCheckersBoard[Xopponent][Yopponent] = ZERO;
		}

		else if(xdistance == ONE && ydistance == ONE)
		{//If the displacement is 1 square, the move is carried out

			CMCheckersBoard[Xfinal][Yfinal] = CMCheckersBoard[Xinitial][Yinitial];
			CMCheckersBoard[Xinitial][Yinitial] = ZERO;
		}
		if(Xfinal == numRowsInBoard - ONE)
		{//If the checker has reached the final row from its side, the checker must be turned to a king

			if(CMCheckersBoard[Xfinal][Yfinal] == WHITEMULE)
			{//If the checker being turned to a king is a mule, then the opponent wins the game.
			 //The user is asked to enter any character to exit the game
				cout << endl;
				cout << "White has created a Mule King, Red wins the game" << endl;
				cout << "Enter any character to terminate the game then press the enter key" << endl;
				cin >> endgame;

				return 4;
			}
			else
			{//If not a mule, the checker is turned to a king

				CMCheckersBoard[Xfinal][Yfinal] = WHITEKING;
			}
		}
		return true; //Return true if no false is encountered
	}

	else if(player == REDPLAYER) //RED PLAYER
	{
		if(xdistance == TWO && ydistance == TWO)
		{//Checks if the vertical and horizontal displacement is two

			if(CMCheckersBoard[Xopponent][Yopponent] != WHITEMULE && CMCheckersBoard[Xopponent][Yopponent] != WHITEKING && CMCheckersBoard[Xopponent][Yopponent] != WHITESOLDIER)
			{//If so, then it further checks if there is an opponent checker in between the squares, if no, then the function returns a false

				cerr << "Error; illegal move" << endl;
				return false;
			}
		}
		if(CMCheckersBoard[Xinitial][Yinitial] == REDMULE || CMCheckersBoard[Xinitial][Yinitial] == REDSOLDIER)
		{//Checks if a mule or soldier is trying ot move behind, if so then the move is invalid and the function returns a false

			if(Xinitial < Xfinal)
			{
				cerr << "Error; illegal move" << endl;
				return false;
			}
		}

		if(xdistance == TWO && ydistance == TWO)
		{//If the checker is able to move 2 squares, that must mean the checker has jumped over an opponent
		 //the opponent checker is then reset to zero and the move is made

			CMCheckersBoard[Xfinal][Yfinal] = CMCheckersBoard[Xinitial][Yinitial];
			CMCheckersBoard[Xinitial][Yinitial] = ZERO;
			CMCheckersBoard[Xopponent][Yopponent] = ZERO;
		}

		else if(xdistance == ONE && ydistance == ONE)
		{//If the displacement is 1 square, the move is carried out

			CMCheckersBoard[Xfinal][Yfinal] = CMCheckersBoard[Xinitial][Yinitial];
			CMCheckersBoard[Xinitial][Yinitial] = ZERO;
		}

		if(Xfinal == ZERO)
		{
			if(CMCheckersBoard[Xfinal][Yfinal] == REDMULE)
			{//If the checker being turned to a king is a mule, then the opponent wins the game.
			 //The user is asked to enter any character to exit the game
				cout << endl;
				cout << "Red has created a Mule King, White wins the game" << endl;
				cout << "Enter any character to terminate the game then press the enter key" << endl;
				cin >> endgame;

				return 5;
			}
			else
			{//If not a mule, the checker is turned to a king
					CMCheckersBoard[Xfinal][Yfinal] = REDKING;
			}
		}
		return true; //Return true if no false is encountered
	}
	
}

bool CheckWin(int CMCheckersBoard[MAX_ARRAY_SIZE][MAX_ARRAY_SIZE], int numRowsInBoard)
{
	//The function counts the number of each type of checker present in the board. Then it considers certain conditions to determine which player has won the game.

	//Declared and initialized variables and constants
	int i = 0;
	int k = 0;
	int REDMULEcounter = 0;
	int REDKINGcounter = 0;
	int REDSOLDIERcounter = 0;
	int WHITEMULEcounter = 0;
	int WHITEKINGcounter = 0;
	int WHITESOLDIERcounter = 0;

	const int ZERO = 0;
	
	for(i = 0; i < numRowsInBoard; i ++)
	{
		for(k = 0; k < numRowsInBoard; k++)
		{
			if(CMCheckersBoard[i][k] == REDKING) // Checks to see if square contains a red king
			{
				REDKINGcounter++; //If so, then it increments the red king counter
			}
			else if(CMCheckersBoard[i][k] == REDMULE) // Checks to see if the square contains a red mule
			{
				REDMULEcounter++; //If so, then it increments the red mule counter
			}
			else if(CMCheckersBoard[i][k] == REDSOLDIER) // Checks to see of the square contains a red soldier
			{
				REDSOLDIERcounter++; //If so, then it increments the red soldier counter
			}
			else if(CMCheckersBoard[i][k] == WHITEKING) // Checks to see if the square contains a white king
			{
				WHITEKINGcounter++; //If so, then it increments the white king counter
			}
			else if(CMCheckersBoard[i][k] == WHITESOLDIER) // Checks to see if the square contains a white soldier
			{
				WHITESOLDIERcounter++; //If so, then it increments the white soldier counter
			}
			else if(CMCheckersBoard[i][k] == WHITEMULE) //Checks to see if the square contains a white mule
			{
				WHITEMULEcounter++; //If so, then it contains a white mule counter
			}
		}
	}
	if(REDMULEcounter == ZERO) //If the red player has no mule, then red player wins the game
	{
		cout << " The Red Player has won the game by losing all of the Red Mules" << endl;
		return true;
	}
	else if(WHITEMULEcounter == ZERO) //If the white player has no mule, then white player wins the game
	{
		cout << " The White Player has won the game by losing all of the White Mules" << endl;
		return true;
	}
	else if(REDMULEcounter > ZERO && REDKINGcounter == ZERO && REDSOLDIERcounter == ZERO) //If the red player has ONLY mules, then white player wins the game
	{
		cout << "The White Player has won by capturing all of the red players soldiers and kings" << endl;
		return true;
	}
	else if(WHITEMULEcounter > ZERO && WHITEKINGcounter == ZERO && WHITESOLDIERcounter == ZERO) //If the white player has ONLY mules, then red player wins the game
	{
		cout << "The Red Player has won by capturing all of the white players soldiers and kings" << endl;
		return true;
	}
	else //If none of the conditions above is met, the function returns false
	{
		return false;
	}
}