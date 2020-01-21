//============================================================================
// Name        : A4.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
using namespace std;

class Node{
	string city;
	float time;
	Node *next;

public:
	Node();
	Node(string ct,float t);
	friend class Graph;
};
Node::Node(){
	time=0;
	next=NULL;
	city="";

}
Node::Node(string ct,float t){
	city=ct;
	time=t;
	next=NULL;
}



class node{
	string city;
    node *down;
	Node *next;

public:
	node();
	node(string ct);
	friend class Graph;
};
node::node(){
	down=NULL;
	next=NULL;
	city="";

}
node::node(string ct){
	city=ct;
	next=NULL;
	down=NULL;
}

class Graph{
int n;
node *start1;
Node *start2;
public:
    Graph(){
	   n=0;
	   start1=NULL;
	   start2=NULL;
    }
	void readVertex();
	void flightDetails();
	int isListEmpty();
	void display();
	void addCity();
	void deleteCity(string);
	void indegree(string);
	void outdegree(string);
};

void Graph::readVertex(){
	string city;
	cout<<"Enter number of cities - "<<endl;
	cin>>n;
	int f=0;
	node *t1=start1;

	while(f!=n){
		cout<<"Enter the name of city "<<f+1<<" - "<<endl;
		cin>>city;
		node *temp=new node(city);
		cout<<temp->city<<endl;
		if(start1==NULL){ start1=temp; t1=start1; }
		else{
			t1->down=temp;
			t1=t1->down;
		}
		++f;
	}
}

void Graph::flightDetails(){
	string dep_city;
	string des_city;
	float time;
	cout<<"Enter departure city - "<<endl;
	cin>>dep_city;
	cout<<"Enter destination city - "<<endl;
	cin>>des_city;
	cout<<"Enter the time required to reach the destination city - "<<endl;
	cin>>time;
	node *t1=start1;
	int flag1=0;
	while(t1!=NULL){
				if(t1->city==des_city){
					flag1=1;
					break;
				}
				t1=t1->down;
			}

	t1=start1;
	int flag2=0;
	while(t1!=NULL){
		if(t1->city==dep_city){
			flag2=1;
			break;
		}
		t1=t1->down;
	}


	if(flag2==0 || flag1==0){
		cout<<"The entered city is not in List! Plz add the city in the List!"<<endl;
		return;
	}
	else if(flag2==1 && flag1==1){
		Node *temp=new Node(des_city,time);
		start2=t1->next;
		Node *t2=start2;
		if(start2==NULL){
			start2=temp;
			t2=start2;
		}
		else{
			while(t2->next!=NULL){
				t2=t2->next;
			}
			t2->next=temp;
		}
	}
	t1->next=start2;
}


void Graph::addCity(){
	string city;
	node *t1=start1;
	while(t1->down!=NULL){
		t1=t1->down;
	 }
	cout<<endl;
	cout<<"Enter the city to be added - "<<endl;
	cin>>city;
	node *temp=new node(city);
	t1->down=temp;
}

void Graph::deleteCity(string c){

	int flag1=0;
	node *t1=start1;
		while(t1!=NULL){
			if((t1->down)->city==c){
				node *temp1=t1->down;
				t1->down=(t1->down)->down;
				temp1->down=NULL;
				delete temp1;
				flag1=1;
				break;
			}
			t1=t1->down;
		 }
        cout<<"HI"<<endl;
		if(flag1==0){
			cout<<"The entered city is not in the List!"<<endl;
			return;
		}

		t1=start1;
			Node *t;
			Node *temp2;
			while(t1!=NULL){
				t=t1->next;
				while(t!=NULL){
					  if(t->city==c && t->next==NULL){
						  cout<<"Flight from "<<t1->city<<" to "<<t->city<<" has been stopped!"<<endl;
								temp2=t;
								t=NULL;
								temp2->next=NULL;
								delete temp2;
								t1->next=t;

								goto l;
						}
					   else if((t->next)->city==c){
						temp2=t->next;
						t->next=(t->next)->next;
						temp2->next=NULL;
					    delete temp2;
					    cout<<"Flight from "<<t1->city<<" to "<<t->city<<" has been stopped!"<<endl;
					}

				}
				l:
				t1=t1->down;
			}
			cout<<endl;
			cout<<"ALL THE FLIGHTS FROM "<<c<<" HAVE BEEN CANCELLED!"<<endl;
			cout<<endl;

}

int Graph::isListEmpty(){
	if(start1==NULL)
		return 1;
	else
		return 0;
}

void Graph::outdegree(string c){
	node *t1=start1;
	while(t1->city!=c){
		t1=t1->down;
	}
	Node *t=t1->next;
	int i=0;
	while(t!=NULL){
		i++;
		t=t->next;
	}
	cout<<"Outdegree of "<<t1->city<<" is "<<i<<endl;
}

void Graph::indegree(string c){

}

void Graph::display(){
	node *t1=start1;
	Node *t;
	while(t1!=NULL){
		t=t1->next;
		cout<<"DEPARTURE CITY - "<<t1->city<<endl;
		if(t==NULL){
			cout<<"NO FLIGHTS FROM THIS CITY!"<<endl;
		}
		else{
		cout<<"DESTINATION CITIES - "<<endl;
		for(;t!=NULL;t=t->next){
			cout<<t->city<<"    Time Required - "<<t->time<<endl;
		}
		}
		cout<<endl;
		t1=t1->down;
	}
}

int main() {
	int c;
	Graph obj;
    string city;

	for(; ; ){

    cout<<"*********FLIGHT ANALYSER*********"<<endl;
    cout<<"1. Enter Flight Details"<<endl;
    cout<<"2. Add a City"<<endl;
    cout<<"3. Delete a City"<<endl;
    cout<<"4. Indegree of a city"<<endl;
    cout<<"5. Outdegree of a city"<<endl;
    cout<<"6. Display data"<<endl;
    cin>>c;
    switch(c){
    case 1:  if(obj.isListEmpty()==1){
    	        cout<<"Enter Flight Database!"<<endl;
    	        cout<<endl;
    	        obj.readVertex();
             }
              obj.flightDetails();
             break;

    case 2:  obj.addCity();
             break;

    case 3:
    	    cout<<"Enter the City to be Deleted - "<<endl;
    	    cin>>city;
    	    obj.deleteCity(city);
            break;

    case 5:
    	       cout<<"Enter the City whose Outdegree is to be calculated - "<<endl;
    	    	    cin>>city;
    	    	    obj.outdegree(city);
    	            break;

    case 6:  obj.display();
             break;

    }
    cout<<"Do you want to continue?(1 if yes/0 if no)"<<endl;
    	cin>>c;
    	if(c==1)
    	{continue;}
    	else
    	{break;}
    }
	return 0;
}
