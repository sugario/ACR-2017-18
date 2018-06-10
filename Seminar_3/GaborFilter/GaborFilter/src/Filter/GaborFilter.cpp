#include "Filter/GaborFilter.hpp"

#include <opencv2/core/hal/interface.h>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/core/types.hpp>

#include <cmath>

#define DEFAULT_KERNEL_SIZE     3U
#define PI                      3.1415926535897932384626433832795

GaborFilter::GaborFilter() {
    this->m_Size.height = DEFAULT_KERNEL_SIZE;
    this->m_Size.width = DEFAULT_KERNEL_SIZE;

    RefreshKernel();
}

GaborFilter::GaborFilter(const cv::Size &size) {
    this->m_Size = size;

    RefreshKernel();
}

GaborFilter::GaborFilter(const int32_t kernelRowsSize,
                         const int32_t kernelColumnsSize) {
    this->m_Size.height = kernelRowsSize;
    this->m_Size.width = kernelColumnsSize;

    RefreshKernel();
}

void GaborFilter::SetDeviation(const double deviation) noexcept {
    this->m_Properties.deviation = deviation;
}

void GaborFilter::SetOrientation(const double orientation) noexcept {
    this->m_Properties.deviation = orientation;
}

void GaborFilter::SetWaveLength(const double wavelength) noexcept {
    this->m_Properties.deviation = wavelength;
}

void GaborFilter::SetSpatialAspectRatio(const double ratio) noexcept {
    this->m_Properties.deviation = ratio;
}

void GaborFilter::SetPhaseOffset(const double offset) noexcept {
    this->m_Properties.deviation = offset;
}

void GaborFilter::AdjustWithBandwith(const double bandwith) noexcept {
    this->m_Properties.deviation = this->m_Properties.wavelength;
    this->m_Properties.deviation /= PI;
    this->m_Properties.deviation *= std::sqrt(std::log(2.0) / 2);
    this->m_Properties.deviation *= std::pow(2, bandwith) + 1;
    this->m_Properties.deviation /= std::pow(2, bandwith) - 1;
}

void GaborFilter::RefreshKernel() {
    this->kernel = GetGaborKernel(this->m_Size,
                                  this->m_Properties.deviation,
                                  this->m_Properties.orientation,
                                  this->m_Properties.wavelength,
                                  this->m_Properties.ratio,
                                  this->m_Properties.offset);
}

cv::Mat GaborFilter::GetGaborKernel(const cv::Size &size,
                                    const double sigma,
                                    const double theta,
                                    const double lambda,
                                    const double gamma,
                                    const double psi) const {
    if (size.empty()) {
        return cv::Mat(1, 1, CV_32F, cv::Scalar(1, 0, 0));
    }

    assert(sigma != 0.0);
    assert(lambda != 0.0);
    assert(gamma != 0.0);

    const auto rowMax = size.height / 2;
    const auto columnMax = size.width / 2;

    const auto rowMin = -rowMax;
    const auto columnMin = -columnMax;

    const auto sigmaRow = -0.5 / std::pow(sigma / gamma, 2);
    const auto sigmaColumn = -0.5 / std::pow(sigma, 2);
    cv::Mat kernel(rowMax - rowMin + 1, columnMax - columnMin + 1, CV_32F);

    for (auto row = rowMin; row <= rowMax; row++) {
        for (auto column = columnMin; column <= columnMax; column++) {
            const auto thetaRow = -column * sin(theta) + row * cos(theta);
            const auto thetaColumn = column * cos(theta) + row * sin(theta);

            const auto gabor = std::exp(sigmaColumn * thetaColumn * thetaColumn + sigmaRow * thetaRow * thetaRow) *
                               std::cos(2 * PI * thetaColumn / lambda + psi);
            kernel.at<float>(rowMax - row, columnMax - column) = static_cast<float>(gabor);
        }
    }

    return kernel;
}
