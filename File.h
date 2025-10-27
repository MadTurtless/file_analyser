#ifndef FILE_H
#define FILE_H

#include <string>
#include <vector>
#include <unordered_map>

class File {
    std::string path;
    std::string type;
    int perms;

    void setType();
    void setPerms();
    static std::string getTypeBySignature(const std::string& signature);

public:
    explicit File(std::string path);
    [[nodiscard]] std::string getType() const;
    [[nodiscard]] std::string getPath() const;
    [[nodiscard]] int getPerms() const;

    // static signature map
    static const std::unordered_multimap<std::string, std::string> sigs;
};

#endif // FILE_H
