#include<iostream>
#include <fstream>
#include "Header.h"
#include "Header2.h"
#include <Windows.h>
#include <string>
using namespace std;



class intNode {
public:
	int data;
	intNode* next;
	fileNode index;
};

class intList {
public:
	intNode* head;
	intList() {
		head = NULL;
	}

	int findRangeLocation(int noOfNodes, int num) {
		intNode* temp = head;
		int loc = 0;
		for (loc = 0; loc < noOfNodes;loc++) {
			if (num <= temp->data) {
				break;
			}
			temp = temp->next;
		}
		return loc;
	}

	intNode* getNode(int at) {
		intNode* temp = head;
		for (int i = 0; i < at; i++) {
			temp = temp->next;
		}
		return temp;
	}

	int insert(int data, string loc) {
		intNode* newNode = new intNode;
		newNode->data = data;
		newNode->next = NULL;
		newNode->index.location = loc;
		if (!head) {
			head = newNode;
			return 0;
		}
		if (data < head->data) {
			newNode->next = head;
			head = newNode;
			return 0;
		}
		intNode* temp = head;
		int index = 1;
		while (temp->next) {
			if (data >= temp->data && data <= temp->next->data) {
				break;
			}
			temp = temp->next;
			index++;
		}
		newNode->next = temp->next;
		temp->next = newNode;
		return index;
	}
};




struct node {
public:
    intList* key;
    node** child;
    bool isLeaf;
    int noOfNodes;
    node() {
        key = NULL;
        child = NULL;
        isLeaf = false;
        noOfNodes = 0;
    }
    node(int keys) {
        key = new intList;
        child = new node*[keys+1];
        isLeaf = false;
        noOfNodes = 0;
        for (int i = 0; i < keys+1; i++)
        {
            child[i] = NULL;
        }
    }

	

	bool isFull(int keys) {
		return noOfNodes == keys;
	}

	int insert(int data, string loc) {
		return key->insert(data, loc);
	}
};


class BPlusTree {
	node* root;
	int keys;
public:
	BPlusTree() {
		root = NULL;
		keys = 2;
	}
	BPlusTree(int keys) {
		this->keys = keys;
		root = NULL;
	}

	int splitNodes(node* node) {

	}

	void insert(int data, string loc) {
		if (!root) {
			root = new node(keys);
			root->insert(data, loc);
			root->isLeaf = true;
			root->noOfNodes = 1;
			return;
		}
		if (root->isLeaf) {
			if (!root->isFull(keys)) {
				root->insert(data, loc);
				root->noOfNodes++;
			}
			else{
				node* temp = root;
				// finding the mid Value
				int center = temp->noOfNodes / 2;
				intNode* tempNode = temp->key->getNode(center);
				temp = root;
				root = new node(keys);
				root->noOfNodes = 1;
				root->isLeaf = false;
				root->insert(tempNode->data, loc);
				root->child[0] = temp;
				temp->noOfNodes = center+1;
				root->child[1] = new node(keys);
				root->child[1]->isLeaf = true;
				root->child[1]->noOfNodes = keys - center;
				root->child[1]->key->head = temp->key->getNode(center + 1);

				if (data > root->key->head->data) {
					root->child[1]->insert(data, loc);
					//root->child[1]->noOfNodes++;
				}
				else {
					root->child[0]->insert(data, loc);
					//root->child[1]->noOfNodes++;
				}
			}
		}
		else {
			insertData(root, data, loc);
		}
	}

	node* splitNode(node* root, node* dataPtr) {
		//int mid = root->noOfNodes / 2;
		//node* temp = new node(keys);
		//temp->isLeaf = false;
		//temp->key->insert(root->key->getNode(mid)->data);
		//temp->child[0] = root;
		//temp->child[0]->noOfNodes = mid + 1;
		//temp->noOfNodes = 1;
		//temp->child[1] = new node(keys);
		//temp->child[1]->isLeaf = true;
		//temp->child[1]->key->head = root->key->getNode(mid + 1);
		//temp->child[1]->noOfNodes = root->noOfNodes - mid;
		//if (data > temp->key->head->data) {
		//	temp->child[1]->insert(data);
		//	temp->child[1]->noOfNodes++;
		//	//root->child[1]->noOfNodes++;
		//}
		//else {
		//	temp->child[0]->insert(data);
		//	temp->child[0]->noOfNodes++;
		//}
		//return temp;
	}

