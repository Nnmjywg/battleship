//----- Copyright (C) 2018 NNmJYwg -----//
//-----           GPL v3           -----//

// Checklist:
// [x]  Implement input
// -->  [x] Check the input to make sure it's 1-10 (and avoid negative numbers!)
//
// [x]  Finish the game manager
//
// [x]  Write the draw functions
//
// [x]  Write a function that will generate ships (for now just random squares)
// -->  [ ] Write a function which will generate full ships
//
// [x]  Write a function that will check hits and misses
// -->  [ ] Write a function that will keep track of destroyed ships
//

// Includes
#include <iostream> // For IO
#include <time.h> // To make a nice seed (not meant ambiguously)
#include <random> // Self-explanatory
#include <limits> // For RNG

// Important game stuff
const int empty = 0; // Water
const int occupied = 1; // Ship (not shown)
const int hit = 2; // Hit a ship
const int miss = 3; // Missed
const int ship = 4; // Debug, show ship

// Variables
const int fields = 10;
// We want a 10x10 field
int board[fields][fields]; // board[x][y]
// 4 Different rotations (0, 1, 2, 3)

// Random ship generator
void genship(int number, int board[fields][fields]);
int genrand(int min, int max); // Generate a nice random number in a min-max range
int ships = 10; // 10 Ships (for now squares)


// Functions

// Main game manager
int game(void);

// Draw functions

// Initialize board
void initb(int array[fields][fields]);
// Draw one row of the board
void draw_one_row(int array[fields][fields], int row_to_draw);
// Draw the whole board
void draw_board(int array[fields][fields]);
// Draw vertical lines
void draw_v_lines(int fields);

// Print numbers on X
void px(int fields);

// Print
void printx(void);
void printy(void);

// Input
int inputx(int input_x, int x, int fields);
int inputy(int input_y, int y, int fields);

int ip1x;   int ip1y; // Input of Player 1, X, player 1, Y
int p1x;    int p1y; // Player 1 X, player 1 Y

// # of guesses
int guesses;

int scanShips(int board[fields][fields]); // Scan the board for ships
int genShips = 0; // # of generated ships

bool checkHit(int x, int y, int board[fields][fields]); // Check for a hit

// Has the game finished yet?
bool gameFinished = false;
// Special win
bool special = false;

// Error + abort
void error(void);

int main(int argc, char *argv[])
{
    game();
    return 0;
}

// This next function will scan one row at a time, then scan 10 rows.
// The integer increased by the function, genShips, will be used to determine a win.
int scanShips(int board[fields][fields])
{
    for(int i = 0; i < fields; i++)
        for(int j = 0; j < fields; j++){
            if(board[j][i] == ship || board[j][i] == occupied)
                genShips++;
            else {}
        }
    return genShips;
}

bool checkHit(int x, int y, int board[fields][fields])
{
    if(board[x][y] == occupied || board[x][y] == ship)
    {
        board[x][y] = hit;
        genShips--;
        std::cout <<"Hit!\n";
        std::cout << genShips << " ships left\n";
        return true;
    }
    
    else {
        board[x][y] = miss;
        std::cout << "Miss.\n";
        std::cout << genShips << " ships left\n";
        return false;
    }
}

int genrand(void)
{
    std::random_device device;
    std::mt19937 generator(device());
    std::uniform_int_distribution<int> distribution(1,10);
    return(distribution(generator));
}

void genship(int ships, int board[fields][fields])
{
    for(int i = 1; i <= ships; ++i) {
        // std::cout << i << "\n";
        board[genrand()][genrand()] = occupied;
    }
}

void px(int fields)
{
    std::cout << "      ";
    for(int i = 1; i < fields + 1; i++)
    {
        if(i == 1)
            std::cout << "  1  ";
        else if(i == fields && fields >= 10)
            std::cout << " " << i << "\n";
        else if(i == fields && fields < 10)
            std::cout << "  " << i << "\n";
        else
            std::cout << "  " << i << "  ";
    }
    std::cout << "      ";
    for(int i = 1; i < fields + 1; i++)
    {
        if(i == 1)
            std::cout << "  |  ";
        else if(i == fields)
            std::cout << "  " << "|" << "\n";
        else
            std::cout << "  " << "|" << "  ";
    }
}

