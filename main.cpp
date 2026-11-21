#include "tit.hpp"
#include <opencv2/opencv.hpp>
#include <iostream>
#include <chrono>
#include <cstring>

using namespace std::chrono;

auto main([[maybe_unused]]int argc, [[maybe_unused]]char **argv) -> int
{
    cv::VideoCapture cap;
    cap.set(cv::CAP_PROP_FRAME_WIDTH, 320);
    cap.set(cv::CAP_PROP_FRAME_HEIGHT, 240);
    cap.open(0);

    if (!cap.isOpened())
    {
        std::cerr << "Failed to open video feed" << std::endl;
        return -1;
    }

    const cv::Rect roi{108, 48, 82, 81};
    titd tit{10.0f, 0.01f, roi};
    cv::Mat frame;
    auto prev_point = steady_clock::now();

    unsigned int image_idx = 0;
    char filename[128] = {};

    while (true)
    {
        cap >> frame; 

        if (tit.feed(frame))
        {
            auto now = steady_clock::now();
            if (now - prev_point >= duration<float>(1.0f))
            {
                std::cout << "Movement!" << std::endl;
                std::snprintf(filename, 128, "/userdata/images/frame%d.png", image_idx++);
                cv::imwrite(filename, frame);
                prev_point = now;
            }
        }
    }

    return 0;
}
