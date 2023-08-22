#pragma once
#ifndef KMP_H
#define KMP_H
#include<iostream>
#include<string>
#include<vector>
using namespace std;

int GetNext(string s, vector<int>& next)
{
	int k = 0;
	int j = -1;
	while (k < s.size()-1)
	{
		if (j == -1 || s[k] == s[j])
		{
			j += 1;
			k += 1;
			next[k] = j;
		}
		else
		{
			j = next[j];
		}
	}
}
#endif