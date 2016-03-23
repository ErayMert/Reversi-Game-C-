//HW01_121044033_Eray_Mert

//reversi.cpp

//Created on 05/10/2014 by Eray Mert

//reversi game and artifical intelligent game

#include <iostream>
#include <limits>
#include <cmath>
#include <cctype>

const int TSIZE = 20;
const int USER = 1;
const int COMPUTER = 2;
const int NONE = 0;
const int POSITION = 2;

using namespace std;


//Tabloyu dolduran fonksiyon
void fillTable(int board[][TSIZE], int size);

//Tabloyu ekrana basar
void printTable(int board[][TSIZE], int size);

//takePosition fonksiyonunu çagirir
void userPlay(int board[][TSIZE], int size);

//kullanicidan koordinatlari alir
void takePosition(int board[][TSIZE], int size,int cellPosition[POSITION]);

//hamlelerin legal olup olmadigini kontrol eder
bool validatePosition(int position[POSITION], int board[][TSIZE],int size,
                                    int turn, int opponent,bool control );

//check fonksitonlarını cagirir ve kontrol eder
bool isThatLegal(int board[][TSIZE], int size, int xCoor, int yCoor,
                              int turn, int opponent, bool control);

//sol tarafa yapilan hamleyi kontrol eder
int checkPosLeft(int board[][TSIZE], int size, int xCoor, int yCoor,
            int turn, int opponent, bool aiMoveActive,bool control);

//sag tarafa yapilan hamleyi kontrol eder
int checkPosRight(int board[][TSIZE], int size, int xCoor, int yCoor,
            int turn, int opponent, bool aiMoveActive,bool control);

//yukari yapilan hamleyi kotrol eder
int checkPosUp(int board[][TSIZE], int size, int xCoor, int yCoor,
            int turn, int opponent, bool aiMoveActive,bool control);

//asagi yapilan hamleyi kontrol eder
int checkPosDown(int board[][TSIZE], int size, int xCoor, int yCoor,
            int turn, int opponent, bool aiMoveActive,bool control);

//sol capraz yukari hamleyi kontrol eder 
int checkPosLeftCrossUp(int board[][TSIZE], int size, int xCoor, int yCoor,
            int turn, int opponent, bool aiMoveActive,bool control);

//sol capraz asagi hamleyi kontrol eder 
int checkPosLeftCrossDown(int board[][TSIZE], int size, int xCoor, int yCoor,
            int turn, int opponent, bool aiMoveActive,bool control);

//sag capraz yukari hamleyi kontrol eder 
int checkPosRightCrossUp(int board[][TSIZE], int size, int xCoor, int yCoor,
            int turn, int opponent, bool aiMoveActive,bool control);

//sag capraz asagi hamleyi kontrol eder 
int checkPosRightCrossDown(int board[][TSIZE], int size, int xCoor, int yCoor,
            int turn, int opponent, bool aiMoveActive,bool control);

//sol tarafa hamleyi yapa
void makeMoveLeft(int board[][TSIZE], int xCoor,int yCoor,
                        int foundedCellXCoorLeft, int turn);

//sag tarafa hamleyi yapar
void makeMoveRight(int board[][TSIZE], int xCoor,int yCoor,
                        int foundedCellXCoorRight, int turn);

//yukari hamleyi yapar
void makeMoveUp(int board[][TSIZE], int xCoor,int yCoor,
                        int foundedCellYCoorUp, int turn);

//asagi hamleyi yapar
void makeMoveDown(int board[][TSIZE], int xCoor,int yCoor,
                        int foundedCellYCoorDown, int turn);

//sol capraz yukari hamleyi yapar
void makeMoveLeftCrossUp(int board[][TSIZE], int xCoor,int yCoor,
                        int foundedCellLeftCrossUp[], int turn);

//sol capraz asagi hamleyi yapar
void makeMoveLeftCrossDown(int board[][TSIZE], int xCoor,int yCoor,
                        int foundedCellLeftCrossDown[], int turn);

//sag capraz yukari hamleyi yapar
void makeMoveRightCrossUp(int board[][TSIZE], int xCoor,int yCoor,
                        int foundedCellRightCrossUp[], int turn);

//sag capraz asagi hamleyi yapar
void makeMoveRightCrossDown(int board[][TSIZE], int xCoor,int yCoor,
                        int foundedCellRightCrossDown[], int turn);

//degisebilecek taslari sayar
int opponentCellCounter(int board[][TSIZE], int size, int xCoor, int yCoor);

