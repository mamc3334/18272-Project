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
    displayInfo();
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
    cout << "maxlevel: " << argv[4] << endl;
    /* TODO: Intensity Rescaling
         * Read metadata similar to info but store instead of print
         * Store these somewhere in common
         * then go to aos/soa file for rest of read */
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
    /* TODO: Image resize
         * Read metadata similar to info but store instead of print
         * Store these somewhere in common
         * then go to aos/soa file for rest of read */
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
    cout << "Cutfreq" << endl;
    /* TODO: Remove least frequent colors
         * Read metadata similar to info but store instead of print
         * Store these somewhere in common
         * then go to aos/soa file for rest of read */
}

void prog_compress(const int argc)
{
    if (argc != 4) {
        cerr << "Error:\tInvalid extra arguments for info:\t" << (4 - argc) << "\n";
        exit(-1);
    }
    cout << "Compress" << endl;
    /* TODO: Photo Compression
         * Read metadata similar to info but store instead of print
         * Store these somewhere in common
         * go to aos/soa file
         * Follow color table instructions
         * create output CPPM file */
}