#ifndef CPP_HSE_FILTER_H
#define CPP_HSE_FILTER_H

#include <memory>
#include <algorithm>
#include <vector>
#include <cmath>

#include "../image/Image.h"
#include "../parse/Parser.h"

namespace filters {
class Filter {
public:
    Filter() = default;
    virtual Image Apply(const Image& img) const = 0;
    virtual ~Filter() = default;

protected:
    template <typename T>
    std::vector<T> GetPixColor(const std::vector<std::vector<T>>& matrix, const Image& image, int x, int y) const;
};

class SharpeningFilter : public Filter {
public:
    Image Apply(const Image& img) const override;
};

class CropFilter : public Filter {
public:
    CropFilter(size_t width, size_t height);
    Image Apply(const Image& img) const override;

private:
    size_t width_;
    size_t height_;
};

class GrayScaleFilter : public Filter {
public:
    Image Apply(const Image& img) const override;
};

class NegativeFilter : public Filter {
public:
    Image Apply(const Image& img) const override;
};

class GaussianBlurFilter : public Filter {
public:
    GaussianBlurFilter(double sigma);  // NOLINT
    std::vector<double> MakeGaussMatrix() const;
    Image Apply(const Image& img) const override;

private:
    double sigma_;
};

class EdgeFilter : public Filter {
public:
    EdgeFilter(double thres);                      // NOLINT
    Image Apply(const Image& img) const override;  // NOLINT

private:
    double threshold_;
};

class MyFilter : public Filter {
public:
    Image Apply(const Image& image) const override;
};

std::unique_ptr<Filter> CreateFilter(const parser::Token& token);
}  // namespace filters
#endif  // CPP_HSE_FILTER_H