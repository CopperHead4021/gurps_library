/******************************************************************************
 *                                                                            *
 *          .d8888b.  888     888 8888888b.  8888888b.   .d8888b.             *
 *         d88P  Y88b 888     888 888   Y88b 888   Y88b d88P  Y88b            *
 *         888    888 888     888 888    888 888    888 Y88b.                 *
 *         888        888     888 888   d88P 888   d88P  "Y888b.   d8b        *
 *         888  88888 888     888 8888888P"  8888888P"      "Y88b. Y8P        *
 *         888    888 888     888 888 T88b   888              "888            *
 *         Y88b  d88P Y88b. .d88P 888  T88b  888        Y88b  d88P d8b        *
 *          "Y8888P88  "Y88888P"  888   T88b 888         "Y8888P"  Y8P        *
 *                                                                            *
 *          .d8888b.                                                          *
 *         d88P  Y88b                                                         *
 *         Y88b.                                                              *
 *          "Y888b.   88888b.   8888b.   .d8888b  .d88b.                      *
 *             "Y88b. 888 "88b     "88b d88P"    d8P  Y8b                     *
 *               "888 888  888 .d888888 888      88888888                     *
 *         Y88b  d88P 888 d88P 888  888 Y88b.    Y8b.                         *
 *          "Y8888P"  88888P"  "Y888888  "Y8888P  "Y8888                      *
 *                    888                                                     *
 *                    888                                                     *
 *                    888                                                     *
 *                                                                            *
******************************************************************************/


/******************************************************************************
*                              Include Statments                              *
******************************************************************************/
#include "gurps_dice.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/******************************************************************************
*                       Type Definitions and Constants                        *
******************************************************************************/

/******************************************************************************
 * @struct StellarMassEntry
 * @brief Struct to store information about stellar mass based on dice rolls.
 * @param first_roll is the first roll
 * @param second_roll_min is the minimum range for the second roll
 * @param second_roll_max is the maximum range for the second roll
 * @param mass is the mass of the star in the rolled bracket
 * 
 * @details This structure is used to store the results of rolling two sets of
 * three six-sided dice and mapping them to a stellar mass in solar masses. The
 * first roll determines the initial category, and the second roll determines
 * the specific range within that category to find the corresponding stellar
 * mass.
 *****************************************************************************/
typedef struct T_STELLAR_MASS_ENTRY{
    int first_roll;
    int second_roll_min;
    int second_roll_max;
    double mass;
} T_STELLAR_MASS_ENTRY;

const T_STELLAR_MASS_ENTRY Stellar_mass_table[] = {
    {3,  3, 10, 2.00}, {3, 11, 18, 1.90}, {4,  3,  8, 1.80}, {4,  9, 11, 1.70},
    {4, 12, 18, 1.60}, {5,  3,  7, 1.50}, {5,  8, 10, 1.45}, {5, 11, 12, 1.40},
    {5, 13, 18, 1.35}, {6,  3,  7, 1.30}, {6,  8,  9, 1.25}, {6, 10, 10, 1.20},
    {6, 11, 12, 1.15}, {6, 13, 18, 1.10}, {7,  3,  7, 1.05}, {7,  8,  9, 1.00},
    {7, 10, 10, 0.95}, {7, 11, 12, 0.90}, {7, 13, 18, 0.85}, {8,  3,  7, 0.80},
    {8,  8,  9, 0.75}, {8, 10, 10, 0.70}, {8, 11, 12, 0.65}, {8, 13, 18, 0.60},
    {9,  3,  8, 0.55}, {9,  9, 11, 0.50}, {9, 12, 18, 0.45}, {10, 3,  8, 0.40},
    {10, 9, 11, 0.35}, {10,12, 18, 0.30}, {11, 3, 18, 0.25}, {12, 3, 18, 0.20},
    {13, 3, 18, 0.15}, {14, 3, 18, 0.10}, {15, 3, 18, 0.10}, {16, 3, 18, 0.10},
    {17, 3, 18, 0.10}, {18, 3, 18, 0.10}
};

const int STELLAR_MASS_TABLE_SIZE =
    sizeof(Stellar_mass_table) / sizeof(T_STELLAR_MASS_ENTRY);

