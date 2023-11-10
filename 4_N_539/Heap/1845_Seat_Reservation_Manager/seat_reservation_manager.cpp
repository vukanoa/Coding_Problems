#include <iostream>
#include <vector>
#include <queue>

/*
    ==============
    === MEDIUM ===
    ==============

    ==============================
    1845) Seat Reservation Manager
    ==============================

    ============
    Description:
    ============

    Design a system that manages the reservation state of n seats that are numbered from 1 to n.

    Implement the SeatManager class:

        SeatManager(int n) Initializes a SeatManager object that will manage n
        seats numbered from 1 to n. All seats are initially available.  int
        reserve() Fetches the smallest-numbered unreserved seat, reserves it,
        and returns its number.  void unreserve(int seatNumber) Unreserves the
        seat with the given seatNumber.


    ===============================
    CLASS:
    class SeatManager {
    public:
        SeatManager(int n) {

        }

        int reserve() {

        }

        void unreserve(int seatNumber) {

        }
    };
    ===============================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input:
    ["SeatManager", "reserve", "reserve", "unreserve", "reserve", "reserve",
    "reserve", "reserve", "unreserve"]
    [[5], [], [], [2], [], [], [], [], [5]]

    Output:
    [null, 1, 2, null, 2, 3, 4, 5, null]


    Explanation
    SeatManager seatManager = new SeatManager(5); // Initializes a SeatManager with 5 seats.
    seatManager.reserve();    // All seats are available, so return the lowest
                                 numbered seat, which is 1.
    seatManager.reserve();    // The available seats are [2,3,4,5], so return
                                 the lowest of them, which is 2.
    seatManager.unreserve(2); // Unreserve seat 2, so now the available seats
                                 are [2,3,4,5].
    seatManager.reserve();    // The available seats are [2,3,4,5], so return
                                 the lowest of them, which is 2.
    seatManager.reserve();    // The available seats are [3,4,5], so return the
                                 lowest of them, which is 3.
    seatManager.reserve();    // The available seats are [4,5], so return the
                                 lowest of them, which is 4.
    seatManager.reserve();    // The only available seat is seat 5, so return 5
    seatManager.unreserve(5); // Unreserve seat 5, so now the available seats
                                 are [5]




    *** Constraints ***
    1 <= n <= 10^5
    1 <= seatNumber <= n
    For each call to reserve, it is guaranteed that there will be at least one unreserved seat.
    For each call to unreserve, it is guaranteed that seatNumber will be reserved.
    At most 105 calls in total will be made to reserve and unreserve.

*/

/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Beats: 40.88% */
/* Space Beats: 56.28% */

/* Time  Complexity: O(n * logn) */
/* Space Complexity: O(n) */
class SeatManager_Inefficient {
public:
    SeatManager(int n)
    {
        for (int i = 1; i <= n; i++)
            seats.push(i);
    }

    int reserve()
    {
        int min = seats.top();
        seats.pop();

        return min;
    }

    void unreserve(int seatNumber)
    {
        seats.push(seatNumber);
    }

private:
    std::priority_queue<int, std::vector<int>, std::greater<int> > seats;
};




/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Beats: 99.19% */
/* Space Beats: 78.45% */

/* Time  Complexity: O(n * logn) */
/* Space Complexity: O(n) */
class SeatManager_Efficient {
public:
    SeatManager(int n) : last_reserved(0) {}

    int reserve()
    {
        if (min_heap.empty())
            return ++last_reserved;
        else
        {
            int seat = min_heap.top();
            min_heap.pop();

            return seat;
        }
    }

    void unreserve(int seatNumber)
    {
        if (seatNumber == last_reserved)
            --last_reserved;
        else
            min_heap.push(seatNumber);
    }

private:
    std::priority_queue<int, std::vector<int>, std::greater<int>> min_heap;
    int last_reserved;
};
