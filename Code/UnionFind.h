/* ========================================================================= *
 * Union find interface:
 * ========================================================================= */

#ifndef _UNIONFIND_H_
#define _UNIONFIND_H_

#include <stdlib.h>

/* Opaque structure */
typedef struct union_find_t UnionFind;

typedef enum {UF_ERROR, UF_MERGED, UF_SAME} ufStatus;


/* ------------------------------------------------------------------------- *
 * Build a union find structure for $n_items$ items (initially each in their
 * respective component).
 *
 * PARAMETERS
 * n_items      Number of items to store in the union find structure
 *
 * NOTE
 * The returned structure should be cleaned with $freeUnionFind$ after
 * usage.
 *
 * RETURN
 * union_find   The created union find structure.
 * ------------------------------------------------------------------------- */
UnionFind* ufCreate(size_t n_items);

/* ------------------------------------------------------------------------- *
 * Free the memory allocated for the union find structure.
 *
 * PARAMETERS
 * union_find   The UnionFind structure
 * ------------------------------------------------------------------------- */
void ufFree(UnionFind* union_find);

/* ------------------------------------------------------------------------- *
 * Merge the components containing the items $item1$ and $item2$.
 *
 * PARAMETERS
 * union_find   The UnionFind structure
 * item1        The item in the first component to merge
 * item2        The item in the second component to merge
 *
 * NOTE
 * Both items should be known by the structure.
 *
 * RETURN
 * status       The resulting status of the merge operation; UF_SAME means
 *              the two items were already in the same component
 * ------------------------------------------------------------------------- */
ufStatus ufUnion(UnionFind* union_find, size_t item1, size_t item2);

/* ------------------------------------------------------------------------- *
 * Search for the component of an item.
 *
 * PARAMETERS
 * union_find   The UnionFind structure
 * item         The item for which the component should be searched
 *
 * NOTE
 * The item should be known by the structure
 *
 * RETURN
 * component    the index of the component where $item$ belongs
  * ------------------------------------------------------------------------- */
size_t ufFind(const UnionFind* union_find, size_t item);

/* ------------------------------------------------------------------------- *
 * Count the number of components.
 *
 * PARAMETERS
 * union_find   The UnionFind structure
 *
 * RETURN
 * count        The number of components
 * ------------------------------------------------------------------------- */
size_t ufComponentsCount(const UnionFind* union_find);

#endif // _UNIONFIND_H_
