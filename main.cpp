#include <opencv2/opencv.hpp>

#include "imageopencv.h"

int main() {
    ImageOpenCV processor("/home/alex/OpenCVProject/image.webp");
    processor.convertColorSpaces();
    processor.applyGaussianBlur();
    processor.detectCircles();
    processor.detectLines();
    processor.drawCircles();
    processor.drawLines();
    processor.showImages();
    return 0;
}
