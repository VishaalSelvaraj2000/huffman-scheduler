#pragma once

#include <stdlib.h>
#include <stdbool.h>

namespace FGK {

	const int INVALID = -1;
	typedef struct node_t {
		bool isZero;
		bool isRoot;
		bool isLeaf;

		struct node_t *parent;
		struct node_t *left_child;
		struct node_t *right_child;

		int symbol;
		unsigned long long int value;
		int order;
	}Node;

	typedef struct symbol_t {
		int symbol;
		Node* tree;
	}Symbol;

	class FGKTree {
	private:
		int alphabet_size;
		Symbol** symbols;
		Node** zeroNode;
		Node** root;
		bool* codebuffer;

		Node* createTree();
		void updateTree(Node* currNode);
		Node* findReplaceNode(Node* currMax, Node* root);
		void swapNodes(Node* x, Node* y);
		Node* addChild(Node* parent, int symbol, int order, int value, bool isZero, bool isRoot);
		Node* addSymbol(int symbol);
		
		bool* codeOfNode(Node* node, int *n);
		void reverseCode(bool *code, int codeSize);
	public:
		FGKTree(int n);
		FGKTree();
		//~FGKTree();
		Node* getRootNode();
		Node* getTreeFromSymbol(int symbol);
		void encode(int symbol, bool** code, int* code_length);
		void remove(int symbol);
		int getDepth(int symbol);
		void update(int symbol);
	};

}