//============================================================================
// Name        : Q4.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <fstream>
#include <string.h>
using namespace std;

//int find(char x, char words[2000][2]){
//	for(int i=0;i<2000;i++){
//		if(strcmp(words[i],"NULL")!=0 && strcmp(x,words[i])==0)
//			return 1;
//	}
//	words[i] = x;
//	return 0;
//}

int main() {
	ifstream inFile;
	int i;
	char x[100];
	char words[2000][2000];
	for(i=0;i<200;i++){
		words[i] = "NULL";
	inFile.open("/home/student/Downloads/cranfield0001.txt");
	i=0;
	while(inFile >> x){
		if(strcmp(x,"<TEXT>")==0){
			while(inFile >> x){
				if(strcmp(x,"</TEXT>")!=0){
					cout<<x<<" ";

				}
				else
					break;
			}
		}
	}

	cout<<"Occurences:\n";
	for(int j=0;j<=i;j++){
		cout<<words[j][0]<<": "<<words[j][1]<<endl;
	}
	inFile.close();
	return 0;
}
