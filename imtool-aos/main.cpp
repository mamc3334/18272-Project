#include <iostream>
using namespace std;

#include "../common/binaryio.hpp"
#include "../common/progargs.hpp"

int main(int argc, char *argv[]) {
    if (argc < 4) {
        cerr << "Error:\tInvalid number of arguments:\t" << argc << "\n";
        exit(-1);
    } else {
        // Has the correct number of default arguments
        if(argv[3] == "info") {
            if (argc != 4) {
                cerr << "Error:\tInvalid extra arguments for info:\t" << (4 - argc) << "\n";
                exit(-1);
            }
            else
            {
                displayInfo(); //function in common progargs.
            }
        } else if (argv[3] == "maxlevel") {
            if (argc != 5) {
                cerr << "Error:\tInvalid extra arguments for maxlevel:\t" << (5 - argc) << "\n";
                exit(-1);
            }

            // do this in progrargs
            //// TODO: Check if arguments are strings before converting to an int (not sure how)
            if (atoi(argv[4]) < 0 || atoi(argv[4]) > 65535) {
                cerr << "Invalid maxlevel: " << argv[4] << "\n";
            }
            else
            {
                maxLevel(atoi(argv[4])); //function in progargs
            }
        } else if (argv[3] == "resize") {
            if (argc != 6) {
                cerr << "Error:\tInvalid extra arguments for info:\t" << (6 - argc) << "\n";
                exit(-1);
            }

            if (atoi(argv[4]) < 0) {
                cerr << "Invalid resize width: " << argv[4] << "\n";
            }

            if (atoi(argv[5]) < 0) {
                cerr << "Invalid resize height: " << argv[5] << "\n";
            }

            resize(atoi(argv[4]), atoi(argv[5])); //function in progargs

        } else if (argv[3] == "cutfreq") {
            if (argc != 5) {
                cerr << "Error:\tInvalid extra arguments for info:\t" << (5 - argc) << "\n";
                exit(-1);
            }

            if (atoi(argv[4]) < 0) {
                cerr << "Invalid cutfreq: " << argv[3] << "\n";
            }
            cutfreq(atoi(argv[4]));
        } else if (argv[3] == "compress") {
            if (argc != 4) {
                cerr << "Error:\tInvalid extra arguments for info:\t" << (4 - argc) << "\n";
                exit(-1);
            }
            compress();
        } else {
            cerr << "Error:\tInvalid option:\t" << argv[3] << "\n";
            exit(-1);
        }
    }
}