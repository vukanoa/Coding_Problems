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

    The whole idea is to have two stacks so that you can implement getMin in
    O(1) as well.

    The only problem here is -- How to implement getMin() function in O(1)?

    As we've said -- We need two stacks.
    Why?

    In the main stack every time we push, we check if that element is the
    lowest value in the other, min_stack(if it exists, of course), stack.

    If it is, then push this current value in min_stack, that way the minimum
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
         stack               min_stack

    If we were to pop from the stack, then min_stack would remain as it is
    since 5 wasn't the current global minimum.

    However, if we were to pop again, now we would've popped 2 which, at this
    point, is indeed a GLOBAL minimum(i.e. Minimum in the entire Stack). Thus,
    we would pop that value from the min_stack, as well.

    Also, consider this example:

        |     |               |     |
        |     |               |     |
        |     |               |     |
        |  3  |               |     |
        |  5  |               |  3  |
        |  3  |               |  3  |
        -------               -------
         stack               min_stack

    You may wonder -- Why do we push 3 for the second time in min_stack?
    Well, if we didn't do that, if we kept only a single 3, we would have this
    situation:

        |     |               |     |
        |     |               |     |
        |     |               |     |
        |  3  |               |     |
        |  5  |               |     |
        |  3  |               |  3  |
        -------               -------
         stack               min_stack

     Now imagine that we pop from the stack. Since we are popping 0 and that is
     the current global minimum, then we would end up like this:


        |     |               |     |
        |     |               |     |
        |     |               |     |
        |     |               |     |
        |  1  |               |     |
        |  0  |               |     |
        -------               -------
         stack               min_stack

    Which is obviously erroneous since our stack is NOT Empty, but our
    stack_minimums IS which should be impossible. Thus, if we push an element
    that is EQUAL to our current global minimum(at the top of the min_stack)
    then push that value in min_stack again.

    I believe that the implementation of this is self-explanatory.

    However I'd like to note a few things:
        1. "sp" stands for "Stack Pointer" since compiler on LeetCode did not
           give me to name it "top" since we have a function with that name
           already

        2. "min_sp" is a "Stack Pointer" for min_stack, i.e. the "other" stack.

        3. I often check if (sp >= 0) or if (min >= 0) to prevent underflow and
           overflow, since both "sp" and "min_sp" are set to -1 in the
           constructor.

        4. I'm not using neither "stack" from C++, nor "vector", I'm actually
           constructing a basic array on the STACK OF THE PROCESS(This has
           nothing to do with the data structure we're about to simulate with
           that array)

           If we were to use "std::stack" or "std::vector" those would've been
           allocated on the HEAP OF THE PROCESS. Since STACK is faster and we
           know in advance max size of it, why not use a basic array on the
           STACK OF THE ARRAY?

*/

/* Time  Beats: 100.00% */
/* Space Beats:  5.62% */

/* Time  Complexity: O(N) */
/* Space Complexity: O(N) */
class MinStack {
public:
    MinStack()
    {
        
    }
    
    void push(int val)
    {
        if (sp == -1 || min_stack[min_sp] >= val)
            min_stack[++min_sp] = val;

        stack[++sp] = val;
    }
    
    void pop()
    {
        if (stack[sp] == min_stack[min_sp])
            min_sp--; // Pop from the Min_Stack as well

        sp--;
    }
    
    int top()
    {
        return stack[sp];
    }
    
    int getMin()
    {
        return min_stack[min_sp];
    }

private:
    static constexpr int MAX_CALLS = 3 * 1e4;

    int stack[MAX_CALLS];     // Allocated on the STACK instead of HEAP
    int min_stack[MAX_CALLS]; // Allocated on the STACK instead of HEAP

    int sp     = -1; // Stack     pointer
    int min_sp = -1; // Min_Stack pointer
};
