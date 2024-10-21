#include <iostream>
#include <cstring>
using namespace std;

#include "../common/binaryio.hpp"
#include "../common/progargs.hpp"
#include "../common/utility.hpp"

int main(int argc, char *argv[]) {
    if (argc < 4) {
        cerr << "Error:\tInvalid number of arguments:\t" << argc << "\n";
        exit(-1);
    } else {
        // Has the correct number of default arguments
        progPaths(argv[1], argv[2]);
        if(strcmp(argv[3], "info") == 0)
        {
            info(argc);
        } else if (strcmp(argv[3], "maxlevel") == 0) {
            maxLevel(argc, argv);
        } else if (strcmp(argv[3], "resize") == 0) {
            resize(argc, argv); //function in progargs
        } else if (strcmp(argv[3], "cutfreq") == 0) {
            cutfreq(argc, argv);
        } else if (strcmp(argv[3], "compress") == 0) {
            compress(argc);
        } else {
            cerr << "Error:\tInvalid option:\t" << argv[3] << "\n";
            exit(-1);
        }
    }
}