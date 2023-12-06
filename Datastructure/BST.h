#pragma once
#include<vector>
#include<iostream>
#include<string>

template<typename T>
class BST {
private:
	struct Node {
		T element;
		Node* left;
		Node* right;
		Node(T element);
	};
	Node* root;
	void nodeDelete(Node*& node);
	struct BST<T>::Node* recremove(T& element, Node*& removenode);
	void ToGraphvizHelper(std::string& listOfNodes, std::string& listOfConnections, Node* toWorkWith, size_t& uniqueID);
	void preOrder(std::vector<T>& treevec, Node*& node);
	void inOrder(std::vector<T>& treevec, Node*& node);
	void postOrder(std::vector<T>& treevec, Node*& node);
	int recheight(Node*& node);

public:
	BST();
	~BST();
	void insert(const T& element);
	void remove(T element);
	bool find(const T& element) const;
	std::vector<T> preOrderWalk();
	std::vector<T> inOrderWalk();
	std::vector<T> postOrderWalk();
	int getTreeHeight();
	void getMaxRemove(Node* thisnode, Node*& removenode);
	T& getMin() const;
	T& getMax() const;
	std::string ToGraphviz();
};

template<typename T>
inline BST<T>::Node::Node(T element) : element(element), left(nullptr), right(nullptr)
{

}

template<typename T>
inline BST<T>::BST() : root(nullptr)
{

}

template<typename T>
inline void BST<T>::nodeDelete(Node*& node) {
	if (node != nullptr) {
		nodeDelete(node->left);
		nodeDelete(node->right);
		delete node;
		node = nullptr;
	}
}
template<typename T>
inline BST<T>::~BST() {
	nodeDelete(this->root);
}


template<typename T>
inline void BST<T>::insert(const T& element) { //Lägger till ett element i trädet. Inga duplicerade element skall tillåtas.
	if (this->root == nullptr) {
		this->root = new Node(element);
	}
	else {
		Node* current = root;
		Node* parent = nullptr;
		while (current != nullptr) {
			if (current->element == element) {//Check för duplicate
				current = nullptr;
				parent = nullptr;
			}
			else {
				parent = current;
				if (element < current->element) {
					current = current->left;
				}
				else {
					current = current->right;
				}
			}
		}
		if (parent != nullptr) {
			if (element < parent->element) {
				parent->left = new Node(element);
			}
			else {
				parent->right = new Node(element);
			}
		}
	}
}


template<typename T>
inline void BST<T>::getMaxRemove(Node* thisnode, Node*& removenode) {
	while (thisnode && thisnode->right != nullptr)
		thisnode = thisnode->right;
	removenode = thisnode;
}
template<typename T>
inline void BST<T>::remove(T element) {
	recremove(element, this->root);
}
template<typename T>
inline struct BST<T>::Node* BST<T>::recremove(T& element, Node*& removenode) {
	if (removenode == nullptr)
		return removenode;
	if (element < removenode->element)
		removenode->left = recremove(element, removenode->left);
	else if (element > removenode->element)
		removenode->right = recremove(element, removenode->right);
	else {
		if (removenode->left == nullptr && removenode->right == nullptr) {
			delete removenode;
			removenode = nullptr;
			return nullptr;
		}
		else if (removenode->left == nullptr) {
			Node* temp = removenode->right;
			delete removenode;
			removenode = nullptr;
			return temp;
		}
		else if (removenode->right == nullptr) {
			Node* temp = removenode->left;
			delete removenode;
			removenode = nullptr;
			return temp;
		}
		else {
			Node* temp;
			getMaxRemove(removenode->left, temp);

			removenode->element = temp->element;
			removenode->left = recremove(temp->element, removenode->left);
		}
	}
	return removenode;
}


template<typename T>
inline bool BST<T>::find(const T& element) const { //Letar upp det efterfrågade elementet i trädet. Returnerar true om det finns, false om det inte finns.
	Node* current = this->root;
	while (current != nullptr) {
		if (current->element == element)
			return true;
		else if (element > current->element)
			current = current->right;
		else
			current = current->left;
	}
	return false;
}


template<typename T>
inline void BST<T>::preOrder(std::vector<T>& treevec, Node*& node) {
	if (node != nullptr) {
		treevec.push_back(node->element);
		preOrder(treevec, node->left);
		preOrder(treevec, node->right);
	}
}
template<typename T>
inline std::vector<T> BST<T>::preOrderWalk() { //Traverserar trädet enligt principen preorder och lägger till varje node värde i vector - objektet
	std::vector<T> vec;
	preOrder(vec, this->root);
	return vec;
}


