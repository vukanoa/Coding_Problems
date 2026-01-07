/*
    ============
    === EASY ===
    ============

    ===========================
    706) Design HashMap
    ===========================

    ============
    Description:
    ============

    Design a HashMap without using any built-in hash table libraries.

    Implement the MyHashMap class:

        - MyHashMap() initializes the object with an empty map.

        - void put(int key, int value) inserts a (key, value) pair into the
          HashMap. If the key already exists in the map, update the
          corresponding value.

        - int get(int key) returns the value to which the specified key is
          mapped, or if this map contains no mapping for the key.

        - void remove(key) removes the key and its corresponding value if the
          map contains the mapping for the key.


    ===============================
    class MyHashMap {
    public:
        MyHashMap() {

        }

        void put(int key, int value) {

        }

        int get(int key) {

        }

        void remove(int key) {

        }
    };
    ===============================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input
    ["MyHashMap", "put", "put", "get", "get", "put", "get", "remove", "get"]
    [[], [1, 1], [2, 2], [1], [3], [2, 1], [2], [2], [2]]
    Output
    [null, null, null, 1, -1, null, 1, null, -1]

    Explanation
    MyHashMap myHashMap = new MyHashMap();
    myHashMap.put(1, 1); // The map is now [[1,1]]
    myHashMap.put(2, 2); // The map is now [[1,1], [2,2]]
    myHashMap.get(1);    // return 1, The map is now [[1,1], [2,2]]
    myHashMap.get(3);    // return -1 (i.e., not found), The map is now [[1,1], [2,2]]
    myHashMap.put(2, 1); // The map is now [[1,1], [2,1]] (i.e., update the existing value)
    myHashMap.get(2);    // return 1, The map is now [[1,1], [2,1]]
    myHashMap.remove(2); // remove the mapping for 2, The map is now [[1,1]]
    myHashMap.get(2);    // return -1 (i.e., not found), The map is now [[1,1]]

    *** Constraints ***
    0 <= key, value <= 10^6
    At most 104 calls will be made to put, get, and remove.

*/

#include <cstring>
#include <vector>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    Self-explanatory.

*/

/* Time  Beats: 50.11% */
/* Space Beats: 23.47% */

/* Time  Complexity: O(1) */
/* Space Complexity: O(n) */
class MyHashMap {
private:
    static constexpr int SIZE = 1e6 + 1;
    int hash_map[SIZE]; // On the Stack

public:
    MyHashMap()
    {
        memset(hash_map, 0xff, sizeof(hash_map));
    }

    void put(int key, int value)
    {
        hash_map[key] = value;
    }

    int get(int key)
    {
        if (hash_map[key] != -1)
            return hash_map[key];

        return -1;
    }

    void remove(int key)
    {
        hash_map[key] = -1;
    }
};




/*
    ------------
    --- IDEA ---
    ------------

    "Separate Chaining" implementation.

*/

/* Time  Beats: 95.34% */
/* Space Beats: 70.32% */

/* Time  Complexity: O(1) Avg and O(N) worst */
/* Space Complexity: O(N)                    */
class MyHashMap_Separate_Chaining {
private:
    struct ListNode
    {
        int key;
        int value;
        ListNode* next;

        ListNode(int key = -1, int value = -1, ListNode* next = nullptr)
            : key(key), value(value), next(next)
        {
        }
    };

    vector<ListNode*> buckets;

public:
    MyHashMap_Separate_Chaining()
    {
        buckets.resize(1000);

        for (ListNode*& bucket : buckets)
        {
            // Dummy head to simplify insert/remove logic
            bucket = new ListNode();
        }
    }

    // O(1) Average, O(N) worst
    void put(int key, int value)
    {
        ListNode* curr_node = buckets[hash_of(key)];

        while (curr_node->next)
        {
            if (curr_node->next->key == key)
            {
                curr_node->next->value = value;
                return;
            }

            curr_node = curr_node->next;
        }

        curr_node->next = new ListNode(key, value);
    }

    // O(1) Average, O(N) worst
    int get(int key)
    {
        ListNode* curr_node = buckets[hash_of(key)]->next;

        while (curr_node)
        {
            if (curr_node->key == key)
                return curr_node->value;

            curr_node = curr_node->next;
        }

        return -1;
    }

    // O(1) Average, O(N) worst
    void remove(int key)
    {
        ListNode* curr_node = buckets[hash_of(key)];

        while (curr_node->next)
        {
            if (curr_node->next->key == key)
            {
                ListNode* node_to_delete = curr_node->next;
                curr_node->next = curr_node->next->next;
                delete node_to_delete;
                return;
            }

            curr_node = curr_node->next;
        }
    }

private:
    int hash_of(int key)
    {
        return key % buckets.size();
    }
};
