#pragma once

using BTreeNode = struct _BTreeNode
{
    int val = 0;
    _BTreeNode* left;
    _BTreeNode* right;

    _BTreeNode(int x, _BTreeNode* l, _BTreeNode* r) : val(x), left(l), right(r) {}
    _BTreeNode(int x) : _BTreeNode(x, nullptr, nullptr) {}
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

void testBTree()
{
    /*BTreeNode* head = new BTreeNode(1, new BTreeNode(2, new BTreeNode(4), new BTreeNode(5)),
        new BTreeNode(3, new BTreeNode(6), new BTreeNode(7)));*/

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

    /*BTreeNode* head
        = new BTreeNode(0,
            new BTreeNode(2,
                new BTreeNode(-2),
                nullptr),
            new BTreeNode(8)
        );

    BTreeTargetSum(head, 0);*/
    minDepth(head);
}