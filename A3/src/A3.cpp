//============================================================================
// Name        : A3.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================
#include "bits/stdc++.h"
using namespace std;

class Node{
private:
	int data;
	Node *left,*right;
	bool leftTag,rightTag;
	/*
		tag=false => Thread
		tag=true => Child
	*/
public:
	Node(int);
	friend class ThreadedBinaryTree;
};
Node::Node(int data){
	this->data=data;
	left=NULL;
	right=NULL;
	leftTag=false;
	rightTag=false;
}

class ThreadedBinaryTree{
private:
	Node *root;
public:
	ThreadedBinaryTree();
	void insertBST(int);
	void insert(int);
	void callInorder();
	void inorder(Node*);
	void deleteNode(int);
	void noBranch(Node*,Node*);
	void oneBranch(Node*,Node*);
	void twoBranch(Node*,Node*);
	void inorder();
	void preorder();
	Node* inPred(Node*);
	Node* inSucc(Node*);
};
ThreadedBinaryTree::ThreadedBinaryTree(){
	root=new Node(0);
	root->left=root;
	root->right=root;
}
void ThreadedBinaryTree::insertBST(int data){
	Node *temp=new Node(data);
	if(root->left==root&&root->right==root){
		root->leftTag=true;
		root->left=temp;

		temp->left=root;
		temp->right=root;
		cout<<"\n"<<data<<" Set as Root";
		return;
	}
	Node *p=root->left;
	bool currentLeft,currentRight;
	while(true){
		if(temp->data<p->data){
			if(p->leftTag==false){
				currentLeft=true;
				currentRight=false;
				break;
			}
			else
				p=p->left;
		}
		else if(temp->data>p->data){
			if(p->rightTag==false){
				currentLeft=false;
				currentRight=true;
				break;
			}
			else
				p=p->right;
		}
		else{
			cout<<"\n"<<data<<" Already Exists in Tree!";
			return;
		}
	}
	if(currentLeft){
		temp->leftTag=p->leftTag;
		temp->left=p->left;

		p->leftTag=true;
		p->left=temp;

		temp->rightTag=false;
		temp->right=p;
	}
	else if(currentRight){
		temp->rightTag=p->rightTag;
		temp->right=p->right;

		p->rightTag=true;
		p->right=temp;

		temp->leftTag=false;
		temp->left=p;
	}
	else
		cout<<"\nError While insertion";
	cout<<"\n"<<data<<" Inserted into Tree";
}
void ThreadedBinaryTree::insert(int data){
	Node *temp=new Node(data);
	if(root->left==root&&root->right==root){
		root->leftTag=true;
		root->left=temp;

		temp->left=root;
		temp->right=root;
		cout<<"\n"<<data<<" Set as Root";
		return;
	}
	Node *p=root->left;
	bool currentLeft,currentRight;
	char pos;
	while(true){
		cout<<"\nChoose L/R of "<<p->data<<": ";
		cin>>pos;
		if(pos=='l'||pos=='L'){
			if(p->leftTag==false){
				currentLeft=true;
				currentRight=false;
				break;
			}
			else
				p=p->left;
		}
		else{
			if(p->rightTag==false){
				currentLeft=false;
				currentRight=true;
				break;
			}
			else
				p=p->right;
		}
	}
	if(currentLeft){
		temp->leftTag=p->leftTag;
		temp->left=p->left;

		p->leftTag=true;
		p->left=temp;

		temp->rightTag=false;
		temp->right=p;
	}
	else if(currentRight){
		temp->rightTag=p->rightTag;
		temp->right=p->right;

		p->rightTag=true;
		p->right=temp;

		temp->leftTag=false;
		temp->left=p;
	}
	else
		cout<<"\nError While insertion";
	cout<<"\n"<<data<<" Inserted into Tree";
}
void ThreadedBinaryTree::callInorder(){
	if(root->right==root&&root->left==root){
		cout<<"\nTree is Empty!";
		return;
	}
	inorder(root->left);
}
void ThreadedBinaryTree::inorder(Node* p){
	if(p==root)
		return;
	if(p->leftTag)
		inorder(p->left);

	cout<<p->data<<" ";

	if(p->rightTag)
		inorder(p->right);
}
Node* ThreadedBinaryTree::inPred(Node *p){
	if(p->leftTag==false)
		return p->left;
	p=p->left;
	while(p->rightTag!=false)
		p=p->right;
	return p;
}
Node* ThreadedBinaryTree::inSucc(Node *p){
	if(p->rightTag==false)
		return p->right;
	p=p->right;
	while(p->leftTag!=false)
		p=p->left;
	return p;
}
void ThreadedBinaryTree::noBranch(Node *p,Node *q){
	if(p==root->left){
		root->left=root;
		root->leftTag=false;
	}
	else if(q==p->left){
		p->leftTag=false;
		p->left=q->left;
	}
	else{
		p->rightTag=false;
		p->right=q->right;
	}
	delete q;
	return;
}
void ThreadedBinaryTree::oneBranch(Node *p,Node *q){
	Node *next;
	if(q->leftTag)
		next=q->left;
	else
		next=q->right;
	if(p==NULL)
		root=next;
	else if(q==p->left)
		p->left=next;
	else
		p->right=next;
	Node *succ=inSucc(q);
	Node *pred=inPred(q);
	if(q->leftTag)
		pred->right=succ;
	else if(q->rightTag)
		succ->left=pred;
	delete q;
}
void ThreadedBinaryTree::twoBranch(Node *p,Node *q){
	Node *parsucc=q;
	Node *succ=q->right;
	while(succ->leftTag!=false){
		parsucc=succ;
		succ=succ->left;
	}
	q->data=succ->data;

	if(succ->leftTag==false&&succ->rightTag==false)
		noBranch(parsucc,succ);
	else
		oneBranch(parsucc,succ);
}
void ThreadedBinaryTree::deleteNode(int data){
	Node *q=root->left;
	Node *p=NULL;
	bool found=false;
	while(true){
		if(q->data==data){
			found=true;
			break;
		}
		p=q;
		if(data<q->data){
			if(q->leftTag)
				q=q->left;
			else
				break;
		}
		else{
			if(q->rightTag)
				q=q->right;
			else
				break;
		}
	}
	if(!found){
		cout<<"\n"<<data<<" Not Present in Tree";
		return;
	}
	if(q->leftTag==true && q->rightTag==true)
		twoBranch(p,q);
	else if(q->leftTag==true)
		oneBranch(p,q);
	else if(q->rightTag==true)
		oneBranch(p,q);
	else
		noBranch(p,q);
	return;
}
void ThreadedBinaryTree::inorder(){
	Node *p=root->left;
	while(p!=root){
		while(p->leftTag==true)
			p=p->left;
		cout<<p->data<<" ";
		if(p->rightTag==true)
			p=p->right;
		else{
			if(p->right!=root){
				p=p->right;
				cout<<p->data<<" ";
			}
			p=p->right;
		}
	}
}
void ThreadedBinaryTree::preorder(){
	Node *p=root->left;
	while(p!=root){
		while(p->leftTag==true){
			cout<<p->data<<" ";
			p=p->left;
		}
		cout<<p->data<<" ";
		if(p->rightTag==true)
			p=p->right;
		else{
			if(p->right!=root)
				p=p->right;
			p=p->right;
		}
	}
}
int main(){
	int elements[]={50,20,70,60,80,10,30,5,15,25,35};
	int n=sizeof(elements)/sizeof(int);
	ThreadedBinaryTree container;

	for(int i=0;i<n;i++)container.insert(elements[i]);
	cout<<"\nInorder: ";
	container.callInorder();
	cout<<"\nInorder: ";
	container.inorder();
	cout<<"\nPreorder: ";
	container.preorder();
	cout<<"\n";
	return 0;
}


