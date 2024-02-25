#include <iostream>
#include <vector>
#include <stack>

/*
    ==============
    === MEDIUM ===
    ==============

    ===========================
    155) Min Stack
    ===========================

    ============
    Description:
    ============

    Design a stack that supports push, pop, top, and retrieving the minimum
    element in constant time.

    Implement the MinStack class:
        - MinStack() initializes the stack objects
        - void push(int val) pushes the element 'val' onto the stack
        - void pop() removes the element on the top of the stack.
        - int top() gets the top element of the stack.
        - int getMin() retrieves the minimum element in the stack.

    =====
    Node: You must implement a solution with O(1) time complexity for each
    ===== function.

    ===============================
    CLASS:
    class MinStack{
        MinStack()
        {

        }

        void push(int val)
        {

        }

        void pop()
        {

        }

        int top()
        {

        }

        int getMin()
        {

        }
    };
    ===============================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input:
        ["MinStack", "push", "push", "push", "getMin", "pop", "top", "getMin"]
        [[], [-2], [0], [-3], [], [], [], []]

    Output:
        [null, null, null, null, -3, null, 0, -2]

    Explanation
    MinStack minStack = new MinStack();
    minStack.push(-2);
    minStack.push(0);
    minStack.push(-3);
    minStack.getMin(); // return -3
    minStack.pop();
    minStack.top();    // return 0
    minStack.getMin(); // return -2

    *** Constraints ***
    -2^31 <= val <= 2^31 - 1
    Methods pop, top and getMin operations will always be called on non-empty
    stacks.
    At most 3 * 10^4 calls will be made to "push", "pop", "top", and "getMin".

*/

/**
 * Your MinStack object will be instantiated and called as such:
 * MinStack* obj = new MinStack();
 * obj->push(val);
 * obj->pop();
 * int param_3 = obj->top();
 * int param_4 = obj->getMin();
 */

/*
    ------------
    --- IDEA ---
    ------------

    ============
    === NOTE ===
    ============
    This is the best Solution out of all three in this file.


    The whole idea is to have two stacks so that you can implement getMin in
    O(1) as well.

    It is, actually, pretty difficult to implement stack functions:
        1. push
        2. pop
        3. top

    in worse than O(1). So the Problem becomes - How to implement a stack with
    a "getMin" function in O(1) Time Complexity.

    As we've said - We need two stacks.
    Why?

    In the main stack every time we push, we ask if that element is the lowest
    value in the other, stack_minimum(if it exists, of course), stack.

    If it is, then push this current value in stack_min, that way the minimum
    of the whole stack will always be at the top of the 2nd stack named
    stack_minimum.

    Consider this example:
        push 4
        push 3
        push 6
        push 7
        push 2
        push 5

    The stack will look like this:

    |  5  |               |     |
    |  2  |               |     |
    |  7  |               |     |
    |  6  |               |  2  |
    |  3  |               |  3  |
    |  4  |               |  4  |
    -------               -------
     stack             stack_minimums

    If we were to pop from stack, then stack_minimums would remain as it is
    since 5 wasn't the current global minimum.

    However, if we were to pop again, now we would've pop-ed 2 which, at this
    point, is indeed a global minimum. Thus, we would pop that value from the
    stack_minimum, as well.

    Also, consider this example:

    |     |               |     |
    |     |               |     |
    |     |               |     |
    |  0  |               |     |
    |  1  |               |  0  |
    |  0  |               |  0  |
    -------               -------
     stack             stack_minimums

    You may wonder - Why do we push 0 for the second time in stack_minimums?
    Well, if we didn't do that, if we kept only a single 0, we would have this
    situation:

    |     |               |     |
    |     |               |     |
    |     |               |     |
    |  0  |               |     |
    |  1  |               |     |
    |  0  |               |  0  |
    -------               -------
     stack             stack_minimums

     Now imagine that we pop from the stack. Since we are popping 0 and that is
     the current global minimum, then we would end up like this:


    |     |               |     |
    |     |               |     |
    |     |               |     |
    |     |               |     |
    |  1  |               |     |
    |  0  |               |     |
    -------               -------
     stack             stack_minimums

     Which is obviously erroneous since our stack is NOT Empty, but our
     stack_minimums IS which should be impossible. Thus, if we push an element
     that is equal to our current global minimum(at the top of the
     stack_minimums) then push that value in stack_minimums again.

    I believe that the implementation of this is self-explanatory.

    However I'd like to note a few things:
        1. "sp" stands for "Stack Pointer" since compiler on LeetCode did not
           give me to name it "top" since we have a function with that name
           already

        2. "min" is "Stack Pointer" for stack_minimums

        3. I often check if (sp >= 0) or if (min >= 0) to prevent underflow and
           overflow, since both "sp" and "min" are set to -1 in the constructor

*/

