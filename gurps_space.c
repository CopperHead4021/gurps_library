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
 *                    GURPS Space from Steve Jackson Games                    *
 *          Written by Zeigler, J. F., Cambias, J. L., & Upchurch, W.         *
******************************************************************************/


/******************************************************************************
*                              Include Statments                              *
******************************************************************************/
#include "gurps_dice.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdint.h>
#include "logging.h"
#include <string.h>

/******************************************************************************
*                                   Defines                                   *
******************************************************************************/
#define NAME_SIZE 6 

/******************************************************************************
*                       Type Definitions and Constants                        *
******************************************************************************/


/******************************************************************************
 * @struct T_STELLAR_MASS_ENTRY
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

const T_MULTIPLE_STAR_ENTRY System_num_star_table[] = {
    { 3, 10, 1},
    {11, 15, 2},
    {16, 18, 3}
};

const int STELLAR_NUM_TABLE_SIZE =
    sizeof(System_num_star_table) / sizeof(T_MULTIPLE_STAR_ENTRY);

typedef struct T_STELLAR_AGE_ENTRY {
    int roll_min;
    int roll_max;
    uint8_t population;
    double base_age;
    double step_a;
    double step_b;
} T_STELLAR_AGE_ENTRY;

const T_STELLAR_AGE_ENTRY Stellar_age_table[] = {
    { 3,  3, 0, 0.00, 0.00, 0.00},
    { 4,  6, 1, 0.10, 0.30, 0.05},
    { 7, 10, 2, 2.00, 0.60, 0.10},
    {11, 14, 3, 5.60, 0.60, 0.10},
    {15, 17, 4, 8.00, 0.60, 0.10},
    {18, 18, 5, 10.0, 0.60, 0.10}
};

const char* Stellar_population_table[] = {
    "Extreme Population I",
    "Young Population I",
    "Intermediate Poplation I",
    "Old Poplation I",
    "Intermediate Poplation II",
    "Extreme Poplation II"
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

const char* STAR_LETTERS = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
#define STAR_LETTERS_SIZE sizeof(STAR_LETTERS) - 1

const char* STAR_NUMBERS = "0123456789ABCD";
#define STAR_NUMBERS_SIZE sizeof(STAR_NUMBERS) - 1

/******************************************************************************
 * @struct T_STAR
 * @brief Struct to store information about a star using GURPS Space generation
 * tables.
 * @param name A string containing the alpha-numeric name of the star
 * @param mass A double representing the mass of the star in solar-masses
 * @param population An integer representing the population around the star.
 * See the population table
 * @param base_age A double representing the current age of the star
 * @param step_a A double representing the age at which the star enters its
 * A-Step
 * @param step_b A double representing the age at which the star enters its
 * B-Step
 * @param type A string that represents the star type. Uses the OBAFGKM model
 * @param temp An integer that represents the star's temperature in kelvin
 * @param l_min A double representing the minimum luminosity of the star.
 * @param l_max A double representing the maximum luminosity of the star.
 * @param main_span A double representing
 * @param subgiant_span A double representing
 * @param giant_span A double representing
 * 
 * @details This structure is used to store the results of generating a star...
 *****************************************************************************/
typedef struct T_STAR {
    char name[NAME_SIZE + 1];
    double mass;
    uint8_t population;
    double base_age;
    double step_a;
    double step_b;
    char* type;
    int temp;
    double l_min;
    double l_max;
    double main_span;
    double subgiant_span;
    double giant_span;
} T_STAR;

/******************************************************************************
*                             Function Prototypes                             *
******************************************************************************/
// Stellar Classification 
static int                      system_generate_num_stars(void);
static void                     star_generate_name(char*);
static double                   star_generate_mass(void);
static T_STELLAR_AGE_ENTRY      star_generate_age(void);                
static T_STELLAR_CHARS_ENTRY    star_generate_characteristics(double mass);
static double*                  star_generate_companion_orbits(void);   // TODO
static double*                  star_generate_orbital_zones(void);      // TODO
       T_STAR                   star_generate_star(void);
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
static int system_generate_num_stars(void)
{
    int roll = groll();
    for (int i = 0; i < STELLAR_NUM_TABLE_SIZE; i++)
    {
        if ((roll >= System_num_star_table[i].roll_min) &&
            (roll <= System_num_star_table[i].roll_max))
        {
            return System_num_star_table[i].number_of_stars;
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
    return (T_STELLAR_AGE_ENTRY) {-1, -1, -1, -1.00, -1.00, -1.00};
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

#define LETTER_CHUNK NAME_SIZE/2
#define NUMBER_CHUNK NAME_SIZE/2

void star_generate_name(char* star_name)
{
    char name[2 * NAME_SIZE + 1] = "";
    char char_holder = 'A';
    for (int i = 0; i < NAME_SIZE; i++)
    {
        char_holder = STAR_LETTERS[rand() % STAR_LETTERS_SIZE];
        name[i] = char_holder;
    }
    for (int i = 0; i < NAME_SIZE; i++)
    {
        char_holder = STAR_NUMBERS[rand() % STAR_NUMBERS_SIZE];
        name[NAME_SIZE + i] = char_holder;
    }
    name[2 * NAME_SIZE] = '\0';
    star_name = name;
}

T_STAR star_generate_star(void)
{
    T_STAR star;
    star_generate_name(&star.name);
    star.mass = star_generate_mass();
    
    T_STELLAR_AGE_ENTRY star_age_roll = star_generate_age();
    star.population = star_age_roll.population;
    star.base_age = star_age_roll.base_age;
    star.step_a = star_age_roll.step_a;
    star.step_b = star_age_roll.step_b;

    T_STELLAR_CHARS_ENTRY star_chars_roll =
        star_generate_characteristics(star.mass);
    star.type = star_chars_roll.type;
    star.temp = star_chars_roll.temp;
    star.l_min = star_chars_roll.l_min;
    star.l_max = star_chars_roll.l_max;
    star.main_span = star_chars_roll.main_span;
    star.subgiant_span = star_chars_roll.subgiant_span;
    star.giant_span = star_chars_roll.giant_span;

    return star;
}

void star_printf(T_STAR star)
{
    LOGI("Star Details");
    LOGP("Name: %s", star.name);
    LOGR("Mass: %.2f solar masses", star.mass);
    LOGGR("Population: %u", star.population);
    LOGGR("Base Age: %.2f billion years", star.base_age);
    LOGGR("Step A: %.2f", star.step_a);
    LOGGR("Step B: %.2f", star.step_b);
    LOGB("Type: %s", star.type);
    LOGR("Temperature: %d K", star.temp);
    LOGGR("Luminosity Min: %.4f", star.l_min);
    LOGGR("Luminosity Max: %.4f", star.l_max);
    LOGGR("Main Sequence Span: %.2f billion years", star.main_span);
    LOGGR("Subgiant Span: %.2f billion years", star.subgiant_span);
    LOGGR("Giant Span: %.2f billion years", star.giant_span);
}
/******************************************************************************
*                                Main Function                                *
******************************************************************************/
int main(void)
{
    init_dice();

    T_STAR star = star_generate_star();
    star_printf(star);

    return 0;
}