# Assign Categories to Transactions Using an AVL Tree

Project: Adding Budget Categories to Bank Statements Using an AVL Tree
Name: Seth Ely
Class and Semester: CSPB2270 , Spring 2022

To track my own personal spending, I use a budget with close to 30 categories. I then track each and every expenditure in a spreadsheet and assign categories to each transaction, allowing me to track the totals for each category and know how much I have left for each month. I find myself having to add similar transactions from duplicate vendors to the same category, and have often wanted to create a program to read my bank account statement (downloaded as a .csv) and assign each known vendor with its corresponding category. For each transaction, the program would need to strip unnecessary information from the transaction string (date, location, purchase number, and card number) and search the AVL for a match. If one is found, it will add the associated category to the csv in a new column.

The program would already be operating at a runtime complexity of O(N) to run through each individual transaction from the bank statement (which may be lengthy), so the search for a match would need to be as efficient as possible as the list of known vendors/categories may also be quite extensive. The ADT will need to be able to insert nodes received from a large list of vendors/categories from a separate .csv which may or may not be sorted. Because of this, it would be ideal for the ADT to guarantee an efficient search runtime complexity independent of the order of the vendors/categories list. I believe the most efficient ADT for this data would be an AVL Tree, which would insert each vendor/category data entry into a self-balancing binary search tree to guarantee a worst-case runtime complexity of O(log N), regardless of the order in which entries are inserted.

I will create a class named VendorCategories which will have the following member methods:
## Data Structs 
### vendor_cat struct
- This struct contains the vendor name and category, both as a string as well as left and right pointers to its children
- Also will contain the height stored as an int to be used to find the balance factor of each node (to determine whether a rotation is necessary)
## Public Member Functions for user to interact with:
###	shared_ptr<vendor_cat> BuildAVL(string vendor_cat_filepath)
- This function will receive the filepath for a csv file with only two columns. Each row will contain the vendor and category 
-	The function will open the csv and for each row it will create a vendor_cat struct and insert it into the self-balancing AVL Tree
-	Will return a shared_ptr to the root of the AVL that is created
###	bool AssignCategories(string statement_filepath, shared_ptr<vendor_cat> root)
-	This function will receive the filepath of the bank statement (should be a csv in the format of a bank statement downloaded from Wells Fargo website) and iterate through each transaction, using the vendor name to search through the AVL Tree. If found, it will add an additional column to the bank statement csv with the corresponding category. If not found, it will not perform any operations for that row
-	Will return “True” if all transactions are iterated through without errors
-	Will return “False” if any of the following are encountered:
-- filepath is not in .csv format
--	filepath is non-existent
--	AVL Tree is empty
--	csv has fewer/more columns than expected
--	no transactions are matched with a vendor and no categories are added to the csv
###	bool RemoveCategories(string statement_filepath)
-	This function will remove all categories from a csv that has already had categories assigned. This will be important for unit testing, as it would be ideal for the same csv file to be reused, even after it has categories assigned
-	Will return “True” if categories have been removed (or if there were no categories to begin with)
-	Will return “False” if errors are encountered (e.g. filepath not csv or nonexistent)
###	void PrintAVL(shared_ptr<vendor_cat> root)
-	This function will print the AVL Tree for debugging
###	void PrintCSV(string filepath)
-	This function will print the csv file for debugging
## Private Member Functions Hidden From User:
###	bool AVLInsert(shared_ptr<vendor_cat> node)
-	This function will insert a vendor_cat node into the avl_tree private member variable following BST insert traversal and AVL self-balancing along the way. Will be used in the CreateAVL public function.
-	Will use the vendor_name string of vendor_cat node as the key during traversal
-	Will return “True” if node is successfully inserted
-	Will return “False” if errors are encountered 
###	shared_ptr<vendor_cat> AVLSearch(string vendor_name)
-	This function will search the AVL tree using bst search traversal using the vendor_name as the key
-	If a match is found the vendor_cat node is returned, else NULL is returned
###	void BalanceAVL(shared_ptr<vendor_cat> root)
-	This function will be used in the AVLInsert function to make sure the tree is balanced according to the AVL rules
Since the AVL will be populated from a csv file, I do not believe a remove function to be necessary.
I will create a series of tests to make sure the algorithm is working.
### Testing Criteria:
-	I will include two test files, a test bank statement csv and vendor/category csv
-	I will include a run_tests.cpp which will execute each private member function to make sure all functions are operating as they should
-	Will test for potential errors such as inserting a duplicate vendor_cat, searching/printing a null AVL,  calling BuildAVL or AssignCategories with invalid filepaths, etc.
-	Will also build an AVL from the vendor/category csv and assign categories to the statement csv. Will print the AVL contents after BuildAVL and print the statement csv before and after
-	Will remove categories after this test to leave the csv unchanged
-	The project will be done when all unit tests can be passed and a bank statement csv file can successfully be assigned with categories that correspond to matching vendors.

### References:
[1] Zybook chapters 7 and 8

[2] https://en.wikipedia.org/wiki/AVL_tree 
