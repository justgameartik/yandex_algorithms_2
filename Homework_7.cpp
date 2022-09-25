/* Homework 7. Task A
#include <iostream>
#include <vector>
#include <set>
using namespace::std;

int Search_bus_num(vector<int> where_buses, int bus_stop)
{
	for (int i = 0; i < where_buses.size(); i++)
		if (where_buses[i] == bus_stop)
			return i;
	return -1;
}

void Buses_location(vector<vector<int>> bus_way, int count, vector<int>& where_buses)
{
	for (int i = 0; i < where_buses.size(); i++)
		where_buses[i] = bus_way[i][count % bus_way[i].size()];
}

int main()
{
	int stops_amount, bus_amount;
	cin >> stops_amount >> bus_amount;

	vector<vector<int>> bus_way;	bus_way.resize(bus_amount);
	set<int> stops_in_usage;
	for (int i = 0; i < bus_amount; i++)
	{
		int way_len; cin >> way_len;
		vector<int> temp;	temp.resize(way_len);
		for (int j = 0; j < way_len; j++)
		{
			int stop; cin >> stop;
			temp[j] = stop;
			stops_in_usage.insert(stop);
		}
		bus_way[i] = temp;
	}

	int passengers_amount; cin >> passengers_amount;
	vector<vector<int>> people_way;

	for (int i = 0; i < passengers_amount; i++)
	{
		int first_stop, plan_len;
		cin >> first_stop >> plan_len;

		vector<int> temp;
		temp.push_back(first_stop);

		for (int j = 0; j < plan_len; j++)
		{
			int next_stop; cin >> next_stop;
			temp.push_back(next_stop);
		}
		people_way.push_back(temp);
	}
	
	//cout << '\n' << "BUSSES" << '\n';
	//for (int i = 0; i < bus_way.size(); i++)
	//{
	//	for (int j = 0; j < bus_way[i].size(); j++)
	//		cout << bus_way[i][j] << ' ';
	//	cout << '\n';
	//}

	//cout << '\n' << "PASSENGERS" << '\n';
	//for (int i = 0; i < people_way.size(); i++)
	//{
	//	for (int j = 0; j < people_way[i].size(); j++)
	//		cout << people_way[i][j] << ' ';
	//	cout << '\n';
	//}

	vector < vector<int>> answer; 
	answer.resize(passengers_amount);
	for (int i = 0; i < passengers_amount; i++)
	{
		answer[i].push_back(0);
		answer[i].push_back(0);
	}
	
	for (int i = 0; i < passengers_amount; i++)
	{
		if (stops_in_usage.find(people_way[i][0]) == stops_in_usage.end())
			continue;

		long long count = 0;
		vector<int> where_buses; where_buses.resize(bus_amount);

		int passenger_location = people_way[i][0];

		for (int index = 1; index < people_way[i].size(); index++)
		{
			Buses_location(bus_way, count, where_buses);
			int needed_bus = Search_bus_num(where_buses, passenger_location);
			
			while (needed_bus < 0)
			{
				count += 1;
				Buses_location(bus_way, count, where_buses);
				needed_bus = Search_bus_num(where_buses, passenger_location);
			}

			count += people_way[i][index];
			Buses_location(bus_way, count, where_buses);
			passenger_location = where_buses[needed_bus];
			count += 1;
		}

		answer[i][0] = count - 1; 
		answer[i][1] = passenger_location;
	}

	for (int i = 0; i < passengers_amount; i++)
		cout << answer[i][0] << ' ' << answer[i][1] << '\n';
}
*/