/* Time  Beats: 91.83% */
/* Space Beats: 58.58% */

/* Time  Complexity: O(1) */
/* Space Complexity: O(n) */
class MinStack_1 {
public:
    MinStack_1()
    {
        sp = -1;
        sp_min = -1;
    }

    void push(int val)
    {
        stack.push_back(val);
        sp++;

        if (sp_min == -1 || val <= stack_minimums[sp_min])
        {
            stack_minimums.push_back(val);
            sp_min++;
        }
    }

    void pop()
    {
        /* Though, we're told that "Method pop, top and getMin operations will
        always be called on non-empty stacks", so this checkup is redundant */
        if (sp_min >= 0 && sp >= 0 && stack_minimums[sp_min] == stack[sp])
        {
            stack_minimums.pop_back();
            sp_min--;
        }

        if (sp >= 0)
        {
            stack.pop_back();
            sp--;
        }
    }

    int top()
    {
        if (sp >= 0)
            return stack[sp];

        // We're told in Constraint that:
        /*
            Methods pop, top and getMin operations will always be called on
            non-empty stacks.
        */
        // So this won't ever happen, therefore we can return any number.
        return -1;
    }

    int getMin()
    {
        return stack_minimums[sp_min];
    }

private:
    int sp;
    int sp_min;
    std::vector<int> stack;
    std::vector<int> stack_minimums;

};




/*
    ------------
    --- IDEA ---
    ------------

    This one uses std::stack instead of vector and "sp"s.

*/

/* Time  Beats: 96.61% */
/* Space Beats: 11.70% */

/* Time  Complexity: O(1) */
/* Space Complexity: O(n) */
class MinStack_Stack {
public:
    MinStack_Stack()
    {}

    void push(int val)
    {
        stack.push(val);

        if (mon_stack.empty() || val <= mon_stack.top())
            mon_stack.push(val);
    }

    void pop()
    {
        int top = stack.top();
        stack.pop();

        if (top == mon_stack.top())
            mon_stack.pop();
    }

    int top()
    {
        return stack.top();
    }

    int getMin()
    {
        return mon_stack.top();
    }

private:
    std::stack<int> stack;
    std::stack<int> mon_stack;
};




/*
    ------------
    --- IDEA ---
    ------------

    It's the same idea, but we're just using Singly Linked List instead of
    vectors/arrays.

*/

/* Time  Beats: 74.85% */
/* Space Beats: 11.13% */

/* Time  Complexity: O(1) */
/* Space Complexity: O(n) */
class MinStack_2 {
private:
    struct Node{
        int val;
        int min;
        struct Node* next;

        Node(int val, int min, struct Node* next) : val(val), min(min), next(next)
        {}
    };

public:
    MinStack_2()
    {
        head = nullptr;
    }

    void push(int val)
    {
        if (head == nullptr)
            head = new Node(val, val, nullptr);
        else
            head = new Node(val, std::min(val, head->min), head);
    }

    void pop()
    {
        head = head->next;
    }

    int top()
    {
        return head->val;
    }

    int getMin()
    {
        return head->min;
    }

private:
    struct Node* head;
};




