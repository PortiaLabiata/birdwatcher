#include "tit.hpp"
#include <opencv2/opencv.hpp>
#include <iostream>
#include <chrono>

using namespace std::chrono;

auto main([[maybe_unused]]int argc, [[maybe_unused]]char **argv) -> int
{
    auto cap = cv::VideoCapture{0};
    if (!cap.isOpened())
    {
        std::cerr << "Failed to open video feed" << std::endl;
        return -1;
    }

    titd tit{10.0f, 0.15f, cv::Rect{150, 100, 200, 200}};
    cv::Mat frame;
    auto prev_point = steady_clock::now();

    while (true)
    {
        if (!cap.read(frame))
        {
            std::cerr << "Failed to read frame" << std::endl;
            break;
        }

        if (tit.feed(frame))
        {
            auto now = steady_clock::now();
            if (now - prev_point >= duration<float>(1.0f))
            {
                std::cout << "Movement!" << std::endl;
                prev_point = now;
            }
        }
    }

    return 0;
}
