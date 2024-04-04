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