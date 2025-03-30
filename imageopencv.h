#ifndef IMAGEOPENCV_H
#define IMAGEOPENCV_H

#include <opencv2/opencv.hpp>

class ImageOpenCV {
public:
    explicit ImageOpenCV(const std::string& imagePath);

    void convertColorSpaces();
    void applyGaussianBlur();
    void detectCircles();
    void detectLines();
    void drawCircles();
    void drawLines();
    void showImages();

private:
    cv::Mat image, hsv, lab, yuv, xyz, gray, gaus;
    cv::Mat imageCircles, imageLines;
    std::vector<cv::Vec3f> circles;
    std::vector<cv::Vec2f> lines;
};

#endif  // IMAGEOPENCV_H
