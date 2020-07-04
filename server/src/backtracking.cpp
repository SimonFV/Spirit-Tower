#include <stdio.h>

#define SIZE 6

//the maze problem
int maze[SIZE][SIZE] = {
    {0,1,1,1,1,1},
    {0,1,0,0,0,1},
    {0,1,0,1,0,0},
    {0,1,0,0,1,0},
    {0,1,1,0,1,0},
    {0,0,0,0,1,0}
};

// Positions start at 0 as in array
int x_start = 2; 
int y_start = 3;

int x_end = 3; 
int y_end = 5;

//matrix to store the solution
int solution[SIZE][SIZE];

//function to print the solution matrix
void printsolution()
{
    int i,j;
    for(i=0;i<SIZE;i++)
    {
        for(j=0;j<SIZE;j++)
        {
            printf("%d\t",solution[i][j]);
        }
        printf("\n\n");
    }
}

//function to solve the maze
//using backtracking
int solvemaze(int r, int c)
{
    //if destination is reached, maze is solved
    //destination is the last cell(maze[SIZE-1][SIZE-1])
    if((r==y_end) && (c==x_end))
    {
        solution[r][c] = 1;
        return 1;
    }
    //checking if we can visit in this cell or not
    //the indices of the cell must be in (0,SIZE-1)
    //and solution[r][c] == 0 is making sure that the cell is not already visited
    //maze[r][c] == 0 is making sure that the cell is not blocked
    if(r>=0 && c>=0 && r<SIZE && c<SIZE && solution[r][c] == 0 && maze[r][c] == 0)
    {
        //if safe to visit then visit the cell
        solution[r][c] = 1;
        //going down
        if(solvemaze(r+1, c))
            return 1;
        //going right
        if(solvemaze(r, c+1))
            return 1;
        //going up
        if(solvemaze(r-1, c))
            return 1;
        //going left
        if(solvemaze(r, c-1))
            return 1;
        //backtracking
        solution[r][c] = 0;
        return 0;
    }
    return 0;

}

int main()
{
    //making all elements of the solution matrix 0
    int i,j;
    for(i=0; i<SIZE; i++)
    {
        for(j=0; j<SIZE; j++)
        {
            solution[i][j] = 0;
        }
    }
    if (solvemaze(y_start,x_start))
        printsolution();
    else
        printf("No solution\n");
    return 0;
}