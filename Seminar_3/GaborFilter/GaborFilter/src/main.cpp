#include <Filter/GaborFilter.hpp>
#include <Image/Convolution.hpp>
#include <Image/Image.hpp>
#include <Utility/Stopwatch.hpp>

#include <opencv2/core/mat.hpp>
#include <opencv2/core/hal/interface.h>

#include <cstdio>
#include <cstdint>
#include <string>

#define EXTRA_SMALL         "assets/xs_3x3.png"
#define SMALL               "assets/s_128x256.png"
#define MEDIUM              "assets/m_1920x1080.png"
#define LARGE               "assets/l_2400x1583.png"
#define EXTRA_LARGE         "assets/xl_10315x7049.jpg"

#define PATH_TO_IMAGE       (MEDIUM)

void SavePng(const cv::Mat &image, const std::string &fileName) {
    Image result(image);
    result.WriteToFile(fileName);
}

int32_t main() {
    Stopwatch stopwatch;
    Image image(PATH_TO_IMAGE, cv::IMREAD_GRAYSCALE);
    image.FormatItself(CV_32F);

    GaborFilter filter(3, 3);
    filter.RefreshKernel();

    // Sequential
    stopwatch.Start();
    const auto convResultSequential = convolution::Sequential(image.GetData(),
                                                              filter.kernel);
    stopwatch.Pause();

    SavePng(convResultSequential, "resultSequential.png");
    printf("Sequential:\t%lld ms\n", stopwatch.ElapsedMiliseconds());
    // !Sequential

    // Parallel
    stopwatch.Restart();
    const auto convResultParallel = convolution::Parallel(image.GetData(),
                                                          filter.kernel);
    stopwatch.Pause();

    SavePng(convResultParallel, "resultParallel.png");
    printf("Parallel:\t%lld ms\n", stopwatch.ElapsedMiliseconds());
    // !Parallel

    // CUDA
    stopwatch.Restart();
    const auto convResultCuda = convolution::Cuda(image.GetData(),
                                                  filter.kernel);
    stopwatch.Pause();

    SavePng(convResultCuda, "resultCUDA.png");
    printf("CUDA:\t\t%lld ms\n", stopwatch.ElapsedMiliseconds());
    // !CUDA

    return EXIT_SUCCESS;
}
