#include <iostream>
#include <vector>
#include <climits>

/*
    ============
    === HARD ===
    ============

    ==============================
    4) Median of Two Sorted Arrays
    ==============================

    ============
    Description:
    ============

    Given two sorted arrays nums1 and nums2 of size m and n respectively,
    return the median of the two sorted arrays.

    The overall run time complexity should be O(log (m + n)).

    ================================================================================
    FUNCTION: double findMedianSortedArrays(vector<int>& nums1, vector<int>& nums2);
    ================================================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input:  nums1 = [1, 3], nums2 = [2]
    Output: 2.00000
    Explanation: merged array = [1, 2, 3] and median is 2

    --- Example 2 ---
    Input:  nums1 = [1, 2], nums2 = [3, 4]
    Output: 2.50000

    *** Constraints ***
    nums1.length == m
    nums2.length == n
    0 <= m <== 1000
    0 <= n <== 1000
    1 <= m + n <= 2000
    -10^6 <= nums1[i], nums2[i] <= 10^6

*/


/*
    ------------
    --- IDEA ---
    ------------

    If we tried to traverse both vectors and recreate a new that is entirely
    sorted(Kind of like Sorted Merge Lists problem but with arrays).

    However that would require going through entire nums1 and entire nums2
    vector which is O(m + n).

    m = nums1.size();
    n = nums2.size();

    But we are told that the Time Complexity under which we have to invent a
    Solution is: O(log(m + n));

    Which usually means we have to do a binary search. Which indeed is the case
    here.


    So let's say that we're given a different example:

    array B: [1, 2, 3, 4, 5, 6, 7, 8]
    array A: [1, 2, 3, 4, 5]

    sorted B & A would look like: [1, 1, 2, 2, 3, 3, 4, 4, 5, 5, 6, 7, 8]

    But, as we've said the Time Complexity of this is: O(n + m) which is
    forbidden.

    Anyway, how would we find a median in this sorted array?
    Well, it's the middle value. If number of elements in nums1 + number of
    elements in nums2 is an odd number then the median is:
        std::floor(total / 2)
    else if it is an even number then it's:
        std::floor(total / 2) + std::floor(total / 2) + 1

    Or in other words if total number of elements is odd then that means that
    there are equal number on the left of the median element as the number of
    elements on the right of the median element.

    In this example:
        [1, 1, 2, 2, 3, 3, 4, 4, 5, 5, 6, 7, 8]
         #  #  #  #  #  #     $  $  $  $  $  $

    There are total of 13 elements.
    There are 6 on the left,  designated with character '#'
    There are 6 on the right, designated with character '$'

    Thus, the Median element is at index: 6 and that is number 4.

    If there were an even number of elements, say:
        [1, 1, 2, 2, 3, 3, 4, 4, 5, 5, 6, 7]
         #  #  #  #  #  #  $  $  $  $  $  $

    Then there are total of 12 elements.
    Now we have two halves of size 6.
    We take:
        The max element of the left  half
            +
        The min element of the right half

        And then divide that sum with 2.

    In this example it's:
        Max of the left half:  3
        Min of the right half: 4

        (3 + 4) / 2 = 3.5 // We don't floor the end value!


    So how can we simulate that WITHOUT actually mergign these two arrays?
    How can we simulate that with just original arrays?

    Luckily our two original arrays are in sorted order.


    Let's again look at this example:

    array B: [1, 2, 3, 4, 5, 6, 7, 8]
    array A: [1, 2, 3, 4, 5]

    Total = 13
    Half  = std::floor(total / 2) = 6

    When we talk about partitioning, we want our left partition to be rougly
    equal to Half.

    So the most intuitive way to do this is:
        let's get half of the elements of, let's say, array A.
        Let's initialize L(left pointer) and R(right pointer) at the beginning
        and the end of the array, respectively.

    array A: [1, 2, 3, 4, 5]
              L           R

    We know that the middle is going to be at index: 2. So:

                    m
    array A: [1, 2, 3, 4, 5]
              L           R

    Basically what that means is that our left partition is going to look like
    this:
               m
        [1, 2, 3]
         L

    Obviously we can increasing by adding an element and we can remove it by
    removing an element.
    Anyway, now our left partition have 3 elements in it.

    Now, can we repeat that same process on the array B?
        array B: [1, 2, 3, 4, 5, 6, 7, 8]

    Well, we can but we don't need to. Look at this:
        Half is equal to 6.
        Left partition is of size 3.

        So the left partition of the other array is going to be equal to:
            Half - size of Left partition in array A
        which also ends up being size 3.

    So if we run a Binary search on this one array, A in our case, we can
    compute size of the right partition for the second array. We can compute it
    using our "Half" value.

    So Left parition in array A is:
               m
        [1, 2, 3]
         L

    And left partition in array B: // In this example it has same values
               m
        [1, 2, 3]
         L


    Now, how do we know if we've found the correct left partition or not?
    Well, we want them in order right?
    We already know that this element 3 in array A:

                        #
        array A: [1, 2, 3, 4, 5]
                  L           R

    less than or equal to the element that comes after it, which is 4 in this
    example, that is what sorted order means.

    And we also know that this element 3 in array B:

                        #
        array B: [1, 2, 3, 4, 5, 6, 7, 8]

    is less than or equal to, to the element of the right of it, because the
    B array is also in the sorted order.

    But, here comes the tricky part, we wanto to make sure that the left
    partition is less than every element in the ENTIRE right paritition(which
    includes all of the elements that are not a part of the Left partition in
    both arrays).

    So the rigth partition in array B is:
        [4, 5, 6, 7, 8]

    and the right partition in array A is:
        [4, 5]

    So how can we determine if the Left Part is less than or equal to the
    Right partition?

    Well we've already proved that the last element of the left partition in
    each array is less than or equal to the very next element in the array,
    however we also want to make sure that the max element of the Left
    partition in array B is also less than or equal to the first element of the
    Right partition in array A.

    And vice versa. The max element of the Left partition in array A is also
    less than or equal to the first element of the Right partition in array B.

    Let's visual that:

    array B: [1, 2, 3, 4, 5, 6, 7, 8]
              #  #  #  ~  ~  ~  ~  ~
                    |
                    ----  3 has to be <= 4
                       |
                       v
    array A: [1, 2, 3, 4, 5]
              #  #  #  ~  ~

    # is Left  partition
    ~ is right partition


    Also:

    array B: [1, 2, 3, 4, 5, 6, 7, 8]
              #  #  #  ~  ~  ~  ~  ~
                       ^
                       |
                    ----  3 has to be <= 4
                    |
                    |
    array A: [1, 2, 3, 4, 5]
              #  #  #  ~  ~

    # is Left  partition
    ~ is right partition

    Then we are sure that the Left partition is <= Right partition or that
    the Left partition is rightly divided.

    After that we check if the total amount of elements is even or odd.
    If it's an odd then:
        std:min( min element of Right partition of array B,
                 min element of Right partition of array A)
        // In this example it could be either of the two 4's since those two
        are equal.


    else // Total amount of numbers is even
        max element of the entire Left  partition
          +
        min element of the entire Right partition

        divided by 2.

        // In this example(the one without the 8) (3 + 4) / 2 = 3.5



    That's basically it. However this example was too easy, so try to simulate
    this example:


    array B: [1, 2, 3, 4, 5, 6, 7, 8]
    array A: [1, 2, 3, 4]

    Total = 12
    Half = 6

    array A:
                 m
    array A: [1, 2, 3, 4]
              L        R

    So Left partitoin of array A:
                m
    Left A: [1, 2]
             L

    So the size is 2. Remember how we get the left partition of the other
    array?

    Half - 2 => 6 - 2 = 4

                       m
    array B: [1, 2, 3, 4, 5, 6, 7, 8]

                       m
    Left  B: [1, 2, 3, 4]

    We check those crisscross "<="s.
    max element of Left of array A is 2 which is indeed <= than 5 which is
    the minimum element of the Left partition of array B.

    However, max element of Left of array B is 4 which isn't <= than 3 which is
    the minimum element of the Right partition of array A, then in that case
    our left partition of array A is NOT correct in this case.

    So now we have to update the L and R pointers in array A and do a binary
    search all over again. Now L becomes index:
        m + 1
    and then we do a binary search again.


    array A:
                    m
    array A: [1, 2, 3, 4]
                    L  R

    So now our Left partition of array A becomes:
                   m
    Left A: [1, 2, 3]
                   L

    And then again we compute the Left partition of array B, since we have
    the new size of Left partition of array A. So now:
        Half - 3 = 3

                    m
    array B: [1, 2, 3, 4, 5, 6, 7, 8]

    Left  B: [1, 2, 3]

    Now let's check if we've partitioned this correctly by doing a crisscross
    comparison:
        Now we see that the partitioning was successfull


    Now we do this:
    We check if the total amount of elements is even or odd. 12 in this case.

    If it's an odd then:
        std:min( min element of Right partition of array B,
                 min element of Right partition of array A)
        are equal.


    else // Total amount of numbers is even
        max element of the entire Left  partition
          +
        min element of the entire Right partition

        divided by 2.


    There's one more thing we have to notice. There could be, theoretically
    an edge case in which we end up having Left partition of array A be of
    size 0 and Left partition of array B be of size 6.

    Now, since we have to do the crisscross comparison, we have to assume that
    the element before the 0th is -infinity(INT_MIN) and the element after
    the last one in the array +infinity(INT_MAX).

    That's the whole idea.

*/

