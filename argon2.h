#ifndef ARGON2_WRAPPER_H
#define ARGON2_WRAPPER_H

#include <string>

std::string argon2_hash_string(const std::string& password, const std::string& salt);
std::string generateSalt(int length);

#endif