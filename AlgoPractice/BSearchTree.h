#pragma once

using BSTNode = struct _BSTNode {

	int data;

	_BSTNode* left;
	_BSTNode* right;

	_BSTNode(int data, _BSTNode* left, _BSTNode* right) : data(data), left(left), right(right) {}
	_BSTNode(int data) : _BSTNode(data, nullptr, nullptr) {}
	_BSTNode() : _BSTNode(0, nullptr, nullptr) {}
};

/*
* Count of Smaller Numbers After Self
* 
* Given an integer array nums, return an integer array counts where counts[i] is the number of smaller elements to the right of nums[i].
*/
vector<int> countSmaller_BruteForce(const vector<int>& nums, long long& itrations)
{
    vector<int> res(nums.size(), 0);

    for (int i = 0; i < nums.size(); i++)
    {
        for (int j = 0; j < i; j++)
        {
            ++itrations;
            if (nums[j] > nums[i])
                ++res[j];
        }
    }

    return move(res);
}

vector<int> countSmaller_RedBlackTree(const vector<int>& nums, long long& itrations)
{
    multimap<int, int> numVsIndx;

    for (int i = 0; i < nums.size(); i++)
    {
        ++itrations;
        numVsIndx.emplace(nums[i], i);
    }

    vector<int> res(nums.size(), 0);

    for (int i = 0; i < nums.size(); i++)
    {
        map<int, int>::iterator itr = numVsIndx.find(nums[i]);

        while (--itr != numVsIndx.end())
        {
            ++itrations;
            if (itr->second > i)
                ++res[i];
        }
    }
    return res;
}


void displayTwoTimeStamps(const time_point<system_clock>& t1, const time_point<system_clock>& t2, const time_point<system_clock>& t3)
{
    auto BFrAprch = std::chrono::duration_cast<std::chrono::milliseconds>(t2 - t1);
    auto RbTAprch = std::chrono::duration_cast<std::chrono::milliseconds>(t3 - t2);

    cout << "Brute force-------- " << BFrAprch.count() << endl;
    cout << "Red-Black Tree----- " << BFrAprch.count() << endl;
    cout << endl;
}

void CompareTwoVecsSameLength(const vector<int>& res1, const vector<int>& res2)
{
    for (int i = 0; i < res1.size(); i++)
    {
        if (res1[i] != res2[i])
            cout << "Error:- Different Results";
    }
}

void testBSearchTree(const vector<int>& nums)
{
    /*auto XRes = countSmaller_RedBlackTree({5,2,6,1});
    XRes = countSmaller_RedBlackTree({ 12, 1, 2, 3, 0, 11, 4 });
    XRes = countSmaller_RedBlackTree({ 5, 4, 3, 2, 1 });
    XRes = countSmaller_RedBlackTree({ 1, 2, 3, 4, 5 });
    XRes = countSmaller_RedBlackTree({ -1 });
    XRes = countSmaller_RedBlackTree({ 1, -1 });
    XRes = countSmaller_RedBlackTree({ -1, -1 });*/

    
    int count = 5;

    while (count-- > 0)
    {
        //auto t1 = system_clock::now();
        long long BTFCOUNT = 0;
        auto xBF = countSmaller_BruteForce(nums, BTFCOUNT);
        //auto t2 = system_clock::now();
        long long RBTCOUNT = 0;
        auto xRbT = countSmaller_RedBlackTree(nums, RBTCOUNT);

        cout << "Brute force-------- " << BTFCOUNT << endl;
        cout << "Red-Black Tree----- " << RBTCOUNT << endl;
        cout << endl;
        //auto t3 = system_clock::now();

        //CompareTwoVecsSameLength(xBF, xRbT);
        //displayTwoTimeStamps(t1, t2, t3);
    }
}