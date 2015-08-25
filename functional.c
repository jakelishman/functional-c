#include "functional.h"

// Helper for array mapping.
void
array_map_helper (void *output, const void *array, const size_t len,
                  const size_t in_type_size, const size_t out_type_size,
                  void * (mapping (const void *el)))
{
    if (len == 0) return;
    void *tmp = (*mapping)(array);
    memcpy (output, tmp, out_type_size);
    free (tmp);
    array_map_helper (output + out_type_size, array + in_type_size, len - 1,
                      in_type_size, out_type_size, mapping);
}

// Apply a mapping function to every element in an array, and return a new array
// containing those values.
void *
array_map (const void *array, const size_t len, const size_t in_type_size,
           const size_t out_type_size, void * (mapping (const void *el)))
{
    void *output = malloc (len * out_type_size);
    array_map_helper (output, array, len, in_type_size, out_type_size, mapping);
    return output;
}

// Helper for indexed array mapping.
void
array_mapi_helper (const size_t i, void *output, const void *array,
                   const size_t len, const size_t in_type_size, const size_t out_type_size,
                   void * (mapping (const size_t i, const void *el)))
{
    if (len == 0) return;
    void *tmp = (*mapping)(i, array);
    memcpy (output, tmp, out_type_size);
    free (tmp);
    array_mapi_helper (i + 1, output + out_type_size, array + in_type_size,
                       len - 1, in_type_size, out_type_size, mapping);
}

// Apply a mapping function to every element in an array, also passing the index
// of the element we're mapping, and return an array of the result.
void *
array_mapi (const void *array, const size_t len, const size_t in_type_size,
            const size_t out_type_size, void * (mapping (const size_t i, const void *el)))
{
    void *tmp;
    void *output = malloc (len * out_type_size);
    for (size_t i = 0; i < len; i++) {
        tmp = (*mapping)(i, array + (i * in_type_size));
        memcpy (output + (i * out_type_size), tmp, out_type_size);
        free (tmp);
    }
    return output;
}

// Iterate through an array, performing a function on each element.
void
array_iter (const void *array, const size_t len, const size_t type_size,
            void (iter (const void *)))
{
    if (len == 0) return;
    (*iter)(array);
    array_iter (array + type_size, len - 1, type_size, iter);
}

// Helper for indexed iteration.
void
array_iteri_helper (const size_t i, const void *array, const size_t len,
                    const size_t type_size,
                    void (iter (const size_t i, const void *el)))
{
    if (len == 0) return;
    (*iter)(i, array);
    array_iteri_helper (i + 1, array + type_size, len - 1, type_size, iter);
}

// Iterate through an array, performing a function on each element with the
// index of the element passed as well.
void
array_iteri (const void *array, const size_t len, const size_t type_size,
             void (iter (const size_t i, const void *el)))
{
    return array_iteri_helper (0, array, len, type_size, iter);
}

// Fold an array into one value, given a starting state of that value, and a
// function which folds each element into the state. Returns a pointer to the
// state variable.
void *
array_fold  (const void *array, const size_t len, const size_t type_size,
             void (fold (void *state, const void *el)), void *state)
{
    if (len == 0) return state;
    (*fold)(state, array);
    return array_fold (array + type_size, len - 1, type_size, fold, state);
}

// Helper for indexed array folding.
void *
array_foldi_helper (const size_t i, const void *array, const size_t len,
                    const size_t type_size,
                    void (fold (const size_t i, void *state, const void *el)),
                    void *state)
{
    if (len == 0) return state;
    (*fold)(i, state, array);
    return array_foldi_helper (i + 1, array + type_size, len - 1, type_size, fold, state);
}

// Fold an array into one value, given a starting state of that value, and a
// function which folds each element into the state, given the index of the
// value in the array. Returns a pointer to the state variable.
void *
array_foldi (const void *array, const size_t len, const size_t type_size,
             void (fold (const size_t i, void *state, const void *el)),
             void *state)
{
    return array_foldi_helper (0, array, len, type_size, fold, state);
}

// Reduce an array into one variable. Fails (returns NULL), if the length is
// equal to zero.
void *
array_reduce (const void *array, const size_t len, const size_t type_size,
              void (reduction (void *state, const void *el)))
{
    if (len == 0) return NULL;
    void *state = malloc (type_size);
    state = memcpy (state, array + 0, type_size);
    return array_fold (array + type_size, len - 1, type_size, reduction, state);
}
