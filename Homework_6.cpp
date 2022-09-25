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

/* H\w 6. Task D 
#include <iostream>
#include <vector>
#include <algorithm>
using namespace::std;

bool Is_possible(vector<vector<long long>> a_deer, vector<vector<long long>> b_elf, 
	int possible_ans, vector<vector<long long>>& result)
{
	long long deers_index = 0;
	
	for (long long i = 0; i < possible_ans; i++)
	{
		long long r_elf_index = b_elf.size() - possible_ans + i;

		while (deers_index < a_deer.size() && a_deer[deers_index][1] <= b_elf[i][1])
			deers_index += 1;

		if (deers_index == a_deer.size() || a_deer[deers_index][1] >= b_elf[r_elf_index][1])
			return false;

		vector<long long> temp;
		temp.push_back(a_deer[deers_index][0]); temp.push_back(b_elf[i][0]); 
		temp.push_back(b_elf[r_elf_index][0]);

		result.push_back(temp);
	}

	//int elf_index = 0;
	//while (elf_index < possible_ans)
	//{
	//	if (deers_index >= a_deer.size())
	//	{
	//		result.clear();
	//		return false;
	//		break;
	//	}

	//	if (possible_ans > b_elf.size() / 2)
	//	{
	//		result.clear();
	//		return false;
	//		break;
	//	}

	//	if (b_elf[elf_index][1] >= a_deer[deers_index][1] || 
	//		b_elf[b_elf.size() - possible_ans + elf_index][1] <= a_deer[deers_index][1])
	//			deers_index += 1;
	//	else
	//	{
	//		vector<int> temp;
	//		temp.push_back(a_deer[deers_index][0]); temp.push_back(b_elf[elf_index][0]);
	//		temp.push_back(b_elf[b_elf.size() - possible_ans + elf_index][0]);
	//		
	//		result.push_back(temp);

	//		elf_index += 1;
	//	}
	//}

	return true;
}

bool Sort_col(const vector<long long>& v1, const vector<long long>& v2)
{
	return v1[1] < v2[1];
}

int main()
{
	long long deer_amount, elf_amount;
	cin >> deer_amount >> elf_amount;

	vector<vector<long long>> a_deer;
	for (long long i = 0; i < deer_amount; i++)
	{
		long long temp; cin >> temp;
		vector<long long> vec_temp;
		vec_temp.push_back(i + 1); vec_temp.push_back(temp);
		a_deer.push_back(vec_temp);
	}

	vector<vector<long long>> b_elf;
	for (long long i = 0; i < elf_amount; i++)
	{
		long long temp; cin >> temp;
		vector <long long> vec_temp;
		vec_temp.push_back(i + 1); vec_temp.push_back(temp);
		b_elf.push_back(vec_temp);
	}

	sort(a_deer.begin(), a_deer.end(), Sort_col);
	sort(b_elf.begin(), b_elf.end(), Sort_col);

	vector<vector<long long>> result;
	long long max_deers = min(a_deer.size(), b_elf.size() / 2);
	long long min_deers = 0;
	while (max_deers > min_deers)
	{
		long long m = (max_deers + min_deers + 1) / 2;
		if (Is_possible(a_deer, b_elf, m, result))
			min_deers = m;
		else
			max_deers = m - 1;

		result.clear();
	}

	Is_possible(a_deer, b_elf, max_deers, result);
	
	cout << min_deers;
	for (long long i = 0; i < min_deers; i++)
		cout << '\n' << result[i][0] << ' ' << result[i][1] << ' ' << result[i][2];
}
*/
/* H\w 6. Task E
#include <iostream>
#include <vector>
#include <algorithm>
using namespace::std;

bool Win_or_lose(long long money_spend, vector<vector<long long>> party, vector<long long> difference)
{
	
	for (long long i = 0; i < party.size(); i++)
	{
		if (party[i][2] == -1)
			continue;

		long long lost_money = party[i][2];
		long long local_voters = party[i][1];

		long long max_voters = party[party.size() - 1][1];

		long long index = 0;
		while (local_voters <= max_voters)
		{
			long long temp = difference[difference.size() - index - 1];
			local_voters += temp * (index + 1);
			lost_money += temp * (index + 1);
			max_voters -= temp;
			index += 1;
		}

		index -= 1;
		local_voters -= difference[difference.size() - index - 1] * (index + 1);
		lost_money -= difference[difference.size() - index - 1] * (index + 1);
		max_voters += difference[difference.size() - index - 1];

		long long temp = (max_voters * (index + 1) + local_voters) / (index + 2);
		max_voters -= (temp - local_voters) / (index + 1);
		local_voters += ((temp - local_voters) / (index + 1)) * (index + 1);
		lost_money += ((temp - local_voters) / (index + 1)) * (index + 1);

		local_voters += max_voters - local_voters + 1;
		lost_money += max_voters - local_voters + 1;

		if (lost_money <= money_spend)
			return true;
	}
	return false;
}

bool Sort_col(const vector<long long>& v1, const vector<long long>& v2)
{
	return v1[1] < v2[1];
}

int main()
{
	int party_amount; cin >> party_amount;
	vector<vector<long long>> party;

	long long all_voters = 0, max_gift = -1;
	for (int i = 0; i < party_amount; i++)
	{
		int temp_1, temp_2; cin >> temp_1 >> temp_2;
		all_voters += temp_1; 
		if (temp_2 > max_gift)
			max_gift = temp_2;

		vector<long long> temp; temp.push_back(i + 1); temp.push_back(temp_1); temp.push_back(temp_2);
		party.push_back(temp);
	}

	sort(party.begin(), party.end(), Sort_col);
	
	vector<long long> difference;
	for (long long i = 0; i < party.size() - 1; i++)
		difference.push_back(party[i][1] - party[i + 1][1]);

	long long max_spend = all_voters + max_gift;
	long long min_spend = 0;
	while (max_spend > min_spend)
	{
		long long m = (max_spend + min_spend) / 2;

		if (Win_or_lose(m, party, difference))
			max_spend = m;
		else
			min_spend = m + 1;
	}
	cout << max_spend;
}
*/