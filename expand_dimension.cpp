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
    vector<vector<double>> expanded_data;  // 存储扩展后的二维数组
    for (size_t row_idx = 0; row_idx < data.size(); ++row_idx) {
        const auto& row = data[row_idx];
        const auto& coord = coordinates[row_idx];  // 获取当前行的坐标
        vector<double> expanded_row;  // 存储扩展后的行
        for (size_t i = 0; i < row.size(); i += 10) {
            // 提取每组 10 个数
            vector<double> group(row.begin() + i, row.begin() + i + 10);
            // 添加坐标值作为第 11 和第 12 个数
            group.push_back(coord[0]);  // 添加第一个坐标值
            group.push_back(coord[1]); // 添加第二个坐标值
            // 将扩展后的组添加到扩展后的行
            expanded_row.insert(expanded_row.end(), group.begin(), group.end());
        }
        // 将扩展后的行添加到扩展后的二维数组
        expanded_data.push_back(expanded_row);
    }
    return expanded_data;
}

vector<vector<double>> expand_20_dimension(
    const vector<vector<double>>& datas,
    const vector<vector<double>>& coords)
{
    // 检查输入是否有效
    if (datas.empty() || coords.empty()) {
        return {};
    }
    if (datas.size() != coords.size()) {
        throw runtime_error("数据与坐标数量不匹配");
    }

    // 计算每个点附近距离小于20的所有邻居及其距离
    // 修改返回类型为: vector<vector<pair<double, size_t>>>
    vector<vector<pair<double, size_t>>> neighbors_info = computeClosestDatas(datas, coords,100);

    vector<vector<double>> expanded_data;
    expanded_data.reserve(datas.size()); // 预分配空间

    for (size_t row_idx = 0; row_idx < datas.size(); ++row_idx) {
        const auto& row = datas[row_idx];
        if (row.size() != 10 * 23) {
            throw runtime_error("数据行必须是230维(23组×10维)");
        }

        // 获取当前点的所有邻居信息
        const auto& current_neighbors = neighbors_info[row_idx];

       /* // 计算权重（使用距离的倒数）
        double sum_inv_dist = 0.0;
        vector<double> weights;
        weights.reserve(current_neighbors.size());

        for (const auto& neighbor : current_neighbors) {
            double dist = neighbor.first;
            if (dist <= 0) {
                throw runtime_error("发现非正距离值: " + to_string(dist));
            }
            double inv_dist = 1.0 / dist;
            weights.push_back(inv_dist);
            sum_inv_dist += inv_dist;
        }

        // 归一化权重
        if (sum_inv_dist > 0) {
            for (double& w : weights) {
                w /= sum_inv_dist;
            }
        }*/

        vector<double> expanded_row;
        expanded_row.reserve(23 * 20); // 预分配空间

        // 处理每一组（共23组）
        for (size_t group_idx = 0; group_idx < 23; ++group_idx) {
            size_t start_pos = group_idx * 10;

            // 原始数据（10维）
            expanded_row.insert(expanded_row.end(),
                row.begin() + start_pos,
                row.begin() + start_pos + 10);

            // 新增的10维（加权邻居）
            if (!current_neighbors.empty()) {
                for (size_t dim = 0; dim < 10; ++dim) {
                    double weighted_sum = 0.0;
                    for (size_t i = 0; i < current_neighbors.size(); ++i) {
                        size_t neighbor_idx = current_neighbors[i].second;
                        if (start_pos + dim >= datas[neighbor_idx].size()) {
                            throw runtime_error("邻居数据维度不匹配");
                        }
                        //weighted_sum += weights[i] * datas[neighbor_idx][start_pos + dim];
                        weighted_sum +=  datas[neighbor_idx][start_pos + dim]/ current_neighbors.size();

                    }
                    expanded_row.push_back(weighted_sum);
                }
            }
            else {
                // 如果没有邻居，填充0或原始值
                expanded_row.insert(expanded_row.end(), 10, 0.0);
            }
        }

        expanded_data.push_back(move(expanded_row));
    }

    return expanded_data;
}

vector<vector<double>> expand_22_coord(const vector<vector<double>>& data, const vector<vector<double>>& coordinates) {
    vector<vector<double>> expanded_data;  // 存储扩展后的二维数组
    for (size_t row_idx = 0; row_idx < data.size(); ++row_idx) {
        const auto& row = data[row_idx];
        const auto& coord = coordinates[row_idx];  // 获取当前行的坐标
        vector<double> expanded_row;  // 存储扩展后的行
        for (size_t i = 0; i < row.size(); i += 20) {
            // 提取每组 20 个数
            vector<double> group(row.begin() + i, row.begin() + i + 20);
            // 添加坐标值作为第 21 和第 22 个数
            group.push_back(coord[0]);  // 添加第一个坐标值
            group.push_back(coord[1]); // 添加第二个坐标值
            // 将扩展后的组添加到扩展后的行
            expanded_row.insert(expanded_row.end(), group.begin(), group.end());
        }
        // 将扩展后的行添加到扩展后的二维数组
        expanded_data.push_back(expanded_row);
    }
    return expanded_data;
}