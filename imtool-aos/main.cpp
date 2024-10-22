#include <iostream>
#include <cstring>
using namespace std;

#include "../common/progargs.hpp"
#include "../common/intensityscaling.hpp"
#include "../imgaos/imageaos.hpp"

int main(int argc, char *argv[]) {
    if (argc < 4) {
        cerr << "Error:\tInvalid number of arguments:\t" << argc << "\n";
        exit(-1);
    } else {
        // Has the correct number of default arguments
        prog_paths(argv[1], argv[2]);
        if(strcmp(argv[3], "info") == 0)
        {
            prog_info(argc);
            displayInfo();
        } else if (strcmp(argv[3], "maxlevel") == 0) {
            prog_maxlevel(argc, argv);
            read_image_intensity_scaling(atoi(argv[4]));
        } else if (strcmp(argv[3], "resize") == 0) {
            prog_resize(argc, argv);
            aos_resize();
        } else if (strcmp(argv[3], "cutfreq") == 0) {
            prog_cutfreq(argc, argv);
            aos_cutfreq();
        } else if (strcmp(argv[3], "compress") == 0) {
            prog_compress(argc);
            aos_compress();
        } else {
            cerr << "Error:\tInvalid option:\t" << argv[3] << "\n";
            exit(-1);
        }
    }
}