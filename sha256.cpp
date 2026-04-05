#include "sha256.h"
#include <windows.h>
#include <wincrypt.h>
#include <sstream>
#include <iomanip>

#pragma comment(lib, "advapi32.lib")

std::string sha256(const std::string& input) {

    HCRYPTPROV hProv = 0;
    HCRYPTHASH hHash = 0;

    BYTE hash[32];
    DWORD hashLen = 32;

    CryptAcquireContext(&hProv, NULL, NULL, PROV_RSA_AES, CRYPT_VERIFYCONTEXT);
    CryptCreateHash(hProv, CALG_SHA_256, 0, 0, &hHash);
    CryptHashData(hHash, (BYTE*)input.c_str(), input.length(), 0);
    CryptGetHashParam(hHash, HP_HASHVAL, hash, &hashLen, 0);

    std::stringstream ss;
    for (DWORD i = 0; i < hashLen; i++) {
        ss << std::hex << std::setw(2) << std::setfill('0') << (int)hash[i];
    }

    CryptDestroyHash(hHash);
    CryptReleaseContext(hProv, 0);

    return ss.str();
}