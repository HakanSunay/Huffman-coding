#pragma once
#include <iostream>
using namespace std;

//template <typename t>
//struct btelem 
//{
//	t data;
//	btelem *left, *right;
//	btelem(btelem *_left=nullptr,btelem *_right=nullptr,t _data=t())
//	{
//		left = _left;
//		right = _right;
//		data = _data;
//	}
//
//};

template <typename T>
class BinaryTree
{
private:
	T data;
	BinaryTree<T>* leftChild;
	BinaryTree<T>* rightChild;
	string path;
public:
	BinaryTree(T _data=T(), BinaryTree<T>* _leftChild=nullptr, BinaryTree<T>* _rightChild=nullptr, string _path="")
	{
		data = _data;
		leftChild = _leftChild;
		rightChild = _rightChild;
		path = _path;
	}
	bool operator!=(BinaryTree<T>& second)
	{
		if (this->data == second.getData() && this->getLeftChild() == second.getLeftChild() && this->getRightChild() == second.getRightChild())
			return true;
		return false;
	}
	BinaryTree<T>& operator=(BinaryTree<T> const& other)
	{
		/*deleteNodes(this);*/
		data = other.getData();
		leftChild = other.getLeftChild();
		rightChild = other.getRightChild();
		path = other.getPath();
		return *this;
	}
	BinaryTree(BinaryTree<T> const & other)
	{
		data = other.getData();
		leftChild = other.getLeftChild();
		rightChild = other.getRightChild();
		path = other.getPath();
	}
	/*void deleteNodes(BinaryTree<T>* ptr)
	{
		if (ptr == nullptr)
			return;
		deleteNodes(ptr->getLeftChild());
		deleteNodes(ptr->getRightChild());
		delete ptr;
	}*/
	bool isLeaf() const
	{
		if (leftChild == nullptr && rightChild == nullptr)
			return true;
		return false;
	}
	void addLeftChild(BinaryTree<T>& newLeftTree)
	{
		leftChild = &newLeftTree;
		//newLeftTree.path = "0" + newLeftTree.path;

	}
	void addRightChild(BinaryTree<T>& newRightTree)
	{
		rightChild = &newRightTree;
		//newRightTree.path = "1" + newRightTree.path;
	}
	T getData() const
	{
		return data;
	}
	void setData(T _data)
	{
		data = _data;
	}
	void setMyPaths()
	{
		while (leftChild != nullptr && rightChild != nullptr)
		{
			if (leftChild != nullptr) 
			{
				leftChild->setPath(this->getPath() + "0");
				leftChild->setMyPaths();
			}
			if (rightChild != nullptr)
			{
				rightChild->setPath(this->getPath() + "1");
				rightChild->setMyPaths();
			}
			return;
		}
	}
	BinaryTree<T>*& newNode(T key)
	{
		BinaryTree* temp = new BinaryTree;
		temp->setData(key);
		temp->leftChild = temp->rightChild = nullptr;
		return temp;
	}
	void print()
	{
		while (leftChild != nullptr && rightChild != nullptr)
		{
			//cout<<"Node : " << data
		}
	}
	BinaryTree<char>* deSerialize(ifstream& fp)
	{
		// Read next item from file. If theere are no more items or next
		// item is marker, then return
		char val;
		if (!fp.get(val) || (int)val == (int)'.')
			return nullptr;

		// Else create node with this item and recur for children
		BinaryTree<char>* root = newNode(val);
		root->leftChild = deSerialize(fp);
		root->rightChild = deSerialize(fp);
		return root;
	}
	void setPath(string _path)
	{
		path = _path;
	}
	string getPath() const
	{
		return path;
	}
	BinaryTree<T>* getLeftChild() const
	{
		return leftChild;
	}
	BinaryTree<T>*& getLeftChild()
	{
		return leftChild;
	}
	BinaryTree<T>* getRightChild() const
	{
		return rightChild;
	}
	BinaryTree<T>*& getRightChild()
	{
		return rightChild;
	}
	~BinaryTree()
	{
		/*deleteNodes(this);*/
	}
	//special constructor
	BinaryTree<pair<char,unsigned>>& operator+=(BinaryTree<pair<char, unsigned>>& second)
	{
		BinaryTree<pair<char, unsigned>> newTree;
		newTree = *this;
		unsigned sum = (getData().second) + (second.getData().second);
		addLeftChild(newTree);
		addRightChild(second);
		this->data.second = sum;
		this->data.first = '*';
		return *this;
	}
	BinaryTree<char>* fileToTree(ifstream& input_file)
	{
		char c;
		input_file >> c;
		if ((int)c == (int)'.' || !input_file)
			return nullptr;
		BinaryTree<char>* head = new BinaryTree<char>;
		head->data = c;
		head->leftChild = fileToTree(input_file);
		head->rightChild = fileToTree(input_file);
		return head;
	}
};

BinaryTree<pair<char,unsigned>> mergeThese(BinaryTree<pair<char, unsigned>>* first,BinaryTree<pair<char, unsigned>>* second)
{
	first->setPath("0" + first->getPath());
	second->setPath("1" + second->getPath());
	unsigned sum = (first->getData().second) + (second->getData().second);
	BinaryTree<pair<char, unsigned>>* newTree;
	newTree = new BinaryTree<pair<char, unsigned>>(make_pair('*', sum), first, second, "");
	return *newTree;
}

