//============================================================================
// Name        : A2.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <stdio.h>
#include <string.h>
using namespace std;

class Node{
	string keyword;
	string meaning;
	Node *left;
	Node *right;

public:
	Node();
	Node(Node *t);
	Node(string,string);
	friend class SearchTree;

};
Node::Node(){
     keyword="";
    meaning="";
	left=NULL;
	right=NULL;
}
Node::Node(string key,string mean){
	keyword=key;
	meaning=mean;
	left=NULL;
	right=NULL;

}

class SearchTree{
	Node *start;
public:
	SearchTree(){
		start=NULL;
	}
	int checkleft(Node *p);
	int checkright(Node *p);
	void readdata();
	void displayTree();
	void update(string,string);
	void inidelete();
	Node *deleteNode(Node *root, string key);
	void displayTreeinorder_rec(Node *t);
	Node* assignTree(Node *t);
	Node* findmin(Node* p);
	void operator=(SearchTree &s1);
	void countComparisons(string key);
};

int SearchTree::checkleft(Node *p){
	if(p->left==NULL)
		return 1;
	else return 0;
}

int SearchTree::checkright(Node *p){
	if(p->right==NULL)
		return 1;
	else return 0;
}

void SearchTree::readdata(){
	string key,mean;
	cout<<"Enter the keyword - "<<endl;
	cin.ignore();
	getline(cin,key);
	cout<<"Enter the meaning - "<<endl;
	getline(cin,mean);

	Node *temp=new Node(key,mean);

	if(start==NULL){
		start=temp;
		cout<<temp->keyword<<" Inserted in the Dictionary!"<<endl;
		return;
    }
	else{
		Node*t=start;

		while(true){
				if(temp->keyword.compare(t->keyword)<0)
					if(t->left==NULL){
						t->left=temp;
						cout<<"\n"<<temp->keyword<<" Added to Dictionary!"<<endl;
						return;
					}
					else
						t=t->left;
				else if(temp->keyword.compare(t->keyword)>0)
					if(t->right==NULL){
						t->right=temp;
						cout<<"\n"<<temp->keyword<<" Added to Dictionary!"<<endl;;
						return;
					}
					else
						t=t->right;
				else{
					cout<<"\n"<<temp->keyword<<" Exists in Dictionary"<<endl;
					return;
				}
			}
	 }
}


void SearchTree::update(string key,string mean){
	Node *t=start;
	while(t!=NULL){
					if(key.compare(t->keyword)<0)
							t=t->left;
					else if(key.compare(t->keyword)>0)
							t=t->right;
					else{
						t->meaning=mean;
						cout<<"Meaning Updated!"<<endl;
						return;
					}
			}
	cout<<"Keyword not found in the Dictionary!"<<endl;
}

	Node* SearchTree::deleteNode(Node *root, string key){
		if(root == NULL)
			return root;
		if(root->keyword.compare(key)>0){
			root->left = deleteNode(root->left, key);
			return root;
		}
		else if(root->keyword.compare(key)<0){
			root->right = deleteNode(root->right, key);
			return root;
		}
		if(root->left == NULL)
			return root->right;
		else if(root->right == NULL)
			return root->left;
		else{
			Node* succparent = root->right;
			Node* succ = root->right;
			while(succ->left != NULL){
				succparent = succ;
				succ= succ->left;
			}
			succparent->left = succ->right;
			root->keyword = succ->keyword;
			delete succ;
			return root;
		}
	}
	void SearchTree::inidelete(){
		cout<<"Enter the keyword to be deleted - "<<endl;
		string key;
		cin>>key;
		deleteNode(start, key);
		cout<<"Keyword deleted!"<<endl;
	}
	
void SearchTree::displayTree(){
	Node *t=start;
	cout<<"Ascending order - "<<endl;
	cout<<endl;
	displayTreeinorder_rec(t);
}

void SearchTree::displayTreeinorder_rec(Node *t){
	if(t){
		displayTreeinorder_rec(t->left);
		cout<<"Keyword - "<<t->keyword<<" , Meaning - "<<t->meaning<<endl;
		displayTreeinorder_rec(t->right);
	}
}

Node* SearchTree::assignTree(Node *t){
	if(t!=NULL){
		Node *p=new Node(t->keyword,t->meaning);
		p->left=assignTree(t->left);
		p->right=assignTree(t->right);
		return p;
	}
	else{
		return NULL;
	}
}

void SearchTree:: operator=(SearchTree &s1){
	start=assignTree(s1.start);
}

void SearchTree:: countComparisons(string key){
	Node *t=start; int c=0;
		while(t!=NULL){
						if(++c && key.compare(t->keyword)<0)
								t=t->left;
						else if(++c && key.compare(t->keyword)>0)
								t=t->right;
						else{
							cout<<"Number of comparison for "<<key<<" are - "<<c<<endl;
							return;
						}
				}
		cout<<"Keyword not found in the Dictionary!"<<endl;
}



	int main(){
		SearchTree obj1,obj2;
		int ch;
		string key,mean;
		char k[10];
		for(; ; ){

		cout<<"***********BINARY SEARCH TREE OPERATIONS**************"<<endl;
		cout<<endl;
		cout<<"1. Read the elements of the tree "<<endl;
		cout<<"2. Display the elements of the tree "<<endl;
		cout<<"3. Update an element of the tree "<<endl;
		cout<<"4. Deleting a keyword from the dictionary "<<endl;
		cout<<"5. Assign current tree to another "<<endl;
		cout<<"6. Finding Maximum number of comparisons for finding a keyword"<<endl;
		cin>>ch;

		switch(ch){
		case 1:  obj1.readdata();
		          break;

		case 2:  obj1.displayTree();
		         break;

		case 3:     cout<<"Enter the keyword whose meaning is to be update - "<<endl;
		            cin.ignore();
			        getline(cin,key);
			        cout<<"Enter the Updated meaning - "<<endl;
			        getline(cin,mean);
			        obj1.update(key,mean);
			        obj1.displayTree();
			        break;
			        
		case 4:     obj1.inidelete();
				     break;

		case 5:  obj2=obj1;
		         cout<<"Tree Assigned!"<<endl;
		         obj2.displayTree();
		          break;

		case 6:   cout<<"Enter the keyword whose no. of comparisons is to be found -"<<endl;
		          cin>>key;
		          obj1.countComparisons(key);
		          break;

	    default:
			 cout<<"Enter from the above menu!"<<endl;
		}
        cout<<endl;
		cout<<"Do you want to continue?(1 if yes/0 if no)"<<endl;
		cin>>ch;
		if(ch==1)
		{continue;}
		else
		{break;}
		}
	}


