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

void prog_maxlevel(const int argc, const vector<string> & args)
{
    if (argc != 5) {
        cerr << "Error:\tInvalid extra arguments for maxlevel:\t" << (5 - argc) << "\n";
        exit(-1);
    }
    if (stoi(args[3]) < 0 || stoi(args[3]) > 65535) {
        cerr << "Invalid maxlevel: " << args[3] << "\n";
        exit(-1);
    }
}

void prog_resize(const int argc, const vector<string> & args)
{
    if (argc != 6) {
        cerr << "Error:\tInvalid extra arguments for info:\t" << (6 - argc) << "\n";
        exit(-1);
    }
    if (stoi(args[3]) < 0) {
        cerr << "Invalid resize width: " << args[3] << "\n";
        exit(-1);
    }
    if (stoi(args[4]) < 0) {
        cerr << "Invalid resize height: " << args[3] << "\n";
        exit(-1);
    }
}

void prog_cutfreq(const int argc, const vector<string> & args)
{
    if (argc != 5) {
        cerr << "Error:\tInvalid extra arguments for cutfreq:\t" << (5 - argc) << "\n";
        exit(-1);
    }
    if (stoi(args[3]) < 0) {
        cerr << "Invalid cutfreq: " << args[3] << "\n";
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