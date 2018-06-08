#include <Image/Convolution.hpp>
#include <Image/Image.hpp>
#include <Filter/GaborFilter.hpp>
#include <Utility/Stopwatch.hpp>

#include <cstdint>
#include <cstdlib>

#define EXTRA_SMALL         "assets/xs_3x3.png"
#define SMALL               "assets/s_128x256.png"
#define MEDIUM              "assets/m_1920x1080.png"
#define LARGE               "assets/l_2400x1583.png"
#define EXTRA_LARGE         "assets/xl_10315x7049.jpg"

#define PATH_TO_IMAGE       (LARGE)

int32_t main() {
    Stopwatch stopwatch;
    Image image(PATH_TO_IMAGE, cv::IMREAD_GRAYSCALE);
    image.FormatItself(CV_32F);

    GaborFilter filter(3, 3);
    filter.RefreshKernel();

    // Sequential
    stopwatch.Start();

    const auto convResultSequential = Convolution::Sequential(image.GetData(),
                                                              filter.kernel);
    Image resultSequential(convResultSequential);
    resultSequential.FormatItself(CV_8U, 1.0 / 255.0);
    resultSequential.WriteToFile("resultSequential.png");

    stopwatch.Pause();
    printf("Sequential:\t%lld ms\n", stopwatch.ElapsedMiliseconds());
    // !Sequential

    // Parallel
    stopwatch.Restart();

    const auto convResultParallel = Convolution::Parallel(image.GetData(),
                                                          filter.kernel);
    Image resultParallel(convResultParallel);
    resultParallel.FormatItself(CV_8U, 1.0 / 255.0);
    resultParallel.WriteToFile("resultParallel.png");

    stopwatch.Pause();
    printf("Parallel:\t%lld ms\n", stopwatch.ElapsedMiliseconds());
    // !Parallel

    // CUDA
    stopwatch.Restart();

    const auto convResultCUDA = Convolution::Cuda(image.GetData(),
                                                  filter.kernel);
    Image resultCUDA(convResultCUDA);
    resultCUDA.FormatItself(CV_8U, 1.0 / 255.0);
    resultCUDA.WriteToFile("resultCUDA.png");

    stopwatch.Pause();
    printf("CUDA:\t\t%lld ms\n", stopwatch.ElapsedMiliseconds());
    // !CUDA

    return EXIT_SUCCESS;
}