void initb(int array[fields][fields])
{
    for(int x = 1; x <= 10; x++)
    {
        for(int y = 1; y <= 10; y++)
        {
            array[x][y] = empty;
        }
    }
}

void draw_v_lines(int fields)
{
    std::cout << "\t";
    for(int i = 0; i < fields; i++)
    {
        if(i == 0)
            std::cout << "❘  ";
        else if(i == fields-1)
            std::cout << "  ❘\n";
        else
            std::cout << "  ❘  ";
    }
}

void draw_one_row(int array[fields][fields], int row_to_draw)
{
    if(row_to_draw == 9)
        std::cout << row_to_draw+1 << "————— ";
    else
        std::cout << row_to_draw+1 << "——————\t";
    for(int i = 0; i < fields; i++)
    {

        if(array[row_to_draw][i] == empty || array[row_to_draw][i] == occupied)
        {
            if(i == 0)
                std::cout << "  —";
            else if(i == 9) {
                std::cout << "—  \n";
                if(row_to_draw == fields-1)
                    std::cout << "\n";
                else
                    draw_v_lines(fields);
            }
            else
                std::cout << "—   —";
        }
        
        else if(array[row_to_draw][i] == hit)
        {
            if(i == 0)
                std::cout << "X —";
            else if(i == 9) {
                std::cout << "— X\n";
                if(row_to_draw == fields-1)
                    std::cout << "\n";
                else
                    draw_v_lines(fields);
            }
            else
                std::cout << "— X —";
        }
        
        else if(array[row_to_draw][i] == miss)
        {
            if(i == 0)
                std::cout << "O —";
            else if(i == 9) {
                std::cout << "— O\n";
                if(row_to_draw == fields-1)
                    std::cout << "\n";
                else
                    draw_v_lines(fields);
            }
            else
                std::cout << "— O —";
        }
        
        else if(array[row_to_draw][i] == ship)
        {
            if(i == 0)
                std::cout << "S —";
            else if(i == 9) {
                std::cout << "— S\n";
                if(row_to_draw == fields-1)
                    std::cout << "\n";
                else
                    draw_v_lines(fields);
            }
            else
                std::cout << "— S —";
        }
    }
}

void draw_board(int array[fields][fields])
{
    px(fields);
    for(int i = 0; i < fields; i++)
    {
        draw_one_row(array, i);
    }
}

void error(void)
{
    std::cerr << "Something went wrong!\n";
    abort();
}

void printx(void)
{
    std::cout << "Enter an x-value: ";
}

void printy(void)
{
    std::cout << "Enter a y-value:  ";
}

int inputx(int input_x, int x, int fields)
{
    while(input_x > fields || input_x < 1)
    {
        printy();
        std::cin >> input_x;
        if(input_x > fields || input_x < 1)
            std::cerr << "Sorry, your input is not in the range.\n";
    }
    return x = input_x - 1;
}

int inputy(int input_y, int y, int fields)
{
    while(input_y > fields || input_y < 1)
    {
        printx();
        std::cin >> input_y;
        if(input_y > fields || input_y < 1)
            std::cerr << "Sorry, your input is not in the range.\n";
    }
    return y = input_y - 1;
}

int game(void)
{
    initb(board);
    genship(ships, board);
    scanShips(board);
    while(!gameFinished)
    {
        draw_board(board);
        checkHit(inputx(ip1x, p1x, fields), inputy(ip1y, p1y, fields), board);
        guesses++;
        if(genShips == 0) {
            gameFinished = true;
            std::cout << "You win!\n" << "You took " << guesses << " to win!";
        } else {}
        
        if(guesses == 75)
        {
            std::cout << "Sorry, you've guessed 75 times now and still haven't won. This is getting boring for you.\n";
            exit(1);
        } else {}
    }
    return genShips + 1;
}