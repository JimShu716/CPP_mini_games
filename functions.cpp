#include <iostream>
#include <array>
#include <iomanip>

using namespace std;

void greetAndInstruct() //Q1
{
  cout << "Hello and welcome to the Tic-Tac-Toe challenge: Player against Computer.\n"
       << endl;
  cout << "The board is numbered from 1 to 27 as per the following:\n\n"
       << endl;
  cout << "1 | 2 | 3"
       << "          "
       << "10 | 11 | 12"
       << "          "
       << "19 | 20 | 21" << endl; // first line
  cout << "----------"
       << "         "
       << "------------"
       << "          "
       << "------------" << endl; //second line
  cout << "4 | 5 | 6"
       << "          "
       << "13 | 14 | 15"
       << "          "
       << "22 | 23 | 24" << endl; //third line
  cout << "----------"
       << "         "
       << "------------"
       << "          "
       << "------------" << endl; //fourth line
  cout << "7 | 8 | 9"
       << "          "
       << "16 | 17 | 18"
       << "          "
       << "25 | 26 | 27" << endl; //fifth line

  cout << "\n"
       << "Player starts first. Simply input the number of the cell you want to occupy. Player's move is marked with X. Computer's move is marked with O.\n"
       << endl;
  cout << "Start? (y/n):" << endl;

  bool isTrue = false;
  string userInput;
  cin >> userInput;

  while (isTrue == false)
  {
    //        cin >> answer;
    if (userInput == "y")
    {
      isTrue = true;
      break;
    }
    if (userInput == "n")
    {
      isTrue = true;
      cout << "Bye!" << endl;
      exit(0); //the program exits
    }
    cout << "your input is " << userInput << endl;
    cout << "Unknown input. Please try again." << endl;

    cout << "Start? (y/n):" << endl;
    cin >> userInput;
  }
}

void displayBoard(char board[]) //Q2
{
  string temp_board[27];

  for (int i = 0; i < 27; i++)
  {
    if (board[i] == 'X') // if the Xs exist on board
    {
      temp_board[i] = "X"; // display the Xs
    }
    else if (board[i] == 'O') // if the Os exist on board
    {
      temp_board[i] = "O"; // display the Os
    }
    else
    {
      temp_board[i] = to_string(i + 1); // otherwise, display the cell number
    }
  }

  for (int j = 0; j < 3; j++) //display three tables
  {
    int index = j * 3; //index of cells for each table

    cout << setw(2) << temp_board[index] << " | " << setw(2) << temp_board[index + 1] << " | " << setw(2) << temp_board[index + 2] << "          "
         << setw(2) << temp_board[index + 9] << " | " << setw(2) << temp_board[index + 10] << " | " << setw(2) << temp_board[index + 11] << "          "
         << setw(2) << temp_board[index + 18] << " | " << setw(2) << temp_board[index + 19] << " | " << setw(2) << temp_board[index + 20] << endl;

    if (j < 2)
    {
      cout << "------------"
           << "          "
           << "------------"
           << "          "
           << "------------" << endl;
    }
  }
}

bool checkIfLegal(int cellNbre, char board[])
{ //Q3
  int cellNum = cellNbre - 1;
  if (board[cellNum] == 'X' || board[cellNum] == 'O')
  {

    cout << "Illegal move: cell alreafy occupied!\n"
         << endl;
    cout << "Please enter a different cell number: " << endl;
    return false;
  }

  if (cellNum < 0 || cellNum > 26)
  {

    cout << "Illegal move: out of bound!\n"
         << endl;
    cout << "Please enter a different cell number: " << endl;
    return false;
  }
  return true;
}

