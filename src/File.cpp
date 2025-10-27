#include "../include/File.h"

#include <filesystem>
#include <fstream>
#include <sstream>
#include <iterator>
#include <iomanip>
#include <stdexcept>
#include <utility>
#include <vector>

const std::unordered_multimap<std::string, std::string> File::sigs {
        {"jpeg", "ffd8ffdb"},
        {"jpeg", "ffd8ffe1"},
        {"png", "89504e470d0a1a0a"},
        {"mp3", "fffb"},
        {"mp3", "fff2"},
        {"mp3", "fff3"},
        {"mp3", "494433"}
};

// Constructor
File::File(std::string path) : path(std::move(path)) {
    setType();
    setPerms();
    setSize();
}

// Getters
std::string File::getType() const { return type; }
std::string File::getPath() const { return path; }
std::filesystem::perms File::getPerms() const { return perms; }
uintmax_t File::getSize() const { return sizeInBytes; }

// Private methods
void File::setType() {
    constexpr size_t SIGNATURE_BYTES = 16;

    std::ifstream f(this->path, std::ios::binary);
    if (!f.is_open()) {
        throw std::runtime_error("Failed to open file: " + this->path);
    }

    std::vector<unsigned char> buffer(SIGNATURE_BYTES);
    f.read(reinterpret_cast<char*>(buffer.data()), SIGNATURE_BYTES);
    buffer.resize(f.gcount());

    std::stringstream ss;
    for (unsigned char i : buffer) {
        ss << std::hex << std::setw(2) << std::setfill('0') << static_cast<int>(i);
    }

    type = getTypeBySignature(ss.str());
}

void File::setPerms() {
    const std::filesystem::path f(this->path);
    const auto& p = std::filesystem::status(f).permissions();
    this->perms = p; //This is an octal value; use std::oct when printing!
}

void File::setSize() {
    const std::filesystem::path f(this->path);
    const auto size = std::filesystem::file_size(f);
    this->sizeInBytes = size;
}

std::string File::getTypeBySignature(const std::string& signature) {
    for (const auto& [fst, snd] : sigs) {
        if (signature.find(snd) != std::string::npos) {
            return fst;
        }
    }

    return "unknown";
}
