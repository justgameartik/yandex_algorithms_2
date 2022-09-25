/* H\w 4. Task A
#include <iostream>
#include <map>
using namespace::std;

void Count_letters(char* str, int str_length, int letter_amount[])
{
	for (int i = 0; i < str_length; i++)
		letter_amount[str[i] - 'A'] += 1;
}

string Final_polyndrom(int letter_amount[], int latin_alphabet)
{
	string result;
	for (int i = 0; i < latin_alphabet; i++)
	{
		if (letter_amount[i] >= 2)
			for (int j = 0; j < letter_amount[i]/2; j++)
				result.push_back(char(i) + 'A');
	}

	for (int i =0; i < latin_alphabet; i++)
		if (letter_amount[i] % 2 == 1)
		{
			result.push_back(char(i) + 'A');
			break;
		}

	for (int i = latin_alphabet - 1; i >= 0; i--)
	{
		if (letter_amount[i] >= 2)
			for (int j = 0; j < letter_amount[i] / 2; j++)
				result.push_back(char(i) + 'A');
	}

	return result;
}

int main()
{
	int str_length;
	cin >> str_length;

	char* str = new char[str_length];

	for (int i = 0; i < str_length; i++)
		cin >> str[i];

	const int latin_alphabet = 26;
	int letter_amount[latin_alphabet];
	for (int i = 0; i < latin_alphabet; i++)
		letter_amount[i] = 0;

	Count_letters(str, str_length, letter_amount);

	cout << Final_polyndrom(letter_amount, latin_alphabet);
}
*/

/* H\w 4. Task B
#include <iostream>
#include <string>
using namespace::std;

int main()
{
	int side, words_amount;
	cin >> side >> words_amount;

	string* table = new string[side];
	for (int i = 0; i < side; i++)
		cin >> table[i];

	string* word = new string[words_amount];
	for (int i = 0; i < words_amount; i++)
		cin >> word[i];

	int amount_letter_table[26];
	int amount_letter_words[26];
	for (int i = 0; i < 26; i++)
	{
		amount_letter_table[i] = 0;
		amount_letter_words[i] = 0;
	}

	for (int i = 0; i < words_amount; i++)
		for (int j = 0; j < word[i].length(); j++)
			amount_letter_words[int(word[i][j] - 'A')] += 1;

	for (int i = 0; i < side; i++)
		for (int j = 0; j < side; j++)
			amount_letter_table[int(table[i][j] - 'A')] += 1;

	
	for (int i = 0; i < 26; i++)
	{
		amount_letter_words[i] = amount_letter_table[i] - amount_letter_words[i];
		for (int j = 0; j < amount_letter_words[i]; j++)
			cout << char(i + 'A');
	}

	delete[] word; delete[] table;
}
*/
/* H\w 4. Task C */
#include <iostream>
#include <map>
#include <set>
#include <random>
using namespace::std;

int main()
{
	int stones_amount, pairs_amount;
	cin >> stones_amount >> pairs_amount;

	string stones; cin >> stones;

	map<char, string> beauty_pairs;
	for (int i = 0; i < pairs_amount; i++)
	{
		string temp; cin >> temp;
		beauty_pairs[temp[0]].push_back(temp[1]);
	}

	int count_letters[26];
	for (int i = 0; i < 26; i++)
		count_letters[i] = 0;
	
	int count = 0;
	for (int i = stones.length() - 1; i >= 0; i--)
	{
		if (beauty_pairs.find(stones[i]) != beauty_pairs.end())
		{
			for (int j = 0; j < 26; j++)
			{
				if (beauty_pairs[stones[i]].find(char(j + 'a')) != string::npos)
				{
					count += count_letters[j];
				}
			}
		}
		count_letters[int(stones[i] - 'a')] += 1;
	}

	cout << count;
}


/* H\w 4. Task D 
#include <iostream>
#include <string>
using namespace::std;

int Min(int a, int b)
{
	int result;
	if (a < b)
		result = a;
	else
		result = b;

	return result;
}

int main()
{
	string a, b;
	cin >> a >> b;

	int count_numbers_a[10];
	int count_numbers_b[10];
	for (int i = 0; i < 10; i++)
	{
		count_numbers_a[i] = 0;
		count_numbers_b[i] = 0;
	}

	for (int i = 0; i < a.length(); i++)
		count_numbers_a[int(a[i] - '0')] += 1;

	for (int i = 0; i < b.length(); i++)
		count_numbers_b[int(b[i] - '0')] += 1;

	bool not_null = false;
	for (int i = 9; i > 0; i--)
	{
		for (int j = 0; j < Min(count_numbers_a[i], count_numbers_b[i]); j++)
		{
			cout << i;
			not_null = true;
		}
	}


	for (int i = 0; i < Min(count_numbers_a[0], count_numbers_b[0]); i++)
	{
		cout << 0;
		if (!not_null)
		{
			not_null = true;
			break;
		}
	}

	if (!not_null)
		cout << -1;
}
*/

/* H\w 4. Task E
#include <iostream>
#include <map>
#include <vector>
#include <set>
using namespace::std;

int Min(int a, int b)
{
	int result;
	if (a < b)
		result = a;
	else
		result = b;

	return result;
}

int main()
{
	string mum_name, dad_name;
	cin >> dad_name >> mum_name;

	map <char, vector<int>> dad_name_letters;
	map <char, vector<int>> mum_name_letters;

	for (int i = 0; i < dad_name.length(); i++)
		dad_name_letters[int(dad_name[i] - 'a')].push_back(i);

	for (int i = 0; i < mum_name.length(); i++)
		mum_name_letters[int(mum_name[i] - 'a')].push_back(i);

	int mum_index = -1, dad_index = -1;

	for (int i = 25; i >= 0; i--)
	{
		if (dad_name_letters.find(i) != dad_name_letters.end() &&
			mum_name_letters.find(i) != mum_name_letters.end())
		{
			int dad_count_not_missed = dad_name_letters[i].size();
			int mum_count_not_missed = mum_name_letters[i].size();

			for (int j = 0; j < dad_name_letters[i].size(); j++)
			{
				if (dad_name_letters[i][j] > dad_index)
				{
					//dad_index = dad_name_letters[i][j];
					break;
				}
				dad_count_not_missed -= 1;
			}

			for (int j = 0; j < mum_name_letters[i].size(); j++)
			{
				if (mum_name_letters[i][j] > mum_index)
				{
					//mum_index = mum_name_letters[i][j];
					break;
				}
				mum_count_not_missed -= 1;
			}
			
			for (int j = 0; j < Min(mum_count_not_missed, dad_count_not_missed); j++)
			{
				cout << char(i + 'a');
				dad_index = dad_name_letters[i][dad_name_letters[i].size() - dad_count_not_missed + j];
				mum_index = mum_name_letters[i][mum_name_letters[i].size() - mum_count_not_missed + j];
			}
		}
	}
}
*/