#include <iostream>
#include <fstream>
#include <cstring>
#include <cstdlib>

struct Image {
    char header[4];
    int width;
    int height;
    char data[10];
};

int ProcessImage(const char* filename) {
    FILE* fp = fopen(filename, "rb");
    if (fp == nullptr) {
        std::cerr << "Can't open file or file doesn't exist.\n";
        return 1;
    }

    Image img;
    if (fread(&img, sizeof(img), 1, fp) != 1) {
        std::cerr << "Failed to read image data.\n";
        fclose(fp);
        return 1;
    }

    std::cout << "\n\tHeader\tWidth\tHeight\tData\n";
    std::cout << "\t" << img.header << "\t" << img.width << "\t" << img.height << "\t" << img.data << "\n";

    // Check for overflow/invalid allocation
    int size1 = img.width + img.height;
    if (size1 <= 0 || size1 > 1024) {
        std::cerr << "Invalid size1 calculation.\n";
        fclose(fp);
        return 1;
    }

    char* buff1 = (char*)malloc(size1);
    if (!buff1) {
        std::cerr << "Memory allocation failed for buff1.\n";
        fclose(fp);
        return 1;
    }

    memcpy(buff1, img.data, sizeof(img.data));
    free(buff1);

    int size2 = img.width - img.height + 100;
    if (size2 <= 0 || size2 > 1024) {
        std::cerr << "Invalid size2 calculation.\n";
        fclose(fp);
        return 1;
    }

    char* buff2 = (char*)malloc(size2);
    if (!buff2) {
        std::cerr << "Memory allocation failed for buff2.\n";
        fclose(fp);
        return 1;
    }

    memcpy(buff2, img.data, sizeof(img.data));

    if (img.height == 0) {
        std::cerr << "Division by zero error.\n";
        free(buff2);
        fclose(fp);
        return 1;
    }

    int size3 = img.width / img.height;
    if (size3 <= 0 || size3 >= 10) {
        std::cerr << "Invalid size3 for buffer indexing.\n";
        free(buff2);
        fclose(fp);
        return 1;
    }

    char buff3[10] = {0};
    char* buff4 = (char*)malloc(size3);
    if (!buff4) {
        std::cerr << "Memory allocation failed for buff4.\n";
        free(buff2);
        fclose(fp);
        return 1;
    }

    // Simulated processing
    memcpy(buff4, img.data, sizeof(img.data));

    // Safe access
    buff3[size3 - 1] = 'c';
    buff4[size3 - 1] = 'c';

    free(buff4);
    free(buff2);
    fclose(fp);

    return 0;
}

int main(int argc, char* argv[]) {
    if (argc < 2) {
        std::cerr << "Usage: ./helloworld <filename>\n";
        return 1;
    }

    std::cout << "Hello World!\n";
    return ProcessImage(argv[1]);
}
