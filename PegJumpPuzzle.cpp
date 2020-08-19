// Ashley Stojak
// Peg Jump Puzzle Project

#include <iostream>
#include <cctype>     // For toupper()
using namespace std;


//-------------------------------------------------------------------------------------
void displayInstructions()
{
    cout << endl
         << "Welcome to the peg jump puzzle. The board starts out with a \n"
         << "single blank position, represented by the '*'.  To make a \n"
         << "move, select the letter of a peg.  A peg must be able to \n"
         << "jump over an adjacent peg into a blank position for a move \n"
         << "to be valid.  The jumped peg is then removed from the board. \n"
         << "The game is over when there are no valid moves left. At any \n"
         << "point enter '-' to exit, or '+' for instructions. \n"
         << endl;
}

// Purpose of function is to loop through the board array to display the board
void displayGameBoard(char board[]) {
  
    for (int i = 0; i < 121; i++) {
        if (board[i] == '#') { // change # to ' '
            board[i] = ' ';
        }
        cout << board[i] << " ";
        if ((i+1) % 11 == 0) { // print characters on a new line when the loop reaches 11 characters
            cout << endl;
        }
    }
}


// Purpose of function is to make a game move by changing the character the user enters into an asterick and 
// make the destination position into the character the user entered and change the position between the current position 
// and the destination position into an asterick 
void makeGameMove(int currentPosition, int jumpedIndex, int destinationIndex, char playersMove, char board[]) {
  
    board[currentPosition] = '*';
    board[jumpedIndex] = '*';
    board[destinationIndex] = playersMove;
                     
}


// Purpose of function is to display a new board that shows the user the options they have for the moves they could make
void displayValidMoveOptions(int moveList[], char board[], int currentPosition, int &moveListIndex) {
    
    int findCounter = 0;
    bool foundMoveOption;
    int playersChoice = 0;
  
    char copyOfBoard[] = {
            '#','#','#','#','#','#','#','#','#','#','#',
            '#','#','#','#','#','#','#','#','#','#','#',
            '#','#','#','#','A','B','C','#','#','#','#',
            '#','#','#','#','D','E','F','#','#','#','#',
            '#','#','G','H','I','J','K','L','M','#','#',
            '#','#','N','O','P','*','Q','R','S','#','#',
            '#','#','T','U','V','W','X','Y','Z','#','#',
            '#','#','#','#','1','2','3','#','#','#','#',
            '#','#','#','#','4','5','6','#','#','#','#',
            '#','#','#','#','#','#','#','#','#','#','#',
            '#','#','#','#','#','#','#','#','#','#','#'
    };

    // looking for valid moves in the move list 
    for (int i = 0; i < 121; i++) {
        foundMoveOption = false;
        for (int j = 0; j < 4; j++) {
            if (moveList[j] == i) {
                foundMoveOption = true;
                findCounter++; // increments counter when valid move is found
                break;
            }
        }
        if (foundMoveOption == false) {
            if (i == currentPosition) {
                copyOfBoard[i] = '+'; // change players move into a +                 
            }
            else if ((board[i] != ' ') && (board[i] != '+')) {
                copyOfBoard[i] = '*'; // change characters on the board to * except for the move options and player's current position
            }
        }
        else { 
            copyOfBoard[i] = '0' + findCounter; // displays number where a move option is 
        }
    }
  
   displayGameBoard(copyOfBoard); // display mutiple options board
   cout << "There is more than one possible move.  Which move do you want? ";
   cin >> playersChoice;
   moveListIndex = playersChoice - 1; // position of the move option the player chooses
   
}
 
