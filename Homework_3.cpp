/*H\w 3. Task A
#include <iostream>
#include <string>
#include <set>
#include <math.h>
#include <vector>
using namespace::std;


bool Str_is_help(string& str)
{
	getline(cin, str);
	if (str == "HELP")
		return false;
	else
		return true;
}

int Char_to_int(char c)
{
	return c - '0';
}

int String_to_int(string str)
{
	// 100
	int temp = 0;
	for (int i = 0; i < str.length(); i++)
	{
		temp += Char_to_int(str[i]) * pow(10, str.length() - 1 - i);
	}
	return temp;
}

int main()
{
	long long n;
	cin >> n;
	cin.ignore();

	set<long long> set_no;
	string input_str = " ";

	while (Str_is_help(input_str))
	{
		set<long long> local_meanings;
		long long temp = 0; long long pos = 0;

		for (long long i = input_str.length() - 1; i >= 0; i--)
		{
			if (input_str[i] != ' ' || i == 0)
			{
				temp += Char_to_int(input_str[i]) * pow(10, pos);
				pos++;
			}
			else {
				pos = 0;
				local_meanings.insert(temp);
				temp = 0;
			}
		}
		local_meanings.insert(temp);

		set<long long>::iterator it;
		for (it = set_no.begin(); it != set_no.end(); it++)
		{
			if (local_meanings.find(*it) != local_meanings.end())
			{
				local_meanings.erase(*it);
			}
		}

		if (local_meanings.size() <= (n - set_no.size()) / 2)
		{
			cout << "NO" << '\n';
			set<long long>::iterator it;
			for (it = local_meanings.begin(); it != local_meanings.end(); it++)
			{
				set_no.insert((*it));
			}
		}
		else {
			cout << "YES" << '\n';
			for (long long i = 1; i <= n; i++)
			{
				if (local_meanings.find(i) == local_meanings.end())
				{
					set_no.insert(i);
				}
			}
		}
	}

	for (long long i = 1; i <= n; i++)
		if (set_no.find(i) == set_no.end())
			cout << i << ' ';
}
*/

