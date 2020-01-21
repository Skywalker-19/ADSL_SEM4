//============================================================================
// Name        : A1.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <bits/stdc++.h>
#include<stack>
using namespace std;

class Node{
	int data;
	Node *left;
	Node *right;

public:
	Node();
	Node(Node *t);
	Node(int a);
	friend class Tree;
	//friend class Stack;
};
Node::Node(){
	data=0;
	left=NULL;
	right=NULL;

}

Node::Node(int a){
	this->data=a;
	left=NULL;
	right=NULL;

}

class node{
	Node *p;
	node *next;
public:
	node(){
		p=NULL;

		next=NULL;
	}
	node(Node *t){
		p=t;

		next=NULL;
	}
	friend class Stack;
};

/*
class Stack
{
	node *start;
	public:
	Stack(){  start=new node();}
          void push(node *t);
           void pop();
           void display();
           node* peek();
           int empty();
};

void Stack::push(node *t)
{
     node *temp=new node(t);
     temp->next=start;
     start=temp;
}

void Stack::pop()
{
if(start==NULL)
{cout<<"Stack is Empty"<<endl;
return;}
       node* temp=start;
	start=start->next;
	delete temp;
}

node* Stack::peek()
   {
if(start==NULL)
{cout<<"Stack is Empty!"<<endl; return NULL; }
else
return (start);
   }


int Stack::empty()
{
	if(start==NULL)
	{return 1;}
	else
	{return 0;}
}

*/



class Tree{
	Node *start;
public:
	Tree(){
		start=NULL;
	}
	int checkleft(Node *p);
	int checkright(Node *p);
	void readNodes();
	void displayTree();
	void displayTreeinorder_rec(Node *t);
	void displayTreepreorder_rec(Node *t);
	void displayTreepostorder_rec(Node *t);
	void displayTreeinorder_non();
	void displayTreepreorder_non();
	void displayTreepostorder_non();
	void mirror();
	void treeMirror(Node *t);
	Node* assignTree(Node *t);
	void erase();
	void eraseTree(Node *t);
	bool isEqual(Tree T);
	bool compare(Node*p,Node*q);
	void operator=(Tree &s1);
	void printLeafNodes(Node *t);
	void callPrintLeafNodes();
	void callPrintInternalNodes();
	void printInternalNodes(Node *p);
};

int Tree::checkleft(Node *p){
	if(p->left==NULL)
		return 1;
	else return 0;
}

int Tree::checkright(Node *p){
	if(p->right==NULL)
		return 1;
	else return 0;
}

void Tree::readNodes(){
	int n;
	if(start==NULL){
		cout<<"Enter root node element - "<<endl;
		cin>>n;
		Node *t=new Node(n);
		start=t;
	}

	else{

		Node *t=start;
		goto z;

		y:
				cout<<"Enter 1 to insert to the left side of the node or 2 to insert to the right side of the node."<<endl;
				cin>>n;
				if(n==1){
					if(checkleft(t)==1){
						cout<<"Enter the element to be inserted - "<<endl;
						cin>>n;
						Node *temp=new Node(n);
						t->left=temp;
						cout<<"Element inserted!"<<endl;
						return;
					}
					else if(checkleft(t)==0){
						cout<<"Element is already inserted at left."<<endl;

					}
					return;
				}
				else{
					                  if(checkright(t)==1){
											cout<<"Enter the element to be inserted - "<<endl;
											cin>>n;
											Node *temp=new Node(n);
											t->right=temp;
											cout<<"Element inserted!"<<endl;
											return;
										}
										else if(checkright(t)==0){
											cout<<"Element is already inserted at right."<<endl;
										}
					return;
				}

	  z:
	 for(;;){
		cout<<"POINTER CURRENTLY POINTING AT - "<<t->data<<endl;
		cout<<endl;
		cout<<"Enter 1 to insert at the current node or 0 to insert at some other node!"<<endl;
		cin>>n;
		if(n==1){ goto y; }
		else{
			cout<<"Enter 1 to insert to the left side of the next node or 2 to insert to the right side of the next node."<<endl;
			cin>>n;
			if(n==1){
				if(t->left!=NULL)
				t=t->left;
				else
			     {cout<<"No node is present after this position!!"<<endl; break;}
			 }
			else
			{if(t->right!=NULL)
				t=t->right;
				else
			     {cout<<"No node is present after this position!!"<<endl;
			     break;}
			}
	    }
	 }



	}
}

