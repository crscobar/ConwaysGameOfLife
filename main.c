/** ----------------------------------------------
* Project 2
* This program implements Conway's Game of Life. *
* Rules:
*    -Any live cell with fewer than two live neighbours dies, as if caused by underpopulation.
*    -Any live cell with two or three live neighbours lives on to the next generation.
*    -Any live cell with more than three live neighbours dies, as if by overpopulation.
*    -Any dead cell with exactly three live neighbours becomes a live cell, as if by reproduction.
*
* Class: CS 107, Spr 2018
* System: onlineGDB, Windows 10 *
* @author Chris Escobar
* @version March 7, 2018
* ---------------------------------------------- */
#include <stdio.h>
#include <string.h>

const int MAXSIZE = 50;         //declaing constant variables
const int MAXTIME = 50;

int neighbors(int anArray[MAXSIZE][MAXSIZE][MAXTIME+1], int i, int j, int size, int step){
    int aliveCount = 0;         //counting alive neighbors variable
    //j = columns
    //i = rows

    if(i == 0 && j == 0){       //top left corner of grid, adds 3 valid neighbors
        aliveCount += anArray[i][j+1][step];
        aliveCount += anArray[i+1][j+1][step];
        aliveCount += anArray[i+1][j][step];
    }
    else if(i == (size-1) && j == (size-1)){      //bottom right corner of grid, adds 3 valid neighbors
        aliveCount += anArray[i][j-1][step];
        aliveCount += anArray[i-1][j-1][step];
        aliveCount += anArray[i-1][j][step];
    }
    else if(i == 0 && j == (size-1)){        //bottom left corner of grid, adds 3 valid neighbors
        aliveCount += anArray[i][j-1][step];
        aliveCount += anArray[i+1][j-1][step];
        aliveCount += anArray[i+1][j][step];
    }
    else if(i == (size-1) && j == 0){        //top right corner of grid, adds 3 valid neighbors
        aliveCount += anArray[i-1][j][step];
        aliveCount += anArray[i-1][j+1][step];
        aliveCount += anArray[i][j+1][step];
    }
    else if(j == 0 && (i > 0 && i < (size-1))){        //top row of grid, adds 5 valid neighbors
        aliveCount += anArray[i-1][j][step];
        aliveCount += anArray[i-1][j+1][step];
        aliveCount += anArray[i][j+1][step];
        aliveCount += anArray[i+1][j+1][step];
        aliveCount += anArray[i+1][j][step];
    }
    else if(i == 0 && (j > 0 && j < (size-1))){        //most left column of grid, adds 5 valid neighbors
        aliveCount += anArray[i][j-1][step];
        aliveCount += anArray[i+1][j-1][step];
        aliveCount += anArray[i+1][j][step];
        aliveCount += anArray[i+1][j+1][step];
        aliveCount += anArray[i][j+1][step];
    }
    else if(j == (size-1) && (i > 0 && i < (size-1))){      //bottom row of grid, adds 5 valid neighbors
        aliveCount += anArray[i-1][j][step];
        aliveCount += anArray[i-1][j-1][step];
        aliveCount += anArray[i][j-1][step];
        aliveCount += anArray[i+1][j-1][step];
        aliveCount += anArray[i+1][j][step];
    }
    else if(i == (size-1) && (j > 0 && j < (size-1))){      //most right column of grid, adds 5 valid neighbors
        aliveCount += anArray[i][j-1][step];
        aliveCount += anArray[i-1][j-1][step];
        aliveCount += anArray[i-1][j][step];
        aliveCount += anArray[i-1][j+1][step];
        aliveCount += anArray[i][j+1][step];
    }
    else if((i > 0 && i < (size-1)) && (j > 0 && j < (size-1))){        //middle of grid, adds all 8 valid neighbors
        aliveCount += anArray[i][j+1][step];
        aliveCount += anArray[i+1][j+1][step];
        aliveCount += anArray[i+1][j][step];
        aliveCount += anArray[i+1][j-1][step];
        aliveCount += anArray[i][j-1][step];
        aliveCount += anArray[i-1][j-1][step];
        aliveCount += anArray[i-1][j][step];
        aliveCount += anArray[i-1][j+1][step];
    }

    if(anArray[i][j][step] == 1){           //checks if current array spot is alive, if so executes body
        if(aliveCount == 2 || aliveCount == 3){             //checks if array has 2 or 3 alive neighbors, if so stays alive in next timestep
            anArray[i][j][step+1] = 1;
        }
        else if(aliveCount < 2 && aliveCount >= 0){             //checks if array spot has between 0 & 2 alive neighbors, if so it dies in next timestep
            anArray[i][j][step+1] = 0;
        }
        else if(aliveCount > 3){                //checks if array spot has more than 3 neighbors, if so it dies in next timestep
            anArray[i][j][step+1] = 0;
        }
    }
    else if(anArray[i][j][step] == 0){              //checks if current array spot is dead, if so executes body
        if(aliveCount == 3){                //checks if array spot has 3 alive neighbors, if so it becomes alive in next timestep
            anArray[i][j][step+1] = 1;
        }
    }
    return aliveCount;
}
// returns the number of neighbors of position i,j that are alive at time step.

