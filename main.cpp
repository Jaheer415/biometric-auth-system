#include <iostream>
#include <fstream>
#include <string>
#include <ctime>
#include <windows.h>
#include <cmath>
#include <sstream>
#include <vector>

#include "argon2.h"
#include "sha256.h"
#include "feature_extractor.h"

using namespace std;

// 🔐 Secret keys
const string PEPPER = "MySuperSecretPepper123!";
const string TRANSFORM_KEY = "BiometricSecretKey123";

// ---------------- TRANSFORMATION ----------------
double transformFeature(double value, int index) {
    double key = (int)TRANSFORM_KEY[index % TRANSFORM_KEY.size()];
    return sin(value * key);
}

// ---------------- LOG ----------------
void logEvent(string username, string status) {
    ofstream log("log.txt", ios::app);

    time_t now = time(0);
    string timeStr = ctime(&now);
    timeStr.pop_back();

    log << "User: " << username << " | "
        << status << " | Time: " << timeStr << endl;

    log.close();
}

// ---------------- PARSE + TRANSFORM ----------------
vector<double> parseFeatures(const string& s) {
    vector<double> v;
    string temp;
    stringstream ss(s);

    int index = 0;

    while (getline(ss, temp, ',')) {
        try {
            if (!temp.empty()) {
                double val = stod(temp);

                // 🔥 APPLY TRANSFORMATION HERE
                val = transformFeature(val, index);

                v.push_back(val);
                index++;
            }
        } catch (...) {}
    }
    return v;
}

// ---------------- QUALITY CHECK ----------------
bool isLowQuality(const vector<double>& v) {
    if (v.size() < 4) return true;

    if (v[0] < 0.1) return true;

    return false;
}

// ---------------- SIMILARITY ----------------
double computeSingleSimilarity(const string& a, const string& b) {

    vector<double> v1 = parseFeatures(a);
    vector<double> v2 = parseFeatures(b);

    if (v1.size() != v2.size() || v1.empty())
        return 0;

    if (isLowQuality(v1) || isLowQuality(v2))
        return 0;

    double sum = 0;

    for (int i = 0; i < v1.size(); i++) {

        double weight = 1.0;

        if (i == 0) weight = 2.5;
        else if (i == 1) weight = 2.5;
        else if (i == 2) weight = 2.0;
        else if (i == 3) weight = 2.0;

        sum += weight * abs(v1[i] - v2[i]);
    }

    double avgDiff = sum / (v1.size() * 2.0);

    return exp(-5 * avgDiff);
}

// ---------------- VARIANT MATCH ----------------
double similarityScore(const string& a, const string& b) {

    vector<string> variantsA, variantsB;
    string temp;

    stringstream sa(a), sb(b);

    while (getline(sa, temp, '|')) variantsA.push_back(temp);
    while (getline(sb, temp, '|')) variantsB.push_back(temp);

    double bestScore = 0;

    for (string va : variantsA) {
        for (string vb : variantsB) {

            double score = computeSingleSimilarity(va, vb);

            if (score > bestScore)
                bestScore = score;
        }
    }

    return bestScore;
}

// ---------------- REGISTER ----------------
void registerUser() {

    string username, imagePath;

    cin.ignore();

    cout << "\nEnter username: ";
    getline(cin, username);

    cout << "Enter fingerprint image path: ";
    getline(cin, imagePath);

    string biometric = extractFeatures(imagePath);

    if (biometric == "") {
        cout << "\n[ ERROR ] Could not load image\n";
        return;
    }

    string salt = generateSalt(16);
    string hash = argon2_hash_string(biometric + PEPPER, salt);

    ofstream out("database.txt", ios::app);
    out << username << " " << salt << " " << hash << " " << biometric << endl;
    out.close();

    cout << "\n[ SUCCESS ] User Registered Successfully\n";
}

// ---------------- LOGIN ----------------
void loginUser() {

    string username, imagePath;

    ifstream db("database.txt");
    if (!db) {
        cout << "\n[ ERROR ] Cannot open database\n";
        return;
    }

    cin.ignore();

    cout << "\nEnter username: ";
    getline(cin, username);

    string line;
    bool userFound = false;

    string userSalt, userHash, userBio;

    while (getline(db, line)) {

        stringstream ss(line);

        string dbUser, dbSalt, dbHash, dbBio;
        ss >> dbUser >> dbSalt >> dbHash;
        getline(ss, dbBio);

        if (!dbBio.empty() && dbBio[0] == ' ')
            dbBio = dbBio.substr(1);

        if (dbUser == username) {
            userFound = true;
            userSalt = dbSalt;
            userHash = dbHash;
            userBio = dbBio;
            break;
        }
    }

    db.close();

    if (!userFound) {
        cout << "\n[ ERROR ] User not found\n";
        logEvent(username, "NOT FOUND");
        return;
    }

    int attempts = 0;

    while (attempts < 3) {

        cout << "Enter fingerprint image path: ";
        getline(cin, imagePath);

        string biometric = extractFeatures(imagePath);

        if (biometric == "") {
            cout << "\n[ ERROR ] Could not load image\n";
            return;
        }

        double score = similarityScore(biometric, userBio);

        cout << "Similarity Score: " << score << endl;

        if (score > 0.65) {

            cout << "\n[ SUCCESS ] Authentication Successful\n";
            logEvent(username, "SUCCESS");

            string sessionKey = sha256(userHash + to_string(time(0)));

            cout << "Session Key:\n" << sessionKey << endl;

            Sleep(5000);
            cout << "Session expired\n";

            return;
        }

        attempts++;

        cout << "\n[ FAILED ] Authentication Failed (" << attempts << "/3)\n";
        logEvent(username, "FAILED");
    }

    cout << "\n[ BLOCKED ] Access Blocked\n";
    logEvent(username, "BLOCKED");
}

// ---------------- MAIN ----------------
int main() {

    int choice;

    while (true) {

        cout << "\n==== Biometric Auth System ====\n";
        cout << "1. Register\n2. Login\n3. Exit\n";

        cout << "Choice: ";
        cin >> choice;

        if (choice == 1)
            registerUser();
        else if (choice == 2)
            loginUser();
        else if (choice == 3)
            break;
        else
            cout << "[ ERROR ] Invalid choice\n";
    }

    return 0;
}
