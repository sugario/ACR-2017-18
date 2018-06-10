#ifndef FILTER_FILTER_HPP
#define FILTER_FILTER_HPP

#include <Filter/FilterProperties.hpp>

#include <opencv2/core/mat.hpp>
#include <opencv2/core/types.hpp>

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

    void AdjustWithBandwith(double bandwith) noexcept;

    void RefreshKernel();

    cv::Mat kernel;

private:
    cv::Mat GetGaborKernel(const cv::Size &size,
                           double sigma,
                           double theta,
                           double lambda,
                           double gamma,
                           double psi) const;

    cv::Size m_Size;
    FilterProperties m_Properties;
};

#endif  // !FILTER_FILTER_HPP
