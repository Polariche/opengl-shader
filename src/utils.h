#include <iostream>
#include <fstream>
#include <string>

std::string load_text(const char* path) {
    std::ifstream file_stream(path);

    if (!file_stream.is_open()) {
        printf("ERROR OPENING FILE! %s\n", path);
        return nullptr;
    }

    std::string content(
        (std::istreambuf_iterator<char>(file_stream)),
        std::istreambuf_iterator<char>()
    );

    return content;
}