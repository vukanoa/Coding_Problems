#include <iostream>
#include <vector>

/*
    ==============
    === MEDIUM ===
    ==============

    =====================================
    540) Single Element in a Sorted Array
    =====================================

    ============
    Description:
    ============

    You are given a sorted array consisting of only integers where every
    element appears exactly twice, except for one element which appears exactly
    once.

    Return the single element that appears only once.

    Your solution must run in O(log n) time and O(1) space.

    ====================================================
    FUNCTION: int singleNonDuplicate(vector<int>& nums);
    ====================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: nums = [1,1,2,3,3,4,4,8,8]
    Output: 2

    --- Example 2 ---
    Input: nums = [3,3,7,7,10,11,11]
    Output: 10


    *** Constraints ***
    1 <= nums.length <= 10^5
    0 <= nums[i] <= 10^5

*/

/*
    ------------
    --- IDEA ---
    ------------

    For some reason, this implementation has better Beating times than the 2nd
    Solution down below(than the bottom one) even if this one has 3 additional
    check-ups.

    I've submitted both Solution more than 10 times, but for some reason this
    one runs faster. I have no idea why.

*/

/* Time  Beats: 90.62% */
/* Space Beats: 46.33% */

/* Time  Complexity: O(logn) */
/* Space Complexity: O(1) */
class Solution {
public:
    int singleNonDuplicate(std::vector<int>& nums)
    {
        int n = nums.size();

        int left  = 0;
        int right = n - 1;

        while (left < right)
        {
            int mid = left + (right - left) / 2;

            if (
                ((mid-1 ==-1) || (mid-1 >= 0 && nums[mid - 1] != nums[mid])) &&
                ((mid+1 == n) || (mid+1 <  n && nums[mid + 1] != nums[mid]))
               )
                return nums[mid];

            int left_one;
            if (mid-1 >= 0 && nums[mid-1] == nums[mid])
                left_one = mid-1;
            else if (mid+1 < n && nums[mid] == nums[mid+1]) // Or just else
                left_one = mid;

            /*
                Now if from the left one of two appearances, to the end of the
                vector there are EVEN number of elements, we are certain that
                the "single number" is in the left portion since we're told
                that it's guaranteed that there is only one single element in
                the entire array.
            */
            if ((n - left_one) % 2 == 0)
                right = mid;
            else
                left = mid + 1;
        }

        return nums[left];
    }
};




/* Time  Beats: 80.82% */
/* Space Beats: 46.33% */

/* Time  Complexity: O(logn) */
/* Space Complexity: O(1) */
class Solution_2 {
public:
    int singleNonDuplicate(std::vector<int>& nums)
    {
        int n = nums.size();

        int left  = 0;
        int right = n - 1;

        while (left < right)
        {
            int mid = left + (right - left) / 2;

            if (
                ((mid-1 == -1) || (nums[mid - 1] != nums[mid])) &&
                ((mid+1 ==  n) || (nums[mid + 1] != nums[mid]))
               )
                return nums[mid];

            int left_one;
            if (mid-1 >= 0 && nums[mid-1] == nums[mid])
                left_one = mid-1;
            else // if (mid+1 < n && nums[mid] == nums[mid+1])
                left_one = mid;

            /*
                Now if from the left one of two appearances, to the end of the
                vector there are EVEN number of elements, we are certain that
                the "single number" is in the left portion since we're told
                that it's guaranteed that there is only one single element in
                the entire array.
            */
            if ((n - left_one) % 2 == 0)
                right = mid;
            else
                left = mid + 1;
        }

        return nums[left];
    }
};



