#include <iostream>
#include <vector>

/*
    ============
    === EASY ===
    ============

    ===========================
    88) Merge Sorted Array
    ===========================

    ============
    Description:
    ============

    You are given two integer arrays nums1 and nums2, sorted in non-decreasing
    order, and two integers m and n, representing the number of elements in
    nums1 and nums2 respectively.

    Merge nums1 and nums2 into a single array sorted in non-decreasing order.

    The final sorted array should not be returned by the function, but instead
    be stored inside the array nums1. To accommodate this, nums1 has a length
    of m + n, where the first m elements denote the elements that should be
    merged, and the last n elements are set to 0 and should be ignored. nums2
    has a length of n.

    Follow up: Can you come up with an algorithm that runs in O(m + n) time?

    ===========================================================================
    FUNCTION: void merge(vector<int>& nums1, int m, vector<int>& nums2, int n);
    ===========================================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: nums1 = [1,2,3,0,0,0], m = 3, nums2 = [2,5,6], n = 3
    Output: [1,2,2,3,5,6]

    --- Example 2 ---
    Input: nums1 = [1], m = 1, nums2 = [], n = 0
    Output: [1]

    --- Example 3 ---
    Input: nums1 = [0], m = 0, nums2 = [1], n = 1
    Output: [1]

    *** Constraints ***
    nums1.length == m + n
    nums2.length == n
    0 <= m, n <= 200
    1 <= m + n <= 200
    -109 <= nums1[i], nums2[j] <= 109

*/


/*
    ------------
    --- IDEA ---
    ------------

    ============================================================
    Note: This Solution is NOT Optimal even though it beats 100%
    ============================================================

    Start from the beginning of nums1.
    If nums1 at that index is smaller than nums2[0] then:
        do nothing.

    However, if nums1[i] > nums2[0], then:
        Swap nums1[i] with nums2[0];

        But that new number in nums2[0] can be larger than some or all of the
        elements. Thus we have to "insert it in the right place".

    That won't happen very often, so you could consider this Solution O(m + n)
    as well, but it's not quite the same as the Solution Efficient down below.

    It's better not to do it this way, but just wanted to have it here as an
    extra idea.

*/

/* Time  Beats: 100% */
/* Space Beats: 84.20% */

/* Time  Complexity: O(m + n) */
/* Space Complexity: O(1) */
class Solution_worse {
public:
    void merge(std::vector<int>& nums1, int m, std::vector<int>& nums2, int n)
    {
        if (n == 0)
            return;

        for (int left = 0; left < m; left++)
        {
            if (nums1[left] > nums2[0])
            {
                std::swap(nums1[left], nums2[0]);

                // Put in order
                for (int i = 0; i < n - 1; i++)
                {
                    if (nums2[i] < nums2[i + 1])
                        break;
                    else
                        std::swap(nums2[i], nums2[i + 1]);
                }
            }
        }

        for (int i = m; i < m+n; i++)
            nums1[i] = nums2[i - m];
    }
};




/*
    ------------
    --- IDEA ---
    ------------

    "last_unfilled" is going to be reffered, down there, simply as "x".


    What is, instead of starting from the beginning, we started from the back?

    Luckily, we've been told that nums1 has m+n elements, where last n are 0's.

    We'll use variable 'x' to represent the index, from the back of nums1, at
    which we have to put the next biggest item from both arrays.

    However, there's a caveat - What if we run out of elements in one array
    before we've finished?

    Example:
        nums1 = [9, 0, 0, 0]
        nums2 = [1, 2, 3]


    Simulation:

    1)
        nums1 = [9, 0, 0, 0]
                 ^        x

        nums2 = [1, 2, 3]
                       ^

    2)
        nums1 = [9, 0, 0, 9]
                       x

        nums2 = [1, 2, 3]
                       ^

    What now?

    So if either pointer of these two vectors gets below 0, then just fill the
    rest of 'x' indexes with elements from the non-empty vector.

    "The rest" means until x becomes less than 0.

    That's the only caveat.

*/

