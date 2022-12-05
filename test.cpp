#define CATCH_CONFIG_MAIN
#include "catch2/catch.hpp"
#include "AVL_TREE.h"
#include "key.h"
#include "indexHandler.h"
#include <string>
#include "userInterface.h"

using namespace std;

TEST_CASE("Check that AVL tree works"){

    SECTION("Regular functions"){
        AvlTree<int> tree;
        tree.insert(10);
        tree.insert(20);
        tree.insert(30);
        tree.insert(40);
        tree.insert(50);
        tree.prettyPrintTree();
        CHECK(tree.isEmpty() == false);
        CHECK(tree.contains(10) == true);
        CHECK(tree.contains(5) == false);
        CHECK(tree.find(20) == 20);
        tree.~AvlTree();
    }

    SECTION("Using Keys"){
        AvlTree<key> tree;
        key alex = key("Alex");
        key ethan = key("Ethan");
        key kyle = key("Kyle");
        key miles = key("Miles Youngblood");
        CHECK(tree.getRoot() == nullptr);
        tree.insert(ethan);
        tree.insert(alex);
        tree.insert(kyle);
        tree.insert(miles);
        tree.prettyPrintTree();
        CHECK(tree.isEmpty() == false);
        //CHECK(tree.contains(alex) == true);
        //CHECK(tree.contains("Mile") == false);
        //CHECK(tree.find("") == 20);
        tree.~AvlTree();
    }

    SECTION("Index Handler"){
        indexHandler index;
        index.populate("sample_data");
        index.printOrgs();
        index.printInfo();
        index.printPeeps();
        index.checkKey("reuters");
    }

    SECTION("Check Persistence"){
       indexHandler handy;
       handy.populate("sample_data");
       handy.search();
       handy.storeTree(handy.getWords(), "testwordtree.txt");
       CHECK(!handy.getWords().isEmpty());
       handy.storeMaps(handy.getHashMap(), handy.getCountMap(), handy.getUUIDs(), "testTitleMap.txt", "testCountMap.txt");
       handy.clear();
       CHECK(handy.getWords().isEmpty());
       handy.wordreloadTree("testwordtree.txt");
       handy.reloadMaps("testTitleMap.txt", "testCountMap.txt");
       CHECK(!handy.getWords().isEmpty());
       CHECK(!handy.getHashMap().empty());
    }

}