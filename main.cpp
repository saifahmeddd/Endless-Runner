#include <iostream>
#include <cstdlib>
#include <ctime>
#include <conio.h>
#include<fstream>
#include<iomanip>
#include<Windows.h>
#include<string>

using namespace std;


void Gameboard(char board[][20], int rows, int cols)
{
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            board[i][j] = ' ';
        }
    }


    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            if (i == 0 || i == rows - 1)
            {
                board[i][j] = '-';
            }
            if (j == 0 || j == cols - 1)
            {
                board[i][j] = '|';
            }
        }
    }
}


void player(char board[][20], int rows, int cols, int& playermoverows, int& playermovecols, int& distance, int& health, int& score)
{
    int centerColumn = cols / 2;
    playermovecols = centerColumn;
    playermoverows = rows - 2;
    board[playermoverows][playermovecols] = '#';

    distance = 0;
    health = 8;
    score = 0;
}



void moveplayer(char board[][20], int rows, int cols, int& playermoverows, int& playermovecols, char input, int& distance)
{
    if (input == 75) // left arrow key
    {
        if (board[playermoverows][playermovecols - 1] != '|')
        {
            board[playermoverows][playermovecols] = ' ';

            playermovecols--;
            distance = distance + 5; // Increment distance when the player moves
        }
    }


    else if (input == 77) // right arrow key
    {
        if (board[playermoverows][playermovecols + 1] != '|')
        {
            board[playermoverows][playermovecols] = ' ';

            playermovecols++;
            distance = distance + 2;
        }
    }
    else if (input == 72) // up arrow key
    {
        if (board[playermoverows - 1][playermovecols] != '-')
        {
            board[playermoverows][playermovecols] = ' ';

            playermoverows--;
            distance = distance + 2;
        }

    }
    else if (input == 80) // down arrow key
    {
        if (board[playermoverows + 1][playermovecols] != '-')
        {
            board[playermoverows][playermovecols] = ' ';

            playermoverows++;
            distance = distance + 2;
        }
    }
    else if (input == 32)   //for jump
    {
        for (int i = 0; i < 3; i++)
        {
            if (board[playermoverows - 1][playermovecols] != '-')
            {
                board[playermoverows][playermovecols] = ' ';

                playermoverows--;
                distance = distance + 5;
            }
            else if (board[playermoverows - 1][playermovecols] != '-')
            {
                board[playermoverows][playermovecols] = ' ';

                playermoverows++;
                distance = distance + 5;
            }

        }
    }
    else if (input == 'q')
    {
        exit(0);
    }

    board[playermoverows][playermovecols] = '#';
}




void healthdec(char board[][20], int rows, int cols, int& playermoverows, int& playermovecols, int& distance, int& health)
{
    if ((board[playermoverows][playermovecols] == 'X'))
    {
        health = health--;
    }

}


void scoreincrease(char board[][20], int rows, int cols, int& playermoverows, int& playermovecols, int& distance, int& health, int& score)
{
    if (distance >= 100)
    {
        if (health > 3)
        {
            score = score + 5;
        }
        

    }
}



void add_enemy(char board[][20], int rows, int cols)
{
    srand(time(nullptr));
    int rand_col = (rand() % (cols - 2)) + 1;
    int rand_row = 4;

    board[rand_row][rand_col] = 'X';
}


void move_enemies(char board[][20], int rows, int cols, int& distance)
{
    for (int i = rows - 2; i >= 0; i--)
    {
        for (int j = 1; j < cols - 2; j++)
        {
            if (board[i][j] == 'X' && i == 28)
            {
                board[i][j] = ' ';
                distance += 2;
            }

            if (board[i][j] == 'X')
            {
                board[i][j] = ' ';
                /* board[i+1][j] = ' ';
                 board[i+2][j] = ' ';*/

                board[i + 1][j] = 'X';

            }

        }
    }
}



