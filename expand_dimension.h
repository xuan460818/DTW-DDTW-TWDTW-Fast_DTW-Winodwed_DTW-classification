#pragma once
#include <vector>
#include "classification.h"
using namespace std;

vector<vector<pair<double, size_t>>> computeClosestDatas(
    const vector<vector<double>>& datas,
    const vector<vector<double>>& coords,
    double max_distance = 100.0);
//���������5�����ݡ�
vector<vector<double>> expand_12_coord(
    const vector<vector<double>>& data, 
    const vector<vector<double>>& coordinates);
//��10ά�������������x,y
vector <vector<double>> expand_20_dimension(
    const vector<vector<double>>& datas,
    const vector<vector<double>>& coords);

//��10ά�Ļ����ϣ����������Ȩ�õ�20ά����
vector<vector<double>> expand_22_coord(
    const vector<vector<double>>& data, 
    const vector<vector<double>>& coordinates);
//��20ά�����������x,y