void Tree::displayTreeinorder_rec(Node *t){
	if(t){
		displayTreeinorder_rec(t->left);
		cout<<t->data<<endl;
		displayTreeinorder_rec(t->right);
	}

}

void Tree::displayTreeinorder_non(){
	stack<Node *> ob;

	Node *t=start;
	int flag=0;
	while(flag==0){
		if(t!=NULL)
		{
			ob.push(t);
			t=t->left;
		}
		else{
			if(!ob.empty())
			{
				t=ob.top();
				ob.pop();
				cout<<t->data<<endl;
				t=t->right;
			}
			else
				flag=1;
		}
	}
}

void Tree::displayTreepreorder_rec(Node *t){
	if(t!=NULL){
	        cout<<t->data<<endl;
	        displayTreepreorder_rec(t->left);
			displayTreepreorder_rec(t->right);
	}

}

void Tree::displayTreepreorder_non(){

	stack<Node*> ob;
		Node *t=start;
		int flag=0;
		while(flag==0){
			if(t!=NULL)
			{
				cout<<t->data<<endl;
				ob.push(t);
				t=t->left;
			}
			else{
				if(!ob.empty())
				{
					t=ob.top();
					ob.pop();
				    t=t->right;
				}
				else
					flag=1;
			}
}
}


void Tree::displayTreepostorder_rec(Node *t){
	if(t){
	        displayTreepostorder_rec(t->left);
			displayTreepostorder_rec(t->right);
			cout<<t->data<<"   "<<endl;
	}

}

void Tree::displayTreepostorder_non(){

	Node* p=start;
		if(p==NULL){
			cout<<"Tree does not exist\n";
			return;}
		stack<Node *> s;
		do{
			while(p){
				if(p->right)
				{
					s.push(p->right);
				}
				s.push(p);
				p=p->left;
			}
			p=s.top();
			s.pop();
			if(p->right && !s.empty() && s.top()==p->right)
			{

				s.pop();
				s.push(p);
				p=p->right;
			}
			else
			{
				cout<<p->data<<endl;
				p=NULL;
			}
		}while(!s.empty());

}

void Tree::displayTree(){
	Node *t=start;
	cout<<"Inorder traversal (Recursive) - "<<endl;
	displayTreeinorder_rec(t);
	cout<<endl;
	cout<<"Preorder traversal (Recursive) - "<<endl;
	displayTreepreorder_rec(t);
	cout<<endl;
	cout<<"Postorder traversal (Recursive) - "<<endl;
	displayTreepostorder_rec(t);
	cout<<endl;
	cout<<"Inorder traversal (Non Recursive) - "<<endl;
		displayTreeinorder_non();
		cout<<endl;
		cout<<"Preorder traversal (Non Recursive) - "<<endl;
		displayTreepreorder_non();
		cout<<endl;
		cout<<"Postorder traversal (Non Recursive) - "<<endl;
		displayTreepostorder_non();
		cout<<endl;
}


void Tree::mirror(){
    cout<<"Original Tree - "<<endl;
	displayTreeinorder_rec(start);
	treeMirror(start);
	cout<<"Mirror Image - "<<endl;
	displayTreeinorder_rec(start);



}
void Tree::treeMirror(Node *t){

	if(t==NULL){
		return;
	}
	treeMirror(t->left);
	treeMirror(t->right);
	Node *temp=t->left;
	t->left=t->right;
	t->right=temp;
	return;
}

void Tree::erase(){
	eraseTree(start);
	start=NULL;
}
void Tree::eraseTree(Node *t){
	 if(t==NULL){
		 return;
	 }
			eraseTree(t->left);
			eraseTree(t->right);
		t->left=NULL;
		delete t->left;
		t->right=NULL;
		delete t->right;
		return;
}

