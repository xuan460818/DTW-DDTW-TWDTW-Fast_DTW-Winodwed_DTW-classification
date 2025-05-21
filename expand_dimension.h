#pragma once
#include <vector>
#include "classification.h"
using namespace std;

vector<vector<pair<double, size_t>>> computeClosestDatas(
    const vector<vector<double>>& datas,
    const vector<vector<double>>& coords,
    double max_distance = 100.0);
//计算最近的5个数据。
vector<vector<double>> expand_12_coord(
    const vector<vector<double>>& data, 
    const vector<vector<double>>& coordinates);
//在10维数据上添加坐标x,y
vector <vector<double>> expand_20_dimension(
    const vector<vector<double>>& datas,
    const vector<vector<double>>& coords);

//在10维的基础上，经过距离加权得到20维数据
vector<vector<double>> expand_22_coord(
    const vector<vector<double>>& data, 
    const vector<vector<double>>& coordinates);
//在20维后面加上坐标x,y