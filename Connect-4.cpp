/*                                                                         
Muhammad Umar Farooq                
21i-xxxx
Project
*/

#include <iostream>
#include <stdlib.h>
#include <windows.h>
#include <fstream>
#include <string>

using namespace std;

//Global character arrays declared to store, well... the names of the players.
char *name1 = new char[1];
char *name2 = new char[1];

//Enumerated datatype for the fancy colors used in the console window.
enum colors {black,
      blue,
      green,
      cyan,
      red,
      magenta,
      yellow,
      white,
      gray,
      lightblue,
      lightgreen,
      lightcyan,
      lightred,
      lightmagenta,
      lightyellow,
      lightwhite};

void setColor(int textColor, int bgColor);
void Menu();
void howTo();
void Play();
void Display(int **seats);
int checkWin(int **seats);

int main()
{
    for (int i=0; i<19; i++)
    {
        name1[i]=0;
        name2[i]=0;
    }
    int choose;
    menu:
    Menu();
    cin >> choose;
    if (cin.fail()) 
    {
        cin.clear();
        cin.ignore(INT_MAX, '\n');
        cout << "Please choose a valid option\n";
        Sleep(1000);
        system("CLS");
        goto menu;
    }
    switch (choose)
    {
    case 1:
        Play();
    break;

    case 2:
        howTo();
        system("PAUSE");
        system("CLS");
        goto menu;
    break;

    case 3:
        exit(0);
    break;

    default:
        cout << "Please choose a valid option\n";
        Sleep(1000);
        system("CLS");
        goto menu;
    break;
    }   
}

void setColor(int textColor, int bgColor) 
{
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), (textColor + (bgColor * 16)));
}

//Unsurprisingly, this function displays my humble menu screen.
void Menu()
{
    system("CLS");
    cout 
    << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~-CONNECT-4!-~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n"
    << "|                                                                      |\n"
    << "|                                                                      |\n"
    << "|                        Welcome to CONNECT-4!                         |\n"
    << "|                        1.PLAY NOW!                                   |\n"
    << "|                        2.HOW TO PLAY                                 |\n"
    << "|                        3.QUIT                                        |\n"
    << "|                                                                      |\n"
    << "|                                                                      |\n"
    << "|                                                                      |\n"
    << "|                                                                      |\n"
    << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~------------~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";    
}

//In the case the user had a rough childhood and never got to play this classic, this is the manual.
void howTo()
{
    system("CLS");
    cout 
    << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~-HOW TO PLAY-~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n"
    << "|                                                                       |\n"
    << "|                                                                       |\n"
    << "|   The goal is to be the first player to connect 4 of the same         |\n"
    << "|   colored discs in a row (either vertically, horizontally, or         |\n"
    << "|   diagonally)                                                         |\n"
    << "|                                                                       |\n"
    << "|   1.Players must alternate turns, and only one disc can be dropped    |\n"
    << "|     in each turn.                                                     |\n"
    << "|   2.On your turn, drop one of your colored discs from the top into    |\n"
    << "|     any of the seven slots.                                           |\n"
    << "|   3.The game ends when there is a 4-in-a-row or a stalemate.          |\n"
    << "|                                                                       |\n"
    << "|                                                                       |\n"
    << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~------------~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";
}