typedef struct T_MULTIPLE_STAR_ENTRY {
    int roll_min;
    int roll_max;
    int number_of_stars;
} T_MULTIPLE_STAR_ENTRY;

const T_MULTIPLE_STAR_ENTRY Star_num_table[] = {
    { 3, 10, 1},
    {11, 15, 2},
    {16, 18, 3}
};

const int STELLAR_NUM_TABLE_SIZE =
    sizeof(Star_num_table) / sizeof(T_MULTIPLE_STAR_ENTRY);

typedef struct T_STELLAR_AGE_ENTRY {
    int roll_min;
    int roll_max;
    char* p_population;
    double base_age;
    double step_a;
    double step_b;
} T_STELLAR_AGE_ENTRY;

const T_STELLAR_AGE_ENTRY Stellar_age_table[] = {
    {3,   3, "Extreme Population I",      0.00, 0.00, 0.00},
    {4,   6, "Young Population I",        0.10, 0.30, 0.05},
    {7,  10, "Intermediate Poplation I",  2.00, 0.60, 0.10},
    {11, 14, "Old Poplation I",           5.60, 0.60, 0.10},
    {15, 17, "Intermediate Poplation II", 8.00, 0.60, 0.10},
    {18, 18, "Extreme Poplation II",      10.0, 0.60, 0.10}
};

const int STELLAR_AGE_TABLE_SIZE =
    sizeof(Stellar_age_table) / sizeof(T_STELLAR_AGE_ENTRY);

typedef struct T_STELLAR_CHARS_ENTRY {
    double mass;
    char* type;
    int temp;
    double l_min;
    double l_max;
    double main_span;
    double subgiant_span;
    double giant_span;
} T_STELLAR_CHARS_ENTRY;

const T_STELLAR_CHARS_ENTRY Stellar_chars_table[] = {
    {0.10, "M7", 3100, 0.0012,  0.0,    0.0,    0.0,    0.0},
    {0.15, "M6", 3200, 0.0036,  0.0,    0.0,    0.0,    0.0},
    {0.20, "M5", 3200, 0.0079,  0.0,    0.0,    0.0,    0.0},
    {0.25, "M4", 3300, 0.015,   0.0,    0.0,    0.0,    0.0},
    {0.30, "M4", 3300, 0.024,   0.0,    0.0,    0.0,    0.0},
    {0.35, "M3", 3400, 0.037,   0.0,    0.0,    0.0,    0.0},
    {0.40, "M2", 3500, 0.054,   0.0,    0.0,    0.0,    0.0},
    {0.45, "M1", 3600, 0.070,   0.08,   70.0,   0.0,    0.0},
    {0.50, "M0", 3800, 0.090,   0.11,   59.0,   0.0,    0.0},
    {0.55, "K8", 4000, 0.11,    0.15,   50.0,   0.0,    0.0},
    {0.60, "K6", 4200, 0.13,    0.20,   42.0,   0.0,    0.0},
    {0.65, "K5", 4400, 0.15,    0.25,   37.0,   0.0,    0.0},
    {0.70, "K4", 4600, 0.19,    0.35,   30.0,   0.0,    0.0},
    {0.75, "K2", 4900, 0.23,    0.48,   24.0,   0.0,    0.0},
    {0.80, "K0", 5200, 0.28,    0.65,   20.0,   0.0,    0.0},
    {0.85, "G8", 5400, 0.36,    0.84,   17.0,   0.0,    0.0},
    {0.90, "G6", 5500, 0.45,    1.0,    14.0,   0.0,    0.0},
    {0.95, "G4", 5700, 0.56,    1.3,    12.0,   1.8,    1.1},
    {1.00, "G2", 5800, 0.68,    1.6,    10.0,   1.6,    1.0},
    {1.05, "G1", 5900, 0.87,    1.9,    8.8,    1.4,    0.8},
    {1.10, "G0", 6000, 1.1,     2.2,    7.7,    1.2,    0.7},
    {1.15, "F9", 6100, 1.4,     2.6,    6.7,    1.0,    0.6},
    {1.20, "F8", 6300, 1.7,     3.0,    5.9,    0.9,    0.6},
    {1.25, "F7", 6400, 2.1,     3.5,    5.2,    0.8,    0.5},
    {1.30, "F6", 6500, 2.5,     3.9,    4.6,    0.7,    0.4},
    {1.35, "F5", 6600, 3.1,     4.5,    4.1,    0.6,    0.4},
    {1.40, "F4", 6700, 3.7,     5.1,    3.7,    0.6,    0.4},
    {1.45, "F3", 6900, 4.3,     5.7,    3.3,    0.5,    0.3},
    {1.50, "F2", 7000, 5.1,     6.5,    3.0,    0.5,    0.3},
    {1.60, "F0", 7300, 6.7,     8.2,    2.5,    0.4,    0.2},
    {1.70, "A9", 7500, 8.6,     10.0,   2.1,    0.3,    0.2},
    {1.80, "A7", 7800, 11.0,    13.0,   1.8,    0.3,    0.2},
    {1.90, "A6", 8000, 13.0,    16.0,   1.5,    0.2,    0.1},
    {2.00, "A5", 8200, 16.0,    20.0,   1.3,    0.2,    0.1}
};

