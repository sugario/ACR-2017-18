#ifndef IMAGE_CONVOLUTION_HPP
#define IMAGE_CONVOLUTION_HPP

#include <opencv2/core/mat.hpp>

namespace convolution {
    cv::Mat Sequential(const cv::Mat &image, const cv::Mat &kernel);
    cv::Mat Parallel(const cv::Mat &image, const cv::Mat &kernel);
    cv::Mat Cuda(const cv::Mat &image, const cv::Mat &kernel);
}

#endif  // !IMAGE_CONVOLUTION_HPP
