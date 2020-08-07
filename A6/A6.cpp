//============================================================================
// Name        : A6.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
using namespace std;
#define MAX 29

class Dictionary{
	string keyword;
	string meaning;
public:
	Dictionary();
	Dictionary(string,string);
	void accept();
	friend class Hash;
};

Dictionary::Dictionary(){
	keyword="";
    meaning="";
}

Dictionary::Dictionary(string key,string mean){
	keyword=key;
	meaning=mean;
}

void Dictionary::accept(){
	cout<<"Enter the Word (Key)"<<endl;
	cin>>keyword;
	cout<<"Enter the Meaning (Value)"<<endl;
	cin>>meaning;
}


class Hash{
	Dictionary h_table[MAX];
public:
	void insert_withoutreplacement(string,string);
	void insert_withreplacement(string,string);
	int find(string);
	void del_key(string);
	void display_Hash();
	int hash_generator(string);
};

int Hash::hash_generator(string key){
	int sum=0;

	     for(int i=0;i<key.length();i++){
	    	 sum+=key[i];
	     }

	     int index=sum%MAX;

	     return index;
}

void Hash::insert_withreplacement(string key,string mean){
	 int index=hash_generator(key);
	 if((h_table[index].keyword).length()==0){
	    	 h_table[index].keyword=key;
	    	 h_table[index].meaning=mean;
	    	 return;
	  }
	     else if(h_table[index].keyword!=key){              //REPLACEMENT CONDITION

	    	 if(index!=hash_generator(h_table[index].keyword)){
	    	 string tempkey=key;
	    	 string tempmean=mean;
	    	 key=h_table[index].keyword;
	    	 mean=h_table[index].meaning;
	    	 h_table[index].keyword=tempkey;
	    	 h_table[index].meaning=tempmean;
	    	 }

	    	 int i,flag;
	        	  for(i=index+1; ;i++){
	        		  if(i==MAX){
	        			  i=0;
	        		  }
	        		  if(i==index){
	        			  flag=0;
	        			  break;
	        		  }
	        		  if((h_table[i].keyword).length()==0){
	        			  flag=1;
	        			  break;
	        		  }
	        	  }
	        	  if(flag==1){
	        		  h_table[i].keyword=key;
	        		  h_table[i].meaning=mean;
	        	  }
	        	  else{
	        		  cout<<endl;
	        		  cout<<"HASH TABLE FULL!!"<<endl;
	        	  }


	 }
}

void Hash::insert_withoutreplacement(string key,string mean){
	 int index=hash_generator(key);

     if((h_table[index].keyword).length()==0){
    	 h_table[index].keyword=key;
    	 h_table[index].meaning=mean;
    	 return;
     }

     else{                           //WITHOUT REPLACEMENT CONDITION
    	 int i,flag;
    	  for(i=index+1; ;i++){
    		  if(i==MAX){
    			  i=0;
    		  }
    		  if(i==index){
    			  flag=0;
    			  break;
    		  }
    		  if((h_table[i].keyword).length()==0){
    			  flag=1;
    			  break;
    		  }
    	  }
    	  if(flag==1){
    		  h_table[i].keyword=key;
    		  h_table[i].meaning=mean;
    	  }
    	  else{
    		  cout<<endl;
    		  cout<<"HASH TABLE FULL!!"<<endl;
    	  }
     }
}


void Hash::display_Hash(){
	cout<<"Index \t Key \t Value"<<endl;
	for(int i=0;i<MAX;i++){
		if((h_table[i].keyword).length()!=0){
			cout<<i<<"\t"<<h_table[i].keyword<<"\t"<<h_table[i].meaning<<endl;
		}

}
}

int Hash::find(string key){
	int index=hash_generator(key);
    int count=0;
	for(int i=index;count<MAX ;i++){

	    		  if(i==MAX){
	    			  i=0;
	    		  }
                  ++count;
	    		  if(h_table[i].keyword==key){

	    		  			  cout<<"No. of Comparisons are - "<<count<<endl;
	    		  			  return i;
	    		  		  }
	    	 }
	  cout<<"Keyword not present in Hash Table!"<<endl;
	  cout<<"No. of Comparisons are - "<<count<<endl;
	  return -1;

}

void Hash::del_key(string key){
	int index=find(key);
	if(index==-1){
		cout<<"Key not present in Hash Table!"<<endl;
	}
	else{
		cout<<"Keyword "<<h_table[index].keyword<<" deleted!"<<endl;
		h_table[index].keyword="";
		h_table[index].meaning="";
	}

}
int main() {

	Hash obj;
	int flag=0;
	int ch;
    string key,meaning;

    for( ; ; ){
	cout<<"***********DICTIONARY HASH TABLE**************"<<endl;
			cout<<endl;
			cout<<"1. Insert the Data "<<endl;
			cout<<"2. Display the hash table "<<endl;
			cout<<"3. Deleting a Keyword from the Dictionary "<<endl;
			cout<<"4. Finding a Keyword and No. of Comparisons"<<endl;
			cin>>ch;

			switch(ch){

			case 1:  	cout<<"1.Without Replacement"<<endl;
			            cout<<"2.With Replacement"<<endl;
			            cin>>flag;
				        cout<<"Enter the Word (Key)"<<endl;
			            cin>>key;
			            cout<<"Enter the Meaning (Value)"<<endl;
			            cin>>meaning;
			            if(flag==1)
				            obj.insert_withoutreplacement(key,meaning);
			            else
			            	obj.insert_withreplacement(key,meaning);

			            break;

			case 2:  obj.display_Hash();
			         break;

			case 3: cout<<"Enter the keyword to be deleted - "<<endl;
			        cin.ignore();
			        getline(cin,key);
			        obj.del_key(key);
                    break;

			case 4: cout<<"Enter the keyword to be searched - "<<endl;
			        cin>>key;
			         flag=obj.find(key);
			        if(flag!=-1){
			        	cout<<"Keyword found at index "<<flag<<endl;
			        }
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
