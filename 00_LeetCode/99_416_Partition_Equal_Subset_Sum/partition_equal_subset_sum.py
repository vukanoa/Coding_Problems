# Same Idea, for some reason this is much faster(Have to figure out why)
# Time Beats: 87.38
# Space Beats: 62.14%
class Solution(object):
    def canPartition(self, nums):
        if sum(nums) % 2:
                return False;

        dp = set()
        dp.add(0)
        target = sum(nums) // 2

        for i in range(len(nums) - 1, -1, -1):
            nextDP = set()
            for t in dp:
                    if (t + nums[i]) == target:
                        return True;

                    nextDP.add(t + nums[i])
                    nextDP.add(t)
            dp = nextDP

        return True if target in dp else False


