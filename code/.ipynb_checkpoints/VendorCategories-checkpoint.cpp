#include "VendorCategories.h"
#include <memory>
#include <string>
#include <fstream>
#include <iostream>
#include <vector>
#include <sstream>
#include <regex>

using namespace std;


VendorCategories::VendorCategories(string statement_filepath, string categories_filepath){
  //class constructor, sets filepaths of categories and statement csv files
  statement_csv = statement_filepath;
  categories_csv = categories_filepath;
}

VendorCategories::~VendorCategories(){
    //nothing to do here, using shared_ptr
}

string VendorCategories::GetStatementPath(){
  return statement_csv;
}

string VendorCategories::GetCategoryPath(){
  return categories_csv;
}

vector<vector<string>> CSVToVector(string file_path){
  //vector of string vectors to contain 2D array with all csv data
  vector<vector<string>> data;
  //ifstream = class to open file streams (specifically input)
  ifstream file_in;
  //open csv in filestream
  file_in.open(file_path);
  //out parameter where the output for each line will be stored;
  
  string out_string;
  //vector to contain each cell in a single row
  vector<string> line;
  //while there is a valid line in stream
  while (getline(file_in, out_string)) {
    //convert to istringstream to pass the string to stream
    istringstream string_input(out_string);
    //out parameter where each cell will be stored
    string cell;
    //while there is a valid stream in istringstream
    while (getline(string_input, cell)){
      //regex object to store captures
      smatch captures;
      string expression = "\"[^\"]*\"";
      //while searches can be found
      while (regex_search(cell, captures, regex(expression))){
        //push cell that was matched to line
        line.push_back(captures[0]);
        //set cell to everything that wasn't matched and find another match
        cell = captures.suffix();
      }
    }
    //push line to data vector
    data.push_back(line);
    //clear line to use again
    line.clear();
  }
  file_in.close();
  return data;
}

void overwriteCSV(string file_path, vector<vector<string>> data){
  //stream to write to
  ofstream csv;
  //open write only stream
  csv.open(file_path, ios::out);
  //iterate through csv data (2D vector)
  for (unsigned int i = 0; i < data.size(); i++){
    for (unsigned int j = 0; j < data.at(i).size(); j++){
      csv << data.at(i).at(j);
      if (j < data.at(i).size() - 1){
        csv << ",";
      }else{
        csv << "\n";
      }
    }
  }
  csv.close();
}

shared_ptr<vendor_cat> VendorCategories::BuildAVL(string vendor_categories_filepath){
  //convert to 2D vector to convert each row to a node
  vector<vector<string>> data = CSVToVector(vendor_categories_filepath);
  if (data.size() == 0){
    return NULL;
  }
  shared_ptr<vendor_cat> ret;
  //iterate through data and create AVL tree
  for (unsigned int i = 0; i < data.size() - 1; i++){
    //categories csv must have only two columns, first col is name and second is category
    shared_ptr<vendor_cat> node(new vendor_cat);
    node->name = data.at(i).at(0);
    node->category = data.at(i).at(1);
    ret = AVLInsert(node, ret);
    //AVLBalance here, or in insert?
  }
  //uncomment to debug AVL tree, especially self-balancing properties
  //PrintAVL(ret);
  return ret;
}

bool VendorCategories::AssignCategories(string statement_filepath, shared_ptr<vendor_cat> root){
  //create a 2D vector with CSV data
  vector<vector<string>> data = CSVToVector(statement_filepath);
  //iterate through each row
  for (unsigned int i = 0; i < data.size(); i++){
    //if row is not empty
    if (!data.at(i).empty()){
      //all wells fargo bank statements store transaction info in column 5 (index 4 in vector)
      string original_string = data.at(i).at(4);
      //out param to store capture groups
      smatch capture_groups;
      //regular expression to parse text convention for most transactions
      string expression = "(\")(\\D*)(\\s)(\\d\\d\\/\\d\\d)(\\s)(.*)(\\s)([P,S]\\d{15})(\\s)(CARD \\d{4})(\")";
      bool matched = regex_match(original_string, capture_groups, regex(expression));
      string key = data.at(i).at(4);
      if (matched){
        //is matching, going out of range
        //capture group 0 contains entire string
        //1, 3, 5, 7, 9, and 11 contain matches of white space and double quotes
        //necessary to match to find each section of text, however not significant data
        string purchase_text = capture_groups[2];
        string date = capture_groups[4];
        string vendor = capture_groups[6];
        string transaction_id = capture_groups[8];
        string card_number = capture_groups[10];
        //add double quotes to match other cells
        //quotes are necessary for text that contains a ,
        key = "\"";
        key += vendor;
        key += "\"";
      }
      //find a match in AVL tree
      shared_ptr<vendor_cat> node_match(AVLSearch(root, key));
      if (node_match){
        //if match was found, add category to end of row
        data.at(i).push_back(node_match->category);
      }
    }
  }
  overwriteCSV(statement_filepath, data);
  //PrintCSV(statement_filepath);
  return true;
}

bool VendorCategories::RemoveCategories(string statement_filepath){
  //convert to 2D vector
  vector<vector<string>> data(CSVToVector(statement_filepath));
  //remove anything past index 4 (size is one more than last index)
  for (unsigned int i = 0; i < data.size(); i++){
    while (data.at(i).size() > 5){
      data.at(i).pop_back();
    }
  }
  //overwrite to filepath
  overwriteCSV(statement_filepath, data);
  return true;
}

