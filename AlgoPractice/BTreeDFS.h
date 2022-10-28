#pragma once

#define NONODE INT_MAX;

using BTreeNode = struct _BTreeNode
{
    int val = 0;
    _BTreeNode* left;
    _BTreeNode* right;

    _BTreeNode(int x, _BTreeNode* l, _BTreeNode* r) : val(x), left(l), right(r) {}
    _BTreeNode(int x) : _BTreeNode(x, nullptr, nullptr) {}

    /*_BTreeNode(int val, int lval, int rval)
    {
        this->val = val;
        this->left = (lval != NONODE) ? new _BTreeNode(lval) : nullptr;
        this->right = (rval != NONODE) ? new _BTreeNode(rval) : nullptr;
    }*/
};

using TreeNode = BTreeNode;

using Node = struct _Node
{
    int val = 0;
    _Node* left;
    _Node* right;
    _Node* next;

    _Node(int x, _Node* l, _Node* r) : val(x), left(l), right(r), next(nullptr) {}
    _Node(int x) : _Node(x, nullptr, nullptr) {}
};

void BTreeDFSPrint(BTreeNode* head)
{
    if (!head)   return;

    BTreeDFSPrint(head->left);
    BTreeDFSPrint(head->right);
    cout << head->val << " -> ";
}

bool BTreeTargetSum(BTreeNode* head, int Target)
{
    if (!head)   return false;

    Target -= head->val;
    if (0 == Target && !head->right && !head->left)
        return true;

    if (BTreeTargetSum(head->left, Target) || BTreeTargetSum(head->right, Target))
        return true;

    return false;
}

inline void minDepth(BTreeNode* crnt, int depth, int& minDep)
{
    if (!crnt)               return;
    if (depth >= minDep)   return;

    if (!crnt->left && !crnt->right)
        minDep = min(depth, minDep);

    minDepth(crnt->left, depth + 1, minDep);
    minDepth(crnt->right, depth + 1, minDep);
}

int minDepth(BTreeNode* root)
{
    int MD = INT_MAX;
    minDepth(root, 0, MD);
    return MD;
}


using ManagerMap = unordered_map<int, vector<int>>;

inline void MaxTimeForALeaf(int crntID, ManagerMap& managerMap, const vector<int>& informTime, int leafTime, int& maxLeafTime)
{
    leafTime += informTime[crntID];

    const vector<int>& sbordnts = managerMap[crntID];

    if (sbordnts.empty())
        maxLeafTime = max(maxLeafTime, leafTime);
    else
    {
        for (auto x : sbordnts)
        {
            MaxTimeForALeaf(x, managerMap, informTime, leafTime, maxLeafTime);
        }
    }
}

inline int numOfMinutes(int n, int headID, const vector<int>& manager, const vector<int>& informTime)
{
    if (n == 0) return 0;
    int totalTime = 0;
    ManagerMap managerMap;

    for (int i = 0; i < manager.size(); i++)
        if (informTime[i] != 0)
            managerMap[manager[i]].push_back(i);

    MaxTimeForALeaf(headID, managerMap, informTime, 0, totalTime);
    return totalTime;
}

inline void pathSum(TreeNode* crnt, int targetSum, vector<int>& pathNodes, vector<vector<int>>& res)
{
    pathNodes.push_back(crnt->val);
    targetSum -= crnt->val;

    if (!crnt->left && !crnt->right)
    {
        if (0 == targetSum)
            res.push_back(pathNodes);
    }
    else
    {
        if (crnt->left)  pathSum(crnt->left, targetSum, pathNodes, res);
        if (crnt->right) pathSum(crnt->right, targetSum, pathNodes, res);
    }
    pathNodes.pop_back();
}

inline vector<vector<int>> pathSum(TreeNode* root, int targetSum)
{
    vector<int> pathNodes;
    vector<vector<int>> res;
    if (!root)   return res;
    pathSum(root, targetSum, pathNodes, res);
    return move(res);
}

// Return count of all path (either complete or partial) that sums up to target
int pathSumThree(TreeNode* root, int targetSum)
{   
    unordered_map<int, int> prefixSums;

    function<int(TreeNode*, int)> pathSumCountWNegtvs = [targetSum, &prefixSums, &pathSumCountWNegtvs](TreeNode* crnt, int crntSum)->int
    {
        if(crnt)
        {
            crntSum += crnt->val;
            ++prefixSums[crntSum];

            int nCount = (crntSum == targetSum) ? 1 : 0;                
            auto itr = prefixSums.find(crntSum - targetSum);
            nCount += (itr == prefixSums.end()) ? 0 : itr->second;

            nCount += pathSumCountWNegtvs(crnt->left, crntSum);
            nCount += pathSumCountWNegtvs(crnt->right, crntSum);
            
            --prefixSums[crntSum];
            return nCount;
        }

        return 0;
    };

    return pathSumCountWNegtvs(root, 0);
}

