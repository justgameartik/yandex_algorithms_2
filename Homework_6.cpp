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

long long Add_votes(long long i, vector<vector<long long>> party, vector<long long> suffix_sum, long long level)
{
	long long l = 0, r = party.size() - 1;
	while (l < r)
	{
		long long m = (l + r) / 2;
		if (party[m][1] < level)
			l = m + 1;
		else
			r = m;
	}
	if (party[l][0] < level)
		return 0;
	
	long long added = suffix_sum[l] - level * (party.size() - 1);
	if (party[i][1] >= level)
		added -= (party[i][1] - level);

	return added;
}

void Modeling(vector<vector<long long>>party,long long i, vector<long long> suffix_sum,
	long long& cost, long long& level, long long& recovery)
{
	long long min_value = 0;
	long long max_value = 1000001;
	while (max_value > min_value)
	{
		long long level = (max_value + min_value + 1) / 2;
		long long count_votes = Add_votes(i, party, suffix_sum, level);

		if (count_votes + party[i][2] > level)
			min_value = level;
		else
			max_value = level - 1;
	}
	long long count_votes = Add_votes(i, party, suffix_sum, min_value);
	if (recovery > party[i][1] + count_votes - min_value - 2)
		recovery = party[i][1] + count_votes - min_value - 2;
	else
		recovery = 0;
	cost = count_votes - recovery; level = min_value;
	recovery = recovery;

}

bool Sort_col(const vector<long long>& v1, const vector<long long>& v2)
{
	return v1[1] < v2[1];
}

bool Sort_col_last(const vector<long long>& v1, const vector<long long>& v2)
{
	return v1[0] < v2[0];
}

int main()
{
	long long n; cin >> n;
	vector<vector<long long>> party;
	
	for (long long i = 0; i < n; i++)
	{
		vector<long long> temp;
		long long temp_1, temp_2;
		cin >> temp_1 >> temp_2;
		temp.push_back(i + 1); temp.push_back(temp_1); temp.push_back(temp_2);

		party.push_back(temp);
	}

	sort(party.begin(), party.end(), Sort_col);
	
	vector<long long> suffix_sum;
	suffix_sum.resize(n);
	suffix_sum[suffix_sum.size() - 1] = party[suffix_sum.size() - 1][1];
	for (long long i = n - 2; i > -1; i--)
		suffix_sum[i] = suffix_sum[i + 1] + party[i][1];

	long long min_needed_money = 1000000000;


	long long cost, level, recovery, winner;
	for (long long i = 0; i < n; i++)
	{
		if (party[i][2] == -1)
			continue;
		else
		{
			Modeling(party, i, suffix_sum, cost, level, recovery);
			if (party[i][2] + cost < min_needed_money)
			{
				min_needed_money = party[i][2] + cost;
				winner = i;
			}
		}
	}

	vector<long long> result; result.resize(n);

	for (long long i = 0; i < n; i++)
	{
		if (i == winner)
			result[party[i][0]] = party[i][1] + cost;
		else
		{
			if (party[i][1] <= level)
				result[party[i][0]] = party[i][1];
			else
			{
				if (recovery > 0)
				{
					result[party[i][0]] = level + 1;
					recovery -= 1;
				}
				else
					result[party[i][0]] = level;
			}
		}
	}

	cout << min_needed_money << '\n' << party[winner][1] + 1 << '\n';
	for (long long i = 0; i < n; i++)
		cout << result[i]<< ' ';

}
*/

/*

bool Haircut(vector<vector<long long>> party, long long target_party, long long m, long long& new_score)
{
	long long index = party.size() - 1;
	long long local_voters = party[target_party][1];
	while (party[index][1] > m)
	{
		local_voters += party[index][1] - m;
		index -= 1;
	}

	if (local_voters > m)
	{
		new_score = local_voters;
		return true;
	}
	else
		return false;
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

	long long min_needed_money = all_voters + max_gift + 1;
	long long winner_party = 0, haircut_level = 0;
	for (long long i = 0; i < party.size(); i++)
	{
		if (party[i][2] == -1)
			continue;

		long long max_value = party[party.size() - 1][1];
		long long min_value = party[i][1];
		long long new_score = min_value;
		while (max_value > min_value)
		{
			long long m = (max_value + min_value + 1) / 2;

			if (Haircut(party, i, m, new_score))
				min_value = m;
			else
				max_value = m - 1;
		}
		Haircut(party, i, max_value, new_score);

		if (new_score - party[i][1] + party[i][2] < min_needed_money)
		{
			min_needed_money = new_score - party[i][1] + party[i][2];
			winner_party = i;
			haircut_level = max_value;
		}
	}

	cout << min_needed_money << '\n' << party[winner_party][0] << '\n';

	long long index = party.size() - 1;
	while (party[index][1] > haircut_level)
	{
		party[winner_party][1] += party[index][1] - haircut_level;
		party[index][1] = haircut_level;
		index -= 1;
	}
	
	sort(party.begin(), party.end(), Sort_col_last);
	for (long long i = 0; i < party.size(); i++)
		cout << party[i][1] << ' ';
}
*/