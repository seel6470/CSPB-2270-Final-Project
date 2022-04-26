#include <gtest/gtest.h>
#include "../code/VendorCategories.h"

#include <iostream>
#include <string>
#include <fstream>

using namespace std;

class test_vendor_cat : public ::testing::Test {
protected:
	// This function runs only once before any TEST_F function
	static void SetUpTestCase(){
	}

	// This function runs after all TEST_F functions have been executed
	static void TearDownTestCase(){
	}
    
	// this function runs before every TEST_F function
	void SetUp() override {
    }

	// this function runs after every TEST_F function
	void TearDown() override {
	}
};

TEST_F(test_vendor_cat, StructConstruction){
  shared_ptr<vendor_cat> node(new vendor_cat);
  string name = "McDonalds";
  string category = "Eating Out";
  node->name = name;
  node->category = category;
  //names should match
  ASSERT_EQ(name, node->name);
  //categories should match
  ASSERT_EQ(category, node->category);
}

TEST_F(test_vendor_cat, ClassConstruction){
  string file1 = "untitled.csv";
  string file2 = "untitled (2).csv";
  VendorCategories myobj(file1, file2);
  //respective file path strings should match
  ASSERT_EQ(file1, myobj.GetStatementPath());
  ASSERT_EQ(file2, myobj.GetCategoryPath());
}

TEST_F(test_vendor_cat, BuildAVL){
  VendorCategories m("statement.csv","categories.csv");
  string categories = m.GetCategoryPath();
  //build AVL tree with a non existent file path
  shared_ptr<vendor_cat> null_root(m.BuildAVL("incorrect.csv"));
  bool is_null = null_root == NULL;
  //avl tree should be NULL
  ASSERT_TRUE(is_null);
  //create a valid AVL tree
  shared_ptr<vendor_cat> tree_root(m.BuildAVL(categories));
  is_null = tree_root == NULL;
  //should not be NULL
  ASSERT_FALSE(is_null);
}

TEST_F(test_vendor_cat, AssignCategories){
  VendorCategories newVendor("statement.csv", "categories.csv");
  string category = newVendor.GetCategoryPath();
  string statement = newVendor.GetStatementPath();
  //remove categories in case AssignCategories was already run
  newVendor.RemoveCategories(statement);
  shared_ptr<vendor_cat> tree(newVendor.BuildAVL(category));
  bool assign_complete = newVendor.AssignCategories(statement, tree);
  //should return true
  ASSERT_TRUE(assign_complete);
  //should be the value of 23rd row
  string twenty_third_row = "\"04/15/2022\",\"-12.99\",\"*\",\"\",\"PURCHASE AUTHORIZED ON 04/13 WENDY'S 3735 GRAND JUNCTIO CO S302103625096467 CARD 9179\",\"Eating Out\"";
  
  //read contents of file until 23rd row is reached
  ifstream file;
  file.open(statement);
  int row = 1;
  string cur_row;
  while (getline(file, cur_row) && row < 23){
    row++;
  }
  file.close();
  //should be equal
  ASSERT_EQ(twenty_third_row, cur_row);
  
  //contents of 23rd row before
  twenty_third_row = "\"04/15/2022\",\"-12.99\",\"*\",\"\",\"PURCHASE AUTHORIZED ON 04/13 WENDY'S 3735 GRAND JUNCTIO CO S302103625096467 CARD 9179\"";
  newVendor.RemoveCategories(statement);
  file.open(statement);
  row = 1;
  while (getline(file, cur_row) && row < 23){
    row++;
  }
  //should be equal after removal
  ASSERT_EQ(twenty_third_row, cur_row);
}

bool recursiveInvariantCheck(shared_ptr<vendor_cat> node){
  static bool ret = true;
  if (node->left){
    ret = recursiveInvariantCheck(node->left);
  }
  
  int balance_factor = 0;
  if (node->left){
    //left balances are negative
    balance_factor -= node->left->height;
  }else{
    //null left subtree counts toward right height
    balance_factor++;
  }
  if (node->right){
    //right balances are positive
    balance_factor += node->right->height;
  }else{
    //null right subtree counts toward left height
    balance_factor--;
  }
  
  if (balance_factor > 1 && balance_factor < -1) {
    ret = false;
  } 
  
  
  if (node->right){
    ret = recursiveInvariantCheck(node->right);
  }
  return ret;
}

TEST_F(test_vendor_cat, AVLBalanced){
  VendorCategories newVendor("statement.csv", "categories.csv");
  string category = newVendor.GetCategoryPath();
  string statement = newVendor.GetStatementPath();
  shared_ptr<vendor_cat> tree(newVendor.BuildAVL(category));
  shared_ptr<vendor_cat> cur(tree);
  recursiveInvariantCheck(tree);
  newVendor.PrintAVL(tree);
}
