#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>
#include <string>
#include <sstream>
#include <cmath>
#include <numeric>
#include <limits>
#include "classification.h"
using namespace std;

vector<vector<pair<double, size_t>>> computeClosestDatas(
    const vector<vector<double>>& datas,
    const vector<vector<double>>& coords,
    double max_distance = 100.0)
{
    vector<vector<pair<double, size_t>>> result(datas.size());

    for (size_t i = 0; i < coords.size(); ++i) {
        for (size_t j = 0; j < coords.size(); ++j) {
            if (i == j) continue;

            double dist = sqrt(pow(coords[i][0] - coords[j][0], 2) +
                pow(coords[i][1] - coords[j][1], 2));
            if (dist <= max_distance) {
                result[i].emplace_back(dist, j);
            }
        }
    }
    return result;
}

vector<vector<double>> expand_12_coord(const vector<vector<double>>& data, const vector<vector<double>>& coordinates) {
    vector<vector<double>> expanded_data;  // �洢��չ��Ķ�ά����
    for (size_t row_idx = 0; row_idx < data.size(); ++row_idx) {
        const auto& row = data[row_idx];
        const auto& coord = coordinates[row_idx];  // ��ȡ��ǰ�е�����
        vector<double> expanded_row;  // �洢��չ�����
        for (size_t i = 0; i < row.size(); i += 10) {
            // ��ȡÿ�� 10 ����
            vector<double> group(row.begin() + i, row.begin() + i + 10);
            // �������ֵ��Ϊ�� 11 �͵� 12 ����
            group.push_back(coord[0]);  // ��ӵ�һ������ֵ
            group.push_back(coord[1]); // ��ӵڶ�������ֵ
            // ����չ�������ӵ���չ�����
            expanded_row.insert(expanded_row.end(), group.begin(), group.end());
        }
        // ����չ�������ӵ���չ��Ķ�ά����
        expanded_data.push_back(expanded_row);
    }
    return expanded_data;
}

vector<vector<double>> expand_20_dimension(
    const vector<vector<double>>& datas,
    const vector<vector<double>>& coords)
{
    // ��������Ƿ���Ч
    if (datas.empty() || coords.empty()) {
        return {};
    }
    if (datas.size() != coords.size()) {
        throw runtime_error("����������������ƥ��");
    }

    // ����ÿ���㸽������С��20�������ھӼ������
    // �޸ķ�������Ϊ: vector<vector<pair<double, size_t>>>
    vector<vector<pair<double, size_t>>> neighbors_info = computeClosestDatas(datas, coords,100);

    vector<vector<double>> expanded_data;
    expanded_data.reserve(datas.size()); // Ԥ����ռ�

    for (size_t row_idx = 0; row_idx < datas.size(); ++row_idx) {
        const auto& row = datas[row_idx];
        if (row.size() != 10 * 23) {
            throw runtime_error("�����б�����230ά(23���10ά)");
        }

        // ��ȡ��ǰ��������ھ���Ϣ
        const auto& current_neighbors = neighbors_info[row_idx];

       /* // ����Ȩ�أ�ʹ�þ���ĵ�����
        double sum_inv_dist = 0.0;
        vector<double> weights;
        weights.reserve(current_neighbors.size());

        for (const auto& neighbor : current_neighbors) {
            double dist = neighbor.first;
            if (dist <= 0) {
                throw runtime_error("���ַ�������ֵ: " + to_string(dist));
            }
            double inv_dist = 1.0 / dist;
            weights.push_back(inv_dist);
            sum_inv_dist += inv_dist;
        }

        // ��һ��Ȩ��
        if (sum_inv_dist > 0) {
            for (double& w : weights) {
                w /= sum_inv_dist;
            }
        }*/

        vector<double> expanded_row;
        expanded_row.reserve(23 * 20); // Ԥ����ռ�

        // ����ÿһ�飨��23�飩
        for (size_t group_idx = 0; group_idx < 23; ++group_idx) {
            size_t start_pos = group_idx * 10;

            // ԭʼ���ݣ�10ά��
            expanded_row.insert(expanded_row.end(),
                row.begin() + start_pos,
                row.begin() + start_pos + 10);

            // ������10ά����Ȩ�ھӣ�
            if (!current_neighbors.empty()) {
                for (size_t dim = 0; dim < 10; ++dim) {
                    double weighted_sum = 0.0;
                    for (size_t i = 0; i < current_neighbors.size(); ++i) {
                        size_t neighbor_idx = current_neighbors[i].second;
                        if (start_pos + dim >= datas[neighbor_idx].size()) {
                            throw runtime_error("�ھ�����ά�Ȳ�ƥ��");
                        }
                        //weighted_sum += weights[i] * datas[neighbor_idx][start_pos + dim];
                        weighted_sum +=  datas[neighbor_idx][start_pos + dim]/ current_neighbors.size();

                    }
                    expanded_row.push_back(weighted_sum);
                }
            }
            else {
                // ���û���ھӣ����0��ԭʼֵ
                expanded_row.insert(expanded_row.end(), 10, 0.0);
            }
        }

        expanded_data.push_back(move(expanded_row));
    }

    return expanded_data;
}

vector<vector<double>> expand_22_coord(const vector<vector<double>>& data, const vector<vector<double>>& coordinates) {
    vector<vector<double>> expanded_data;  // �洢��չ��Ķ�ά����
    for (size_t row_idx = 0; row_idx < data.size(); ++row_idx) {
        const auto& row = data[row_idx];
        const auto& coord = coordinates[row_idx];  // ��ȡ��ǰ�е�����
        vector<double> expanded_row;  // �洢��չ�����
        for (size_t i = 0; i < row.size(); i += 20) {
            // ��ȡÿ�� 20 ����
            vector<double> group(row.begin() + i, row.begin() + i + 20);
            // �������ֵ��Ϊ�� 21 �͵� 22 ����
            group.push_back(coord[0]);  // ��ӵ�һ������ֵ
            group.push_back(coord[1]); // ��ӵڶ�������ֵ
            // ����չ�������ӵ���չ�����
            expanded_row.insert(expanded_row.end(), group.begin(), group.end());
        }
        // ����չ�������ӵ���չ��Ķ�ά����
        expanded_data.push_back(expanded_row);
    }
    return expanded_data;
}