const int STELLAR_CHARS_TABLE_SIZE =
    sizeof(Stellar_chars_table) / sizeof(T_STELLAR_CHARS_ENTRY);


/******************************************************************************
*                             Function Prototypes                             *
******************************************************************************/
// Stellar Classification 
static int                      star_generate_num_stars(void);
static double                   star_generate_mass(void);
static T_STELLAR_AGE_ENTRY      star_generate_age(void);                
static T_STELLAR_CHARS_ENTRY    star_generate_characteristics(double mass);
static double*                  star_generate_companion_orbits(void);   // TODO
static double*                  star_generate_orbital_zones(void);      // TODO
// Placing First Planets
// Place Planetary Orbits
// Place Worlds
// Place Moons

/******************************************************************************
*                          Declaration of Variables                           *
******************************************************************************/

/******************************************************************************
*                          Function Implementations                           *
******************************************************************************/

/******************************************************************************
*                              Private Functions                              *
******************************************************************************/
static int star_generate_num_stars(void)
{
    int roll = groll();
    for (int i = 0; i < STELLAR_NUM_TABLE_SIZE; i++)
    {
        if ((roll >= Star_num_table[i].roll_min) &&
            (roll <= Star_num_table[i].roll_max))
        {
            return Star_num_table[i].number_of_stars;
        }
    }
    return -1;
}

static double star_generate_mass(void)
{
    int first_roll = groll();
    int second_roll = groll();

    for (int i = 0; i < STELLAR_MASS_TABLE_SIZE; i++)
    {
        if (Stellar_mass_table[i].first_roll == first_roll &&
            Stellar_mass_table[i].second_roll_min <= second_roll &&
            Stellar_mass_table[i].second_roll_max >= second_roll)
        {
            return Stellar_mass_table[i].mass;
        }
    }
    return -1.0;
}

static T_STELLAR_AGE_ENTRY star_generate_age(void)
{
    int roll = groll();
    for (int i = 0; i < STELLAR_AGE_TABLE_SIZE; i++)
    {
        if ((roll >= Stellar_age_table[i].roll_min) &&
            (roll <= Stellar_age_table[i].roll_max))
        {
            return Stellar_age_table[i];
        }
    }
    return (T_STELLAR_AGE_ENTRY) {-0, -0, NULL, -0.00, -0.00, -0.00};
}

static T_STELLAR_CHARS_ENTRY star_generate_characteristics(double mass)
{
    for (int i = 0; i < STELLAR_CHARS_TABLE_SIZE; i++)
    {
        if (mass <= Stellar_chars_table[i].mass)
        {
            return Stellar_chars_table[i];
        }
    }
    return (T_STELLAR_CHARS_ENTRY)
        {-0.0, "XX", -0, -0.0, -0.0, -0.0, -0.0, -0.0};
}

/******************************************************************************
*                                Main Function                                *
******************************************************************************/
int main(void) {
    init_dice();

    double mass = get_stellar_mass();
    if (mass > 0) {
        printf("Generated stellar mass: %.2f solar masses\n", mass);
    } else {
        printf("Error generating stellar mass.\n");
    }

    return 0;
}