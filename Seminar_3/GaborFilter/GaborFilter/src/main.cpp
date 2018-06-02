#include <Image/Convolution.hpp>
#include <Image/Convolution_CUDA.cuh>
#include <Image/Image.hpp>
#include <Filter/GaborFilter.hpp>

#include <cstdint>
#include <cstdlib>

#define RAINBOW             "assets/rainbow.png"
#define CHART               "assets/chart.jpg"
#define SYNTHETIC           "assets/synthetic1.png"

#define RESULT_FILE_NAME    "result.png"

#define PATH_TO_IMAGE       (RAINBOW)

int32_t main() {
    Image image(PATH_TO_IMAGE, cv::IMREAD_GRAYSCALE);
    image.FormatItself(CV_32F);

    GaborFilter filter(3, 3);
    filter.RefreshKernel();

    // Sequential
    const auto convResultSequential = Convolution::Sequential(image.GetData(),
                                                              filter.kernel);
    Image resultSequential(convResultSequential);
    resultSequential.FormatItself(CV_8U, 1.0 / 255.0);
    resultSequential.WriteToFile("resultSequential.png");
    // !Sequential

    // Parallel
    const auto convResultParallel = Convolution::Parallel(image.GetData(),
                                                          filter.kernel);
    Image resultParallel(convResultParallel);
    resultParallel.FormatItself(CV_8U, 1.0 / 255.0);
    resultParallel.WriteToFile("resultParallel.png");
    // !Parallel

    // CUDA
    const auto convResultCUDA = Convolution::CUDA(image.GetData(),
                                                  filter.kernel);
    Image resultCUDA(convResultCUDA);
    resultCUDA.FormatItself(CV_8U, 1.0 / 255.0);
    resultCUDA.WriteToFile("resultCUDA.png");
    // !CUDA

    return EXIT_SUCCESS;
}
