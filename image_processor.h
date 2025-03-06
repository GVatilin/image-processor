#ifndef CPP_HSE_MAIN_H
#define CPP_HSE_MAIN_H

#include <iostream>

#include "parse/Parser.h"
#include "image/Image.h"
#include "read_and_write/Reader.h"
#include "read_and_write/Writer.h"
#include "filters/Filter.h"

Image GetImage(const std::string& path);

std::vector<parser::Token> ParseTokens(int argc, char** argv);

Image ApplyFilter(const std::vector<parser::Token>& tokens, Image& image);

void PrintImage(const std::string& path, const Image& image);

#endif  // CPP_HSE_MAIN_H