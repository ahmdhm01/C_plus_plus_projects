#include<iostream>
using namespace std;
#include <cmath>
#include <vector>

void temporal(vector<vector<vector<double>>> &temp, float total_time, float alpha, float x_inc, int No_elements, int No_time_steps, double time_inc)
{

	for (int i = 1; i < No_time_steps; i++)
	{
		for (int j = 0; j <= No_elements; j++)
		{
			for (short k = 0; k <= No_elements; k++)
			{
				if (j == 0 || j == No_elements || k == 0 || k == No_elements)
				{
					temp[j][k][i] = temp[j][k][i - 1];
				}
				else
				{
					temp[j][k][i] = temp[j][k][i-1] + (alpha * time_inc / pow(x_inc, 2)) * (temp[j-1][k][i - 1] + temp[j+1][k][i-1] - 4 * temp[j][k][i-1] + temp[j][k-1][i-1] + temp[j][k + 1][i - 1]);
				}
			}
		}
	}

}


/* Intializing the solution array
Inputs no of element and no. of time steps
function calls for the boundary condition 
returns an array of initial solution*/
vector<vector<vector<double>>> initialize(int No_elements, int No_time_steps)
{
	double boundaries[4];
	double avg=0.0;
	cout << "B.C. in x-direction 1,2 -- B.C. in y-direction 1,2 -- B.C. in z-direction 1,2 --\n ";
	for (short i = 0; i < 4; i++)
	{
		cout << "Enter Boundary No. " << i + 1<< " ";
		cin >> boundaries[i];
		avg += boundaries[i];
	}
	avg = avg / 4.0;
	vector<vector<vector<double>>> temp(No_elements+1, vector<vector<double>>(No_elements+1, vector<double>(No_time_steps, avg)));

	// intialize the boundaries as 0,0,100,100 
	for (short i = 0; i <= No_elements; i++)
	{
		for (short j = 0; j <= No_elements; j++)
		{
			if (i == 0)
			{
				temp[i][j][0] = boundaries[0];
			}
			else if (i == No_elements)
			{
				temp[i][j][0] = boundaries[1];
			}
			else if (j == 0)
			{
				temp[i][j][0] = boundaries[2];
			}
			else if (j == No_elements)
			{
				temp[i][j][0] = boundaries[3];
			}
		}
	}
	return temp;
}

/* Intializing the first solution of the first time step
Inputs no of element
function calls for the boundary condition
returns an array of initial solution*/
void FDM(vector<vector<vector<double>>> &temp, int No_grids)
{

	double res, threshold;
	cout << "insert threshold" << endl;
	cin >> threshold;
	double tempor;
	short int iter = 0;


	// Compute the temperature in the domain as average

	do {
		res = 0;
		for (short i = 1; i < No_grids; i++)
		{
			for (short j = 1; j < No_grids; j++)
			{
				tempor = temp[i][j][0];
				temp[i][j][0] = (temp[i - 1][j][0] + temp[i + 1][j][0] + temp[i][j - 1][0] + temp[i][j + 1][0]) / 4;
				res = res + abs(tempor - temp[i][j][0]);
			}
		}

		iter++;
		cout << iter << "\t" << res << "\n";
	} while (res > threshold && iter < 1000);
}

int main(void)
{
	float time_inc, total_time, alpha, x_inc, total_length; //int grid_No;
	int steadyness, No_time_steps, number_of_elements;
	cout << " Steady or Transient Solution, 0 for steady and 1 for transient  ";
	cin >> steadyness;
	cout << "insert alpha: ";
	cin >> alpha;
	cout << "insert length: ";
	cin >> total_length;
	cout << "insert number of elements: ";
	cin >> number_of_elements;
	x_inc = total_length / (number_of_elements);

	if (steadyness == 0)
	{
		time_inc = 0;
		total_time = 1;
		No_time_steps = 1;
	}
	else
	{
		cout << "insert time increment: ";
		cin >> time_inc;
		cout << "insert total time: ";
		cin >> total_time;
		
		cout << " Stability condition : " << (alpha * time_inc / pow(x_inc, 2)) << endl;
		if (alpha * time_inc / pow(x_inc, 2) > 0.5)
		{
			cout << "Most likely, Solution would not be stable/n";
		}
		else
		{
			cout << " Allah Wishes, solution would be right./n";
		}
		No_time_steps = total_time / time_inc + 1;
	}

	


	// Entering and Intializing the boundaries
	auto temp = initialize(number_of_elements, No_time_steps);

	// solving 1st time step
	FDM(temp, number_of_elements);
	
	//void temporal(double temp[No_elements][No_elements][No_time_steps], float total_time, float alpha, float x_inc, int number_of_elements, int No_time_steps)
	temporal(temp, total_time, alpha, x_inc, number_of_elements, No_time_steps, time_inc);

	
	for (short j = 0; j < No_time_steps; j++)
	{
		cout << "Time Step: " << j << endl;
		for (short i = 0; i <= number_of_elements; i++)
		{

			for (short k = 0; k <= number_of_elements; k++)
			{
				cout << temp[i][k][j] << "    ";
			}
			cout << endl;
		}
	}
}