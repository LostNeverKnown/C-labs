#pragma once
#include<vector>
#include<iostream>
#include<string>

template<typename T>
class AVL {
private:
	struct Node {
		T element;
		int height;
		Node* left;
		Node* right;
		Node(T element);
	};
	Node* root;
	void nodeDelete(Node*& node);
	struct AVL<T>::Node* recremove(T& element, Node*& removenode);
	void ToGraphvizHelper(std::string& listOfNodes, std::string& listOfConnections, Node* toWorkWith, size_t& uniqueID);
	void preOrder(std::vector<T>& treevec, Node*& node);
	void inOrder(std::vector<T>& treevec, Node*& node);
	void postOrder(std::vector<T>& treevec, Node*& node);
	int recheight(Node*& node);
	void balance(Node*& node);

public:
	AVL();
	~AVL();
	void insert(T& element);
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
inline AVL<T>::Node::Node(T element) : element(element), height(-1), left(nullptr), right(nullptr)
{

}

template<typename T>
inline AVL<T>::AVL() : root(nullptr)
{

}

template<typename T>
inline void AVL<T>::nodeDelete(Node*& node) {
	if (node != nullptr) {
		nodeDelete(node->left);
		nodeDelete(node->right);
		delete node;
		node = nullptr;
	}
}
template<typename T>
inline AVL<T>::~AVL() {
	nodeDelete(this->root);
}


template<typename T>
inline void AVL<T>::balance(Node*& node) {
	if (node->left != nullptr && node->right != nullptr) {
		int left = recheight(node->left);
		int right = recheight(node->right);
		if ((left + 1) != right && (left - 1) != right && left != right) {
			if (left > right) {

			}
			else {

			}
		}
	}
	else if (node->left != nullptr) {
		int left = recheight(node->left);
		if (left > 1) {
			//right rotation
		}
	}
	else {
		int right = recheight(node->right);
		if (right > 1) {
			//left rotation
		}
	}
}

template<typename T>
inline void AVL<T>::insert(T& element) { //Lägger till ett element i trädet. Inga duplicerade element skall tillåtas.
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
inline void AVL<T>::getMaxRemove(Node* thisnode, Node*& removenode) {
	while (thisnode && thisnode->right != nullptr)
		thisnode = thisnode->right;
	removenode = thisnode;
}
template<typename T>
inline void AVL<T>::remove(T element) { //Tar bort det efterfrågade elementet i trädet om det finns.
	if (find(element) == true) {
		recremove(element, this->root);
	}
}
template<typename T>
inline struct AVL<T>::Node* AVL<T>::recremove(T& element, Node*& removenode) {
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
inline bool AVL<T>::find(const T& element) const { //Letar upp det efterfrågade elementet i trädet. Returnerar true om det finns, false om det inte finns.
	Node* current = this->root;
	if (current == nullptr)
		return false;
	else {
		Node* value = new Node(this->root->element);
		while (current != nullptr) {
			value->element = current->element;
			if (current->element == element)
				current = nullptr;
			else if (element > current->element)
				current = current->right;
			else
				current = current->left;
		}
		if (value->element == element) {
			delete value;
			return true;
		}
		else
			delete value;
		return false;
	}
}

template<typename T>
inline void AVL<T>::preOrder(std::vector<T>& treevec, Node*& node) {
	if (node != nullptr) {
		treevec.push_back(node->element);
		preOrder(treevec, node->left);
		preOrder(treevec, node->right);
	}
}
template<typename T>
inline std::vector<T> AVL<T>::preOrderWalk() { //Traverserar trädet enligt principen preorder och lägger till varje node värde i vector - objektet
	std::vector<T> vec;
	preOrder(vec, this->root);
	return vec;
}


template<typename T>
inline void AVL<T>::inOrder(std::vector<T>& treevec, Node*& node) {
	if (node != nullptr) {
		inOrder(treevec, node->left);
		treevec.push_back(node->element);
		inOrder(treevec, node->right);
	}
}
template<typename T>
inline std::vector<T> AVL<T>::inOrderWalk() { //Traverserar trädet enligt principen in order och lägger till varje nods värde i vector - objektet.
	std::vector<T> vec;
	inOrder(vec, this->root);
	return vec;
}


template<typename T>
inline void AVL<T>::postOrder(std::vector<T>& treevec, Node*& node) {
	if (node != nullptr) {
		postOrder(treevec, node->left);
		postOrder(treevec, node->right);
		treevec.push_back(node->element);
	}
}
template<typename T>
inline std::vector<T> AVL<T>::postOrderWalk() { //Traverserar trädet enligt principen post order och lägger till varje nods värde i vector - objektet.
	std::vector<T> vec;
	postOrder(vec, this->root);
	return vec;
}


template<typename T>
inline int AVL<T>::recheight(Node*& node) {
	if (node == nullptr)
		return -1;
	else {
		int left = recheight(node->left);
		int right = recheight(node->right);
		if (left > right)
			return (left + 1);
		else
			return (right + 1);
	}
}
template<typename T>
inline int AVL<T>::getTreeHeight() { //Returnerar höjden på trädet. Om trädet är tomt returnerar ni - 1.
	return recheight(this->root);
}

template<typename T>
inline T& AVL<T>::getMin() const { //Returnerar det minsta värdet i trädet.
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
inline T& AVL<T>::getMax() const { //Returnerar det största värdet i trädet.
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
std::string AVL<T>::ToGraphviz() // Member function of the AVLTree class
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
void AVL<T>::ToGraphvizHelper(std::string& listOfNodes, std::string& listOfConnections, Node* toWorkWith, size_t& uniqueID) // Member function of the AVLTree class
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