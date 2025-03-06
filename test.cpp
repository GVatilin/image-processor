#include "image_processor.h"

void FiltersTest() {
    // Too many params for sharp
    try {
        parser::Token token;
        token.name = "-sharp";
        token.params = {"1"};
        filters::CreateFilter(token);
        std::cout << "Test 1 failed: \"Too many params sharp\". ";
    } catch (std::invalid_argument& e) {
        std::cout << "Test 1 passed: \"Too many params sharp\". ";
        std::cout << "Catch error: (" << e.what() << ")" << std::endl;
    }

    // Too many params for edge
    try {
        parser::Token token;
        token.name = "-edge";
        token.params = {"str", "2"};
        filters::CreateFilter(token);
        std::cout << "Test 2 failed: \"Too many params for edge\". ";
    } catch (std::invalid_argument& e) {
        std::cout << "Test 2 passed: \"Too many params for edge\". ";
        std::cout << "Catch error: (" << e.what() << ")" << std::endl;
    }

    // Not enough params for edge
    try {
        parser::Token token;
        token.name = "-edge";
        token.params = {};
        filters::CreateFilter(token);
        std::cout << "Test 3 failed: \"Not enough params for edge\". ";
    } catch (std::invalid_argument& e) {
        std::cout << "Test 3 passed: \"Not enough params for edge\". ";
        std::cout << "Catch error: (" << e.what() << ")" << std::endl;
    }

    // Incorrect type for edge
    try {
        parser::Token token;
        token.name = "-edge";
        token.params = {"param"};
        filters::CreateFilter(token);
        std::cout << "Test 4 failed: \"Incorrect arg for edge\". ";
    } catch (std::invalid_argument& e) {
        std::cout << "Test 4 passed: \"Incorrect arg for edge\". ";
        std::cout << "Catch error: (" << e.what() << ")" << std::endl;
    }

    // Too many params for gs
    try {
        parser::Token token;
        token.name = "-gs";
        token.params = {"1", "2", "3"};
        filters::CreateFilter(token);
        std::cout << "Test 5 failed: \"Too many params for gs\". ";
    } catch (std::invalid_argument& e) {
        std::cout << "Test 5 passed: \"Too many params for gs\". ";
        std::cout << "Catch error: (" << e.what() << ")" << std::endl;
    }

    // Too many params for neg
    try {
        parser::Token token;
        token.name = "-neg";
        token.params = {"str"};
        filters::CreateFilter(token);
        std::cout << "Test 6 failed: \"Too many params for neg\". ";
    } catch (std::invalid_argument& e) {
        std::cout << "Test 6 passed: \"Too many params for neg\". ";
        std::cout << "Catch error: (" << e.what() << ")" << std::endl;
    }

    // Too many params for log
    try {
        parser::Token token;
        token.name = "-log";
        token.params = {"1"};
        filters::CreateFilter(token);
        std::cout << "Test 7 failed: \"Too many params for log\". ";
    } catch (std::invalid_argument& e) {
        std::cout << "Test 7 passed: \"Too many params for log\". ";
        std::cout << "Catch error: (" << e.what() << ")" << std::endl;
    }

    // Too many params for crop
    try {
        parser::Token token;
        token.name = "-crop";
        token.params = {"10", "10", "100"};
        filters::CreateFilter(token);
        std::cout << "Test 8 failed: \"Too many params for crop\". ";
    } catch (std::invalid_argument& e) {
        std::cout << "Test 8 passed: \"Too many params for crop\". ";
        std::cout << "Catch error: (" << e.what() << ")" << std::endl;
    }

    // Not enough params for crop
    try {
        parser::Token token;
        token.name = "-crop";
        token.params = {"1"};
        filters::CreateFilter(token);
        std::cout << "Test 9 failed: \"Not enough params for crop\". ";
    } catch (std::invalid_argument& e) {
        std::cout << "Test 9 passed: \"Not enough params for crop\". ";
        std::cout << "Catch error: (" << e.what() << ")" << std::endl;
    }

    // Incorrect type for crop
    try {
        parser::Token token;
        token.name = "-crop";
        token.params = {"str", "10"};
        filters::CreateFilter(token);
        std::cout << "Test 10 failed: \"Incorrect type for crop\". ";
    } catch (std::invalid_argument& e) {
        std::cout << "Test 10 passed: \"Incorrect type for crop\". ";
        std::cout << "Catch error: (" << e.what() << ")" << std::endl;
    }

    // Too many params for blur
    try {
        parser::Token token;
        token.name = "-blur";
        token.params = {"10", "10", "100"};
        filters::CreateFilter(token);
        std::cout << "Test 11 failed: \"Too many params for blur\". ";
    } catch (std::invalid_argument& e) {
        std::cout << "Test 11 passed: \"Too many params for blur\". ";
        std::cout << "Catch error: (" << e.what() << ")" << std::endl;
    }

    // Not enough params for crop
    try {
        parser::Token token;
        token.name = "-blur";
        token.params = {};
        filters::CreateFilter(token);
        std::cout << "Test 12 failed: \"Not enough params for blur\". ";
    } catch (std::invalid_argument& e) {
        std::cout << "Test 12 passed: \"Not enough params for blur\". ";
        std::cout << "Catch error: (" << e.what() << ")" << std::endl;
    }

    // Incorrect type to blur 1
    try {
        parser::Token token;
        token.name = "-blur";
        token.params = {"string"};
        filters::CreateFilter(token);
        std::cout << "Test 13 failed: \"String parameter for blur\". ";
    } catch (std::invalid_argument& e) {
        std::cout << "Test 13 passed: \"String parameter for blur\". ";
        std::cout << "Catch error: (" << e.what() << ")" << std::endl;
    }

    // Incorrect type to blur 2
    try {
        parser::Token token;
        token.name = "-blur";
        token.params = {"-1.0"};
        filters::CreateFilter(token);
        std::cout << "Test 14 failed: \"Negative number for blur\". ";
    } catch (std::logic_error& e) {
        std::cout << "Test 14 passed: \"Negative number for blur\". ";
        std::cout << "Catch error: (" << e.what() << ")" << std::endl;
    }

    // Incorrect filter
    try {
        parser::Token token;
        token.name = "-wrongfilter";
        token.params = {"-1.0", "str"};
        filters::CreateFilter(token);
        std::cout << "Test 15 failed: \"Incorrect filter\". ";
    } catch (std::logic_error& e) {
        std::cout << "Test 15 passed: \"Incorrect filter\". ";
        std::cout << "Catch error: (" << e.what() << ")" << std::endl;
    }
}