/* H\w 3. Task C
#include <iostream>
#include <set>
using namespace::std;

int main()
{
	int n, k;
	cin >> n >> k;
	int* first_day = new int[k];
	int* period = new int[k];

	set<int> bad_days;

	for (int i = 0; i < k; i++)
		cin >> first_day[i] >> period[i];
	
	for (int i = 0; i < k; i++)
	{
		int count = first_day[i];
		while (count <= n)
		{
			if (count % 7 != 6 && count % 7 != 0)
				bad_days.insert(count);
			
			count += period[i];
		}
	}

	cout << bad_days.size();

	delete[] first_day; delete[] period;
}
*/
/* H\w 3. Task D
#include <iostream>
#include <set>
using namespace::std;

int Find_min_not_repeatable(int* players_numbers, int n)
{
	int result = 200;

	set<int> all_used_numbers;
	set<int> repeatable_numbers;

	for (int i = 0; i < n; i++)
	{
		if (all_used_numbers.find(players_numbers[i]) != all_used_numbers.end())
			repeatable_numbers.insert(players_numbers[i]);
		else
			all_used_numbers.insert(players_numbers[i]);
	}

	set<int>::iterator it;
	for (it = all_used_numbers.begin(); it != all_used_numbers.end(); it++)
	{
		if (*it < result && repeatable_numbers.find(*it) == repeatable_numbers.end())
		{
			result = *it;
		}
	}

	return result;
}

int Better_than_player(int* player_score, int* players_numbers, int n)
{
	int count = 0;

	int min_not_repetable = Find_min_not_repeatable(players_numbers, n);

	for (int i = 0; i < n; i++)
	{
		if (players_numbers[i] == min_not_repetable)
			player_score[i] += min_not_repetable;
	}

	for (int i = 0; i < n-1; i++)
	{
		if (player_score[i] >= player_score[n - 1])
			count++;
	}

	for (int i = 0; i < n; i++)
	{
		if (players_numbers[i] == min_not_repetable)
			player_score[i] -= min_not_repetable;
	}

	return count;
}


int main()
{
	int n;

	cin >> n;
	int* player_score = new int[n];
	int* players_numbers = new int[n];
	
	set<int> used_numbers;

	for (int i = 0; i < n; i++)
		cin >> player_score[i];

	for (int i = 0; i < n - 1; i++)
	{
		cin >> players_numbers[i];
		used_numbers.insert(players_numbers[i]);
	}
	
	int min_winners = n; int result = 200;
	for (int i = 1; i <= 101; i++)
	{
		players_numbers[n - 1] = i;
		int better_people_now = Better_than_player(player_score, players_numbers, n);
		if (better_people_now < min_winners)
		{
			min_winners = better_people_now;
			result = i;
		}
	}

	cout << result;


	delete[] player_score; delete[] players_numbers;
}
*/
/* H\w 3. Task E*
#include <iostream>
#include <string>
#include <math.h>
#include <set>
using namespace::std;

int Char_to_int(char c)
{
	return c - '0';
}

string Plus_long_numbers(string first_str, string second_str)
{
	string result;
	int in_mind = 0;

	size_t size;
	if (first_str.length() == second_str.length())
	{
		if (Char_to_int(first_str[0]) + Char_to_int(second_str[0]) >= 9)
			size = first_str.length() + 1;
		else size = first_str.length();
	}
	else
		size = second_str.length();

	result.resize(size);

	for (int i = 0; i < first_str.length(); i++)
	{
		int addition = Char_to_int(first_str[first_str.length() - i - 1]) +
			Char_to_int(second_str[second_str.length() - i - 1]);
		result[size - i - 1] = char((addition + in_mind) % 10 + '0');
		
		in_mind = (addition + in_mind) / 10;
	}

	int last_letter = 0;
	if (first_str.length() != second_str.length())
		last_letter = Char_to_int(second_str[0]);

	if (in_mind + last_letter != 0)
		result[0] = char(in_mind + last_letter + '0');
	if (result[0] == 0)
		result.erase(0, 1);
	/*
	int popravka = 0, popravka_2 = 0; int in_mind = 0;
	if (first_str.length() != second_str.length())
	{
		result.push_back(second_str[0]);
		cout << second_str[0];
		popravka = 1;
	}
	else
	{
		if (Char_to_int(first_str[0]) + Char_to_int(second_str[0]) > 9)
		{
			int addition = Char_to_int(first_str[0]) + Char_to_int(second_str[0]);

			char temp[1] = { addition / 10 + '0'};
			result.push_back(temp[0]);
			cout << temp[0];
			in_mind = -addition / 10;
			popravka_2 = 1;
		}
	}

	for (int i = 0; i < first_str.length(); i++)
	{
		int addition = Char_to_int(first_str[i]) + Char_to_int(second_str[i + popravka]);

		char temp[1] = { addition % 10 + '0'};
		result.push_back(temp[0]);
		cout << temp[0];
		int j = 0;
		while (addition > 9)
		{
			addition = Char_to_int(result[i - 1 - j + popravka_2 + popravka]) + addition / 10 + in_mind;
			result[i - 1 + popravka_2 + popravka] = addition + '0';
			in_mind = 0;
			j++;
		}
	}
	cout << endl;
	return result;
}

int main()
{
	int n; cin >> n;
	set<string> fibanacci_numbers;

	string first_str = "1"; string second_str = "1";
	for (int i = 0; i < n; i++)
	{
		string input_str; cin >> input_str;
		while (second_str.length() <= input_str.length())
		{
			fibanacci_numbers.insert(second_str);

			string temp;
			temp.append(second_str);

			second_str = Plus_long_numbers(first_str, temp);
			
			first_str.clear(); first_str.append(temp);
		}

		if (fibanacci_numbers.find(input_str) == fibanacci_numbers.end())
			cout << "No" << '\n';
		else
			cout << "Yes" << '\n';
	}
}
*/

/* H\w 3. Task B
#include <iostream>
#include <set>
#include <string>
using namespace::std;

void Sort(int** arr, int n)
{
	for (int i = 0; i < n; i++)
	{
		if (arr[i][0] > arr[i][1])
		{
			int temp = arr[i][0];
			arr[i][0] = arr[i][1];
			arr[i][1] = temp;
		}
	}
}

int main()
{
	int vertex_amount, edges_amount;
	cin >> vertex_amount >> edges_amount;

	int** edge = new int*[edges_amount];
	for (int i = 0; i < edges_amount; i++)
	{
		edge[i] = new int[2];
		for (int j = 0; j < 2; j++)
			cin >> edge[i][j];
	}

	Sort(edge, edges_amount);

	set<string> new_graph;
	//set<int> new_graph_vertex_amount;

	for (int i = 0; i < edges_amount; i++)
	{
		if (edge[i][0] != edge[i][1])
		{
			//new_graph_vertex_amount.insert(edge[i][0]);
			//new_graph_vertex_amount.insert(edge[i][1]);
			
			string temp;
			temp.append(to_string(edge[i][0]));
			temp.push_back('-');
			temp.append(to_string(edge[i][1]));

			if (new_graph.find(temp) == new_graph.end())
				new_graph.insert(temp);
		}
	}

	cout << vertex_amount << ' ' << new_graph.size() << '\n';
	
	for (auto s : new_graph)
	{
		for (int i = 0; i < s.length(); i++)
		{
			if (s[i] != '-')
				cout << s[i];
			else
				cout << ' ';
		}
		cout << '\n';
	}

	for (int i = 0; i < edges_amount; i++)
		delete[] edge[i];
}*/