int sumDigits(TreeNode* root)
{
    std::function<int(TreeNode*, int)> sumDigis = [&sumDigis](TreeNode* crnt, int sum)->int
    {
        if (!crnt->left && !crnt->right)
            return sum + crnt->val;
        
        int crntFactr = (sum + crnt->val) * 10, sumT = 0;
        if (crnt->left)      sumT += sumDigis(crnt->left, crntFactr);
        if (crnt->right)     sumT += sumDigis(crnt->right, crntFactr);
        return sumT;
    };

    return !root ? 0 : sumDigis(root, 0);
}

bool PathWithGivenSequence(TreeNode* root, const vector<int>& seq)
{
    std::function<bool(TreeNode*, int)> findSeq = [&](TreeNode* crnt, int mtchPos)->bool
    {
        if (!crnt)   return false;

        if (crnt->val == seq[mtchPos])
        {
            if (++mtchPos == seq.size())
                return true;
        }
        else mtchPos = 0;

        return findSeq(crnt->left, mtchPos) || findSeq(crnt->right, mtchPos);
    };

    return seq.empty() ? false : findSeq(root, 0);
}

int GetBTreeDiameter(TreeNode* root)
{
    int diam = INT_MIN;
    function<int(TreeNode*, int&)> getMaxPath = [&getMaxPath](TreeNode* crnt, int& diam)->int
    {
        if (!crnt)      return 0;

        int leftArm = getMaxPath(crnt->left, diam);
        int rightArm = getMaxPath(crnt->right, diam);
        diam = max(diam, 1 + leftArm + rightArm);

        return 1 + max(leftArm, rightArm);
    };

    getMaxPath(root, diam);
    return diam;
}

int maxPathSum(TreeNode* root) 
{

    int maxArmSum = root ? root->val : 0;
    function<int(TreeNode*, int&)> getMaxPath = [&getMaxPath](TreeNode* crnt, int& maxArmSum)->int
    {
        if (!crnt)      return 0;

        int leftArm = getMaxPath(crnt->left, maxArmSum);
        int rightArm = getMaxPath(crnt->right, maxArmSum);

        maxArmSum = max(maxArmSum, crnt->val + (leftArm >= 0 ? leftArm : 0) + (rightArm >= 0 ? rightArm : 0));
        return crnt->val + max((leftArm >= 0 ? leftArm : 0), (rightArm >= 0 ? rightArm : 0));
    };

    getMaxPath(root, maxArmSum);
    return maxArmSum;
}