void ReaderAndWriterTest() {
    // Incorrect path
    try {
        read_and_write::Reader file = read_and_write::Reader("/error_path");
        file.Read();
        std::cout << "Test 1 failed: \"Incorrect path\". ";
    } catch (std::invalid_argument& e) {
        std::cout << "Test 1 passed: \"Incorrect path\". ";
        std::cout << "Catch error: (" << e.what() << ")" << std::endl;
    }

    // Wrong file format
    try {
        read_and_write::Reader file = read_and_write::Reader(
            "/home/grisha/proj_cpp/ami-2312-1-Grigory-Podkhvatilin-gvatilin/tasks/image_processor/read_and_write/"
            "Reader.cpp");
        file.Read();
        std::cout << "Test 2 failed: \"Wrong file format\". ";
    } catch (std::invalid_argument& e) {
        std::cout << "Test 2 passed: \"Wrong file format\". ";
        std::cout << "Catch error: (" << e.what() << ")" << std::endl;
    }

    // Error reading file
    try {
        read_and_write::Reader file = read_and_write::Reader(
            "/home/grisha/proj_cpp/ami-2312-1-Grigory-Podkhvatilin-gvatilin/tasks/image_processor/test_script/data/"
            "test_flag.bmp");
        file.Read();
        std::cout << "Test 3 failed: \"Error reading\". ";
    } catch (std::exception& e) {
        std::cout << "Test 3 passed: \"Error reading\". ";
        std::cout << "Catch error: (" << e.what() << ")" << std::endl;
    }

    // Wrong output file
    try {
        read_and_write::Writer writer{"/home"};
        read_and_write::Reader file = read_and_write::Reader(
            "/home/grisha/proj_cpp/ami-2312-1-Grigory-Podkhvatilin-gvatilin/tasks/image_processor/test_script/data/"
            "lenna.bmp");
        Image img = file.Read();
        writer.Write(img);
        std::cout << "Test 4 failed: \"Wrong output file\". ";
    } catch (std::invalid_argument& e) {
        std::cout << "Test 4 passed: \"Wrong output file\". ";
        std::cout << "Catch error: (" << e.what() << ")" << std::endl;
    }
}

void SetColorTest() {
    Color color{10, 20, 30};
    color.SetVals(50, 60, 70);
    if (color.blue == static_cast<size_t>(50) && static_cast<size_t>(60) && color.red == static_cast<size_t>(70)) {
        std::cout << "Test 1 passed: \"Change colors in pixel\"." << std::endl;
    } else {
        std::cout << "Test 1 failed: \"Change colors in pixel\"." << std::endl;
    }
}

void SimpleImageTest() {
    Image img{100, 120};
    if (img.GetWidth() == 100 && img.GetHeight() == 120) {
        std::cout << "Test 2 passed: \"Simple image\"." << std::endl;
    } else {
        std::cout << "Test 2 failed: \"Simple image\"." << std::endl;
    }
}

void ParserTest() {
    char** s = new char*[7];
    std::vector<std::string> params = {"main", "-sharp", "-gs", "-edge", "0.5", "-blur", "7"};
    for (size_t i = 0; i < 7; i++) {
        s[i] = params[i].data();
    }
    size_t passed_tokens = 0;
    std::vector<parser::Token> tokens = ParseTokens(7, s);
    if (tokens[0].name == "-sharp" && tokens[0].params.empty()) {
        passed_tokens++;
    }
    if (tokens[1].name == "-gs" && tokens[1].params.empty()) {
        passed_tokens++;
    }
    if (tokens[2].name == "-edge" && tokens[2].params[0] == "0.5") {
        passed_tokens++;
    }
    if (tokens[3].name == "-blur" && tokens[3].params[0] == "7") {
        passed_tokens++;
    }
    if (passed_tokens == 4) {
        std::cout << "Test 3 passed: \"Simple Parser test\"." << std::endl;
    } else {
        std::cout << "Test 3 failed: \"Simple Parser test\"." << std::endl;
    }
}

void FuncTests() {
    SetColorTest();
    SimpleImageTest();
    ParserTest();
}

// Чтобы запустить тесты, нужно закомментить main в файле image_processor.cpp
/*int main(){
    std::cout << "======================== Tests ========================" << std::endl;
    std::cout << "-------------------- Filters Errors --------------------" << std::endl;
    std::cout << std::endl;
    FiltersTest();
    std::cout << std::endl;
    std::cout << "---------------- Read and Write Errors ----------------" << std::endl;
    std::cout << std::endl;
    ReaderAndWriterTest();
    std::cout << std::endl;
    std::cout << "-------------------- Function Tests --------------------" << std::endl;
    std::cout << std::endl;
    FuncTests();
    std::cout << std::endl;
    return 0;
}*/