/* Time  Beats: 100% */
/* Space Beats: 84.20% */

/* Time  Complexity: O(m + n) */
/* Space Complexity: O(1) */
class Solution_Efficient {
public:
    void merge(std::vector<int>& nums1, int m, std::vector<int>& nums2, int n)
    {
        int last_unfilled = m + n - 1;

        int one = m - 1;
        int two = n - 1;

        while (last_unfilled >= 0)
        {
            if (one < 0)
                nums1[last_unfilled] = nums2[two--];
            else if (two < 0)
                nums1[last_unfilled] = nums1[one--];
            else if (nums1[one] > nums2[two])
                nums1[last_unfilled] = nums1[one--];
            else
                nums1[last_unfilled] = nums2[two--];

            last_unfilled--;
        }
    }
};




/*
    ------------
    --- IDEA ---
    ------------

    Again, start from the back.
    'i' is the pointer of nums1.
    'j' is the pointer of nums2.

    "last_unfilled" is the pointer at which we want to store the greater
    element, since we are "merging them" from the back.

*/

/* Time  Beats:   100% */
/* Space Beats: 22.41% */

/* Time  Complexity: O(m + n) */
/* Space Complexity: O(1) */
class Solution_3 {
public:
    void merge(std::vector<int>& nums1, int m, std::vector<int>& nums2, int n)
    {
        if (n == 0)
            return;

        int one = m-1;
        int two = n-1;

        int last_unfilled = m + n - 1;

        while (last_unfilled >= 0)
        {
            if (one >= 0 && two >= 0)
            {
                if (nums1[one] <= nums2[two])
                    nums1[last_unfilled--] = nums2[two--];
                else
                    nums1[last_unfilled--] = nums1[one--];
            }
            else if (two >= 0)
                nums1[last_unfilled--] = nums2[two--];
            else
                break; // If only one >= 0 then everything is already okay
        }
    }
};


int
main()
{
    Solution_Efficient sol_eff;
    Solution_3         sol_3;


    /* Example 1 */
    std::vector<int> nums1 = {1, 2, 3, 0, 0, 0};
    int m = 3;
    std::vector<int> nums2 = {2, 5, 6};
    int n = 3;

    /* Example 2 */
    // std::vector<int> nums1 = {};
    // int m = 0;
    // std::vector<int> nums2 = {1};
    // int n = 1;

    /* Example 3 */
    // std::vector<int> nums1 = {1};
    // int m = 1;
    // std::vector<int> nums2 = {};
    // int n = 0;

    /* Example 4 */
    // std::vector<int> nums1 = {9, 0, 0, 0};
    // int m = 1;
    // std::vector<int> nums2 = {1, 2, 3};
    // int n = 3;

    /* Example 5 */
    // std::vector<int> nums1 = {4, 5, 8, 0, 0};
    // int m = 3;
    // std::vector<int> nums2 = {1, 7};
    // int n = 2;


    std::cout << "\n\t===============================";
    std::cout << "\n\t=== MERGE TWO SORTED ARRAYS ===";
    std::cout << "\n\t===============================\n";


    /* Write Input */
    bool first = true;
    std::cout << "\n\tnums1: [";
    for (auto x: nums1)
    {
        if (!first)
            std::cout << ", ";

        std::cout << x;
        first = false;
    }
    std::cout << "]";

    first = true;
    std::cout << "\n\tnums2: [";
    for (auto x: nums2)
    {
        if (!first)
            std::cout << ", ";

        std::cout << x;
        first = false;
    }
    std::cout << "]\n\n";



    /* Solution */
    sol_eff.merge(nums1, m, nums2, n);
    // sol_3.merge(nums1, m, nums2, n);



    /* Write Output */
    first = true;
    std::cout << "\n\tnums1: [";
    for (auto x: nums1)
    {
        if (!first)
            std::cout << ", ";

        std::cout << x;
        first = false;
    }
    std::cout << "]\n\n";


    return 0;
}
