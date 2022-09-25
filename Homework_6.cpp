/* H\w 6. Task A

#include <iostream>
using namespace::std;

long long Find_value(long long imagined)
{
	long long x_max = 1000000000;
	long long x_min = 0;

	int ans;
	
	long long prev = x_max;
	while (x_max != x_min)
	{
		long long m = (x_max + x_min) / 2;
		if (m == prev)
			m += 1;
		
		if (abs(m - imagined) < abs(prev - imagined))
			ans = 1;
		else
			ans = 0;

		if (m < prev)
		{
			if (ans == 1)
				x_max = (m + prev) / 2 - 1 + (m + prev) % 2;
			else
				x_min = (m + prev) / 2 + (m + prev) % 2;
		}
		else
		{
			if (ans == 1)
				x_min = (m + prev) / 2 + 1;
			else
				x_max = (m + prev) / 2;
		}

		prev = m;
	}
	return x_max;
}

int main()
{
	long long max = 1000000000;
	long long min = 0;
	
	long long x_max = 1000000000, y_max = 1000000000;
	long long x_min = 0, y_min = 0;

	int ans;
	cout << x_max << ' ' << y_max << '\n';
	cout.flush();
	cin >> ans;
	long long prev = x_max;
	while (x_max != x_min)
	{
		long long m = (x_max + x_min) / 2;
		if (m == prev)
			m += 1;
		cout << m << ' ' << y_max << '\n';
		cout.flush();
		cin >> ans;
		
		if (m < prev)
		{
			if (ans == 1)
				x_max = (m + prev) / 2 - 1 + (m + prev) % 2;
			else
				x_min = (m + prev) / 2 + (m + prev) % 2;
		}
		else
		{
			if (ans == 1)
				x_min = (m + prev) / 2 + 1;
			else
				x_max = (m + prev) / 2;
		}
		
		prev = m;
	}
	
	prev = y_max;
	while (y_max != y_min)
	{
		long long m = (y_max + y_min) / 2;
		if (m == prev)
			m += 1;
		cout << x_max << ' ' << m << '\n';
		cout.flush();
		cin >> ans;

		if (m < prev)
		{
			if (ans == 1)
				y_max = (m + prev) / 2 - 1 + (m + prev) % 2;
			else
				y_min = (m + prev) / 2 + (m + prev) % 2;
		}
		else
		{
			if (ans == 1)
				y_min = (m + prev) / 2 + 1;
			else
				y_max = (m + prev) / 2;
		}

		prev = m;
	}

	cout << 'A' << ' ' << x_min << ' ' << y_min;
}

*/

/* H\w 6. Task B
#include <iostream>
using namespace::std;

int main()
{
	long long interv_beg, interv_end, money_amount;
	int percent, tickets_amount;

	cin >> interv_beg >> interv_end >> percent >> money_amount >> tickets_amount;

	long long price_max = 1000000001; long long price_min = 0;

	while (price_max != price_min)
	{
		long long local_price = (price_max + price_min + 1) / 2;
		long long sum_price;
		int taxes = 100;

		sum_price = local_price * taxes * tickets_amount;
		
		if (money_amount * 100 >= sum_price)
			price_min = local_price;
		else
			price_max = local_price - 1;
	}

	if (price_max >= interv_beg && price_max <= interv_end)
	{
		price_min = 0;
		while (price_max != price_min)
		{
			long long local_price = (price_max + price_min + 1) / 2;
			long long sum_price;
			int taxes = 100;

			if (local_price >= interv_beg && local_price <= interv_end)
				taxes += percent;

			sum_price = local_price * taxes * tickets_amount;

			if (money_amount * 100 >= sum_price)
				price_min = local_price;
			else
				price_max = local_price - 1;
		}
	}
	
	cout << price_max;
}
*/

/* H\w 6. Task C 
#include <map>
#include <iostream>
#include <vector>
#include <set>
#include <algorithm>
using namespace::std;


long long Count_passed_members(long long members_amount, long long score_enough, 
	vector<vector<long long>> members, map<long long, long long> reg_last_members)
{
	long long max_id = members_amount - 1, min_id = 0;
	while (max_id > min_id)
	{
		long long now_id = (max_id + min_id) / 2;

		if (members[now_id][1] >= score_enough)
			max_id = now_id;
		else
			min_id = now_id + 1;
	}

	long long result = members_amount - max_id;
	
	set<long long> regions_used;
	map<long long, long long>::iterator it;
	for (it = reg_last_members.begin(); it != reg_last_members.end(); it++)
	{
		if (it->second < max_id)
			result += 1;
	}

	return result;
}

bool Sort_col(const vector<long long>& v1, const vector<long long>& v2)
{
	return v1[1] < v2[1];
}

int main()
{
	long long members_amount, max_members_passed, regions_amount;
	cin >> members_amount >> max_members_passed >> regions_amount;

	vector<vector<long long>> members;

	for (long long i = 0; i < members_amount; i++)
	{
		long long id, region, score, is_winner;
		cin >> id >> region >> score >> is_winner;

		vector<long long> temp;
		temp.push_back(region); temp.push_back(score); temp.push_back(is_winner);
		if (is_winner == 1)
			temp[1] = 1000000000;
		
		members.push_back(temp);
	}
	
	sort(members.begin(), members.end(), Sort_col);

	map<long long, long long> reg_last_member;
	for (long long i = members_amount - 1; i >= 0; i--)
	{
		if (reg_last_member.find(members[i][0]) == reg_last_member.end())
			reg_last_member[members[i][0]] = i;

		if (reg_last_member.size() == regions_amount)
			break;
	}

	long long max_score = 1000000000, min_score = 0;

	while (max_score > min_score)
	{
		long long score_passed = (max_score + min_score) / 2;

		long long members_passed = Count_passed_members(members_amount, score_passed, members, reg_last_member);

		if (members_passed <= max_members_passed)
			max_score = score_passed;
		else
			min_score = score_passed + 1;
	}

	cout << max_score;
}
*/

