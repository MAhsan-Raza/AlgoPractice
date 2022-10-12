#pragma once

vector<vector<int>> reconstructQueue(vector<vector<int>>& people)
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    vector<vector<int>> resQ(people.size(), vector<int>(2, -1));

    sort(people.begin(), people.end(), [](const vector<int>& a1, const vector<int>& a2)->bool
        {
            if (a1.front() == a2.front())
                return a1.back() < a2.back();
            else
                return a1.front() < a2.front();
        });

    /*
    * now vector is sorted by height & number of ppl on front allowed
    * smallest height first & if the height is same smallest num_of_ppl_front first
    * we should pick each one & check from the front that how many should we skip before insert it
    *   pairs with smaller height doesn't count
    *   only pairs with greator heigh or empty pairs (that would be filled by greator heights after) should be counted
    */

    for (int i = 0; i < people.size(); i++)
    {
        //int destIndx = getPosToInsert(i);
        int destIndx = 0;
        int toSkip = people[i][1];
        int heightToIns = people[i][0];

        while (destIndx < people.size() - 1)
        {
            if (toSkip == 0)
            {
                if (resQ[destIndx][0] == -1)
                    break;
            }
            else
            {
                if (resQ[destIndx][0] == -1 || resQ[destIndx][0] >= heightToIns)
                    --toSkip;
            }
            ++destIndx;
        }
        resQ[destIndx][0] = people[i][0];
        resQ[destIndx][1] = people[i][1];
    }

    return resQ;
}

inline bool increasingTriplet(const vector<int>& nums)
{
    int backMax = INT_MIN;
    vector<int> backMaxs(nums.size(), 0);

    for (int i = nums.size() - 1; i >= 0; i--)
        backMax = backMaxs[i] = max(nums[i], backMax);

    int crntMin = INT_MAX;
    for (int i = 0; i < nums.size(); i++)
    {
        if (nums[i] <= crntMin)
            crntMin = nums[i];
        else
        {
            if (i == nums.size() - 1)
                break;

            if (nums[i] < backMaxs[i + 1])
                return true;
        }
    }

    return false;
}


void testGreedyAlgos()
{
    vector<vector<int>> y = { {7,0} ,{4,4}, {7,1}, {5,0}, {6,1}, {5,2} };
    y = { {6,0} ,{5,0}, {4,0}, {5,1}, {3,2}, {2,2}, {1,4} };
    //y = { {9,0}, {7,0}, {1,9}, {3,0}, {2,7}, {5,3}, {6,0}, {3,4}, {6,2}, {5,2} };
    //y = { {40,11},{81,12},{32,60},{36,39},{76,19},{11,37},{67,13},{45,39},{99,0},{35,20},{15,3},{62,13},{90,2},{86,0},{26,13},{68,32},{91,4},{23,24},{73,14},{86,13},{62,6},{36,13},{67,9},{39,57},{15,45},{37,26},{12,88},{30,18},{39,60},{77,2},{24,38},{72,7},{96,1},{29,47},{92,1},{67,28},{54,44},{46,35},{3,85},{27,9},{82,14},{29,17},{80,11},{84,10},{5,59},{82,6},{62,25},{64,29},{88,8},{11,20},{83,0},{94,4},{43,42},{73,9},{57,32},{76,24},{14,67},{86,2},{13,47},{93,1},{95,2},{87,8},{8,78},{58,16},{26,75},{26,15},{24,56},{69,9},{42,22},{70,17},{34,48},{26,39},{22,28},{21,8},{51,44},{35,4},{25,48},{78,18},{29,30},{13,63},{68,8},{21,38},{56,20},{84,14},{56,27},{60,40},{98,0},{63,7},{27,46},{70,13},{29,23},{49,6},{5,64},{67,11},{2,31},{59,8},{93,0},{50,39},{84,6},{19,39} };
    auto x = reconstructQueue(y);

    increasingTriplet({ 1,2,3,4,5 });
    increasingTriplet({ 5,4,3,2,1 });
    increasingTriplet({ 2,1,5,0,4,6 });

    /*
    * https://leetcode.com/problems/count-special-quadruplets/
    * https://leetcode.com/tag/greedy/
    */
}