#pragma once

/*
        Use top-down either skip or pick
            go untill m&n>=0 or indx,
            which makes it a 3d memoaization problem
            DEC 0s or 1s req for each step (or no if skp case)
            return max of SKPD / PCKD
    */
inline int findMaxForm(const vector<string>& strs, const int m, const int n)
{
    const int N = strs.size();
    vector<pair<int, int>> subStrCounts; // number of zeros (in first) vs number of ones (in second)
    for (int i = 0; i < N; i++)
    {
        int zrs = 0, ons = 0;
        for (int j = 0; j < strs[i].size(); j++)
        {
            if (strs[i][j] == '0')
                ++zrs;
            else ++ons;
        }
        subStrCounts.emplace_back(zrs, ons);
    }

    vector<vector<vector<int>>> memChc(N + 1, vector<vector<int>>(m + 1, vector<int>(n + 1, -1)));

    function<int(int, int, int)> getMaxSSets = [&](const int indx, const int remZrs, const int remOns)->int
    {
        if ( /*remZrs == 0 || remOns == 0 ||*/ indx == N)    // No need to check then=m since we are checking before picking also, if either of them become Zero we can still pic subset with only the other one
            return 0;

        if (memChc[indx][remZrs][remOns] == -1)
        {
            int pck = 0;
            if (subStrCounts[indx].first <= remZrs && subStrCounts[indx].second <= remOns)
                pck = 1 + getMaxSSets(indx + 1, remZrs - subStrCounts[indx].first, remOns - subStrCounts[indx].second);

            int skp = getMaxSSets(indx + 1, remZrs, remOns);
            memChc[indx][remZrs][remOns] = max(pck, skp);
        }
        return memChc[indx][remZrs][remOns];
    };

    return getMaxSSets(0, m, n);
}

void test3D_Memoaization()
{
    findMaxForm({ "10","0001","111001","1","0" }, 5, 3);
    findMaxForm({ "10","0","1" }, 1, 1);
}