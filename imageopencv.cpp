#include "imageopencv.h"

ImageOpenCV::ImageOpenCV(const std::string& imagePath) {
    image = cv::imread(imagePath);
    if (image.empty()) {
        std::cout << "Ошибка: не удалось загрузить изображение. Проверьте путь "
                     "к файлу."
                  << std::endl;
        exit(-1);
    }
}

void ImageOpenCV::convertColorSpaces() {
    cv::cvtColor(image, hsv, cv::COLOR_BGR2HSV);
    cv::cvtColor(image, lab, cv::COLOR_BGR2Lab);
    cv::cvtColor(image, yuv, cv::COLOR_BGR2YUV);
    cv::cvtColor(image, xyz, cv::COLOR_BGR2XYZ);
    cv::cvtColor(image, gray, cv::COLOR_BGR2GRAY);
}

void ImageOpenCV::applyGaussianBlur() {
    cv::GaussianBlur(gray, gaus, cv::Size(9, 9), 2, 2);
}

void ImageOpenCV::detectCircles() {
    cv::HoughCircles(
        gaus, circles, cv::HOUGH_GRADIENT, 1, gaus.rows / 8, 50, 50, 20, 200);
}

void ImageOpenCV::detectLines() {
    cv::Mat edges;
    cv::Canny(gaus, edges, 50, 150, 3);
    cv::HoughLines(edges, lines, 1, CV_PI / 180, 80);
}

void ImageOpenCV::drawCircles() {
    imageCircles = image.clone();
    for (size_t i = 0; i < circles.size(); i++) {
        cv::Vec3i c = circles[i];
        cv::Point center(c[0], c[1]);
        int radius = c[2];
        cv::circle(
            imageCircles, center, 3, cv::Scalar(0, 255, 0), -1, cv::LINE_AA);
        cv::circle(
            imageCircles, center, radius, cv::Scalar(255, 0, 0), 2,
            cv::LINE_AA);
    }
}

void ImageOpenCV::drawLines() {
    imageLines = image.clone();
    for (size_t i = 0; i < lines.size(); i++) {
        float rho   = lines[i][0];
        float theta = lines[i][1];

        double a = cos(theta), b = sin(theta);
        double x0 = a * rho, y0 = b * rho;

        cv::Point pt1(cvRound(x0 + 1000 * (-b)), cvRound(y0 + 1000 * (a)));
        cv::Point pt2(cvRound(x0 - 1000 * (-b)), cvRound(y0 - 1000 * (a)));
        cv::line(imageLines, pt1, pt2, cv::Scalar(0, 0, 255), 2, cv::LINE_AA);
    }
}

void ImageOpenCV::showImages() {
    cv::imshow("Original", image);
    cv::imshow("HSV", hsv);
    cv::imshow("LAB", lab);
    cv::imshow("YUV", yuv);
    cv::imshow("XYZ", xyz);
    cv::imshow("Grayscale", gray);
    cv::imshow("Gaus", gaus);
    cv::imshow("Circles", imageCircles);
    cv::imshow("Lines", imageLines);
    cv::waitKey(0);
    cv::destroyAllWindows();
}
