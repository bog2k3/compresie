/*
 * TreeBuilder.h
 *
 *  Created on: Apr 17, 2016
 *      Author: alexandra
 */

#ifndef TREEBUILDER_H_
#define TREEBUILDER_H_

#include <vector>
#include <map>

struct TreeNode {
	std::vector<std::pair<char, double>> ch;	// caracterele de sub nodul curent
	bool bit;									// bitul asociat nodului curent (0/1)

	TreeNode* pLeft = nullptr;
	TreeNode* pRight = nullptr;
	TreeNode* pParent = nullptr;

	TreeNode(std::vector<std::pair<char, double>> &&ch, bool bit, TreeNode* pParent)
		: ch(std::move(ch)), bit(bit), pParent(pParent) {
	}

	~TreeNode() {
		if (pLeft)
			delete pLeft;
		if (pRight)
			delete pRight;
	}

	bool isLeaf() { return pLeft == nullptr && pRight == nullptr; }
	void getBitSequence(std::vector<bool> &out);
	void split();
};

class TreeBuilder {
public:
	static TreeNode* buildHuffmanTree(std::map<char, double> const& stats);
};

#endif /* TREEBUILDER_H_ */
