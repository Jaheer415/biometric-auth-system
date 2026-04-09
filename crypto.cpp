#include "crypto.h"

std::string encryptDecrypt(const std::string& data, const std::string& key) {

    std::string output = data;

    for (size_t i = 0; i < data.size(); i++) {
        output[i] = data[i] ^ key[i % key.size()];
    }

    return output;
}