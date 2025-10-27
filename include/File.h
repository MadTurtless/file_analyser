#ifndef FILE_H
#define FILE_H

#include <filesystem>
#include <string>
#include <vector>
#include <unordered_map>

class File {
    std::string path;
    std::string type;
    std::filesystem::perms perms;
    uintmax_t sizeInBytes;

    void setType();
    void setPerms();
    void setSize();
    static std::string getTypeBySignature(const std::string& signature);

public:
    explicit File(std::string path);
    [[nodiscard]] std::string getType() const;
    [[nodiscard]] std::string getPath() const;
    [[nodiscard]] std::filesystem::perms getPerms() const;
    [[nodiscard]] uintmax_t getSize() const;

    // static signature map
    static const std::unordered_multimap<std::string, std::string> sigs;
};

#endif // FILE_H
