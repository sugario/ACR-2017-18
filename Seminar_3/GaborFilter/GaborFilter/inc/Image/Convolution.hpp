#ifndef IMAGE_CONVOLUTION_HPP
#define IMAGE_CONVOLUTION_HPP

#include <opencv2/core/mat.hpp>

class Convolution {
public:
    static cv::Mat Sequential(const cv::Mat &image, const cv::Mat &kernel);
    // static cv::Mat Parallel(const cv::Mat &image, const cv::Mat &kernel);
    // static cv::Mat CUDA(const cv::Mat &image, const cv::Mat &kernel);
};

#endif  // !IMAGE_CONVOLUTION_HPP
