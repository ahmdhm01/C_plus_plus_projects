#include<iostream>
using namespace std;
#include <cmath>
#include <chrono>
#include <fstream>

using namespace std::chrono;
/*
int saving(int rows, int cols, float* array) {
	std::ofstream file("data.csv");
	for (short i = 0; i < rows; ++i) {
		for (short j = 0; j < cols; ++j) {
			file << array[i][j];
			//if (j < cols - 1) file << ",";
		}
		file << "\n";
	}
	file.close();
	return 0;
}
*/

int temporal_derivative(float *solution,float time_inc,float total_time, float alpha, float x_inc, int grid_size)
{
	int No_time_steps = total_time / time_inc;
	
	for (int i = 1; i <= No_time_steps; i++)
	{
		for (int j = 0; j < grid_size; j++)
		{
			for (int k = 0; k < grid_size; k++)
			{
				if (k == 0 || j == 0 || j == grid_size - 1 || k == grid_size - 1)
				{
					solution[j][k][i] = solution[j][k][i - 1];
				}
				else
				{
					solution[j][k][i] = solution[j][k][i - 1] + alpha * time_inc / x_inc * *2 * (solution[j + 1][k][i - 1] - 4 * solution[j][k][i - 1] + solution[j - 1][k][i - 1]+ solution[j][k-1][i - 1]+ solution[j][k+1][i - 1])
				}
				
			}
		}
		
	}
}
// this program solves for the temperature distribution over the domain based on boundary temperature and using FDM

int main()
{

	float res, threshold;
	cout << "insert threshold" << endl;
	cin >> threshold;
	float tempor;
	short int iter = 0;
	int grid_size;
	cout << "Please, insert grid size" << endl;
	cin >> grid_size;

	float temp[grid_size][grid_size];


	// calculate the start time
	auto start = high_resolution_clock::now();

	// intialize the boundaries as 0,0,100,100 
	for (short i = 0; i < grid_size; i++)
	{
		for (short j = 0; j < grid_size; j++)
		{
			if (i == 0 || j == 0)
			{
				temp[i][j] = 0;
			}
			else if (i == grid_size-1 || j == grid_size-1)
			{
				temp[i][j] = 100;
			}
			else
			{
				temp[i][j] = 50;
			}
		}	
	}
	// Compute the temperature in the domain as average
	
	do {
		res = 0;
		for (short i = 1; i < grid_size-1; i++)
		{
			for (short j = 1; j < grid_size-1; j++)
			{
				tempor = temp[i][j];
				temp[i][j] = (temp[i - 1][j] + temp[i + 1][j] + temp[i][j - 1] + temp[i][j + 1]) / 4;
				res = res + abs(tempor - temp[i][j]);
			}
		}

		iter++;
		cout << iter << "\t" << res << "\n";
	} while (res > threshold && iter < 1000);

	// Printing the results
	cout << "Temperature Distribution:\n";


	for (short i = 0; i < grid_size; i++)
	{
		for (short j = 0; j < grid_size; j++)
		{
			cout << temp[i][j] << "    ";
		}
		cout << endl;
	}
	//saving( grid_size, grid_size, temp);
	// calculate the run time
	auto stop = high_resolution_clock::now();
	auto duration = duration_cast<microseconds>(stop - start);

	cout << "Time taken by function: "
		<< duration.count() << " microseconds" << endl;
	//cout << "number of iterations: " << iter<<endl;
}