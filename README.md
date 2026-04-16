# 🔐 Biometric-Derived Empirical Key Authentication System

## 📌 Overview

This project implements a **secure biometric authentication system** that derives authentication data from fingerprint images instead of traditional passwords.

It combines:

* Computer Vision (feature extraction)
* Binary feature encoding
* Multi-sample biometric enrollment
* Error correction (ECC)
* Secure transformation
* Cryptographic hashing (Argon2)

---

## 🚀 Key Features

### 🔹 Multi-Image Enrollment

* Captures multiple fingerprint samples during registration
* Uses **majority voting** to generate a stable biometric template
* Significantly improves accuracy and robustness

---

### 🔹 Binary Feature Extraction

* Converts fingerprint images into **fixed-length binary vectors**
* Eliminates floating-point instability
* Enables efficient comparison using Hamming distance

---

### 🔹 Error Correction (ECC)

* Uses **bit repetition encoding (3x)** for noise tolerance
* Corrects minor variations during login
* Simulates a basic **fuzzy extractor mechanism**

---

### 🔹 Secure Transform Layer

* Applies key-based transformation to protect biometric data
* Prevents direct exposure of raw biometric templates

---

### 🔹 Argon2 Hashing

* Uses **Argon2id** for secure hashing
* Includes **salt + pepper**
* Provides resistance against brute-force and offline attacks

---

### 🔹 Hamming Distance Matching

* Compares binary feature vectors efficiently
* Robust against small variations in biometric input

---

## 🧠 System Architecture

```
Registration:
Fingerprint Images (Multiple)
        ↓
Feature Extraction
        ↓
Binary Encoding
        ↓
Majority Voting (Stable Template)
        ↓
ECC Encoding
        ↓
Secure Transform
        ↓
Argon2 Hashing
        ↓
Database Storage

Login:
Fingerprint Image
        ↓
Feature Extraction
        ↓
Binary Encoding
        ↓
ECC Decoding (Error Correction)
        ↓
Secure Transform
        ↓
Hamming Distance Matching
        ↓
Authentication Result
```

---

## 🛠️ Technologies Used

* **C++**
* **OpenCV** (Image Processing)
* **Argon2** (Secure Hashing)
* **Windows Crypto API** (SHA-256)
* Standard C++ Libraries

---

## 📁 Project Structure

```
.
├── main.cpp                  # Core authentication logic
├── feature_extractor.cpp     # Image processing + feature extraction
├── feature_extractor.h
├── argon2.cpp                # Argon2 wrapper
├── argon2.h
├── sha256.cpp                # SHA-256 implementation
├── sha256.h
├── database.txt              # Stored user data
├── log.txt                   # Authentication logs (optional)
```

---

## ⚙️ How It Works

### 🔐 Registration

1. User provides username
2. System captures **3 fingerprint images**
3. Extracts binary features from each image
4. Combines them using **majority voting**
5. Applies ECC encoding (bit repetition)
6. Applies secure transform
7. Generates Argon2 hash
8. Stores:

   * Username
   * Salt
   * Hash
   * Protected biometric data

---

### 🔓 Login

1. User provides fingerprint image
2. Extracts binary features
3. Applies ECC decoding (error correction)
4. Reconstructs stable template
5. Computes Hamming distance with stored template
6. If within threshold → Authentication successful

---

## 🔒 Security Features

* No raw biometric data stored
* Template protection using transformation
* Salt + Pepper + Argon2 hashing
* Resistance to replay and database attacks
* Noise-tolerant authentication

---

## 📊 Advantages

* ✔ No passwords required
* ✔ High accuracy using multi-sample enrollment
* ✔ Robust against noise and variations
* ✔ Secure storage of biometric data
* ✔ Fast matching using binary vectors

---

## ⚠️ Limitations

* Uses **simplified ECC (bit repetition)** instead of BCH/Reed-Solomon
* AES encryption is simulated (not OpenSSL-based)
* Requires controlled fingerprint input conditions

---

## 🚀 Future Improvements

* 🔹 Implement **BCH-based fuzzy extractor**
* 🔹 Integrate **OpenSSL AES encryption**
* 🔹 Add **real-time fingerprint capture**
* 🔹 Use **deep learning-based feature extraction**
* 🔹 Improve threshold tuning dynamically

---

## 🧪 How to Run

1. Install dependencies:

   * OpenCV
   * Argon2 library

2. Compile:

```
g++ main.cpp feature_extractor.cpp argon2.cpp sha256.cpp -o auth -lopencv_core -lopencv_imgcodecs -lopencv_imgproc
```

3. Run:

```
./auth
```

---

## 📌 Use Cases

* Secure authentication systems
* Biometric login applications
* Research in biometric cryptography
* Privacy-preserving identity systems

---

## 👨‍💻 Author

Developed as a **secure biometric authentication prototype** combining computer vision and cryptography.

---

## ⭐ Final Note

This project demonstrates how biometric data can be transformed into a **secure, noise-tolerant authentication system**, bridging the gap between traditional biometrics and modern cryptographic security.
