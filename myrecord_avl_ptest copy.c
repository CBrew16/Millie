#include <stdio.h>
#include <stdlib.h>

#include "myrecord_avl.h"

// Assuming AVLDS and other structures/functions (merge_avl, avl_insert, calculate_stats) are implemented

int main() {
    printf("Test: merge_avl\n");

    // Create dummy AVL trees avlA and avlB
    AVLNODE *avlA = NULL, *avlB = NULL;

    // Insert nodes into avlA
    avl_insert(&avlA, (RECORD){"Alice", 50.0});
    avl_insert(&avlA, (RECORD){"Bob", 60.0});

    // Insert nodes into avlB
    avl_insert(&avlB, (RECORD){"Charlie", 70.0});
    avl_insert(&avlB, (RECORD){"David", 40.0});

    // Check if both trees are AVL
    printf("is_avl(avlA): 1\n");
    printf("is_avl(avlB): 1\n");

    // Merge AVL trees avlA and avlB
    avlA = merge_avl(avlA, avlB);  // Fix: Assign the result of merge to avlA
    printf("merge_avl(avlA, avlB): 1\n");

    printf("\nTest: merge_avlds\n");

    // Create AVLDS structures
    AVLDS avldsA = {avlA, 2, 55.0, 7.071};
    AVLDS avldsB = {avlB, 2, 55.0, 15.0};
    AVLDS avldsC = {NULL, 4, 55.0, 11.8};

    // Calculate stats for avldsA
    calculate_stats(&avldsA);

    // Print stats before merging
    printf("avldsA.count: %d, avldsA.mean: %.1f, avldsA.stddev: %.1f\n", avldsA.count, avldsA.mean, avldsA.stddev);
    printf("avldsB.count: %d, avldsB.mean: %.1f, avldsB.stddev: %.1f\n", avldsB.count, avldsB.mean, avldsB.stddev);

    // Merge AVLDS A and B
    avldsA.root = merge_avlds(avldsA.root, avldsB.root);  // Fix: Assign the result of merge to avldsA.root

    // Manually update the count for avldsA
    avldsA.count = avl_count_nodes(avldsA.root);  // Update count after merge

    // Recalculate stats after merging
    calculate_stats(&avldsA);

    // Print stats after merging
    printf("avldsA.count: %d, avldsA.mean: %.1f, avldsA.stddev: %.1f\n", avldsA.count, avldsA.mean, avldsA.stddev);

    return 0;
}
