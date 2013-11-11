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

    /* mode -- 0:none 1:f->u 2:u->f */
    int mode = 0;

    while ((c = getopt_long(argc, argv, "hd:f:u:", options, &index)) != -1) {
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
                mode = 1;
                break;

            case 'u':
                pace = str_to_time(optarg);
                mode = 2;
                break;

            default:
                break;
        }
    }

    /* main proc */
    if (mode == 1) {
        pace = finish / dist;
    } else if (mode == 2) {
        finish = pace * dist;
    }

    /* disp results */
    char finish_str[128], pace_str[128];
    time_to_str(finish, finish_str);
    time_to_str(pace, pace_str);

    cout << "Results:" << endl;
    cout << "  mode        " << mode_str[mode] << endl;
    cout << "  dist        " << dist << " (km)" << endl;
    cout << "  finish-time " << finish_str << endl;
    cout << "  pace-time   " << pace_str << " (/km)" << endl;

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

