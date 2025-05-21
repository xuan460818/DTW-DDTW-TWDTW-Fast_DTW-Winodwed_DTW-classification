#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include <cmath>
#include <limits>
#include "classification.h"

using namespace std;
// 定义一个结构体来表示数据集中的一条记录
struct DataRecord {
    int label;               // 标签
    vector<double> features; // 特征向量
};

// 读取数据集文件
vector<DataRecord> readDataset_with_label(const string&filename) {
    ifstream inFile(filename); 
    vector<DataRecord> dataset;

    if (!inFile) {
        cerr << "无法打开文件: " << filename << endl;
        return dataset;
    }

    string line;
    while (getline(inFile, line)) {
        DataRecord record;
        stringstream ss(line); // 使用 stringstream 分割字符串
        double value;

        // 读取标签（第一个值）
        ss >> record.label;

        // 读取特征值
        while (ss >> value) {
            record.features.push_back(value);
        }

        dataset.push_back(record);
    }

    inFile.close();
    return dataset;
}

vector<vector<double>> readDataset_without_label(const string& filename) {
    ifstream inFile(filename);
    vector<vector<double>> dataset;

    if (!inFile) {
        cerr << "无法打开文件: " << filename << endl;
        return dataset;
    }

    string line;
    while (getline(inFile, line)) {
        vector<double> record;
        stringstream ss(line);
        string value;

        // 读取逗号分隔的值
        while (getline(ss, value, ',')) {
            // 将字符串转换为 double
            try {
                double num = stod(value);
                record.push_back(num);
            }
            catch (const invalid_argument& e) {
                cerr << "无法将字符串转换为数字: " << value << endl;
                continue; // 跳过无效值
            }
        }

        // 将当前行的记录添加到数据集中
        if (!record.empty()) {
            dataset.push_back(record);
        }
    }

    inFile.close();
    return dataset;
}

vector<vector<double>> readDataset_without_label_1(const string& filename) {
    //读取空格作为分隔的数据集
    ifstream inFile(filename);
    vector<vector<double>> dataset;

    if (!inFile) {
        cerr << "无法打开文件: " << filename << endl;
        return dataset;
    }

    string line;
    while (getline(inFile, line)) {
        vector<double> record;
        stringstream ss(line);
        double value;

        // 读取空格分隔的值
        while (ss >> value) {
            record.push_back(value);
        }

        // 将当前行的记录添加到数据集中
        if (!record.empty()) {
            dataset.push_back(record);
        }
    }

    inFile.close();
    return dataset;
}

vector<double> readLabelDataset(const string& filename) {
    ifstream inFile(filename);
    vector<double> labels;

    if (!inFile) {
        cerr << "无法打开文件: " << filename << endl;
        return labels;
    }

    string line;
    while (getline(inFile, line)) {
        // 使用 stringstream 读取每行的值
        stringstream ss(line);
        double label;
        if (ss >> label) { // 读取每行的标签
            labels.push_back(label);
        }
        else {
            cerr << "警告: 无法解析行: " << line << endl;
        }
    }

    inFile.close();
    return labels;
}

void savePredictions(const string& filename, const vector<double>& predictions) {
    ofstream outFile(filename);

    if (!outFile) {
        cerr << "无法打开文件: " << filename << endl;
        return;
    }

    // 将每个预测标签逐行写入文件
    for (const auto& label : predictions) {
        outFile << label << endl;
    }

    outFile.close();
    cout << "预测结果已保存到文件: " << filename << endl;
}

