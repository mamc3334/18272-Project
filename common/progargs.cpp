//
// Created by finnb on 10/7/2024.
//

#include "progargs.hpp"
#include <fstream>

void prog_paths(const string& inName, const string& outName)
{
    setInFile(inName);
    setOutFile(outName);
}

void prog_info(const int argc)
{
    if (argc != 4) {
        cerr << "Error:\tInvalid extra arguments for info:\t" << (4 - argc) << "\n";
        exit(-1);
    }
}

void prog_maxlevel(const int argc, char *argv[])
{
    if (argc != 5) {
        cerr << "Error:\tInvalid extra arguments for maxlevel:\t" << (5 - argc) << "\n";
        exit(-1);
    }
    if (atoi(argv[4]) < 0 || atoi(argv[4]) > 65535) {
        cerr << "Invalid maxlevel: " << argv[4] << "\n";
        exit(-1);
    }
}

void prog_resize(const int argc, char *argv[])
{
    if (argc != 6) {
        cerr << "Error:\tInvalid extra arguments for info:\t" << (6 - argc) << "\n";
        exit(-1);
    }
    if (atoi(argv[4]) < 0) {
        cerr << "Invalid resize width: " << argv[4] << "\n";
        exit(-1);
    }
    if (atoi(argv[5]) < 0) {
        cerr << "Invalid resize height: " << argv[5] << "\n";
        exit(-1);
    }
    util_set_new_w(atoi(argv[4]));
    util_set_new_h(atoi(argv[5]));
}

void prog_cutfreq(const int argc, char *argv[])
{
    if (argc != 5) {
        cerr << "Error:\tInvalid extra arguments for cutfreq:\t" << (5 - argc) << "\n";
        exit(-1);
    }
    if (atoi(argv[4]) < 0) {
        cerr << "Invalid cutfreq: " << argv[3] << "\n";
        exit(-1);
    }
}

void prog_compress(const int argc)
{
    if (argc != 4) {
        cerr << "Error:\tInvalid extra arguments for info:\t" << (4 - argc) << "\n";
        exit(-1);
    }
}