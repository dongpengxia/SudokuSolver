//Sudoku puzzle solving program. Modify display[][] and filled for specific puzzles.
//2015

#include <iostream>
#include <iomanip>
using namespace std;

const int N = 3,
SIZE = N * N;

void updateBoard(int, int, int, bool [SIZE][SIZE][SIZE]);
void printDisplay(int [SIZE][SIZE]);
void setBoard(bool [SIZE][SIZE][SIZE], bool);
void printBoard(bool [SIZE][SIZE][SIZE]);

int main()
{
    //board is a 9x9x9 3-dimensional boolean array
    //if board[a][b][c] is false, that means that display[a][b] can not have value c
    bool board[SIZE][SIZE][SIZE];
    
    int filled;//number of spaces in display already known
    
    //display is a 9x9 2-dimensional array that holds the integer values
    int display[SIZE][SIZE] =
    {
    {4, 2, -1, -1, 6, -1, -1, -1, -1},
    {5, -1, -1, 0, 8, 4, -1, -1, -1},
    {-1, 8, 7, -1, -1, -1, -1, 5, -1},
    {7, -1, -1, -1, 5, -1, -1, -1, 2},
    {3, -1, -1, 7, -1, 2, -1, -1, 0},
    {6, -1, -1, -1, 1, -1, -1, -1, 5},
    {-1, 5, -1, -1, -1, -1, 1, 7, -1},
    {-1, -1, -1, 3, 0, 8, -1, -1, 4},
    {-1, -1, -1, -1, 7, -1, -1, 6, 8}
    };
    filled = 30; //# of spaces already known at start

    //local integer variables
    int i = 0, j = 0, k = 0, l = 0, m = 0, a = 0, b = 0, blank = 0, row = 0, column = 0, block = 0,
    vertical = 0, oFill = 0;
    
    setBoard(board, true);
    
    //this is the part where we initialize the 9x9x9 grid with boolean values
    for (row = 0; row < SIZE; row++)
        for (column = 0; column < SIZE; column++)
            if (display[row][column] != -1) //only apply changes if the value is already known
                updateBoard(row, column, display[row][column], board);
    
    //while not all values of display are known yet
    while (filled < SIZE*SIZE)
    {
        //displays the new grid each time a new conclusion is made for a display[][] value
        printDisplay(display);
        cout << endl << filled << endl;
        
        oFill = filled;
        for (i = 0; i < SIZE; i++)
        {
            for (j = 0; j < SIZE; j++)
            {
                //Check a horizontal row on a set height and row (only the column changes)
                column = a = b = 0;
                for (k = 0; k < SIZE; k++) //goes right, down a row, then up the third dimension
                {
                    if (!board[j][k][i])
                    {
                        column++;
                    }
                    //if board[j][k][i] is true  //board[a][b][blank] //blank is the missing number
                    else
                    {
                        blank = i;
                        a = j;
                        b = k;
                    }
                }
                
                //if column = 8, that means there can only be one true value left, located at [a][b][blank]
                if (column == SIZE - 1)
                {
                    display[a][b] = blank; //we found a new number for display
                    filled++; //increment the count of squares we've deduced
                    updateBoard(a,b,blank,board);
                }
                
                //check a vertical column for a set row and height
                row = a = b = 0;
                for (k = 0; k < SIZE; k++) //goes down, right, then up (third dimension)
                {
                    if (!board[k][j][i]) //if the column can not have that value
                    {
                        row++;
                    }
                    //if board[k][j][i] is true, board[a][b][blank]
                    else
                    {
                        blank = i;
                        a = k;
                        b = j;
                    }
                }
                
                //if we have deduced yet another number
                if (row == SIZE - 1)
                {
                    display[a][b] = blank;
                    filled++;
                    updateBoard(a,b,blank,board);
                }
                
                //this checks each 3x3 grid in a given height
                for (k = 0; k < SIZE; k++)
                {
                    block = a = b = 0;
                    
                    //check a single 3x3 grid
                    for (l = j - j % N; l < j - j % N + N; l++)
                        for (m = k - k % N; m < k - k % N + N; m++)
                        {
                            if (!board[l][m][i])
                            {
                                block++;
                            }
                            //if board[l][m][i] is true, board[a][b][blank]
                            else
                            {
                                blank = i;
                                a = l;
                                b = m;
                            }
                        }
                    //if only one true value for the 3x3 grid
                    if (block == SIZE - 1)
                    {
                        //we've deduced another number
                        display[a][b] = blank;
                        filled++;
                        updateBoard(a,b,blank,board);
                    }
                }
                
                //Checks vertical column for deductible values
                vertical = a = b = 0;
                for(k = 0; k < N; k++)
                {
                    if(!board[i][j][k])
                    {
                        vertical++;
                    }
                    else
                    {
                        a = i;
                        b = j;
                        blank = k;
                    }
                }
                if (vertical == SIZE - 1)
                {
                    display[a][b] = blank;
                    filled++;
                    updateBoard(a,b,blank,board);
                }
                
            }
        }
        printBoard(board);
        
    }//end while
    
    
    //displaying the completed solution
    printDisplay(display);
    cout << filled << endl;
    
    return 0;
    
}//end main

void updateBoard(int row, int column, int number, bool board[SIZE][SIZE][SIZE])
{
    int i, j;
    
    //the horizontal + sign of falses
    for (i = 0; i < SIZE; i++)
    {
        board[row][i][number] = false;
        board[i][column][number] = false;
    }
    //the horizontal 3x3 square is made false
    for (i = row - row % N; i < row - row % N + N; i++)
        for (j = column - column % N; j < column - column % N + N; j++)
        {
            board[i][j][number] = false;
        }
    //vertical line of blocks made false
    for(i = 0; i < SIZE; i++)
    {
        board[row][column][i] = false;
    }
    
}//end updateBoard

void printDisplay(int display[SIZE][SIZE])
{
    int i, j;
    cout << endl;
    for (i = 0; i < SIZE; i++)
    {
        for (j = 0; j < SIZE; j++)
            cout << setw(2) << display[i][j] << " ";
        cout << endl;
    }
    
}//end printDisplay

void setBoard(bool board[SIZE][SIZE][SIZE], bool truth)
{
    int i,j,k;
    for(i = 0; i < SIZE; i++)
        for(j = 0; j < SIZE; j++)
            for(k=0; k < SIZE; k++)
                board[i][j][k] = truth;
    
}//end setBoard

void printBoard(bool board[SIZE][SIZE][SIZE])
{
    int i,j,k;
    for(i = 0; i < SIZE; i++)
    {
        cout << i << endl;
        for(j = 0; j < SIZE; j++)
        {
            for(k = 0; k < SIZE; k++)
                cout << board[j][k][i] << " ";
            cout << endl;
        }
        cout << endl;
    }
    
}//end printBoard