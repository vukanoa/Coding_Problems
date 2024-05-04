#include <iostream>
#include <vector>

/*
    ==============
    === MEDIUM ===
    ==============

    ============================
    382) Linked List Random Node
    ============================

    ============
    Description:
    ============

    Given a singly linked list, return a random node's value from the linked
    list. Each node must have the same probability of being chosen.

    Implement the Solution class:

        Solution(ListNode head) Initializes the object with the head of the
        singly-linked list head. int getRandom() Chooses a node randomly from
        the list and returns its value. All the nodes of the list should be
        equally likely to be chosen.


    ---------------
    -- Follow Up --
    ---------------

    What if the linked list is extremely large and its length is unknown to
    you? Could you solve this efficiently without using extra space?


    ===============================
    CLASS:
    class Solution {
    public:
        Solution(ListNode* head)
        {

        }

        int getRandom()
        {

        }
    };
    ===============================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input
    ["Solution", "getRandom", "getRandom", "getRandom", "getRandom", "getRandom"]
    [[[1, 2, 3]], [], [], [], [], []]
    Output
    [null, 1, 3, 2, 2, 3]

    Explanation
    Solution solution = new Solution([1, 2, 3]);
    solution.getRandom(); // return 1
    solution.getRandom(); // return 3
    solution.getRandom(); // return 2
    solution.getRandom(); // return 2
    solution.getRandom(); // return 3
    // getRandom() should return either 1, 2, or 3 randomly. Each element
    // should have equal probability of returning.


    *** Constraints ***
    The number of nodes in the linked list will be in the range [1, 10^4].
    -10^4 <= Node.val <= 10^4
    At most 10^4 calls will be made to getRandom.

*/

/*
    ------------
    --- IDEA ---
    ------------

    Iterate through entire Linked List and put its value in a vector called
    "node_values".

    Once we have all the values stores inside that vector, now we can use a
    rand() function and mod it with the size of the vector. That way, we're
    guaranteed to have the same probability of choosing any node.

    At the end return node_values[random];

*/

/* Time  Beats: 56.42% */
/* Space Beats: 11.17% */

/* Time  Complexity: O(n) */
/* Space Complexity: O(n) */
class Solution {
public:
    Solution(ListNode* head) : beginning(head)
    {
        node_values = vectorify_linked_list(head);
    }

    int getRandom()
    {
        int random = std::rand() % node_values.size();

        return node_values[random];
    }

private:
    std::vector<int> vectorify_linked_list(ListNode* head)
    {
        std::vector<int> vec;

        while (head)
        {
            vec.push_back(head->val);
            head = head->next;
        }

        return vec;
    }

    ListNode* beginning;
    std::vector<int> node_values;
};

/**
 * Your Solution object will be instantiated and called as such:
 * Solution* obj = new Solution(head);
 * int param_1 = obj->getRandom();
 */




/*
    ------------
    --- IDEA ---
    ------------

    Instead of making a vector out of every node, we can just iterate through
    entire Linked List to find out the number of nodes.

    Once we have that, we can again use a rand() function now we mod it with
    variable "size" instead of node_values.size().

    But what is the difference?

    The difference is that now once we know the size and once we've correctly
    picked the i-th node, then we can just iterate "random" number of times
    through the original Linked List and return its value.

    That way we don't use extra space as before.

*/

/* Time  Beats: 93.26% */
/* Space Beats: 57.53% */

/* Time  Complexity: O(n) */
/* Space Complexity: O(1) */
class Solution_Follow_Up {
public:
    Solution(ListNode* head) : beginning(head)
    {
        size = get_size(head);
    }

    int getRandom()
    {
        int random = std::rand() % size;

        ListNode* curr = beginning;
        while(random > 0)
        {
            random--;
            curr = curr->next;
        }

        return curr->val;
    }

private:
    int get_size(ListNode* head)
    {
        int n = 0;

        while (head)
        {
            n++;
            head = head->next;
        }

        return n;
    }

    ListNode* beginning;
    int size;
};
