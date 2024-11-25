//
// Created by finnb on 10/7/2024.
//

#include "progargs.hpp"
#include "utility.hpp"
#include <iostream>


void prog_info(const int argc)
{
    if (argc != InfoArgs) {
        cerr << "Error:\tInvalid arguments for info:\t" << (argc) << "\n";
        exit(1);
    }
}

void prog_maxlevel(const int argc, const vector<string> & args)
{
    if (argc != MaxLevelArgs) {
        cerr << "Error:\tInvalid arguments for maxlevel:\t" << (argc) << "\n";
        exit(1);
    }
    if (stoi(args[3]) < 0 || stoi(args[3]) > MaxIntensity) {
        cerr << "Error:\tInvalid maxlevel: " << args[3] << "\n";
        exit(1);
    }
}

void prog_resize(const int argc, const vector<string> & args)
{
    if (argc != ResizeArgs) {
        cerr << "Error:\tInvalid arguments for resize:\t" << (argc) << "\n";
        exit(1);
    }
    if (stoi(args[3]) < 0) {
        cerr << "Error:\tInvalid resize width: " << args[3] << "\n";
        exit(1);
    }
    if (stoi(args[4]) < 0) {
        cerr << "Error:\tInvalid resize height: " << args[4] << "\n";
        exit(1);
    }
}

void prog_cutfreq(const int argc, const vector<string> & args)
{
    if (argc != CutFreqArgs) {
        cerr << "Error:\tInvalid arguments for cutfreq:\t" << (argc) << "\n";
        exit(1);
    }
    if (stoi(args[3]) < 0) {
        cerr << "Error:\tInvalid cutfreq:\t" << args[3] << "\n";
        exit(1);
    }
}

void prog_compress(const int argc)
{
    if (argc != CompressArgs) {
        cerr << "Error:\tInvalid arguments for compress:\t" << (argc) << "\n";
        exit(1);
    }
}