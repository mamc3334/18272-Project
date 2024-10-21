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
        progPaths(argv[1], argv[2]);
        if(argv[3] == "info")
        {
            info(argc);
        } else if (argv[3] == "maxlevel") {
            maxLevel(argc, argv);
        } else if (argv[3] == "resize") {
            resize(argc, argv); //function in progargs
        } else if (argv[3] == "cutfreq") {
            cutfreq(argc, argv);
        } else if (argv[3] == "compress") {
            compress(argc);
        } else {
            cerr << "Error:\tInvalid option:\t" << argv[3] << "\n";
            exit(-1);
        }
    }
}