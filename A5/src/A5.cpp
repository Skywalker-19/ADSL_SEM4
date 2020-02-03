//============================================================================
// Name        : A5.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <bits/stdc++.h>
using namespace std;

class Business{
	int n;
    int **cost;
public:
    void cityDetails();
    void displayMatrix();
	void prims(int);
		void printMST(int*,int);
		int minKey(int*,bool*);
};

 void Business::cityDetails(){
	cout<<"Enter the no. of cities - "<<endl;
	cin>>n;

	cost=new int *[n];
	for(int i=0;i<n;i++){
		cost[i]=new int[n];
	}


	for(int i=0;i<n;i++){
		for(int j=i;j<n;j++){
           if(j!=i){
        	   cout<<"Enter cost for connection between city "<<i+1<<" and city "<<j+1<<endl;
        	   cin>>cost[i][j];
        	   cost[j][i]=cost[i][j];
           }
		}
	}
}

 void Business::displayMatrix(){
	 for(int i=0;i<n;i++){
		 for(int j=0;j<n;j++){
			 cout<<cost[i][j]<<" ";
		 }
		 cout<<endl;
	 }
 }



 void Business::prims(int start=0){  //MST
 	int *connection=new int[n];
 	int *key=new int[n];
 	bool *prim_set=new bool[n];

 	for(int i=0;i<n;i++){
 		connection[i]=-1;
 		key[i]=INT_MAX;
 		prim_set[i]=false;
 	}
 	key[start]=0;
 	connection[start]=-1;

 	for(int i=0;i<n;i++){
 		int current=minKey(key,prim_set);
 		prim_set[current]=true;
 		for(int j=0;j<n;j++){
 			if(cost[current][j]&&prim_set[j]==false&&cost[current][j]<key[j]){
 				connection[j]=current;
 				key[j]=cost[current][j];
 			}
 		}
 	}
 	this->printMST(connection,start);
 }

 int Business::minKey(int *key,bool *prim_set){
 	int min=INT_MAX;
 	int index;
 	for(int i=0;i<n;i++){
 		if(prim_set[i]==false&&key[i]<min){
 			min=key[i];
 			index=i;
 		}
 	}
 	return index;
 }

 void Business::printMST(int *connection,int start){
 	int sum=0;
 	cout<<"\nConnections \t Weight\n";
 	for(int i=0;i<n;i++){
 		if(i==start)	continue;
 		cout<<connection[i]+1<<" - "<<i+1<<"\t "<<cost[i][connection[i]]<<"\n";
 		sum=sum+cost[i][connection[i]];
 	}
 	cout<<"Optimal Connection Cost: "<<sum<<"\n";
 }

int main(){
	Business b;
	b.cityDetails();
	b.displayMatrix();
	b.prims(0);

	return 0;
}
