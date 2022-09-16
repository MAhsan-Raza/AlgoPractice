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

void BTreeLevelOrderTrv_BFS()
{
	BTreeNode* head =
		new BTreeNode(3,
			new BTreeNode(9,
				new BTreeNode(11),
				new BTreeNode(30)
			),
			new BTreeNode(20,
				new BTreeNode(15),
				nullptr
			)
		);
	/*printBFS(head);
	retrieveBFS(head);
	auto x = zigzagLevelOrder(head);*/
}