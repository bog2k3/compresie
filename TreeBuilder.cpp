/*
 * TreeBuilder.cpp
 *
 *  Created on: Apr 17, 2016
 *      Author: alexandra
 */

#include "TreeBuilder.h"
#include <algorithm>

TreeNode* TreeBuilder::createNode(std::vector<std::pair<char, double>>::iterator it) {
	TreeNode* pNode = new TreeNode('\0', true);
	pNode->pLeft = new TreeNode(it->first, false);
	return pNode;
}

TreeNode* TreeBuilder::buildHuffmanTree(std::map<char, double> const& stats) {
	// transformam dictionarul intr-o lista:
	std::vector<std::pair<char, double>> statList;
	for (auto p : stats)
		statList.push_back(p);
	// sortam lista dupa numarul de aparitii (cel mai mare la inceput)
	std::sort(statList.begin(), statList.end(), [](std::pair<char, double> &l, std::pair<char, double> &r) {
		return l.second > r.second;
	});

	auto it = statList.begin();
	TreeNode* root = createNode(it);
	TreeNode* last = root;
	while (++it != statList.end()) {
		last->pRight = createNode(it);
		last = last->pRight;
	}

	return root;
}
