#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include <cmath>
#include <limits>
#include "classification.h"

using namespace std;
// ����һ���ṹ������ʾ���ݼ��е�һ����¼
struct DataRecord {
    int label;               // ��ǩ
    vector<double> features; // ��������
};

// ��ȡ���ݼ��ļ�
vector<DataRecord> readDataset_with_label(const string&filename) {
    ifstream inFile(filename); 
    vector<DataRecord> dataset;

    if (!inFile) {
        cerr << "�޷����ļ�: " << filename << endl;
        return dataset;
    }

    string line;
    while (getline(inFile, line)) {
        DataRecord record;
        stringstream ss(line); // ʹ�� stringstream �ָ��ַ���
        double value;

        // ��ȡ��ǩ����һ��ֵ��
        ss >> record.label;

        // ��ȡ����ֵ
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
        cerr << "�޷����ļ�: " << filename << endl;
        return dataset;
    }

    string line;
    while (getline(inFile, line)) {
        vector<double> record;
        stringstream ss(line);
        string value;

        // ��ȡ���ŷָ���ֵ
        while (getline(ss, value, ',')) {
            // ���ַ���ת��Ϊ double
            try {
                double num = stod(value);
                record.push_back(num);
            }
            catch (const invalid_argument& e) {
                cerr << "�޷����ַ���ת��Ϊ����: " << value << endl;
                continue; // ������Чֵ
            }
        }

        // ����ǰ�еļ�¼��ӵ����ݼ���
        if (!record.empty()) {
            dataset.push_back(record);
        }
    }

    inFile.close();
    return dataset;
}

vector<vector<double>> readDataset_without_label_1(const string& filename) {
    //��ȡ�ո���Ϊ�ָ������ݼ�
    ifstream inFile(filename);
    vector<vector<double>> dataset;

    if (!inFile) {
        cerr << "�޷����ļ�: " << filename << endl;
        return dataset;
    }

    string line;
    while (getline(inFile, line)) {
        vector<double> record;
        stringstream ss(line);
        double value;

        // ��ȡ�ո�ָ���ֵ
        while (ss >> value) {
            record.push_back(value);
        }

        // ����ǰ�еļ�¼��ӵ����ݼ���
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
        cerr << "�޷����ļ�: " << filename << endl;
        return labels;
    }

    string line;
    while (getline(inFile, line)) {
        // ʹ�� stringstream ��ȡÿ�е�ֵ
        stringstream ss(line);
        double label;
        if (ss >> label) { // ��ȡÿ�еı�ǩ
            labels.push_back(label);
        }
        else {
            cerr << "����: �޷�������: " << line << endl;
        }
    }

    inFile.close();
    return labels;
}

void savePredictions(const string& filename, const vector<double>& predictions) {
    ofstream outFile(filename);

    if (!outFile) {
        cerr << "�޷����ļ�: " << filename << endl;
        return;
    }

    // ��ÿ��Ԥ���ǩ����д���ļ�
    for (const auto& label : predictions) {
        outFile << label << endl;
    }

    outFile.close();
    cout << "Ԥ�����ѱ��浽�ļ�: " << filename << endl;
}

