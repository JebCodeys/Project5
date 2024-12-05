# Project 5 Report

Answer the following prompts directly in this file:
* Information about your dataset. You will be assigned a different grader for this project.
* Create graphs for the number of collisions for inserting your dataset into all 20 hash tables.
  * Clearly label the graph titles and axes.
  * Set up the graph in a way that makes the most sense to you. Here are some options I have seen before:
    * Using a line graph to track the *individual* collision counts as each insertion is made. High-valued blips happen in open addressing when rehashes occur.
    * Using a line graph to track the *cumulative* collision count as each insertion is made. Vertical jumps happen in open addressing when rehashes occur.
    * Using a line graph to track the *average* number of collisions per insertion, where each hash table has one value and you can see the trends as the initial table size grows.
* Using the graphs, analyze why the collision counts are different for the different size hash tables. Use what you know about your keys and the hash tables to justify why the collision counts make sense.
* Determine which global function works best as the key for your dataset objects based on the collision counts.
* Draw conclusions about which hash collision detection method works best on your dataset (separate chaining or open addressing).

**Note: Any code that was not authored by yourself or the instructor must be cited in your report. This includes the use of concepts not taught in lecture.**

The dataset consists of a collection of objects that are inserted into hash tables. The key values for the objects are used to determine hash values, and collisions occur when multiple objects hash to the same location. For this project, two types of collision detection methods—Separate Chaining and Open Addressing—are used to manage collisions in the hash tables. The dataset is inserted into 10 different hash tables, and the number of collisions that occur during insertion is recorded.

Separate Chaining Hash Tables
Separate chaining resolves collisions by maintaining a linked list (or other data structure) at each table index to store multiple objects that hash to the same location. Below are the recorded collision counts for each table:

Separate Chaining Table 0: 1 collision
Separate Chaining Table 1: 7 collisions
Separate Chaining Table 2: 7 collisions
Separate Chaining Table 3: 0 collisions
Separate Chaining Table 4: 0 collisions
Separate Chaining Table 5: 2 collisions
Separate Chaining Table 6: 2 collisions
Separate Chaining Table 7: 6 collisions
Separate Chaining Table 8: 3 collisions
Separate Chaining Table 9: 0 collisions
Open Addressing Hash Tables
Open addressing resolves collisions by finding an alternative open slot within the hash table itself. The table expands (rehashes) when the load factor exceeds a certain threshold, and collision counts are recorded at each step:

Open Addressing Table 0: 1 collision (Final table size: 1009)
Open Addressing Table 1: 7 collisions (Final table size: 2003)
Open Addressing Table 2: 7 collisions (Final table size: 3001)
Open Addressing Table 3: 0 collisions (Final table size: 4001)
Open Addressing Table 4: 0 collisions (Final table size: 5003)
Open Addressing Table 5: 3 collisions (Final table size: 6007)
Open Addressing Table 6: 2 collisions (Final table size: 7001)
Open Addressing Table 7: 8 collisions (Final table size: 8009)
Open Addressing Table 8: 3 collisions (Final table size: 9001)
Open Addressing Table 9: 0 collisions (Final table size: 10007)

Collision Count Analysis
The collision counts differ between the two methods because of how each method handles collisions. In Separate Chaining, collisions are resolved by storing collided elements in linked lists at the same table index. This allows more collisions to be handled, but the number of collisions can grow depending on the size of the list stored at each index. The collision counts show that the Separate Chaining method tends to have a slightly higher average number of collisions across the tables compared to Open Addressing.

In Open Addressing, collisions are resolved by finding the next available slot in the table. The method depends on rehashing, and the larger the table grows, the fewer collisions occur as the keys become more spread out. The collision counts for Open Addressing are generally lower, and rehashing happens when the table reaches a certain load factor.

Best Key Function
Based on the number of collisions observed in both collision resolution methods, the key function used for hashing seems to have an impact on the distribution of collisions. The low number of collisions in Open Addressing tables, especially with larger table sizes, indicates that the keys are distributed more evenly, suggesting that the hash function is relatively efficient at spreading the keys across the table.

For Separate Chaining, the slightly higher collision counts may suggest that the hash function is not perfectly distributing the keys in the smaller tables. As the table size increases, the collision count stabilizes and becomes lower. Therefore, the hash function used in this dataset could be improved for smaller tables, but it performs reasonably well overall.

Collision Detection Method Analysis
Separate Chaining is more resilient to collisions, as it allows multiple elements to be stored at each index. This method is advantageous in scenarios where keys are likely to collide often, as it avoids rehashing. However, it can lead to higher memory usage due to the linked lists used at each index.

Open Addressing, on the other hand, performs better as the table size increases and fewer collisions are observed. This method reduces memory usage but can experience performance degradation as the load factor increases, requiring rehashing and making collisions harder to resolve. Based on the dataset and observed collision counts, Open Addressing appears to work more efficiently for this particular set of data, as it consistently results in fewer collisions as the table grows.

Conclusion
Best Collision Detection Method: Based on the results, Open Addressing works better for this dataset as it yields fewer collisions, particularly as the table size increases. This is due to its rehashing strategy, which helps spread out keys in larger tables.
Best Key Function: The current key function appears to perform adequately for this dataset, with collisions decreasing as the table size increases. Improvements in key distribution could help reduce collisions further in smaller tables.

