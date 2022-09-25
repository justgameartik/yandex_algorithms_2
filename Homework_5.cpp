/* H\w 5. Task A
#include <iostream>
using namespace::std;

void heapify(int arr[], int n, int i)
{
    int largest = i;
    // Инициализируем наибольший элемент как корень
    int l = 2 * i + 1; // левый = 2*i + 1
    int r = 2 * i + 2; // правый = 2*i + 2

    // Если левый дочерний элемент больше корня
    if (l < n && arr[l] > arr[largest])
        largest = l;

    // Если правый дочерний элемент больше, чем самый большой элемент на данный момент
    if (r < n && arr[r] > arr[largest])
        largest = r;

    // Если самый большой элемент не корень
    if (largest != i)
    {
        swap(arr[i], arr[largest]);

        // Рекурсивно преобразуем в двоичную кучу затронутое поддерево
        heapify(arr, n, largest);
    }
}

// Основная функция, выполняющая пирамидальную сортировку
void Sort(int arr[], int n)
{
    // Построение кучи (перегруппируем массив)
    for (int i = n / 2 - 1; i >= 0; i--)
        heapify(arr, n, i);

    // Один за другим извлекаем элементы из кучи
    for (int i = n - 1; i >= 0; i--)
    {
        // Перемещаем текущий корень в конец
        swap(arr[0], arr[i]);

        // вызываем процедуру heapify на уменьшенной куче
        heapify(arr, i, 0);
    }
}

bool Is_end(int index[], int clothes_amount[], int clothes_elements)
{
    bool result = true;
    for (int i = 0; i < clothes_elements; i++)
    {
        if (index[i] != clothes_amount[i] - 1)
            result = false;
    }
    
    return result;
}

int Max(int a, int b, int c, int d)
{
    int result;

    if (a >= b && a >= c && a >= d)
        result = 0;
    if (b >= a && b >= c && b >= d)
        result = 1;
    if (c >= a && c >= b && c >= d)
        result = 2;
    if (d >= a && d >= b && d >= c)
        result = 3;

    return result;
}

int Min(int a, int b, int c, int d)
{
    int result;

    if (a <= b && a <= c && a <= d)
        result = 0;
    if (b <= a && b <= c && b <= d)
        result = 1;
    if (c <= a && c <= b && c <= d)
        result = 2;
    if (d <= a && d <= b && d <= c)
        result = 3;

    return result;
}

int main()
{
	const int clothes_elements = 4;
	int clothes_amount[clothes_elements];
	int** clothes_color = new int* [clothes_elements];

	for (int i = 0; i < clothes_elements; i++)
	{
		cin >> clothes_amount[i];
		clothes_color[i] = new int[clothes_amount[i]];
		for (int j = 0; j < clothes_amount[i]; j++)
			cin >> clothes_color[i][j];
	}

    int result[clothes_elements];
    int index[clothes_elements];

    for (int i = 0; i < clothes_elements; i++)
    {
        Sort(clothes_color[i], clothes_amount[i]);
        result[i] = clothes_color[i][0];
        index[i] = 0;
    }
	

    int max_distance = 100001;
    while (!Is_end(index, clothes_amount, clothes_elements))
    {
        int max = Max(clothes_color[0][index[0]], clothes_color[1][index[1]], clothes_color[2][index[2]],
            clothes_color[3][index[3]]);
        max = clothes_color[max][index[max]];

        for (int i = 0; i < clothes_elements; i++)
        {
            while (index[i] < clothes_amount[i] && clothes_color[i][index[i]] <= max)
                index[i] += 1;
            index[i] -= 1;
        }

        int min = Min(clothes_color[0][index[0]], clothes_color[1][index[1]], clothes_color[2][index[2]],
            clothes_color[3][index[3]]);
        min = clothes_color[min][index[min]];

        int distance = max - min;
        if (distance < max_distance)
        {
            max_distance = distance;
            for (int i = 0; i < clothes_elements; i++)
                result[i] = clothes_color[i][index[i]];
        }

        int max_array[clothes_elements];

        for (int i = 0; i < clothes_elements; i++)
            if (index[i] != clothes_amount[i] - 1)
                max_array[i] = clothes_color[i][index[i]];
            else
                max_array[i] = 100001;

        min = Min(max_array[0], max_array[1], max_array[2], max_array[3]);

        if (index[min] != clothes_amount[min] - 1)
            index[min] += 1;
    }

    for (int i = 0; i < clothes_elements; i++)
        cout << result[i] << ' ';
	

	for (int i = 0; i < clothes_elements; i++)
		delete[] clothes_color[i];
    delete[] clothes_color;
}
*/