template<typename T>
inline void BST<T>::inOrder(std::vector<T>& treevec, Node*& node) {
	if (node != nullptr) {
		inOrder(treevec, node->left);
		treevec.push_back(node->element);
		inOrder(treevec, node->right);
	}
}
template<typename T>
inline std::vector<T> BST<T>::inOrderWalk() { //Traverserar trädet enligt principen in order och lägger till varje nods värde i vector - objektet.
	std::vector<T> vec;
	inOrder(vec, this->root);
	return vec;
}


template<typename T>
inline void BST<T>::postOrder(std::vector<T>& treevec, Node*& node) {
	if (node != nullptr) {
		postOrder(treevec, node->left);
		postOrder(treevec, node->right);
		treevec.push_back(node->element);
	}
}
template<typename T>
inline std::vector<T> BST<T>::postOrderWalk() { //Traverserar trädet enligt principen post order och lägger till varje nods värde i vector - objektet.
	std::vector<T> vec;
	postOrder(vec, this->root);
	return vec;
}


template<typename T>
inline int BST<T>::recheight(Node*& node) {
	if (node != nullptr) {
		int left = recheight(node->left);
		int right = recheight(node->right);
		if (left < right)
			return (right + 1);
		else
			return (left + 1);
	}
	else {
		return -1;
	}
}
template<typename T>
inline int BST<T>::getTreeHeight() { //Returnerar höjden på trädet. Om trädet är tomt returnerar ni - 1.
	return recheight(this->root);
}


template<typename T>
inline T& BST<T>::getMin() const { //Returnerar det minsta värdet i trädet.
	Node* current = this->root;
	if (current == nullptr)
		throw std::out_of_range("Tree is empty!");
	else {
		while (current->left != nullptr)
			current = current->left;
		return current->element;
	}
}


template<typename T>
inline T& BST<T>::getMax() const { //Returnerar det största värdet i trädet.
	Node* current = this->root;
	if (current == nullptr)
		throw std::out_of_range("Tree is empty!");
	else {
		while (current->right != nullptr)
			current = current->right;
		return current->element;
	}
}


template <typename T>
std::string BST<T>::ToGraphviz() // Member function of the AVLTree class
{
	std::string toReturn = "";
	if (this->root) // root is a pointer to the root node of the tree
	{
		std::string listOfNodes;
		std::string listOfConnections = std::string("\t\"Root\" -> ") + std::to_string(0) + std::string(";\n");
		toReturn += std::string("digraph {\n");
		size_t id = 0;
		ToGraphvizHelper(listOfNodes, listOfConnections, root, id);
		toReturn += listOfNodes;
		toReturn += listOfConnections;
		toReturn += std::string("}");
	}
	return toReturn;
}
template <typename T>
void BST<T>::ToGraphvizHelper(std::string& listOfNodes, std::string& listOfConnections, Node* toWorkWith, size_t& uniqueID) // Member function of the AVLTree class
{
	size_t myID = uniqueID;
	listOfNodes += std::string("\t") + std::to_string(myID) + std::string(" [label=\"") + std::to_string(toWorkWith->element) + std::string("\"];\n");
	if (toWorkWith->left)
	{
		listOfConnections += std::string("\t") + std::to_string(myID) + std::string(" -> ") + std::to_string(uniqueID + 1) + std::string(" [color=blue];\n");
		ToGraphvizHelper(listOfNodes, listOfConnections, toWorkWith->left, ++uniqueID);
	}
	else
	{
		listOfNodes += std::string("\t") + std::to_string(++uniqueID) + std::string(" [label=") + std::string("nill, style = invis];\n");
		listOfConnections += std::string("\t") + std::to_string(myID) + std::string(" -> ") + std::to_string(uniqueID) + std::string(" [ style = invis];\n");
	}

	if (toWorkWith->right)
	{
		listOfConnections += std::string("\t") + std::to_string(myID) + std::string(" -> ") + std::to_string(uniqueID + 1) + std::string(" [color=red];\n");
		ToGraphvizHelper(listOfNodes, listOfConnections, toWorkWith->right, ++uniqueID);
	}
	else
	{
		listOfNodes += std::string("\t") + std::to_string(++uniqueID) + std::string(" [label=") + std::string("nill, style = invis];\n");
		listOfConnections += std::string("\t") + std::to_string(myID) + std::string(" -> ") + std::to_string(uniqueID) + std::string(" [ style = invis];\n");
	}
}