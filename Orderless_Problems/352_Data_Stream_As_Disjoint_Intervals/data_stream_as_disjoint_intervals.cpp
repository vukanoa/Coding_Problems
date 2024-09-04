#include <iostream>
#include <vector>
#include <set>

/*
    ============
    === HARD ===
    ============

    ======================================
    352) Data Stream as Disjoint Intervals
    ======================================

    ============
    Description:
    ============

    Given a data stream input of non-negative integers a1, a2, ..., an,
    summarize the numbers seen so far as a list of disjoint intervals.

    Implement the SummaryRanges class:

        + SummaryRanges() Initializes the object with an empty stream.

        + void addNum(int value) Adds the integer value to the stream.

        + int[][] getIntervals() Returns a summary of the integers in the
          stream currently as a list of disjoint intervals [starti, endi]. The
          answer should be sorted by starti.

    ===============================
    CLASS:
    class SummaryRanges {
    public:
        SummaryRanges() {

        }

        void addNum(int value) {

        }

        vector<vector<int>> getIntervals() {

        }
    };
    ===============================

     * Your SummaryRanges object will be instantiated and called as such:
     * SummaryRanges* obj = new SummaryRanges();
     * obj->addNum(value);
     * vector<vector<int>> param_2 = obj->getIntervals();


    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input
    ["SummaryRanges", "addNum", "getIntervals", "addNum", "getIntervals", "addNum", "getIntervals", "addNum", "getIntervals", "addNum", "getIntervals"]
    [[], [1], [], [3], [], [7], [], [2], [], [6], []]
    Output
    [null, null, [[1, 1]], null, [[1, 1], [3, 3]], null, [[1, 1], [3, 3], [7, 7]], null, [[1, 3], [7, 7]], null, [[1, 3], [6, 7]]]

    Explanation
    SummaryRanges summaryRanges = new SummaryRanges();
    summaryRanges.addNum(1);      // arr = [1]
    summaryRanges.getIntervals(); // return [[1, 1]]
    summaryRanges.addNum(3);      // arr = [1, 3]
    summaryRanges.getIntervals(); // return [[1, 1], [3, 3]]
    summaryRanges.addNum(7);      // arr = [1, 3, 7]
    summaryRanges.getIntervals(); // return [[1, 1], [3, 3], [7, 7]]
    summaryRanges.addNum(2);      // arr = [1, 2, 3, 7]
    summaryRanges.getIntervals(); // return [[1, 3], [7, 7]]
    summaryRanges.addNum(6);      // arr = [1, 2, 3, 6, 7]
    summaryRanges.getIntervals(); // return [[1, 3], [6, 7]]


    *** Constraints ***
    0 <= value <= 10^4
    At most 3 * 104 calls will be made to addNum and getIntervals.
    At most 10^2 calls will be made to getIntervals.

*/

using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Beats: 100.00% */
/* Space Beats:  61.67% */

/* Time  Complexity: O(n) */
/* Space Complexity: O(n) */
class SummaryRanges {
public:
    set<int> set;

    SummaryRanges() {}

    // O(logn)
    void addNum(int value)
    {
        set.insert(value);
    }

    // O(n)
    vector<vector<int>> getIntervals()
    {
        if (set.empty())
            return {};

        vector<vector<int>> result;

        int start = -1;
        int last  = -1;

        for (int val : set)
        {
            if (start < 0)
            {
                start = last = val;
            }
            else if (val - last==1)
            {
                last = val;
            }
            else
            {
                result.push_back({start, last});
                start = last = val;
            }
        }

        result.push_back({start, last});

        return result;
    }
};

/**
 * Your SummaryRanges object will be instantiated and called as such:
 * SummaryRanges* obj = new SummaryRanges();
 * obj->addNum(value);
 * vector<vector<int>> param_2 = obj->getIntervals();
 */
