### Alex Gonzalez and Ethan Haugen 

## ** High-level Design of Solution **

![alt text](https://github.com/SMUCS2341/assignment-4-search-engine-she-s-bulletproof/)

### ** User Interface **
The user interface class is responsible for printing and managing the menu for the user. Through the superSearch function,
the class prints out all possible options for the search engine. From this menu, an input of a character is taken in from
the user and used to determine the choice. The menu allows the user to create a new index from a directory, reload an index
from a file, clear indexes, query an index or quit. The functionality is placed in a loop to allow options to be selected
until exit is selected.

### ** Index Handler **
Index Handler is the majority of the work for the functionality of the engine. The index handler is responsible for creating
and managing all the indexes for the project. The handler is able to scan a document object's words, people, and organizations 
and add them to their appropiate indexes and add the instances accordingly. The handler starts by populating both hash maps
with UUIDs and titles, and then scanning the content to add to the index of words, organizations, and people. The handler also
manages the search function, a query object to manage different searches, and calculates results/relevancy. The search function 
then stores results and returns them in a list menu.

### ** Query **
The query object is the main assistance used in the search function to manage searching a certain word. The getQuery function 
asks the user to give a search term, then takes that term to determine if the query is for words, people, or organizations. The
function serves to hold lists of each index type with the words that the function will be searching, as well as if any words
should be excluded.

### ** DocParser **
The DocParser object is used primarily to read JSON files. The functionality takes in a JSON file and then creates a myDocument
object to hold all necessary information from the JSON file, and then returns it. Aside from using a lowercase function internally,
the DocParser serves mainly only to read in files and return a myDocument object populated with all necessary information.

### ** myDocument **
The myDocument class is used as an object for documents, used to hold all necessary information needed to properly index all words. 
The object is used when reading JSON files as a placeholder to hold all information for given UUID, before converting to indexes of
words that use the UUIDs as instances. 

### ** Key **
The key class is used as the object that the trees for the indexes will hold. Each key node holds it's name, which is a specific word,
and then a vector of strings which will hold all the UUIDs where the word is present. The class exists to be the node value type.


## ** Your Timeline to Finish the Project **
Weekly milestones/tasks. Set out a plan at the beginning and then record when you got it done.

| Task        | Planned completion | Actual completion | Time spent in hrs by X | Time spent in hrs by Y |
| ----------- | :-----------------:| :---------------: | :--------------------: | :--------------------: |
| UML         | Nov 5              | Nov 5             | .5                     | 0                      |
| myDocument  | Nov 14             | Nov 16            | 1.5                    | 0                      |
| key         | Nov 16             | Nov 20            | 1.5                    | 1.5                    |
| AVL Tree    | Nov 16             | Nov 16            | .5                     | 4                      |
| docParser   | Nov 23             | Nov 23            | 1                      | .5                     |
| indexHandler| Nov 30             | Dec 5 (editing)   | 5                      | 5                      |
| query       | Nov 30             | Dec 1             | 3.5                    | 4                      |
| UI          | Nov 30             | Dec 5             | 1.5                    | 1                      |
| document.md | Dec 3              | Dec 5             | 1                      | .5                     |


## Used Data Structures

### ** Avl Tree **
Avl tree is used as the structure to hold all the keys, each of which is a unique word. The tree sorts these
words and holds a vector of strings that has all the occurences by UUID. 

### ** Queue **
The queue data structure is used when writing a tree to file, in order to be able to traverse a tree by
breadth. The queue adds the children nodes for every level, allowing for the tree to be read in order,
so when the file is read again the tree requires minimal rebalancing. Without a queue, writing the tree
in order would be significantly more complicated. 

### ** Vector **
Vectors are used throughout the entire program, mainly whenever a list of strings of any kind needs to be
kept. It is used to hold lists of words such as queries, lists of UUIDs, people, organization, words, and
so on. It is one of the most used data structures in this program since it has many built in functions.
Another option which may have been quicker would be to use Linked Lists instead, however, it would be 
a more complicated inplementation. 

### ** Unordered Map **
Unordered maps are used as a hash table to match UUIDs to the article title. Since UUIDs and titles are
only available when a document is being read in, and the document object is not saved, the titles and
UUIDs are matched up in a hash table to be able to retrieve article titles when returning results. It
is also used for relevancy ranking, as the other hash map links UUID to a counter of how many times it 
is returned per UUID. 


Explanation of what data structures are used where. For each, state 
    - time and space complexity (Big-Oh),
    - why it is the appropriate data structure and what other data structure could have been used.

## User Documentation 
- How to use the software.
In order to run the program, you must run our main file to call supersearch, which will activate the UI.
When in UI, you must follow prompts to upload a directory or reload one and then you can query it. Follow
menu instructions to save indexes or exit supersearch.

- Some example queries with the results.





## Performance
- Statistics for indexing all documents and timing.



## Automatic Tests and Memory Tests
You need to describe test cases for:
- Tests for your AVL tree's function
AVL Tree tests is used to ensure that the tree is able to add, remove, balance, print, and so on. Various
CHECKs are used to ensure that all nodes were properly added. 

- Tests for your AVL tree for memory leaks (don't forget to test the persistence functions)
Ran valgrind on the tree tests to ensure no memory leaks.

- Tests for indexer
The index handler is tested for many different functions, such as being able to populate a directory, print
a given index. The handler is also tested for being able to reload indexes, write indexes, and access data. 

- Tests for the complete system
The main testing for this system on a large scale was performed by running the UI class and finding 
inconsistencies in expected results from actual results.

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
