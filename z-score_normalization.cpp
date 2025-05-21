#include <iostream>
#include <vector>
#include <numeric>
#include <cmath>

using namespace std;

// 计算均值
double mean(const vector<double>& data) {
    double sum = accumulate(data.begin(), data.end(), 0.0);
    return sum / data.size();
}

// 计算标准差
double standard_deviation(const vector<double>& data) {
    double mu = mean(data);
    double sum = 0.0;
    for (double value : data) {
        sum += pow(value - mu, 2);
    }
    return sqrt(sum / data.size());
}

// Z-Score 归一化
vector<double> z_score_normalization(const vector<double>& data) {
    vector<double> normalized_data;
    double mu = mean(data);
    double sigma = standard_deviation(data);

    // 避免除零错误
    if (sigma == 0) {
        normalized_data = data;  // 如果标准差为 0，直接返回原数据
        return normalized_data;
    }

    for (double value : data) {
        double normalized_value = (value - mu) / sigma;
        normalized_data.push_back(normalized_value);
    }

    return normalized_data;
}
vector<vector<double>> normalize_10_array(const vector<vector<double>>& data , int n) {
    vector<vector<double>> normalized_data;  // 存储归一化后的二维数组
    for (const auto& row : data) {
        vector<double> normalized_row;  // 存储归一化后的行
        for (size_t i = 0; i < row.size(); i += 10+n) {
            // 提取每组 12 个数
            vector<double> group(row.begin() + i, row.begin() + i + 10+n);
            // 对每组进行 Z-Score 归一化
            vector<double> normalized_group = z_score_normalization(group);
            // 将归一化后的组添加到归一化后的行
            normalized_row.insert(normalized_row.end(), normalized_group.begin(), normalized_group.end());
        }
        // 将归一化后的行添加到归一化后的二维数组
        normalized_data.push_back(normalized_row);
    }
    return normalized_data;
}

vector<vector<double>> normalize_20_array(const vector<vector<double>>& data, int n) {
    vector<vector<double>> normalized_data;  // 存储归一化后的二维数组
    for (const auto& row : data) {
        vector<double> normalized_row;  // 存储归一化后的行
        for (size_t i = 0; i < row.size(); i += 20 + n) {
            // 提取每组 22 个数
            vector<double> group(row.begin() + i, row.begin() + i + 20 + n);
            // 对每组进行 Z-Score 归一化
            vector<double> normalized_group = z_score_normalization(group);
            // 将归一化后的组添加到归一化后的行
            normalized_row.insert(normalized_row.end(), normalized_group.begin(), normalized_group.end());
        }
        // 将归一化后的行添加到归一化后的二维数组
        normalized_data.push_back(normalized_row);
    }
    return normalized_data;
}