#pragma once
#include <iostream>
#include "Header1.h"



class floatNode {
public:
	float data;
	floatNode* next;
	fileNode* index;
};

class floatList {
public:
	floatNode* head;
	floatList() {
		head = NULL;
	}

	int findRangeLocation(int noOfNodes, float num) {
		floatNode* temp = head;
		int loc = 0;
		for (loc = 0; loc < noOfNodes; loc++) {
			if (num <= temp->data) {
				break;
			}
			temp = temp->next;
		}
		return loc;
	}

	floatNode* getNode(int at) {
		floatNode* temp = head;
		for (int i = 0; i < at; i++) {
			temp = temp->next;
		}
		return temp;
	}

	int insert(float data) {
		floatNode* newNode = new floatNode;
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
		floatNode* temp = head;
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


struct fnode {
public:
	floatList* key;
	fnode** child;
	bool isLeaf;
	int noOfNodes;
	fnode() {
		key = NULL;
		child = NULL;
		isLeaf = false;
		noOfNodes = 0;
	}
	fnode(int keys) {
		key = new floatList;
		child = new fnode * [keys + 1];
		isLeaf = false;
		noOfNodes = 0;
		for (int i = 0; i < keys + 1; i++)
		{
			child[i] = NULL;
		}
	}



	bool isFull(int keys) {
		return noOfNodes == keys;
	}

	int insert(float data) {
		return key->insert(data);
	}
};


class FloatBPlusTree {
	fnode* root;
	int keys;
public:
	FloatBPlusTree() {
		root = NULL;
		keys = 2;
	}
	FloatBPlusTree(int keys) {
		this->keys = keys;
		root = NULL;
	}

	int splitNodes(fnode* node) {

	}

	void insert(float data) {
		if (!root) {
			root = new fnode(keys);
			root->insert(data);
			root->isLeaf = true;
			root->noOfNodes = 1;
			return;
		}
		if (root->isLeaf) {
			if (!root->isFull(keys)) {
				root->insert(data);
				root->noOfNodes++;
			}
			else {
				fnode* temp = root;
				// finding the mid Value
				int center = temp->noOfNodes / 2;
				floatNode* tempNode = temp->key->getNode(center);
				temp = root;
				root = new fnode(keys);
				root->noOfNodes = 1;
				root->isLeaf = false;
				root->insert(tempNode->data);
				root->child[0] = temp;
				temp->noOfNodes = center + 1;
				root->child[1] = new fnode(keys);
				root->child[1]->isLeaf = true;
				root->child[1]->noOfNodes = keys - center;
				root->child[1]->key->head = temp->key->getNode(center + 1);

				if (data > root->key->head->data) {
					root->child[1]->insert(data);
					//root->child[1]->noOfNodes++;
				}
				else {
					root->child[0]->insert(data);
					//root->child[1]->noOfNodes++;
				}
			}
		}
		else {
			insertData(root, data);
		}
	}

	fnode* splitNode(fnode* root, fnode* dataPtr) {
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

	fnode* insertData(fnode* root, float data) {
		if (!root->isLeaf) {
			int loc = root->key->findRangeLocation(root->noOfNodes, data);
			fnode* temp = insertData(root->child[loc], data);
			if (temp != NULL) {
				if (root->isFull(keys)) {
					int mid = root->noOfNodes / 2;
					fnode* tempNode = new fnode(keys);
					tempNode->insert(root->key->getNode(mid)->data);
					tempNode->child[0] = root;
					tempNode->child[0]->noOfNodes = mid + 1;
					tempNode->noOfNodes = 1;
					tempNode->isLeaf = false;
					tempNode->child[1] = new fnode(keys);
					for (int i = mid + 1; i < keys; i++) {
						tempNode->child[1]->child[i - mid - 1] = root->child[i];
					}
					tempNode->child[1]->isLeaf = false;
					tempNode->child[1]->key->head = root->key->getNode(mid + 1);
					tempNode->child[1]->noOfNodes = root->noOfNodes - mid;
					int num;
					if (temp->key->head->data > tempNode->key->head->data) {
						num = tempNode->child[1]->insert(temp->key->head->data);
						tempNode->child[1]->noOfNodes++;
						fnode* childTemp;
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
						num = tempNode->child[0]->insert(temp->key->head->data);
						tempNode->child[0]->noOfNodes++;
						fnode* childTemp;
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
					int num = root->key->insert(temp->key->head->data);
					root->noOfNodes++;
					fnode* childTemp;
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
				int mid = root->noOfNodes / 2;
				fnode* temp = new fnode(keys);
				temp->isLeaf = false;
				temp->key->insert(root->key->getNode(mid)->data);
				temp->child[0] = root;
				temp->child[0]->noOfNodes = mid + 1;
				temp->noOfNodes = 1;
				temp->child[1] = new fnode(keys);
				temp->child[1]->isLeaf = true;
				temp->child[1]->key->head = root->key->getNode(mid + 1);
				temp->child[1]->noOfNodes = root->noOfNodes - mid;
				if (data > temp->key->head->data) {
					temp->child[1]->insert(data);
					temp->child[1]->noOfNodes++;
					//root->child[1]->noOfNodes++;
				}
				else {
					temp->child[0]->insert(data);
					temp->child[0]->noOfNodes++;
				}
				return temp;
			}
			else {
				root->key->insert(data);
				root->noOfNodes++;
				return NULL;
			}
		}
		return NULL;
	}


	void search(fnode* temp, float data) {
		if (!temp) {
			return;
		}
		if (temp->isLeaf) {
			floatNode* t = temp->key->head;
			for (int i = 0; i < temp->noOfNodes; i++) {
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
			int index = temp->key->findRangeLocation(temp->noOfNodes, data);
			search(temp->child[index], data);
		}
		return;
	}

	void search(float data) {
		search(root, data);
	}

	void traverse(fnode* p)
	{
		cout << endl;
		int i;
		floatNode* temp = p->key->head;
		/*cout << "data: " <<temp->data << endl;
		cout << "is Leaf:" << p->isLeaf << endl;
		cout << "NoOfNodes:" << p->noOfNodes << endl;*/

		for (i = 0; i < p->noOfNodes; i++)
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