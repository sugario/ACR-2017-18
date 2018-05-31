#include "Filter/GaborFilter.hpp"

#include <opencv2/core/mat.hpp>
#include <opencv2/imgproc/imgproc.hpp>

#define DEFAULT_KERNEL_SIZE 3U

GaborFilter::GaborFilter() {
    this->m_Size.height = DEFAULT_KERNEL_SIZE;
    this->m_Size.width = DEFAULT_KERNEL_SIZE;

    RefreshKernel();
}

GaborFilter::GaborFilter(const cv::Size &size) {
    this->m_Size = size;

    RefreshKernel();
}

GaborFilter::GaborFilter(const int32_t kernelRowsSize, const int32_t kernelColumnsSize) {
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

void GaborFilter::RefreshKernel() {
    this->kernel = cv::getGaborKernel(this->m_Size,
                                      this->m_Properties.deviation,
                                      this->m_Properties.orientation,
                                      this->m_Properties.wavelength,
                                      this->m_Properties.ratio,
                                      this->m_Properties.offset,
                                      CV_32F);
}
