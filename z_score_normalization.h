#pragma once

#include <vector>

using namespace std;  // 或者在每个 vector 前加上 std::

// 计算均值
double mean(const vector<double>& data);

// 计算标准差
double standard_deviation(const vector<double>& data);

// Z-Score 归一化
vector<double> z_score_normalization(const vector<double>& data);

// 对二维数组的每组数据进行 Z-Score 归一化
vector<vector<double>> normalize_10_array(const vector<vector<double>>& data, int n);
vector<vector<double>> normalize_20_array(const vector<vector<double>>& data, int n);