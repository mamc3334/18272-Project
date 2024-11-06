//
// Created by finnb on 10/7/2024.
//

#include "progargs.hpp"

void prog_paths(const string& inName, const string& outName)
{
    setInFile(inName);
    setOutFile(outName);
}

void prog_info(const int argc)
{
    if (argc != InfoArgs) {
        cerr << "Error:\tInvalid extra arguments for info:\t" << (4 - argc) << "\n";
        exit(-1);
    }
}

void prog_maxlevel(const int argc, const vector<string> & args)
{
    if (argc != MaxLevelArgs) {
        cerr << "Error:\tInvalid extra arguments for maxlevel:\t" << (5 - argc) << "\n";
        exit(-1);
    }
    if (stoi(args[3]) < 0 || stoi(args[3]) > MaxIntensity) {
        cerr << "Invalid maxlevel: " << args[3] << "\n";
        exit(-1);
    }
}

void prog_resize(const int argc, const vector<string> & args)
{
    if (argc != ResizeArgs) {
        cerr << "Error:\tInvalid extra arguments for info:\t" << (6 - argc) << "\n";
        exit(-1);
    }
    if (stoi(args[3]) < 0) {
        cerr << "Invalid resize width: " << args[3] << "\n";
        exit(-1);
    }
    if (stoi(args[4]) < 0) {
        cerr << "Invalid resize height: " << args[4] << "\n";
        exit(-1);
    }
}

void prog_cutfreq(const int argc, const vector<string> & args)
{
    if (argc != CutFreqArgs) {
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
    if (argc != CompressArgs) {
        cerr << "Error:\tInvalid extra arguments for info:\t" << (4 - argc) << "\n";
        exit(-1);
    }
}