//bilgisayarin en iyi hamlesini yapar
void makeBestMove(int board[][TSIZE], int size, int xCoor, int yCoor);

//bilgisayarin oyunu oynadigi fonksiyon
void computerPlay(int board[][TSIZE], int size);

//tablonun dolup dolmadigini kontrol eder
bool isBoardFilled(int board[][TSIZE], int size);

//hamle kalmadiginda diger oyuncuya gecmesini saglar
bool turnCanPlay(int board[][TSIZE], int size, int turn,int opponent);

//kullanicinin taslarini sayar
int countUserCells(int board[][TSIZE], int size);

//bilgisayarin taslarini sayar
int countComputerCells(int board[][TSIZE], int size);

//tablonun boyutunu alir
int takeSize();

//tum fonksiyonlar burada cagirilir ve oyun oynanir
void game(int board[][TSIZE], int size);

int main()
{
    int board[TSIZE][TSIZE];
    int userSize=0;
    char again;

    do
    {
        cout<< "\n------------- REVERSİ GAME  -------------\n";
        cout<< "USER will be ( O ) and COMPUTER will be ( X )\n\n";

        userSize = takeSize();
        game(board, userSize);

        cout<<"Do you want to play again (y/n): " ; 
        cin>>again;
        cout<<endl;

    }while(tolower(again) == 'y');
    
    return 0;   
}

void game(int board[][TSIZE], int size)
{
    char again;
    bool userGameOver = true, computerGameOver = true;

    fillTable(board,size);
    printTable(board, size);

    cout<< "\nUser : "<<countUserCells(board,size)<<endl;
    cout<< "\nComputer : "<<countComputerCells(board,size)<<endl<<endl;
    
    do
    {
        if(turnCanPlay(board,size,USER,COMPUTER)) // set(COM)
        {
            userPlay(board, size);
            printTable(board,size);
            cout<< "\nUser : "<<countUserCells(board,size)<<endl;
            cout<< "\nComputer : "<<countComputerCells(board,size)<<endl<<endl;
        }
        else
        {
            cout<< "\nYou can't play any more!!!\n";
            userGameOver = false;
        }

        if(turnCanPlay(board,size,COMPUTER,USER))
        {
            computerPlay(board,size);
            printTable(board,size);
            cout<< "\nUser : "<<countUserCells(board,size)<<endl;
            cout<< "\nComputer : "<<countComputerCells(board,size)<<endl<<endl;
        }
        else
        {
            cout<< "\nComputer can't play any more!!!\n";
            computerGameOver = false;
        }
                
    }while(isBoardFilled(board,size) && (userGameOver || computerGameOver));
   
    if(countUserCells(board,size) > countComputerCells(board,size))
    cout <<"\n---- USER WINNER ----\n\n";
    else
    cout <<"\n---- COMPUTER WINNER ----\n\n";
}


int takeSize()
{
      int size=0;

      cout << "Enter the size of matris: ";
      cin >> size;

      /*size kontrolu yapilir istenilen degerin girilip girilmedigi
       kontrol edilir*/
      while (size <4 || size > 20 || (size % 2 != 0) || 
                  cin.fail())
      { 
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout<< "You have entered the wrong value!!!!\n";
            cout << "Enter the size of matris: ";
            cin >> size;
      }
      return size;
}

void userPlay(int board[][TSIZE], int size)
{
      int cellPosition[POSITION];
    takePosition(board, size,cellPosition);
}

void takePosition(int board[][TSIZE], int size,int cellPosition[POSITION])
{
    char xPos;
    
    cout<< "Enter coordinate ( Y coordinate - X coordinate ) : ";
    cin>> cellPosition[1];
    --cellPosition[1];
    
    cin>> xPos;
    cout<<endl;

    if (islower(xPos))
        xPos = toupper(xPos);

    while((xPos>=48 && xPos<=57) || cin.fail())
    {

        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout<< "You have entered the wrong value!!!!\n";
        cout<< "Enter coordinate ( Y coordinate - X coordinate ) : ";
	    cin>> cellPosition[1];
	    --cellPosition[1];
	    
	    cin>> xPos;
	    cout<<endl;

	    if (islower(xPos))
	        xPos = toupper(xPos);

    }

    cellPosition[0] = static_cast<int>(xPos) - 65;
      
      while(validatePosition(cellPosition, board, size, USER, COMPUTER, false))
      {
            cout<<"\nYou have entered incorrect position!\n";
            cout<<"Please enter again\n";

           cout<< "Enter coordinate ( Y coordinate - X coordinate ) : ";
            cin>> cellPosition[1];
           --cellPosition[1];

            cin>> xPos;

            cout<<endl;

        if (islower(xPos))
            xPos = toupper(xPos);

       cellPosition[0] = static_cast<int>(xPos) - 65;       
      }
}

