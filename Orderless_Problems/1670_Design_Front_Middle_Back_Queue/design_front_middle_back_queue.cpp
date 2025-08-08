/*
    ==============
    === MEDIUM ===
    ==============

    ====================================
    1670) Design Front Middle Back Queue
    ====================================

    ============
    Description:
    ============


    Design a queue that supports push and pop operations in the front, middle,
    and back.

    Implement the FrontMiddleBack class:

        + FrontMiddleBack() Initializes the queue.

        + void pushFront(int val) Adds val to the front of the queue.

        + void pushMiddle(int val) Adds val to the middle of the queue.

        + void pushBack(int val) Adds val to the back of the queue.

        + int popFront() Removes the front element of the queue and returns it.
          If the queue is empty, return -1.

        + int popMiddle() Removes the middle element of the queue and returns
          it. If the queue is empty, return -1.

        + int popBack() Removes the back element of the queue and returns it.
          If the queue is empty, return -1.

    Notice that when there are two middle position choices, the operation is
    performed on the frontmost middle position choice. For example:

        Pushing 6 into the middle of [1, 2, 3, 4, 5] results in:
        [1, 2, 6, 3, 4, 5].

        Popping the middle from [1, 2, 3, 4, 5, 6] returns 3 and results in:
        [1, 2, 4, 5, 6].

    ===============================
    CLASS:
    class FrontMiddleBackQueue {
    public:
        FrontMiddleBackQueue() {
            
        }
        
        void pushFront(int val) {
            
        }
        
        void pushMiddle(int val) {
            
        }
        
        void pushBack(int val) {
            
        }
        
        int popFront() {
            
        }
        
        int popMiddle() {
            
        }
        
        int popBack() {
            
        }
    };
    ===============================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input:
    ["FrontMiddleBackQueue", "pushFront", "pushBack", "pushMiddle",
     "pushMiddle", "popFront", "popMiddle", "popMiddle", "popBack", "popFront"]
    [[], [1], [2], [3], [4], [], [], [], [], []]
    Output:
    [null, null, null, null, null, 1, 3, 4, 2, -1]

    Explanation:
    FrontMiddleBackQueue q = new FrontMiddleBackQueue();
    q.pushFront(1);   // [1]
    q.pushBack(2);    // [1, 2]
    q.pushMiddle(3);  // [1, 3, 2]
    q.pushMiddle(4);  // [1, 4, 3, 2]
    q.popFront();     // return 1 -> [4, 3, 2]
    q.popMiddle();    // return 3 -> [4, 2]
    q.popMiddle();    // return 4 -> [2]
    q.popBack();      // return 2 -> []
    q.popFront();     // return -1 -> [] (The queue is empty)


    *** Constraints ***
    1 <= val <= 10^9
    At most 1000 calls will be made to pushFront, pushMiddle, pushBack,
    popFront, popMiddle, and popBack.

*/

#include <deque>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Beats: 68.73% */
/* Space Beats: 59.16% */

/* Time  Complexity: O(1) */
/* Space Complexity: O(N) */
class FrontMiddleBackQueue {
    deque<int> left_deque;
    deque<int> right_deque;

    void from_left_to_right()
    {
        if (left_deque.size() <= right_deque.size())
            return;

        right_deque.push_front(left_deque.back());
        left_deque.pop_back();
    }

    void from_right_to_left()
    {
        if (right_deque.size() <= left_deque.size() + 1)
            return;

        left_deque.push_back(right_deque.front());
        right_deque.pop_front();
    }

public:
    FrontMiddleBackQueue() {}

    void pushFront(int val)
    {
        left_deque.push_front(val);
        from_left_to_right();
    }

    void pushMiddle(int val)
    {
        left_deque.push_back(val);
        from_left_to_right();
    }

    void pushBack(int val)
    {
        right_deque.push_back(val);
        from_right_to_left();
    }

    int popFront()
    {
        if (left_deque.empty() && right_deque.empty())
            return -1;

        int result;
        if (left_deque.empty())
        {
            result = right_deque.front();
            right_deque.pop_front();
        }
        else
        {
            result = left_deque.front();
            left_deque.pop_front();
            from_right_to_left();
        }

        return result;
    }

    int popMiddle()
    {
        if (left_deque.empty() && right_deque.empty())
            return -1;

        int result;
        if (left_deque.size() == right_deque.size())
        {
            result = left_deque.back();
            left_deque.pop_back();
        }
        else
        {
            result = right_deque.front();
            right_deque.pop_front();
        }

        return result;
    }

    int popBack()
    {
        if (left_deque.empty() && right_deque.empty())
            return -1;

        int result = right_deque.back();
        right_deque.pop_back();
        from_left_to_right();

        return result;
    }
};
