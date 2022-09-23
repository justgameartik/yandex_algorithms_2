/* Task A
#include <iostream>
using namespace::std;
void Confuse(long long* arr, int arr_size)
{
	long long sum = 0;
	for (int i = 0; i < arr_size; i++)
		sum += arr[i];
	for (int i = 0; i < arr_size; i++)
		arr[i] = sum - arr[i];
}
long long Max_n_Min(long long* arr, int arr_size)
{
	long long max = arr[0];
	long long min = arr[0];
	for (int i = 1; i < arr_size; i++)
	{
		if (arr[i] > max)
			max = arr[i];
		if (arr[i] < min)
			min = arr[i];
	}
	return max - min;
}
int main()
{
	int n, k;
	cin >> n >> k;
	long long* arr = new long long[n];
	for (int i = 0; i < n; i++)
		cin >> arr[i];
	for (int i = 0; i < k; i++)
		Confuse(arr, n);
	cout << Max_n_Min(arr, n);
}
*/

/* Task B
#include <iostream>
#include <string>
using namespace::std;
int main()
{
	string x_str, y_str, z_str, temp;
	cin >> x_str >> z_str;

	int multiplier = 2*z_str.length() / x_str.length() + 1;
	for (int i = 0; i < multiplier; i++)
	{
		temp.append(x_str);
	}

	bool result = false;
	y_str.append(z_str);
	for (int i = 0; i < z_str.length(); i++)
	{
		// mama
		// amamam
		// mamamamamamamama
		if (temp.rfind(y_str) != string::npos &&
			temp.rfind(y_str) + y_str.length() == temp.length())
		{
			result = true;
		}
		else
			y_str.erase(y_str.length() - 1);
		if (result)
			break;
	}
	for (int i = y_str.length(); i < z_str.length(); i++)
		cout << z_str[i];
}
*/
/* Task C
#include <iostream>
using namespace::std;

int Case_x_y(int* x, int* y, int n, int target_x, int target_y)
{
	int result = 0;
	for (int i = 0; i < n; i++)
	{
		if (x[i] == target_x && abs(target_y - y[i]) == 1 || 
			y[i] == target_y && abs(target_x - x[i]) == 1)
		{
			result += 3;
		}
	}
	switch (result)
	{
	case(0):
		return 4;
		break;
	case(3):
		return 3;
		break;
	case(6):
		return 2;
		break;
	case(9):
		return 1;
		break;
	case(12):
		return 0;
		break;
	}
}

int main()
{
	int n;
	cin >> n;

	int* x = new int[n]; int* y = new int[n];

	for (int i = 0; i < n; i++)
		cin >> x[i] >> y[i];

	int perimetr = 0;

	for (int i = 0; i < n; i++)
	{
		perimetr += Case_x_y(x, y, n, x[i], y[i]);
	}

	cout << perimetr;

	delete[] x, delete[] y;
}*/
/* Task D
#include <iostream>
using namespace::std;

int Max_index(int* arr, int n)
{
	int result_index = 0;
	for (int i = 0; i < n; i++)
		if (arr[i] > arr[result_index])
			result_index = i;

	return result_index;
}

int Sum(int* arr, int n)
{
	int index = Max_index(arr, n);
	int sum = 0;
	for (int i = 0; i < n; i++)
	{
		if (i != index)
			sum += arr[i];
	}

	if (sum >= arr[index])
		return sum + arr[index];
	else
		return arr[index] - sum;
}

int main()
{
	int n;
	cin >> n;

	int* length = new int[n];

	for (int i = 0; i < n; i++)
		cin >> length[i];

	cout << Sum(length, n);
}
*/
/*
#include <iostream>
#include <math.h>
using namespace::std;

void Locate(long long* x, long long* y)
{
	long long result = 0;
	if (x[0] < x[1] && y[0] < y[1])
		result = 1;
	if (x[0] > x[1] && y[0] > y[1])
		result = 2;
	if (x[0] < x[1] && y[0] > y[1])
		result = 3;
	if (x[0] > x[1] && y[0] < y[1])
		result = 4;

	long long temp_x, temp_y;
	switch (result)
	{
	case(1):
		break;
	case(2):
		temp_x = x[0], temp_y = y[0];
		x[0] = x[1]; y[0] = y[1];
		x[1] = temp_x; y[1] = temp_y;
		break;
	case(3):
		temp_y = y[0];
		y[0] = y[1];
		y[1] = temp_y;
		break;
	case(4):
		temp_x = x[0];
		x[0] = x[1];
		x[1] = temp_x;
		break;
	default:
		result = 0;
	}
}

int Find_border(long long x_0, long long y_0, long long y, long long r)
{
	int result = int(sqrt((pow(r, 2)) - (pow(y - y_0, 2))));

	return result;
}

int main()
{
	const int n = 3;
	long long x[n], y[n], r;

	cin >> x[0] >> y[0] >> x[1] >> y[1];
	cin >> x[2] >> y[2] >> r;

	Locate(x, y);

	//cout << x[0] << ' ' << y[0] << '\t' << x[1] << ' ' << y[1] << '\n';
	long long sum = 0;

	for (long long i = y[0]; i <= y[1]; i++)
	{
		if (abs(i - y[2]) <= r)
		{
			long long border_1, border_2;
			long long x_proection = Find_border(x[2], y[2], i, r);

			border_1 = x[2] - x_proection; border_2 = x[2] + x_proection;
			
			if (border_1 > x[1] || border_2 < x[0])
				continue;

			if (border_1 < x[0])
				border_1 = x[0];

			if (border_2 > x[1])
				border_2 = x[1];

			sum += border_2 - border_1 + 1;
		}
		else
			continue;
	}

	cout << sum;
}
*/