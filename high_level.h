#ifndef __HIGH_LEVEL_H
#define __HIGH_LEVEL_H

#include <stdlib.h>
#include <string.h>
#include <stdio.h>

void *array_map    (const void *array, const size_t len, const size_t in_type_size,
                    const size_t out_type_size, void *(mapping (const void *el)));
void *array_mapi   (const void *array, const size_t len, const size_t in_type_size,
                    const size_t out_type_size, void *(mapping (const size_t i, const void *el)));

void  array_iter   (const void *array, const size_t len, const size_t type_size,
                    void (iter (const void *el)));
void  array_iteri  (const void *array, const size_t len, const size_t type_size,
                    void (iter (const size_t i, const void *el)));

void *array_fold   (const void *array, const size_t len, const size_t type_size,
                    void (fold (void *state, const void *el)), void *state);
void *array_foldi  (const void *array, const size_t len, const size_t type_size,
                    void (fold (const size_t i, void *state, const void *el)),
                    void *state);

void *array_reduce (const void *array, const size_t len, const size_t type_size,
                    void (reduction (void *state, const void *el)));

#endif
