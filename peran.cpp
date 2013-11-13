/** peran.cpp */

#include <iostream>
#include <getopt.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "peran.hpp"

static option options[] = {
    {"help", no_argument, NULL, 'h'},
    {"distance", required_argument, NULL, 'd'},
    {"finish-time", required_argument, NULL, 'f'},
    {"pace-time", required_argument, NULL, 'p'},
    {0, 0, 0, 0}
};

int main(int argc, char *argv[]) {
    int c, index;
    double dist = 0.0;
    int finish = -1, pace = -1;
    double finishd = -1.0, paced = -1.0;
    int mode = MODE_NONE;

    while ((c = getopt_long(argc, argv, "hd:f:p:", options, &index)) != -1) {
        switch (c) {
            case 'h':
                print_help();
                return 0;

            case 'd':
                if (strcmp("h", optarg) == 0)
                    dist = DIST_HALF;
                else if (strcmp("f", optarg) == 0)
                    dist = DIST_FULL;
                else
                    dist = atof(optarg);
                break;

            case 'f':
                finish = str_to_time(optarg);
                mode = mode | MODE_FTOP;
                break;

            case 'p':
                pace = str_to_time(optarg);
                mode = mode | MODE_PTOF;
                break;

            default:
                break;
        }
    }

    /* main proc */
    /* more than 1 mode are on */
    if (1 < countbits(mode))
        exit_with_error("Selected more than 1 mode.");

    /* calc and prepare result */
    char finish_str[128], pace_str[128];
    if (mode == MODE_FTOP) {
        paced = (double)finish / dist;
        dtime_to_str(paced, pace_str);
        time_to_str(finish, finish_str);
    } else if (mode == MODE_PTOF) {
        finishd = (double)pace * dist;
        time_to_str(pace, pace_str);
        dtime_to_str(finishd, finish_str);
    }

    /* disp results */
    cout << "Results:" << endl;
    cout << "  mode        " << mode_str[mode] << endl;
    cout << "  dist        " << dist << " km" << endl;
    cout << "  finish-time " << finish_str << endl;
    cout << "  pace-time   " << pace_str << " /km" << endl;

    return 0;
}

void print_help() {
    cout << "Usage:" << endl;
    cout << "    -d [--distance]:    Distance you will run in kilometer." << endl;
    cout << "                        Shortened form: h(21.0975km), f(42.195km)." << endl;
    cout << "    -f [--finish-time]: Time you want to finish in format like 1h23m45s." << endl;
    cout << "    -p [--pace-time]:   Pace time you want to keep in format like 4m00s." << endl;
}

int str_to_time(char *str) {
    /* value till current position */
    int v = 0;
    /* indivisual time, hour, minute, second */
    int h = 0, m = 0, s = 0;

    for (int i = 0; ; i++) {
        char c = str[i];
        if (c == '\0') {
            break;
        } else if ('0' <= c && c <= '9') {
            v = v * 10 + c - '0';
        } else if (c == 'h') {
            h = v;
            v = 0;
        } else if (c == 'm') {
            m = v;
            v = 0;
        } else if (c == 's') {
            s = v;
        }
    }

    return h * 3600 + m * 60 + s;
}

void time_to_str(int time, char *str) {
    int h, m, s;
    char t[128];

    str[0] = '\0';

    s = time % 60;
    time = time / 60;
    m = time % 60;
    time = time / 60;
    h = time;

    if (0 < h) {
        sprintf(t, "%dh", h);
        strcat(str, t);
    }
    if (0 < m) {
        sprintf(t, "%02dm", m);
        strcat(str, t);
    }
    sprintf(t, "%02ds", s);
    strcat(str, t);
}

void dtime_to_str(double dtime, char *str) {
    char t[128], dps[128];
    char *dpsd;
    int ip = (int)dtime; /* integer part */
    double dp = dtime - ip; /* decimal part */

    time_to_str(ip, t);
    strcpy(str, t);
    sprintf(dps, "%f", dp);
    dpsd = &dps[2];
    strcat(str, dpsd);
}

int countbits(int bits) {
    bits = (bits & 0x55555555) + (bits >> 1 & 0x55555555);
    bits = (bits & 0x33333333) + (bits >> 2 & 0x33333333);
    bits = (bits & 0x0f0f0f0f) + (bits >> 4 & 0x0f0f0f0f);
    bits = (bits & 0x00ff00ff) + (bits >> 8 & 0x00ff00ff);
    return (bits & 0x0000ffff) + (bits >> 16 & 0x0000ffff);
}

void exit_with_error(string msg) {
    cerr << "Error: " << msg << endl;
    exit(1);
}

