#include <iostream>
#include <vector>

/*
    ==============
    === MEDIUM ===
    ==============

    =================================
    341) Flatten Nested List Iterator
    =================================

    ============
    Description:
    ============

    You are given a nested list of integers nestedList. Each element is either
    an integer or a list whose elements may also be integers or other lists.
    Implement an iterator to flatten it.

    Implement the NestedIterator class:

        + NestedIterator(List<NestedInteger> nestedList) Initializes the
          iterator with the nested list nestedList.

        + int next() Returns the next integer in the nested list.

        + boolean hasNext() Returns true if there are still some integers in
          the nested list and false otherwise.

    Your code will be tested with the following pseudocode:

    initialize iterator with nestedList
    res = []
    while iterator.hasNext()
        append iterator.next() to the end of res
    return res

    If res matches the expected flattened list, then your code will be judged
    as correct.

    ===============================
    class NestedIterator {
    public:
        NestedIterator(vector<NestedInteger> &nestedList) {

        }

        int next() {

        }

        bool hasNext() {

        }
    };
    ===============================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: nestedList = [[1,1],2,[1,1]]
    Output: [1,1,2,1,1]
    Explanation: By calling next repeatedly until hasNext returns false, the
                 order of elements returned by next should be: [1,1,2,1,1].

    --- Example 2 ---
    Input: nestedList = [1,[4,[6]]]
    Output: [1,4,6]
    Explanation: By calling next repeatedly until hasNext returns false, the
                 order of elements returned by next should be: [1,4,6].


    *** Constraints ***
    1 <= nestedList.length <= 500
    The values of the integers in the nested list is in the range [-10^6, 10^6].

*/

/**
 * // This is the interface that allows for creating nested lists.
 * // You should not implement it, or speculate about its implementation
 * class NestedInteger {
 *   public:
 *     // Return true if this NestedInteger holds a single integer, rather than a nested list.
 *     bool isInteger() const;
 *
 *     // Return the single integer that this NestedInteger holds, if it holds a single integer
 *     // The result is undefined if this NestedInteger holds a nested list
 *     int getInteger() const;
 *
 *     // Return the nested list that this NestedInteger holds, if it holds a nested list
 *     // The result is undefined if this NestedInteger holds a single integer
 *     const vector<NestedInteger> &getList() const;
 * };
 */

class NestedIterator {
public:
    NestedIterator(vector<NestedInteger> &nestedList)
    {

    }

    int next()
    {

    }

    bool hasNext()
    {

    }
};

/**
 * Your NestedIterator object will be instantiated and called as such:
 * NestedIterator i(nestedList);
 * while (i.hasNext()) cout << i.next();
 */

/**
 * // This is the interface that allows for creating nested lists.
 * // You should not implement it, or speculate about its implementation
 * class NestedInteger {
 *   public:
 *     // Return true if this NestedInteger holds a single integer, rather than a nested list.
 *     bool isInteger() const;
 *
 *     // Return the single integer that this NestedInteger holds, if it holds a single integer
 *     // The result is undefined if this NestedInteger holds a nested list
 *     int getInteger() const;
 *
 *     // Return the nested list that this NestedInteger holds, if it holds a nested list
 *     // The result is undefined if this NestedInteger holds a single integer
 *     const vector<NestedInteger> &getList() const;
 * };
 */

/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Beats: 15.40% */
/* Space Beats: 67.14% */

/* Time  Complexity: O(n) */
/* Space Complexity: O(n) */
class NestedIterator {
public:
    NestedIterator(vector<NestedInteger> &nestedList)
    {
        this->nestedList = nestedList;

        // Flatten the nestedList during initialization
        flatten(nestedList);
    }

    // Returns the next integer in the flattened list
    int next()
    {
        int number = flattenedList[curr_idx];
        curr_idx++;

        return number;
    }

    // Checks if there are more integers in the flattened list
    bool hasNext()
    {
        return curr_idx < flattenedList.size();
    }

private:
    // The list of NestedInteger elements to be flattened
    vector<NestedInteger> nestedList;

    // The flattened list of integers
    vector<int> flattenedList;

    // Index to keep track of the current position in the flattenedList
    int curr_idx = 0;

    // Recursively flattens the nested list and adds integers to the flattenedList
    void flatten(vector<NestedInteger>& currentList)
    {
        for (int i = 0; i < currentList.size(); i++)
        {
            if (currentList[i].isInteger())
                flattenedList.push_back(currentList[i].getInteger());
            else
                flatten(currentList[i].getList()); // Recursively flatten nested lists
        }
    }
};
