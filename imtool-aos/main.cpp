#include <iostream>
#include <string.h>
#include "../imgaos/imageaos.hpp"
using namespace std;

int main(int argc, char *argv[]) {
    int program_args = argc - 1;
    if (program_args < 3) {
        cerr << "Error:\tInvalid number of arguments:\t" << program_args << "\n";
        exit(-1);
    } else {
        string input_filename = argv[1];
        string output_filename = argv[2];
        // Has the correct number of default arguments
        if(strcmp(argv[3], "info") == 0) {
            if (program_args != 3) {
                cerr << "Error:\tInvalid extra arguments for info:\t" << (3 - program_args) << "\n";
                exit(-1);
            }

            vector<string> img_metadata = get_image_metadata(input_filename);
            cout <<
                "Input:\t\t" << input_filename << "\n" <<
                "Output:\t\t" << output_filename << "\n" <<
                "Operation:\t" << argv[3] << "\n" <<
                "Image size:\t" << img_metadata[0] << "x" << img_metadata[1] << "\n" <<
                "Max level:\t" << img_metadata[2] << "\n";
        } else if (strcmp(argv[3], "maxlevel") == 0) {
            if (program_args != 4) {
                cerr << "Error:\tInvalid extra arguments for info:\t" << (4 - program_args) << "\n";
                exit(-1);
            }

            // TODO: Check if arguments are strings before converting to an int (not sure how)
            if (atoi(argv[4]) < 0 || atoi(argv[4]) > 65535) {
                cerr << "Invalid maxlevel: " << argv[4] << "\n";
            }


        } else if (strcmp(argv[3], "resize") == 0) {
            if (program_args != 5) {
                cerr << "Error:\tInvalid extra arguments for info:\t" << (5 - program_args) << "\n";
                exit(-1);
            }

            if (atoi(argv[4]) < 0) {
                cerr << "Invalid resize width: " << argv[4] << "\n";
            }

            if (atoi(argv[5]) < 0) {
                cerr << "Invalid resize height: " << argv[5] << "\n";
            }

        } else if (strcmp(argv[3], "cutfreq") == 0) {
            if (program_args != 4) {
                cerr << "Error:\tInvalid extra arguments for info:\t" << (4 - program_args) << "\n";
                exit(-1);
            }

            if (atoi(argv[4]) < 0) {
                cerr << "Invalid cutfreq: " << argv[4] << "\n";
            }
        } else if (strcmp(argv[3], "compress") == 0) {
            if (program_args != 3) {
                cerr << "Error:\tInvalid extra arguments for info:\t" << (3 - program_args) << "\n";
                exit(-1);
            }
        } else {
            cerr << "Error:\tInvalid option:\t" << argv[3] << "\n";
            exit(-1);
        }
    }
}