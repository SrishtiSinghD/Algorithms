#include<stdio.h>
#include<cs50.h>
#include<string.h>



// n : Size of the Chess Board
// Counter : Keeps track of the number of feasible solutions
int n, counter;    //Global Variables

/* This function is used to get a positive size / length of the side of Chessboard */
int get_len(void);

/* This fucntion uses BackTracking to Solve the N-Queens Problem */
void solve(string board[n][n], int row,int col[],int ndiag[],int rdiag[]);




// Driver Function
int main()
{
    //Initially there are no possible solutions
    counter = 0;

    //Get the size of the board from the user
    n= get_len();

    // I initialize or make a 2D array i.e. my chessboard of size n x n
    string board[n][n];

    /*

        Initially the board is empty
        So I will represent the empty spaces with *
        And later on replace them with a Queen(Q) where ever necessary

    */
    for(int i = 0; i < n; i++)
    {
        for(int j = 0; j < n; j++)
        {
            board[i][j] = "*";
        }
    }


    /*

        The N-Queen Problem Algorithm can be solved using three additional arrays along with the board

        Arrays used:

                    1. col :
                            - keep tracks of the coloumns which are already used or have a queen in it
                            - this helps in keeping track of the coloumn constraint

                    2. ndiag :
                            - Keeps track of the normal diagonal (bottom-left --> top-right) constraint

                                                     top-right
                                               //\\
                                                /
                                               /
                                              /
                                             /
                                            /
                                           /
                              bottom-left

                            - The boxes in the same normal diagonal have equal value of the expression : (row + coloumn)
                            - is a 1D array of size = (2*n)-1
                    3. rdiag :
                            - Keeps track of the normal diagonal (top-left --> bottom-right) constraint
                              top-left
                                        \
                                         \
                                          \
                                           \
                                            \
                                             \
                                             \V/
                                                 bottom-right


                            - The boxes in the same normal diagonal have equal value of the expression : (row - coloumn)
                            - But since it results in negative number and we cant have an array of negative indexes so we add (board size - 1) to it to make every number positive
                            - is a 1D array of size = (2*n)-1

    */
    int l = (2*n) - 1;
    int col[n], ndiag[l], rdiag[l];


    /*
        Intialially all coloumns are empty
        So to represent availability of coloumns, we initialize all the coloumn with a False/0 value
    */
    for(int i = 0; i < n; i++)
    {
        col[i] = 0;
    }


    /*
        Intialially all diagonals are empty and free from constraints
        So to represent availability, we initialize all the indexes representing a unique diagonal(normal or reverse) with a False/0 value
    */

    for(int i = 0; i < l; i++)
    {
        ndiag[i]= 0;
        rdiag[i]= 0;
    }


/* Calling the Solver Function and we will start from the first row (index = 0) */
    solve(board, 0, col, ndiag, rdiag);

/* Final note to the user on how many possible solutions the Computer found! */
    if(counter == 0)
    {
        printf("No Possible Solutions \n");
    }

    else
    {
        printf("Total Number of Possible Solutions = %d\n", counter);
    }


// Main function ends


}










/* Solver Function : made by using the powerful recursion */
void solve(string board[n][n], int row, int col[], int ndiag[], int rdiag[])
{

    // Base case : We reach the end of the board or the last row
    if(row == n)
    {
        counter++;
        printf("Solution %d: \n\n",counter);
        for(int i = 0; i < n; i++)
        {
            for(int j = 0; j < n; j++)
            {
                printf("%s",board[i][j]);
            }
            printf("\n");
        }
        printf("\n\n");
        return;
    }


   // Recursive Case

   /* We will test and try all possible combinations of the queens in the coloumns */
    for(int c=0; c < n; c++)
    {

        /*

            - Constraints :
                            {Since for each row we assign only one queen so that no two queens are in same row}

                            Constraints in the if statement :-
                            1. No two queens must be in the same coloumn
                            2. No two queens must be in the same normal diagonal
                            3. No two queens must be in the same reverse diagonal

        */

        if(col[c] == 0 && ndiag[row+c] == 0 && rdiag[row-c + n-1] == 0)
        {

            /* If all condition are satisfied, we can replace the blank space (*) with our Queen(Q) */
            board[row][c] = "Q";

            /* Update our constraint arrays to fulfill the restrictions */

            // We change the value of the index representing the coloumn to show it's occupied
            col[c] = 1;

            // We update the value of the index representing the common number shared by boxes in the same normal diagonal
            ndiag[row+c]=1;

            // We update the value of the index representing the common number shared by boxes in the same reverse diagonal
            rdiag[row-c + n-1]=1;

            // Now we move onto the next row
            solve(board, row+1, col, ndiag, rdiag);

            /*

                To find other possible solutions we backtrack to the previous state
                and free
                        - the space occupied by queen
                        - the coloumn occupied by the queen
                        - the normal diagonal occupied by the queen
                        - the reverse diagonal occupied by the queen

            */

            // the space occupied by queen
            board[row][c] = "*";

            // the coloumn occupied by the queen
            col[c]=0;

            // the normal diagonal occupied by the queen
            ndiag[row+c]=0;

            // the reverse diagonal occupied by the queen
            rdiag[row-c + n-1]=0;
        }
    }

}










// Function to recieve a positive board length
int get_len(void)
{
    int size;
    do
    {
        size = get_int("Board Size : ");
    }
    while (size <= 0);
    // The loop will keep getting implemented till the user enters a natural number
    return size;
}
