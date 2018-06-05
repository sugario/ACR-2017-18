#include "Image/Convolution.hpp"

#include <opencv2/core.hpp>

#include <algorithm>
#include <future>
#include <vector>

cv::Mat Convolution::Sequential(const cv::Mat& image, const cv::Mat& kernel, struct Thread thread) {
    auto output = image.clone();
    if (thread.step == NO_THREAD_STEP) {
        thread.step = image.rows;
    }

    const auto kernelCenterRow = (kernel.rows - 1) / 2;
    const auto kernelCenterColumn = (kernel.cols - 1) / 2;

    for (auto imageRow = thread.id * thread.step; imageRow < (thread.id + 1) * thread.step; imageRow++) {
        for (auto imageColumn = 0; imageColumn < image.cols; imageColumn++) {
            auto sum = 0.0F;
            for (auto kernelRow = -kernelCenterRow; kernelRow <= kernelCenterRow; kernelRow++) {
                for (auto kernelColumn = -kernelCenterColumn; kernelColumn <= kernelCenterColumn; kernelColumn++) {
                    if (imageRow + kernelRow <= 0 ||
                        imageRow + kernelRow >= image.rows ||
                        imageColumn + kernelColumn <= 0 ||
                        imageColumn + kernelColumn >= image.cols) {
                        continue;
                    }

                    sum += kernel.at<float>(kernelRow + kernelCenterRow, kernelColumn + kernelCenterColumn) *
                           image.at<float>(imageRow + kernelRow, imageColumn + kernelColumn);
                }
            }

            output.at<float>(imageRow, imageColumn) = sum;
        }
    }

    return output.rowRange(thread.id * thread.step, (thread.id + 1) * thread.step);
}

cv::Mat Convolution::Parallel(const cv::Mat& image, const cv::Mat& kernel) {
    const auto numberOfThreads = std::max(cv::getNumThreads(), cv::getNumberOfCPUs());
    const auto splitRowCount = image.rows / (numberOfThreads - 1);
    cv::Mat output;

    std::vector<std::future<cv::Mat>> threads;
    for (auto i = 0; i < numberOfThreads - 1; i++) {
        const struct Thread thread = { i, splitRowCount };
        threads.emplace_back(std::async(Sequential, image, kernel, thread));
    }

    for (auto &thread : threads) {
        const auto processedImagePart = thread.get();
        output.push_back(processedImagePart);
    }

    return output;
}