/* Time  Beats: 97.61% */
/* Space Beats: 91.10% */

/* Time  Complexity: O(log(min(m, n))) */
/* Space Complexity: O(1) */
class Solution {
public:
    double findMedianSortedArrays(std::vector<int>& nums1, std::vector<int>& nums2)
    {
        int A = nums1.size();
        int B = nums2.size();

        if(A > B)
            return findMedianSortedArrays(nums2, nums1);

        int total = A + B;

        int left  = 0;
        int right = A; // A is the shorter one

        while(left <= right)
        {
            int i = (right - left) / 2 + left;
            int j = (total + 1) / 2 - i;

            int A_left  = (i == 0) ? INT_MIN : nums1[i - 1];
            int A_right = (i == A) ? INT_MAX : nums1[i];
            int B_left  = (j == 0) ? INT_MIN : nums2[j - 1];
            int B_right = (j == B) ? INT_MAX : nums2[j];

            if(A_left <= B_right && B_left <= A_right)
            {
                if(total & 1) // Odd
                    return (double) std::max(A_left, B_left);
                else // Even
                    return (double)(std::max(A_left,B_left) + std::min(A_right,B_right))/2;
            }
            else if(A_left > B_right)
                right = i - 1;
            else
                left = i + 1;
        }

        return -1.0;
    }
};


