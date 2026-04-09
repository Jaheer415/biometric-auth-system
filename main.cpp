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
#include "crypto.h"

using namespace std;

const string PEPPER = "MySuperSecretPepper123!";

// Logging
void logEvent(string username, string status) {
    ofstream log("log.txt", ios::app);

    time_t now = time(0);
    string timeStr = ctime(&now);
    timeStr.pop_back();

    log << "User: " << username << " | "
        << status << " | Time: " << timeStr << endl;

    log.close();
}

// Similarity functions (same as before)
double computeSingleSimilarity(const string& a, const string& b) {
    vector<double> v1, v2;
    string temp;

    stringstream ss1(a), ss2(b);

    while (getline(ss1, temp, ',')) v1.push_back(stod(temp));
    while (getline(ss2, temp, ',')) v2.push_back(stod(temp));

    if (v1.size() != v2.size()) return 0;

    double sum = 0;
    for (int i = 0; i < v1.size(); i++) {
        sum += abs(v1[i] - v2[i]);
    }

    double avgDiff = sum / v1.size();
    return exp(-10 * avgDiff);
}

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

// REGISTER
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

    ifstream db("database.txt");
    string line;

    while (getline(db, line)) {
        stringstream ss(line);

        string dbUser, dbSalt, dbHash, dbBioEnc;
        ss >> dbUser >> dbSalt >> dbHash;
        getline(ss, dbBioEnc);

        if (!dbBioEnc.empty() && dbBioEnc[0] == ' ')
            dbBioEnc = dbBioEnc.substr(1);

        string dbBio = encryptDecrypt(dbBioEnc, PEPPER); // 🔓 decrypt

        if (dbUser == username) {
            cout << "\n[ ERROR ] Username already exists\n";
            return;
        }

        double score = similarityScore(biometric, dbBio);
        if (score > 0.90) {
            cout << "\n[ ERROR ] Fingerprint already registered\n";
            return;
        }
    }

    db.close();

    string salt = generateSalt(16);
    string hash = argon2_hash_string(biometric + PEPPER, salt);

    string encryptedBio = encryptDecrypt(biometric, PEPPER); // 🔐 encrypt

    ofstream out("database.txt", ios::app);
    out << username << " " << salt << " " << hash << " " << encryptedBio << endl;
    out.close();

    cout << "\n[ SUCCESS ] User Registered Successfully\n";
}

// LOGIN
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

        string dbUser, dbSalt, dbHash, dbBioEnc;
        ss >> dbUser >> dbSalt >> dbHash;
        getline(ss, dbBioEnc);

        if (!dbBioEnc.empty() && dbBioEnc[0] == ' ')
            dbBioEnc = dbBioEnc.substr(1);

        if (dbUser == username) {
            userFound = true;
            userSalt = dbSalt;
            userHash = dbHash;
            userBio = encryptDecrypt(dbBioEnc, PEPPER); // 🔓 decrypt
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

        if (score > 0.58) {

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

// MAIN
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