#include <iostream>
#include <vector>

/*
    ============
    === EASY ===
    ============

    ===========================
    705) Design HashSet
    ===========================

    ============
    Description:
    ============

    Design a HashSet without using any built-in hash table libraries.

    Implement MyHashSet class:

        void add(key) Inserts the value key into the HashSet.

        bool contains(key) Returns whether the value key exists in the HashSet
        or not.

        void remove(key) Removes the value key in the HashSet. If key does not
        exist in the HashSet, do nothing.

    ===============================
    CLASS:
    class MyHashSet {
    public:
        MyHashSet() {

        }

        void add(int key) {

        }

        void remove(int key) {

        }

        bool contains(int key) {

        }
    };
    ===============================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input
    ["MyHashSet", "add", "add", "contains", "contains", "add", "contains",
     "remove", "contains"]
    [[], [1], [2], [1], [3], [2], [2], [2], [2]]
    Output
    [null, null, null, true, false, null, true, null, false]

    Explanation
    MyHashSet myHashSet = new MyHashSet();
    myHashSet.add(1);      // set = [1]
    myHashSet.add(2);      // set = [1, 2]
    myHashSet.contains(1); // return True
    myHashSet.contains(3); // return False, (not found)
    myHashSet.add(2);      // set = [1, 2]
    myHashSet.contains(2); // return True
    myHashSet.remove(2);   // set = [1]
    myHashSet.contains(2); // return False, (already removed)


    *** Constraints ***
    0 <= key <= 10^6
    At most 10%4 calls will be made to add, remove, and contains.

*/

/* Time  Beats: 88.05% */
/* Space Beats: 43.44% */

/* Time  Complexity: O(1) */
/* Space Complexity: O(n) */
class MyHashSet {
public:
    MyHashSet()
    {
        hash_set = std::vector<bool>(1000001, false);
    }

    void add(int key)
    {
        hash_set[key] = true;
    }

    void remove(int key)
    {
        hash_set[key] = false;
    }

    bool contains(int key)
    {
        return hash_set[key] == true;
    }

private:
    std::vector<bool> hash_set;
};

/**
 * Your MyHashSet object will be instantiated and called as such:
 * MyHashSet* obj = new MyHashSet();
 * obj->add(key);
 * obj->remove(key);
 * bool param_3 = obj->contains(key);
 */
