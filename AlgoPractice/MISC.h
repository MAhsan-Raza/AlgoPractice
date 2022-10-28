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

// wrong description & solution on geeks for geeks
int findRepeat_my(int a, int b)
{
    double dA = a, dB = b, deci = 0;

    int digiTmp = deci = dA / dB;
    if (deci > 1)
        deci = deci - digiTmp;

    unordered_map<int, int> digiCounter;
    int count = 0;
    int prevDigi = 0;
    while (deci != 0)
    {
        deci *= double(10);
        int digi = round(deci);
        deci -= digi;

        if (prevDigi == 0 && digi == 0)
            return 0;
        if (prevDigi != 0 && digi != 0 && prevDigi == digi)
        {
            cout << a << " Vs " << b << " = 1" << endl;
            return 1;
        }

        if (digiCounter[digi] == 2)
            break;
        ++digiCounter[digi];
        prevDigi = digi;
    }

    for (auto x : digiCounter)
    {
        if (x.second >= 1)
            ++count;
    }

    cout << a << " Vs " << b << " = " << count << endl;
    return count;
}

// wrong description & solution on geeks for geeks
string fractionToDecimal(int numr, int denr)
{
    string res; // Initialize result

    map<int, int> mp;
    mp.clear();

    int rem = numr % denr;

    while ((rem != 0)
        && (mp.find(rem) == mp.end()))
    {
        mp[rem] = res.length();
        rem = rem * 10;

        int res_part = rem / denr;
        res += to_string(res_part);

        rem = rem % denr;
    }

    return (rem == 0) ? "" : res.substr(mp[rem]);
}

// shitty question & even shittier solution on geeks for geeks
int findRepeat(int p, int q)
{
	// checking if p is perfectly divisible by q
	if (p % q == 0)
		return 0;

	// performing basic division method (which we do manually ) and mapping remainders with their position	
	map<int, int>mapp;
	int initial_rem, i, rem, curr_dividend, temp, newRem = -1;
	initial_rem = p % q;
	curr_dividend = p % q;
	mapp[initial_rem] = 0;
	int z = 0;
	while (7)
	{

		i = 0;
		while (curr_dividend < q)
		{
			if (i == 0)
			{
				curr_dividend *= 10;

			}
			else
			{
				curr_dividend *= 10;
				z++;
			}
			i++;
		}
		temp = curr_dividend / q;
		newRem = curr_dividend % q;
		z++;
		//checking if current remainder is already present in map 
		// if not present then adding it into map 
		if (mapp.find(newRem) == mapp.end())
		{
			mapp[newRem] = z;
		}
		// if remainder is already present then 
		//returning the length (current position - initial position)	
		else
		{
			return z - mapp[newRem];
		}
		curr_dividend = newRem;
		// case when remainder is zero
		if (newRem == 0)
		{
			return 0;
		}


	}

}

//Prefix Sum & Postfix Sum
long long int project(const vector<long long int>& algoExperts, const vector<long long int>& Developers, int n)
{
    /*
    A = A0, A1, A2, A3, A4, A5
    D = D0, D1, D2, D3, D4


            A1*D0 + A2*D1 + A3*D2 + A4*D3 + A5*D4
    A0*D0 +         A2*D1 + A3*D2 + A4*D3 + A5*D4
    A0*D0 + A1*D1 +         A3*D2 + A4*D3 + A5*D4
    A0*D0 + A1*D1 + A2*D2 +         A4*D3 + A5*D4
    A0*D0 + A1*D1 + A2*D2 + A3*D3 +         A5*D4
    A0*D0 + A1*D1 + A2*D2 + A3*D3 + A4*D4
    */

    vector<long long int> prefixSums(n, 0);
    long long int pfxSm = 0;
    for (int i = 0; i < n - 1; i++)
    {
        pfxSm += algoExperts[i] * Developers[i];
        prefixSums[i] = pfxSm;        
    }
    for (int i = 0; i < n; i++)
        cout << "PreFix:- " << i << " * " << i << " @ [" << i << "] = " << prefixSums[i] << endl;

    cout << endl;

    vector<long long int> postfixSums(n, 0);
    pfxSm = 0;
    for (int i = n - 1; i > 0; i--)
    {
        pfxSm += algoExperts[i] * Developers[i - 1];
        postfixSums[i] = pfxSm;        
    }

    for (int i = n - 1; i >= 0; i--)
        cout << "PostFix:- " << i << " * " << i - 1 << " @ [" << i << "] = " << postfixSums[i] << endl;

    cout << endl;

    long long int maxProj = INT_MIN;

    for (int skpIndx = 0; skpIndx < n; skpIndx++)
    {
        long long int crntProj = 0;

        int prfIndx = skpIndx - 1;
        int pstIndx = skpIndx + 1;

        cout << "skpIndx = " << skpIndx << ":- ";

        if (prfIndx >= 0)
        {
            crntProj += prefixSums[prfIndx];
            cout << prefixSums[prfIndx] << " + ";
        }

        if (pstIndx < n)
        {
            crntProj += postfixSums[pstIndx];
            cout << postfixSums[pstIndx];
        }

        cout << " = " << crntProj << endl;

        maxProj = max(maxProj, crntProj);
    }

    return maxProj;
}


// Why it is not an unbounded knapsack???????
bool is_possibleMatrixEndJumps(vector<vector<int>> MTX, int N)
{
    vector<vector<bool>> vztd(N + 1, vector<bool>(N + 1, false));

    function<bool(int, int)> is_possibleMate = [&](const int x, const int y)->bool
    {
        if (x == N - 1 && y == N - 1)
            return true;
        if (x < 0 || y < 0 || x >= N || y >= N || MTX[x][y] == 0 || vztd[x][y])
            return false;

        vztd[x][y] = true;

        bool bRes = false;

        int crntDist = MTX[x][y];
        while (!bRes && crntDist > 0)
            bRes = is_possibleMate(x, y - crntDist--);

        crntDist = MTX[x][y];
        while (!bRes && crntDist > 0)
            bRes = is_possibleMate(x, y + crntDist--);

        crntDist = MTX[x][y];
        while (!bRes && crntDist > 0)
            bRes = is_possibleMate(x - crntDist--, y);

        crntDist = MTX[x][y];
        while (!bRes && crntDist > 0)
            bRes = is_possibleMate(x + crntDist--, y);

        return bRes;
    };

    return is_possibleMate(0, 0);
}

void testMISC()
{
	/*CalcContainersWDiscount(
		{
			{7, 3},
			{4, 2},
			{2, 5}
		}
	);

    findRepeat(1, 2);
    findRepeat(22, 7);
    findRepeat(8, 2);
    findRepeat(2, 25);
    findRepeat(19, 25);
    findRepeat(23, 28);*/

    project({ 42, 22, 36, 40, 9, 47 }, { 40, 41, 47, 43, 15 }, 6);

    // Why it is not an unbounded knapsack???????
    is_possibleMatrixEndJumps(
        {
            { 3, 0, 0, 2 },
            { 0, 2, 1, 1 },
            { 1, 0, 0, 0 },
            { 0, 4, 0, 0 }
        }
    );

    // Why it is not an unbounded knapsack???????
    is_possibleMatrixEndJumps(
        {
            { 1, 2, 0 },
            { 0, 0, 2 },
            { 3, 0, 1 }
        }
    );

}