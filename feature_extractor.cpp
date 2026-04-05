#include "feature_extractor.h"
#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/imgproc.hpp>
#include <sstream>

using namespace cv;
using namespace std;


string extractSingle(const Mat& imgInput) {

    Mat img = imgInput.clone();

   
    resize(img, img, Size(128, 128));
    normalize(img, img, 0, 255, NORM_MINMAX);

    GaussianBlur(img, img, Size(5,5), 0);
    equalizeHist(img, img);

   
    Mat binary;
    adaptiveThreshold(img, binary, 255,
        ADAPTIVE_THRESH_GAUSSIAN_C,
        THRESH_BINARY_INV, 11, 2);

    Rect bbox = boundingRect(binary);
    Mat cropped = binary(bbox);
    resize(cropped, cropped, Size(128,128));
    binary = cropped;

   
    GaussianBlur(binary, binary, Size(3,3), 0);

    
    Mat edges;
    Canny(binary, edges, 30, 100);

    double ridgeDensity = countNonZero(binary) / (double)(binary.total());
    double edgeDensity  = countNonZero(edges) / (double)(edges.total());

  
    resize(edges, edges, Size(32, 32));

    int rows = 4;
    int cols = 2;

    int h = edges.rows / rows;
    int w = edges.cols / cols;

    vector<double> regionFeatures;

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {

            Mat region = edges(Rect(j*w, i*h, w, h));

            double ratio = countNonZero(region) / (double)(region.total());
            regionFeatures.push_back(ratio);
        }
    }

    stringstream ss;
    ss << ridgeDensity << "," << edgeDensity;

    for (double v : regionFeatures)
        ss << "," << v;

    return ss.str();
}

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