#ifndef IMAGE_CONVOLUTION_HPP
#define IMAGE_CONVOLUTION_HPP

#include <opencv2/core/mat.hpp>

#define NO_THREAD        0
#define NO_THREAD_STEP  -1

struct Thread {
    int32_t id;
    int32_t step;
};

namespace Convolution {
    cv::Mat Sequential(const cv::Mat &image,
                       const cv::Mat &kernel,
                       struct Thread thread = { NO_THREAD, NO_THREAD_STEP });
    cv::Mat Parallel(const cv::Mat &image, const cv::Mat &kernel);
}

#endif  // !IMAGE_CONVOLUTION_HPP
