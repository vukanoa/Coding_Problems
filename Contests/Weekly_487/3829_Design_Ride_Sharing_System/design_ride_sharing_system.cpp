/*
    ==============
    === MEDIUM ===
    ==============

    ================================
    3829) Design Ride Sharing System
    ================================

    ============
    Description:
    ============


    A ride sharing system manages ride requests from riders and availability
    from drivers. Riders request rides, and drivers become available over time.
    The system should match riders and drivers in the order they arrive.

    Implement the RideSharingSystem class:

        + RideSharingSystem() Initializes the system.

        + void addRider(int riderId) Adds a new rider with the given riderId.

        + void addDriver(int driverId) Adds a new driver with the given driverId.

        + int[] matchDriverWithRider() Matches the earliest available driver
          with the earliest waiting rider and removes both of them from the
          system. Returns an integer array of size 2 where result = [driverId,
          riderId] if a match is made. If no match is available, returns [-1,
          -1].

        + void cancelRider(int riderId) Cancels the ride request of the rider
          with the given riderId if the rider exists and has not yet been
          matched.

    ===============================
    CLASS
    class RideSharingSystem {
    public:
        RideSharingSystem()
        {
            
        }
        
        void addRider(int riderId)
        {

        }
        
        void addDriver(int driverId)
        {

        }
        
        vector<int> matchDriverWithRider()
        {

        }
        
        void cancelRider(int riderId)
        {

        }
    };
    ===============================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input:
    ["RideSharingSystem", "addRider", "addDriver", "addRider", "matchDriverWithRider", "addDriver", "cancelRider", "matchDriverWithRider", "matchDriverWithRider"]
    [[], [3], [2], [1], [], [5], [3], [], []]

    Output:
    [null, null, null, null, [2, 3], null, null, [5, 1], [-1, -1]]

    Explanation
    RideSharingSystem rideSharingSystem = new RideSharingSystem(); // Initializes the system
    rideSharingSystem.addRider(3); // rider 3 joins the queue
    rideSharingSystem.addDriver(2); // driver 2 joins the queue
    rideSharingSystem.addRider(1); // rider 1 joins the queue
    rideSharingSystem.matchDriverWithRider(); // returns [2, 3]
    rideSharingSystem.addDriver(5); // driver 5 becomes available
    rideSharingSystem.cancelRider(3); // rider 3 is already matched, cancel has no effect
    rideSharingSystem.matchDriverWithRider(); // returns [5, 1]
    rideSharingSystem.matchDriverWithRider(); // returns [-1, -1]

    --- Example 2 ---

    --- Example 3 ---

    *** Constraints ***

*/

#include <queue>
#include <unordered_set>
#include <vector>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    This is an almost trivial problem if you know about a basic "queue" data
    structure, however it is a VERY good problem to get familiar with a concept
    of "Lazy Deletion".

    The concept of "Lazy Deletion" is CRUCIAL to "Segment Trees", so it's a
    nice introduction to that concept.

*/

/* Time  Beats: 67.74% */
/* Space Beats: 52.69% */

/* Time  Complexity: O(1) */
/* Space Complexity: O(N) */
class RideSharingSystem {
public:
    RideSharingSystem()
    {
        
    }
    
    void addRider(int riderId)
    {
        queue_riders.push(riderId);
        uset_waiting_riders.insert(riderId);
    }
    
    void addDriver(int driverId)
    {
        queue_drivers.push(driverId);
    }
    
    vector<int> matchDriverWithRider()
    {
        if (queue_drivers.empty() || queue_riders.empty())
            return {-1, -1};

        /* Lazy Deletion */
        while ( ! queue_riders.empty() && uset_cancelled_riders.count(queue_riders.front()))
        {
            uset_cancelled_riders.erase(queue_riders.front());
            queue_riders.pop();
        }

        if (queue_riders.empty())
            return {-1, -1};


        int earliest_driver = queue_drivers.front();
        int earliest_rider  = queue_riders.front();

        
        
        queue_drivers.pop();
        queue_riders.pop();

        uset_waiting_riders.erase(earliest_rider);


        return {earliest_driver, earliest_rider};
    }
    
    void cancelRider(int riderId)
    {
        // If no such riderId exists in "waiting riders", return immediately
        if (uset_waiting_riders.find(riderId) == uset_waiting_riders.end())
            return;

        uset_waiting_riders.erase(riderId);    // Remove
        uset_cancelled_riders.insert(riderId); // Insert
    }

private:
    queue<int> queue_riders;
    queue<int> queue_drivers;

    unordered_set<int> uset_waiting_riders;
    unordered_set<int> uset_cancelled_riders;
};

/**
 * Your RideSharingSystem object will be instantiated and called as such:
 * RideSharingSystem* obj = new RideSharingSystem();
 * obj->addRider(riderId);
 * obj->addDriver(driverId);
 * vector<int> param_3 = obj->matchDriverWithRider();
 * obj->cancelRider(riderId);
 */
