#ifndef CLASSIFICATION_H
#define CLASSIFICATION_H

#include <vector>
using namespace std;

double euclideanDistance(const vector<double>& v1, const vector<double>& v2);
double dtwDistance(const vector<double>& x, const vector<double>& y);
double fastdtw(const vector<double>& seq1, const vector<double>& seq2, int radius);
double twdtw(const vector<double>& series1, const vector<double>& series2, double lambda);
vector<double> computeDerivative(const vector<double>& seg);
double ddtw(const vector<double>& seg1, const vector<double>& seg2);
double windowed_dtw(const vector<double>& seq1, const vector<double>& seq2, int windowSize);

#endif // CLASSIFICATION_H


#pragma once
