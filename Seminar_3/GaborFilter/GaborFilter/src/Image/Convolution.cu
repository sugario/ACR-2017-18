#include "Image/Convolution.hpp"

#ifdef __CUDACC__
#include <cuda.h>
#include <cuda_runtime.h>
#include <device_launch_parameters.h>

#include <opencv2/core/cuda.hpp>
#include <opencv2/core/cuda_types.hpp>
#endif

#include <opencv2/core/mat.hpp>
#include <opencv2/core/types.hpp>

#include <cstdint>
#include <cstdio>

#ifdef __CUDACC__

#define BLOCK_SIZE      16
#define GPU_ERROR_CHECK(ans) { GpuAssert((ans), __FILE__, __LINE__); }

inline void GpuAssert(const cudaError_t code,
                      const char *file,
                      const int32_t line) {
    if (code == cudaSuccess) {
        return;
    }

    fprintf(stderr,
            "GpuAssert: %s %s %d\n",
            cudaGetErrorString(code),
            file,
            line);

    exit(code);
}

__global__
void CudaConvolve(cv::cuda::PtrStepSz<float> image,
                  cv::cuda::PtrStepSz<float> output,
                  cv::cuda::PtrStepSz<float> kernel) {
    const auto pixelRow = threadIdx.y + blockIdx.y * blockDim.y;
    const auto pixelColumn = threadIdx.x + blockIdx.x * blockDim.x;

    if (pixelRow >= image.rows || pixelColumn >= image.cols) {
        return;
    }

    const auto kernelCenterRow = (kernel.rows - 1) / 2;
    const auto kernelCenterColumn = (kernel.cols - 1) / 2;

    auto sum = 0.0F;
    for (auto kernelRow = -kernelCenterRow; kernelRow <= kernelCenterRow; kernelRow++) {
        for (auto kernelColumn = -kernelCenterColumn; kernelColumn <= kernelCenterColumn; kernelColumn++) {
            if (pixelRow + kernelRow <= 0 ||
                pixelRow + kernelRow >= image.rows ||
                pixelColumn + kernelColumn <= 0 ||
                pixelColumn + kernelColumn >= image.cols) {
                continue;
            }

            sum += kernel.ptr(kernelRow + kernelCenterRow)[kernelColumn + kernelCenterColumn] *
                   image.ptr(pixelRow + kernelRow)[pixelColumn + kernelColumn];
        }

    }

    output.ptr(pixelRow)[pixelColumn] = sum;
}

cv::Mat Convolution::Cuda(const cv::Mat &image, const cv::Mat &kernel) {
    auto output = image.clone();

    cv::cuda::GpuMat image_d(image);
    cv::cuda::GpuMat kernel_d(kernel);
    cv::cuda::GpuMat output_d(output);

    dim3 threadsPerBlock(BLOCK_SIZE, BLOCK_SIZE);
    dim3 numBlocks(ceil((float)image.cols / threadsPerBlock.x), ceil((float)image.rows / threadsPerBlock.y));

    CudaConvolve<<<numBlocks, threadsPerBlock>>>(image_d, output_d, kernel_d);
    GPU_ERROR_CHECK(cudaPeekAtLastError());
    GPU_ERROR_CHECK(cudaDeviceSynchronize());

    output_d.download(output);

    image_d.release();
    kernel_d.release();
    output_d.release();

    return output;
}

#else
#pragma message ("CUDA-NOT-SUPPORTED!")
cv::Mat Convolution::Cuda(const cv::Mat &image, const cv::Mat &kernel) {
    return cv::Mat(image.rows, image.cols, CV_32F, cv::Scalar(0, 0, 0));
}
#endif