void coin(char board[][20], int rows, int cols, int& distance, int& score)
{
    srand(time(0)); 

 
    int randRow = rand() % rows;
    int randCol = rand() % cols;

    board[randRow][randCol] = 'o';

    if ((board[rows][cols] != '|'))
    {
        board[rows][cols] = ' ';
    }

    if ((board[rows][cols] != '#'))
    {
        board[rows][cols] = 'o';
        score += 50;
    }
    board[rows][cols] = '#';
}
int main()
{
    int rows = 30;
    int cols = 20;
    int check;
    int distance = 0;
    int health = 0;
    int score = 0;
    int playermoverows = 0;
    int playermovecols = 0;
    int enemyCol = rand() % (cols - 2) + 1;
    char board[99][20];
    static int speed = 0;
    string name;
    string playerName;

    Gameboard(board, rows, cols);
    system("color f3");

    ifstream infile("score.txt");
    int prev_score;
    if (infile >> prev_score) 
    {
        cout << "\n\n\t\tYOUR LAST SCORE: " << prev_score << endl;
    }
    else
    {
        cout << "\n\n\t\tNO PREVIOUS HIGH SCORE FOUND" << endl;
    }
    infile.close();

    
        ifstream nameFile("name.txt");
    string prev_name;
    if (nameFile >> prev_name)
    {
        cout << "\n\n\t\tLAST PERSON WHO PLAYED THIS GAME: " << prev_name << endl;
        cout << endl;
    }
    
    else
    {
        cout << "\n\n\t\tNO PREVIOUS NAME FOUND" << endl;
    }
    nameFile.close();

    cout << "\t\t" << setw(41) << setfill('=') << "" << endl;
    cout << "\t\t" << setw(15) << setfill(' ') << "" << "VIPER DASH" << setw(15) << setfill(' ') << "" << endl;
    cout << "\t\t" << setw(41) << setfill('=') << "" << endl;
    cout << endl;
    cout << endl;
    cout << endl;
    cout << "ENTER YOUR NAME: ";
    getline(cin, playerName);

    ofstream nameFileOut("name.txt");
    if (nameFileOut) {
        nameFileOut << playerName;
        nameFileOut.close();
        cout << "\n\n\t\tYOUR NAME HAS BEEN SAVED." << endl;
    }
    else {
        cout << "ERROR: Unable to write the name to the file." << endl;
    }

    system("cls");

    cout << "\n \n \n" << "1: PRESS 1 TO SEE INSTRUCTIONS ";
    cout << "\n" << "2: PRESS 2 TO PLAY THE GAME " << endl;
    cin >> check;

    if (check == 1) {
        cout << " \t\t\t1.USE ARROW KEYS TO CONTROL THE PLAYER." << endl;
        cout << " \t\t\t2.GAME WILL BE OVER WHEN HEALTH GETS ZERO." << endl;
        cout << " \t\t\t3.YOU PLAYER SHOULD AVOID SNAKES IN ORDER TO MOVE UPWARDS AND SIDEWAYS." << endl;
        cout << " \t\t\t4.SCORE WILL BE INCREMENTED IF THE PLAYER COVERS A CERTAIN DISTANCE WITHOUT CRASHING.";
    }
    cout << endl;
    cout << endl;
    cout << endl;
    cin >> check;
    if (check == 2) {
        ifstream infile("score.txt");

        player(board, rows, cols, playermoverows, playermovecols, distance, health, score);

        while (true) {
            system("cls");
            Sleep(50);
            add_enemy(board, rows, cols);
            move_enemies(board, rows, cols, distance);
            coin(board, rows, cols, distance, score);
            for (int i = 0; i < rows; i++) {
                for (int j = 0; j < cols; j++) {
                    cout << board[i][j];
                }
                cout << endl;
            }

            if (distance > 200) {
                speed++;
            }

            cout << " DISTANCE : " << distance << endl;
            cout << " SCORE : " << score << endl;
            cout << " HEALTH :" << health << endl;
            scoreincrease(board, rows, cols, playermoverows, playermovecols, distance, health, score);

            if (_kbhit()) {
                char input = _getch();
                moveplayer(board, rows, cols, playermoverows, playermovecols, input, distance);
            }

            healthdec(board, rows, cols, playermoverows, playermovecols, distance, health);

            if (health <= 0) {
                system("cls");
                cout << "\n\n\n\t\t\tGAME OVER!!!" << endl;
                    cout << "\n\n\t\t\tYOUR SCORE IS: " << score << endl;
                break;
            }
        }

      
            if (score > prev_score) {
                ofstream outfile("score.txt");
                if (outfile) {
                    outfile << score;
                    outfile.close();
                                    cout << "\t\t\tCONGRATULATIONS! NEW HIGH SCORE!" << endl;
            }
            else {
                cout << "ERROR: Unable to write the score to the file." << endl;
            }
        }
    }

    return 0;
}


