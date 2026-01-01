#include <iostream>
#include <vector>
#include <stack>
#include <unordered_map>

/*
    ============
    === HARD ===
    ============

    ============================
    895) Maximum Frequency Stack
    ============================

    ============
    Description:
    ============

    Design a stack-like data structure to push elements to the stack and pop
    the most frequent element from the stack.

    Implement the FreqStack class:

        + FreqStack() constructs an empty frequency stack.

        + void push(int val) pushes an integer val onto the top of the stack.

        + int pop() removes and returns the most frequent element in the stack.

            + If there is a tie for the most frequent element, the element
              closest to the stack's top is removed and returned.


    ===============================
    class FreqStack {
    public:
        FreqStack() {

        }

        void push(int val) {

        }

        int pop() {

        }
    };
    ===============================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input
    ["FreqStack", "push", "push", "push", "push", "push", "push", "pop", "pop",
     "pop", "pop"]
    [[], [5], [7], [5], [7], [4], [5], [], [], [], []]
    Output
    [null, null, null, null, null, null, null, 5, 7, 5, 4]

    Explanation
    FreqStack freqStack = new FreqStack();
    freqStack.push(5); // The stack is [5]
    freqStack.push(7); // The stack is [5,7]
    freqStack.push(5); // The stack is [5,7,5]
    freqStack.push(7); // The stack is [5,7,5,7]
    freqStack.push(4); // The stack is [5,7,5,7,4]
    freqStack.push(5); // The stack is [5,7,5,7,4,5]

    freqStack.pop();   // return 5, as 5 is the most frequent. The stack
                          becomes [5,7,5,7,4].

    freqStack.pop();   // return 7, as 5 and 7 is the most frequent, but 7 is
                          closest to the top. The stack becomes [5,7,5,4].

    freqStack.pop();   // return 5, as 5 is the most frequent. The stack
                          becomes [5,7,4].

    freqStack.pop();   // return 4, as 4, 5 and 7 is the most frequent, but 4
                          is closest to the top. The stack becomes [5,7].


    *** Constraints ***
    0 <= val <= 10^9
    At most 2 * 10^4 calls will be made to push and pop.
    It is guaranteed that there will be at least one element in the stack
    before calling pop.

*/

/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Beats: 27.34% */
/* Space Beats:  5.10% */

/* Time  Complexity: O(1) */
/* Space Complexity: O(1) */
class FreqStack {
public:
    FreqStack()
        : group_stacks(1)
    {}

    void push(int val)
    {
        umap_count[val]++;

        if (group_stacks.size() < umap_count[val] + 1)
        {
            std::stack<int> stack;
            stack.push(val);

            group_stacks.push_back(std::make_pair(umap_count[val], stack));
        }
        else
            group_stacks[umap_count[val]].second.push(val);
    }

    int pop()
    {
        int val = group_stacks.back().second.top();
        group_stacks.back().second.pop();

        umap_count[val]--;

        if (group_stacks.back().second.empty())
            group_stacks.pop_back();

        return val;
    }

private:
    std::unordered_map<int, int> umap_count;
    std::vector<std::pair<int, std::stack<int>>> group_stacks;
};

/**
 * Your FreqStack object will be instantiated and called as such:
 * FreqStack* obj = new FreqStack();
 * obj->push(val);
 * int param_2 = obj->pop();
 */




/*
    ------------
    --- IDEA ---
    ------------

    Another way of solving it.

    This one uses a HashMap of stacks instead of vector of stacks.
    When we are using the vector we're always retrieving from:

        group_stacks.back()

    whereas here, we retrieve from:

        group_stacks[max_count]

    That's why we have to maintain and update "max_count".

*/

/* Time  Beats: 96.06% */
/* Space Beats: 47.77% */

/* Time  Complexity: O(1) */
/* Space Complexity: O(1) */
class FreqStack {
public:
    FreqStack()
        : group_stacks(1), max_count(0)
    {}

    void push(int val)
    {
        umap_count[val]++;

        if (umap_count[val] > max_count)
            max_count = umap_count[val];

        group_stacks[umap_count[val]].push(val);
    }

    int pop()
    {
        int val = group_stacks[max_count].top();
        group_stacks[max_count].pop();

        umap_count[val]--;

        if (group_stacks[max_count].empty())
            max_count--;

        return val;
    }

private:
    std::unordered_map<int, int> umap_count;
    std::unordered_map<int, std::stack<int>> group_stacks;
    int max_count;
};
