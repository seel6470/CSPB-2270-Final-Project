#ifndef VENDOR_CAT__
#define VENDOR_CAT__
#include <memory>
#include <string>
#include <vector>

using namespace std;

struct vendor_cat {
  string name;
  string category;
  shared_ptr<vendor_cat> left;
  shared_ptr<vendor_cat> right;
  //default height to 0
  int height = 0;
};



class VendorCategories{
public:
  string GetStatementPath();
  string GetCategoryPath();
  
  //constructor
  VendorCategories(string statement_filepath, string categories_filepath);
  //destructor - will be using shared_ptr so won't need to change the destructor
  ~VendorCategories();
  
  //This function will receive the filepath for a csv file with only two columns. 
  //Each row will contain the vendor and category 
  //The function will open the csv and for each row it will create a vendor_cat struct and insert it into the self-balancing AVL Tree
  //Will return a shared_ptr to the root of the AVL that is created
  shared_ptr<vendor_cat> BuildAVL(string vendor_categories_filepath);
  
  //This function will receive the filepath of the bank statement 
  //(should be a csv in the format of a bank statement downloaded from Wells Fargo website) 
  //and iterate through each transaction, using the vendor name to search through the AVL Tree. 
  //If found, it will add an additional column to the bank statement csv with the corresponding category. 
  //If not found, it will not perform any operations for that row
  //Will return “True” if all transactions are iterated through without errors
  //Will return “False” if any of the following are encountered:
      //filepath is not in .csv format
      //filepath is non-existent
      //AVL Tree is empty
      //csv has fewer/more columns than expected
      //no transactions are matched with a vendor and no categories are added to the csv
  bool AssignCategories(string statement_filepath, shared_ptr<vendor_cat> root);
  
  //This function will remove all categories from a csv that has already had categories assigned. 
  //This will be important for unit testing, as it would be ideal for the same csv file to be reused, even after it has categories assigned
  //Will return “True” if categories have been removed (or if there were no categories to begin with)
  //Will return “False” if errors are encountered (e.g. filepath not csv or nonexistent)
  bool RemoveCategories(string statement_filepath);
  
  //Will print the contents of the AVL tree starting at root to the console
  //using DOT language to be visualized with Graphviz (http://webgraphviz.com)
  void PrintAVL(shared_ptr<vendor_cat> root);
  //recursive call to print each node
  void PrintAVLRecursive(shared_ptr<vendor_cat> root);

  //will print the csv file for debugging
  void PrintCSV(string file_path);
    
private:
  //This function will insert a vendor_cat node into the avl_tree private member variable 
  //following BST insert traversal and AVL self-balancing along the way. Will be used in the CreateAVL public function.
  //Will use the vendor_name string of vendor_cat node as the key during traversal
  //recursive function to be able to set height on exit of each recursive call
  shared_ptr<vendor_cat> AVLInsert(shared_ptr<vendor_cat> node, shared_ptr<vendor_cat> root);
  
  //rotation helper functions that will be called according to the balance_factor value
  //if absolute value of balance factor is > 1
  shared_ptr<vendor_cat> RotateRight(shared_ptr<vendor_cat> node);
  shared_ptr<vendor_cat> RotateLeft(shared_ptr<vendor_cat> node);

  
  
  //This function will search the AVL tree using bst search traversal using the vendor_name as the key
  //If a match is found the vendor_cat node is returned, else NULL is returned
  shared_ptr<vendor_cat> AVLSearch(shared_ptr<vendor_cat> root, string vendor_name);
  
  //private member values storing the filepaths for the statement and categories csv files
  string statement_csv;
  string categories_csv;
};

#endif // VENDOR_CAT__