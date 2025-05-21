#pragma once

#include <vector>

using namespace std;  // ������ÿ�� vector ǰ���� std::

// �����ֵ
double mean(const vector<double>& data);

// �����׼��
double standard_deviation(const vector<double>& data);

// Z-Score ��һ��
vector<double> z_score_normalization(const vector<double>& data);

// �Զ�ά�����ÿ�����ݽ��� Z-Score ��һ��
vector<vector<double>> normalize_10_array(const vector<vector<double>>& data, int n);
vector<vector<double>> normalize_20_array(const vector<vector<double>>& data, int n);