bool validatePosition(int position[POSITION], int board[][TSIZE],int size,
                                    int turn, int opponent,bool control )
{
      if(!(position[0] >= 0 && position[0]< size) ||
             !(position[1] >= 0 && position[1]< size))
            return true;
      
  if(isThatLegal(board, size, position[0], position[1],turn, opponent,control))
            return false;

      return true;
}

bool isThatLegal(int board[][TSIZE], int size, int xCoor, int yCoor,
                              int turn, int opponent,bool control)
{
    bool legal = false;
      if(checkPosLeft(board,size, xCoor,yCoor,turn,opponent,false,       
                control) > 0)
        legal = true;
            
    if(checkPosRight(board,size, xCoor, yCoor, turn, opponent,false,
                control) >0)
        legal = true;

    if(checkPosUp(board,size, xCoor, yCoor, turn, opponent,false,
                control) >0)
        legal = true;

    if(checkPosDown(board,size, xCoor, yCoor, turn, opponent,false,
                control) >0)
        legal = true;

    if(checkPosLeftCrossUp(board,size, xCoor, yCoor, turn, opponent,false,
                control) >0)
        legal = true;

    if(checkPosRightCrossUp(board, size, xCoor, yCoor, turn, opponent,false,
                control) >0)
        legal = true;

    if(checkPosLeftCrossDown(board,size, xCoor, yCoor, turn, opponent,false,
                control) >0)
        legal = true;
       
    if(checkPosRightCrossDown(board, size, xCoor, yCoor,turn, opponent,false,
                control) >0)
            legal = true;
      
    return legal;
}

/*bu fonksiyon kullanicinin ya da bilgisayarin tasi oynayıp oynayamadigini 
kontrol eder ve diger butun check fonksiyonlari bu sekilde calişir*/
int checkPosLeft(int board[][TSIZE], int size, int xCoor, int yCoor,
            int turn, int opponent, bool aiMoveActive, bool control)
{
    int  foundedCellXCoorLeft = 0,// ters tarafta tasinin koordinitani tutar
    		//iki tas arasinda rakibin tasi olup olmadigina bakar
             requiredOpponentCellNumLeft = 0,
             opponentCellNumLeft = 0;//rakib oyunucunun tasini sayar
        bool foundedLeft = false, //kendi taşi var mı
                legalLeft = false;//dogru hamle mi

        //koordinat burada kontrol edilir
        for (int i = xCoor - 1; i >= 0 && foundedLeft == false; --i)
            if (board[yCoor][i] == turn) {
                foundedCellXCoorLeft = i;
                foundedLeft = true;
            }

        if (foundedLeft && (abs(xCoor - foundedCellXCoorLeft) > 1)) {
            
            requiredOpponentCellNumLeft =
                    abs(xCoor - foundedCellXCoorLeft - 1);


            if (requiredOpponentCellNumLeft > 0) {
                
                for (int i = foundedCellXCoorLeft + 1; i < xCoor; ++i)
                    if (board[yCoor][i] == opponent)
                        opponentCellNumLeft++;

                if (opponentCellNumLeft == requiredOpponentCellNumLeft)
                     legalLeft = true;
            }
        }
        //hareketlerin oynanamasina izin verilen kisim
        if (legalLeft && turn == USER && !control) {
            makeMoveLeft(board, xCoor, yCoor, foundedCellXCoorLeft, turn);
            return opponentCellNumLeft;
        } 
        else if (legalLeft && turn == USER && control)//eger hamleyi yapamiyorsa
        // bu else if sadece rakib oyuncunun kac tasi oldugunu dondurur
            return opponentCellNumLeft;
        else if (legalLeft && turn == COMPUTER && !aiMoveActive)
            return opponentCellNumLeft;
        else if (legalLeft && turn == COMPUTER && aiMoveActive) {
            makeMoveLeft(board, xCoor, yCoor, foundedCellXCoorLeft, turn);
            return opponentCellNumLeft;
        } else
            return 0;
} 

