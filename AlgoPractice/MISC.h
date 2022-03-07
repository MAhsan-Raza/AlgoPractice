#pragma once

//DDAAABCAZCC -> A4BC3D2Z
void EncodeString(const string& inStr, string& outStr)
{}

//DDAAABCAZCC -> D2A4BC3Z
void EncodeString2(const string& inStr, string& outStr)
{}

void CalcContainersWDiscount(const vector<pair<int, int>>& data)
{
	for (const auto& x : data)
	{
		int extra = 0;
		int CanReturn = x.first;
		const int freeOnCount = x.second;
		int total = CanReturn;

		while (CanReturn != 0)
		{
			int GotFree = CanReturn / freeOnCount;
			if (GotFree == 0)
				break;
			extra = CanReturn % freeOnCount;
			total += GotFree;
			CanReturn = GotFree + extra;
		}

		cout << "Can Purchase= " << x.first << ", One free on=" << x.second << ", Total containers got=" << total << endl;
	}
}

void testMISC()
{
	CalcContainersWDiscount(
		{
			{7, 3},
			{4, 2},
			{2, 5}
		}
	);
}