int
main()
{
    Solution sol;

    /* Example 1 */
    // std::vector<int> nums1 = {1, 3};
    // std::vector<int> nums2 = {2};

    /* Example 2 */
    // std::vector<int> nums1 = {1, 2};
    // std::vector<int> nums2 = {3, 4};

    /* Example 3 */
    // std::vector<int> nums1 = {1, 2, 3, 4, 5, 6, 7, 8};
    // std::vector<int> nums2 = {1, 2, 3, 4, 5};

    /* Example 4 */
    std::vector<int> nums1 = {1, 2, 3, 4, 5, 6, 7, 8};
    std::vector<int> nums2 = {1, 2, 3, 4};

    std::cout << "\n\t===================================";
    std::cout << "\n\t=== MEDIAN OF TWO SORTED ARRAYS ===";
    std::cout << "\n\t===================================\n";


    /* Write Input */
    bool first = true;
    std::cout << "\n\tNums 1: [";
    for (auto x: nums1)
    {
        if (!first)
            std::cout << ", ";

        std::cout << x;
        first = false;
    }
    std::cout << "]";

    first = true;
    std::cout << "\n\tNums 2: [";
    for (auto x: nums2)
    {
        if (!first)
            std::cout << ", ";

        std::cout << x;
        first = false;
    }
    std::cout << "]\n";

    /* Solution */
    double output = sol.findMedianSortedArrays(nums1, nums2);

    /* Write Output */
    printf("\n\tOutput: %lf\n\n", output);
    // std::cout << "\n\tOutput: " << output << "\n\n";

    return 0;
}
