#ifndef IMAGE_IMAGE_HPP
#define IMAGE_IMAGE_HPP

#include <opencv2/core/mat.hpp>
#include <opencv2/imgcodecs.hpp>

#include <cstdint>
#include <string>

struct Image {
    explicit Image(const cv::Mat &data);
    explicit Image(const std::string &fileName);
    Image(const std::string &fileName, int32_t mode);

    void ReadFromFile(const std::string &fileName,
                      int32_t mode = cv::IMREAD_COLOR);
    void WriteToFile(const std::string &fileName) const;

    cv::Mat Format(int32_t format, double scaleFactor = 1.0) const;
    void FormatItself(int32_t format, double scaleFactor = 1.0);

    cv::Mat GetData() const;
    void SetData(const cv::Mat &data);

private:
    cv::Mat m_ImageData;
};

#endif  // !IMAGE_IMAGE_HPP
