#include <iostream>
#include <vector>
#include <functional>
#include "../include/File.h"

int main() {
    try {
        const File img("test/assets/picture.jpg");
        const File mp3("test/assets/audio.mp3");
        const File iso("test/assets/image.iso");

        const std::vector files {
            img,
            mp3,
            iso
        };

        for (auto& f : files) {
            std::cout << "The file at '" << f.getPath()
                      << "' is a(n) " << f.getType() << " file "
                      << "with permissions '" << std::oct << static_cast<int>(f.getPerms())
                      << " and a size of " << f.getSize() << " bytes" << ".\n";
        }

        std::cout << std::dec;
    } catch (const std::exception& e) {
        std::cerr << e.what() << "\n";
    }

    return 0;
}
