/*
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
	string input_str =" ";

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
}*/