/*
    ------------
    --- IDEA ---
    ------------

    ********************************
    *** Explanation for the Code ***
    ********************************

    This one is the most elegant and the most efficient out of all 3 Binary
    Search implementations.

    First of all, we are 100% sure there will be exactly one non-duplicate
    element and since that is the case we can use a Binary Search
    implementation that iterates while (left <= right), which means that at the
    end we will end up with a single element which is guaranteed to be the
    answer.

    Since we are going to use while(left <= right), that means we must
    initialize our "right" pointer to point at an element we will use, in other
    words all the elements in range [left, right] CAN BE answers.

    We are not using a range that includes the "left" and excludes the "right".
    We will also use a "left leaning" calculation of "mid" pointer.

        1. "Left  leaning" : mid = left + std::floor((right - left    ) / 2);
        2. "Right leaning" : mid = left + std::floor((right - left + 1) / 2);

    As a consequence of "left leaning" Binary Search, we will use:
        if (...)
            left  = mid + 1;
        else
            right = mid - 1;

    i.e. we will always exclude mid completely and since both "left" and
    "right" pointers point to elements that COULD BE answers and since we just
    realized that nums[mid] CANNOT be an answers, we have to exclude it either
    way. That's why we do this:

        if (...)
            left  = mid + 1;
        else
            right = mid - 1;


    *****************
    *** Intuition ***
    *****************

    Now that this is out of the way, let me explain the main idea behind this
    Solution.

    Consider this example:

        --- Example 1 ---

        nums = [1, 1, 2, 3, 3, 4, 4, 8, 8]
                0  1  2  3  4  5  6  7  8

    Since we are asked to solve this problem in O(logn) Time and O(1) Space, we
    realize that we must use a Binary Search. There is no other way to solve
    this problem. Everything else requires to iterate through all the elements
    first and then put it in some other data structure and then do it in:
        O(logn)

    However, that would be O(n), which is unacceptable.

    Okay, if we perform a basic Binary Search, what can we notice?

        nums = [1, 1, 2, 3, 3, 4, 4, 8, 8]
                0  1  2  3  4  5  6  7  8
                L           M           R

    We are on index "M". How are we going to decide if we should go to the left
    or to the right?

    At first glance, it seems impossible. However, look at these 3 additional
    examples:



        1)                |
                          V
            nums = [1, 1, 2, 3, 3, 4, 4, 5, 5, 7, 7, 8, 8]
                    0  1  2  3  4  5  6  7  8  9 10 11 12
                    L                 M                 R


        2)                                        |
                                                  V
            nums = [1, 1, 2, 2  3, 3, 4, 4, 5, 5, 7, 8, 8]
                    0  1  2  3  4  5  6  7  8  9 10 11 12
                    L                 M                 R



        3)                            |
                                      V
            nums = [1, 1, 2, 2  3, 3, 4, 5, 5, 7, 7, 8, 8]
                    0  1  2  3  4  5  6  7  8  9 10 11 12
                    L                 M                 R


    At first glance at 1) and 2), it seems even more impossible, right?
    However, when you look at 3), you might get an idea.

    At example 3) we can notice that if our "M" pointers points to an element
    we need to return, we can immediately return it.
    However, how can we know that this is exactly that element?

    We must internalize these two facts:
        1. There is CERTAINLY going to be a non-duplicate element
        2. There is CERTAINLY going to be exactly one non-duplicate element.

    Once that is out of the way, ask yourself - If "M" points to some random
    element in our array, how can I determine in O(1) if that is the element I
    need to return?

    The answer is - You have to determine if that element is a non-duplicate.

    How are you going to determine if some element that "M" points to is indeed
    a non-duplicate?

    By checking one element BEFORE and one element AFTER index "M".
    (Be careful here as "M" could, at some point, point to index 0 or n-1)

    Okay, let's consider example 1) again.


        1)                |
                          V
            nums = [1, 1, 2, 3, 3, 4, 4, 5, 5, 7, 7, 8, 8]
                    0  1  2  3  4  5  6  7  8  9 10 11 12
                    L                 M                 R

    We're going to chech one element BEFORE index "M" and one element AFTER
    index "M" and if neither element at "M-1"th or "M+1"th position is equal to
    our element at index "M"(4 in this case), then we'll just return 4.

    However, that is not the case here since we can notice that element at
    index "M-1" is equal to our element at index "M".

    Okay, that means that the current element we're on(i.e. where our "M"
    pointer points to) is NOT a non-duplicate, meaning it's NOT an answer we're
    looking for.

    So how can we decide if we should go to the left or to the right?

    You have to be perspicacious and notice that in order to have a SINGLE
    non-duplicate element in the entire array, you MUST have ODD number of
    elements in the array.

    Does that help?

    So if you find an element that has a duplicate, then take it's right part
    as an index and calculate total number of elements from that element,
    including that element, until the beginning of the array.

    In our case:

        1)                |
                          V
            nums = [1, 1, 2, 3, 3, 4, 4, 5, 5, 7, 7, 8, 8]
                    0  1  2  3  4  5  6  7  8  9 10 11 12
                    L                 M                 R
                                      ^
                                      |
                                    "right" part of the duplicate, pair, 4

        How many elements are there in the left part: [0, 6]?
        (6th index because "right" part of the duplicate 4 is at index 6)

        There are 7 elements ===> 6 - 0 + 1 = 7

        Is 7 an EVEN number?
        No!

        Then that means it's an ODD number, which further means that our answer
        is on the left side of our current "M" index.

        Therefore:
            right = mid - 1;




    Let's look at our example 2) now:

        2)                                        |
                                                  V
            nums = [1, 1, 2, 2  3, 3, 4, 4, 5, 5, 7, 8, 8]
                    0  1  2  3  4  5  6  7  8  9 10 11 12
                    L                 M                 R


            element at index "M" is NOT a non-duplicate, i.e. it's NOT what we
            are looking for because there are 2 elements with value 4 in our
            array "nums".

            Okay, now we have to move either to the left or to the right. Where
            are we going to move?

            The "right" part of our duplicate, pair, 4 is at index 7, therefore
            total element to the left of our "M" is:

                5 - 0 + 1 = 6 (We could also do "7 - 0 + 1" it doesn't make
                              any difference)

            which is EVEN, therefore, we DON'T want to go there since we are
            sure we won't find our answer. Therefore, we move our "left"
            pointer to the right of our "M" pointer:

                left = mid + 1;


        We continue doing this Binary Search until we hit an element with "M"
        that is a NON-duplicate.

*/

/* Time  Beats: 90.49% */
/* Space Beats: 19.78% */

/* Time  Complexity: O(logn) */
/* Space Complexity: O(1)    */
class Solution_3 {
public:
    int singleNonDuplicate(std::vector<int>& nums)
    {
        if (1 == nums.size())
            return nums[0];

        int left  = 0;
        int right = nums.size() - 1;

        while (left <= right)
        {
            int mid = left + (right - left) / 2;

            if (mid-1 >= 0 && nums[mid-1] == nums[mid])
            {
                if ((mid - 0 + 1) % 2 == 0)
                    left  = mid + 1;
                else
                    right = mid - 1;
            }
            else if (mid+1 < nums.size() && nums[mid] == nums[mid+1])
            {
                if ((mid+1 - 0 + 1) % 2 == 0) // Or just "mid % 2 == 0"
                    left  = mid + 1;
                else
                    right = mid - 1;
            }
            else
                return nums[mid];
        }

        return -1; // Since we are sure there will be a single non-duplicate
    }
};
