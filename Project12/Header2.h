#pragma once
#include <iostream>
#include "Header1.h"



class charNode {
public:
	char data;
	charNode* next;
	fileNode* index;
};

class charList {
public:
	charNode* head;
	charList() {
		head = NULL;
	}

	int findRangeLocation(int noOcnodes, char num) {
		charNode* temp = head;
		int loc = 0;
		for (loc = 0; loc < noOcnodes; loc++) {
			if (num <= temp->data) {
				break;
			}
			temp = temp->next;
		}
		return loc;
	}

	charNode* getNode(int at) {
		charNode* temp = head;
		for (int i = 0; i < at; i++) {
			temp = temp->next;
		}
		return temp;
	}

	int insert(char data) {
		charNode* newNode = new charNode;
		newNode->data = data;
		newNode->next = NULL;
		newNode->index = NULL;
		if (!head) {
			head = newNode;
			return 0;
		}
		if (data < head->data) {
			newNode->next = head;
			head = newNode;
			return 0;
		}
		charNode* temp = head;
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


struct cnode {
public:
	charList* key;
	cnode** child;
	bool isLeaf;
	int noOcnodes;
	cnode() {
		key = NULL;
		child = NULL;
		isLeaf = false;
		noOcnodes = 0;
	}
	cnode(int keys) {
		key = new charList;
		child = new cnode * [keys + 1];
		isLeaf = false;
		noOcnodes = 0;
		for (int i = 0; i < keys + 1; i++)
		{
			child[i] = NULL;
		}
	}



	bool isFull(int keys) {
		return noOcnodes == keys;
	}

	int insert(char data) {
		return key->insert(data);
	}
};


class charBPlusTree {
	cnode* root;
	int keys;
public:
	charBPlusTree() {
		root = NULL;
		keys = 2;
	}
	charBPlusTree(int keys) {
		this->keys = keys;
		root = NULL;
	}

	int splitNodes(cnode* node) {

	}

	void insert(char data) {
		if (!root) {
			root = new cnode(keys);
			root->insert(data);
			root->isLeaf = true;
			root->noOcnodes = 1;
			return;
		}
		if (root->isLeaf) {
			if (!root->isFull(keys)) {
				root->insert(data);
				root->noOcnodes++;
			}
			else {
				cnode* temp = root;
				// finding the mid Value
				int center = temp->noOcnodes / 2;
				charNode* tempNode = temp->key->getNode(center);
				temp = root;
				root = new cnode(keys);
				root->noOcnodes = 1;
				root->isLeaf = false;
				root->insert(tempNode->data);
				root->child[0] = temp;
				temp->noOcnodes = center + 1;
				root->child[1] = new cnode(keys);
				root->child[1]->isLeaf = true;
				root->child[1]->noOcnodes = keys - center;
				root->child[1]->key->head = temp->key->getNode(center + 1);

				if (data > root->key->head->data) {
					root->child[1]->insert(data);
					//root->child[1]->noOcnodes++;
				}
				else {
					root->child[0]->insert(data);
					//root->child[1]->noOcnodes++;
				}
			}
		}
		else {
			insertData(root, data);
		}
	}

	cnode* splitNode(cnode* root, cnode* dataPtr) {
		//int mid = root->noOcnodes / 2;
		//node* temp = new node(keys);
		//temp->isLeaf = false;
		//temp->key->insert(root->key->getNode(mid)->data);
		//temp->child[0] = root;
		//temp->child[0]->noOcnodes = mid + 1;
		//temp->noOcnodes = 1;
		//temp->child[1] = new node(keys);
		//temp->child[1]->isLeaf = true;
		//temp->child[1]->key->head = root->key->getNode(mid + 1);
		//temp->child[1]->noOcnodes = root->noOcnodes - mid;
		//if (data > temp->key->head->data) {
		//	temp->child[1]->insert(data);
		//	temp->child[1]->noOcnodes++;
		//	//root->child[1]->noOcnodes++;
		//}
		//else {
		//	temp->child[0]->insert(data);
		//	temp->child[0]->noOcnodes++;
		//}
		//return temp;
	}

	cnode* insertData(cnode* root, char data) {
		if (!root->isLeaf) {
			int loc = root->key->findRangeLocation(root->noOcnodes, data);
			cnode* temp = insertData(root->child[loc], data);
			if (temp != NULL) {
				if (root->isFull(keys)) {
					int mid = root->noOcnodes / 2;
					cnode* tempNode = new cnode(keys);
					tempNode->insert(root->key->getNode(mid)->data);
					tempNode->child[0] = root;
					tempNode->child[0]->noOcnodes = mid + 1;
					tempNode->noOcnodes = 1;
					tempNode->isLeaf = false;
					tempNode->child[1] = new cnode(keys);
					for (int i = mid + 1; i < keys; i++) {
						tempNode->child[1]->child[i - mid - 1] = root->child[i];
					}
					tempNode->child[1]->isLeaf = false;
					tempNode->child[1]->key->head = root->key->getNode(mid + 1);
					tempNode->child[1]->noOcnodes = root->noOcnodes - mid;
					int num;
					if (temp->key->head->data > tempNode->key->head->data) {
						num = tempNode->child[1]->insert(temp->key->head->data);
						tempNode->child[1]->noOcnodes++;
						cnode* childTemp;
						for (int i = 0; i < keys - num - 1; i++) {
							childTemp = tempNode->child[1]->child[keys - 2 - i + 1];
							tempNode->child[1]->child[keys - num - i + 1] = tempNode->child[1]->child[keys - num - i];
							tempNode->child[1]->child[keys - num - i] = childTemp;
						}
						tempNode->child[1]->child[num] = temp->child[0];
						tempNode->child[1]->child[num + 1] = temp->child[1];
						//root->child[1]->noOcnodes++;
					}
					else {
						num = tempNode->child[0]->insert(temp->key->head->data);
						tempNode->child[0]->noOcnodes++;
						cnode* childTemp;
						for (int i = 0; i < keys - num - 1; i++) {
							childTemp = tempNode->child[1]->child[keys - 2 - i + 1];
							tempNode->child[0]->child[keys - num - i + 1] = tempNode->child[0]->child[keys - num - i];
							tempNode->child[0]->child[keys - num - i] = childTemp;
						}
						tempNode->child[0]->child[num] = temp->child[0];
						tempNode->child[0]->child[num + 1] = temp->child[1];
						//root->child[1]->noOcnodes++;
					}

					if (root == this->root) {
						this->root = tempNode;
					}
					return tempNode;
				}
				else {
					int num = root->key->insert(temp->key->head->data);
					root->noOcnodes++;
					cnode* childTemp;
					for (int i = 0; i < keys - num - 1; i++) {
						childTemp = root->child[keys - 2 - i + 1];
						root->child[keys - num - i + 1] = root->child[keys - num - i];
						root->child[keys - num - i] = childTemp;
					}
					root->child[num] = temp->child[0];
					root->child[num + 1] = temp->child[1];
				}
			}

		}
		if (root->isLeaf) {
			if (root->isFull(keys)) {
				int mid = root->noOcnodes / 2;
				cnode* temp = new cnode(keys);
				temp->isLeaf = false;
				temp->key->insert(root->key->getNode(mid)->data);
				temp->child[0] = root;
				temp->child[0]->noOcnodes = mid + 1;
				temp->noOcnodes = 1;
				temp->child[1] = new cnode(keys);
				temp->child[1]->isLeaf = true;
				temp->child[1]->key->head = root->key->getNode(mid + 1);
				temp->child[1]->noOcnodes = root->noOcnodes - mid ;
				if (data > temp->key->head->data) {
					temp->child[1]->insert(data);
					temp->child[1]->noOcnodes++;
					//root->child[1]->noOcnodes++;
				}
				else {
					temp->child[0]->insert(data);
					temp->child[0]->noOcnodes++;
				}
				return temp;
			}
			else {
				root->key->insert(data);
				root->noOcnodes++;
				return NULL;
			}
		}
		return NULL;
	}


	void search(cnode* temp, char data) {
		if (!temp) {
			return;
		}
		if (temp->isLeaf) {
			charNode* t = temp->key->head;
			for (int i = 0; i < temp->noOcnodes; i++) {
				if (t->data == data) {
					cout << "Data Found\n";
					return;
				}
				t = t->next;
			}
			cout << "Data not Exist\n";
			return;
		}
		else {
			int index = temp->key->findRangeLocation(temp->noOcnodes, data);
			search(temp->child[index], data);
		}
		return;
	}

	void search(char data) {
		search(root, data);
	}

	void traverse(cnode* p)
	{
		cout << endl;
		int i;
		charNode* temp = p->key->head;
		/*cout << "data: " <<temp->data << endl;
		cout << "is Leaf:" << p->isLeaf << endl;
		cout << "NoOcnodes:" << p->noOcnodes << endl;*/

		for (i = 0; i < p->noOcnodes; i++)
		{
			if (p->isLeaf == false)
			{
				traverse(p->child[i]);
			}
			cout << " " << temp->data;
			temp = temp->next;
		}
		if (p->isLeaf == false)
		{
			traverse(p->child[i]);
		}
		cout << endl;
	}

	void traverse() {
		traverse(root);

	}

};