// Purpose of function is to determine if the move the user entered is valid
bool findValidMove(char playersMove, char board[]) {
  
    int numberOfValidMoves = 0;
    int destinationIndex = 0;
    int jumpedIndex = 0;
  
    // intialize variables to invalid values 
    int currentPosition = -1;  
    int moveList[] = {-1,-1,-1,-1}; 
    int jumpList[] = {-1,-1,-1,-1}; 
    int moveListIndex = -1;
  
    // find where player's move is on the board
    for (int i = 0; i < 121; i++) {
        if (board[i] == playersMove) {
            currentPosition = i;
            break;
        }
    }
 
    if (((board[currentPosition - 11]) != '*' && (board[currentPosition - 11]) != ' ') && ((board[currentPosition - 22]) == '*')) {
        numberOfValidMoves++; 
        destinationIndex = currentPosition - 22; // two rows above current position
        jumpedIndex = currentPosition - 11; // one row above current postion
        moveList[numberOfValidMoves - 1] = destinationIndex; // stores valid move into move list array to display later if their are mutiple valid moves
        jumpList[numberOfValidMoves - 1] = jumpedIndex; // stores jumped index in jump list array to use if their are multiple move options
    }
    if (((board[currentPosition - 1]) != '*' && (board[currentPosition - 1]) != ' ') && ((board[currentPosition - 2]) == '*')) {
        numberOfValidMoves++; 
        destinationIndex = currentPosition - 2; // two columns to the left of current position 
        jumpedIndex = currentPosition - 1; // one column to the left of current position
        moveList[numberOfValidMoves - 1] = destinationIndex;
        jumpList[numberOfValidMoves - 1] = jumpedIndex;
    }
    if (((board[currentPosition + 1]) != '*' && (board[currentPosition + 1]) != ' ') && ((board[currentPosition + 2]) == '*')) {
        numberOfValidMoves++; 
        destinationIndex = currentPosition + 2; // two columns to the right of current position
        jumpedIndex = currentPosition + 1; // one column to the right of current position
        moveList[numberOfValidMoves - 1] = destinationIndex;
        jumpList[numberOfValidMoves - 1] = jumpedIndex;
    }
    if (((board[currentPosition + 11]) != '*' && (board[currentPosition + 11]) != ' ') && ((board[currentPosition + 22]) == '*')) {
        numberOfValidMoves++; 
        destinationIndex = currentPosition + 22; // two rows below current position
        jumpedIndex = currentPosition + 11; // one row below current position
        moveList[numberOfValidMoves - 1] = destinationIndex;
        jumpList[numberOfValidMoves - 1] = jumpedIndex;
    }
    
    if (numberOfValidMoves == 0) { // there are no valid moves
        cout << "*** Invalid move, please retry. ***" << endl;
        return false;
    }
    
    if (numberOfValidMoves == 1) { // one valid move
        makeGameMove(currentPosition, jumpedIndex, destinationIndex, playersMove, board); 
        return true;     
    }   

    if (numberOfValidMoves > 1) { // more than one valid move option, need to display mutiple options
        displayValidMoveOptions(moveList, board, currentPosition, moveListIndex); // displays mutiple move options
        makeGameMove(currentPosition, jumpList[moveListIndex], moveList[moveListIndex], playersMove, board); // makes the move that players chooses 
        return true;  
    }   

    return false; 
}


// Purpose of function is to check if their are any valid moves left on the board
// Function returns true if it does not find a valid move and false if it finds a valid move
bool gameOver(char board[]) {
  
    bool gameOver = true;  
    for (int i = 0; i < 121; i++) {       
        if ((board[i] != '*') && (board[i] != ' ')) {
            if (((board[i - 11]) != '*' && (board[i - 11]) != ' ') && ((board[i - 22]) == '*')) {
                gameOver = false;
            }
            if (((board[i - 1]) != '*' && (board[i - 1]) != ' ') && ((board[i - 2]) == '*')) {
                gameOver = false;
            } 
            if (((board[i + 1]) != '*' && (board[i + 1]) != ' ') && ((board[i + 2]) == '*')) {
                gameOver = false;
            }
            if (((board[i + 11]) != '*' && (board[i + 11]) != ' ') && ((board[i + 22]) == '*')) {
                gameOver = false;
            }
        }
    }
    return gameOver;
}


//-------------------------------------------------------------------------------------
int main()
{
    //Variable declarations
    char board[] = {
            '#','#','#','#','#','#','#','#','#','#','#',
            '#','#','#','#','#','#','#','#','#','#','#',
            '#','#','#','#','A','B','C','#','#','#','#',
            '#','#','#','#','D','E','F','#','#','#','#',
            '#','#','G','H','I','J','K','L','M','#','#',
            '#','#','N','O','P','*','Q','R','S','#','#',
            '#','#','T','U','V','W','X','Y','Z','#','#',
            '#','#','#','#','1','2','3','#','#','#','#',
            '#','#','#','#','4','5','6','#','#','#','#',
            '#','#','#','#','#','#','#','#','#','#','#',
            '#','#','#','#','#','#','#','#','#','#','#'
    };

    cout << "Welcome to the peg jump puzzle! \n"
         << "Enter '-' to exit, or '+' for instructions. "
         << endl;
  
    displayGameBoard(board);

    char playersMove;
    int roundNumber = 1;
    int remainingPieces;
     
    // Main loop to play the game
    while (!gameOver(board)) {
      
        // Prompt for and get move
        cout << roundNumber << ". Enter the peg to move: ";
        cin >> playersMove;
        playersMove = toupper(playersMove);
        
        // Check for '-' to exit, and '+' for displaying instructions
        if (playersMove == '-') {
            cout << endl << "Exiting..." << endl << endl;
            break; // break out of loop to exit out of game
        }
        else if (playersMove == '+') {
            displayInstructions();
            continue; 
        }
    
        // Make move
        if (findValidMove(playersMove, board)) { // If the move is valid, increment round number
     
            // Increment move number and display the board
            roundNumber++;
            displayGameBoard(board);
        }
      
    }

    // Find number of remaining pieces 
    remainingPieces = 0;
    for (int i = 0; i < 121; i++) {
        if ((board[i] != ' ') && (board[i] != '*')) {
            remainingPieces++;
        }
    }
  
    // Display appropriate message depending on number of remaining pegs
    cout << remainingPieces << " pieces remaining.";
  
    if (remainingPieces == 1) {
        cout << " Excellent!" << endl << endl;
    }
    else if (remainingPieces == 2) {
        cout << " Good!" << endl << endl;
    }
    else if (remainingPieces == 3) {
        cout << " OK." << endl << endl;
    }
    else if (remainingPieces == 4) {
        cout << " Needs Improvement." << endl << endl;
    }
    else if (remainingPieces > 4) {
        cout << " Ouch!" << endl << endl;
    }

    return 0;
    
}//end main()
