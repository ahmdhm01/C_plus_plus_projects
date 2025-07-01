#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

// حساب معاملات المعادلة
vector<vector<double>> Implicit_coefficients(vector<vector<double>>& a, double r, int No_grids) {
    for (int i = 1; i < No_grids; i++) {
        a[i][i - 1] = -r;
        a[i][i] = 1 + 2 * r;
        a[i][i + 1] = -r;
    }
    return a;
}

// تهيئة توزيع الحرارة بالمتوسط
void FDM(vector<vector<double>>& temp, int No_grids, double threshold) {
    double res, tempor;
    int iter = 0;
    do {
        res = 0;
        for (int i = 1; i < No_grids; i++) {
            tempor = temp[i][0];
            temp[i][0] = (temp[i - 1][0] + temp[i + 1][0]) / 2.0;
            res += abs(tempor - temp[i][0]);
        }
        iter++;
    } while (res > threshold && iter < 1000);
}

// حساب الطرف الأيمن (b) في كل زمن
vector<double> b_calculator(double r, int k, int No_grids, vector<vector<double>>& temp, vector<double>& b) {
    for (int i = 1; i < No_grids; i++) {
        b[i] = (1 - 2 * r) * temp[i][k - 1] + r * (temp[i - 1][k - 1] + temp[i + 1][k - 1]);
    }
    return b;
}

// حل المعادلة باستخدام Gauss-Seidel
void Gauss_Seidel(vector<vector<double>>& a, vector<double>& b, int No_grids, vector<vector<double>>& temp, double r, int No_time_steps) {
    for (int k = 1; k < No_time_steps; k++) {
        b = b_calculator(r, k, No_grids, temp, b);

        for (int i = 0; i <= No_grids; i++) {
            temp[i][k] = temp[i][k - 1];  // بدء التكرار من الحل السابق
        }

        int iter = 1;
        double res;
        do {
            res = 0;
            for (int i = 1; i < No_grids; i++) {
                double temp_old = temp[i][k];
                temp[i][k] = (b[i] - a[i][i - 1] * temp[i - 1][k] - a[i][i + 1] * temp[i + 1][k]) / a[i][i];
                res += abs(temp_old - temp[i][k]);
            }
            iter++;
        } while (iter < 1000 && res > 0.01);
    }
}

// البرنامج الرئيسي
int main() {
    double total_time = 1.0;
    double alpha = 1.0;
    double threshold = 0.01;
    double t_inc = 0.01;
    double total_dist = 1.0;
    double ratio = 1.0;  // Crank-Nicolson: ratio = 1.0, Implicit: ratio = 2.0, Explicit: ratio large
    int No_grids = 10;

    int No_time_steps = int(round(total_time / t_inc));
    double x_inc = total_dist / No_grids;
    double Fo = alpha * t_inc / (x_inc * x_inc);
    double r = Fo / ratio;

    // مصفوفة المعاملات
    vector<vector<double>> a(No_grids + 1, vector<double>(No_grids + 1, 0.0));
    a = Implicit_coefficients(a, r, No_grids);

    // تهيئة الحدود
    vector<double> boundaries = { 0.0, 100.0 };
    double avg = (boundaries[0] + boundaries[1]) / 2.0;

    // مصفوفة الحرارة
    vector<vector<double>> temp(No_grids + 1, vector<double>(No_time_steps, avg));
    temp[0][0] = boundaries[0];
    temp[No_grids][0] = boundaries[1];

    // إيجاد أول حالة اتزان حراري ابتدائية
    FDM(temp, No_grids, threshold);

    vector<double> b(No_grids + 1, 0.0);

    // حل المعادلة
    Gauss_Seidel(a, b, No_grids, temp, r, No_time_steps);

    // عرض النتائج
    for (int k = 0; k < No_time_steps; k++) {
        cout << "\nTemperature at time step " << k << ": ";
        for (int i = 0; i <= No_grids; i++) {
            cout << temp[i][k] << " ";
        }
    }
    cout << endl;
    return 0;
}
