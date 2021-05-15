#pragma once

#include <cstdio>
#include <vector>
#include <exception>

#include <jpeglib.h>


namespace image {

    constexpr int JPEG_QUALITY = 88;

    class jpegfile {
    public:

        jpegfile(std::string const& filepath) {
            m_output = fopen(filepath.c_str(), "wb");
            if(!m_output) {
                throw std::runtime_error("Failed to open output");
            }
        }

        ~jpegfile() {
            fclose(m_output);
            m_output = nullptr;
        }


        void write(std::vector<char> const& buffer, const int width, const int height) {
            struct jpeg_compress_struct cinfo;
            struct jpeg_error_mgr       jerr;

            cinfo.err = jpeg_std_error(&jerr);
            jpeg_create_compress(&cinfo);
            jpeg_stdio_dest(&cinfo, m_output);
            cinfo.image_width = width;
            cinfo.image_height = height;
            cinfo.input_components = 3;
            cinfo.in_color_space = JCS_RGB;

            jpeg_set_defaults(&cinfo);
            jpeg_set_quality(&cinfo, JPEG_QUALITY, true);
            jpeg_start_compress(&cinfo, true);

            JSAMPROW row_pointer;

            while(cinfo.next_scanline < cinfo.image_height) {
                const auto scanline = cinfo.next_scanline*cinfo.input_components*cinfo.image_width;
                row_pointer = (JSAMPROW) &buffer[scanline];
                jpeg_write_scanlines(&cinfo, &row_pointer, 1);
            }

            jpeg_finish_compress(&cinfo);
        }


    private:
        FILE* m_output;

    };

}
