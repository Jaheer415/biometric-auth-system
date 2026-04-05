# biometric-auth-system
Biometric fingerprint authentication system using OpenCV and Argon2 hashing
# 🔐 Biometric Authentication System (Fingerprint-Based)

A C++ based biometric authentication system that uses fingerprint images for secure user registration and login. The system combines **image processing (OpenCV)** with **secure cryptographic hashing (Argon2 + SHA-256)** to provide a robust authentication pipeline.

---

## 🚀 Features

- 📷 Fingerprint-based authentication  
- 🧠 Feature extraction using image processing  
- 🔄 Rotation and flip invariant matching  
- 🧩 Multi-region feature vector analysis  
- 🔐 Secure storage using:
  - Argon2 hashing  
  - Unique salt per user  
  - Global pepper  
- 🚫 Duplicate user and fingerprint prevention  
- 🔑 Session key generation using SHA-256  
- 📜 Logging system for authentication events  

---

## 🧠 System Workflow

Fingerprint Image  
↓  
Preprocessing (Grayscale, Blur, Threshold, Edge Detection)  
↓  
Feature Extraction (Density + Region Features)  
↓  
Feature Vector  
↓  
Similarity Calculation  
↓  
Threshold Decision  
↓  
Authentication Result  
↓  
Secure Storage (Argon2 + Salt + Pepper)  

---

## 🛠️ Tech Stack

- **Language:** C++  
- **Libraries:** OpenCV, Argon2, Windows CryptoAPI  

### Concepts Used:
- Image Processing  
- Feature Extraction  
- Similarity Scoring  
- Cryptography (Hashing, Salt, Pepper)  

---

## 📊 Feature Extraction Details

The system extracts a feature vector consisting of:

- Ridge density  
- Edge density  
- Region-based spatial distribution (grid analysis)  
- Rotation and flip variants for robustness  

---

## 🔍 Matching Logic

- Uses an **exponential similarity function**  
- Compares multiple rotated and flipped feature variants  
- Authentication is successful if:

Similarity Score > 0.58  

---

## 🔐 Security Design

- **Argon2 hashing** for secure storage  
- **Salt** (unique per user) to prevent rainbow table attacks  
- **Pepper** (secret key) for additional protection  
- **SHA-256** used for session key generation  

---

## 📁 Project Structure

.
├── main.cpp  
├── feature_extractor.cpp  
├── feature_extractor.h  
├── argon2.cpp  
├── argon2.h  
├── sha256.cpp  
├── sha256.h  
├── README.md  
├── .gitignore  

---

## ⚙️ How to Run

### 1. Compile

g++ main.cpp argon2.cpp sha256.cpp feature_extractor.cpp -I <OpenCV_INCLUDE_PATH> -L <OpenCV_LIB_PATH> -lopencv_core455 -lopencv_imgcodecs455 -lopencv_imgproc455 -largon2 -o app.exe

### 2. Run

./app.exe  

---

## ⚠️ Limitations

- Sensitive to large variations in fingerprint placement  
- Not a full minutiae-based system (no ridge endings/bifurcations detection)  
- Works best with consistent image quality  
- Threshold tuning required for different datasets  

---

## 🚀 Future Improvements

- Minutiae-based fingerprint extraction  
- Machine learning / deep learning integration  
- Better rotation and scale invariance  
- GUI-based interface  
- Encrypted biometric template storage  

---

## 👨‍💻 Author

**Udayagiri Jaheer**

---

## 📌 Note

This project is developed for academic and learning purposes, demonstrating the integration of **biometrics, security, and image processing**.
