#include "feature_extractor.h"
#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/imgproc.hpp>
#include <sstream>
#include <cmath>

using namespace cv;
using namespace std;

string extractSingle(const Mat& imgInput) {

    Mat img = imgInput.clone();

    resize(img, img, Size(128, 128));
    normalize(img, img, 0, 255, NORM_MINMAX);

    GaussianBlur(img, img, Size(5,5), 0);
    equalizeHist(img, img);

    // Binary
    Mat binary;
    adaptiveThreshold(img, binary, 255,
        ADAPTIVE_THRESH_GAUSSIAN_C,
        THRESH_BINARY_INV, 11, 2);

    // Crop
    Rect bbox = boundingRect(binary);
    Mat cropped = binary(bbox);
    resize(cropped, cropped, Size(128,128));
    binary = cropped;

    GaussianBlur(binary, binary, Size(3,3), 0);

    // Edges
    Mat edges;
    Canny(binary, edges, 30, 100);

    // ---------------- BASIC FEATURES ----------------
    double ridgeDensity = countNonZero(binary) / (double)(binary.total());
    double edgeDensity  = countNonZero(edges) / (double)(edges.total());

    // ---------------- GRADIENT ----------------
    Mat gradX, gradY;
    Sobel(img, gradX, CV_32F, 1, 0);
    Sobel(img, gradY, CV_32F, 0, 1);

    Mat magnitude, angle;
    cartToPolar(gradX, gradY, magnitude, angle, true);

    Scalar avgMag = mean(magnitude);
    Scalar avgAngle = mean(angle);

    double gradMagnitude = avgMag[0] / 255.0;  // normalized

    // Cosine orientation (important fix)
    double orientation = cos(avgAngle[0] * CV_PI / 180.0);

    // Resize for grid
    resize(edges, edges, Size(64, 64));
    resize(angle, angle, Size(64, 64));

    // ---------------- 6x6 GRID ----------------
    int rows = 6;
    int cols = 6;

    int h = edges.rows / rows;
    int w = edges.cols / cols;

    vector<double> regionFeatures;

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {

            Rect r(j*w, i*h, w, h);

            Mat regionEdge = edges(r);
            Mat regionAngle = angle(r);

            double edgeRatio = countNonZero(regionEdge) / (double)(regionEdge.total());

            Scalar meanAngle = mean(regionAngle);

            // Cosine orientation (local)
            double localOrientation = cos(meanAngle[0] * CV_PI / 180.0);

            regionFeatures.push_back(edgeRatio);
            regionFeatures.push_back(localOrientation);
        }
    }

    // ---------------- FINAL FEATURE STRING ----------------
    stringstream ss;

    ss << ridgeDensity << "," << edgeDensity << ","
       << gradMagnitude << "," << orientation;

    for (double v : regionFeatures)
        ss << "," << v;

    return ss.str();
}

// ---------------- MULTI-VARIANT ----------------
string extractFeatures(const string& imagePath) {

    Mat img = imread(imagePath, IMREAD_GRAYSCALE);
    if (img.empty()) return "";

    vector<string> featureVariants;

    Mat base = img.clone();
    for (int i = 0; i < 4; i++) {
        featureVariants.push_back(extractSingle(base));
        rotate(base, base, ROTATE_90_CLOCKWISE);
    }

    Mat flipped;
    flip(img, flipped, 0);

    for (int i = 0; i < 4; i++) {
        featureVariants.push_back(extractSingle(flipped));
        rotate(flipped, flipped, ROTATE_90_CLOCKWISE);
    }

    string result = "";
    for (int i = 0; i < featureVariants.size(); i++) {
        result += featureVariants[i];
        if (i != featureVariants.size() - 1)
            result += "|";
    }

    return result;
}
