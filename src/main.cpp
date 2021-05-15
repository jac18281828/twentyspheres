#include <iostream>
#include <vector>
#include <chrono>
#include <thread>

#include "image.h"

using namespace std::literals::chrono_literals;

int main(int argc, char* argv[]) {

    if(argc < 1) {
        std::cerr << "filename expected." << std::endl;
        return 1;
    } else {

        const int height = 400;
        const int width  = 400;

        const int depth = 3;
        const char color = 255;

        std::vector<char> buffer;
        const auto buffer_size = height*width*depth;
        buffer.reserve(buffer_size);

        for (int j=0; j<height; ++j) {
            for (int i=0; i<width*depth; ++i) {
                const auto offset = i + j*width*depth;
                if (j < height/4 && i < width*depth/4) {
                    buffer[offset] = color;
                } else {
                    buffer[offset] = 0;
                }
            }
        } 

        auto jpeg = image::jpegfile(argv[1]);

        jpeg.write(buffer, width, height);

    }

    std::cout << argv[1] << std::endl;

    std::this_thread::sleep_for(60s);

    return 0;

}
