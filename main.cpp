#include <iostream>
#include <vector>
#include <functional>
#include "File.h"

int main() {
    try {
        const File img("./windows-7-official-3840x2160-13944.jpg");
        const File mainFile("./main.cpp");
        const File mp3("./NASA Sun Sonification (raw audio).mp3");

        const std::vector files {
            img,
            mainFile,
            mp3
        };

        for (auto& f : files) {
            std::cout << "The file at '" << f.getPath()
                      << "' is a(n) " << f.getType() << " file.\n";
        }

    } catch (const std::exception& e) {
        std::cerr << e.what() << "\n";
    }

    return 0;
}
