#include "Filter.h"
#include "../read_and_write/Utils.h"

namespace filters {

template <typename T>
std::vector<T> filters::Filter::GetPixColor(const std::vector<std::vector<T>>& matrix, const Image& image, int x,
                                            int y) const {
    T blue = 0;
    T green = 0;
    T red = 0;
    for (size_t j = 0; j < matrix.size(); ++j) {
        for (size_t i = 0; i < matrix[0].size(); ++i) {
            red += image
                       .GetColor(std::clamp(static_cast<size_t>(x + i > 0 ? x + i - 1 : 0), static_cast<size_t>(0),
                                            image.GetWidth() - 1),
                                 std::clamp(static_cast<size_t>(y + j > 0 ? y - 1 + j : 0), static_cast<size_t>(0),
                                            image.GetHeight() - 1))
                       .red *
                   matrix[i][j];
            green += image
                         .GetColor(std::clamp(static_cast<size_t>(x + i > 0 ? x + i - 1 : 0), static_cast<size_t>(0),
                                              image.GetWidth() - 1),
                                   std::clamp(static_cast<size_t>(y + j > 0 ? y - 1 + j : 0), static_cast<size_t>(0),
                                              image.GetHeight() - 1))
                         .green *
                     matrix[i][j];
            blue += image
                        .GetColor(std::clamp(static_cast<size_t>(x + i > 0 ? x + i - 1 : 0), static_cast<size_t>(0),
                                             image.GetWidth() - 1),
                                  std::clamp(static_cast<size_t>(y + j > 0 ? y - 1 + j : 0), static_cast<size_t>(0),
                                             image.GetHeight() - 1))
                        .blue *
                    matrix[i][j];
        }
    }
    return {blue, green, red};
}

uint8_t GetCorrectColors(int color, const uint8_t max_color = 255) {
    if (color < 0) {
        return 0;
    } else if (color > max_color) {
        return max_color;
    }
    return color;
}

Image filters::SharpeningFilter::Apply(const Image& img) const {
    std::vector<std::vector<Color>> new_data;
    std::vector<std::vector<int>> matrix = {{0, -1, 0}, {-1, 5, -1}, {0, -1, 0}};  // NOLINT
    for (size_t i = 0; i < img.GetHeight(); i++) {
        std::vector<Color> row(img.GetWidth());
        for (size_t j = 0; j < img.GetWidth(); j++) {
            std::vector<int> colors = GetPixColor(matrix, img, j, i);  // NOLINT
            row[j].blue = GetCorrectColors(colors[0]);
            row[j].green = GetCorrectColors(colors[1]);
            row[j].red = GetCorrectColors(colors[2]);
        }
        new_data.push_back(row);
    }
    return {new_data};
}

Image EdgeFilter::Apply(const Image& img) const {
    std::vector<std::vector<Color>> ans;
    GrayScaleFilter gs;
    Image data = gs.Apply(img);
    std::vector<std::vector<int>> matrix = {{0, -1, 0}, {-1, 4, -1}, {0, -1, 0}};
    for (size_t i = 0; i < data.GetHeight(); ++i) {
        std::vector<Color> row(data.GetWidth());
        for (size_t j = 0; j < data.GetWidth(); ++j) {
            std::vector<int> colors = GetPixColor(matrix, data, j, i);  // NOLINT
            row[j].blue = GetCorrectColors(colors[0]);
            row[j].green = GetCorrectColors(colors[1]);
            row[j].red = GetCorrectColors(colors[2]);
            if (static_cast<double>(row[j].blue + row[j].green + row[j].red) / 3 >= threshold_) {
                row[j].blue = image::utils::MAX_VALUE_COLOR;
                row[j].green = image::utils::MAX_VALUE_COLOR;
                row[j].red = image::utils::MAX_VALUE_COLOR;
            } else {
                row[j].blue = 0;
                row[j].green = 0;
                row[j].red = 0;
            }
        }
        ans.push_back(row);
    }
    return {ans};
}

Image filters::GrayScaleFilter::Apply(const Image& img) const {
    std::vector<std::vector<Color>> new_data;
    for (size_t i = 0; i < img.GetHeight(); i++) {
        std::vector<Color> row(img.GetWidth());
        for (size_t j = 0; j < img.GetWidth(); j++) {
            double color = img.GetColor(j, i).red * image::utils::GRAYSCALE[0] +
                           img.GetColor(j, i).green * image::utils::GRAYSCALE[1] +
                           img.GetColor(j, i).blue * image::utils::GRAYSCALE[2];
            row[j].blue = static_cast<size_t>(color);
            row[j].green = static_cast<size_t>(color);
            row[j].red = static_cast<size_t>(color);
        }
        new_data.push_back(row);
    }
    return {new_data};
}

Image filters::NegativeFilter::Apply(const Image& img) const {
    std::vector<std::vector<Color>> new_data;
    for (size_t i = 0; i < img.GetHeight(); i++) {
        std::vector<Color> row(img.GetWidth());
        for (size_t j = 0; j < img.GetWidth(); j++) {
            row[j].blue = image::utils::MAX_VALUE_COLOR - img.GetColor(j, i).blue;
            row[j].green = image::utils::MAX_VALUE_COLOR - img.GetColor(j, i).green;
            row[j].red = image::utils::MAX_VALUE_COLOR - img.GetColor(j, i).red;
        }
        new_data.push_back(row);
    }
    return {new_data};
}

std::vector<double> filters::GaussianBlurFilter::MakeGaussMatrix() const {
    size_t radius = static_cast<size_t>(sigma_ * 2);
    std::vector<double> gauss_matrix(radius * 2 + 1);
    double p = 1 / (std::pow(M_PI * 2, image::utils::GAUSS_DEGREE) * sigma_);
    double sum = 0;
    gauss_matrix[radius] = p;
    sum += gauss_matrix[radius];

    for (int i = 1; i < static_cast<int>(sigma_ * 2) + 1; i++) {
        double kf = std::pow(M_E, -1 * i * i / (2 * sigma_ * sigma_)) * p;
        gauss_matrix[radius - i] = kf;
        gauss_matrix[radius + i] = kf;
        sum += gauss_matrix[radius - i] * 2;
    }

    for (size_t i = 0; i < radius * 2 + 1; i++) {
        gauss_matrix[i] /= sum;
    }

    return gauss_matrix;
}

Image filters::GaussianBlurFilter::Apply(const Image& img) const {
    std::vector<double> gauss_matrix = MakeGaussMatrix();
    std::vector<std::vector<Color>> new_data;
    int side = static_cast<int>(gauss_matrix.size() / 2);

    for (size_t i = 0; i < img.GetHeight(); i++) {
        std::vector<Color> row(img.GetWidth());
        for (size_t j = 0; j < img.GetWidth(); j++) {
            double b = 0;
            double g = 0;
            double r = 0;
            for (int k = -side; k < side + 1; k++) {
                int y = std::max(std::min(static_cast<int>(j) + k, static_cast<int>(img.GetWidth()) - 1), 0);
                b += gauss_matrix[side + k] * static_cast<float>(img.GetColor(y, i).blue);
                g += gauss_matrix[side + k] * static_cast<float>(img.GetColor(y, i).green);
                r += gauss_matrix[side + k] * static_cast<float>(img.GetColor(y, i).red);
            }
            row[j].blue = GetCorrectColors(static_cast<size_t>(b));   // NOLINT
            row[j].green = GetCorrectColors(static_cast<size_t>(g));  // NOLINT
            row[j].red = GetCorrectColors(static_cast<size_t>(r));    // NOLINT
        }
        new_data.push_back(row);
    }

    std::vector<std::vector<Color>> res(img.GetHeight(), std::vector<Color>(img.GetWidth()));
    for (size_t j = 0; j < img.GetWidth(); j++) {
        for (size_t i = 0; i < img.GetHeight(); i++) {
            double b = 0;
            double g = 0;
            double r = 0;
            for (int k = -side; k < side + 1; k++) {
                int x = std::max(std::min(static_cast<int>(i) + k, static_cast<int>(img.GetHeight()) - 1), 0);
                b += gauss_matrix[side + k] * static_cast<float>(new_data[x][j].blue);
                g += gauss_matrix[side + k] * static_cast<float>(new_data[x][j].green);
                r += gauss_matrix[side + k] * static_cast<float>(new_data[x][j].red);
            }
            res[i][j].blue = GetCorrectColors(static_cast<size_t>(b));   // NOLINT
            res[i][j].green = GetCorrectColors(static_cast<size_t>(g));  // NOLINT
            res[i][j].red = GetCorrectColors(static_cast<size_t>(r));    // NOLINT
        }
    }

    return {res};
}

Image CropFilter::Apply(const Image& image) const {
    Image new_img(std::min(width_, image.GetWidth()), std::min(height_, image.GetHeight()));
    for (size_t i = image.GetHeight() - std::min(height_, image.GetHeight()); i < image.GetHeight(); ++i) {
        for (size_t j = 0; j < std::min(width_, image.GetWidth()); ++j) {
            new_img.SetColor(i - (image.GetHeight() - std::min(height_, image.GetHeight())), j, image.GetColor(j, i));
        }
    }
    return new_img;
}

Image MyFilter::Apply(const Image& img) const {
    std::vector<std::vector<Color>> new_data;
    for (size_t i = 0; i < img.GetHeight(); i++) {
        std::vector<Color> row(img.GetWidth());
        for (size_t j = 0; j < img.GetWidth(); j++) {
            std::vector<std::vector<int>> matrix = {
                {0, -1, 0}, {-3, static_cast<int>(std::log(i) * std::log(j) / 6) % 10, 0}, {0, -1, 0}};  // NOLINT
            std::vector<int> colors = GetPixColor(matrix, img, j, i);                                    // NOLINT
            row[j].blue = GetCorrectColors(colors[0]);
            row[j].green = GetCorrectColors(colors[1]);
            row[j].red = GetCorrectColors(colors[2]);
        }
        new_data.push_back(row);
    }
    return {new_data};
}

CropFilter::CropFilter(size_t width, size_t height) {
    width_ = width;
    height_ = height;
}

EdgeFilter::EdgeFilter(double thres) {
    threshold_ = thres;
}

GaussianBlurFilter::GaussianBlurFilter(double sigma) {
    sigma_ = sigma;
}

}  // namespace filters

