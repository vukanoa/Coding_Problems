/*
    ==============
    === MEDIUM ===
    ==============

    =============================
    2424) Longest Uploaded Prefix
    =============================

    ============
    Description:
    ============


    You are given a stream of n videos, each represented by a distinct number
    from 1 to n that you need to "upload" to a server. You need to implement a
    data structure that calculates the length of the longest uploaded prefix at
    various points in the upload process.

    We consider i to be an uploaded prefix if all videos in the range 1 to i
    (inclusive) have been uploaded to the server. The longest uploaded prefix
    is the maximum value of i that satisfies this definition.

    Implement the LUPrefix class:

        + LUPrefix(int n) Initializes the object for a stream of n videos.

        + void upload(int video) Uploads video to the server.

        + int longest() Returns the length of the longest uploaded prefix
          defined above.

    ===============================
    CLASS:
    class LUPrefix {
    public:
        LUPrefix(int n) {
            
        }
        
        void upload(int video) {
            
        }
        
        int longest() {
            
        }
    };
    ===============================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input
    ["LUPrefix", "upload", "longest", "upload", "longest", "upload", "longest"]
    [[4], [3], [], [1], [], [2], []]
    Output
    [null, null, 0, null, 1, null, 3]

    Explanation
    LUPrefix server = new LUPrefix(4);   // Initialize a stream of 4 videos.
    server.upload(3);                    // Upload video 3.
    server.longest();                    // Since video 1 has not been uploaded yet, there is no prefix.
                                         // So, we return 0.
    server.upload(1);                    // Upload video 1.
    server.longest();                    // The prefix [1] is the longest uploaded prefix, so we return 1.
    server.upload(2);                    // Upload video 2.
    server.longest();                    // The prefix [1,2,3] is the longest uploaded prefix, so we return 3.


    *** Constraints ***
    1 <= n <= 10^5
    1 <= video <= n
    All values of video are distinct.
    At most 2 * 105 calls in total will be made to upload and longest.
    At least one call will be made to longest.

*/

#include <vector>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Beats: 17.22% */
/* Space Beats: 22.71% */

/* Time  Complexity: O(N) + O(logN) */
/* Space Complexity: O(N)           */
class SegmentTree {
private:
    int n;
    vector<int> seg_tree;

public:
    SegmentTree(int n)
        : n(n)
    {
        seg_tree.resize(4 * n);

        construct_segment_tree(0, 1, n);
    }

    void construct_segment_tree(int idx, int start, int end)
    {
        if (start == end)
        {
            seg_tree[idx] = 0;
            return;
        }

        int mid = start + (end - start) / 2;

        construct_segment_tree(2 * idx + 1, start, mid);
        construct_segment_tree(2 * idx + 2, mid+1, end);

        seg_tree[idx] = seg_tree[2 * idx + 1] +
                        seg_tree[2 * idx + 2];
    }

    void update(int idx, int start, int end, int target_idx)
    {
        if (start == end)
        {
            seg_tree[idx] = 1;
            return;
        }

        int mid = start + (end - start) / 2;

        if (target_idx <= mid)
            update(2 * idx + 1, start, mid, target_idx);
        else
            update(2 * idx + 2, mid+1, end, target_idx);


        seg_tree[idx] = seg_tree[2 * idx + 1] +
                        seg_tree[2 * idx + 2];
    }

    // Find leftmost index that has value 0
    int find_first_zero(int idx, int start, int end)
    {
        if (start == end)
            return start;

        int mid       = start + (end - start) / 2;
        int left_size = mid - start + 1;

        // If left child is NOT completely filled
        if (seg_tree[2 * idx + 1] < left_size)
            return find_first_zero(2 * idx + 1, start, mid);

        return find_first_zero(2 * idx + 2, mid+1, end);
    }

    int longest()
    {
        if (seg_tree[0] == n)
            return n;

        return find_first_zero(0, 1, n) - 1;
    }
};

class LUPrefix {
private:
    int n;
    SegmentTree seg_tree;

public:

    LUPrefix(int n)
        : n(n), seg_tree(n) // Call the constructor, O(N)
    {

    }

    // O(logN)
    void upload(int video)
    {
        seg_tree.update(0, 1, n, video);
    }

    // O(logN)
    int longest()
    {
        return seg_tree.longest();
    }
};
