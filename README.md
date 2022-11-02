# Assignment 4: Search Engine 

This is a longer group project! Here are the [Project Instructions](Project_Instructions.pdf).


**Objectives:**

* Work in a team using version control.
* Design a larger system, plan the implementation and submit multiple deliverables.
* Implement a search tree-based map.
* Implement a persistent data structure.


## Timeline 

You have about four weeks to complete the assignment. Start right away! **The lab TA will expect that you already have most of that week's work completed. Come with prepared questions and
be prepared to answer the TA's questions about your code.**

Suggested timeline (see Canvas for early deliverables):

* Week 1: Plan your timeline (see below); design you solution (first UML class diagram); 
    adapt the AVL tree from class to work as a map suitable for the inverted file index and provide tests (Catch2 test would be great).
* Week 2: Implement the document parser; build the indices. 
* Week 3: Implement the query processor; user interface; and add persistence to the index.
* Week 4: Finish code and write the documentation file.

# Submission 

In addition to the code, you need to submit a markdown document called `documentation.md` containing the following information (You can copy and paste the section structure below):

## High-level Design of Solution

- UML class diagram, etc.
- High-level pseudo code for each component.

## Your Timeline to Finish the Project
Weekly milestones/tasks. Set out a plan at the beginning and then record when you got it done.

| Task        | Planned completion | Actual completion | Time spent in hrs by X | Time spent in hrs by Y |
| ----------- | :-----------------:| :---------------: | :--------------------: | :--------------------: |
| x           | Nov 3              | Nov 6             | 8.5                    | 0                      |


## Used Data Structures
Explanation of what data structures are used where. For each, state 
    - time and space complexity (Big-Oh),
    - why it is the appropriate data structure and what other data structure could have been used.

## User Documentation 
- How to use the software.
- Some example queries with the results.

## Performance
- Statistics for indexing all documents and timing.

## Automatic Tests and Memory Tests
You need to describe test cases for:
- Tests for your AVL tree's function
- Tests for your AVL tree for memory leaks (don't forget to test the persistence functions)
- Tests for indexer
- Tests for the complete system

## Grading Rubric

| Task                        | Points Possible | Points Awarded |
| :------------------         | --------------: | -------------: |
| UML diagram/design          | 10              |                |
| AVL tree map + tests        | 20              |                |
| AVL tree persistence + tests| 10              |                |
| Document parser             | 10              |                |
| Query processor + interface | 20              |                |
| Proper Memory Management    | 5               |                |
| Formatting, Comments, etc.  | 5               |                |
| Documentation               | 20              |                |
| 48hr early submission bonus | +5              |                |