/* H\w 5. Task D
#include <iostream>
#include <string>
#include <set>
#include <vector>
using namespace::std;



int main()
{
    string str_in;
    cin >> str_in;
    
    long long count = 0;
    vector<int> balance; balance.push_back(0);
    for (int i = 0; i < str_in.length(); i++)
    {
        if (str_in[i] == '(')
            balance.push_back(balance[balance.size() - 1] + 1);
        else
            balance.push_back(balance[balance.size() - 1] - 1);
    }

    int index_1 = 0, index_2 = 1;

    while (index_1 != balance.size() - 1)
    {
        
        if (balance[index_2] != 0)
            index_2 += 1;
        else
        {
            while (index_1 != index_2)
            {
                count += index_2 - index_1 - 1;
                index_1 += 1;
            }
            index_2 += 1;
        }
    }

    count += (str_in.length() + 1) * (str_in.length() + 2) / 2;
    cout << count;
}
*/

/* H\w 5. Task
#include <iostream>
#include <vector>
#include <algorithm>
using namespace::std;

int Find_group(vector<int> prefix_amount_sum, long long target_el)
{
    int count = 0;

    for (int i = 0; i < prefix_amount_sum.size() - 1; i++)
    {
        if (target_el + 1 <= prefix_amount_sum[i+1])
            return i;
    }

    cout << "External";
    return -1;
}

int main()
{
    int pairs_amount;
    cin >> pairs_amount;

    vector<vector <int>> sweets; 
    vector<int> prefix_amount_sum;
    prefix_amount_sum.push_back(0);
    for (int i = 0; i < pairs_amount; i++)
    {
        vector<int> temp;
        int temp_1, temp_2;

        cin >> temp_1 >> temp_2;
        prefix_amount_sum.push_back(prefix_amount_sum[prefix_amount_sum.size() - 1] + temp_2);

        temp.push_back(temp_1); temp.push_back(temp_2);
        sweets.push_back(temp);
    }

    long long index_1 = 0; long long index_2 = prefix_amount_sum[prefix_amount_sum.size() - 1] - 1;

    long long left_donor = sweets[index_1][0], left_acceptor;
    long long right_donor = sweets[Find_group(prefix_amount_sum, index_2)][0], right_acceptor;
    bool left_recently_changed, right_recenlty_changed;
    
    left_acceptor = sweets[Find_group(prefix_amount_sum, index_1 + 1)][0];
    right_acceptor = sweets[Find_group(prefix_amount_sum, index_2 - 1)][0];

    while (index_2 - index_1 >= 2)
    {
        long long moved = min(left_donor, right_donor);
        left_acceptor += moved;
        right_acceptor += moved;

        left_donor -= moved;
        right_donor -= moved;

        left_recently_changed = false; right_recenlty_changed = false;

        if (left_donor == 0)
        {
            left_recently_changed = true;
            left_donor = left_acceptor;
            index_1 += 1;

            left_acceptor = sweets[Find_group(prefix_amount_sum, index_1 + 1)][0];
        }
        if (right_donor == 0)
        {
            right_recenlty_changed = true;
            right_donor = right_acceptor;
            index_2 -= 1;

            right_acceptor = sweets[Find_group(prefix_amount_sum, index_2 - 1)][0];
        }
        
    }

    if (index_1 == index_2)
    {
        if (prefix_amount_sum[prefix_amount_sum.size() - 1] > 2)
            cout << 1 << '\n' << left_donor + right_donor - sweets[Find_group(prefix_amount_sum, index_1)][0];
        else
            cout << 1 << '\n' << sweets[index_1][0];
    }
    else
    {
        if (prefix_amount_sum[prefix_amount_sum.size() - 1] > 2)
        {
            long long result[2];
            if (left_recently_changed)
                result[0] = left_donor + right_acceptor - sweets[Find_group(prefix_amount_sum, index_1)][0];
            else
                result[0] = left_donor;

            if (right_recenlty_changed)
                result[1] = left_acceptor + right_donor - sweets[Find_group(prefix_amount_sum, index_2)][0];
            else
                result[1] = right_donor;

            cout << 2 << '\n' << result[0] << ' ' << result[1];
        }
        else
            cout << 2 << '\n' << sweets[Find_group(prefix_amount_sum, index_1)][0] << ' ' <<
                sweets[Find_group(prefix_amount_sum, index_2)][0];
    }
}
*/
/*
#include <iostream>
#include <vector>
#include <cmath>
using namespace::std;

//bool Possible_triangle(long long side_length[])
//{
//    if (side_length[0] + side_length[1] > side_length[2])
//        return true;
//    else
//        return false;
//}
//
//bool Cool_triangle(long long side_length[])
//{
//    if (pow(side_length[2], 2) > pow(side_length[1], 2) + pow(side_length[0], 2))
//        return true;
//    else
//        return false;
//}

int main()
{
    int n; cin >> n;

    vector<long long> trubka_length;
    for (int i = 0; i < n; i++)
    {
        long long temp; cin >> temp;
        trubka_length.push_back(temp);
    }
    
    long long count = 0;
    
    for (int i = 0; i < n - 2; i++)
    {
        int index_min = i + 2, index_max =  i + 2;
        
        for (int j = i + 1; j < n - 1; j++)
        {
            long long min_value_sq = trubka_length[i] * trubka_length[i] + trubka_length[j] * trubka_length[j];
            long long max_value = trubka_length[i] + trubka_length[j];

            if (index_min <= j)
                index_min = j + 1;
            if (index_max <= j)
                index_max = j + 1;

            bool flag_min = false, flag_max = false;
            
            for (int k = index_min; k < n; k++)
                if (trubka_length[k] * trubka_length[k] > min_value_sq)
                {
                    flag_min = true;
                    index_min = k;
                    break;
                }
            if (!flag_min)
                index_min = n - 1;

            for (int k = index_max; k < n; k++)
                if (trubka_length[k] < max_value)
                {
                    flag_max = true;
                    index_max = k;
                }
                else
                    break;

            if (index_max >= index_min && flag_max && flag_min)
            {
                count += index_max - index_min + 1;
                //cout << index_max - index_min + 1 << ' ' << i << ' ' << j << ' ' << index_max << ' ' << index_min << '\n';
            }
        }
    }

    cout << count;
}
*/

