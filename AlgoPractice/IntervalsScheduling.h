#pragma once

enum class IntervalRelations
{
	A_ENDS_IN_B = 0,	//but A doesn't starts inside B
	A_ISOVERLAPPING_B,	//
	B_ISOVERLAPPING_A,
	SEPARATE_INTERVALS

};

vector<vector<int>> mergeLeetCode(vector<vector<int>>& intervals) {

    vector<vector<int>> mergedIntervals;
    if (false == intervals.empty()) mergedIntervals;
    auto IntervalComparer = [](const vector<int>& A, const vector<int>& B)
    { 
        return *A.begin() < *B.begin(); 
    };
    sort(intervals.begin(), intervals.end(), IntervalComparer);

    int prevStart = *(intervals.begin()->begin());
    int prevEnd = *(intervals.begin()->begin() + 1);

    for (size_t i = 0; i < intervals.size(); i++)
    {
        int crntStart = *intervals[i].begin();
        int crntEnd = *(intervals[i].begin() + 1);

        if (prevEnd >= crntStart)    //B starts within A
        {
            prevEnd = max(crntEnd, prevEnd);    //In case A continues after B's end
        }
        else
        {
            mergedIntervals.push_back({ prevStart, prevEnd });
            prevStart = crntStart;  // Considering new interval
            prevEnd = max(crntEnd, prevEnd);
        }
    }

    //Insert last interval
    mergedIntervals.push_back({ prevStart, prevEnd });
    return mergedIntervals;
}

vector<vector<int>> insertInterval(vector<vector<int>>& intervals, const vector<int>& newInterval) {

    vector<vector<int>> res;
    if (true == intervals.empty())
    {
        res.push_back(newInterval);
        return res;
    }

    bool NotInserted = true;
    if (newInterval[0] <= intervals[0][0])
    {
        intervals.insert(intervals.begin(), newInterval);
        NotInserted = false;
    }
    else if (newInterval[0] >= (*intervals.rbegin())[0])
    {
        intervals.push_back(newInterval);
        NotInserted = false;
    }

    int newStart = newInterval[0];
    int newEnd = newInterval[1];

    int prevStart = intervals[0][0];
    int prevEnd = intervals[0][1];

    for (size_t i = 1; i < intervals.size(); i++)
    {
        int crntStart = intervals[i][0];
        int crntEnd = intervals[i][1];

        if (NotInserted && newStart <= crntStart)
        {
            intervals.insert(intervals.begin() + i, newInterval);
            --i;
            NotInserted = false;
            continue;
        }

        if (crntStart <= prevEnd)
        {
            prevEnd = max(prevEnd, crntEnd);
        }
        else
        {
            res.push_back({ prevStart, prevEnd });
            prevStart = crntStart;
            prevEnd = crntEnd;
        }
    }

    res.push_back({ prevStart, prevEnd });
    return res;
}

vector<vector<int>> IntervalIntersection(const vector<vector<int>>& v1, const vector<vector<int>>& v2)
{
    vector<vector<int>>::const_iterator cI1 = v1.cbegin();
    vector<vector<int>>::const_iterator cI2 = v2.cbegin();
    vector<vector<int>> res;

    while(cI1 != v1.cend() && cI2 != v2.cend())
    {
        int start1 = *cI1->begin();
        int end1 = *(cI1->begin() + 1);
        int start2 = *cI2->begin();
        int end2 = *(cI2->begin() + 1);

        if (end1 < start2)
        {
            ++cI1;
        }
        else if (end2 < start1)
        {
            ++cI2;
        }
        else
        {
            res.push_back({ max(start1, start2), min(end1, end2) });
            end1 < end2 ? ++cI1 : ++cI2;
        }
    }

    return res;
}

void testIntervalScheduling()
{
    /*vector<vector<int>> x = {{2,6}, {1,3}, {8,10}, {15,18}};
    PrintVecOfVec(x, "-> ");
    auto res = mergeLeetCode(x);
    PrintVecOfVec(res, "-> ");
    vector<vector<int>> x = { {1, 3},{6, 9} };
    PrintVecOfVec(insertInterval(x, { 2, 6 }), "-> ");
    x = { {2, 3},{6, 9} };
    PrintVecOfVec(insertInterval(x, { 1, 1 }), "-> ");
    x = { {1, 3},{6, 9} };
    PrintVecOfVec(insertInterval(x, { 10, 11 }), "-> ");
    x = { {1, 3},{6, 9} };
    PrintVecOfVec(insertInterval(x, { 4, 7 }), "-> ");
    x = { {1, 3},{6, 9} };
    PrintVecOfVec(insertInterval(x, { 2, 4 }), "-> ");*/
    IntervalIntersection({ {0,2}, {5,10}, {13,23}, {24,25} }, { {1,5}, {8,12}, {15,24}, {25,26 } });
}
