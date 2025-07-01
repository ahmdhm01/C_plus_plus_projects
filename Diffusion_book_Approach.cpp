#include<iostream>
#include <cmath>
#include <vector>

using namespace std;

double boundaries(double x)
{
	coeff = 0;
	if (boundary == "Specified")
	{
		coeff += 2 * x;
	}
	else if (boundary == "Insulated")
	{
		coeff += 0;
	}
	else if (boundary == "flux")
	{
		coeff +=
	}
}
void a_matrix(vector<vector<double>>& coeff, int No_grid, double a, int total_nodes, int arr_l, double inc_x, double inc_y, double inc_z...
			int No_x_ele, int No_y_ele, int No_z_ele, double kappa, double A_x, double A_y, double A_z)
{

	for (short i = 0; i < total_nodes; i++)
	{
		for (short j = 1; j < arr_l; j++)
		{
			if (inc_z != 0)
			{
				if (i > = ((No_x_ele * No_y_ele * No_z_ele) - (No_x_ele * No_y_ele)) && i < (No_x_ele * No_y_ele * No_z_ele))
				{
					a[i][6] = 0;
					a[i][5] = kappa * A_z / inc_z;
				}
				else if (i < (No_x_ele* No_y_ele - 1))
				{
					a[i][5] = 0;
					a[i][6] = kappa * A_z / inc_z;
				}
				else
				{
					a[i][5] = kappa * A_z / inc_z;
					a[i][6] = kappa * A_z / inc_z;
				}
			}
			
			// y-coefficient
			if ((inc_y != 0))
			{
				if ((i % (No_x_ele * No_y_ele) > = 0) && (i % (No_x_ele * No_y_ele)) < (No_x_ele))
				{
					a[i][3] = 0;
					a[i][4] = kappa * A_y / inc_y;
				}
				else if ((i % (No_x_ele * No_y_ele)) > (No_x_ele * No_y_ele - No_x_ele) && (i % (No_x_ele * No_y_ele) <= (No_x_ele * No_y_ele - 1))
				{
					a[i][3] = kappa * A_y / inc_y;
					a[i][4] = 0;
				}
				else
				{
					a[i][3] = kappa * A_y / inc_y;
					a[i][4] = kappa * A_y / inc_y;
				}
			}
			// x-coefficient
			if (i % No_x_ele == 0)
			{
				a[i][1] = 0;
				a[i][2] = kappa * A_x / inc_x;
			}
			else if ((i+1)% No_x_ele == 0)
			{
				a[i][1] = kappa * A_x / inc_x;
				a[i][2] = 0;
			}
			else
			{
				a[i][1] = kappa * A_x / inc_x;
				a[i][2] = kappa * A_x / inc_x;
			}			
		}
	}
}

void a_p(double a)
{
	for (int i = 0; i < total_nodes; i++)
	{

		for ( int j = 1; j < arr_l; j ++)
		if (inc_z != 0)
		{
			a[i][0] = a[i][1] + a[i][2] + a[i][3] + a[i][4] + a[i][5] + a[i][6] -s[i];
		}
		else if (inc_y != 0)
		{
			a[i][0] = a[i][1] + a[i][2] + a[i][3] + a[i][4] - s[i];
		}
		else
		{
			a[i][0] = a[i][1] + a[i][2] - s[i];
		}
	}
}
int main()
{
	// insert the domain dimensions
	float x, y, z;

	// insert the mesh size in ezery drection
	double inc_x, inc_y, inc_z;

	//Calculate No_of_elements in x-direc
	int No_x_ele = (int)(x / inc_x+0.5);
	inc_x = x / No_x_ele;

	//Calculate No_of_elements in x-direc
	int No_y_ele = (int)(y / inc_y + 0.5);
	inc_y = y / No_y_ele;

	//Calculate No_of_elements in x-direc
	int No_z_ele = (int)(z / inc_z + 0.5);
	inc_z = z / No_z_ele;

	if (inc_z == 0)
	{
		arr_l = 5;
		total_nodes = No_x_ele * No_y_ele;
	}
	else if (inc_y == 0)
	{
		arr_l = 3;
		total_nodes = No_x_ele;
	}
	else
	{
		arr_l = 7;
		total_nodes = No_x_ele * No_y_ele * No_z_ele;
	}
	 // initialize the coefficient array
	vector<vector<double>> coeff(total_nodes, vector<double>(arr_l,0.0));

	// initialize the b array
	vector<double> b(total_nodes);

	// initialize the property array

	vector<double> prop(total_nodes);
}
