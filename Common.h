//  ---------------------------------------------------
//  Common:
//  - general functions
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
#include <unistd.h>

// random double between 0 and max
/*static double RandomDouble(const double max) {
    srand ((unsigned int)time(NULL));
    return max * (static_cast<double>(rand()) / static_cast<double>(RAND_MAX));
}*/

static int RandomInt(const int max)
{
    srand ((unsigned int)time(NULL));
    return (rand() % max);
}

// Sleeps <duration>
static void Sleep(double duration) {
    usleep(1000000 * duration);
}

#endif