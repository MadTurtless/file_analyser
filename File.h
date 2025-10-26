#ifndef FILE_H
#define FILE_H

#include <string>
#include <vector>
#include <unordered_map>

class File {
    std::string path;
    std::string type;
    std::vector<std::string> content;

    void setType();
    static std::string getTypeBySignature(const std::string& signature);

public:
    explicit File(std::string path);
    std::string getType() const;
    std::string getPath() const;

    // static signature map
    static const std::unordered_multimap<std::string, std::string> sigs;
};

#endif // FILE_H
