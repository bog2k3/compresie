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

	TreeNode(char ch, bool bit)
		: ch(ch), bit(bit) {
	}
};

class TreeBuilder {
public:
	static TreeNode* buildHuffmanTree(std::map<char, double> const& stats);

private:
	static TreeNode* createNode(std::vector<std::pair<char, double>>::iterator it);
};

#endif /* TREEBUILDER_H_ */
