#include <stdint.h>
#include <stdlib.h>

struct ListNode {
    int val;
    struct ListNode *next;
};

// precondition: beg != NULL
uint64_t list_to_int(struct ListNode *beg)
{
    uint64_t ret = 0, ratio = 1, digits = 0;
    
    do {
        ret += beg->val * ratio;
        ratio *= 10;
        digits += 1;
    } while (beg != NULL);
    
    return ret;
}

void free_ListNode(struct ListNode *curr)
{
    while (curr != NULL) {
        struct ListNode *next = curr->next;
        free(curr);
        curr = next;
    }
}

// Only return NULL if any allocation fails.
struct ListNode* int_to_list(uint64_t input)
{
    struct ListNode *ret;
    struct ListNode **next_p = &ret;
    
    do {
        *next_p = (struct ListNode*) malloc(sizeof(struct ListNode));
        
        if (*next_p == NULL) {
            free_ListNode(ret);
            ret = NULL;
            break;
        }
        
        (*next_p)->val = input % 10;
        
        next_p = &((*next_p)->next);
        input /= 10;
    } while(input != 0);
    
    return ret;
}

struct ListNode* addTwoNumbers(struct ListNode* l1, struct ListNode* l2) {
    return int_to_list(list_to_int(l1) + list_to_int(l2));
}
