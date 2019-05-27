/*-----------------------------------------------------------------------------
 *				HTBLA-Leonding / Class: <your class name here>
 *-----------------------------------------------------------------------------
 * Exercise Number: #exercise_number#
 * File:			battleship.c
 * Author(s):		Peter Bauer
 * Due Date:		#due#
 *-----------------------------------------------------------------------------
 * Description:
 * <your description here>
 *-----------------------------------------------------------------------------
*/
#include <stdio.h>
#include "battleship.h"

CellContent my[FIELDSIZE][FIELDSIZE];
CellContent op[FIELDSIZE][FIELDSIZE];
CellContent guess[FIELDSIZE][FIELDSIZE];

void load_game()
{
    FILE* fd_my = fopen("battleship.my", "r");
    FILE* fd_op = fopen("battleship.op", "r");

    for (int i = 0; i < FIELDSIZE; i++)
    {
        for (int j = 0; j < FIELDSIZE; j++)
        {
            fread(&op[i][j], sizeof(CellContent), 1, fd_op);
            fread(&my[i][j], sizeof(CellContent), 1, fd_my);
            guess[i][j] = Unknown;
        }
    }
    
    fclose(fd_my);
    fclose(fd_op);
}

CellContent get_shot(int row, int col)
{
    if((col >= 0 && col < FIELDSIZE) && (row >= 0 && row < FIELDSIZE))
    {
        return my[row][col];
    }
    
    return OutOfRange;
}

bool shoot(int row, int col)
{
    if((col >= 0 && col < FIELDSIZE) && (row >= 0 && row < FIELDSIZE))
    {
        if(op[row][col] == Boat)
        {
            for(int i = row - 1; i <= row + 1; i++)
            {
                for(int j = col - 1; j <= col + 1; j++)
                {
                    guess[i][j] = Water;
                }
            }
        }
        
        guess[row][col] = op[row][col];
        return true;
    }
    return false;
}

CellContent get_my_guess(int row, int col)
{
    if(col >= 0 && col < FIELDSIZE && row >= 0 && row < FIELDSIZE)
    {
        return guess[row][col];
    }
    
    return OutOfRange;
}