# Assign Categories to Transactions Using an AVL Tree

### Project: Adding Budget Categories to Bank Statements Using an AVL Tree
### Name: Seth Ely
### Class and Semester: CSPB2270 , Spring 2022

To track my own personal spending, I use a budget with close to 30 categories. I then track each and every expenditure in a spreadsheet and assign categories to each transaction, allowing me to track the totals for each category and know how much I have left for each month. I find myself having to add similar transactions from duplicate vendors to the same category, and have often wanted to create a program to read my bank account statement (downloaded as a .csv) and assign each known vendor with its corresponding category. I have found that this cannot be done in Excel given that the transaction cell needs to be parsed using regular expressions to find a unique vendor key that is the same for each transaction and Excels regex functionality is not very robust.

The program would already be operating at a runtime complexity of O(N) to run through each individual transaction from the bank statement (which may be lengthy), so the search for a match would need to be as efficient as possible as the list of known vendors/categories may also be quite extensive. The ADT will need to be able to insert nodes received from a large list of vendors/categories from a separate .csv which may or may not be sorted. Because of this, it would be ideal for the ADT to guarantee an efficient search runtime complexity independent of the order of the vendors/categories list, especially since csv files are likely to be sorted. I have implemented a solution to this problem using an AVL Tree, which inserts each vendor/category data entry into a self-balancing binary search tree to guarantee a worst-case runtime complexity of O(log N), regardless of the order in which entries are inserted. Each node stores the key (vendor name), the category to be returned, left and right pointers and the height of the node. The height is important as it is used to determine the balance factor, or difference in left/right subtree heights, which will determine whether the node needs to be rebalanced or not.

## To Start the Application
After cloning the repository, run `cmake .. && make` Running `./run_app` from the build folder will  create a class with the given test files statement.csv and categories.csv, build an AVL tree out of the categories.csv file, and print the contents of the AVL tree in DOT Language to be used with Graphviz to the console (visit http://webgraphviz.com/ and copy and paste this text to generate the visual representation of the AVL tree). Afterwards, it will call the `AssignCategories` member function to read the statement.csv file, parse significant vendor information from the transaction column using regular expressions and search the AVL tree for a match. If a match is found, a new column with the category will be added to the statement.csv file. This file can be viewed after running `./run_app` to view it’s changed contents (original_statement.csv is included to view the file in its unchanged form contents before functions were called). The RemoveCategories function can be uncommented within main.cpp to reset the statement.csv file to its initial state by removing the added categories column.

Running `./run_tests` will show the status of the test cases I have developed to ensure proper functionality of the class. Included are tests for:

- Node construction
- Class Construction (including checks for GetStatementPath and GetCategoryPath)
- AVL Creation
- AssignCategories
- Check for AVL Invariants

### References used (but not copied):
[1] Zybook chapters 7 and 8

[2] https://en.wikipedia.org/wiki/AVL_tree

[3] https://www.geeksforgeeks.org/avl-tree-set-1-insertion/

[4] https://eli.thegreenplace.net/2009/11/23/visualizing-binary-trees-with-graphviz
