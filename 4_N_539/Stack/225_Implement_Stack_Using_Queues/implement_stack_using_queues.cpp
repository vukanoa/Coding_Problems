#include <iostream>
#include <queue>

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

/*
    ------------
    --- IDEA ---
    ------------

    Using two Queues.

*/

/* Time  Beats: 100.00% */
/* Space Beats:  50.64% */

/* Time  Complexity: O(n) */
/* Space Complexity: O(n) */
class MyStack {
public:
    MyStack()
    {

    }

    void push(int x)
    {
        if (empty())
            queue_left.push(x);
        else if (!queue_left.empty())
            queue_left.push(x);
        else
            queue_right.push(x);
    }

    int pop()
    {
        int top_elem;

        if (!queue_left.empty())
        {
            while (queue_left.size() > 1)
            {
                queue_right.push(queue_left.front());
                queue_left.pop();
            }

            top_elem = queue_left.front();
            queue_left.pop();
        }
        else
        {
            while (queue_right.size() > 1)
            {
                queue_left.push(queue_right.front());
                queue_right.pop();
            }

            top_elem = queue_right.front();
            queue_right.pop();
        }

        return top_elem;
    }

    int top()
    {
        int top_elem;

        if (!queue_left.empty())
        {
            while (queue_left.size() > 1)
            {
                queue_right.push(queue_left.front());
                queue_left.pop();
            }

            top_elem = queue_left.front();
            queue_left.pop();
            queue_right.push(top_elem);
        }
        else
        {
            while (queue_right.size() > 1)
            {
                queue_left.push(queue_right.front());
                queue_right.pop();
            }

            top_elem = queue_right.front();
            queue_right.pop();
            queue_left.push(top_elem);
        }

        return top_elem;
    }

    bool empty()
    {
        return queue_left.empty() && queue_right.empty();
    }

private:
    std::queue<int> queue_left;
    std::queue<int> queue_right;
};

/**
 * Your MyStack object will be instantiated and called as such:
 * MyStack* obj = new MyStack();
 * obj->push(x);
 * int param_2 = obj->pop();
 * int param_3 = obj->top();
 * bool param_4 = obj->empty();
 */




/*
    ------------
    --- IDEA ---
    ------------

    Using only one Queue.

*/

/* Time  Beats: 100.00% */
/* Space Beats:  84.76% */

/* Time  Complexity: O(n) */
/* Space Complexity: O(n) */
class MyStack {
public:
    MyStack()
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

        int ret = queue.front();
        queue.pop();

        return ret;
    }

    int top()
    {
        int size = queue.size();
        for (int i = 0; i < size-1; i++)
        {
            int tmp = queue.front();
            queue.pop();
            queue.push(tmp);
        }

        int ret = queue.front();
        queue.pop();
        queue.push(ret);

        return ret;
    }

    bool empty()
    {
        return queue.empty();
    }

private:
    std::queue<int> queue;
};