#include <iostream>
#include <vector>
using namespace::std;

long long Min(long long a, long long b)
{
    if (a < b)
        return a;
    else
        return b;
}

int main()
{
    int pairs_amount; cin >> pairs_amount;
    
    vector<vector<long long>> sweets;
    for (int i = 0; i < pairs_amount; i++)
    {
        vector<long long> temp;
        long long temp_1, temp_2;
        cin >> temp_1 >> temp_2;
        temp.push_back(temp_1); temp.push_back(temp_2);

        sweets.push_back(temp);
    }

    int index_1 = 0, index_2 = pairs_amount - 1;

    long long to_clear_left_group = sweets[index_1][0] * (sweets[index_1][1] + 1) * sweets[index_1][1] / 2, 
        to_clear_right_group = sweets[index_2][0] * (sweets[index_2][1] + 1) * sweets[index_2][1] / 2;

    long long left_added = 0, right_added = 0;
    while (index_2 - index_1 > 1)
    {
        long long min = Min(to_clear_left_group, to_clear_right_group);
        
        to_clear_left_group -= min;
        to_clear_right_group -= min;

        if (to_clear_left_group == 0)
        {
            left_added += sweets[index_1][0] * sweets[index_1][1];
            index_1 += 1;
            to_clear_left_group = sweets[index_1][0] * (sweets[index_1][1] + 1) * sweets[index_1][1] / 2 + 
                left_added * sweets[index_1][1];
        }

        if (to_clear_right_group == 0)
        {
            right_added += sweets[index_2][0] * sweets[index_2][1];
            index_2 -= 1;
            to_clear_right_group = sweets[index_2][0] * (sweets[index_2][1] + 1) * sweets[index_2][1] / 2 +
                right_added * sweets[index_2][1];
        }
    }

    if (index_1 == index_2)
    {
        long long left_index = 0, right_index = sweets[index_1][1] - 1;
        to_clear_left_group = sweets[index_1][0] + left_added; 
        to_clear_right_group = sweets[index_2][1] + right_added;
        long long already_given_left = 0, already_given_right = 0;

        while (right_index - left_index > 1)
        {
            long long min = Min(to_clear_left_group, to_clear_right_group);

            to_clear_left_group -= min;
            to_clear_right_group -= min;
            already_given_left += min;
            already_given_right += min;

            if (to_clear_left_group == 0)
            {
                left_added += sweets[index_1][0];
                to_clear_left_group = sweets[index_1][0] + left_added;
                left_index += 1;
                already_given_left = 0;
            }
            if (to_clear_right_group == 0)
            {
                already_given_right = 0;
                right_added += sweets[index_2][0];
                to_clear_right_group = sweets[index_2][0] + right_added;
                right_index -= 1;
            }
        }

        if (right_index - left_index == 0)
            cout << 1 << '\n' << to_clear_left_group + to_clear_right_group - sweets[index_1][0];
        else
        {
            cout << 2 << '\n';
            cout << left_added + sweets[index_1][0] + already_given_right - already_given_left << ' ';
            cout << right_added + sweets[index_2][0] + already_given_left - already_given_right;
        }
    }
    else
    {
        if (to_clear_left_group > to_clear_right_group)
        {
            long long temp = to_clear_left_group;
            to_clear_left_group = to_clear_right_group;
            to_clear_right_group = temp;

            temp = left_added;
            left_added = right_added;
            right_added = temp;

            temp = index_1;
            index_1 = index_2;
            index_2 = temp;
        }

        if (sweets[index_2][0] * sweets[index_2][1] * (sweets[index_2][1] - 1) / 2 +
            right_added * (sweets[index_2][1] - 1) > to_clear_left_group)
        {
            long long right_index = sweets[index_2][1];

            for (long long i = 0; i < sweets[index_2][1]; i++)
                if (sweets[index_2][0] * (i + 1) * (i + 2) / 2 + right_added * (i + 1) <= to_clear_left_group)
                {
                    to_clear_right_group = sweets[index_2][0] * (i + 1) * (i + 2) / 2 + right_added * (i + 1);
                    right_index = sweets[index_2][1] - i - 1;
                }
                else
                {
                    right_added += sweets[index_2][0] * (i - 1);
                    break;
                }

            long long left_index = -1; left_added += sweets[index_1][0] * (sweets[index_1][1] - 1);
            long long already_given_left = 0, already_given_right = 0;
            while (right_index - left_index > 1)
            {
                long long min = Min(to_clear_left_group, to_clear_right_group);

                to_clear_left_group -= min;
                to_clear_right_group -= min;
                already_given_left += min; already_given_right += min;
                if (to_clear_left_group == 0)
                {
                    if (left_index < 0)
                        left_added += sweets[index_1][0];
                    else
                        left_added += sweets[index_2][0];
                    already_given_left = 0;
                    left_index += 1;
                    to_clear_left_group = sweets[index_2][0] + left_added;
                }
                if (to_clear_right_group == 0)
                {
                    already_given_right = 0;
                    right_index -= 1;
                    right_added += sweets[index_2][0];
                    to_clear_right_group = sweets[index_2][0] + right_added;
                }
            }

            if (right_index - left_index == 0)
                cout << 1 << '\n' << to_clear_left_group + to_clear_right_group - sweets[index_2][0];
            else
            {
                cout << 2 << '\n';
                cout << left_added + sweets[index_2][0] + already_given_right - already_given_left << ' ';
                cout << right_added + sweets[index_2][0] + already_given_left - already_given_right;
            }
        }
        else
        {
            if (sweets[index_2][0] * sweets[index_2][1] * (sweets[index_2][1] - 1) / 2 +
                right_added * (sweets[index_2][1] - 1) == to_clear_left_group)
                cout << 1 << '\n' << to_clear_left_group + sweets[index_2][0] * sweets[index_2][1] * (sweets[index_2][1] - 1) / 2 +
                right_added * (sweets[index_2][1] - 1) + sweets[index_2][0];
            else
            {
                cout << 2 << '\n';
                cout << to_clear_left_group - sweets[index_2][0] * sweets[index_2][1] * (sweets[index_2][1] - 1) / 2 +
                    right_added * (sweets[index_2][1] - 1) << ' ' << sweets[index_2][0] * sweets[index_2][1] * (sweets[index_2][1] - 1) / 2 +
                    right_added * (sweets[index_2][1] - 1) + sweets[index_2][0] + left_added +
                    (sweets[index_2][1] - 1) * sweets[index_2][0];
            }
        }
    }
}