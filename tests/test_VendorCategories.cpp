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
  ASSERT_EQ(name, node->name);
  ASSERT_EQ(category, node->category);
}

TEST_F(test_vendor_cat, ClassConstruction){
  string file1 = "untitled.csv";
  string file2 = "untitled (2).csv";
  VendorCategories myobj(file1, file2);
  ASSERT_EQ(file1, myobj.GetStatementPath());
  ASSERT_EQ(file2, myobj.GetCategoryPath());
}

TEST_F(test_vendor_cat, BuildAVL){
  VendorCategories m("statement.csv","categories.csv");
  string categories = m.GetCategoryPath();
  shared_ptr<vendor_cat> null_root(m.BuildAVL("incorrect.csv"));
  bool is_null = null_root == NULL;
  ASSERT_TRUE(is_null);
  shared_ptr<vendor_cat> tree_root(m.BuildAVL(categories));
  is_null = tree_root == NULL;
  ASSERT_FALSE(is_null);
}

TEST_F(test_vendor_cat, AssignCategories){
  VendorCategories newVendor("statement.csv", "categories.csv");
  string category = newVendor.GetCategoryPath();
  string statement = newVendor.GetStatementPath();
  newVendor.RemoveCategories(statement);
  shared_ptr<vendor_cat> tree(newVendor.BuildAVL(category));
  bool assign_complete = newVendor.AssignCategories(statement, tree);
  ASSERT_TRUE(assign_complete);
  string twenty_third_row = "\"04/15/2022\",\"-12.99\",\"*\",\"\",\"PURCHASE AUTHORIZED ON 04/13 WENDY'S 3735 GRAND JUNCTIO CO S302103625096467 CARD 9179\",\"WENDY'S 3735 GRAND JUNCTIO CO\",\"Eating Out\"";
  
  ifstream file;
  file.open(statement);
  int row = 1;
  string cur_row;
  while (getline(file, cur_row) && row < 23){
    row++;
  }
  file.close();
  ASSERT_EQ(twenty_third_row, cur_row);
  
  twenty_third_row = "\"04/15/2022\",\"-12.99\",\"*\",\"\",\"PURCHASE AUTHORIZED ON 04/13 WENDY'S 3735 GRAND JUNCTIO CO S302103625096467 CARD 9179\"";
  newVendor.RemoveCategories(statement);
  file.open(statement);
  row = 1;
  while (getline(file, cur_row) && row < 23){
    row++;
  }
  ASSERT_EQ(twenty_third_row, cur_row);
}

TEST_F(test_vendor_cat, AVLBalanced){
  VendorCategories newVendor("statement.csv", "categories.csv");
  string category = newVendor.GetCategoryPath();
  string statement = newVendor.GetStatementPath();
  shared_ptr<vendor_cat> tree(newVendor.BuildAVL(category));
  shared_ptr<vendor_cat> cur(tree);
  int height_of_left = 0;
  int height_of_right = 0;
  while (cur->left){
    cur = cur->left;
    height_of_left++;
  }
  cur = tree;
  while (cur->right){
    cur = cur->right;
    height_of_right++;
  }
  newVendor.PrintAVL(tree);
  ASSERT_EQ(height_of_left, height_of_right);
}
