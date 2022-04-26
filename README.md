# Assign Categories to Transactions Using an AVL Tree

### Name: Seth Ely
### Class and Semester: CSPB2270 , Spring 2022
### Data Structure Implemented: AVL Tree

## To Start the Application
After cloning the repository, run `cmake .. && make` 
Running `./run_app` from the build folder will  create a class with the given test files statement.csv and categories.csv, build an AVL tree out of the categories.csv file, and print the contents of the AVL tree in DOT Language to be used with Graphviz to the console (visit http://webgraphviz.com/ and copy and paste this text to generate the visual representation of the AVL tree). Afterwards, it will call the `AssignCategories` member function to read the statement.csv file, parse significant vendor information from the transaction column using regular expressions and search the AVL tree for a match. If a match is found, a new column with the category will be added to the statement.csv file. This file can be viewed after running `./run_app` to view it’s changed contents (original_statement.csv is included to view the file in its unchanged form contents before functions were called). The RemoveCategories function can be uncommented within main.cpp to reset the statement.csv file to its initial state by removing the added categories column.

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
