# CS 124 Project 5

For this project, you will hash the 1000+ objects from your data set. You will experiment to see what size hash table, collision detection method, and key work best for your data.

## Implement

### Setup
You will want to start at the end of Project 1. You should have a vector of 1000+ objects in your main function.
* You must use Separate Chaining.
* You must also choose any of the following open addressing methods (I recommend that you rename the LinearProbing class and modify it according to the method you chose):
  * Quadratic Probing
  * Exponential Probing
  * Double Hashing
  
  Hint: You should modify all three methods of the class (insert, find, and remove).

### Separate Chaining Class
Modify the insert method to count the number of reads of the hashed object.
* A read in this class is when you look at an item from the linked list, which appears as `*it` in the code.
  * Hint: the reads are not actually in the insert method, but in a method called from insert.

### Open Addressing Class
Modify the insert method to count the number of reads of the hashed object.
* A read in this class is when you look at one of the template objects from the table, which appears as `table[index].item` in the code.
  * Hint: the reads are not actually in the insert method, but in a method called from insert.

### Main File
You must create **two** different global functions in your main.cpp file that will be used as your getKey function in the hash tables.
* If you use the hornerHash algorithm from class, make sure your global functions take in an object of your class and return a unique string.
  * If you only have one unique field in your class, make each global function concatenate the unique field with another field.
* If you prefer, you can use a different hash function besides hornerHash. Make sure your keys are still unique for each object.

Create 10 separate-chaining hash table objects and 10 open addressing hash table objects of your custom data type.
* Half of the tables will use your first getKey function, half will use your second getKey function.
* You should use varying initial sizes for each of the five hash tables that use the same collision detection method and getKey function. 
  * The sizes should range from just bigger than the size of your data set to more than twice the size of your dataset, with at least two sizes being more than twice the size of your dataset.
  * Note that the hash table constructors will go to the next prime given the table size passed in, so you don't have to pass prime numbers to the constructors and your table sizes will always be prime.
* Using a single loop, insert all 1000+ objects into each of the 20 hash tables.
* For each object inserted in each of the 20 tables, record the number of hashed objects that were read. You should write this data out to file(s).
* For open addressing, print (cout) the size of the table after inserting all of 1000+  objects (because the table size may have changed in a rehash). You will need this info for the report.

## Extra Credit
For up to 10 points extra credit (at the grader’s discretion), you can:
* Use timers to see how long it takes you to insert/find elements in the hash tables.
* Use multiple types of open addressing and compare/analyze their read counts.
* Compare the runtimes with the time it takes to insert/find elements stored in other data structures (e.g. an unsorted vector, a sorted vector, a binary search tree, an AVL tree, a splay tree, a heap, etc.) The more structures you include, the better!

If you choose the extra credit option, clearly label the results and analysis in this section of your README.md file.

## Report
Include the following in this section of your README.md file:
* Information about your data set. You will be assigned a different grader for this project.
* Create graphs for the number of reads for inserting your dataset into all 20 hash tables.
  * Clearly label the graph titles and axes.
  * Set up the graph in a way that makes the most sense to you. Here are some options I have seen before:
    * Using a line graph to track the *individual* read counts as each insertion is made. High-valued blips happen in open addressing when rehashes occur.
    * Using a line graph to track the *cumulative* read count as each insertion is made. Vertical jumps happen in open addressing when rehashes occur.
    * Using a line graph to track the *average* number of reads per insertion, where each hash table has one value and you can see the trends as the initial table size grows.
* Using the graphs, analyze why the read counts are different for the different size hash tables. Use what you know about your keys and the hash tables to justify why the read counts make sense.
* Determine which getKey function works best on your dataset based on the read counts.
* Draw conclusions about which hash collision detection method works best on your dataset (separate chaining or open addressing).

**Note: Any code that was not authored by yourself or the instructor must be cited in your report. This includes the use of concepts not taught in lecture.**

## Submit
You must include your source (all .cpp and .h) files, your data (.csv) file(s), your output file(s), CMakeLists.txt, and your updated README.md file that contains your report to your repository. Submit to Gradescope using the GitHub repository link, double-check that all the correct files are there, and wait for the autograder to provide feedback.

## Grading
The project is out of 70 points.

| Points Possible | Description of requirement                                                    |
|------------------- |-------------------------------------------------------------------------------|
| 5 pts | Program compiles and runs.                                                    |
| 5 pts | Code style. Readable, naming style is consistent, comments where appropriate. |
| 5 pts | Hashed at least 1000 objects using separate chaining.                         |
| 15 pts | Hashed at least 1000 objects using open addressing.                           |
| 5 pts | Used at least 5 different hash table sizes, as specified above.               |
| 5 pts | Used two getKey functions, as specified above.                                |
| 10 pts | Recorded the number of reads for each type of hashing.                        |
| 15 pts | Analyzed the results and wrote about everything outlined above.               |
| 5 pts | Report: professional, grammatically correct, cites sources.                   |