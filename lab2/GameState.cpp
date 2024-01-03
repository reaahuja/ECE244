//
//  GameState.cpp
//  Connect Four Game

#include "GameState.h"
#include "globals.h"

// ECE244 Student: add you code below to implement the methods of the Gamestate class 

GameState::GameState(){
 selectedRow = 0; 
 selectedColumn = 0; 
 moveValid = true; 
 gameOver = false;
 turn = true;
 winner = 0;

 for (int row = 0; row < boardSize; row++){
    for (int col = 0; col < boardSize; col++){
        gameBoard[row][col] = 0;
    }
 }
}

int GameState::get_selectedRow(){
    return selectedRow; 
}

int GameState::get_selectedColumn(){
    return selectedColumn;
}

void GameState::set_selectedRow(int value){
    if (value >= 0 && value < boardSize){
        selectedRow = value;
    }
    return; 
}

void GameState::set_selectedColumn(int value){
   if (value >= 0 && value < boardSize){
        selectedColumn = value;
   }
   return; 
}

bool GameState::get_moveValid(){
    return moveValid; 
}

void GameState::set_moveValid(bool value){
    moveValid = value;
}

bool GameState::get_gameOver(){
    return gameOver;
}

void GameState::set_gameOver(bool value){
    gameOver = value; 
}

bool GameState::get_turn(){
    return turn;
}

void GameState::set_turn(bool value){
    turn = value;
}

int GameState::get_winner(){
    return winner;
}

void GameState::set_winner(int value){
    winner = value; 
}

int GameState::get_gameBoard(int row, int col){
    if ((row >= 0 && row < boardSize) && (col >= 0 && col < boardSize)){
        return gameBoard[row][col];
    }
    return 0; 
}

void  GameState::set_gameBoard(int row, int col, int value){
    if ((row >= 0 && row < boardSize) && (col >= 0 && col < boardSize)){
        if(value == 1){
            gameBoard[row][col] = 1; 
        }else if(value == -1){
            gameBoard[row][col] = -1;
        }
    }
    return;
}


