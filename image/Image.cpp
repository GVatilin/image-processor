#include "Image.h"

Image::Image(size_t width, size_t height) {
    pixels_.resize(height);
    for (size_t i = 0; i < height; ++i) {
        pixels_[i].resize(width);
    }
    width_ = width;
    height_ = height;
}

Image::Image(const std::vector<std::vector<Color>>& pixels) {
    for (auto& item : pixels) {
        pixels_.push_back(item);
    }
    width_ = pixels_[0].size();
    height_ = pixels_.size();
}
Image::Image(const Image& other) {
    pixels_ = other.pixels_;
    width_ = other.width_;
    height_ = other.height_;
}
size_t Image::GetHeight() const {
    return height_;
}
size_t Image::GetWidth() const {
    return width_;
}

const Color& Image::GetColor(size_t x, size_t y) const {
    return pixels_[y][x];
}

void Image::SetColor(size_t x, size_t y, const Color& color) {
    pixels_[x][y] = color;
}
