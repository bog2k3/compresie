/*
 * TreeBuilder.h
 *
 *  Created on: Apr 17, 2016
 *      Author: alexandra
 */

#ifndef TREEBUILDER_H_
#define TREEBUILDER_H_

struct TreeNode {
	// ...
	TreeNode* pNext = nullptr;
};

class TreeBuilder {
public:
	static TreeNode* buildHuffmanTree(std::map<char, double> const& stats);
};

#endif /* TREEBUILDER_H_ */
