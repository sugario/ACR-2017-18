#ifndef IMAGE_CONVOLUTIONCUDA_HPP
#define IMAGE_CONVOLUTIONCUDA_HPP

#include <opencv2/core/mat.hpp>

namespace Convolution {
    cv::Mat CUDA(const cv::Mat &image, const cv::Mat &kernel);
}

#endif  // !IMAGE_CONVOLUTIONCUDA_HPP
