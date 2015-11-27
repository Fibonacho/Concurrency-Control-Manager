//Common

#include <stdio.h>      /* printf, scanf, puts, NULL */
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */
#include <unistd.h>

// random double between 0 and max
double RandomDouble(const double max) {
    return max * (static_cast<double>(rand()) / static_cast<double>(RAND_MAX));
}

// Sleeps <duration>
void Sleep(double duration) {
    usleep(1000000 * duration);
}