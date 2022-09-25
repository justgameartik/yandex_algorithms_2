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

#include <iostream>
#include <map>
#include <set>
using namespace::std;

int main()
{
	int stones_amount, pair_amount;
	cin >> stones_amount >> pair_amount;
	
	map<char, set<char>> beauty_pair;

	string stones; cin >> stones;

	for (int i = 0; i < pair_amount; i++)
	{
		string temp;
		cin >> temp;
		beauty_pair[temp[0]].insert(temp[1]);
	}

	int count = 0;
	int letter_amount[26];
	for (int i = 0; i < 26; i++)
		letter_amount[i] = 0;

	for (int i = stones_amount - 1; i >= 0; i--)
	{
		if (beauty_pair.find(stones[i]) != beauty_pair.end())
		{
			for (int j = 0; j < 26; j++)
			{
				if (beauty_pair[stones[i]].find(char(j + 'a')) != beauty_pair[stones[i]].end())
				{
					count += letter_amount[j];
				}
			}
		}

		letter_amount[int(stones[i] - 'a')] += 1;
	}

	cout << count;
}