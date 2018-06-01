#include "Image/Convolution.hpp"

#include <opencv2/core.hpp>

#include <algorithm>
#include <future>
#include <vector>

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

cv::Mat Convolution::Parallel(const cv::Mat& image, const cv::Mat& kernel) {
    const auto numberOfThreads = std::max(cv::getNumThreads(), cv::getNumberOfCPUs());
    const auto splitRowCount = image.rows / (numberOfThreads - 1);
    cv::Mat output;

    if (numberOfThreads == 1) {
        return Sequential(image, kernel);
    }

    std::vector<std::future<cv::Mat>> threads;
    for (auto i = 1; i < numberOfThreads; i++) {
        const auto startRow = splitRowCount * (i - 1);
        auto endRow = splitRowCount * i;

        if (i == numberOfThreads - 1) {
            endRow = image.rows;
        }

        auto imagePart = image.rowRange(startRow, endRow);
        threads.emplace_back(std::async(Sequential, imagePart, kernel));
    }

    for (auto &thread : threads) {
        const auto processedImagePart = thread.get();
        output.push_back(processedImagePart);
    }

    return output;
}
