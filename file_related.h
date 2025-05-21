#ifndef FILE_RELATED_H
#define FILE_RELATED_H
struct DataRecord {
    int label;               // ��ǩ
    vector<double> features; // ��������
};

vector<double> readLabelDataset(const string& filename);
vector<DataRecord> readDataset_with_label(const string& filename);
vector<vector<double>> readDataset_without_label(const string& filename);
vector<vector<double>> readDataset_without_label_1(const string& filename);
void savePredictions(const string& filename, const vector<double>& predictions);


#endif //FILE_RELATED_H

#pragma once
