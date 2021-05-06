/*
 * Author: Angel De Niz
 * Email: ad1038274@swccd.edu
 * ID: 1038274
 * Date: 09/2020
 * Program: findPath
 * Class: Math230
 * Description: Navigate a 2D array representing a topography elevation grid
 *              finding paths of least resistance. 
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <ctype.h>
#include <string.h>

#define ROWS 5
#define COLS 6

void calcSums(int topog[ROWS][COLS], int sumList[ROWS]);

int main(int argc, char** argv)
{
    
    int topography[ROWS][COLS] =
        {
            {3011, 2800, 2852, 2808, 2791, 2818},
            {2972, 2937, 2886, 2860, 2830, 2748},
            {2937, 2959, 2913, 2864, 2791, 2742},
            {2999, 2888, 2986, 2910, 2821, 2754},
            {2909, 3816, 2893, 2997, 2962, 2798}};
    int sumList[ROWS] = {0};
    int r, c;
    
    if (argc == 2)//for checking 2nd test array with modified value for topagraphy[2][2]
    {
        int arg = atoi(argv[1]);
        topography[2][2] = arg; //parameter is a number so set topography[2][2] to whatever was passed in via stdin

    }

    /*  student to implement calcSums */
    calcSums(topography, sumList); //pass in topography, get back list of elevation sums

    for (r = 0; r < ROWS; r++)
        printf("%d \n",sumList[r]); //should display calculated sums

    return 0;
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
        srand(time(NULL));
        if ((rand() % 2) == 0)
        {
            *r_curr = *r_curr - 1;
        }
        else
        {
            *r_curr = *r_curr + 1;
        }
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
void calcSums(int topog[ROWS][COLS], int sums[ROWS])
{
    int r_curr, c_curr; //temp values
    int curr_sum = 0;

    for (r_curr = 0; r_curr < ROWS; r_curr++)
    {
        int r_curr_tmp = r_curr; // to keep track of where path started (r_curr is updated below)
        for (c_curr = 0; c_curr < COLS - 1; c_curr++)
        {
            int current = topog[r_curr][c_curr]; //variables to make the following code more readable
            int top = topog[r_curr - 1][c_curr + 1];
            int mid = topog[r_curr][c_curr + 1];
            int bot = topog[r_curr + 1][c_curr + 1];

            int min = 0; // minimum difference between current array value and the next value along path

            if (r_curr == 0) // if on first row
            {
                min = getMin(current, __INT32_MAX__, mid, bot);             // get least absolute difference
                update_row(min, current, &r_curr, __INT32_MAX__, mid, bot); // update r_curr (current row)
                sums[r_curr_tmp] = sums[r_curr_tmp] + min;                  // add min to sums[]
            }
            else if (r_curr == ROWS - 1) // if on last row
            {
                min = getMin(current, top, mid, __INT32_MAX__);
                update_row(min, current, &r_curr, top, mid, __INT32_MAX__);
                sums[r_curr_tmp] = sums[r_curr_tmp] + min;
            }
            else // if on inner row
            {
                min = getMin(current, top, mid, bot);
                update_row(min, current, &r_curr, top, mid, bot);
                sums[r_curr_tmp] = sums[r_curr_tmp] + min;
            }
        }
        r_curr = r_curr_tmp; // reset r_curr to where the path started
    }
}