int checkPosRight(int board[][TSIZE], int size, int xCoor, int yCoor,
            int turn, int opponent, bool aiMoveActive,bool control)
{
    int foundedCellXCoorRight = 0,
                requiredOpponentCellNumRight = 0,
                opponentCellNumRight = 0;
        bool foundedRight = false,
                legalRight = false;

        for (int i = xCoor + 1; i < size && foundedRight == false; ++i)
            if (board[yCoor][i] == turn) {
                foundedCellXCoorRight = i;
                foundedRight = true;
            }

        if (foundedRight && (abs(foundedCellXCoorRight - xCoor) > 1)) {
            requiredOpponentCellNumRight =
                    abs(foundedCellXCoorRight - xCoor - 1);

            if (requiredOpponentCellNumRight > 0) {
                for (int i = xCoor + 1; i < foundedCellXCoorRight; ++i)
                    if (board[yCoor][i] == opponent)
                        opponentCellNumRight++;

                if (opponentCellNumRight == requiredOpponentCellNumRight)
                    legalRight = true;
            }
        }

        if (legalRight && turn == USER && !control) {
            makeMoveRight(board, xCoor, yCoor, foundedCellXCoorRight, turn);
            return opponentCellNumRight;
        } else if (legalRight && turn == USER && control)
            return opponentCellNumRight;
        else if (legalRight && turn == COMPUTER && !aiMoveActive)
            return opponentCellNumRight;
        else if (legalRight && turn == COMPUTER && aiMoveActive) {
            makeMoveRight(board, xCoor, yCoor, foundedCellXCoorRight, turn);
            return opponentCellNumRight;
        } else
            return 0;
}

int checkPosUp(int board[][TSIZE], int size, int xCoor, int yCoor,
            int turn, int opponent, bool aiMoveActive,bool control)
{
    int foundedCellYCoorUp = 0,
            requiredOpponentCellNumUp = 0,
            opponentCellNumUp = 0;
        bool foundedUp = false,
                legalUp = false;

        for (int i = yCoor - 1; i >= 0 && foundedUp == false; --i)
            if (board[i][xCoor] == turn) {
                foundedCellYCoorUp = i;
                foundedUp = true;
            }

        if (foundedUp && abs(yCoor - foundedCellYCoorUp) > 1) {
            requiredOpponentCellNumUp = abs(yCoor - foundedCellYCoorUp - 1);

            for (int i = foundedCellYCoorUp + 1; i < yCoor; ++i)
                if (board[i][xCoor] == opponent)
                    opponentCellNumUp++;

            if (opponentCellNumUp == requiredOpponentCellNumUp)
                legalUp = true;
        }

        if (legalUp && turn == USER && !control) {
            makeMoveUp(board, xCoor, yCoor, foundedCellYCoorUp, turn);
            return opponentCellNumUp;
        } else if (legalUp && turn == USER && control)
            return opponentCellNumUp;
        else if (legalUp && turn == COMPUTER && !aiMoveActive)
            return opponentCellNumUp;
        else if (legalUp && turn == COMPUTER && aiMoveActive) {
            makeMoveUp(board, xCoor, yCoor, foundedCellYCoorUp, turn);
            return opponentCellNumUp;
        }
        else
            return 0;
}

int checkPosDown(int board[][TSIZE], int size, int xCoor, int yCoor,
            int turn, int opponent, bool aiMoveActive,bool control)
{
    int foundedCellYCoorDown = 0,
            requiredOpponentCellNumDown = 0,
            opponentCellNumDown = 0;
        bool foundedDown = false,
                legalDown = false;

        for (int i = yCoor + 1; i < size && foundedDown == false; ++i)
            if (board[i][xCoor] == turn) {
                foundedCellYCoorDown = i;
                foundedDown = true;
            }

        if (foundedDown && (abs(foundedCellYCoorDown - yCoor) > 1)) {
            requiredOpponentCellNumDown =
                    abs(foundedCellYCoorDown - yCoor - 1);

            for (int i = yCoor + 1; i < foundedCellYCoorDown; ++i)
                if (board[i][xCoor] == opponent)
                    opponentCellNumDown++;

            if (opponentCellNumDown == requiredOpponentCellNumDown)
                legalDown = true;
        }

        if (legalDown && turn == USER && !control) {
            makeMoveDown(board, xCoor, yCoor, foundedCellYCoorDown, turn);
            return opponentCellNumDown;
        } else if (legalDown && turn == USER && control)
            return opponentCellNumDown;
        else if (legalDown && turn == COMPUTER && !aiMoveActive)
            return opponentCellNumDown;
        else if (legalDown && turn == COMPUTER && aiMoveActive) {
            makeMoveDown(board, xCoor, yCoor, foundedCellYCoorDown, turn);
            return opponentCellNumDown;
        }
        else
            return 0;
}

