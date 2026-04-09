# 🔐 Biometric Authentication System (Fingerprint-Based)

**Author:** Udayagiri Jaheer

---

## 📌 Overview

This project implements a **fingerprint-based biometric authentication system** using C++, OpenCV, and modern cryptographic techniques.

It allows users to:

* Register using a fingerprint image
* Login using fingerprint matching
* Securely store biometric data using encryption and hashing

---

## 🚀 Features

* 🧬 Fingerprint feature extraction using OpenCV
* 🔐 Secure storage using:

  * Argon2 hashing (with salt + pepper)
  * XOR-based encryption (for biometric template protection)
* 🔑 Session key generation using SHA-256
* 📊 Similarity-based matching (handles real-world variations)
* 🛡️ Protection against duplicate users and duplicate fingerprints
* 📜 Logging system for authentication attempts

---

## 🧠 System Workflow

### 🟢 Registration

1. User inputs username + fingerprint image
2. Image is processed using OpenCV:

   * Grayscale conversion
   * Noise reduction
   * Edge detection
   * Grid-based feature extraction
3. Feature string (biometric template) is generated
4. Biometric is:

   * 🔐 Encrypted using XOR + Pepper
   * 🔑 Hashed using Argon2 + Salt + Pepper
5. Stored in database:

   ```
   username | salt | hash | encrypted_biometric
   ```

---

### 🟡 Login

1. User enters username
2. System retrieves stored data
3. Stored biometric is decrypted
4. New fingerprint image is processed
5. Similarity score is computed
6. If score exceeds threshold → authentication successful

---

## 🔐 Security Design

### 🔑 Argon2 Hashing

* Used to securely hash biometric data
* Resistant to brute-force and GPU attacks

### 🧂 Salt

* Random value added to prevent identical hashes

### 🌶️ Pepper

* Secret constant used for:

  * Hash strengthening
  * Encryption key

### 🔄 XOR Encryption

* Used to protect biometric template
* Reversible (for matching purposes)

> ⚠️ Note: XOR is used for demonstration. In real systems, AES encryption should be used.

---

### 🔑 Session Key (SHA-256)

* Generated after successful login:

  ```
  sessionKey = SHA256(hash + timestamp)
  ```
* Provides temporary authentication session

---

## 📂 Project Structure

```
main.cpp                → Core logic (register/login)
feature_extractor.cpp   → Fingerprint processing (OpenCV)
argon2.cpp              → Secure hashing
sha256.cpp              → Session key generation
crypto.cpp              → Encryption/Decryption (XOR)
database.txt            → Stored user data
log.txt                 → Authentication logs
```

---

## ⚙️ Compilation

```bash
g++ main.cpp argon2.cpp sha256.cpp feature_extractor.cpp crypto.cpp \
-I C:\OpenCV-MinGW-Build-OpenCV-4.5.5-x64\include \
-L C:\OpenCV-MinGW-Build-OpenCV-4.5.5-x64\x64\mingw\lib \
-lopencv_core455 -lopencv_imgcodecs455 -lopencv_imgproc455 \
-largon2 -o app.exe
```

---

## ▶️ Usage

Run the program:

```bash
.\app.exe
```

Menu:

```
1. Register
2. Login
3. Exit
```

---

## 📊 Matching Logic

* Fingerprint is divided into multiple regions
* Each region is compared separately
* Final similarity score is computed
* Threshold-based authentication

---

## ⚠️ Limitations

* XOR encryption is not secure for production
* No liveness detection (fake fingerprints possible)
* Matching is approximate (not industry-level minutiae matching)
* Plain text database (no Base64 encoding yet)

---

## 🚀 Future Improvements

* 🔐 Replace XOR with AES encryption
* 📦 Add Base64 encoding for safe storage
* 🧬 Implement minutiae extraction (ridge endings, bifurcations)
* 🛡️ Add liveness detection
* 🗄️ Use a proper database (SQLite/MySQL)

---

## 💡 Key Learnings

* Biometric systems require **approximate matching**
* Hashing alone is not enough → encryption is required
* Salt + Pepper significantly improve security
* Real-world systems balance **security vs usability**

---

## 📜 License

This project is for educational purposes.

---

## ⭐ Final Note

This project demonstrates a **complete biometric authentication pipeline**, combining:

* Computer Vision
* Cryptography
* System Design

It serves as a strong foundation for building **secure, real-world authentication systems**.

---
