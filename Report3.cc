#include <iostream>
using namespace std;
#include <cstdlib>
#include<iomanip>

#include<vector>
#include<iterator>
#include <algorithm>
#include<string>

#include <fstream>

#include "Report3.h"
#include "Record.h"

Report3::Report3(){
	l=new DescBehaviour<int>();
	repo3=new ReportData<int>(l);
	ReportGenerator::populate();
}
Report3::~Report3(){
	delete repo3;
	ReportGenerator::cleanUp();
}


void Report3::computeHelper(vector<Record*>& e){
	int maxPos=0;
	max.clear();
	for(int i=0;i<e.size();i++){
		if(e[i]->getRegion()!="CAN" && e[i]->getYear()!=2011 && e[i]->getsubRegion()!="All"){
			int maxHor=0;
			for(int j=i;j<=e.size();j++){
				if(e[j]->getRegion()==e[i]->getRegion()){
					//find maximum num of animals of all within this for loops save the position and once it is false set the max Hor back to 0 let maxPos be as it is
					if(maxHor<e[j]->getnumAnimals()){
						maxHor=e[j]->getnumAnimals();
						maxPos=j;
					}			
				}
				else{	
					i=j-1;
					break;
				}
			}
			max.push_back(e[maxPos]);
		} 
	}
	
	for(int i=0;i<e.size();i++){
		int c=0;
		if(e[i]->getRegion()!="CAN" && e[i]->getYear()!=2011){
			for(int j=i;j<e.size();j++){
				if(e[j]->getRegion()==e[i]->getRegion()){
					c++;
				}
				else{
					i=j-1;
					break;
				}
			}
			if(c==1){
				max.push_back(e[i]);
			}
		}
	}

	formatData(repo3);
	printReport(repo3);
}


void Report3::compute(){
	try{
		vector<Record*>& a=animalTypeMap["Horses-Ponies"];
		computeHelper(a);
		cout<<endl;
	}
	catch(char* b){
		cout<<b<<endl;
	}
	
}

void Report3::formatData(ReportData<int>* ab){
	for(int i=0;i<max.size();i++){

		stringstream ss;
		if(max[i]->getsubRegion()=="All"){
			ss<<max[i]->getRegion()<<"   "<<setw(40)<<left<<"  "<<"  "<<setw(7)<<right<<0<<endl;

			ab->add(0,ss.str());
		}
		else{
			ss<<max[i]->getRegion()<<"   "<<setw(40)<<left<<max[i]->getsubRegion()<<"   "<<setw(6)<<right<<max[i]->getnumAnimals()<<endl;
			ab->add(max[i]->getnumAnimals(),ss.str());
		}
	}	
}

void Report3::printReport(ReportData<int>* k){
	cout<<"\n\t SUB-REGION WITH MOST HORSES/PONIES BY REGION IN 2016\t\t\n";
	cout<<"\t------------------------------------------------------\n";
	cout<<*k;
	cout<<"\t------------------------------------------------------\n";
	//now write all this shizzle into the file
	ofstream outfile("Report3.txt",ios::out);
	if (!outfile) {
    		cout << "Error:  could not open file" << endl;
    		exit(1);
  	}
  	
  	outfile<<"\n\t SUB-REGION WITH MOST HORSES/PONIES BY REGION IN 2016\t\t\n";
  	outfile<<"\t------------------------------------------------------\n";
  	outfile<<*k;
  	outfile<<"\t------------------------------------------------------\n";
  	outfile<<endl;
  	repo3->CLEAN();
}

