int checkPosLeftCrossUp(int board[][TSIZE], int size, int xCoor, int yCoor,
            int turn, int opponent, bool aiMoveActive,bool control)
{
    int foundedCellLeftCrossUp[POSITION];
        int requiredOpponentCellLeftCrossUp = 0,
            opponentCellNumLeftCrossUp = 0;
        bool foundedLeftCrossUp = false,
                legalLeftCrossUp = false;

        for (int i = yCoor - 1, j = xCoor - 1;
                 i >= 0 && j >= 0 && foundedLeftCrossUp == false;
                 --i, --j) {
            if (board[i][j] == turn) {
                foundedCellLeftCrossUp[0] = j;
                foundedCellLeftCrossUp[1] = i;
                foundedLeftCrossUp = true;
            }
        }

        if (foundedLeftCrossUp &&
            abs(xCoor - foundedCellLeftCrossUp[0]) > 1 &&
            abs(yCoor - foundedCellLeftCrossUp[1]) > 1) {

            requiredOpponentCellLeftCrossUp =
                   abs(xCoor - foundedCellLeftCrossUp[0] - 1);

           for (int i = foundedCellLeftCrossUp[1] + 1,
                    j = foundedCellLeftCrossUp[0] + 1;
                    i < yCoor && j < xCoor;
                    ++i, ++j) {
               if (board[i][j] == opponent)
                   ++opponentCellNumLeftCrossUp;
           }

           if (opponentCellNumLeftCrossUp == requiredOpponentCellLeftCrossUp)
               legalLeftCrossUp = true;
        }

        if (legalLeftCrossUp && turn == USER && !control) {
            makeMoveLeftCrossUp(board, xCoor, yCoor, foundedCellLeftCrossUp, turn);
            return opponentCellNumLeftCrossUp;
        } else if (legalLeftCrossUp && turn == USER && control)
            return opponentCellNumLeftCrossUp;
        else if (legalLeftCrossUp && turn == COMPUTER && !aiMoveActive)
            return opponentCellNumLeftCrossUp;
        else if (legalLeftCrossUp && turn == COMPUTER && aiMoveActive) {
            makeMoveLeftCrossUp(board, xCoor, yCoor, foundedCellLeftCrossUp, turn);
            return opponentCellNumLeftCrossUp;
        } else
            return 0;
}

int checkPosLeftCrossDown(int board[][TSIZE], int size, int xCoor, int yCoor,
            int turn, int opponent, bool aiMoveActive,bool control)
{
    int foundedCellLeftCrossDown[POSITION];
        int requiredOpponentCellLeftCrossDown = 0,
            opponentCellNumLeftCrossDown = 0;
        bool foundedLeftCrossDown = false,
                legalLeftCrossDown = false;

        for (int i = yCoor + 1, j = xCoor + 1;
                 i < size && j < size &&
                 foundedLeftCrossDown == false;
                 ++i, ++j)
            if (board[i][j] == turn) {
                foundedCellLeftCrossDown[0] = j;
                foundedCellLeftCrossDown[1] = i;
                foundedLeftCrossDown = true;
            }

        if (foundedLeftCrossDown &&
            abs(foundedCellLeftCrossDown[0] - xCoor) > 1 &&
            abs(foundedCellLeftCrossDown[1] - yCoor) > 1) {

            requiredOpponentCellLeftCrossDown =
                    abs(foundedCellLeftCrossDown[0] - xCoor - 1);

            for (int i = yCoor + 1, j = xCoor + 1;
                     i < foundedCellLeftCrossDown[1] &&
                     j < foundedCellLeftCrossDown[0];
                     ++i, ++j)
                if (board[i][j] == opponent)
                    ++opponentCellNumLeftCrossDown;

            if (opponentCellNumLeftCrossDown ==
                    requiredOpponentCellLeftCrossDown)
                legalLeftCrossDown = true;
        }

        if (legalLeftCrossDown && turn == USER && !control) {
            makeMoveLeftCrossDown(board, xCoor, yCoor, foundedCellLeftCrossDown,
                    turn);
            return opponentCellNumLeftCrossDown;
        } else if (legalLeftCrossDown && turn == USER && control)
            return opponentCellNumLeftCrossDown;
        else if (legalLeftCrossDown && turn == COMPUTER && !aiMoveActive)
            return opponentCellNumLeftCrossDown;
        else if (legalLeftCrossDown && turn == COMPUTER && aiMoveActive) {
            makeMoveLeftCrossDown(board, xCoor, yCoor, foundedCellLeftCrossDown, turn);
            return opponentCellNumLeftCrossDown;
        } else
            return 0;
}

