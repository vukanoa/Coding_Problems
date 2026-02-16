/*
    ============
    === HARD ===
    ============

    ===========================
    460) LFU Cache
    ===========================

    ============
    Description:
    ============

    Design and implement a data structure for a Least Frequently Used (LFU)
    cache.

    Implement the LFUCache class:

        + LFUCache(int capacity) Initializes the object with the capacity of
          the data structure.

        + int get(int key) Gets the value of the key if the key exists in the
          cache. Otherwise, returns -1.

        + void put(int key, int value) Update the value of the key if present,
          or inserts the key if not already present. When the cache reaches its
          capacity, it should invalidate and remove the least frequently used
          key before inserting a new item. For this problem, when there is a
          tie (i.e., two or more keys with the same frequency), the least
          recently used key would be invalidated.

    To determine the least frequently used key, a use counter is maintained for
    each key in the cache. The key with the smallest use counter is the least
    frequently used key.

    When a key is first inserted into the cache, its use counter is set to 1
    (due to the put operation). The use counter for a key in the cache is
    incremented either a get or put operation is called on it.

    The functions get and put must each run in O(1) average time complexity.

    ===============================
    CLASS:

    class LFUCache {
    public:
        LFUCache(int capacity) {

        }

        int get(int key) {

        }

        void put(int key, int value) {

        }
    };
    ===============================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input
    ["LFUCache", "put", "put", "get", "put", "get", "get", "put", "get", "get", "get"]
    [[2], [1, 1], [2, 2], [1], [3, 3], [2], [3], [4, 4], [1], [3], [4]]
    Output
    [null, null, null, 1, null, -1, 3, null, -1, 3, 4]

    Explanation
    // cnt(x) = the use counter for key x
    // cache=[] will show the last used order for tiebreakers (leftmost element is  most recent)
    LFUCache lfu = new LFUCache(2);
    lfu.put(1, 1);   // cache=[1,_], cnt(1)=1
    lfu.put(2, 2);   // cache=[2,1], cnt(2)=1, cnt(1)=1
    lfu.get(1);      // return 1
                     // cache=[1,2], cnt(2)=1, cnt(1)=2
    lfu.put(3, 3);   // 2 is the LFU key because cnt(2)=1 is the smallest, invalidate 2.
                     // cache=[3,1], cnt(3)=1, cnt(1)=2
    lfu.get(2);      // return -1 (not found)
    lfu.get(3);      // return 3
                     // cache=[3,1], cnt(3)=2, cnt(1)=2
    lfu.put(4, 4);   // Both 1 and 3 have the same cnt, but 1 is LRU, invalidate 1.
                     // cache=[4,3], cnt(4)=1, cnt(3)=2
    lfu.get(1);      // return -1 (not found)
    lfu.get(3);      // return 3
                     // cache=[3,4], cnt(4)=1, cnt(3)=3
    lfu.get(4);      // return 4
                     // cache=[4,3], cnt(4)=2, cnt(3)=3


    *** Constraints ***
    1 <= capacity <= 10^4
    0 <= key <= 10^5
    0 <= value <= 10^9
    At most 2 * 105 calls will be made to get and put.

*/

#include <unordered_map>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    TODO
    (You need to be VERY careful when implementing the Solution for this one)

*/

/* Time  Beats: 77.60% */
/* Space Beats: 77.07% */

/* Time  Complexity: O(1) */
/* Space Complexity: O(N) */
struct Node {
    int key;
    int value;
    int used_count;

    Node* prev;
    Node* next;

    Node(int key, int value, int used_count)
        : key(key), value(value), used_count(used_count), prev(nullptr), next(nullptr)
    {}
};

class LFUCache {
public:
    LFUCache(int capacity)
        : capacity(capacity), lfu_freq(0)
    {}
    
    // O(1)
    int get(int key)
    {
        /* If the key does NOT exist */
        if (umap_key_to_node.find(key) == umap_key_to_node.end())
            return -1;

        Node* node = umap_key_to_node[key];

        yank_from_linked_list_for_curr_freq(node); // Yank
        node->used_count++;                        // Because we "touched it"
        insert_in_linked_list_for_curr_freq(node); // Insert

        return node->value;
    }
    
