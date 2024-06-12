/*
 * Two Integer Sum:
 * Given an array of integers nums and an integer target, return the indices i and j such that nums[i] + nums[j] == target and i != j.
 * You may assume that every input has exactly one pair of indices i and j that satisfy the condition.
 * Return the answer with the smaller index first.
 *
 * Example 1:
 *  Input: nums = [3,4,5,6], target = 7
 *  Output: [0,1]
 *  Explanation: nums[0] + nums[1] == 7, so we return [0, 1].
 *
 * Example 2:
 *  Input: nums = [4,5,6], target = 10
 *  Output: [0,2]
 *
 * Example 3:
 *  Input: nums = [5,5], target = 10
 *  Output: [0,1]
 *
 * Constraints:
 *  2 <= nums.length <= 1000
 *  -10,000,000 <= nums[i] <= 10,000,000
 *  -10,000,000 <= target <= 10,000,000
 */

#include <iostream>
#include <vector>
#include <unordered_map>
#include "miscellaneous.h"

class Solution
{
public:
    std::vector<int> twoSum(std::vector<int> &nums, int target)
    {
        std::vector<int> foundIndexes;
        std::unordered_map<int, int> differencesFromTarget;

        for (int i = 0; i < nums.size(); ++i)
        {
            const auto &[currentElement, _] = differencesFromTarget.emplace(nums.at(i), i);
            const auto differenceMatchFound = differencesFromTarget.find(target - currentElement->first);

            if (differenceMatchFound != differencesFromTarget.end() && differenceMatchFound->second != i)
            {
                foundIndexes.push_back(differenceMatchFound->second);
                foundIndexes.push_back(i);
                break;
            }
        }

        return foundIndexes;
    }
};

int main(int argc, char **argv)
{
    Solution solution;
    std::vector<int> testcase1 = {3, 4, 5, 6};
    std::vector<int> testcase2 = {4, 5, 6};
    std::vector<int> testcase3 = {5, 5};

    miscellaneous::printVector(solution.twoSum(testcase1, 7), std::cout);
    miscellaneous::printVector(solution.twoSum(testcase2, 10), std::cout);
    miscellaneous::printVector(solution.twoSum(testcase3, 10), std::cout);

    return 0;
}