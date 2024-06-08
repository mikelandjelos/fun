/*
 * Implement a function that receives two IPv4 addresses,
 * and returns the number of addresses between them (including the first one, excluding the last one).
 *
 *
 * All inputs will be valid IPv4 addresses in the form of strings.
 * The last address will always be greater than the first one.
 *
 * Examples:
 *
 * - With input "10.0.0.0", "10.0.0.50"  => return   50
 * - With input "10.0.0.0", "10.0.1.0"   => return  256
 * - With input "20.0.0.10", "20.0.1.0"  => return  246
 */

#include <inttypes.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

#define DOT '.'
#define BASE_10 10

// -------------------------------------------------->----------------------------
// SOLUTION
// ------------------------------------------------------------------------------

uint32_t ips_between(const char *start, const char *end)
{
    const char *start_curr = start, *end_curr = end;

    unsigned long start_val, end_val;
    uint32_t difference = 0ul;
    uint32_t weight = (UINT16_MAX + 1) << 8;

    do
    {
        start_val = strtoul(start_curr, NULL, BASE_10);
        end_val = strtoul(end_curr, NULL, BASE_10);

        if (start_val > UINT8_MAX || end_val > UINT8_MAX)
        {
            fprintf(stderr, "Numbers too large: %lu %lu.\n", start_val, end_val);
            exit(EXIT_FAILURE);
        }

        difference += (end_val - start_val) * weight;
        start_curr = strchr(start_curr, DOT);
        end_curr = strchr(end_curr, DOT);

        if (start_curr && *start_curr == DOT)
            start_curr++;

        if (end_curr && *end_curr == DOT)
            end_curr++;

        weight >>= 8;
    } while (start_curr && end_curr);

    return difference;
}

// ------------------------------------------------------------------------------
// TESTING
// ------------------------------------------------------------------------------

void do_test(const char *start, const char *end, uint32_t expected)
{
    uint32_t actual = ips_between(start, end);
    if (actual != expected)
    {
        fprintf(stdout, "for (start = %s ; end = %s) expected %u but got %u\n",
                start, end, expected, actual);
        fflush(stdout);
        exit(EXIT_FAILURE);
    }
}

int main(int argc, char **argv)
{
    do_test("10.0.0.0", "10.0.0.50", 50);
    do_test("20.0.0.10", "20.0.1.0", 246);
    do_test("0.0.0.0", "255.255.255.255", UINT32_MAX);
    return 0;
}