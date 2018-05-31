#include "Image/Image.hpp"

#include <string>

Image::Image(const cv::Mat& data) {
    this->m_ImageData = data;
}

Image::Image(const std::string& fileName) {
    this->m_ImageData = cv::imread(fileName);
}

Image::Image(const std::string& fileName, const int32_t mode) {
    this->m_ImageData = cv::imread(fileName, mode);
}

void Image::ReadFromFile(const std::string& fileName, const int32_t mode) {
    this->m_ImageData = cv::imread(fileName, mode);
}

void Image::WriteToFile(const std::string& fileName) const {
    cv::imwrite(fileName, this->m_ImageData);
}

cv::Mat Image::Format(const int32_t format, const double scaleFactor) const {
    cv::Mat formattedImage;
    this->m_ImageData.convertTo(formattedImage, format, scaleFactor);

    return formattedImage;
}

void Image::FormatItself(const int32_t format, const double scaleFactor) {
    cv::Mat formattedImage;
    this->m_ImageData.convertTo(formattedImage, format, scaleFactor);
    this->m_ImageData = formattedImage;
}

cv::Mat Image::GetData() const {
    return this->m_ImageData;
}

void Image::SetData(const cv::Mat &data) {
    this->m_ImageData = data;
}
