#include "Image/Convolution.hpp"

#include <opencv2/core/mat.hpp>
#include <opencv2/core/utility.hpp>

#include <algorithm>
#include <future>
#include <vector>

#define NO_THREAD            0
#define NO_THREAD_STEP      -1

struct Thread {
    int32_t id;
    int32_t step;
};

cv::Mat Convolve(const cv::Mat& image, const cv::Mat& kernel, struct Thread thread) {
    auto output = image.clone();
    if (thread.step == NO_THREAD_STEP) {
        thread.step = image.rows;
    }

    const auto kernelCenterRow = (kernel.rows - 1) / 2;
    const auto kernelCenterColumn = (kernel.cols - 1) / 2;

    for (auto imageRow = thread.id * thread.step; imageRow < (thread.id + 1) * thread.step; imageRow++) {
        if (imageRow >= image.rows) {
            break;
        }

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

    if ((thread.id + 1) * thread.step > image.rows) {
        return output.rowRange(thread.id * thread.step, image.rows);
    }

    return output.rowRange(thread.id * thread.step, (thread.id + 1) * thread.step);
}

cv::Mat Convolution::Sequential(const cv::Mat& image, const cv::Mat& kernel) {
    return Convolve(image, kernel, { NO_THREAD, NO_THREAD_STEP });
}

cv::Mat Convolution::Parallel(const cv::Mat& image, const cv::Mat& kernel) {
    cv::Mat output;
    const auto numberOfThreads = std::max(cv::getNumThreads(), cv::getNumberOfCPUs()) - 1;
    const auto splitRowCount = static_cast<int>
        (std::ceil(static_cast<double>(image.rows) / numberOfThreads));

    std::vector<std::future<cv::Mat>> threads;
    for (auto i = 0; i < numberOfThreads; i++) {
        const struct Thread thread = { i, splitRowCount };
        threads.emplace_back(std::async(Convolve, image, kernel, thread));
    }

    for (auto &thread : threads) {
        const auto processedImagePart = thread.get();
        output.push_back(processedImagePart);
    }

    return output;
}
