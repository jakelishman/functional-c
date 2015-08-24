#include <stdio.h>
#include <string.h>
#include "high_level.h"

#define ARRAY_LENGTH(arr) (sizeof ((arr)) / sizeof ((arr)[0]))
#define STRING_BUF 11

void add (void *acc, const void *num);
void multiply (void *acc, const void *num);
void *int_to_string (const void *num);

int
main (void)
{
    int naturals[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    int state = 0;
    int *output_r, *output_f;
    char **strings = malloc (ARRAY_LENGTH(naturals) * sizeof (*strings));

    output_f = array_fold (naturals, ARRAY_LENGTH(naturals), sizeof (naturals[0]), &add, &state);
    output_r = array_reduce (naturals, ARRAY_LENGTH(naturals), sizeof (naturals[0]), &multiply);
    strings  = array_map (naturals, ARRAY_LENGTH(naturals), sizeof (naturals[0]),
                          sizeof (*strings), &int_to_string);

    printf ("%d\n", *output_f);
    printf ("%d\n", *output_r);
    for (size_t i = 0; i < ARRAY_LENGTH(naturals); i++) printf ("%s\n", strings[i]);

    return 0;
}

void
add (void *acc, const void *num)
{
    int result = *(int *)acc + *(int *)num;
    (void) memcpy (acc, &result, sizeof (int));
}

void
multiply (void *acc, const void *num)
{
    int result = *(int *)acc * *(int *)num;
    (void) memcpy (acc, &result, sizeof (int));
}

void *
int_to_string (const void *num)
{
    char **output = malloc (sizeof (*output));
    *output = malloc (STRING_BUF * sizeof (**output));
    (void) snprintf (*output, STRING_BUF, "string: %2d", *(int *)num);
    return output;
}