std::unique_ptr<filters::Filter> filters::CreateFilter(const parser::Token& token) {
    const ::std::string& name = token.name;
    if (name == "-sharp") {
        if (!token.params.empty()) {
            throw std::invalid_argument("Too many parameters for sharp filter");
        }
        auto ptr = std::make_unique<filters::SharpeningFilter>();
        return ptr;
    } else if (name == "-edge") {
        if (token.params.size() > 1) {
            throw std::invalid_argument("Too many parameters for edge filter");
        }
        if (token.params.empty()) {
            throw std::invalid_argument("Not enough parameters for edge filter");
        }
        try {
            double thres = stod(token.params[0]) * image::utils::MULTIPLIER;
            auto ptr = std::make_unique<filters::EdgeFilter>(thres);
            return ptr;
        } catch (const std::exception& e) {
            throw std::invalid_argument("Incorrect arg type");
        }
    } else if (name == "-gs") {
        if (!token.params.empty()) {
            throw std::invalid_argument("Too many parameters for grayscale filter");
        }
        auto ptr = std::make_unique<filters::GrayScaleFilter>();
        return ptr;
    } else if (name == "-neg") {
        if (!token.params.empty()) {
            throw std::invalid_argument("Too many parameters for negative filter");
        }
        auto ptr = std::make_unique<filters::NegativeFilter>();
        return ptr;
    } else if (name == "-crop") {
        if (token.params.size() <= 1) {
            throw std::invalid_argument("Not enough parameters for crop filter");
        }
        if (token.params.size() >= 3) {
            throw std::invalid_argument("Too many parameters for crop filter");
        }
        try {
            size_t width = static_cast<size_t>(stoi(token.params[0]));
            size_t height = static_cast<size_t>(stoi(token.params[1]));
            auto ptr = std::make_unique<filters::CropFilter>(width, height);
            return ptr;
        } catch (const std::exception& e) {
            throw std::invalid_argument("Incorrect arg type");
        }
    } else if (name == "-blur") {
        if (token.params.size() > 1) {
            throw std::invalid_argument("Too many parameters for gauss filter");
        }
        if (token.params.empty()) {
            throw std::invalid_argument("Not enough parameters for gauss filter");
        }
        try {
            double sigma = stod(token.params[0]);
            if (sigma <= 0) {
                throw std::logic_error("Expected positive arg");
            }
            auto ptr = std::make_unique<filters::GaussianBlurFilter>(sigma);
            return ptr;
        } catch (const std::invalid_argument& e) {
            throw std::invalid_argument("Incorrect arg type");
        } catch (const std::logic_error& e) {
            throw std::logic_error("Expected positive arg");
        }
    } else if (name == "-log") {
        if (!token.params.empty()) {
            throw std::invalid_argument("Too many parameters for log filter");
        }
        auto ptr = std::make_unique<filters::MyFilter>();
        return ptr;
    } else {
        throw std::invalid_argument("Incorrect filter");
    }
}