/* H\w 7. Task B
#include <iostream>
#include <vector>
#include <algorithm>
using namespace::std;

bool Is_possible(vector<long long> paint_woods, long long x, long long woods_amount)
{
	long long already_painted_woods = 0;
	for (int i = 0; i < paint_woods.size(); i++)
	{
		long long extra_painted = 0;
		if (paint_woods[i] > already_painted_woods + x)
		{
			extra_painted = paint_woods[i] - already_painted_woods - x;
		}
		already_painted_woods += x + extra_painted;
	}

	if (already_painted_woods <= woods_amount)
		return true;
	else
		return false;
}

int main()
{
	int friends_amount; long long woods_amount;
	cin >> friends_amount >> woods_amount;

	vector<long long> paint_woods;
	paint_woods.resize(friends_amount);
	for (int i = 0; i < friends_amount; i++)
	{
		long long temp; cin >> temp;
		paint_woods[i] = temp;
	}

	sort(paint_woods.begin(), paint_woods.end());

	long long min_value = 0;
	vector<long long>::iterator it = min_element(paint_woods.begin(), paint_woods.end());
	long long max_value = *it;

	while (max_value > min_value)
	{
		long long m = (min_value + max_value + 1) / 2;

		if (Is_possible(paint_woods, m, woods_amount))
			min_value = m;
		else
			max_value = m - 1;
	}

	cout << max_value;
}
*/

/* H\w 7. Task C 
#include <iostream>
#include <vector>
#include <algorithm>
using namespace::std;

typedef long long ll;

int main()
{
	int n;
	cin >> n;

	vector<ll> x_coord;
	vector<vector<ll>> line;

	for (int i = 0; i < n; i++)
	{
		ll x_1, y_1, x_2, y_2;
		cin >> x_1 >> y_1 >> x_2 >> y_2;

		x_coord.push_back(x_1); x_coord.push_back(x_2);

		vector<ll> temp;
		temp.push_back(y_1); temp.push_back(x_1); temp.push_back(x_2); temp.push_back(1);
		line.push_back(temp);

		temp[0] = y_2; temp[3] = -1;
		line.push_back(temp);
	}

	sort(x_coord.begin(), x_coord.end());
	sort(line.begin(), line.end());

	ll S = 0;

	for (int i = 0; i < 2 * n - 1; i++)
	{
		int now_opened = 0;
		ll start_line; 
		for (int j = 0; j < 2 * n; j++)
		{
			if (line[j][1] >= x_coord[i + 1] || line[j][2] <= x_coord[i])
				continue;

			if (now_opened == 0)
				start_line = line[j][0];

			now_opened += line[j][3];

			if (now_opened == 0)
				S += (x_coord[i+1] - x_coord[i]) * (line[j][0] - start_line);
		}
	}

	cout << S;
}
*/

/* H\w 7. Task D */
#include <iostream>
#include <vector>
#include <set>
#include <map>
#include <algorithm>
using namespace::std;

