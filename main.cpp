#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include <cmath>
#include <limits>
#include <algorithm>
#include <thread>
#include "classification.h"
#include "file_related.h"
#include "z_score_normalization.h"
#include "expand_dimension.h"
using namespace std;

vector<double> classifyTestSet(const vector<vector<double>>& seg1, const vector<vector<double>>& seg2, const vector<double>& trainClass) {
    vector<double> predictions;
    for (size_t j = 0; j < seg2.size(); ++j) {
        double minDistance = numeric_limits<double>::max();
        double nearestLabel = -1.0;

        for (size_t i = 0; i < seg1.size(); ++i) {
            double distance = euclideanDistance(seg1[i], seg2[j]);
            if (distance < minDistance) {
                minDistance = distance;
                nearestLabel = trainClass[i];
            }
        }
        cout <<"Processed test sample:" << j <<"   Predicted class:" << nearestLabel << endl;
        predictions.push_back(nearestLabel);
    }

    return predictions;
}

int main() {
    string train_first = "E:/develop/learning_python/tr_selected_value.txt";
    string train_second = "E:/develop/learning_python/tr_selected_class.txt";
    string train_third = "E:/develop/learning_python/tr_selected_coord.txt";
    string test_first = "E:/develop/learning_python/te_selected_value.txt";
    string test_second = "E:/develop/learning_python/te_selected_class.txt";
    string test_third = "E:/develop/learning_python/te_selected_coord.txt";
    vector<vector<double>> train_value = readDataset_without_label_1(train_first);
    vector<double> train_class = readLabelDataset(train_second);
    vector<vector<double>> train_coord = readDataset_without_label_1(train_third);
    vector<vector<double>> test_value = readDataset_without_label_1(test_first);
    vector<double> test_class = readLabelDataset(test_second);
    vector<vector<double>> test_coord = readDataset_without_label_1(test_third);

    //vector<vector<double>>extended_coord_train_data = expand_12_coord(train_value, train_coord);
    //vector<vector<double>>extended_coord_test_data = expand_12_coord(test_value, test_coord);
    //vector<vector<double>>normalized_12_coord_train_data = normalize_10_array(train_value,0);
    //vector<vector<double>>normalized_12_coord_test_data = normalize_10_array(test_value,0);
    //将原数据10维扩大至20维
    vector<vector<double>> expand_20_train_data = expand_20_dimension(train_value, train_coord);
    vector<vector<double>> expand_20_test_data = expand_20_dimension(test_value,test_coord);

    /*for (size_t i = 0; i < 3; ++i) {
        for (size_t j = 0; j < expand_20_train_data[0].size(); ++j) {
            cout << expand_20_train_data[i][j] << "  ";
        }
        cout<<endl;
    }
    for (size_t i = 0; i < 3; ++i) {
        for (size_t j = 0; j < expand_20_test_data[0].size(); ++j) {
            cout 
                << expand_20_test_data[i][j] << "  ";
        }
        cout << endl;
    }*/
    //在20维后面加上坐标
    vector<vector<double>> expand_22_train_data = expand_22_coord(expand_20_train_data, train_coord);
    vector<vector<double>> expand_22_test_data = expand_22_coord(expand_20_test_data, test_coord);

    vector < vector<double>> normalized_22_train_data = normalize_20_array(expand_22_train_data, 2);
    vector < vector<double>> normalized_22_test_data = normalize_20_array(expand_22_test_data, 2);
    //归一化数据

    vector<double> predictions = classifyTestSet(normalized_22_train_data, normalized_22_test_data, train_class);

    string outputFile = "E:/develop/learning_python/results/space_information/eu_average.txt";
    savePredictions(outputFile, predictions);
    
    return 0;


}