    // O(1)
    void put(int key, int value)
    {
        /* If the key does NOT exist */
        if (umap_key_to_node.find(key) == umap_key_to_node.end())
        {
            Node* new_node = new Node(key, value, 1); // Create "new_node"

            umap_key_to_node.insert( {key, new_node} );

            if (umap_key_to_node.size() > capacity)
                remove_LFU_node();

            insert_in_linked_list_for_curr_freq(new_node); // Insert
            /*
                Newly inserted node will ALWAYS have the LEAST frequent
                "used_count", that's why we must reset "lfu_freq" to 1.
            */
            lfu_freq = 1;
        }
        else // The key DOES exist
        {
            Node* node = umap_key_to_node[key];

            yank_from_linked_list_for_curr_freq(node); // Yank

            node->value = value; // Update value
            node->used_count++;  // Because we've updated its value

            insert_in_linked_list_for_curr_freq(node); // Insert
        }
    }

private:
    int capacity;
    int lfu_freq; // Least FREQUENTLY used among all of the nodes

    unordered_map<int, Node*> umap_key_to_node;
    unordered_map<int, pair<Node*, Node*>> umap_freq_to_linked_list;

    void yank_from_linked_list_for_curr_freq(Node* node)
    {
        int curr_freq = node->used_count;

        auto& [dummy_head, dummy_tail] = umap_freq_to_linked_list[curr_freq];

        /* Re-link AROUND the current "node" */
        Node* prev_node = node->prev;
        Node* next_node = node->next;

        node->next->prev = prev_node;
        node->prev->next = next_node;

        /* If the list is EMPTY -- Free Memory */
        if (dummy_head->next == dummy_tail)
        {
            delete dummy_head;
            delete dummy_tail;

            umap_freq_to_linked_list.erase(curr_freq);

            if (curr_freq == lfu_freq)
                lfu_freq++;
        }

        /* Unlink current "node", i.e. "Yank" current "node" from the list */
        node->prev = nullptr;
        node->next = nullptr;
    }

    void insert_in_linked_list_for_curr_freq(Node* node)
    {
        int curr_freq = node->used_count;

        /* If Linked List does NOT exist for "curr_freq" -- Create one */
        if (umap_freq_to_linked_list.find(curr_freq) == umap_freq_to_linked_list.end())
        {
            /* Create dummies */
            Node* dummy_head = new Node(-1, -1, -1);
            Node* dummy_tail = new Node(-1, -1, -1);

            /* Link dummies */
            dummy_head->next = dummy_tail;
            dummy_tail->prev = dummy_head;

            /* Insert in HashMap */
            umap_freq_to_linked_list[curr_freq] = {dummy_head, dummy_tail};
        }

        auto& [dummy_head, dummy_tail] = umap_freq_to_linked_list[curr_freq];

        /* Insert current "node" as the MRU node */
        node->prev = dummy_tail->prev;
        node->next = dummy_tail;

        dummy_tail->prev->next = node;
        dummy_tail->prev       = node;
    }

    void remove_LFU_node()
    {
        auto& [dummy_head, dummy_tail] = umap_freq_to_linked_list[lfu_freq];

        Node* LFU_node = dummy_head->next;

        /* Re-link AROUND the "LFU_node" */
        LFU_node->prev->next = LFU_node->next;
        LFU_node->next->prev = LFU_node->prev;

        if (dummy_head->next == dummy_tail) // If the List is EMPTY
        {
            delete dummy_head;
            delete dummy_tail;

            umap_freq_to_linked_list.erase(lfu_freq);
        }

        /* Remove from HashMap */
        umap_key_to_node.erase(LFU_node->key);

        /* Free Memory */
        LFU_node->prev = nullptr;
        LFU_node->next = nullptr;
        delete LFU_node;
    }
};

/**
 * Your LFUCache object will be instantiated and called as such:
 * LFUCache* obj = new LFUCache(capacity);
 * int param_1 = obj->get(key);
 * obj->put(key,value);
 */