//This is where the magic.. i mean logic, happens!
void Play()
{
    ofstream outFile;
    ifstream inFile;
    string Names;
    bool name_found1=false;
    bool name_found2=false;

    outFile.open("Info.txt", ios::app);
    inFile.open("Info.txt", ios::in);
    cout << "Please Enter player one's name :\n";
    cin.ignore();
    cin.getline(name1,20,'\n');
    cout << "Please Enter player two's name :\n";
    cin.getline(name2,20,'\n');
    while (!inFile.eof())
    {
        getline(inFile, Names, '\n');
        if (Names == name1)
        {
            name_found1=true;
        }
        if (Names == name2)
        {
            name_found2=true;
        }
    }
    if (name_found1==false)
    {
        outFile << "\n";
        outFile << name1;
    }
    if (name_found2==false)
    {
        outFile << "\n";
        outFile << name2;
    }
    name_found1=false;
    name_found2=false;
    outFile.close();
    inFile.close();
    int **seats = new int*[13];
    for (int i=0; i<13; i++)
    {
        seats[i] = new int [13];
    }

    int col; 
    
    for (int i=0; i<13; i++)
    {
        for (int j=0; j<13; j++)
        {
            seats[i][j]=1;
        }
    }
    int turn=0;
    while (1)
    {
        //If turn is an even number, this one runs.
        if (turn%2==0)
        {
            Display(seats);
            redo1:
            setColor(red, black);
            cout << name1;
            setColor(white, black);
            cout << ", please enter the column in which you would like to drop your coin (1 to 7): ";
            cin >> col;
            //The check below gets rid of that terrifying infinite loop that the program goes into, when the user enters a string or a character.
            if (cin.fail()) 
            {
                cin.clear();
                cin.ignore(INT_MAX, '\n');
                cout << "Please enter a valid column\n";
                goto redo1;
            }
            //This check only allows the user to enter a coin into the columns presented to them.
            if (col<1 || col>7)
            {
                cout << "Please enter a valid column\n";
                goto redo1;
            }
            col+=2;
            //This establishes the players choice after checking which row, closest to the bottom, is available for the column that the player selected. 
            for (int row=9; row>=3; row--)
            {
                if (seats[row][col]==1)
                {
                    seats[row][col]=-1;
                    break;
                }
            }            
        }
        //If turn is an odd number, this one runs.
        else
        {
            Display(seats);
            redo2:
            setColor(blue, black);
            cout << name2;
            setColor(white, black);
            cout << ", please enter the column in which you would like to drop your coin (1 to 7): ";
            cin >> col;
            //The check below gets rid of that terrifying infinite loop that the program goes into, when the user enters a string or a character.
            if (cin.fail()) 
            {
                cin.clear();
                cin.ignore(INT_MAX, '\n');
                cout << "Please enter a valid column\n";
                goto redo2;
            }
            //This check only allows the user to enter a coin into the columns presented to them.
            if (col<1 || col>7)
            {
                cout << "Please enter a valid column\n";
                goto redo2;
            }
            col+=2;
            //This establishes the players choice after checking which row, closest to the bottom, is available for the column that the player selected. 
            for (int row=9; row>=3; row--)
            {
                if (seats[row][col]==1)
                {
                    seats[row][col]=-2;
                    break;
                }
            }            
        }
        //This keeps track of which turn it is, odd or even.
        turn++; 
        if(checkWin(seats)==1)
        {
            Display(seats);
            setColor(red, black);
            cout << name1 << " wins!\n";
            setColor(white, black);
            break;
        }
        else if(checkWin(seats)==2)
        {
            Display(seats);
            setColor(blue, black);
            cout << name2 << " wins!\n";
            setColor(white, black);
            break;
        }
         
    }
    for (int i=0; i<13; i++)
    {
        delete [] seats[i];
    }
    delete [] seats;
}

//This function is used to display the current state of the array, it shows the status of each and every block in the virtual 7x7 grid.
void Display(int **seats)
{
    system("CLS");
    for (int i=3; i<10; i++)
    {       
        for (int col=3; col<10; col++)
        {
            if (seats[i][col] == 1)
            {
                cout << "\t|\t";
            }
            else if (seats[i][col] == -1)
            {
                cout << "\t|";
                setColor(red, black);
                cout << "\tO";
                setColor(white, black);
            }
            else if (seats[i][col] == -2)
            {
                cout << "\t|";
                setColor(blue, black);
                cout << "\tO";
                setColor(white, black);
            }
        }
        cout << "\t|\n";   
        cout << "\t|---------------------------------------------------------------------------------------------------------------|\n";

    }
    cout << "\t|       1               2               3               4               5               6               7       |\n";        
}

int checkWin(int **seats)
{
    for (int i=3; i<10; i++)
    {
        for (int j=3; j<10; j++)
        {
            //North western diagonal check for player 1.
            if (seats[i][j]==-1 && seats[i+1][j+1]==-1 && seats[i+2][j+2]==-1 && seats[i+3][j+3]==-1)
            {
                return 1;
            }
            //North western diagonal check for player 2.
            if (seats[i][j]==-2 && seats[i+1][j+1]==-2 && seats[i+2][j+2]==-2 && seats[i+3][j+3]==-2)
            {
                return 2;
            }
            //North eastern diagonal check for player 1.
            if (seats[i][j]==-1 && seats[i-1][j+1]==-1 && seats[i-2][j+2]==-1 && seats[i-3][j+3]==-1)
            {
                return 1;
            }
            //North eastern diagonal check for player 2.
            if (seats[i][j]==-2 && seats[i-1][j+1]==-2 && seats[i-2][j+2]==-2 && seats[i-3][j+3]==-2)
            {
                return 2;
            }
            //Vertical check for player 1.
            if (seats[i][j]==-1 && seats[i+1][j]==-1 && seats[i+2][j]==-1 && seats[i+3][j]==-1)
            {
                return 1;
            }
            //Vertical check for player 2.
            if (seats[i][j]==-2 && seats[i+1][j]==-2 && seats[i+2][j]==-2 && seats[i+3][j]==-2)
            {
                return 2;
            }
            //Horizontal check for player 1.
            if (seats[i][j]==-1 && seats[i][j+1]==-1 && seats[i][j+2]==-1 && seats[i][j+3]==-1)
            {
                return 1;
            }
            //Horizontal check for player 2.
            if (seats[i][j]==-2 && seats[i][j+1]==-2 && seats[i][j+2]==-2 && seats[i][j+3]==-2)
            {
                return 2;
            }
        }
    }
    return 0;
}