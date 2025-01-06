class Solution:
    def binSearch(self, nums, x):
        low, high = 0, len(nums) - 1
        while low <= high:
            mid = (low + high) // 2
            if nums[mid][1] < x:
                low = mid + 1
            elif nums[mid][1] > x:
                high = mid - 1
            else:
                return mid
        return -1

    def twoSum(self, nums, target):
        tuples = list(enumerate(nums))
        tuples.sort(key=lambda x: x[1])
        for i, x in tuples:
            idx = self.binSearch(tuples, target - x)
            j = tuples[idx][0]
            if idx != -1 and i != j:
                return sorted([i, j])