int checkPosRightCrossUp(int board[][TSIZE], int size, int xCoor, int yCoor,
            int turn, int opponent, bool aiMoveActive,bool control)
{
    int foundedCellRightCrossUp[POSITION];
        int requiredOpponentCellRightCrossUp = 0,
            opponentCellNumRightCrossUp = 0;
        bool foundedRightCrossUp = false,
                legalRightCrossUp = false;

        for (int i = yCoor - 1, j = xCoor + 1;
                 i >= 0 && j < size && foundedRightCrossUp == false;
                 --i, ++j) {
            if (board[i][j] == turn) {
                foundedCellRightCrossUp[0] = j;
                foundedCellRightCrossUp[1] = i;
                foundedRightCrossUp = true;
            }
        }

        if (foundedRightCrossUp &&
            abs(foundedCellRightCrossUp[0] - xCoor) > 1 &&
            abs(foundedCellRightCrossUp[1] - yCoor) > 1) {

            requiredOpponentCellRightCrossUp =
                    abs(foundedCellRightCrossUp[0] - xCoor - 1);

            for (int i = yCoor -1, j = xCoor + 1;
                     i >= foundedCellRightCrossUp[1] &&
                     j < foundedCellRightCrossUp[0];
                     --i, ++j) {
                if (board[i][j] == opponent)
                    ++opponentCellNumRightCrossUp;
            }

            if (opponentCellNumRightCrossUp == requiredOpponentCellRightCrossUp)
                legalRightCrossUp = true;
        }

        if (legalRightCrossUp && turn == USER && !control) {
            makeMoveRightCrossUp(board, xCoor, yCoor, foundedCellRightCrossUp, turn);
            return opponentCellNumRightCrossUp;
        } else if (legalRightCrossUp && turn == USER && control)
            return opponentCellNumRightCrossUp;
        else if (legalRightCrossUp && turn == COMPUTER && !aiMoveActive)
            return opponentCellNumRightCrossUp;
        else if (legalRightCrossUp && turn == COMPUTER && aiMoveActive) {
            makeMoveRightCrossUp(board, xCoor, yCoor, foundedCellRightCrossUp, turn);
            return opponentCellNumRightCrossUp;
        } else
            return 0;
}

int checkPosRightCrossDown(int board[][TSIZE], int size, int xCoor, int yCoor,
            int turn, int opponent, bool aiMoveActive,bool control)
{
    int foundedCellRightCrossDown[POSITION];
        int requiredOpponentCellRightCrossDown = 0,
            opponentCellNumRightCrossDown = 0;
        bool foundedRightCrossDown = false,
                legalRightCrossDown = false;

        for (int i = yCoor + 1, j = xCoor - 1;
                 i < size && j >= 0 && foundedRightCrossDown == false;
                 ++i, --j) {
            if (board[i][j] == turn) {
                foundedCellRightCrossDown[0] = j;
                foundedCellRightCrossDown[1] = i;
                foundedRightCrossDown = true;
            }
        }

        if (foundedRightCrossDown &&
            abs(foundedCellRightCrossDown[0] - xCoor) > 1 &&
            abs(foundedCellRightCrossDown[1] - yCoor) > 1) {

            requiredOpponentCellRightCrossDown =
                    abs(xCoor - foundedCellRightCrossDown[0] - 1);

            for (int i = yCoor + 1, j = xCoor - 1;
                     i < foundedCellRightCrossDown[1] &&
                     j > foundedCellRightCrossDown[0];
                     ++i, --j) {
                if (board[i][j] == opponent)
                    ++opponentCellNumRightCrossDown;
            }

            if (opponentCellNumRightCrossDown ==
                    requiredOpponentCellRightCrossDown)
                legalRightCrossDown = true;
        }

        if (legalRightCrossDown && turn == USER && !control) {
            makeMoveRightCrossDown(board, xCoor, yCoor, foundedCellRightCrossDown,
                    turn);
            return opponentCellNumRightCrossDown;
        } else if (legalRightCrossDown && turn == USER && control)
            return opponentCellNumRightCrossDown;
        else if (legalRightCrossDown && turn == COMPUTER && !aiMoveActive) {
            return opponentCellNumRightCrossDown;
        } else if (legalRightCrossDown && turn == COMPUTER && aiMoveActive) {
            makeMoveRightCrossDown(board, xCoor, yCoor, foundedCellRightCrossDown,
                    turn);
            return opponentCellNumRightCrossDown;
        } else
            return 0;
}