	node* insertData(node* root, int data, string location) {
		if (!root->isLeaf) {
			int loc = root->key->findRangeLocation(root->noOfNodes, data);
			node* temp = insertData(root->child[loc], data, location);
			if (temp != NULL){
				if (root->isFull(keys)) {
					int mid = root->noOfNodes / 2;
					node* tempNode = new node(keys);
					tempNode->insert(root->key->getNode(mid)->data, location);
					tempNode->child[0] = root;
					tempNode->child[0]->noOfNodes = mid + 1;
					tempNode->noOfNodes = 1;
					tempNode->isLeaf = false;
					tempNode->child[1] = new node(keys);
					for (int i = mid + 1; i < keys; i++) {
						tempNode->child[1]->child[i - mid -1] = root->child[i];
					}
					tempNode->child[1]->isLeaf = false;
					tempNode->child[1]->key->head = root->key->getNode(mid + 1);
					tempNode->child[1]->noOfNodes = root->noOfNodes - mid;
					int num;
					if (temp->key->head->data > tempNode->key->head->data) {
						num = tempNode->child[1]->insert(temp->key->head->data, location);
						tempNode->child[1]->noOfNodes++;
						node* childTemp;
						for (int i = 0; i < keys - num - 1; i++) {
							childTemp = tempNode->child[1]->child[keys - 2 - i + 1];
							tempNode->child[1]->child[keys - num - i + 1] = tempNode->child[1]->child[keys - num - i];
							tempNode->child[1]->child[keys - num - i] = childTemp;
						}
						tempNode->child[1]->child[num] = temp->child[0];
						tempNode->child[1]->child[num + 1] = temp->child[1];
						//root->child[1]->noOfNodes++;
					}
					else {
						num = tempNode->child[0]->insert(temp->key->head->data, location);
						tempNode->child[0]->noOfNodes++;
						node* childTemp;
						for (int i = 0; i < keys - num - 1; i++) {
							childTemp = tempNode->child[1]->child[keys - 2 - i + 1];
							tempNode->child[0]->child[keys - num - i + 1] = tempNode->child[0]->child[keys - num - i];
							tempNode->child[0]->child[keys - num - i] = childTemp;
						}
						tempNode->child[0]->child[num] = temp->child[0];
						tempNode->child[0]->child[num + 1] = temp->child[1];
						//root->child[1]->noOfNodes++;
					}

					if (root == this->root) {
						this->root = tempNode;
					}
					return tempNode;
				}
				else {
					int num = root->key->insert(temp->key->head->data, location);
					root->noOfNodes++;
					node* childTemp;
					for (int i = 0; i < keys - num - 1; i++) {
						childTemp = root->child[keys - 2 - i + 1];
						root->child[keys - num - i + 1] = root->child[keys - num - i];
						root->child[keys - num - i] = childTemp;
					}
					root->child[num] = temp->child[0];
					root->child[num+1] = temp->child[1];
				}
			}

		}
		if (root->isLeaf) {
			if (root->isFull(keys)){
				int mid = root->noOfNodes / 2;
				node* temp = new node(keys);
				temp->isLeaf = false;
				temp->key->insert(root->key->getNode(mid)->data, location);
				temp->child[0] = root;
				temp->child[0]->noOfNodes = mid + 1;
				temp->noOfNodes = 1;
				temp->child[1] = new node(keys);
				temp->child[1]->isLeaf = true;
				temp->child[1]->key->head = root->key->getNode(mid+1);
				temp->child[1]->noOfNodes = root->noOfNodes - mid;
				if (data > temp->key->head->data) {
					temp->child[1]->insert(data, location);
					temp->child[1]->noOfNodes++;
					//root->child[1]->noOfNodes++;
				}
				else {
					temp->child[0]->insert(data, location);
					temp->child[0]->noOfNodes++;
				}
				return temp;
			}
			else {
				root->key->insert(data, location);
				root->noOfNodes++;
				return NULL;
			}
		}
		return NULL;
	}


	string search(node* temp, int data) {
		if (!temp) {
			return "No Data";
		}
		if (temp->isLeaf) {
			intNode* t = temp->key->head;
			for (int i = 0; i < temp->noOfNodes; i++) {
				if (t->data == data) {
					cout << "Data Found\n";
					return t->index.location;
				}
				t = t->next;
			}
			cout << "Data not Exist\n";
			return "No Data";
		}
		else {
			int index = temp->key->findRangeLocation(temp->noOfNodes, data);
			return search(temp->child[index], data);
		}
		return "No Data";
	}