void testBTree()
{
    /*BTreeNode* head = new BTreeNode(1, new BTreeNode(2, new BTreeNode(4), new BTreeNode(5)),
        new BTreeNode(3, new BTreeNode(6), new BTreeNode(7)));

    BTreeNode* head
        = new BTreeNode(5,
            new BTreeNode(4,
                new BTreeNode(11,
                    new BTreeNode(7),
                    nullptr
                ),
                nullptr),
            new BTreeNode(8,
                new BTreeNode(13),
                new BTreeNode(4,
                    nullptr,
                    new BTreeNode(1)
                )
            )
        );

    BTreeNode* head
        = new BTreeNode(0,
            new BTreeNode(2,
                new BTreeNode(-2),
                nullptr),
            new BTreeNode(8)
        );

    BTreeTargetSum(head, 0);
    minDepth(head);


    numOfMinutes(6, 2, { 2,2,-1,2,2,2 }, { 0,0,1,0,0,0 });
    numOfMinutes(1, 0, { -1 }, { 0 });
    numOfMinutes(15, 0, { -1, 0, 0, 1, 1, 2, 2, 3, 3, 4, 4, 5, 5, 6, 6 }, { 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0 });
    numOfMinutes(11, 4, { 5, 9, 6, 10, -1, 8, 9, 1, 9, 3, 4 }, { 0, 213, 0, 253, 686, 170, 975, 0, 261, 309, 337 });


    sumDigits(new TreeNode(1, new TreeNode(2), new TreeNode(3)));
    sumDigits(new TreeNode(1, new TreeNode(2), nullptr));
    sumDigits(new TreeNode(1, nullptr, new TreeNode(3)));
    sumDigits(nullptr);
    sumDigits(new TreeNode(1, new TreeNode(2, nullptr, new TreeNode(9)), new TreeNode(3)));

    PathWithGivenSequence(new TreeNode(1, new TreeNode(7), new TreeNode(9, new TreeNode(2), new TreeNode(9))), { 1, 9, 9 });
    PathWithGivenSequence(new TreeNode(1, new TreeNode(7), new TreeNode(9, new TreeNode(2), new TreeNode(9))), { 1, 7 });
    PathWithGivenSequence(new TreeNode(1, new TreeNode(7), new TreeNode(9, new TreeNode(2), new TreeNode(9))), { 20 });
    PathWithGivenSequence(new TreeNode(1, new TreeNode(7), new TreeNode(9, new TreeNode(2), new TreeNode(9))), { 1, 22 });
    PathWithGivenSequence(new TreeNode(1, new TreeNode(7), new TreeNode(9, new TreeNode(2), new TreeNode(9))), {  });
    PathWithGivenSequence(new TreeNode(1, new TreeNode(7), new TreeNode(9, new TreeNode(2), new TreeNode(9))), { 1, 9, 2, 100 });
    PathWithGivenSequence(new TreeNode(1, new TreeNode(0, new TreeNode(1), nullptr), new TreeNode(1, new TreeNode(6), new TreeNode(5))), { 1, 0, 7 });
    PathWithGivenSequence(new TreeNode(1, new TreeNode(0, new TreeNode(1), nullptr), new TreeNode(1, new TreeNode(6), new TreeNode(5))), { 1, 1, 6 });
    PathWithGivenSequence(new TreeNode(5, new TreeNode(2, new TreeNode(1), new TreeNode(4,
        new TreeNode(6), new TreeNode(8))), new TreeNode(3)), { 5, 2, 4, 8 });
    PathWithGivenSequence(new TreeNode(5, new TreeNode(2, new TreeNode(1), new TreeNode(4,
        new TreeNode(6), new TreeNode(8))), new TreeNode(3)), { 5, 3, 4, 9 });*/


    /*pathSumThree(
        new TreeNode(10,
            new TreeNode(5,
                new TreeNode(3,
                    new TreeNode(3),
                    new TreeNode(-2)
                ),
                new TreeNode(2,
                    nullptr,
                    new TreeNode(1)
                )
            ),
            new TreeNode(-3,
                nullptr,
                new TreeNode(11)
            )
        ), 8);

    //                  x
    //[5,4,8,11,null,13,4,7,2,null,null,5,1]

    pathSumThree(
        new TreeNode(5,
            new TreeNode(4,
                new TreeNode(11,
                    new TreeNode(7),
                    new TreeNode(2)),
                nullptr
            ),
            new TreeNode(8,
                new TreeNode(13),
                new TreeNode(4,
                    new TreeNode(5),
                    new TreeNode(1))
            )
        ), 22);

    pathSumThree(new TreeNode(-2, nullptr, new TreeNode(-3)), -5);

    pathSumThree(new TreeNode(1, new TreeNode(-2), new TreeNode(-3)), -2);

    pathSumThree(new TreeNode(1, new TreeNode(-2, new TreeNode(1), new TreeNode(3)), nullptr), 3);*/

    GetBTreeDiameter(new TreeNode(1,
            new TreeNode(-2,
                new TreeNode(1,
                    new TreeNode(-1),
                    nullptr),
                new TreeNode(3)),
            new TreeNode(-3,
                new TreeNode(-2),
                nullptr))
    );

    GetBTreeDiameter(new TreeNode(1,
        new TreeNode(2),
        new TreeNode(3,
            new TreeNode(5,
                new TreeNode(7),
                new TreeNode(8,
                    new TreeNode(10),
                    nullptr)),
            new TreeNode(6,
                new TreeNode(9,
                    new TreeNode(11),
                    nullptr),
                nullptr)))
    );

    maxPathSum(new TreeNode(9,
        new TreeNode(6),
        new TreeNode(-3,
            new TreeNode(-6),
            new TreeNode(2,
                new TreeNode(2,
                    new TreeNode(-6,
                        new TreeNode(-6),
                        nullptr),
                    new TreeNode(-6)),
                nullptr)))
    );

    /*
    * http://lixinchengdu.github.io/algorithmbook/leetcode/path-sum-iv.html
    * https://leetcode.com/problems/find-elements-in-a-contaminated-binary-tree/
    * https://leetcode.com/problems/reachable-nodes-with-restrictions/
    */
}