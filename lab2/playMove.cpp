//
//  playMove.cpp
//  Connect Four Game
//

//  ECE244 Student: write your code for playMove in this file

#include "GameState.h"
#include "globals.h"
#include <iostream>
using namespace std;

// Function prototypes (if you need)

void turn(GameState& game_state);
void gameOver(GameState& game_state);
void checkBoard(GameState& game_state,int direction, int row, int col, int turn);
void winner(GameState& game_state);

void playMove(GameState& game_state) {
  // Change gameOver
  gameOver(game_state);
  // Change winner
  //PRIMARY CHANGE -- commented out winner(game_state)
  //winner(game_state);
  // cout << "Delete: Winner" << game_state.get_winner() << endl;
  // Change turn if move is valid,
  turn(game_state);
}

void winner(GameState& game_state){
  if (game_state.get_gameOver() == true){
    // cout << "Delete: Turn" << game_state.get_turn();
    game_state.set_winner(game_state.get_turn());

  }
}

void gameOver(GameState& game_state){

  /*
  -4 = Northeast
  -3 = Northwest
  -2 = East 
  -1 = North 
  1 = South 
  2 = West
  3 = Southwest
  4 = Southeast
  */
 
 int row = game_state.get_selectedRow();
 int col = game_state.get_selectedColumn();
 bool value = game_state.get_turn(); 
 int turn = 0;
 if (value){
  turn = 1;
 }else{
  turn = -1;
 }
 
 game_state.set_gameOver(false);

 checkBoard(game_state, -4, row, col, turn);
 checkBoard(game_state, -3, row, col, turn);
 checkBoard(game_state, -2, row, col, turn);
 checkBoard(game_state, -1, row, col, turn);
 checkBoard(game_state, 1, row, col, turn);
 checkBoard(game_state, 2, row, col, turn);
 checkBoard(game_state, 3, row, col, turn);
 checkBoard(game_state, 4, row, col, turn);

}

void checkBoard(GameState& game_state, int direction, int row, int col, int turn){
  int counter = 0;

  while ((row >= 0) && (row < boardSize) && (col >= 0) && (col < boardSize)){
    int value = game_state.get_gameBoard(row, col); 
    if (value == turn){
      counter++;
      //cout << "Delete: value" << value << " turn"<< turn << "counter" << counter << "row" << row << "col" << col << "direction" << direction <<endl;

    }else{
      break;
    }
    if(direction == -1){
      row++;
    }else if (direction == 1){
      row--;
    }else if(direction == -2){
      col++;
    }else if(direction == 2){
      col--;
    }else if(direction == 3){
      row--; 
      col--;
    }else if(direction == -3){
      row++;
      col--;
    }else if(direction == 4){
      row--; 
      col++;
    }else{
      row++;
      col++;
    }
  }

  if (counter >= 4){
    game_state.set_gameOver(true);
    //PRIMARY CHANGE -- set winner in this condition instead (could have also done it in winner function but no need of making extra function)
    game_state.set_winner(turn);
  }
  
}

void turn(GameState& game_state){
  bool turnValue = game_state.get_turn();
  if (turnValue){
    game_state.set_turn(false);
  }else{
     game_state.set_turn(true);
  }
}


