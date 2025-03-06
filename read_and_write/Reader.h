#ifndef CPP_HSE_READER_H
#define CPP_HSE_READER_H

#include <string>

#include "../image/Image.h"

namespace read_and_write {
class Reader {
private:
    std::string path_;
    size_t BytesToNum(unsigned char* bytes);  // NOLINT

public:
    Reader(const std::string& path);  // NOLINT
    Image Read();
};
size_t GetPaddedSize(size_t width);
};  // namespace read_and_write

#endif  // CPP_HSE_READER_H