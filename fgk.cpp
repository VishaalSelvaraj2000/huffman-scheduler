
#include "fgk.h"

using namespace FGK;

Node* FGKTree::createTree() {
	Node* node = (Node*)malloc(sizeof(Node));
	node->isRoot = true;
	node->isLeaf = true;
	node->isZero = true;

	node->left_child = NULL;
	node->right_child = NULL;
	node->parent = NULL;

	node->symbol = INVALID;
	node->value = 0;
	node->order = alphabet_size << 1;
	
	return node;
}

Node* FGKTree::findReplaceNode(Node* currMax, Node* node) {
	Node* result = currMax;
	if (node->value > result->value && !node->isLeaf) {
		Node* greatestLeft = findReplaceNode(result, node->left_child);
		if (greatestLeft) result = greatestLeft;

		Node* greatestRight = findReplaceNode(result, node->right_child);
		if (greatestRight) result = greatestRight;
	}
	else if (result->value == node->value && node->order > result->order) {
		result = node;
	}

	return (result != currMax) ? result : NULL;
}

void FGKTree::swapNodes(Node* x, Node* y) {
	int temp_order = x->order;
	x->order = y->order;
	y->order = temp_order;

	if (x->parent->left_child == x) {
		x->parent->left_child = y;
	}
	else {
		x->parent->right_child = y;
	}

	if (y->parent->left_child == y) {
		y->parent->left_child = x;
	}
	else {
		y->parent->right_child = x;
	}

	Node* temp_parent = x->parent;
	x->parent = y->parent;
	y->parent = temp_parent;

}

Node* FGKTree::addChild(Node* parent, int symbol, int order, int value, bool isZero, bool isRoot) {
	Node* child = (Node*)malloc(sizeof(Node));
	child->isLeaf = true;
	child->isRoot = isRoot;
	child->isZero = isZero;
	child->order = order;
	child->symbol = symbol;
	child->parent = parent;
	child->value = value;
	child->left_child = NULL;
	child->right_child = NULL;
	return child;
}

Node* FGKTree::addSymbol(int symbol) {
	Node* previousZeroNode = *zeroNode;
	Node* rightChild = addChild(*zeroNode, symbol, previousZeroNode->order - 1, 1, false, false);
	Node* leftChild = addChild(*zeroNode, INVALID, previousZeroNode->order - 2, 0, true, false);
	previousZeroNode->isLeaf = false;
	previousZeroNode->isZero = false;
	previousZeroNode->left_child = leftChild;
	previousZeroNode->right_child = rightChild;

	symbols[symbol] = (Symbol*)malloc(sizeof(Symbol));
	symbols[symbol]->symbol = symbol;
	symbols[symbol]->tree = rightChild;

	
	*zeroNode = leftChild;
	return previousZeroNode;
}

void FGKTree::updateTree(Node *currNode) {
	while (!currNode->isRoot) {
		Node *replaceNode = findReplaceNode(currNode, *root);

		if (replaceNode && currNode->parent != replaceNode) {
			swapNodes(currNode, replaceNode);
		}

		(currNode->value)++;
		currNode = currNode->parent;
	}

	(currNode->value)++;
}

void FGKTree::reverseCode(bool *code, int codeSize) {
	if (code == NULL) {
		return;
	}

	bool *start = code;
	bool *end = code + (codeSize - 1);

	while (start < end) {
		int temp = *start;
		*start = *end;
		*end = temp;
		start++;
		end--;
	}
}

bool* FGKTree::codeOfNode(Node *node, int *n) {
	Node *current = node;

	int i = 0;
	while (!current->isRoot) {
		Node *parent = current->parent;
		codebuffer[i] = (parent->left_child == current) ? 0 : 1;
		current = current->parent;
		i++;
	}
	reverseCode(codebuffer, i);

	*n = i;
	return codebuffer;
}

Node* FGKTree::getTreeFromSymbol(int symbol) {
	Symbol *symbolPtr = symbols[symbol];

	if (!symbolPtr) {
		return NULL;
	}

	return symbolPtr->tree;
}

FGKTree::FGKTree(int n) {
	alphabet_size = n;
	root = new Node*;
	zeroNode = new Node*;
	*root = createTree();
	*zeroNode = *root;
	symbols = (Symbol**)calloc(n, sizeof(Symbol*));
	codebuffer = (bool*)malloc(sizeof(bool) * 2 * n);
}

void FGKTree::encode(int symbol, bool** code, int *code_length) {
	Node* node = getTreeFromSymbol(symbol);

	if (node) {
		*code = codeOfNode(node, code_length);
		updateTree(node);
	}
	else {
		*code = codeOfNode(*zeroNode, code_length);
		Node* newNode = addSymbol(symbol);
		updateTree(newNode);
	}
}

void FGKTree::update(int symbol) {
	Node* node = getTreeFromSymbol(symbol);
	if (node == NULL) {
		node = addSymbol(symbol);
	}
	updateTree(node);
}

Node* FGKTree::getRootNode() {
	return *root;
}

int FGKTree::getDepth(int symbol) {
	Node* node = getTreeFromSymbol(symbol);
	int x = 0;
	while (!node->isRoot) {
		x++;
		node = node->parent;
	}
	return x;
}

void FGKTree::remove(int symbol) {
    Node* node = getTreeFromSymbol(symbol);
    node->value = 0;
}

FGKTree::FGKTree() {
	//default-constructor
}