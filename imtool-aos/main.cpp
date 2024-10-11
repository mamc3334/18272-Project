#include <iostream>
#include <string.h>
using namespace std;

int main(int argc, char *argv[]) {
    if (argc < 3) {
        cerr << "Error:\tInvalid number of arguments:\t" << argc << "\n";
        exit(-1);
    } else {
        // Has the correct number of default arguments
        if(strcmp(argv[2], "info") == 1) {
            if (argc != 3) {
                cerr << "Error:\tInvalid extra arguments for info:\t" << (3 - argc) << "\n";
                exit(-1);
            }
        } else if (strcmp(argv[2], "maxlevel") == 1) {
            if (argc != 4) {
                cerr << "Error:\tInvalid extra arguments for info:\t" << (4 - argc) << "\n";
                exit(-1);
            }

            // TODO: Check if arguments are strings before converting to an int (not sure how)
            if (atoi(argv[3]) < 0 || atoi(argv[3]) > 65535) {
                cerr << "Invalid maxlevel: " << argv[3] << "\n";
            }


        } else if (strcmp(argv[2], "resize") == 1) {
            if (argc != 5) {
                cerr << "Error:\tInvalid extra arguments for info:\t" << (5 - argc) << "\n";
                exit(-1);
            }

            if (atoi(argv[3]) < 0) {
                cerr << "Invalid resize width: " << argv[3] << "\n";
            }

            if (atoi(argv[4]) < 0) {
                cerr << "Invalid resize height: " << argv[4] << "\n";
            }

        } else if (strcmp(argv[2], "cutfreq") == 1) {
            if (argc != 4) {
                cerr << "Error:\tInvalid extra arguments for info:\t" << (4 - argc) << "\n";
                exit(-1);
            }

            if (atoi(argv[3]) < 0) {
                cerr << "Invalid cutfreq: " << argv[3] << "\n";
            }
        } else if (strcmp(argv[2], "compress") == 1) {
            if (argc != 3) {
                cerr << "Error:\tInvalid extra arguments for info:\t" << (3 - argc) << "\n";
                exit(-1);
            }
        } else {
            cerr << "Error:\tInvalid option:\t" << argv[2] << "\n";
            exit(-1);
        }
    }
}