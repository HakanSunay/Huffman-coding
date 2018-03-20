#include <bitset>
#include <iostream>
#include "BinaryTree.h"
#include <string>
#include <fstream>
#include <vector>
using namespace std;
using myPair = pair<char, unsigned>;

void sortVec(vector<pair<char,unsigned>>& freqTable)
{
	for (int i = 0; i < freqTable.size() - 1; i++)
	{
		int mindex = i;
		for (int j = i + 1; j < freqTable.size(); j++)
		{
			if (freqTable[mindex].second > freqTable[j].second)
			{
				mindex = j;
			}
		}
		swap(freqTable[mindex], freqTable[i]);
	}
}
vector<pair<char,unsigned>> createFrequencyTable(string info,string& readText)
{
	ifstream readFrom;
	readFrom.open(info);
	string myStr;
	getline(readFrom, myStr);
	readText = myStr;
	vector<pair<char, unsigned>> freqTable;
	for (int i = 0; i < myStr.length(); i++)
	{
		bool seen = false;
		for (int k = freqTable.size() - 1; k >= 0; k--)
		{

			if (!freqTable.empty())
			{
				if (myStr[i] == freqTable[k].first)
				{
					seen = true;
					continue;
				}
			}
		}
		if (seen == false)
		{
			int count = 0;
			for (int j = i; j < myStr.length(); j++)
			{
				if (myStr[i] == myStr[j])
				{
					count++;
				}
			}
			freqTable.push_back(make_pair(myStr[i], count));
		}
	}
	sortVec(freqTable);
	return freqTable;
}
void reArrange(vector<pair<char, unsigned>>& myVec)
{
	for (int i = 1; i < myVec.size()-1; i++)
	{
		myVec[i] = myVec[i + 1];
	}
}
void createCodingTable(BinaryTree<pair<char, unsigned>>* myTree, vector<pair<char, string>>& holder)
{
	if (myTree->getLeftChild() == nullptr && myTree->getRightChild() == nullptr)
		holder.push_back(make_pair(myTree->getData().first, myTree->getPath()));
	if (myTree->getLeftChild() != nullptr)
		createCodingTable(myTree->getLeftChild(), holder);
	if (myTree->getRightChild() != nullptr)
		createCodingTable(myTree->getRightChild(), holder);

	return;
}
string findChar(char ser, vector<pair<char, string>> codingTable)
{
	int i = 0;
	while (ser!=codingTable[i].first)
	{
		i++;
	}
	return codingTable[i].second;
}
void getBinCode(vector<pair<char, string>> codingTable,string input, string& binCode)
{
	for (int i = 0; i < input.length(); i++)
	{
		binCode = binCode + findChar(input[i],codingTable);
	}
}
int bitStringToBigDecimal(string binCode) {

	unsigned int value = 0;
	unsigned int indexCounter = 0;
	for (int i = binCode.length() - 1; i >= 0; i--) {

		if (binCode[i] == '1') {
			value += pow(2, indexCounter);
		}
		indexCounter++;
	}
	return value;
}
vector<string> binCodeDivisor(string binCode)
{
	vector<string> binContainer;
	if (binCode.length() >= 8)
	{
		for (int i = 0; i < binCode.length(); i += 8)
		{
			binContainer.push_back(binCode.substr(i, 8));
		}
	}
	else
		binContainer.push_back(binCode);
	return binContainer;
}
void serialize(BinaryTree<myPair> *root, ofstream &fp)
{
	// If current node is NULL, store marker
	if (root == NULL)
	{
		fp << '.';
		return;
	}

	// Else, store current node and recur for its children
	fp << root->getData().first;
	serialize(root->getLeftChild(), fp);
	serialize(root->getRightChild(), fp);
}
string fromTreeToString(BinaryTree<char>* ptr, string binCode)
{
	BinaryTree<char>* begin = ptr;
	string res = "";
	int i = 0;
	while (i <= binCode.size())
	{
		if (binCode[i] == '0' && begin->getLeftChild() != nullptr)
			begin = begin->getLeftChild();
		else if (binCode[i] == '1' && begin->getRightChild() != nullptr)
			begin = begin->getRightChild();
		else
		{
			if (begin->getData() != '#')
			{
				res += begin->getData();
				begin = ptr;
				i--;
			}
		}
		i++;
	}
	return res;
}
int main()
{
	string choice;
	cout << "To encode, please enter E!\n> ";
	cin >> choice;
	while (choice != "E")
	{
		cout << "Wrong key!\nRe-enter E, please!\n> ";
		cin >> choice;
	}
	//whole encoding process


	//gets input string that is to be encoded
	cout << "Now, input file name:\n> ";
	string input;
	cin >> input;
	string readText = "";

	//----

	//creates the frequency table of letters

	vector<myPair> myVect = createFrequencyTable(input, readText);
	BinaryTree<myPair>* arrTree;

	//----

	//creating tree of letters

	arrTree = new BinaryTree<myPair>[myVect.size()];
	for (int i = 0; i < myVect.size(); i++)
		{
			arrTree[i].setData(myVect[i]);
		}
	BinaryTree<myPair>* tempArr = new BinaryTree<myPair>[myVect.size()];
	BinaryTree<myPair>* tempLocator = new BinaryTree<myPair>[myVect.size()];
	BinaryTree<myPair>* tempLocator2 = new BinaryTree<myPair>[myVect.size()];
	int size = myVect.size();
	int k = 0;
	while (size > 1)
		{
			tempLocator[k] = arrTree[0];
			tempLocator2[k] = arrTree[1];
			tempArr[k].addLeftChild(tempLocator[k]);
			tempArr[k].addRightChild(tempLocator2[k]);
			tempArr[k].setData(make_pair('#', tempLocator[k].getData().second + tempLocator2[k].getData().second));
			arrTree[0] = tempArr[k];
			for (int i = 1; i < size - 1; i++)
			{
				arrTree[i] = arrTree[i + 1];
			}
			size--;
			for (int i = 0; i < size - 1; i++)
			{
				int mindex = i;
				for (int j = i + 1; j < size; j++)
				{
					if (arrTree[mindex].getData().second > arrTree[j].getData().second)
					{
						mindex = j;
					}
				}
				swap(arrTree[mindex], arrTree[i]);
			}


			k++;
		}

	//----

	//setting the paths for binCode

	arrTree->setMyPaths();
	BinaryTree<myPair>* p = arrTree;

	//----

	//creating the coding table

	vector<pair<char, string>> codingTable;
	createCodingTable(arrTree, codingTable);
	string binCode = "";
	getBinCode(codingTable, readText, binCode);

	//----

	//transforming binCode to ints and saving into a file

	vector<string> binsContainer = binCodeDivisor(binCode);
	vector<int> intHolder;
	ofstream writeInto;
	writeInto.open("writeInto.txt");
	for (int i = 0; i < binsContainer.size(); i++)
		{
			intHolder.push_back(bitStringToBigDecimal(binsContainer[i]));
			if (i == 0)
				writeInto << binCode.size() << "\n" << intHolder[i];
			else
				writeInto << " " << intHolder[i];

		}
	writeInto.close();
	cout << "Encoding completed!\nYou can check (writeInto.txt)!" << endl;

	//serialize
	ofstream treeKeeper("binTree.txt");
	serialize(arrTree, treeKeeper);
	cout << "Serialization completed, check (binTree.txt)!\n";
	treeKeeper.close();
	//----

	//--------------------------------------------

	//
	
	
	//whole decoding process


	cout << "To decode, please enter D!\n> ";
	cin >> choice;
	while (choice != "D")
	{
		cout << "Wrong key!\nRe-enter D, please!\n> ";
		cin >> choice;
	}
	//----

	//deserialize and get decoded string, using binCode
	cout << "Now, enter serialized binary tree file name:\n> ";
	string btfilename;
	cin >> btfilename;
	ifstream treeData(btfilename);
	BinaryTree<char>* ptr = nullptr;
	ptr = ptr->deSerialize(treeData);

	cout << "Now, enter encoded file name, to be decoded!\n> ";
	string encodedFilename;
	cin >> encodedFilename;

	//gets binCode from coded string

	int sizeOfBinCode;
	ifstream readMe(encodedFilename);
	readMe >> sizeOfBinCode;
	int* numHolder = new int[sizeOfBinCode];
	int i = 0;
	while (readMe)
	{
		readMe >> numHolder[i];
		i++;
	}
	int helperSize = sizeOfBinCode;
	int t = 0;
	string BinCodeHolder = "";
	while (helperSize > 8)
	{
		bitset<8> toBin(numHolder[t]);
		BinCodeHolder += toBin.to_string();
		t++;
		helperSize -= 8;
	}
	static unsigned int const newSize = helperSize;
	if (helperSize > 0 && helperSize < 8)
	{
		char* sizeChar = new char[helperSize];
		sizeChar[helperSize] = '\0';
		for (int i = 0; i < helperSize; i++)
		{
			sizeChar[i] = '0';
		}
		for (int pos = helperSize - 1; pos >= 0; --pos)
		{
			if (numHolder[t] % 2)
				sizeChar[pos] = '1';
			else
				sizeChar[pos] = '0';
			numHolder[t] /= 2;
		}
		string binHelperSize(sizeChar);
		BinCodeHolder += binHelperSize;
	}
	string test;
	test = fromTreeToString(ptr, binCode);

	//----


	//----
	cout << "End of decoding!" << endl;
	cout << "The result is: \n" << test << endl;
	//end of decoding
	return 0;
}

