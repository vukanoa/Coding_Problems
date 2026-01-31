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

#include <stack>
#include <unordered_map>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    This is a Brute-Force Solution. It does work because of the Constraints,
    however this is NOT optimal. It's just so that you can compare it with the
    next Solution and see why example is the next Solutoin better.

*/

/* Time  Beats: 6.66% */
/* Space Beats: 5.83% */

/* Time  Complexity: O(N) */
/* Space Complexity: O(N) */
class FreqStack {
public:
    FreqStack() {
        
    }
    
    void push(int val)
    {
        if (num_to_freq.find(val) != num_to_freq.end() && num_to_freq[val] > 0)
        {
            freq_count[num_to_freq[val]]--; // Decrement
        }

        num_to_freq[val]++;
        freq_count[num_to_freq[val]]++; // Increment

        max_freq = max(max_freq, num_to_freq[val]);

        my_stack.push(val);
    }
    
    int pop()
    {
        stack<int> helper_stack;
        while (num_to_freq[my_stack.top()] < max_freq)
        {
            helper_stack.push(my_stack.top());
            my_stack.pop();
        }

        int ret = my_stack.top();
        my_stack.pop();

        freq_count[num_to_freq[ret]]--; // Decrement
        if (freq_count[num_to_freq[ret]] == 0)
            max_freq--;

        num_to_freq[ret]--;
        freq_count[num_to_freq[ret]]++; // Increment


        while ( ! helper_stack.empty())
        {
            my_stack.push(helper_stack.top());
            helper_stack.pop();
        }

        return ret;
    }

private:
    int max_freq = 0;
    unordered_map<int,int> num_to_freq;
    unordered_map<int,int> freq_count;

    stack<int> my_stack;
};
