#include <iostream>
#include <array>
#include "functions.cpp"

using namespace std;

int main()
{
  greetAndInstruct();

  char board[27];
  int userMove;
  int moveCounter = 0;
  displayBoard(board);

  while (true)
  { //Q5

    cout << "It's your turn, please enter a cell number to move: " << endl;
    cin >> userMove;

    while (cin.fail())
    { //if the input is not number
      cin.clear();
      cin.ignore(INT8_MAX, '\n');
      cout << "Illegal input, please enter a CELL NUMBER to move: " << endl;
      cin >> userMove;
    }

    if (checkIfLegal(userMove, board) == false)
    {
      cin >> userMove;
    }

    board[userMove - 1] = 'X';
    moveCounter++;

    displayBoard(board);
    if (checkWinner(board))
    {
      break;
    }

    cout << "It's computer's turn..." << endl;
    computerMove(board);
    moveCounter++;
    displayBoard(board);
    if (checkWinner(board))
    {
      break;
    }

    if (moveCounter >= 27 && checkWinner(board) == false)
    { //if there is no winner and all cells are occupied, it's a tie

      cout << "Game over, it's a tie!" << endl;
    }
  }

  return 0;
}