void printGrid(int myGrid[MAXSIZE][MAXSIZE][MAXTIME+1], int size, int step){

    for(int j = 0; j < size; j++){
        for(int i = 0; i < size; i++){
            printf("%3d", myGrid[j][i][step]);              //prints grid  of given timestep  with 3 spaces in between each number
        }
        printf("\n");
    }

}
// print the grid of size (size x size) at time step.

int main(void)
{

    int myArray[MAXSIZE][MAXSIZE][MAXTIME+1];               //declaring variables in main
    int userRow;
    int userColumn;
    int userSteps;
    int userGrid;

    printf("Welcome to Conway's game of Life\n");
    printf("Please enter a number (n) for the 'n x n' grid for simulation (max n allowed is 50): ");
    scanf("%d", &userGrid);             //scans grid size

    if((userGrid > 50) || (userGrid < 0)){              //makes sure grid size is in bounds, if not prints error and exits
        printf("ERROR\n");
        return 0;
    }

    printf("\nNow enter the initial x y coordinates for the initial live cells (the board is indexed starting from 0 0).\nThen enter -1 -1 when done with live cells.\n");

    do{
        scanf("%d %d", &userRow, &userColumn);
        if((userRow < -1) || (userColumn < -1)){                //makes sure coordinates are in bounds, if not prints error and exits
            printf("ERROR\n");
            return 0;
        }
        else if((userRow >= userGrid) || (userColumn >= userGrid)){             //makes sure coordiantes are in bounds, if not prints error and exits
            printf("ERROR\n");
            return 0;
        }
        else if (((userRow > -1) && (userRow < userGrid)) || ((userColumn > -1) && (userColumn < userGrid))){               //if coordinates are in bounds, saves it in the array
            myArray[userRow][userColumn][0] = 1;
        }
    }while((userRow != -1) && (userColumn != -1));              //executes body until user enters -1 -1


    printf("\nPlease enter the number of time steps you wish to simulate, max number allowed is 50: ");
    scanf("%d", &userSteps);
    if(userSteps > 50 || userSteps < 0){                //makes sure step size is in bounds, if not prints error and exits
        printf("ERROR\n");
        return 0;
    }


    for(int k = 0; k < userSteps; k++){
        for(int j = 0; j < userGrid; j++){
            for(int i = 0; i < userGrid; i++){
                neighbors(myArray,i,j,userGrid,k);              //runs through neighbors function for every "block" of the array
            }
        }
    }

    printf("After %d timesteps the grid is: \n", userSteps);

    printGrid(myArray, userGrid, userSteps);                //prints the grid based on the user-entered numbers
    printf("Enter any number to close the program.\n");
    int num;
    scanf("%d", &num);
    return 0;
}
