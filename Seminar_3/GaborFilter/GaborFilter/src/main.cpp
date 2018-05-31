#include <Image/Convolution.hpp>
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

    const auto convResult = Convolution::Sequential(image.GetData(),
                                                    filter.kernel);
    Image result(convResult);
    result.FormatItself(CV_8U, 1.0 / 255.0);
    result.WriteToFile(RESULT_FILE_NAME);

    return EXIT_SUCCESS;
}
