#pragma once

using BSTNode = struct _BSTNode {

	int data;

	_BSTNode* left;
	_BSTNode* right;

	_BSTNode(int data, _BSTNode* left, _BSTNode* right) : data(data), left(left), right(right) {}
	_BSTNode(int data) : _BSTNode(data, nullptr, nullptr) {}
	_BSTNode() : _BSTNode(0, nullptr, nullptr) {}
};

