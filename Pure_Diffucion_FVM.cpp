#include<iostream>
#include <cmath>
#include <vector>
#include <fstream>

using namespace std;

void Diffusion_intialize(vector<vector<double>>& coeff, int No_grid, double a)
{

	for (short i = 0; i < No_grid; i++)
	{
		if (i == 0)
		{
			coeff[i][i + 1] = -a;
			coeff[i][i] = -3 * coeff[i][i + 1];
		}
		else if (i == No_grid - 1)
		{
			coeff[i][i - 1] = -a;
			coeff[i][i] = -3 * coeff[i][i - 1];
		}
		else
		{
			coeff[i][i - 1] = -a;
			coeff[i][i + 1] = -a;
			coeff[i][i] = -1 * coeff[i][i - 1] - coeff[i][i + 1];
		}
	}
}

vector<double> b_calculator(double q, double a, int No_grid, vector<double>& boundaries, vector<double>& b) {
	if (abs(q) < 0.01)
	{
		b[0] = 200 * boundaries[0];
		b[No_grid - 1] = 200 * boundaries[1];
	}
	else
	{
		for (short i = 0; i < No_grid; i++)
		{
			if (i == 0)
			{
				b[i] = q + 2 * a * boundaries[0];
			}
			else if (i == No_grid - 1)
			{
				b[i] = q + 2 * a * boundaries[1];
			}
			else
			{
				b[i] = q ;
			}
		}
	}
	return b;
}

void Gauss_Seidel(vector<vector<double>>& coeff, vector<double>& b, int No_grid, vector<double>& temp)
{
	cout << "Gauss_Seidel" << endl;

	short iter;
	double res;
	double temporal;


	
	for (short i = 1; i < No_grid-1; i++)
	{
		double check = 0;
		
		for (short j = i-1; j < i+1; j++)
		{
			if (i != j)
			{
				check += abs(coeff[i][j]);
			}
		}
		if (abs(check) >= abs(coeff[i][i]))
		{
			cerr << "solution not stable (Not Diagonal Dominiant)\n";
			exit(EXIT_FAILURE);
		}
	}

	iter = 1;
	do
	{
		res = 0;


		for (short i = 0; i < No_grid; i++) {
			temporal = temp[i];
			if (i == 0)
			{
				temp[i] = b[i] - coeff[i][i + 1] * temp[i + 1];
			}
			else if (i == No_grid - 1)
			{
				temp[i] = b[i] - coeff[i][i - 1] * temp[i - 1];
			}
			else
			{
				temp[i] = b[i] - coeff[i][i - 1] * temp[i - 1] - coeff[i][i + 1] * temp[i + 1];
			}
			temp[i] = temp[i] / coeff[i][i];
			//cout << solution[i] << endl;
			res = res + abs(temporal - temp[i]);
			cout << iter << "\t" << res << "\n";
			iter++;

		}
	} while (iter < 1000 && res > 0.01);
	
}

int main ()
{
	double k = 0.50, A = 1, inc_x = 0.004;
	double a = k * A / inc_x;
	int No_grid = 5;
	vector<double> boundaries = { 100, 200 };
	double avg = (boundaries[0] + boundaries[1])/2;

	vector<vector<double>> coeff(No_grid, vector<double>(No_grid, 0.0));
	
	vector<double> b(No_grid,0.0);

	double q = 1000000;
	q = q * A * inc_x;
	
	b = b_calculator(q, a, No_grid, boundaries, b);




	Diffusion_intialize(coeff, No_grid, a);

	for (short i = 0; i < No_grid; i++)
	{
		cout << endl;
		for (short j = 0; j < No_grid; j++)
		{
			cout << coeff[i][j]<<"\t";
		}
		cout << b[i] << "\n";
	}
	vector<double> temp(No_grid, avg);


	Gauss_Seidel(coeff, b, No_grid, temp);

	cout << "\nResults =  ";
	for (int i = 0; i <= No_grid-1; i++) {
		cout << temp[i] << " ";
	}
	cout << endl;

	ofstream file("temp.csv");
	if (!file.is_open()) {
		std::cerr << "Failed to open file!\n";
		return 1;
	}
	for (size_t i = 0; i < No_grid; i++) {
		file << temp[i] << ",";
	}
	file << "\n";
	file.close();
	return 0;

}

