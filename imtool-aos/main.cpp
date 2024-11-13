#include <chrono>
#include <iostream>
#include <cstring>
#include <span>
#include <vector>
using namespace std;

#include "../common/progargs.hpp"
#include "../common/intensityscaling.hpp"
#include "../imgaos/imageaos.hpp"

int main(int argc, char *argv[]) {
    auto start = std::chrono::high_resolution_clock::now();
    if (argc < 4) {
      cerr << "Error:\tInvalid number of arguments:\t" << argc << "\n";
      exit(-1);
    } else {
      // Has the correct number of default arguments
      span const args_view{ argv, static_cast<std::size_t>(argc) };
      vector<string> const args{args_view.begin() + 1, args_view.end()};
      prog_paths(args[0], args[1]);
      if(args[2] == "info")
      {
          prog_info(argc);
          displayInfo();
      } else if (args[2] == "maxlevel") {
          prog_maxlevel(argc, args);
          read_image_intensity_scaling(stoi(args[3]));
      } else if (args[2] == "resize") {
          prog_resize(argc, args);
          Image_Attributes newImageData = {.magic_word = "",.width=static_cast<unsigned int>(stoi(args[3])), .height=static_cast<unsigned int>(stoi(args[4])), .intensity=0};
          aos_resize(newImageData);
      } else if (args[2] == "cutfreq") {
          prog_cutfreq(argc, args);
          aos_cutfreq(stoi(args[3]));
      } else if (args[2] == "compress") {
          prog_compress(argc);
          aos_compress();
      } else {
          cerr << "Error:\tInvalid option:\t" << args[2] << "\n";
          exit(-1);
      }
        auto end = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
        std::cout << "Time of execution: " << duration.count() << " microseconds" << "\n";
    }
}