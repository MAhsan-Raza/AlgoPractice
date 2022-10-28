#pragma once

#include "BTreeDFS.h"

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

/*
    Traverse to the most suitable parent node
        while position is empty & staisfy BST
    insert at either left or right
*/
TreeNode* insertIntoBST(TreeNode* root, int val)
{
    if (nullptr == root) return new TreeNode(val);

    TreeNode* crnt = root;

    while (crnt)
    {
        if (val > crnt->val)
        {
            if (nullptr == crnt->right)
            {
                crnt->right = new TreeNode(val);
                break;
            }
            else crnt = crnt->right;
        }
        else if (val < crnt->val)
        {
            if (nullptr == crnt->left)
            {
                crnt->left = new TreeNode(val);
                break;
            }
            else crnt = crnt->left;
        }
        // no else since "It is guaranteed that the new value does not exist in the original BST."
    }

    return root;
}

int rangeSumBST(TreeNode* root, int low, int high)
{
    function<int(TreeNode*)> getSum = [&](TreeNode* const crnt)->int
    {
        if (nullptr == crnt)
            return 0;

        int sum = 0;
        if (crnt->val >= low && crnt->val <= high)
            sum += crnt->val;

        if (crnt->val < low)
            sum += getSum(crnt->right);
        else if (crnt->val > high)
            sum += getSum(crnt->left);
        else
            sum += (getSum(crnt->left) + getSum(crnt->right));

        return sum;
    };

    return getSum(root);
}

void testBSearchTree_(const vector<int>& nums)
{
    /*auto XRes = countSmaller_RedBlackTree({5,2,6,1});
    XRes = countSmaller_RedBlackTree({ 12, 1, 2, 3, 0, 11, 4 });
    XRes = countSmaller_RedBlackTree({ 5, 4, 3, 2, 1 });
    XRes = countSmaller_RedBlackTree({ 1, 2, 3, 4, 5 });
    XRes = countSmaller_RedBlackTree({ -1 });
    XRes = countSmaller_RedBlackTree({ 1, -1 });
    XRes = countSmaller_RedBlackTree({ -1, -1 });

    
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
    }*/


}

TreeNode* increasingBST(TreeNode* root)
{
    TreeNode* prevNode = nullptr;
    function<TreeNode* (TreeNode*)> convToIBST = [&](TreeNode* const crnt)->TreeNode*
    {
        if (nullptr == crnt)
            return root;

        convToIBST(crnt->left);

        if (nullptr == prevNode)
            root = prevNode = crnt;
        else
        {
            prevNode->right = crnt;
            prevNode = crnt;
        }

        convToIBST(crnt->right);
        crnt->left = nullptr;
        return root;
    };

    return convToIBST(root);
}

void dfs(TreeNode* crnt)
{
    if (!crnt)return;
    dfs(crnt->left);
    cout << "Node:- [" << crnt->val << "], L[" << crnt->left << "], R[" << crnt->right << "]" << endl;
    dfs(crnt->right);
}

void testBSearchTree()
{
    rangeSumBST(
        new TreeNode(10,
            new TreeNode(5,
                new TreeNode(3),
                new TreeNode(7)),
            new TreeNode(15,
                nullptr,
                new TreeNode(18))
        ),
        7, 15
    );

    TreeNode* res = increasingBST(
        new TreeNode(2, 
            new TreeNode(1), 
            new TreeNode(4,
                new TreeNode(3), 
                nullptr
            )
        )
    );
    

    /*
    * https://leetcode.com/problems/two-sum-iii-data-structure-design/
    * https://leetcode.com/problems/two-sum-bsts/
    */
}