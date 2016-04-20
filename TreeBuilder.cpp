/*
 * TreeBuilder.cpp
 *
 *  Created on: Apr 17, 2016
 *      Author: alexandra
 */

#include "TreeBuilder.h"
#include <algorithm>

void TreeNode::getBitSequence(std::vector<bool> &out) {
	if (pParent) {
		pParent->getBitSequence(out);
		out.push_back(bit);
	} else
		return;
}

void TreeNode::split() {
	if (ch.size() < 2)
		return;
	double totalWeight = 0;
	for (auto p : ch)
		totalWeight += p.second;
	double halfWeight = totalWeight / 2;

	// impartim nodul astfel incat in stanga ponderile insumate ale caracterelor
	// sa fie cat mai apropiate (dar mai mici) de jumatate din total (halfWeight)
	double summedWeight = ch[0].second;
	for (unsigned i=1; i<ch.size()-1; i++) {
		if (summedWeight + ch[i].second >= halfWeight) {
			pLeft = new TreeNode(decltype(ch)(ch.begin(), ch.begin()+i), false, this);
			pLeft->split();
			pRight = new TreeNode(decltype(ch)(ch.begin()+i, ch.end()), true, this);
			pRight->split();
			break;
		}
		summedWeight += ch[i].second;
	}
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

	TreeNode* root = new TreeNode(std::move(statList), false, nullptr);
	root->split();

	return root;
}
