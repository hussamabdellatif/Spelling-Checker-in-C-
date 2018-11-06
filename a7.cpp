#include <iostream>
#include <map>
#include <string>
#include <algorithm>
#include<fstream>
#include <cmath>
#include <unordered_map>

using namespace std;

void printing_dic(map<string,int>dic ){
  map<string,int>::iterator it = dic.begin();
  for(it = dic.begin();it!=dic.end(); ++it){
    cout<<it->first<<" => "<<it->second<<endl;
  }
}



int main(int argc, char const *argv[]) {
  map<string,int>*dic = new map<string,int>;
  ifstream file(argv[1]);
  string line;
  string name;
  string fs;
  int freq;
  int space_loc;
  while(file.good()){
    getline(file, line);
    if(line.empty())break;
    space_loc = line.find(' ');
    name = line.substr(0,space_loc);
    fs = line.substr(space_loc+1,line.size()-1);
    freq = stoi(fs);
    dic->insert(pair<string,int>(name,freq));
  }
file.close();
string input;
cin>>input;
int input_size;
string new_word;
string temp;
map<string,int>* user_input = new map<string,int>;
map<string,int> results;

map<string,int>::iterator it_dic;
map<string,int>::iterator it;
map<string,int>::iterator dic_it = dic->begin();
while(!(input.empty() || input.size() == 0)){
  user_input->clear();
  results.clear();


  //input contains the whole word.
  input_size = input.size();
  //First possibility: Deleting one character ----Works
  //storing each possibility into the the dic;
  dic_it = dic->find(input);

  if(dic_it != dic->end()){
    int fre= dic_it->second;
    cout<<dic_it->first<<" "<<fre<<endl;
    int new_num = fre+1;
    dic->erase(dic_it);
    dic->insert(pair<string,int>(input, new_num));

  }else{

  for(int i=0; i<input_size;i++){
    temp = input;
    temp.at(i) = ' ';
    new_word = temp;
    new_word.erase(remove(new_word.begin(), new_word.end(), ' '));
    user_input->insert(pair<string, int>(new_word, 0));
  }
  //Second Possibility: Adding a letter (n+1)*26 possibilities

  for(int i=0 ; i<input_size+1; i++){
    temp = input;
    temp.insert(i," ");
    for(int j=65;j<=90;j++){
      char alp_letter = j;
      temp[i] = alp_letter;
      new_word = temp;
      user_input->insert(pair<string,int>(new_word,0));

    }
  }
  //third possibility: replacing a letter n*25 or n*26  (there will be repetition but not important);

  for(int i=0; i<input_size; i++){
    temp =input;
    for(int j=65;j<=90;j++){
      char alp_letter = j;
      temp[i] = alp_letter;
      new_word = temp;
      user_input->insert(pair<string, int>(new_word,0));
    }
  }
  //At this point I have generated all possibile possibilities of the input string, they are now stored inside user_input.
  it = user_input->begin();

  for(it = user_input->begin(); it != user_input->end();it++){
    string key = it->first;
    it_dic = dic->find(key);

    //if it_dic != end means that we found a match
    if(it_dic != dic->end()){

      //if the results empty, insert first match
      int it_freq = it_dic->second;
      if(results.empty()){
      results.insert(pair<string, int>(key, it_freq));
      }else{
      //since results is not empty, now you can compare.
      it_dic = results.begin();
      string old_key = it_dic->first;
      int old_freq = it_dic->second;
      string new_key = key;
      int new_freq = it_freq;

      if(new_freq > old_freq){
        results.clear();
        results.insert(pair<string,int>(new_key,new_freq));
      }else if(old_freq > new_freq){
        //do nothing
      }else{
        // they are equall, so compare lexigrophically....
        if(new_key<old_key){
          results.clear();
          results.insert(pair<string,int>(new_key,new_freq));
        }
      }


      }
    }
  }
  if(results.empty()){
    //no matches at all;
    cout<<"-"<<endl;
    dic->insert(pair<string,int>(input,1));

  }else{
    map<string, int>::iterator it = results.begin();
    cout<<it->first<<" "<<it->second<<endl;
    results.clear();
  }





}

input.clear();
cin>>input;

}
delete dic;
delete user_input;
return 0;
}