	string search(int data) {
		return search(root, data);
	}

	void print(node*& root)
	{
		cout << "\n";
		intNode* temp = root->key->head;
		int i;
		for (i = 0; i < root->noOfNodes; i++) {
		    if (!root->isLeaf) {
		        print(root->child[i]);
		    }
		    cout << " " << temp->data;
			temp = temp->next;
		}
		if (!root->isLeaf) {
		    print(root->child[i]);
		}
		cout << "\n";
	}

	void writeFile(node* p, ofstream& file)
	{
		intNode* temp = p->key->head;
		int i = 0;
		for (i = 0; i < p->noOfNodes; i++) {
			if (!p->isLeaf) {
				writeFile(p->child[i], file);
			}
			else
				file << temp->data << endl;
			
			temp = temp->next;
		}
		if (!p->isLeaf) {
			writeFile(p->child[i], file);
		}
	}
		
	void print() {
		print(root);
	}

	void writeFile(ofstream& file) {
		writeFile(root, file);
	}

};

int main() {
	BPlusTree idtree(3);
	FloatBPlusTree dobtree(3);
	FloatBPlusTree regtree(3);

	ifstream file;
	string fileName = "./Fall2022DSDataFile0";
	string data, str;
	int id = 0;
	float dob = 0.0, reg = 0.0;
	char tempo;
	for (int i = 1; i <= 12; i++) {
		fileName = "./Fall2022DSDataFile0";
		i < 10 ? fileName += '0' : fileName;
		fileName += to_string(i) + ".txt";
		file.open(fileName);
		if (file.is_open()) {
			int j = 1;
			while (!file.eof()) {
				//getting id
				file >> id;
				str = "";
				str += 'F' + to_string(i) + 'L' + to_string(j);
				idtree.insert(id, str);
				
				j++;
				// getting name
				getline(file, data, '\t');
				// getting dob
				/*getline(file, data, '\t');
				string temp = "";
				double dob = 0.0;
				int i = 0;
				for (i = 0; data[i] != '-' && i< data.length(); i++) {
					temp += data[i];
				}
				dob = float(stoi(temp)) / float(365);
				cout << dob << endl;

				temp = "";
				for (++i; data[i] != '-' && i < data.length(); i++) {
					temp += data[i];
				}
				if (temp == "Jan") {
					dob += 1.0 / 12.0;
				}
				else if (temp == "Feb") {
					dob += 2.0 / 12.0;
				}
				else if (temp == "Mar") {
					dob += 3.0 / 12.0;
				}
				else if (temp == "Apr") {
					dob += 4.0 / 12.0;
				}
				else if (temp == "May") {
					dob += 5.0 / 12.0;
				}
				else if (temp == "Jun") {
					dob += 6.0 / 12.0;
				}
				else if (temp == "Jul") {
					dob += 7.0 / 12.0;
				}
				else if (temp == "Aug") {
					dob += 8.0 / 12.0;
				}
				else if (temp == "Sep") {
					dob += 9.0 / 12.0;
				}
				else if (temp == "Oct") {
					dob += 10.0 / 12.0;
				}
				else if (temp == "Nov") {
					dob += 11.0 / 12.0;
				}
				else if (temp == "Dec") {
					dob += 12.0 / 12.0;
				}
				cout << dob << endl;

				temp = "";
				for (++i; data[i] != '-' && data[i] != '\0' && i < data.length(); i++) {
					temp += data[i];
				}
				dob += float(stoi(temp));
				dobtree.insert(dob);*/

				/*getline(file, data, '\t');

				getline(file, data, '\t');
				temp = "";
				dob = 0.0;
				i = 0;
				for (i = 0; data[i] != '-'; i++) {
					temp += data[i];
				}
				dob = float(stoi(temp)) / float(365);
				cout << dob << endl;

				temp = "";
				for (++i; data[i] != '-'; i++) {
					temp += data[i];
				}
				if (temp == "Jan") {
					dob += 1.0 / 12.0;
				}
				else if (temp == "Feb") {
					dob += 2.0 / 12.0;
				}
				else if (temp == "Mar") {
					dob += 3.0 / 12.0;
				}
				else if (temp == "Apr") {
					dob += 4.0 / 12.0;
				}
				else if (temp == "May") {
					dob += 5.0 / 12.0;
				}
				else if (temp == "Jun") {
					dob += 6.0 / 12.0;
				}
				else if (temp == "Jul") {
					dob += 7.0 / 12.0;
				}
				else if (temp == "Aug") {
					dob += 8.0 / 12.0;
				}
				else if (temp == "Sep") {
					dob += 9.0 / 12.0;
				}
				else if (temp == "Oct") {
					dob += 10.0 / 12.0;
				}
				else if (temp == "Nov") {
					dob += 11.0 / 12.0;
				}
				else if (temp == "Dec") {
					dob += 12.0 / 12.0;
				}
				cout << dob << endl;

				temp = "";
				for (++i; data[i] != '-' && data[i] != '\0'; i++) {
					temp += data[i];
				}
				dob += float(stoi(temp));

				regtree.insert(dob);*/

				getline(file, data);
			}
		}
		else
			cout << "File Not Opened\n";
		
			
		file.close();
	}
	
	idtree.search(6600);

	string input;
	do {
		system("CLS");
		cout << "------ TREE SEARCH --------\n";
		cout << "Enter Query: "; 
		getline(cin, input);
		str = input;
		str.pop_back();
		if (input == "SELECT DATA") {
			cout << "entered" << endl;
			for (int i = 1; i <= 12; i++) {
				fileName = "./Fall2022DSDataFile0";
				i < 10 ? fileName += '0' : fileName;
				fileName += to_string(i) + ".txt";
				file.open(fileName);
				if (file.is_open()) {
					int j = 1;
					while (!file.eof()) {
						getline(file, data);
						cout << data << endl;
					}
				}
				file.close();
			}
		}
		else if (str == "SELECT DATA WHERE ID = ") {
			int n = 22;
			string str = "";
			for (int i = n+1; !(input[i] == ' ' || input[i] == '\0'); i++) {
				str += input[i];
			}
			int number = stoi(str);
			str = idtree.search(number);
			if (str == "No Data") {
				cout << "No Data Exist\n";
			}
			else {
				int fileNo = 1;
				int LineNo = 1;
				string temp = "";
				int i;
				for (i = 1; str[i] != 'L'; i++) {
					temp += str[i];
				}
				fileNo = stoi(temp);
				temp = "";
				for (i = i + 1; str[i] != '\0'; i++) {
					temp += str[i];
				}
				LineNo = stoi(temp);
				fileName = "./Fall2022DSDataFile0";
				fileNo < 10 ? fileName += '0' : fileName;
				fileName += to_string(fileNo) + ".txt";
				file.open(fileName);
				for (int i = 0; i < LineNo; i++) {
					getline(file, str);
				}
				cout << str << endl;
			}
		}

		else if (str == "SELECT DATA WHERE ID < ") {
			int n = 23;
			string abc = "";
			for (int i = n + 1; !(input[i] == ' ' || input[i] == '\0'); i++) {
				abc += input[i];
			}
			int number = stoi(abc);
			abc = idtree.search(1);
			int fileNo = 1;
			int LineNo = 1;
			string temp = "";
			int i;
			for (int i = 1; i < number; i++) {
				abc = idtree.search(i);
				temp = "";
				for (i = 1; abc[i] != 'L'; i++) {
					temp += abc[i];
				}
				fileNo = stoi(temp);
				temp = "";
				for (i = i + 1; abc[i] != '\0'; i++) {
					temp += abc[i];
				}
				LineNo = stoi(temp);
				fileName = "./Fall2022DSDataFile0";
				fileNo < 10 ? fileName += '0' : fileName;
				fileName += to_string(fileNo) + ".txt";
				file.open(fileName);
				for (int i = 0; i < LineNo; i++) {
					getline(file, abc);
				}
				cout << abc << endl;
			}
		}

		system("pause");
	} while (!(input == "END" || input == "end"));
	


	//idtree.traverse();

	/*file.open("./Fall2022DSDataFile003.txt");
	int num = 0;
	while (!file.eof()) {
		file >> id;
		getline(file, data);
		tree.insert(id);
		num++;
	}
	*/

	//for (int i = 0; i < 6000; i++) {
	//	idtree.insert(i);
	//}

	//tree.insert(1);
	//tree.insert(2);
	//tree.insert(3);
	//tree.insert(4);
	//tree.insert(5);
	//tree.insert(6);
	//tree.insert(7);
	//tree.insert(8);
	//tree.insert(9);
	//tree.insert(10);
	//tree.insert(11);
	//tree.insert(12);
	//tree.insert(13);
	//tree.insert(14);

	ofstream outFile("./output.txt");
	idtree.writeFile(outFile);
	outFile.close();

	return 0;

}

