//
// Created by finnb on 10/7/2024.
//

#include "progargs.hpp"

void progPaths(string inName, string outName)
{
    const string inFile = inName;
    const string outFile = outName;
}

void info(int argc)
{
    if (argc != 4) {
        cerr << "Error:\tInvalid extra arguments for info:\t" << (4 - argc) << "\n";
        exit(-1);
    }
    else
    {
        displayInfo(); //function in common progargs.
    }
}



string getInFile()
{
    return inFile;
}

string getOutFile()
{
    return outFile;
}

void displayInfo()
{
    cout << "Display Info" << endl;
    /* TODO: display metadata to stdout
     * Open file, use get line, print meta data
     * Do we need to verify file has correct magic number?
     * This will be similar duplicate as first steps for aos/soa file reads
     */
    readMetaDataFromFile(getInFile());
    //TODO: sequence of cout statements
}

void maxLevel(int argc, char *argv[])
{
    if (argc != 5) {
        cerr << "Error:\tInvalid extra arguments for maxlevel:\t" << (5 - argc) << "\n";
        exit(-1);
    }
    if (atoi(argv[4]) < 0 || atoi(argv[4]) > 65535) {
        cerr << "Invalid maxlevel: " << argv[4] << "\n";
    }
    else
    {
        cout << "Max Level: " << argv[4] << endl;
        /* TODO: Intensity Rescaling
         * Read metadata similar to info but store instead of print
         * Store these somewhere in common
         * then go to aos/soa file for rest of read
         */
    }
}

void resize(int argc, char *argv[])
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
    cout << "Resize" << endl;
    /* TODO: Image resize
     * Read metadata similar to info but store instead of print
     * Store these somewhere in common
     * then go to aos/soa file for rest of read
     */
}

void cutfreq(int argc, char *argv[])
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
     * then go to aos/soa file for rest of read
     */
}

void compress(int argc)
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
     * create output CPPM file
     */
}