void makeMoveLeft(int board[][TSIZE], int xCoor,int yCoor,
                        int foundedCellXCoorLeft, int turn)
{
    board[yCoor][xCoor] = turn;
        for (int i = foundedCellXCoorLeft + 1; i < xCoor; ++i)
            board[yCoor][i] = turn;
}

void makeMoveRight(int board[][TSIZE], int xCoor,int yCoor,
                        int foundedCellXCoorRight, int turn)
{
    board[yCoor][xCoor] = turn;
    for (int i = xCoor + 1; i < foundedCellXCoorRight; ++i)
        board[yCoor][i] = turn;
}

void makeMoveUp(int board[][TSIZE], int xCoor,int yCoor,
                        int foundedCellYCoorUp, int turn)
{
    board[yCoor][xCoor] = turn;
    for (int i = foundedCellYCoorUp + 1; i < yCoor; ++i)
        board[i][xCoor] = turn;
}

void makeMoveDown(int board[][TSIZE], int xCoor,int yCoor,
                        int foundedCellYCoorDown, int turn)
{
       board[yCoor][xCoor] = turn;
        for (int i = yCoor + 1; i < foundedCellYCoorDown; ++i)
            board[i][xCoor] = turn;
}

void makeMoveLeftCrossUp(int board[][TSIZE], int xCoor,int yCoor,
                        int foundedCellLeftCrossUp[], int turn)
{
     board[yCoor][xCoor] = turn;
        for (int i = foundedCellLeftCrossUp[1] + 1,
                 j = foundedCellLeftCrossUp[0] + 1;
                 i < yCoor && j < xCoor;
                 ++i, ++j)
            board[i][j] = turn;
}

void makeMoveLeftCrossDown(int board[][TSIZE], int xCoor,int yCoor,
                        int foundedCellLeftCrossDown[], int turn)
{
    board[yCoor][xCoor] = turn;
        for (int i = yCoor + 1, j = xCoor + 1;
             i < foundedCellLeftCrossDown[1] &&
             j < foundedCellLeftCrossDown[0];
             ++i, ++j)
            board[i][j] = turn;
}

void makeMoveRightCrossUp(int board[][TSIZE], int xCoor,int yCoor,
                        int foundedCellRightCrossUp[], int turn)
{
    board[yCoor][xCoor] = turn;
        for (int i = yCoor -1, j = xCoor + 1;
             i >= foundedCellRightCrossUp[1] &&
             j < foundedCellRightCrossUp[0];
             --i, ++j)
            board[i][j] = turn;
}


void makeMoveRightCrossDown(int board[][TSIZE], int xCoor,int yCoor,
                        int foundedCellRightCrossDown[], int turn)
{
    board[yCoor][xCoor] = turn;
        for (int i = yCoor + 1, j = xCoor - 1;
             i < foundedCellRightCrossDown[1] &&
             j >= foundedCellRightCrossDown[0];
             ++i, --j)
            board[i][j] = turn;
}

void computerPlay(int board[][TSIZE], int size)
{    
    int bestPosition[POSITION];
    int bestMove = 0, xCoor,yPos;
    char xPos='a';

    for(int i = 0; i < size; ++i)
        for(int j = 0; j < size; ++j)
            if(board[i][j] == NONE)
                if(bestMove < opponentCellCounter(board,size,j,i))
                {
                    bestMove = opponentCellCounter(board,size,j,i);
                    bestPosition[0] = j;
                    bestPosition[1] = i;
                }
                yPos = bestPosition[1];
                xCoor =bestPosition[0];
                cout<< "Computer played Ypos: "<< yPos+1;
                cout<< "  Xpos : "<< static_cast<char>(xPos +xCoor)<<endl<<endl;
    makeBestMove(board,size,bestPosition[0],bestPosition[1]);
}