/*
    ------------
    --- IDEA ---
    ------------

    It's almost equivalent to the First Solution, however, here, we have the
    same amount of elements in "stack" and "min" at every point.

    Instead of this:

        |     |               |     |
        |     |               |     |
        |     |               |     |
        |  0  |               |     |
        |  1  |               |  0  |
        |  0  |               |  0  |
        -------               -------
         stack             stack_minimums


    We have this:

        |     |               |     |
        |     |               |     |
        |     |               |     |
        |  0  |               |  0  |
        |  1  |               |  1  |
        |  0  |               |  0  |
        -------               -------
         stack             stack_minimums

    Thus, every time we push onto "stack", we push onto "mins" as well.
    Also, every time we pop  from "stack", we pop  from "mins" as well.
*/

/* Time  Beats: 67.20% */
/* Space Beats: 58.58% */

/* Time  Complexity: O(1) */
/* Space Complexity: O(n) */
class MinStack_3 {
public:
    MinStack_3()
    {
        sp = -1;
        sp_min = -1;
    }

    void push(int val)
    {
        stack.push_back(val);
        sp++;

        if (mins.size() == 0 || (sp_min >= 0 && val < mins[sp_min]))
        {
            mins.push_back(val);
            sp_min++;
        }
        else
        {
            mins.push_back(mins[sp_min]);
            sp_min++;
        }
    }

    void pop()
    {
        mins.pop_back();
        sp_min--;

        stack.pop_back();
        sp--;
    }

    int top()
    {
        return stack[sp];
    }

    int getMin()
    {
        return mins[sp_min];
    }

private:
    std::vector<int> stack;
    std::vector<int> mins;
    int sp;
    int sp_min;
};


int
main()
{
    // MinStack_1     obj;
    MinStack_Stack obj;
    // MinStack_2     obj;
    // MinStack_3     obj;


    std::cout << "\n\t=================";
    std::cout << "\n\t=== MIN STACK ===";
    std::cout << "\n\t=================\n\n";


    /* Example 1 */
    obj.push(-2);
    std::cout << "\tpush: -2\n";
    obj.push(0);
    std::cout << "\tpush: 0\n";
    obj.push(-3);
    std::cout << "\tpush: -3\n";

    int min = obj.getMin();
    std::cout << "\tCurrent min: " << min << "\n";

    obj.pop();
    std::cout << "\tpop!\n";

    int top = obj.top();
    std::cout << "\tCurrent top: " << top << "\n";

    min = obj.getMin();
    std::cout << "\tCurrent min: " << min << "\n";

    std::cout << "\n";



    /* Example 2 */
    // obj.push(4);
    // std::cout << "\tpush: 4\n";
    // obj.push(3);
    // std::cout << "\tpush: 3\n";

    // int min = obj.getMin();
    // std::cout << "\tCurrent min: " << min << "\n";

    // obj.push(6);
    // std::cout << "\tpush: 6\n";
    // obj.push(7);
    // std::cout << "\tpush: 7\n";

    // int top = obj.top();
    // std::cout << "\tCurrent top: " << top << "\n";

    // min = obj.getMin();
    // std::cout << "\tCurrent min: " << min << "\n";

    // obj.push(2);
    // std::cout << "\tpush: 2\n";
    // obj.push(5);
    // std::cout << "\tpush: 5\n";

    // top = obj.top();
    // std::cout << "\tCurrent top: " << top << "\n";

    // min = obj.getMin();
    // std::cout << "\tCurrent min: " << min << "\n";

    // std::cout << "\n";



    /* Example 3 */
    // obj.push(0);
    // std::cout << "\tpush: 0\n";
    // obj.push(1);
    // std::cout << "\tpush: 1\n";
    // obj.push(0);
    // std::cout << "\tpush: 0\n";

    // int min = obj.getMin();
    // std::cout << "\tCurrent min: " << min << "\n";

    // obj.pop();
    // std::cout << "\tPop!\n";
    // int top = obj.top();
    // std::cout << "\tCurrent top: " << top << "\n";

    // min = obj.getMin();
    // std::cout << "\tCurrent min: " << min << "\n";


    return 0;
}