int checkResult(char board[])
{ //Q3 helper
  // this function checks the result of the board. Return 1 if the player wins, return 0 if the computer wins, return -1 if no one wins.

  for (int i = 0; i < 3; i++)
  { //check rows
    for (int j = 0; j < 3; j++)
    {
      if (board[j * 3 + i * 9] == 'O' && board[1 + j * 3 + i * 9] == 'O' && board[2 + j * 3 + i * 9] == 'O')
      {
        return 0;
      }
      if (board[j * 3 + i * 9] == 'X' && board[1 + j * 3 + i * 9] == 'X' && board[2 + j * 3 + i * 9] == 'X')
      {
        return 1;
      }
    }
  }

  for (int i = 0; i < 3; i++)
  { //check columns

    for (int j = 0; j < 3; j++)
    {

      if (board[j + i * 9] == 'O' && board[3 + j + i * 9] == 'O' && board[6 + j + i * 9] == 'O')
      {
        return 0;
      }
      if (board[j + i * 9] == 'X' && board[3 + j + i * 9] == 'X' && board[6 + j + i * 9] == 'X')
      {
        return 1;
      }
    }
  }

  for (int i = 0; i < 3; i++)
  { //check  diagonals starting from top left

    if (board[i * 9] == 'O' && board[4 + i * 9] == 'O' && board[8 + i * 9] == 'O')
    {
      return 0;
    }
    if (board[i * 9] == 'X' && board[4 + i * 9] == 'X' && board[8 + i * 9] == 'X')
    {
      return 1;
    }
  }

  for (int i = 0; i < 3; i++)
  { //check  diagonals starting from top right

    if (board[2 + i * 9] == 'O' && board[4 + i * 9] == 'O' && board[6 + i * 9] == 'O')
    {
      return 0;
    }
    if (board[2 + i * 9] == 'X' && board[4 + i * 9] == 'X' && board[6 + i * 9] == 'X')
    {
      return 1;
    }
  }

  for (int j = 0; j < 3; j++)
  { //check rows over three boards

    if ((board[j * 3] == 'O' && board[10 + j * 3] == 'O' && board[20 + j * 3] == 'O') || (board[2 + j * 3] == 'O' && board[10 + j * 3] == 'O' && board[18 + j * 3] == 'O'))
    {
      return 0;
    }
    if ((board[j * 3] == 'X' && board[10 + j * 3] == 'X' && board[20 + j * 3] == 'X') || (board[2 + j * 3] == 'X' && board[10 + j * 3] == 'X' && board[18 + j * 3] == 'X'))
    {
      return 1;
    }
  }

  for (int j = 0; j < 3; j++)
  { //check rows over three boards

    if ((board[j] == 'O' && board[12 + j] == 'O' && board[24 + j] == 'O') || (board[6 + j] == 'O' && board[12 + j] == 'O' && board[18 + j] == 'O'))
    {
      return 0;
    }
    if ((board[j] == 'X' && board[12 + j] == 'X' && board[24 + j] == 'X') || (board[6 + j] == 'X' && board[12 + j] == 'X' && board[18 + j] == 'X'))
    {
      return 1;
    }
  }

  for (int i = 0; i < 3; i++)
  { //check  diagonals starting from top left over three boards

    if ((board[0] == 'O' && board[13] == 'O' && board[26] == 'O') || (board[8] == 'O' && board[13] == 'O' && board[18] == 'O'))
    {
      return 0;
    }
    if ((board[0] == 'X' && board[13] == 'X' && board[26] == 'X') || (board[8] == 'X' && board[13] == 'X' && board[18] == 'X'))
    {
      return 1;
    }
  }

  for (int i = 0; i < 3; i++)
  { //check  diagonals starting from top right over three boards

    if ((board[2] == 'O' && board[13] == 'O' && board[24] == 'O') || (board[6] == 'O' && board[13] == 'O' && board[20] == 'O'))
    {
      return 0;
    }
    if ((board[2] == 'X' && board[13] == 'X' && board[24] == 'X') || (board[6] == 'X' && board[13] == 'X' && board[20] == 'X'))
    {
      return 1;
    }
  }

  return -1;
}

bool checkWinner(char board[])
{
  //Q3
  if (checkResult(board) == 1)
  {
    cout << "You win!" << endl;
    return true;
  }
  else if (checkResult(board) == 0)
  {
    cout << "Computer wins!" << endl;
    return true;
  }

  return false;
};

void computerMove(char board[])
{
  int counter = 0;
  bool seen = false;
  for (int i = 1; i < 27; i++)
  {
    counter++;
    if (checkIfLegal(i, board))
    {
      board[i - 1] = 'O';
      if (checkResult(board) != -1)
      {
        return;
      }
      board[i - 1] = 'X';           //
      if (checkResult(board) != -1) // check if the move will make the player winner
      {
        board[i - 1] = 'O';
        return;
      }
      board[i - 1] = '\0';
    }
    if (counter == 26)
    {
      for (int j = 1; j < 27; j++)
      {
        if (board[j - 1] && checkIfLegal(j + 1, board) && seen == false)
        {
          board[j] = 'O';
          seen = true;
          return;
        }
        seen = false;
      }
    }
  }
}
