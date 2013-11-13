/** peran.hpp */

#ifndef __PERAN_HPP__
#define __PERAN_HPP__

using namespace std;


#define DIST_HALF 21.0975
#define DIST_FULL 42.195

/** structure of time */
/*typedef struct T_TIME {
    int hour;
    int minute;
    int second;
} s_time;*/

/** MODE */
#define MODE_NONE 0x0000
#define MODE_FTOP 0x0001
#define MODE_PTOF 0x0002

/** description string of mode */
static char mode_str[3][25] = {
    "None",
    "Finish-time to Pace-time",
    "Pace-time to Finish-time"
};

/** print help */
void print_help();

/**
 * parse time string to int
 * @param time string
 * @return time(second)
 */
int str_to_time(char *str);

/**
 * parse int to time string
 * @param time(second), time string
 */
void time_to_str(int time, char *str);

/**
 * parse double to time string
 * @param time(second), time string
 */
void dtime_to_str(double dtime, char *str);

/**
 * count number of on-bit
 * @param integer
 * @return number of on-bit
 */
int countbits(int bits);

/**
 * Output message on stderr and exit with error code
 * @param error message
 */
void exit_with_error(string msg);

#endif

