#include <gtest/gtest.h>
#include "../code/VendorCategories.h"

#include <iostream>
#include <string>

using namespace std;

class test_Empty : public ::testing::Test {
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

TEST_F(test_Empty, TestEmptyFunc1){
    VendorCategories myobj("string1", "string2");
    shared_ptr<vendor_cat> node(new vendor_cat);
    string filepath = "/home/file/name";
    ASSERT_EQ(true, myobj.AssignCategories(filepath, node));
}

TEST_F(test_Empty, TestEmptyFunc2){
    VendorCategories myobj("string1", "string2");
    shared_ptr<vendor_cat> node(new vendor_cat);
  string filepath = "/home/file/name";
    ASSERT_EQ(false, myobj.AssignCategories(filepath, node));
}
