#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>
#include <string>
#include <sstream>
#include <cmath>
#include <limits>
using namespace std;

double euclideanDistance(const vector<double>& v1, const vector<double>& v2) {
    double distance = 0.0;
    for (size_t i = 0; i < v1.size(); ++i) {
        distance += pow(v1[i] - v2[i], 2);
    }
    return sqrt(distance);
}

double dtwDistance(const vector<double>& x, const vector<double>& y) {
    size_t n = x.size();
    size_t m = y.size();

    // ������̬�滮��
    vector<vector<double>> dp(n + 1, vector<double>(m + 1, numeric_limits<double>::max()));

    // ��ʼ�����
    dp[0][0] = 0;

    // ��䶯̬�滮��
    for (size_t i = 1; i <= n; ++i) {
        for (size_t j = 1; j <= m; ++j) {
            double cost = abs(x[i - 1] - y[j - 1]); 
            dp[i][j] = cost + min({ dp[i - 1][j], dp[i][j - 1], dp[i - 1][j - 1] }); // ѡ����С·��
        }
    }
    return dp[n][m]; // ���� DTW ����
}

double euclideanDistance(double x, double y) {
    return (x - y) * (x - y); // ƽ�����룬���⿪��,ʱ�����
}
double twdtw(const vector<double>& series1, const vector<double>& series2, double lambda) {
    int n = series1.size();
    int m = series2.size();
    //lambdaһ��ȡ0.1
    // ʹ��һά����洢�������
    vector<double> dtw((n + 1) * (m + 1), numeric_limits<double>::max());
    dtw[0] = 0; // ��ʼ���߽�����

    // Ԥ����ʱ��Ȩ��
    vector<double> timeWeights(n * m);
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= m; ++j) {
            timeWeights[(i - 1) * m + (j - 1)] = exp(-lambda * abs(i - j));
        }
    }
    // ���DTW����
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= m; ++j) {
            double cost = euclideanDistance(series1[i - 1], series2[j - 1]);
            cost *= timeWeights[(i - 1) * m + (j - 1)]; // Ӧ��ʱ��Ȩ��
            // �ҵ���С��·��
            double minPrev = min({ dtw[(i - 1) * (m + 1) + j],
                                 dtw[i * (m + 1) + (j - 1)],
                                 dtw[(i - 1) * (m + 1) + (j - 1)] });
            dtw[i * (m + 1) + j] = cost + minPrev;
        }
    }

    // �������յ�DTW����
    return dtw[n * (m + 1) + m];
}



double LB_Keogh(const vector<double>& query, const vector<double>& candidate, int r) {
    int n = query.size();
    double lb = 0.0;

    // �����ϰ����� U ���°����� L
    vector<double> U(n), L(n);
    for (int i = 0; i < n; ++i) {
        U[i] = query[i] + r;
        L[i] = query[i] - r;
    }

    // ���� LB_Keogh �½�
    for (int i = 0; i < n; ++i) {
        if (candidate[i] > U[i]) {
            lb += (candidate[i] - U[i]) * (candidate[i] - U[i]);
        }
        else if (candidate[i] < L[i]) {
            lb += (L[i] - candidate[i]) * (L[i] - candidate[i]);
        }
    }

    return sqrt(lb);
}

vector<double> downsample(const vector<double>& seq, int resolution) {
    vector<double> downsampled_seq;
    for (size_t i = 0; i < seq.size(); i += resolution) {
        downsampled_seq.push_back(seq[i]);
    }
    return downsampled_seq;
}

double fastdtw(const vector<double>& seq1, const vector<double>& seq2, int radius) {
    // ������г���С�ڰ뾶��ֱ�Ӽ��� DTW
    //raidusһ��ȡ1
    if (seq1.size() <= radius || seq2.size() <= radius) {
        return dtwDistance(seq1, seq2);
    }
    // ������
    vector<double> coarse_seq1 = downsample(seq1, 2);
    vector<double> coarse_seq2 = downsample(seq2, 2);
    // �ݹ����ͷֱ��ʵ� DTW
    double low_res_dtw = fastdtw(coarse_seq1, coarse_seq2, radius);

    // ͶӰ·����ϸ��
    // �����Ϊ�ڸ߷ֱ����ϼ��� DTW��������������Χ
    int n = seq1.size();
    int m = seq2.size();
    vector<vector<double>> dp(n + 1, vector<double>(m + 1, numeric_limits<double>::max()));
    dp[0][0] = 0;

    for (int i = 1; i <= n; ++i) {
        for (int j = max(1, i - radius); j <= min(m, i + radius); ++j) {
            double cost = abs(seq1[i - 1] - seq2[j - 1]);
            dp[i][j] = cost + min({ dp[i - 1][j], dp[i][j - 1], dp[i - 1][j - 1] });
        }
    }
    return dp[n][m];
}

vector<double> computeDerivative(const vector<double>& seg){
    vector<double> derivative;
    for (size_t i = 1; i < seg.size()-1; ++i) {
        double diff = (seg[i + 1] - seg[i - 1]) / 2.0;
        derivative.push_back(diff);
    }
    derivative.insert(derivative.begin(), derivative[0]);
    derivative.push_back(derivative.back());
    return derivative;
}
double ddtw(const vector<double>& seq1, const vector<double>& seq2) {
    vector<double>derivatived1 = computeDerivative(seq1);
    vector<double>derivatived2 = computeDerivative(seq2);

    int n = seq1.size();
    int m = seq2.size();
    vector<vector<double>> dp(n + 1, vector<double>(m + 1, numeric_limits<double>::max()));
    dp[0][0] = 0;

    for (size_t i = 1; i <= n; ++i) {
        for (size_t j = 1; j <= m; ++j) {
            double cost = abs(derivatived1[i-1] - derivatived2[j-1]);
            dp[i][j] = cost + min({ dp[i][j - 1],dp[i - 1][j],dp[i - 1][j - 1] });
        }
    }
    return dp[n][m];
}

double windowed_dtw(const vector<double>& seq1, const vector<double>& seq2,int windowSize) {
    //ʹ��Sakoe-Chiba Band��Ϊ��������
    //windowSize�Ĵ�СΪ���г��ȵ�10%��20%֮�䡣����ȡ35��
    //��ʱ�临�Ӷ�ΪO(r*max(n,m)^2)  �˴�r = 0.152
    int n = seq1.size();
    int m = seq2.size();
    vector<vector<double>> dp(n + 1, vector<double>(m + 1, numeric_limits<double>::max()));
    dp[0][0] = 0;

    //���ô��ڴ�С
    windowSize = max(windowSize, static_cast<int>(abs(n - m)));
    for (size_t i = 1; i <= n; ++i) {
        for (size_t j = max(1, static_cast<int>(i) - windowSize); 
            j <= min(m, static_cast<int>(i) + windowSize); ++j) {
            double cost = abs(seq1[i - 1] - seq2[j - 1]);
            dp[i][j] = cost + min({ dp[i - 1][j],dp[i][j - 1],dp[i - 1][j - 1] });
        }
    }
    return dp[n][m];
}

