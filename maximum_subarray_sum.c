/*  The maximum sum subarray problem consists in finding the maximum sum of a contiguous subsequence in an array or list of integers:
 *      maxSequence({-2, 1, -3, 4, -1, 2, 1, -5, 4}, 9) => should return 6, from sub-array: {4, -1, 2, 1}
 *  Easy case is when the list is made up of only positive numbers and the maximum sum is the sum of the whole array. If the list is made up of only negative numbers, return 0 instead.
 *  Empty list is considered to have zero greatest sum. Note that the empty list or array is also a valid sublist/subarray.
 */

#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>
#include <criterion/criterion.h>

// ------------------------------------------------------------------------------
// SOLUTION 1 - Naive - O(n^2) time, O(1) space
// ------------------------------------------------------------------------------

int max_contiguous_sum_naive(const int *array, long n)
{
    if (n == 0)
        return 0;
    int max_sum = INT32_MIN;
    for (int i = 0; i < n - 1; ++i)
    {
        int current_sum = array[i];

        if (array[i] > max_sum)
            max_sum = array[i];

        for (int j = i + 1; j < n; ++j)
        {
            current_sum += array[j];
            if (current_sum > max_sum)
                max_sum = current_sum;
        }
    }
    return max_sum;
}

// ----------------------------------------------------------------------------------
// SOLUTION 2 - Recursive
//  - O(logn) time (height of the recursive tree)
//  - O(1) space (not including the call stack)
// ----------------------------------------------------------------------------------

int __max_contiguous_sum_crossing_middle(const int *array, long l, long m, long r)
{

    int max_left_sum = INT32_MIN;
    int current_left_sum = 0;

    for (int i = m; i >= l; --i)
    {
        current_left_sum += array[i];
        if (current_left_sum > max_left_sum)
            max_left_sum = current_left_sum;
    }

    int max_right_sum = INT32_MIN;
    int current_right_sum = 0;

    for (int i = m + 1; i <= r; ++i)
    {
        current_right_sum += array[i];
        if (current_right_sum > max_right_sum)
            max_right_sum = current_right_sum;
    }

    return max_left_sum + max_right_sum;
}

int __max_contiguous_sum_recursive(const int *array, long l, long r)
{
    if (l == r)
        return array[l];

    long m = (l + r) / 2;

    int max_left_sum = __max_contiguous_sum_recursive(array, l, m);
    int max_right_sum = __max_contiguous_sum_recursive(array, m + 1, r);
    int max_crossing_sum = __max_contiguous_sum_crossing_middle(array, l, m, r);

    return max_left_sum > max_right_sum
               ? (max_left_sum > max_crossing_sum ? max_left_sum : max_crossing_sum)
               : (max_right_sum > max_crossing_sum ? max_right_sum : max_crossing_sum);
}

int max_contiguous_sum_recursive(const int *array, long n)
{
    if (n == 0)
        return 0;
    return __max_contiguous_sum_recursive(array, 0, n - 1);
}

// ----------------------------------------------------------------------------------
// SOLUTION 3 - Dynamic programming
//  - O(n) time
//  - O(n) space
// ----------------------------------------------------------------------------------

int max_contiguous_sum_dynamic(const int *array, long n)
{
    if (n == 0)
        return 0;

    int *max_sums = (int *)malloc(sizeof(int) * n);
    max_sums[0] = array[0];

    for (int i = 1; i < n; ++i)
        max_sums[i] = max_sums[i - 1] > 0
                          ? max_sums[i - 1] + array[i]
                          : array[i];

    int max_sum = max_sums[0];

    for (int i = 1; i < n; ++i)
        max_sum = max_sum > max_sums[i]
                      ? max_sum
                      : max_sums[i];

    free(max_sums);

    return max_sum;
}

// ----------------------------------------------------------------------------------
// SOLUTION 4 - Kadane's algorithm
//  - O(n) time
//  - O(1) space
// ----------------------------------------------------------------------------------

int max_contiguous_sum_kadane(const int *array, long n)
{
    if (n == 0)
        return 0;

    int current_max_sum = array[0];
    int overall_max_sum = array[0];

    for (int i = 1; i < n; ++i)
    {
        current_max_sum = array[i] > current_max_sum + array[i]
                              ? array[i]
                              : current_max_sum + array[i];
        if (current_max_sum > overall_max_sum)
            overall_max_sum = current_max_sum;
    }

    return overall_max_sum;
}

// ------------------------------------------------------------------------------
// TESTING
// ------------------------------------------------------------------------------

int maxSequence(const int *array, long n)
{
    int max_sum = max_contiguous_sum_kadane(array, n);
    return max_sum > 0 ? max_sum : 0;
}

Test(Sample_Tests, should_work_on_an_empty_array)
{
    const int array[0] = {};
    int submitted = maxSequence(array, 0);
    int expected = 0;
    cr_assert_eq(expected, submitted, "Expected: %d  Submitted %d\n", expected, submitted);
}

Test(Sample_Tests, should_work_on_this_example)
{
    const int array[9] = {-2, 1, -3, 4, -1, 2, 1, -5, 4};
    int submitted = maxSequence(array, 9);
    int expected = 6;
    cr_assert_eq(expected, submitted, "Expected: %d  Submitted %d\n", expected, submitted);
}

Test(Sample_Tests, should_work_on_one_element)
{
    const int array[] = {11};
    int submitted = maxSequence(array, 1);
    int expected = 11;
    cr_assert_eq(expected, submitted, "Expected: %d  Submitted %d\n", expected, submitted);
}

Test(Sample_Tests, should_work_on_negative_elements)
{
    const int array[] = {-5, -4, -3, -2, -1, 0};
    int submitted = maxSequence(array, 6);
    int expected = 0;
    cr_assert_eq(expected, submitted, "Expected: %d  Submitted %d\n", expected, submitted);
}