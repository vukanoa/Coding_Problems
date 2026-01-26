/*
    ============
    === EASY ===
    ============

    =================================
    225) Implement Stack Using Queues
    =================================

    ============
    Description:
    ============

    Implement a last-in-first-out (LIFO) stack using only two queues. The
    implemented stack should support all the functions of a normal stack (push,
    top, pop, and empty).

    Implement the MyStack class:

        void push(int x) Pushes element x to the top of the stack.
        int pop() Removes the element on the top of the stack and returns it.
        int top() Returns the element on the top of the stack.
        boolean empty() Returns true if the stack is empty, false otherwise.

    Notes:

        You must use only standard operations of a queue, which means that only
        push to back, peek/pop from front, size and is empty operations are
        valid.  Depending on your language, the queue may not be supported
        natively. You may simulate a queue using a list or deque (double-ended
        queue) as long as you use only a queue's standard operations.

    ==========
    Follow-up: Can you implement the stack using only one queue?
    ==========

    ===============================
    CLASS:
    class MyStack {
    public:
        MyStack() {

        }

        void push(int x) {

        }

        int pop() {

        }

        int top() {

        }

        bool empty() {

        }
    };
    ===============================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input
    ["MyStack", "push", "push", "top", "pop", "empty"]
    [[], [1], [2], [], [], []]
    Output
    [null, null, null, 2, 2, false]

    Explanation
    MyStack myStack = new MyStack();
    myStack.push(1);
    myStack.push(2);
    myStack.top(); // return 2
    myStack.pop(); // return 2
    myStack.empty(); // return False




    *** Constraints ***
    1 <= x <= 9
    At most 100 calls will be made to push, pop, top, and empty.
    All the calls to pop and top are valid.

*/

#include <queue>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    Using only one Queue. It's completely unnecessary to use two Queues. It
    adds additional overhead.

*/

/* Time  Beats: 100.00% */
/* Space Beats:  84.76% */

/* Time  Complexity: O(n) */
/* Space Complexity: O(n) */
class MyStack_One_Queue {
public:
    MyStack_One_Queue ()
    {
        
    }
    
    void push(int x)
    {
        queue.push(x);
    }
    
    int pop()
    {
        int size = queue.size();
        for (int i = 0; i < size-1; i++)
        {
            queue.push(queue.front());
            queue.pop();
        }

        int top = queue.front();
        queue.pop(); // Pop that element

        return top;
    }
    
    int top()
    {
        int size = queue.size();
        for (int i = 0; i < size-1; i++)
        {
            queue.push(queue.front());
            queue.pop();
        }

        int top = queue.front();
        queue.pop();
        queue.push(top);

        return top;
    }
    
    bool empty()
    {
        return queue.empty();
    }

private:
    queue<int> queue;
};
