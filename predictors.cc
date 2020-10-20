#include<iostream>
#include<fstream>
#include<sstream>
#include<string>
#include<vector>

using namespace std;

//always taken
int alwaysTaken(vector<string> entries){
  //amount correct gonna be added to in for loop  
  long amountCorrect = 0;
  for( int i = 0; i < entries.size(); i++){
    if(entries[i] == "T"){
      amountCorrect++;
    }
  }
  return amountCorrect;
}
//always nontaken
int alwaysNotTaken(vector<string> entries ){
  long amountCorrect = 0;
  for(int i = 0; i < entries.size(); i++) {
    if(entries[i] != "T" ){
      amountCorrect++;
    }
  }
  return amountCorrect;
}


//one bit bimodal
int oneBitBimodal(vector<string> entries,vector<unsigned long long> addresses, int tableSize){
  //set all values in table to t
  string table[tableSize];
  for(int i = 0; i<tableSize; i++){
    table[i] = "T";
  }
  int amountCorrect = 0;
  int index;
  for(int i=0; i<entries.size();i++){
    index = addresses.at(i) % tableSize;
    if( table[index]  == "T" && entries.at(i) == "T"){
      amountCorrect++;
    }
    if(table[index] == "NT" && entries.at(i) == "NT"){
      amountCorrect++;
    }
    if (table[index] == "T" && entries.at(i) == "NT"){
      table[index] = "NT";
    }
    if(table[index] == "NT" && entries.at(i) == "T"){
      table[index] = "T";
    }
  }
  return amountCorrect;
}

//two bit bimodal
int twoBitBimodal(vector<string> entries, vector<unsigned long long> addresses, int tableSize){
  //initial state of all prediction counters is “Strongly Taken” (TT)
  int table[tableSize];
  int amountCorrect = 0;
  int index;
  for(int i=0; i<tableSize; i++){
    table[i] = 11;
  }
  for(int i = 0; i<entries.size(); i++){
    index = addresses.at(i) % tableSize;
    if((table[index] == 11 && entries.at(i) == "T") || (table[index] == 10 && entries.at(i) == "T")){
      amountCorrect++;
    }
    if((table[index] == 01 && entries.at(i) == "NT") || (table[index] == 00 && entries.at(i) == "NT")){
      amountCorrect++;
    }
    if(table[index] == 11 && entries.at(i) =="NT"){
      table[index] = 10;
    }
    if(table[index] == 10 && entries.at(i) == "NT"){
      table[index] = 01;
    }
    if(table[index] == 01 && entries.at(i) =="T"){
      table[index] = 10;
    }
    if(table[index] == 00 && entries.at(i) == "T"){
      table[index]=01;
    }
  }
  return amountCorrect;
}

//gshare
int gshare(vector<string> entries, int k){
  //predition counter XORed wuth history bits
  int tableSize = 2048; //fixed entries
  int index;
  return 0;  
}
int main(int argc, char *argv[]) {

  // Temporary variables                                                        
  unsigned long long addr;
  string behavior;
  unsigned long long target;
  vector<string> givenEntries;
  vector<unsigned long long> givenAddress;                                                
  // Open file for reading                                                      
  ifstream infile(argv[1]);
  ofstream outfile(argv[2]);
  // The following loop will read a hexadecimal number and                      
  // a string each time and then output them                                    
  while(infile >> std::hex >> addr >> behavior >> std::hex >> target) {
    cout << addr;
    if(behavior == "T") {
      cout << " -> taken, ";
      givenEntries.push_back("T");
    }else {
      cout << " -> not taken, ";
      givenEntries.push_back("NT");
    }
    givenAddress.push_back(addr);   
    cout << "target=" << target << endl;
  }
  //always taken
  //takes entries, runs function, outputs amount of correct entries and how many were given
  int retAmountCorrect = alwaysTaken(givenEntries);
  outfile << retAmountCorrect << "," << givenEntries.size() << ";" <<endl;

  //always not taken                                                             
  //takes entries, runs function                                                                        
  retAmountCorrect = alwaysNotTaken(givenEntries);
  outfile << retAmountCorrect << "," <<givenEntries.size() << ";" <<endl;

  //bimodal predictor 1 bit of history
  //make table size options in an array
  int tableSize[7]={16,32,128,256,512,1024,2048};
  //loop through array
  for(int i=0; i<7; i++){
    retAmountCorrect = oneBitBimodal(givenEntries, givenAddress, tableSize[i]);
    outfile << retAmountCorrect << "," << givenEntries.size() << ";";
  }
  outfile << endl;

  //two bit bimodal
  for(int i=0; i<7; i++){
    retAmountCorrect = twoBitBimodal(givenEntries, givenAddress, tableSize[i]);
    outfile << retAmountCorrect << "," << givenEntries.size() <<";";
  }
  outfile << endl;


  //gshare 
  for(int i = 3; i <12; i++){
    //retAmountCorrect = gShare(givenEntries, i);
    //outfile << retAmountCorrect << "," << givenEntries.size() << ";";
  }
  //outfile << endl;
  
  //tournament
  //
  return 0;
}
