#include <iostream>
#include <vector>

/*
    ==============
    === MEDIUM ===
    ==============

    ===============================
    725) Split Linked List in Parts
    ===============================

    ============
    Description:
    ============

    Given the head of a singly linked list and an integer k, split the linked
    list into k consecutive linked list parts.

    The length of each part should be as equal as possible: no two parts should
    have a size differing by more than one. This may lead to some parts being
    null.

    The parts should be in the order of occurrence in the input list, and parts
    occurring earlier should always have a size greater than or equal to parts
    occurring later.

    Return an array of the k parts.

    ====================================================================
    FUNCTION: vector<ListNode*> splitListToParts(ListNode* head, int k);
    ====================================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: head = [1,2,3], k = 5
    Output: [[1],[2],[3],[],[]]
    Explanation:
    The first element output[0] has output[0].val = 1, output[0].next = null.
    The last element output[4] is null, but its string representation as a
    ListNode is [].


    --- Example 2 ---
    Input: head = [1,2,3,4,5,6,7,8,9,10], k = 3
    Output: [[1,2,3,4],[5,6,7],[8,9,10]]
    Explanation:
    The input has been split into consecutive parts with size difference at
    most 1, and earlier parts are a larger size than the later parts.


    *** Constraints ***
    The number of nodes in the list is in the range [0, 1000].
    0 <= Node.val <= 1000
    1 <= k <= 50

*/

/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode() : val(0), next(nullptr) {}
 *     ListNode(int x) : val(x), next(nullptr) {}
 *     ListNode(int x, ListNode *next) : val(x), next(next) {}
 * };
 */

/* Time  Beats: 80.93% */
/* Space Beats: 36.36% */

/* Time  Complexity: O(n) */
/* Space Complexity: O(1) */
class Solution {
public:
    std::vector<ListNode*> splitListToParts(ListNode* head, int k)
    {
        std::vector<ListNode*> results;
        std::vector<int> next_part;

        int total = 0;
        ListNode* tmp = head;
        while (tmp)
        {
            total++;
            tmp = tmp->next;
        }

        make_equal_groups(total, k, next_part);

        tmp = head;
        for (int i = 0; i < k; i++)
        {
            results.push_back(tmp);

            int part = next_part[i];
            while (--part > 0)
                tmp = tmp->next;

            if (tmp)
            {
                ListNode* next = tmp->next;
                tmp->next = nullptr;

                tmp = next;
            }
        }

        return results;
    }

private:
    void make_equal_groups(int total, int k, std::vector<int>& next_part)
    {
        while (k != 0)
        {
            double part = total == 0 ? 0 : std::ceil(1.0*total / k);

            next_part.push_back(static_cast<int>(part));

            total -= total == 0 ? 0 : static_cast<int>(part);
            k--;
        }
    }
};




/* Time  Beats: 80.93% */
/* Space Beats: 36.36% */

/* Time  Complexity: O(n) */
/* Space Complexity: O(n) */
class Solution_2 {
public:
    std::vector<ListNode*> splitListToParts(ListNode* head, int k)
    {
        int length = 0;
        ListNode* current = head;
        std::vector<ListNode*> parts;

        while (current)
        {
            length++;
            current = current->next;
        }

        int base_size = length / k;
        int extra = length % k;
        current = head;

        for (int i = 0; i < k; ++i)
        {
            int part_size = base_size + (extra > 0);
            ListNode* part_head = nullptr, * part_tail = nullptr;

            for (int j = 0; j < part_size; ++j)
            {
                if (!part_head)
                    part_head = part_tail = current;
                else
                {
                    part_tail->next = current;
                    part_tail = part_tail->next;
                }

                if (current)
                    current = current->next;
            }

            if (part_tail)
                part_tail->next = nullptr;

            parts.push_back(part_head);
            extra = max(extra - 1, 0);
        }

        return parts;
    }
};
