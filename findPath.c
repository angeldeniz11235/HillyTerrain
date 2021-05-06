// Your Name: Angel De Niz
// Your email: ad1038274@swccd.edu
// Your ID: 1038274

/*
* This application reads in topographic data (int values representing elevations on a map)
* then traverses the data left to right trying to find the path of lease resistance
* (path with least variance in elevation). 
* Usage: 
*       ~$ findPath [{required} - path to text file containing topographic data]
* Result:
*       ~$ [least sum] [starting row with least sum]
* Example:
*       ~$ findPath dataFolder/topoData.txt
*          323 5
*/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

#define MAXN 100L

//FUNCTION HEADERS
int **malloc2d(int r, int c); //given to you
int findLowestValue();
void calcsumList();
void getData(char *fileName); //you must write this to read in and process data

// GLOBAL VARIABLES
int ROWS, COLS; //must be initialized in your function
int **topog;    //must be allocated in your function
int *sumList;   //must be allocated in your function
int lowRow;

int main(int argc, char *argv[])
{
    char* fileName = argv[1];   //name of file will be here
    //char *fileName = "5by6a.txt"; //comment out to submit

    getData(fileName); //creates your 2d (topog[][]) and 1d array(sumList[]) from `fileName`

    calcsumList(); //populates your 1d array, `sumList[]`

    lowRow = findLowestValue();

    printf("%d %d\n", sumList[lowRow], lowRow);

    return 0;
} //end of main

/*
 * Takes a filename as a parameter and reads in necessary data
 * into memory dinamicaly allocated to the 2d array named topog[][](global variable).
 * Prints out an error if file does not exist. 
*/
void getData(char *fileName)
{
    char lineRead[MAXN];
    int ivarRead;
    double dvarRead;

    FILE *inFile = fopen(fileName, "r");

    if (inFile == NULL) // should print out a reasonable message of failure here
    {
        printf("fopen() failed. Is %s in the correct directory?\n", fileName);
        exit(1);
    }

    int i;
    for (i = 0; i < 10; i++) // read how many rows/cols topog[][] will need allocated 
    {
        if (i == 1)
        {
            fscanf(inFile, "%i", &COLS);
        }
        else if (i == 3)
        {
            fscanf(inFile, "%i", &ROWS);
        }
        else
        {
            fscanf(inFile, "%s", lineRead);
        }
    }

    topog = malloc2d(ROWS, COLS); //allocate memory to 2d array

    int j;
    int k;
    for (j = 0; j < ROWS; j++) // read values from file into topog[][]
    {
        for (k = 0; k < COLS; k++)
        {
            fscanf(inFile, "%i", &topog[j][k]);
        }
    }
    fclose(inFile); // close our file stream
}

int **malloc2d(int r, int c)
{
    int i;
    int **t = malloc(r * sizeof(int *));
    for (i = 0; i < r; i++)
        t[i] = malloc(c * sizeof(int));
    return t;
}

/*
 * Receives four integers and calculates the absolute
 * difference between the first value and each of the last 
 * three values. Whichever of the last three values
 * has the minimum absolute difference gets returned.
 * Input:   curr, top, mid, bot
 * Output:  min
 */
int getMin(int curr, int top, int mid, int bot)
{
    int x = abs(curr - top); // calculate absolute differences
    int y = abs(curr - mid);
    int z = abs(curr - bot);

    int min = __INT32_MAX__;
    int vals[] = {x, y, z};

    int i;
    for (i = 0; i < 3; i++) // find minimum value in vals[] and store in min
    {
        if (vals[i] < min)
        {
            min = vals[i];
        }
    }
    return min;
}

/*
 * Receives a minimum, a current value and the current row number
 * and three values. The function then checks which absolute difference
 * (between the current value and each of the three values) equals 
 * the minimum and updates the current row accordingly.
 * Input:   min, current, *r_curr, top, mid, bot
 * Output:  *r_curr
 */
void update_row(int min, int current, int *r_curr, int top, int mid, int bot)
{
    top = abs(current - top); // calculate absolute differences
    mid = abs(current - mid);
    bot = abs(current - bot);

    if (min == mid) // minimum equals straight across
    {
        return;
    }
    if (min == top & min != bot) // minimum equals top but not bottom
    {
        *r_curr = *r_curr - 1;
        return;
    }
    else if (min == bot & min != top) // minimum equals bottom but not top
    {
        *r_curr = *r_curr + 1;
        return;
    }
    else // minimum equals top and bottom
    {
        // srand(time(NULL));
        // if ((rand() % 2) == 0)
        // {
        *r_curr = *r_curr - 1;
        // }
        // else
        // {
        //     *r_curr = *r_curr + 1;
        // }
    }
}

/*
 *  Receives 2d matrix that represents topography
 *  and uses this data to calculate an elevation path sum for each 
 *  row.  
 *  Input:  topog[][]
 *  Output: sum[]
 *
 */
void calcsumList()
{
    sumList = malloc(ROWS * sizeof(int *)); // allocate memory
    int i;
    for (i = 0; i < ROWS; i++) // zero-out sumList[]
    {
        sumList[i] = 0;
    }

    int r_curr, c_curr; //temp values
    int curr_sum = 0;

    for (r_curr = 0; r_curr < ROWS; r_curr++)
    {
        int r_curr_tmp = r_curr; // to keep track of where path started (r_curr is updated below)
        for (c_curr = 0; c_curr < COLS - 1; c_curr++)
        {
            int current = topog[r_curr][c_curr]; //current value

            int min = 0; // minimum difference between current array value and the next value along path

            if (r_curr == 0) // if on first row
            {
                int mid = topog[r_curr][c_curr + 1];
                int bot = topog[r_curr + 1][c_curr + 1];
                min = getMin(current, __INT32_MAX__, mid, bot);             // get least absolute difference
                update_row(min, current, &r_curr, __INT32_MAX__, mid, bot); // update r_curr (current row)
                sumList[r_curr_tmp] = sumList[r_curr_tmp] + min;            // add min to sumList[]
            }
            else if (r_curr == ROWS - 1) // if on last row
            {
                int top = topog[r_curr - 1][c_curr + 1];
                int mid = topog[r_curr][c_curr + 1];
                min = getMin(current, top, mid, __INT32_MAX__);
                update_row(min, current, &r_curr, top, mid, __INT32_MAX__);
                sumList[r_curr_tmp] = sumList[r_curr_tmp] + min;
            }
            else // if on inner row
            {
                int top = topog[r_curr - 1][c_curr + 1];
                int mid = topog[r_curr][c_curr + 1];
                int bot = topog[r_curr + 1][c_curr + 1];
                min = getMin(current, top, mid, bot);
                update_row(min, current, &r_curr, top, mid, bot);
                sumList[r_curr_tmp] = sumList[r_curr_tmp] + min;
            }
        }
        r_curr = r_curr_tmp; // reset r_curr to where the path started
    }
}

/*
* Return the lowest value in sumList array.
*/
int findLowestValue()
{
    int i, k, row = 0, min = __INT32_MAX__;
    for (i = 0; i < ROWS; i++)
    {
        if (sumList[i]<min)
        {
            row = i;
            min = sumList[i];
        }
        
    }
    return row;
}