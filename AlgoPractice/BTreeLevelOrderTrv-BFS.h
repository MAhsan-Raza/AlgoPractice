#pragma once

#include "BTreeDFS.h"

void printBFS(BTreeNode* head)
{
	if (!head)	return;

	queue<BTreeNode*> q;
	q.push(head);

	while (!q.empty())
	{
		BTreeNode* tmp = q.front();
		q.pop();
		cout << tmp->val << " -> ";

		if (tmp->left)
			q.push(tmp->left);
		if (tmp->right)
			q.push(tmp->right);
	}
}

vector<vector<int>> retrieveBFS(BTreeNode* root)
{
	vector<vector<int>> res;
	if (!root)	return res;

	queue<BTreeNode*> qMain;
	queue<BTreeNode*> qOther;
	qMain.push(root);
	res.push_back(vector<int>());

	while (!qMain.empty() || !qOther.empty())
	{
		if (!qMain.empty())
		{
			res.rbegin()->push_back(qMain.front()->val);
			if (qMain.front()->left)	qOther.push(qMain.front()->left);
			if (qMain.front()->right)	qOther.push(qMain.front()->right);
			qMain.pop();
		}
		else
		{
			res.push_back(vector<int>());
			qMain.swap(qOther);
		}
	}
	return res;
}

vector<vector<int>> zigzagLevelOrder(BTreeNode* root)
{
	vector<vector<int>> res;
	if (!root)   return res;
	queue<BTreeNode*> q;
	q.push(root);
	bool ZigZag = false;
	while (!q.empty())
	{
		int sz = q.size();
		res.push_back(vector<int>(sz));

		int indxStart = ZigZag ? sz - 1 : 0;
		const int indxEnd = ZigZag ? 0 : sz - 1;

		while (true)
		{
			if (ZigZag && indxStart < indxEnd)
				break;
			if (!ZigZag && indxStart > indxEnd)
				break;

			*(res.rbegin()->begin() + indxStart) = q.front()->val;
			if (q.front()->left)		q.push(q.front()->left);
			if (q.front()->right)		q.push(q.front()->right);
			q.pop();
			ZigZag ? --indxStart : ++indxStart;
		}
		ZigZag = !ZigZag;
	}
	return res;
}

TreeNode* findSuccessor_LevelOrder(TreeNode* root, int key)
{
	if (!root)	return nullptr;

	queue<TreeNode*> qMain, qSide;
	qSide.push(root);
	bool returnNext = false;

	while (!qMain.empty() || !qSide.empty())
	{
		if (qMain.empty())
			qMain.swap(qSide);

		TreeNode* crnt = qMain.front();
		qMain.pop();

		if (returnNext)
			return crnt;
		else if (crnt->val == key)
			returnNext = true;

		if (crnt->left)			qSide.push(crnt->left);
		if (crnt->right)		qSide.push(crnt->right);
	}

	return nullptr;
}


Node* connectSiblings(Node* root)
{
	queue<Node*> qMain, qSide;
	if (root) qSide.push(root);
	Node* prevToConn = nullptr;

	while (!qMain.empty() || !qSide.empty())
	{
		if (qMain.empty())
		{
			prevToConn = nullptr;
			qMain.swap(qSide);
		}

		Node* crnt = qMain.front();
		qMain.pop();

		if (prevToConn)  prevToConn->next = crnt;
		prevToConn = crnt;

		if (crnt->left)          qSide.push(crnt->left);
		if (crnt->right)         qSide.push(crnt->right);
	}

	return root;
}

void BTreeLevelOrderTrv_BFS()
{
	/*BTreeNode* head =
		new BTreeNode(1,
			new BTreeNode(2,
				new BTreeNode(4),
				new BTreeNode(5)
			),
			new BTreeNode(3)
		);
	printBFS(head);
	retrieveBFS(head);
	auto x = zigzagLevelOrder(head);

	findSuccessor_LevelOrder(new TreeNode(1,
		new TreeNode(2,
			new TreeNode(4),
			new TreeNode(5)
		),
		new TreeNode(3)
	), 3)->val;

	findSuccessor_LevelOrder(new TreeNode(12,
		new TreeNode(7,
			new TreeNode(9),
			nullptr
		),
		new TreeNode(1,
			new TreeNode(10),
			new TreeNode(5)
		)
	), 9)->val;

	findSuccessor_LevelOrder(new TreeNode(12,
		new TreeNode(7,
			new TreeNode(9),
			nullptr
		),
		new TreeNode(1,
			new TreeNode(10),
			new TreeNode(5)
		)
	), 12)->val;

	findSuccessor_LevelOrder(new TreeNode(20,
		new TreeNode(10,
			new TreeNode(4),
			new TreeNode(18,
				new TreeNode(14,
					new TreeNode(13),
					new TreeNode(15)
				),
				new TreeNode(19)
			)
		),
		new TreeNode(26,
			new TreeNode(24),
			new TreeNode(27)
		)
	), 24)->val;

	findSuccessor_LevelOrder(new TreeNode(20,
		new TreeNode(10,
			new TreeNode(4),
			new TreeNode(18,
				new TreeNode(14,
					new TreeNode(13),
					new TreeNode(15)
				),
				new TreeNode(19)
			)
		),
		new TreeNode(26,
			new TreeNode(24),
			new TreeNode(27)
		)
	), 4)->val;*/

	/*
	* https://leetcode.com/problems/boundary-of-binary-tree/
	* https://leetcode.com/problems/time-needed-to-inform-all-employees/
	* https://leetcode.com/problems/unique-binary-search-trees/
	* https://leetcode.com/problems/count-univalue-subtrees/
	* https://leetcode.com/problems/reorder-routes-to-make-all-paths-lead-to-the-city-zero/
	* https://leetcode.com/problems/find-nearest-right-node-in-binary-tree/
	* https://leetcode.com/problems/count-nodes-with-the-highest-score/
	* https://leetcode.com/problems/binary-tree-vertical-order-traversal/
	* https://leetcode.com/problems/cousins-in-binary-tree/
	* https://leetcode.com/problems/the-time-when-the-network-becomes-idle/
	*/
}