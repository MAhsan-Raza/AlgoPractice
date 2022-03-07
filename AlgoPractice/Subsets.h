#pragma once

void GetAllSubSets_BACKTRACKING(const vector<int>& vec, const int index, vector<int> tmp, vector<vector<int>>& res)
{
	if (index >= 0)
		tmp.push_back(vec[index]);
	res.emplace_back(tmp.cbegin(), tmp.cend());

	for (size_t i = index + 1; i < vec.size(); i++)
	{
		GetAllSubSets_BACKTRACKING(vec, i, tmp, res);
	}
	if (!tmp.empty())
		tmp.pop_back();
}

vector<vector<int>> GetAllSubSets_CASCADING(const vector<int>& vec)
{
	vector<vector<int>> res(1);

	for (const size_t x : vec)
	{
		int SSSize = res.size();
		for (size_t i = 0; i < SSSize; i++)
		{
			vector<vector<int>>::const_iterator cItr = res.cbegin() + i;
			res.emplace_back(cItr->begin(), cItr->end());
			res.rbegin()->push_back(x);
		}
	}

	return res;
}

void Permutations(string& str, const int index, vector<string>& res)
{
	if (index == str.size() - 1)
		res.push_back(str);

	for (int j = index; j < str.size(); j++)
	{
		//cout << index << "<->" << j << "\t";
		SwapInString(str, index, j);
		Permutations(str, index + 1, res);
		SwapInString(str, j, index);
	}
	cout << endl;
}

void Permutations(const string& str)
{
	vector<string> vec;
	Permutations(const_cast<string&>(str), 0, vec);
}

void testSubsets()
{
	/*vector<int> tmp;
	vector<vector<int>> res;
	GetAllSubSets_BACKTRACKING({ 1,5,3 }, -1, tmp, res); //i.e The Power Set*/
	Permutations("ABC");
}
