/*
    ============
    === EASY ===
    ============

    ============================
    3477) Fruits Into Baskets II
    ============================

    ============
    Description:
    ============

    You are given two arrays of integers, fruits and baskets, each of length n
    where fruits[i] represents the quantity of the ith type of fruit, and
    baskets[j] represents the capacity of the jth basket.

    From left to right, place the fruits according to these rules:

        + Each fruit type must be placed in the leftmost available basket with
          a capacity greater than or equal to the quantity of that fruit type.

        + Each basket can hold only one type of fruit.

        + If a fruit type cannot be placed in any basket, it remains unplaced.

    Return the number of fruit types that remain unplaced after all possible
    allocations are made.

    =============================================================================
    FUNCTION: int numOfUnplacedFruits(vector<int>& fruits, vector<int>& baskets);
    =============================================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: fruits = [4,2,5], baskets = [3,5,4]
    Output: 1
    Explanation:
        fruits[0] = 4 is placed in baskets[1] = 5.
        fruits[1] = 2 is placed in baskets[0] = 3.
        fruits[2] = 5 cannot be placed in baskets[2] = 4.

    Since one fruit type remains unplaced, we return 1.



    --- Example 2 ---
    Input: fruits = [3,6,1], baskets = [6,4,7]
    Output: 0
    Explanation:
        fruits[0] = 3 is placed in baskets[0] = 6.

        fruits[1] = 6 cannot be placed in baskets[1] = 4 (insufficient capacity)
                      but can be placed in the next available basket,
                      baskets[2] = 7.

        fruits[2] = 1 is placed in baskets[1] = 4.

    Since all fruits are successfully placed, we return 0.



    *** Constraints ***
    n == fruits.length == baskets.length
    1 <= n <= 100
    1 <= fruits[i], baskets[i] <= 1000

*/

#include <vector>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    Basic Brute-Force.

*/

/* Time  Beats: 100.00% */
/* Space Beats:  53.33% */

/* Time  Complexity: O(N^2) */
/* Space Complexity: O(1) */
class Solution {
public:
    int numOfUnplacedFruits(vector<int>& fruits, vector<int>& baskets)
    {
        const int N = fruits.size();
        int result = N;

        vector<int> taken(N, false);

        for (int i = 0; i < N; i++)
        {
            for (int j = 0; j < N; j++)
            {
                if (taken[j] == false && fruits[i] <= baskets[j])
                {
                    taken[j] = true;
                    result--;

                    break;
                }
            }
        }

        return result;
    }
};




/*
    ------------
    --- IDEA ---
    ------------

    Iterative Segment Tree Implementation.

    TODO

*/

/* Time  Complexity: O(N * logN * logN) */
/* Space Complexity: O(n)               */

/* Time  Beats: 51.50% */
/* Space Beats:  6.51% */

class SegmentTree {
private:
    int n; // Number of Leaf nodes, i.e. Number of Baskets

public:
    vector<int> seg_tree;

    SegmentTree(vector<int> &arr)
    {
        n = arr.size();
        seg_tree.resize(2 * n);
    }

    void construct_segment_tree(vector<int>& arr)
    {
        // Constructing Leaf
        for (int i = 0; i < n; i++)
            seg_tree[n + i] = arr[i];

        // Up to(inclusive) root(i.e. 1), 0 is dummy
        for (int i = n-1; i >= 1; i--)
            seg_tree[i] = max(seg_tree[2 * i], seg_tree[2 * i + 1]);
    }

    void update(int index, int value)
    {
        // Propagate the value from leaf to root(1)
        index += n;
        seg_tree[index] = value;

        // Updating upwards
        index /= 2;
        while (index >= 1) // Because index=0 is a dummy node
        {
            // Update
            seg_tree[index] = max(seg_tree[2 * index    ],
                                  seg_tree[2 * index + 1]);

            index /= 2;
        }
    }

    int query_range_max(int left, int right)
    {
        // Range: [left, right]
        left  += n; // +n means "go to the leaf node of this value at idx left"
        right += n; // +n means "go to the leaf node of this value at idx right"

        int max_value = 0; // Given numbers >= 1, at least set to zero
        while (left <= right)
        {
            if ((left & 1) == 1) // If left is at ODD index
            {
                max_value = max(max_value, seg_tree[left]);
                left++;
            }

            if ((right & 1) == 0) // If right is at EVEN index
            {
                max_value = max(max_value, seg_tree[right]);
                right--;
            }

            // It's guaranteed once left==right, a last max_value accounting
            // will be done from either of the two above if bodies.
            // Then left becomes GREATER(>) than right and terminates
            left  /= 2;
            right /= 2;
        }

        return max_value;
    }
};

class Solution_Seg {
public:
    int numOfUnplacedFruits(vector<int>& fruits, vector<int>& baskets)
    {
        const int N = baskets.size();

        SegmentTree segment_tree(baskets);
        segment_tree.construct_segment_tree(baskets);

        int unplaced = 0;

        for (int curr_fruit_freq : fruits)
        {
            // If EVERY basket is LESS than curr_fruit_freq, then it's unplaced
            if (segment_tree.query_range_max(0, N-1) < curr_fruit_freq)
            {
                unplaced++;
            }
            else // Find the leftmost leaf
            {
                /*
                   Binary Sarch

                   However, the query_range_max is O(logN), so in total it's
                   O( (logN)^2 )

                */
                int low  = 0;   // Inclusive
                int high = N-1; // Inclusive

                while (low < high)
                {
                    int mid = low + (high - low) / 2;

                    if (segment_tree.query_range_max(low, mid) < curr_fruit_freq)
                        low = mid+1;
                    else
                        high = mid;
                }

                // Mark as "taken", i.e. set Leaf node at idx "low" 0 and
                // propagate to update
                segment_tree.update(low, 0);
            }
        }

        return unplaced;
    }
};
