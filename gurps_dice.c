/******************************************************************************
*                                                                             *
*    ,o888888o.    8 8888      88 8 888888888o.   8 888888888o     d888888o.  *
*   8888     `88.  8 8888      88 8 8888    `88.  8 8888    `88. .`8888:' `88 *
* 8 8888       `8. 8 8888      88 8 8888     `88  8 8888     `88 8.`8888.   Y *
* 8 8888           8 8888      88 8 8888     ,88  8 8888     ,88 `8.`8888.    *
* 8 8888           8 8888      88 8 8888.   ,88'  8 8888.   ,88'  `8.`8888.   *
* 8 8888           8 8888      88 8 888888888P'   8 888888888P'    `8.`8888.  *
* 8 8888   8888888 8 8888      88 8 8888`8b       8 8888            `8.`8888. *
* 8 8888       .8' ` 8888     ,8P 8 8888 `8b.     8 8888        8b   `8.`8888 *
*   8888     ,88'    8888   ,d8P  8 8888   `8b.   8 8888        `8b.  ;8.`888 *
*    `8888888P'       `Y88888P'   8 8888     `88. 8 8888         `Y8888P ,88P *
*                                                                             *
******************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/******************************************************************************
*                         Type Defines and Something                          *
******************************************************************************/

typedef enum {FALSE = 0, TRUE} boolean;

typedef enum {
    CRITICAL_SUCCESS    = 1,
    SUCCESS             = 0,
    FAILURE             = -1,
    CRITICAL_FAILURE    = -2
} ROLL_STATUS;



static int roll(int num_sides)
{
    return ((rand() % num_sides) + 1);
}

/******************************************************************************
 * @fn groll()
 * @brief A classic GURPS roll
 * @return The sum of three six-sided dice. Ranges from 3 to 18.
 *****************************************************************************/
int groll(void)
{
    return roll(6) + roll(6) + roll(6);
}

int find_crit(int num_dice, int num_sides, int target, int range)
{
    if (target >= (num_sides * num_dice) - range) return CRITICAL_FAILURE;
    if (target <= (num_dice) + range) return CRITICAL_SUCCESS;
    return 0;
}

void fill_rolls(int roll_array[], int array_length, int sides)
{ for (int i = 0; i < array_length; i++) roll_array[i] = roll(sides); }

void init_dice(void){
    srand(time(NULL));
}

// int main(void)
// {
//     srand(time(NULL));
//     int num_dice, num_sides, roll_sum, crit_val;
    // while(TRUE)
    // {
    //     printf("Enter the number of sides, and the number of dice: ");
    //     scanf("%d %d", &num_sides, &num_dice);

    //     int rolls[num_dice];
    //     for (int j = 0; j < 10; j++)
    //     {
    //         fill_rolls(rolls, num_dice, num_sides);
    //         roll_sum = 0;
    //         for (int i = 0; i < num_dice; i++)
    //         {
    //             roll_sum += rolls[i];
    //             printf("%d + ", rolls[i]);
    //         }
    //         printf("= %d ", roll_sum);
    //         crit_val = find_crit(num_dice, num_sides, roll_sum, 1);
    //         if (crit_val == CRITICAL_FAILURE) printf("Critical Failure...");
    //         else if (crit_val == CRITICAL_SUCCESS) printf("Critical Success!");
    //         printf("\n");
    //     }
    // }
//     boolean three = FALSE;
//     boolean eighteen = FALSE;
//     int i = 0;
//     int myint;
//     while (!three && !eighteen)
//     {
//         i++;
//         myint = groll();
//         printf("%d\n", myint);
//         if ((myint == 3) && !three) {
//             three = TRUE;
//             printf("Got a THREE!\n");
//         }
//         if ((myint == 18) && !eighteen) {
//             eighteen = TRUE;
//             printf("Got an EIGHTEEN!\n");
//         }
//     }
//     printf("Took %d tries!\n", i);
//     return 0;
// }