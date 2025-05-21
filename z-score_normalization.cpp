#include <iostream>
#include <vector>
#include <numeric>
#include <cmath>

using namespace std;

// �����ֵ
double mean(const vector<double>& data) {
    double sum = accumulate(data.begin(), data.end(), 0.0);
    return sum / data.size();
}

// �����׼��
double standard_deviation(const vector<double>& data) {
    double mu = mean(data);
    double sum = 0.0;
    for (double value : data) {
        sum += pow(value - mu, 2);
    }
    return sqrt(sum / data.size());
}

// Z-Score ��һ��
vector<double> z_score_normalization(const vector<double>& data) {
    vector<double> normalized_data;
    double mu = mean(data);
    double sigma = standard_deviation(data);

    // ����������
    if (sigma == 0) {
        normalized_data = data;  // �����׼��Ϊ 0��ֱ�ӷ���ԭ����
        return normalized_data;
    }

    for (double value : data) {
        double normalized_value = (value - mu) / sigma;
        normalized_data.push_back(normalized_value);
    }

    return normalized_data;
}
vector<vector<double>> normalize_10_array(const vector<vector<double>>& data , int n) {
    vector<vector<double>> normalized_data;  // �洢��һ����Ķ�ά����
    for (const auto& row : data) {
        vector<double> normalized_row;  // �洢��һ�������
        for (size_t i = 0; i < row.size(); i += 10+n) {
            // ��ȡÿ�� 12 ����
            vector<double> group(row.begin() + i, row.begin() + i + 10+n);
            // ��ÿ����� Z-Score ��һ��
            vector<double> normalized_group = z_score_normalization(group);
            // ����һ���������ӵ���һ�������
            normalized_row.insert(normalized_row.end(), normalized_group.begin(), normalized_group.end());
        }
        // ����һ���������ӵ���һ����Ķ�ά����
        normalized_data.push_back(normalized_row);
    }
    return normalized_data;
}

vector<vector<double>> normalize_20_array(const vector<vector<double>>& data, int n) {
    vector<vector<double>> normalized_data;  // �洢��һ����Ķ�ά����
    for (const auto& row : data) {
        vector<double> normalized_row;  // �洢��һ�������
        for (size_t i = 0; i < row.size(); i += 20 + n) {
            // ��ȡÿ�� 22 ����
            vector<double> group(row.begin() + i, row.begin() + i + 20 + n);
            // ��ÿ����� Z-Score ��һ��
            vector<double> normalized_group = z_score_normalization(group);
            // ����һ���������ӵ���һ�������
            normalized_row.insert(normalized_row.end(), normalized_group.begin(), normalized_group.end());
        }
        // ����һ���������ӵ���һ����Ķ�ά����
        normalized_data.push_back(normalized_row);
    }
    return normalized_data;
}