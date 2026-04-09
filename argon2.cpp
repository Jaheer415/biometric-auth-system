#include "argon2.h"
#include <argon2.h>
#include <sstream>
#include <iomanip>
#include <random>


std::string generateSalt(int length) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0, 255);

    std::stringstream ss;
    for (int i = 0; i < length; i++) {
        ss << std::hex << std::setw(2) << std::setfill('0') << dis(gen);
    }
    return ss.str();
}


std::string argon2_hash_string(const std::string& password, const std::string& salt) {

    const uint32_t t_cost = 2;
    const uint32_t m_cost = 1 << 16;
    const uint32_t parallelism = 1;

    unsigned char hash[32];

    argon2id_hash_raw(
        t_cost,
        m_cost,
        parallelism,
        password.c_str(),
        password.length(),
        salt.c_str(),
        salt.length(),
        hash,
        32
    );

    std::stringstream ss;
    for (int i = 0; i < 32; i++) {
        ss << std::hex << std::setw(2) << std::setfill('0') << (int)hash[i];
    }

    return ss.str();
}