int main()
{
	int civ_amount; cin >> civ_amount;

	vector<vector<long long>> date;
	for (int i = 0; i < civ_amount; i++)
	{
		long long date_beg, date_end;
		cin >> date_beg >> date_end;
		
		vector<long long> temp;
		temp.push_back(date_beg); temp.push_back(1); temp.push_back(i);
		date.push_back(temp);

		temp[0] = date_end; temp[1] = -1; 
		date.push_back(temp);
	}

	sort(date.begin(), date.end());
	long long answer = 2500000000; map<long long ,set<int>> date_beg;
	vector<int> answer_civ; answer_civ.resize(2);


	long long date_birth = 0; int birth_civ = 0; set<int> civ_alive;
	for (int i = 0; i < (int)date.size() - 1; i++)
	{
		if (date[i][1] == 1)
		{
			date_birth = date[i][0];
			birth_civ = date[i][2];
			civ_alive.insert(birth_civ);
		}
		else
		{
			if (civ_alive.size() > 1)
			{
				long long diff = date[i][0] - date_birth;
				if (diff < answer && diff != 0)
				{
					answer = diff;
					answer_civ[0] = date[i][2] + 1;

					if (date[i][2] == birth_civ)
					{
						civ_alive.erase(date[i][2]);
						set<int>::iterator it = civ_alive.begin();
						answer_civ[1] = *it + 1;
					}
					else
						answer_civ[1] = birth_civ + 1;
				}
			}

			civ_alive.erase(date[i][2]);
		}

	}


	//for (int i = 0; i < (int)date.size() - 1; i++)
	//{
	//	if (date[i][1] == -1)
	//	{
	//		date_beg[date[i][0]].insert(date[i][2]);
	//	}
	//	else
	//	{
	//		int max_index = (int)date_beg.size() - 1;
	//		int min_index = 0;
	//		while (max_index > min_index)
	//		{
	//			int m = (max_index + min_index + 1) / 2;
	//			
	//			map<long long, set<int>>::iterator it = next(date_beg.begin(), m);
	//			if (it->first < date[i][0])
	//				min_index = m;
	//			else
	//				max_index = m - 1;
	//		}
	//		
	//		map<long long, set<int>>::iterator it = next(date_beg.begin(), max_index);

	//		if (it->second.find(date[i][2]) != it->second.end() && it->second.size() == 1)
	//		{
	//			max_index -= 1;
	//			if (max_index >=0)
	//				it = next(date_beg.begin(), max_index);
	//		}

	//		if (max_index >= 0)
	//		{
	//			long long first_cross = max(it->first,date[i][3]);
	//			long long last_cross = date[i][0];
	//			
	//			if (last_cross - first_cross < answer && last_cross - first_cross != 0)
	//			{
	//				answer = last_cross - first_cross;
	//				answer_civ[1] = date[i][2] + 1;
	//				set<int>::iterator set_it;
	//				for (set_it = it->second.begin(); set_it != it->second.end(); set_it++)
	//					if (*set_it != date[i][2])
	//					{
	//						answer_civ[0] = *set_it + 1;
	//						break;
	//					}
	//			}
	//		}
	//		set<int>::iterator set_it = date_beg[date[i][3]].find(date[i][2]);
	//		date_beg[date[i][3]].erase(set_it);
	//		//if (date_beg[date[i][3]].empty())
	//		//	date_beg.erase(date[i][3]);
	//	}
	//}

	if (answer != 2500000000)
	{
		sort(answer_civ.begin(), answer_civ.end());
		cout << answer_civ[0] << ' ' << answer_civ[1];
	}
	else
		cout << 0;
}


/*
#include <iostream>
#include <vector>
using namespace::std;

int main()
{
	vector<long long> test_1 = { 0, 1, 10, 100, 1000 };
	vector<long long> test_2 = { 0, 2, 20, 200, 2000 };
	vector<long long> test_3 = { 0, 3, 30, 300, 3000 };

	vector<vector<long long>> test = { test_1, test_2, test_3 };
	
	vector<long long> test_remove = { 0, 2, 20, 200, 2000 };
	auto it = remove(test.begin(), test.end(), test_remove);
	test.erase(it);

	for (int i = 0; i < test.size(); i++)
	{
		for (int j = 0; j < test[i].size(); j++)
			cout << test[i][j] << ' ';
		cout << '\n';
	}
}
*/
/*
#include <iostream>
#include <map>
#include <set>
using namespace::std;

int main()
{
	map<int, set<int>> test;
	set<int> test_set;
	
	test_set.insert(1); test_set.insert(2); test_set.insert(3);
	test[1] = test_set;

	set<int> test_set_1;
	test_set_1.insert(4); test_set_1.insert(5); test_set_1.insert(6);
	test[2] = test_set_1;

	map<int, set<int>>::iterator it = test.begin();

	it->second.erase(2); it->second.erase(3); it->second.erase(1);
	if (it->second.empty())
		test.erase(it->first);

	for (it = test.begin(); it != test.end(); it++)
	{
		set<int>::iterator set_it;
		cout << it->first << '\t';
		for (set_it = it->second.begin(); set_it != it->second.end(); set_it++)
			cout << *set_it << ' ';
	}
}*/