Node* Tree::assignTree(Node *t){
	if(t!=NULL){
		Node *p=new Node(t->data);
		p->left=assignTree(t->left);
		p->right=assignTree(t->right);
		return p;
	}
	else{
		return NULL;
	}
}

void Tree:: operator=(Tree &s1){
	start=assignTree(s1.start);
}


bool Tree::isEqual(Tree T){
	if (compare(this->start,T.start))
		return true;
	else
		return false;

}

bool Tree::compare(Node*p,Node*q){
	if(p==NULL&&q==NULL)
		return true;
	else if(p==NULL&&q!=NULL)
		return false;
	else if(p!=NULL&&q==NULL)
		return false;
	else{
		if(p->data==q->data&&compare(p->left,q->left)&&compare(p->right,q->right))
			return true;
		else
			return false;
	}
}

void Tree::callPrintLeafNodes(){
	printLeafNodes(start);
}
void Tree::printLeafNodes(Node *p){
	if(p==NULL)
		return;
	if(p->left==NULL&&p->right==NULL){
		cout<<p->data<<" ";
		return;
	}
	printLeafNodes(p->left);
	printLeafNodes(p->right);
}


void Tree::callPrintInternalNodes(){
	printInternalNodes(start);
}
void Tree::printInternalNodes(Node *p){
	if(p==NULL)
		return;
	if(p->left!=NULL||p->right!=NULL)
		cout<<p->data<<" ";
	printInternalNodes(p->left);
	printInternalNodes(p->right);
}


int main(){
	Tree obj1,obj2;
	int ch;
	for(; ; ){

	cout<<"***********BINARY TREE OPERATIONS**************"<<endl;
	cout<<endl;
	cout<<"1. Read the elements of the tree "<<endl;
	cout<<"2. Display the elements of the tree "<<endl;
	cout<<"3. Display the mirror image of the tree "<<endl;
	cout<<"4. Erase all nodes of the tree "<<endl;
	cout<<"5. Assign current tree to another "<<endl;
	cout<<"6. Check if two trees are equal "<<endl;
	cout<<"7. Print Internal Nodes "<<endl;
	cout<<"8, Print Leaf Nodes "<<endl;
	cin>>ch;
	switch(ch){
	case 1:  obj1.readNodes();
	          break;

	case 2:  obj1.displayTree();
	         break;

	case 3:  obj1.mirror();
	         break;

	case 4: obj1.erase();
	         cout<<"All nodes of the tree ERASED!"<<endl;
	        break;

	case 5:  obj2=obj1;
	         cout<<"Tree Assigned!"<<endl;
	          break;

	case 6:   cout<<"Enter elements of 1st tree - "<<endl;
	          while(true){
	          obj1.readNodes();
	          cout<<"Do you want to insert element?(1 if yes/0 if no)"<<endl;
	          cin>>ch;
	          if(ch==1)
	          	{continue;}
	          	else
	          	{break;}
	          }

	          cout<<"Enter elements of 2nd tree - "<<endl;
	          	          while(true){
	          	          obj2.readNodes();
	          	          cout<<"Do you want to insert element?(1 if yes/0 if no)"<<endl;
	          	          cin>>ch;
	          	          if(ch==1)
	          	          	{continue;}
	          	          	else
	          	          	{break;}
	          	         }

	          	          if(obj1.isEqual(obj2)==true)
	          	        	  cout<<"Both the trees are EQUAL!"<<endl;
	          	          else
	          	        	  cout<<"Both the trees are NOT EQUAL!"<<endl;
	          break;

	case 7:             cout<<"\nLeaf Nodes: ";
						obj1.callPrintLeafNodes();
						break;
	case 8:             cout<<"\nInternal Nodes: ";
						obj1.callPrintInternalNodes();
						break;

    default:
		 cout<<"Enter from the above menu!"<<endl;
	}
	cout<<"Do you want to continue?(1 if yes/0 if no)"<<endl;
	cin>>ch;
	if(ch==1)
	{continue;}
	else
	{break;}
	}
}
