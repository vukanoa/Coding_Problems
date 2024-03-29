#include <iostream>
#include <vector>
#include <unordered_map>
#include <unordered_set>

/*
    ============
    === EASY ===
    ============

    ===========================
    219) Contains Duplicate
    ===========================

    ============
    Description:
    ============

    Given an integer array nums and an integer k, return true if there are two
    distinct indices i and j in the array such that nums[i] == nums[j] and
    abs(i - j) <= k.

    =================================================================
    FUNCTION: bool containsNearbyDuplicate(vector<int>& nums, int k);
    =================================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: nums = [1,2,3,1], k = 3
    Output: true

    --- Example 2 ---
    Input: nums = [1,0,1,1], k = 1
    Output: true

    --- Example 3 ---
    Input: nums = [1,2,3,1,2,3], k = 2
    Output: false


    *** Constraints ***
    1 <= nums.length <= 10^5
    -10^9 <= nums[i] <= 10^9
    0 <= k <= 10^5

*/

/*
    ------------
    --- IDEA ---
    ------------

    The very first observation that hints to us that this is a Sliding Window
    problem is right in front of you - In the Description.

    It says:"... array such that ... and abs(i - j) <= k"

    Since "abs(i - j)" is a range(window), it is at least possible that this
    may, in fact, be the Sliding Windows problem. So let's check if we can
    indeed solve it in an efficient manner using this technique.

    What they are asking us to do is to find 2 **distinct** elements, within
    the range(window) that are equal.

    The length of the window is designated by variable 'k', but that's not
    actually true. It's "k + 1" since the condition that must NOT be satisfied
    is (abs(i - j) > k), therefore, if, say, k = 2 then a window where:

        i = 5
        j = 7

    is considered valid, but you can clearly see that it is consisted not of 2,
    but of 3 elements, at indices: 5, 6 and 7.
    Therefore the length of the window is not 'k', but "k + 1".

    So, since we have to "move the window" in order to check all the elements,
    we only need to consider the elements that are currently within the window.

    Also, it's important to note that we don't necessarily have to check every
    single element in the array, as we may satisfy the given condition and
    return true before we reach the end.

    As we've said - We have to "move the window" and check if there are two of
    the same values within that range(window) and if there are we immediately
    stop by returning true.

    However, if we do not find two of the same values within the current window
    then we have to add the next element to the window. But, here is the crux
    of this problem, we have to check if by adding one more element we'll
    exceed the limit length of our "window" which is, as we've concluded, k+1.

    If adding another element won't exceed the limit length of the window(as we
    may still not have filled the entire window) then immediately check if
    current element is present within the current window.
    If it is:
        return true;
    else:
        just add it to the current window.

    However, if by adding this element we'll exceed the given limit length of
    a window, then we have to pop one. But, which one?

    The one that is the "oldest" in the window, meaning the one that got into
    this current window first.

    How can we determine that?

    If we push elements from left to right, one by one, then the element that
    is "the oldest", or the one that got into this current window first, is the
    leftmost one within the given range(window).

    Now that we understand the crux of this Solution, we have to ask ourselves
    one more question - How can we determine if some element exists within the
    current window?

    Well, we can, obviously, iterate and check if certain element is present,
    however that itself has the Time Complexity of O(n). That means that in
    total, this whole Solution would be O(n^2) which is considered inefficient
    for this problem.

    Is there a way to check if a certain element is present within the current
    window in O(1)?

    Yes it is! By using a Hash Set.

    We are going to push elements, one by one, and if we find out that the one
    we're currently on is out of bound of the current window, then at that
    point we evict the leftmost element in the current window and then check
    if this element that we're on is already present within the window(since
    now we are sure the window is of correct length).

    If it is present, we've satisfied both conditions and thus return true.

    If we find out that by adding the current element we would not exceed the
    limit length of our window then we can immediately proceed to check if the
    current element is present within the window.

    If it is present, as above, we've satisfied both conditions and thus return
    true.

    If it is not, we push this current element to the window. (we made sure we
    can do that by previously evicting the leftmost element if it was
    necessary)

    The code is much easier than the explanation.

*/

/* Time  Beats: 85.22% */
/* Space Beats: 93.51% */

/* Time  Complexity: O(n) */
/* Space Complexity: O(k) */
class Solution {
public:
    bool containsNearbyDuplicate(std::vector<int>& nums, int k)
    {
        if (k == 0)
            return false;

        std::unordered_set<int> window;

        int left  = 0;
        int right = 0;

        while (right < nums.size())
        {
            if (right - left > k)
            {
                window.erase(nums[left]);
                left++;
            }

            if (window.find(nums[right]) != window.end())
                return true;
            else
                window.insert(nums[right]);

            right++;
        }

        return false;
    }
};