void VendorCategories::PrintAVLRecursive(shared_ptr<vendor_cat> root){
  //static variable to keep track of how many null nodes there are
  //this is important to ensure unique qualities of each null node
  static int null_count = 0;
  if (!root){
    return;
  }
  if (root->left){
    cout << "    " << root->name << " -> " << root->left->name << ";" << endl;
    //recursive left
    PrintAVLRecursive(root->left);
  }else{
    //null left node
    //make it a point so it is not very noticeable
    cout << "    null" << null_count << " [shape=point];" << endl;
    cout << "    " << root->name << " -> null" << null_count << ";" << endl;
    //increment static variable
    null_count++;
  }
  
  if (root->right){
    cout << "    " << root->name << " -> " << root->right->name << ";" << endl;
    //recursive right
    PrintAVLRecursive(root->right);
  }else{
    //null right, point so not noticeable
    cout << "    null" << null_count << " [shape=point];" << endl;
    cout << "    " << root->name << " -> null" << null_count << ";" << endl;
    //increment static variable
    null_count++;
  }
}

void VendorCategories::PrintAVL(shared_ptr<vendor_cat> root) {
  cout << "go to http://webgraphviz.com/ to copy and paste the following lines and generate a visual representation of the AVL tree" << endl;
  cout << "\n\ndigraph AVL {" << endl;
  cout << "    node [fontname=\"Arial\"];" << endl;
  //recursive call to traverse tree
  PrintAVLRecursive(root);
  cout << "}" << endl;
};

void VendorCategories::PrintCSV(string file_path){
  cout << "printing csv located at " << file_path << endl;
  //convert csv to vector
  vector<vector<string>> data(CSVToVector(file_path));
  for (unsigned int i = 0; i < data.size(); i++){
    for (unsigned int j = 0; j < data.at(i).size(); j++){
      cout << data.at(i).at(j);
      if (j < data.at(i).size() - 1){
        cout << ", ";
      }else{
        cout << "\n";
      }
    }
  }
}

void setHeight(shared_ptr<vendor_cat> node){
  int height = 0;
  if (!node){
    //no height to set
    return;
  }
  if (node->left && node->left->height > height){
    height = node->left->height;
  }
  if (node->right && node->right->height > height){
    height = node->right->height;
  }
  node->height = height + 1;
}

shared_ptr<vendor_cat> VendorCategories::RotateRight(shared_ptr<vendor_cat> node){
  if (!node->left){
    //if there is no left node, should not rotate
    return node;
  }
  //going to take the place of node to be rotated
  shared_ptr<vendor_cat> old_left(node->left);
  //currently right of left node, going to be left of node to be rotated after it has been replaced
  shared_ptr<vendor_cat> old_left_right(node->left->right);
  old_left->right = node;
  node->left = old_left_right;
  //set heights
  setHeight(old_left);
  setHeight(old_left_right);
  return old_left;
}

shared_ptr<vendor_cat> VendorCategories::RotateLeft(shared_ptr<vendor_cat> node){
  if (!node->right){
    //if there is no right, should not rotate
    return node;
  }
  //going to take the place of node to be rotated
  shared_ptr<vendor_cat> old_right(node->right);
  //currently left of right node, going to be right of node to be rotated after it has been replaced 
  shared_ptr<vendor_cat> old_right_left(node->right->left);
  old_right->left = node;
  node->right = old_right_left;
  //set heights
  setHeight(old_right);
  setHeight(old_right_left);
  return old_right;
}


//private member functions
shared_ptr<vendor_cat> VendorCategories::AVLInsert(shared_ptr<vendor_cat> node, shared_ptr<vendor_cat> root){
  if (!root){
    //base case, will work with root node, as well as all leaf nodes
    root = node;
  }
  //traverse like a normal BST
  if (node->name < root->name){
    root->left = AVLInsert(node, root->left);
  }else if (node->name > root->name){
    root->right = AVLInsert(node, root->right);
  //no duplicates allowed
  }else if (node->name == root->name){
    return root;
  }
  
  //calculate balance factor using height of children
  int balance_factor = 0;
  setHeight(root);
  if (root->left){
    //left balances are negative
    balance_factor -= root->left->height;
  }else{
    //null left subtree counts toward right height
    balance_factor++;
  }
  if (root->right){
    //right balances are positive
    balance_factor += root->right->height;
  }else{
    //null right subtree counts toward left height
    balance_factor--;
  }

  //balance factor determines whether or not tree should be rebalanced
  //balance factor > 1 or < -1 must be rebalanced
  
  //left subtree is longer than right
  if (balance_factor < -1 && root->left){
    //first case, left is longer and recursively called insert left then left
    if (node->name < root->left->name){
      //rotate right
      return RotateRight(root);
    //second case, left is longer and recursively called insert left then right
    }else if (node->name > root->left->name){
      //rotate left node left
      root->left = RotateLeft(root->left);
      //rotate right
      return RotateRight(root);
    }
  }
  
  //right subtree is longer than left
  if (balance_factor > 1 && root->right){
    //third case, right is longer and recursively called insert right then right
    if (node->name > root->right->name){
      //rotate left
      return RotateLeft(root);
    //second case, right is longer and recursively called insert right then left
    }else if (node->name < root->right->name){
      //rotate right node right
      root->right = RotateRight(root->right);
      //rotate left
      return RotateLeft(root);
    }
  }
  return root;
}

shared_ptr<vendor_cat> VendorCategories::AVLSearch(shared_ptr<vendor_cat> root, string vendor_name){
  //normal BST search
  shared_ptr<vendor_cat> cur(root);
  while (cur){
    if (vendor_name == cur->name){
      return cur;
    }
    if (vendor_name < cur->name){
      if (cur->left){
        cur = cur->left;
      }else{
        return NULL;
      }
    }else{
      if (cur->right){
        cur = cur->right;
      }else{
        return NULL;
      }
    }
  }
  return NULL;
}