#include <iostream>
#include "../code/VendorCategories.h"
#include <memory>
#include <regex>

using namespace std;

int main(){
  VendorCategories newVendor("./statement.csv", "./categories.csv");
  string category = newVendor.GetCategoryPath();
  string statement = newVendor.GetStatementPath();
  shared_ptr<vendor_cat> tree(newVendor.BuildAVL(category));
  newVendor.PrintAVL(tree);
  //call remove categories to make sure statement does not already include categories column
  newVendor.RemoveCategories(statement);
  newVendor.AssignCategories(statement, tree);
  
  //newVendor.RemoveCategories(statement);
  return 0;
}