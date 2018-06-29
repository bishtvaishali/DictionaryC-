//
//  main.cpp
//  Dictionary
//
//  Created by Vaishali Bisht on 6/22/18.
//  Copyright © 2018 Vaishali Bisht. All rights reserved.
//

#include <stdio.h>
#include <iostream>
#include <fstream>
#include <vector>
#include <string.h>
#include <sstream>
#include <map>
#include <algorithm>


using namespace std;

map<string, map<string, vector<string>>> dictionary;
vector<string> vPos;


string toLowerCase(string str){
    for(int i = 0; str[i]; i++)
    {
        str[i] = tolower(str[i]);
    }
    
    return str;
}


void loadDictionary(){
    string token;
    vector<string> vStr;
    
    ifstream File ("/Users/vaishalibisht/Desktop/SFSU/CSC340/Assignment-01-Code/Data.CS.SFSU.txt");
    
    if (File.is_open()){
        cout<< "! Opening data file... ./Data.CS.SFSU.txt" <<endl;
        cout << "! Loading data..."<<endl;
        
        string line;
        
        while(getline(File,line)){
            string key;
            istringstream tokenStream(line);
            
            string value;
            string lastkey;
            while(getline(tokenStream, value,'|')){
                istringstream innerStream(value);
                int pos = (int)value.find("=>");
                if(pos == -1) {
                    lastkey = value;
                } else {
                    string innerKey = value.substr(0,pos-1);
                    string innerValue = value.substr(pos+2);
                    dictionary[lastkey][innerKey].push_back(innerValue);
                    
                    if (find(vPos.begin(), vPos.end(), innerKey) == vPos.end()){
                        vPos.push_back(innerKey);
                    }
                }
            }
            
        }
        cout<< "! Loading completed..."<<endl;
        
        map<string, map<string, vector<string>>>::iterator it;
        map<string, vector<string>>::iterator ex;
        vector<string> :: iterator vc;
        
        File.close();
        cout << "! Closing data file... ./Data.CS.SFSU.txt" << endl;
    }
    else{
        cout << "Unable to open file"<<endl;
    }
    
    
    
    
}


void search(string line){
    string word;
    string arr[2];
    istringstream ss(line);
    
    //split
    int i = 0;
    while (getline(ss, word, ' ')){
        if(i>1){
            cout << "\t\t|\n\t\t <Please enter a search key (and a part of speech).>"<<endl;
            i++;
            break;
        }else{
            arr[i] = toLowerCase(word);
            if(arr[i].compare("!q") == 0){
                cout<< "\n-----THANK YOU-----"<<endl;
                exit(0);
            }
        }
        
        i++;
    }
    
    //find
    //   cout << i <<":value"<< endl;
   // cout<< "\t\t1.|" <<endl;
    if(i==0){
        cout << "\t\t|\n\t\t < Please enter a search key (and a part of speech).>"<<endl;
    }else if(i<3){
        string key;
        map<string, map<string, vector<string>>>::iterator mapIt;
        mapIt = dictionary.find(arr[0]);
        
        cout<< "\t\t|" <<endl;
        
        key = mapIt->first;
        if(mapIt == dictionary.end()){
            if(i==1){
                cout << "\t\t <Not found.>"<<endl;
            }else{
                int exists = 0;
                for(string items : vPos)
                {
                    if(arr[1] == items)
                    {
                        exists++;
                        break;
                    }
                }
                if(exists>0){
                    cout << "\t\t <Not found.>"<<endl;
                }else{
                    cout << "\t\t <2nd argument must be a part of speech.>"<<endl;
                }
            }
        }else{
            if(arr[0]!= ""){
                
                if(arr[1]== "")
                {
                    map<string, vector<string>>::iterator ex;
                    vector<string> :: iterator vc;
                    
                    for(ex = mapIt->second.begin(); ex != mapIt->second.end(); ex++) {
                        for(vc=ex->second.begin() ; vc!=ex->second.end(); vc++) {
                            cout << "\t\t " <<key << " [" << ex->first << "] :";
                            cout << vc->data() <<endl;
                        }
                    }
                }
                else{
                    int exists = 0;
                    
                    for(string items : vPos)
                    {
                        if(arr[1] == items)
                        {
                            exists++;
                            break;
                        }
                    }
                    if(exists>0){
                        try{
                            string pos = mapIt->second.find(arr[1])->first;
                            vector<string> DefVect = mapIt->second.find(arr[1])->second;
                            vector<string> :: iterator vc;
                            
                            for(vc=DefVect.begin() ; vc!=DefVect.end(); vc++) {
                                cout << "\t\t " << key << " [" << pos << "] :";
                                cout << vc->data() <<endl;
                            }
                        }catch(exception& e){
                            cout << "\t\t <Not found.>"<<endl;
                            
                        }
                    }else{
                        cout << "\t\t <2nd argument must be a part of speech.>"<<endl;
                    }
                }
            }else{
                cout << "\t\t <Please enter a search key (and a part of speech).>" <<endl;
            }
        }
    }
    
    cout<< "\t\t|\nSearch:  ";
    
}


int main(int argc, const char * argv[]) {
    
    string line;
    
    loadDictionary();
    
    cout<< "\n-----DICTIONARY 340 C++-----\n\nSearch:  ";
    
    while (getline(cin, line)){
        search(line);
    }
    
    return 0;
    
}
