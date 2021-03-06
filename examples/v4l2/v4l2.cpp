/**
 * Copyright (C) 2020, Val Doroshchuk <valbok@gmail.com>
 */

#include <Capture/v4l2.h>
#include <iostream>

int main(int argc, char **argv)
{
    Capture::v4l2 cap("/dev/video0");
    if (!cap.start(1920, 1080)) {
        std::cerr << "Could not start capturing." << std::endl;
        return 1;
    }

    int frame_count = argc > 1 ? strtol(argv[1], NULL, 0) : 10;
    char filename[15];
    for (int i = 0; i < frame_count; ++i) {
        auto frame = cap.read_frame();
        if (!frame) {
            std::cerr << "Could not read frame." << std::endl;
            continue;
        }

        sprintf(filename, "frame-%d.jpg", i);
        fprintf(stdout, "Writing %s\n", filename);
        FILE *fp = fopen(filename, "wb");
        fwrite(frame.data(), frame.size(), 1, fp);
        fclose(fp);
    }

    return 0;
}