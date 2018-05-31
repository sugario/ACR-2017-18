#include "Image/Convolution.hpp"

cv::Mat Convolution::Sequential(const cv::Mat& image, const cv::Mat& kernel) {
    auto output = image.clone();

    const auto kernelCenterRow = (kernel.rows - 1) / 2;
    const auto kernelCenterColumn = (kernel.cols - 1) / 2;

    for (auto imageRow = kernelCenterRow; imageRow < image.rows - kernelCenterRow; imageRow++) {
        for (auto imageColumn = kernelCenterColumn; imageColumn < image.cols - kernelCenterColumn; imageColumn++) {
            auto sum = 0.0F;
            for (auto kernelRow = -kernelCenterRow; kernelRow <= kernelCenterRow; kernelRow++) {
                for (auto kernelColumn = -kernelCenterColumn; kernelColumn <= kernelCenterColumn; kernelColumn++) {
                    sum += kernel.at<float>(kernelRow + kernelCenterRow, kernelColumn + kernelCenterColumn) *
                           image.at<float>(imageRow + kernelRow, imageColumn + kernelColumn);
                }
            }
            output.at<float>(imageRow, imageColumn) = sum;
        }
    }

    return output;
}
