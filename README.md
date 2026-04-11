# 🔐 Biometric Derived Empirical Key Authentication System (Secure Version)

## 📌 Overview

This project implements a **secure biometric authentication system** using fingerprint images. Unlike traditional systems, it integrates **feature extraction, cryptographic hashing, and cancelable biometric transformation** to ensure both **accuracy and security**.

The system authenticates users by comparing fingerprint-derived feature vectors instead of passwords and generates secure session keys upon successful login.

---

## 🎯 Objectives

* Replace password-based authentication with biometric authentication
* Extract robust fingerprint features
* Securely store biometric templates
* Prevent biometric data leakage using transformation
* Evaluate system performance using FAR, FRR, and accuracy

---

## 🧠 System Architecture

```id="r0w3k2"
Fingerprint Image
      ↓
Preprocessing
      ↓
Feature Extraction
      ↓
Feature Transformation (Cancelable Biometrics)
      ↓
Hashing (Argon2 + Pepper)
      ↓
Database Storage
      ↓
Matching & Similarity
      ↓
Authentication Decision
      ↓
Session Key Generation
```

---

## ⚙️ Technologies Used

* **C++**
* **OpenCV** (Image Processing)
* **Argon2** (Secure Hashing)
* **SHA-256 (Windows Crypto API)** (Session Keys)
* **File-based storage (database.txt)**

---

## 📂 Project Structure

```id="kvjv6y"
project/
│
├── main.cpp                # Core system logic
├── feature_extractor.cpp  # Feature extraction algorithm
├── feature_extractor.h
├── argon2.cpp             # Argon2 hashing
├── argon2.h
├── sha256.cpp             # SHA-256 session key
├── sha256.h
├── database.txt           # Stored user data
├── log.txt                # Authentication logs
```

---

## 🔍 Feature Extraction

The system extracts multiple levels of fingerprint features:

### 🔹 Global Features

* Ridge Density
* Edge Density
* Gradient Magnitude
* Orientation (cosine-based)

### 🔹 Local Features (6×6 Grid)

Each region extracts:

* Edge ratio
* Local orientation

### 🔹 Multi-Variant Matching

* Rotation (0°, 90°, 180°, 270°)
* Vertical flip

---

## 🔐 Security Enhancements (Key Contribution)

### 🔥 Cancelable Biometrics (Transformation)

To protect biometric templates:

```id="4c9qk0"
Feature → Transform (sin-based with secret key) → Stored
```

* Uses secret key: `TRANSFORM_KEY`
* Applies non-reversible transformation using sine function
* Ensures stored features cannot be reconstructed

---

### 🔐 Hashing

* Argon2 used with:

  * Salt (random)
  * Pepper (fixed secret)
* Prevents database attacks

---

### 🔑 Session Key

* Generated using SHA-256
* Based on hash + timestamp
* Temporary access control

---

## 🧮 Similarity Computation

```id="1dqv3g"
Similarity = exp(-5 × avgDifference)
```

* Weighted comparison
* Global features prioritized
* Multi-variant best match selection

---

## 🎯 Threshold Selection

```id="l0sj3q"
Threshold = 0.65
```

* Above → Accept
* Below → Reject

---

## 📊 Performance Evaluation

Using FVC2002 dataset:

| Metric                      | Value   |
| --------------------------- | ------- |
| FAR (False Acceptance Rate) | ~10–15% |
| FRR (False Rejection Rate)  | ~30–40% |
| Accuracy                    | ~75–85% |

---

## 📈 Observations

* Strong fingerprint samples are correctly authenticated
* Weak samples may be rejected
* Some overlap exists between genuine and impostor scores
* Transformation does not affect matching accuracy

---

## ⚠️ Limitations

* No minutiae-based matching
* Uses statistical features instead of ridge topology
* Sensitive to poor image quality
* Some false acceptances possible

---

## 🚀 Future Improvements

* Minutiae-based fingerprint recognition
* Deep learning (CNN-based models)
* Adaptive thresholding
* Larger dataset evaluation
* Hardware integration (sensor-based input)

---

## ▶️ How to Run

### Compile

```bash id="jyg4dn"
g++ main.cpp argon2.cpp sha256.cpp feature_extractor.cpp crypto.cpp \
-I <opencv_include_path> \
-L <opencv_lib_path> \
-lopencv_core -lopencv_imgcodecs -lopencv_imgproc -largon2 -o app.exe
```

### Run

```bash id="4rrn8f"
./app.exe
```

---

## 📌 Usage

1. Register using fingerprint image
2. Login with another sample of same fingerprint
3. System computes similarity score
4. Authentication is granted or denied
5. Session key generated on success

---

## 🧾 Sample Output

```id="q0xfpn"
Similarity Score: 0.75
[ SUCCESS ] Authentication Successful
Session Key: <generated hash>
```

---

## 🧠 Key Innovation

> The system introduces a cancelable biometric transformation using a secret key to protect feature templates, ensuring non-reversibility while maintaining matching accuracy.

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

This project demonstrates a **secure biometric authentication system** that integrates:

* Feature extraction
* Cryptographic protection
* Cancelable biometrics

It highlights both the **capabilities and limitations** of feature-based biometric systems and provides a strong foundation for future improvements.

---

⭐ This project demonstrates practical implementation of secure biometric authentication systems.
