# 🔐 Biometric Derived Empirical Key Authentication System

## 📌 Overview

This project implements a **biometric-based authentication system** using fingerprint images. Instead of traditional passwords, the system derives a secure authentication mechanism from fingerprint features and generates cryptographic session keys.

The system combines:

* Image processing (OpenCV)
* Feature extraction (custom algorithm)
* Cryptographic hashing (SHA-256, Argon2)
* Secure authentication logic

---

## 🎯 Objectives

* Replace traditional password-based authentication with biometric authentication
* Extract stable and unique fingerprint features
* Securely store biometric data using hashing and salting
* Generate session keys upon successful authentication
* Evaluate system performance using FAR, FRR, and accuracy

---

## 🧠 System Architecture

```
Fingerprint Image
      ↓
Preprocessing (resize, blur, normalize)
      ↓
Feature Extraction
      ↓
Feature Vector
      ↓
Hashing (Argon2 + SHA-256)
      ↓
Database Storage
      ↓
Matching & Similarity Score
      ↓
Authentication Decision
```

---

## ⚙️ Technologies Used

* **C++**
* **OpenCV** (Image Processing)
* **Argon2** (Password Hashing)
* **Windows Crypto API** (SHA-256)
* **SQLite / File Storage** (database.txt)

---

## 📂 Project Structure

```
project/
│
├── main.cpp                # Main application logic
├── feature_extractor.cpp  # Fingerprint feature extraction
├── feature_extractor.h
├── argon2.cpp             # Argon2 hashing
├── argon2.h
├── sha256.cpp             # SHA-256 hashing
├── sha256.h
├── crypto.cpp             # XOR encryption (optional)
├── crypto.h
├── database.txt           # Stored user data
├── log.txt                # Authentication logs
```

---

## 🔍 Feature Extraction Details

The system extracts multiple types of features:

### 1. Global Features

* Ridge Density
* Edge Density
* Gradient Magnitude
* Orientation (cosine-based)

### 2. Local Features (6×6 Grid)

Each region extracts:

* Edge ratio
* Local orientation

### 3. Multi-Variant Matching

* Rotation (0°, 90°, 180°, 270°)
* Flipped image

---

## 🔐 Security Mechanisms

* **Salted Hashing (Argon2)**
* **Pepper (hardcoded secret)**
* **SHA-256 session key generation**
* **No raw biometric stored in plaintext (hashed protection layer)**

---

## 🧮 Similarity Computation

Similarity is computed using:

```
Similarity = exp(-5 × avgDifference)
```

* Weighted feature comparison
* Global features given higher importance
* Multi-variant matching (best score selected)

---

## 🎯 Threshold Selection

Final threshold:

```
Threshold = 0.65
```

* Above → Authentication Success
* Below → Authentication Failure

---

## 📊 Performance Evaluation

Using FVC2002 Dataset:

| Metric                      | Value   |
| --------------------------- | ------- |
| FAR (False Acceptance Rate) | ~12.5%  |
| FRR (False Rejection Rate)  | ~30–40% |
| Accuracy                    | ~75–85% |

---

## 📈 Observations

* Strong fingerprint samples are correctly authenticated
* Weak or noisy samples may be rejected
* Some overlap exists between genuine and impostor scores
* System demonstrates real-world biometric trade-offs

---

## ⚠️ Limitations

* Does not use minutiae-based fingerprint matching
* Relies on statistical features (density, orientation)
* Sensitive to image quality
* Some false acceptances may occur

---

## 🚀 Future Improvements

* Minutiae extraction (ridge endings, bifurcations)
* Machine learning-based feature extraction
* Deep learning (CNN-based fingerprint recognition)
* Improved normalization techniques
* Larger dataset evaluation

---

## ▶️ How to Run

### 1. Compile

```bash
g++ main.cpp argon2.cpp sha256.cpp feature_extractor.cpp crypto.cpp \
-I <opencv_include_path> \
-L <opencv_lib_path> \
-lopencv_core -lopencv_imgcodecs -lopencv_imgproc -largon2 -o app.exe
```

### 2. Run

```bash
./app.exe
```

---

## 📌 Usage

1. Register user with fingerprint image
2. Login using another fingerprint sample
3. System computes similarity and authenticates
4. Session key is generated on success

---

## 🧾 Sample Output

```
Similarity Score: 0.75
[ SUCCESS ] Authentication Successful
Session Key: <generated hash>
```

---

## 👨‍💻 Author

* Developed as part of a college project
* Focused on combining biometrics with cryptographic security

---

## 📚 References

* FVC2002 Fingerprint Dataset
* Argon2 Password Hashing
* OpenCV Documentation
* Biometric Authentication Research Papers

---

## 🏁 Conclusion

This project demonstrates a **biometric authentication system using fingerprint-derived features and cryptographic techniques**. While not as advanced as industrial systems, it successfully highlights:

* Feature extraction challenges
* Security considerations
* Real-world biometric trade-offs

---

⭐ This project reflects practical implementation of biometric security concepts.