void makeBestMove(int board[][TSIZE], int size, int xCoor, int yCoor)
{
    checkPosLeft(board,size,xCoor,yCoor,COMPUTER,USER,true,false);
        checkPosRight(board,size,xCoor,yCoor,COMPUTER,USER,true,false);
        checkPosUp(board,size,xCoor,yCoor,COMPUTER,USER,true,false);
        checkPosDown(board,size,xCoor,yCoor,COMPUTER,USER,true,false);
        checkPosLeftCrossUp(board,size,xCoor,yCoor,COMPUTER,USER,true,false);
        checkPosLeftCrossDown(board,size,xCoor,yCoor,COMPUTER,USER,true,false);
        checkPosRightCrossUp(board,size,xCoor,yCoor,COMPUTER,USER,true,false);
        checkPosRightCrossDown(board,size,xCoor,yCoor,COMPUTER,USER,true,false);
}

int opponentCellCounter(int board[][TSIZE], int size, int xCoor, int yCoor)
{
    int opponentCellNum = 0;

        opponentCellNum += checkPosLeft(board,size,xCoor,yCoor,COMPUTER,
                                        USER,false,false);
        opponentCellNum += checkPosRight(board,size,xCoor,yCoor,COMPUTER,
                                         USER,false,false);
        opponentCellNum += checkPosUp(board,size,xCoor,yCoor,COMPUTER,USER,
                                      false,false);
        opponentCellNum += checkPosDown(board,size,xCoor,yCoor,COMPUTER,
                                        USER,false,false);
        opponentCellNum += checkPosDown(board,size,xCoor,yCoor,COMPUTER,
                                        USER,false,false);
        opponentCellNum += checkPosLeftCrossUp(board,size,xCoor,yCoor,
                                               COMPUTER,USER,false,false);
        opponentCellNum += checkPosLeftCrossDown(board,size,xCoor,yCoor,
                                                 COMPUTER,USER,false,false);
        opponentCellNum += checkPosRightCrossUp(board,size,xCoor,yCoor,
                                                COMPUTER,USER,false,false);
        opponentCellNum += checkPosRightCrossDown(board,size,xCoor,yCoor,
                                                  COMPUTER,USER,false,false);
        return opponentCellNum;
}

bool isBoardFilled(int board[][TSIZE], int size)
{
    bool boardFilled = false;

        for (int i = 0; i < size; ++i)
            for (int j = 0; j < size; ++j)
                if (board[i][j] == NONE)
                    boardFilled = true;

        return boardFilled;
}

bool turnCanPlay(int board[][TSIZE], int size, int turn,int opponent)
{
    bool canPlay = false;
        int position [POSITION];

        for (int i = 0; i < size; ++i) {
            for (int j = 0; j < size; ++j) {
                if (board[i][j] == NONE) {
                    position[0] = j;
                    position[1] = i;
                    if (
                    !validatePosition(position,board,size,turn,opponent,
                            true))
                        canPlay = true;
                }
            }
        }

        return canPlay;
}

int countUserCells(int board[][TSIZE], int size)
{
    int userCellNum = 0;
    
    for (int i = 0; i < size; ++i)
            for (int j = 0; j < size; ++j)
                if (board[i][j] == USER)
                    ++userCellNum;

    return userCellNum;
}

int countComputerCells(int board[][TSIZE], int size)
{
    int userComputerNum = 0;

        for (int i = 0; i < size; ++i)
            for (int j = 0; j < size; ++j)
                if (board[i][j] == COMPUTER)
                    ++userComputerNum;

        return userComputerNum;
}

void fillTable(int board[][TSIZE], int size)
{
      for(int i=0; i<size; i++)
      {
            for(int j=0; j<size; j++)
            {
                  board[i][j] = NONE;                 
            }
      }
      board[(size/2) -1][(size/2) -1] = COMPUTER;
      board[(size/2)-1][(size/2)] = USER;
      board[(size/2)][(size/2)-1] = USER;
      board[(size/2)][(size/2)] = COMPUTER;
}

void printTable(int board[][TSIZE], int size)
{
      char colName = 'a';

      for(int i=0; i<size; i++)
      {
            cout <<"   " <<static_cast<char>(colName +i);
      }
           
      cout<< endl ;

      for(int i =0; i<size; i++)
      {
            cout<<"  -";
            for(int j=0; j<size; j++)
            {
                  cout<< "----";

            }
            cout<<endl;
            if(i>8)
            {
                  cout<< i+1<< "|";
            }
            else
                  cout<< i+1<<" |";

            for(int j=0; j<size; j++)
            {
                  if(board[i][j] == COMPUTER)
                        cout << " X |";
                  else if(board[i][j] == USER)
                        cout << " O |";
                  else 
                        cout << " . |";
            }

            cout<<endl;
      }

      cout<<"  -";
      for(int j=0; j<size; j++)
      {
            cout<<"----";
      }
      cout<<endl;
}