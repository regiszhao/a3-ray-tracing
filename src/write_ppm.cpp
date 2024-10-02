#include "write_ppm.h"
#include <fstream>
#include <cassert>
#include <iostream>

bool write_ppm(
  const std::string & filename,
  const std::vector<unsigned char> & data,
  const int width,
  const int height,
  const int num_channels)
{
  ////////////////////////////////////////////////////////////////////////////
    assert(
        (num_channels == 3 || num_channels == 1) &&
        ".ppm only supports RGB or grayscale images");

    ////////////////////////////////////////////////////////////////////////////

    try {

        // create and open file
        std::ofstream ImageFile;
        ImageFile.open(filename);

        // header information
        if (num_channels == 3) {
            ImageFile << "P3\n";
        }
        else {
            ImageFile << "P2\n";
        }
        ImageFile << width << " " << height << "\n255\n";

        // pixel information
        for (int row = 0; row < height; row++) {
            for (int col = 0; col < width; col++) {
                int which_pixel = row * width + col;
                // rgb
                if (num_channels == 3) {
                    int r = static_cast<int>(data[which_pixel * 3]);
                    int g = static_cast<int>(data[which_pixel * 3 + 1]);
                    int b = static_cast<int>(data[which_pixel * 3 + 2]);
                    ImageFile << r << " " << g << " " << b << "\n";
                }
                // grayscale
                else {
                    int gray_val = static_cast<int>(data[which_pixel]);
                    ImageFile << gray_val << "\n";
                }
            }
        }

        // close file
        ImageFile.close();

        return true;
    }

    catch (const std::exception& e) {
        std::cerr << e.what() << '\n';
        return false;
    }

  ////////////////////////////////////////////////////////////////////////////
}
