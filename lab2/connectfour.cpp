//
//  connectfour.cpp
//  Connect Four Game
//

//  ECE244 Student: Complete the skeletal code of the main function in this file

#include <iostream>
#include <string>
using namespace std;

#include "GameState.h"
#include "globals.h"

// Function prototypes
bool checkValidity(GameState& game_state, int col);
void lowestRow(GameState& game_state, int col);
void printBoard(GameState& game_state);
// The main function
int main() {
  /**********************************************************************************/
  /* Create three initialized game state objects in an array */
  /**********************************************************************************/
  const int numOfRounds = 3;
  int rWon = 0; 
  int sWon = 0;
  GameState game_state[numOfRounds];

  // Read one integer from the user that represents the column
  // the player would like to place their piece (R or Y) in
  // You can assume there will be no formatting errors in the input

  int col;
  int round = 0;
  int gameVal = round + 1;
  cout << "Game " << gameVal<< endl;
  bool endGame = false;

  //PRIMARY CHANGE -- removed !game_state[round].get_gameOver() and substituted with gameValue <=3
  while ((!endGame && round < 3)) {
    cout << "Enter column to place piece: ";
    cin >> col;

 
    if( cin.eof()) {
      cerr << endl << "Game ended by user." << endl ;
      exit( 0 ) ;
    }
    if( cin.fail() || (col == 10)) {
      cin.clear() ;
      cin.ignore( 1000, '\n' ) ;
      col = -1 ; // giving col invalid value so it will be handled as invalid input below
    }
  
    // Check validity of input and if not valid, handle accordingly
    bool validity = checkValidity(game_state[round], col);
    while (validity == false){
      cout << "Invalid column! "<< endl;
      cout << "Enter column to place piece: " << endl;
      cin >> col;
      validity = checkValidity(game_state[round], col);
    }




    // The coordinates are valid; set the selectedRow and selectedColumn
    // members of the game state to the read values
    // Note that the corresponding mutators of GameState must be first
    // implemented before this works
   
    lowestRow(game_state[round], col);
    // Call playMove
    playMove(game_state[round]);
    // Print the GameState object, as prescribed in the handout
    printBoard(game_state[round]);
    // Check if a player won this round and if so handle accordingly
    int winner = game_state[round].get_winner();
    cout << endl;


    if(winner == 1){
      cout << "R won this round!"<< endl;
      rWon++;
      if ((rWon != 3) && (sWon != 3)){
        if ((rWon == 2 && sWon == 0)){
          endGame = true;
        }else{
          round++;
          int gameValue = round +1;
          //MINOR CHANGE -- added this condition due to use and signifiance of round in program
          if (round < 3){
            cout << "Game " << gameValue << endl;
          }
        }
      }else{
        endGame = true;
      }

    }else if(winner == -1){
      cout << "Y won this round!"<< endl;
      sWon++;
       if ((rWon != 3) && (sWon != 3)){
        if ((sWon == 2 && rWon == 0)){
          endGame = true;
        }else{
          round++;
          int gameValue = round +1;
          //MINOR CHANGE -- added this condition due to use and signifiance of round in program
          if (round < 3){
            cout << "Game " << gameValue << endl;
          }
        }
      }else{
        endGame = true;
      }

    }
  
    // Check if a player won this match and if so handle accordingly
  }


  if (rWon > sWon){
    cout << "R won the match!"<< endl;
  }else{
    cout << "Y won the match!"<< endl;
  }
}

void printBoard(GameState& game_state) {
  for (int row = boardSize -1; row >= 0; row--) {
    for (int col = 0; col < boardSize; col++) {
      int value = game_state.get_gameBoard(row, col);
      if (value == 0){
        cout << "_";
      }else if(value == 1){
        cout << "R";
      }else{
        cout << "Y";
      }
    }
    cout << endl;
  }
}

void lowestRow(GameState& game_state, int col){
  cout << "column chosen: " << col <<endl; 
  bool found = false;
  int row = 0;
  while(found == false){
    if(game_state.get_gameBoard(row, col) == 0){
      found = true; 
      game_state.set_selectedRow(row);
      game_state.set_selectedColumn(col);
    }
    row++; 
  }
  bool value = game_state.get_turn(); 
  int turn = 0;
  if (value){
    turn = 1;
  }else{
    turn = -1;
  }
  //update game board
  game_state.set_gameBoard(game_state.get_selectedRow(), game_state.get_selectedColumn(), turn);
}

bool checkValidity(GameState& game_state, int col){
  bool freeSpot = false;
  if (col >= 0 && col < boardSize){
    for (int row = 0; row < boardSize; row++){
      if (game_state.get_gameBoard(row, col) == 0){
        freeSpot = true; 
      }
    }
  }

  return freeSpot;
}
  
