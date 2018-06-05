#ifndef FILTER_FILTER_HPP
#define FILTER_FILTER_HPP

#include <Filter/FilterProperties.hpp>

#include <opencv2/core/mat.hpp>

#include <cstdint>

struct GaborFilter {
    GaborFilter();
    GaborFilter(int32_t kernelRowsSize, int32_t kernelColumnsSize);
    explicit GaborFilter(const cv::Size &size);

    void SetDeviation(double deviation) noexcept;
    void SetOrientation(double orientation) noexcept;
    void SetWaveLength(double wavelength) noexcept;
    void SetSpatialAspectRatio(double ratio) noexcept;
    void SetPhaseOffset(double offset) noexcept;

    void RefreshKernel();

    cv::Mat kernel;

private:
    cv::Size m_Size;
    FilterProperties m_Properties;
};

#endif  // !FILTER_FILTER_HPP