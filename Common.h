//  ---------------------------------------------------
//  Common:
//  - general functions
//  - generating random values
//  - sleep function
//
//  Advanced Databases: Assignment 3 Concurrency Control
//
//
//  Johanna Wald  1520979  johanna.wald@stud.sbg.ac.at
//  Elvis Milas   1223926  elvis.milas@stud.sbg.ac.at
//  Eva Lugstein  1121035  eva.lugstein2@stud.sbg.ac.at
//  ---------------------------------------------------

#ifndef COMMON_H
#define COMMON_H

#include <stdio.h>      /* printf, scanf, puts, NULL */
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */

static void initRand()
{
    srand ((unsigned int)time(NULL));

}

// generate a random integer value in the range 0 to max-1
static int RandomInt(const int max)
{
    return (rand() % max);
}

#endif