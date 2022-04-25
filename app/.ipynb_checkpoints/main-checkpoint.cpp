#include <iostream>
#include "../code/VendorCategories.h"
#include <memory>
#include <regex>

using namespace std;

void testRegex(string cell, string expression) {
  smatch m;
  bool matched = regex_match(cell, m, regex(expression));
  for (unsigned int i = 0; i < m.size(); i++){
    cout << "group " << i << ": " << m[i] << endl;
  }
  cout << "bool: " << matched << endl;
                             
}

int main(){
  VendorCategories newVendor("./statement.csv", "./categories.csv");
  string category = newVendor.GetCategoryPath();
  string statement = newVendor.GetStatementPath();
  shared_ptr<vendor_cat> tree(newVendor.BuildAVL(category));
  //newVendor.PrintCSV(statement);
  //newVendor.PrintCSV(category);
  //newVendor.RemoveCategories(statement);
  newVendor.AssignCategories(statement, tree);
  //string cell = "\"PURCHASE AUTHORIZED ON 04/16 CITY MARKET 444 2600 NORT GRAND JUNCTIO CO P462107090484175 CARD 1003\"";
  //cout << cell << endl;
  //string expression = "(\")(\\D*)(\\s)(\\d\\d\\/\\d\\d)(\\s)(.*)(\\s)([P,S]\\d{15})(\\s)(CARD \\d{4})(\")";
  //testRegex(cell, expression);
  return 0;
}