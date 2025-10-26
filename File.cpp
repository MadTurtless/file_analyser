#include "File.h"
#include <fstream>
#include <sstream>
#include <iterator>
#include <iomanip>
#include <stdexcept>
#include <utility>

// define the static map
const std::unordered_multimap<std::string, std::string> File::sigs {
        {"jpeg", "ffd8ffdb"},
        {"jpeg", "ffd8ffe1"},
        {"png", "89504e470d0a1a0a"},
        {"txt", "ffbbbf"},
        {"iso", "4344303031"},
        {"mp3", "fffb"},
        {"mp3", "fff2"},
        {"mp3", "fff3"},
        {"mp3", "494433"}
};

// Constructor
File::File(std::string path) : path(std::move(path)) {
    std::ifstream f(this->path);
    if (!f.is_open()) {
        throw std::runtime_error("Failed to open file: " + this->path);
    }
    f.close();
    setType();
}

// Getters
std::string File::getType() const { return type; }
std::string File::getPath() const { return path; }

// Private methods
void File::setType() {
    std::ifstream file(this->path, std::ios::binary);
    std::vector<unsigned char> buffer{
        std::istreambuf_iterator(file),
        std::istreambuf_iterator<char>()
    };

    std::stringstream ss;
    for (size_t i = 0; i < 16 && i < buffer.size(); i++) {
        ss << std::hex << std::setw(2) << std::setfill('0') << static_cast<int>(buffer[i]);
    }

    type = getTypeBySignature(ss.str());
}

std::string File::getTypeBySignature(const std::string& signature) {
    for (const auto& [fst, snd] : sigs) {
        if (signature.find(snd) != std::string::npos) {
            return fst;
        }
    }
    return "unknown";
}
