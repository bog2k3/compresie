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
	char ch;
	bool bit;

	TreeNode* pLeft = nullptr;
	TreeNode* pRight = nullptr;
	TreeNode* pParent = nullptr;

	TreeNode(char ch, bool bit, TreeNode* pParent)
		: ch(ch), bit(bit), pParent(pParent) {
	}

	~TreeNode() {
		if (pLeft)
			delete pLeft;
		if (pRight)
			delete pRight;
	}
	void getBitSequence(std::vector<bool> &out);
};

class TreeBuilder {
public:
	static TreeNode* buildHuffmanTree(std::map<char, double> const& stats);

private:
	static TreeNode* createNode(std::vector<std::pair<char, double>>::iterator it, TreeNode* pParent);
};

#endif /* TREEBUILDER_H_ */
