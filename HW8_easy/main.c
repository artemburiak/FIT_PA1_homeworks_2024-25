#ifndef __PROGTEST__
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

typedef struct TSoldier
{
  struct TSoldier   * m_Next;
  int                 m_PersonalID;
  char                m_SecretRecord[64];
} TSOLDIER;

#endif /* __PROGTEST__ */

TSOLDIER *mergePlatoons(TSOLDIER *p1, TSOLDIER *p2) {
    TSOLDIER *mergedHead = NULL;
    TSOLDIER **current = &mergedHead;

    while (p1 || p2) {
        if (p1) {
            *current = p1;
            current = &((*current)->m_Next);
            p1 = p1->m_Next;
        }
        if (p2) {
            *current = p2;
            current = &((*current)->m_Next);
            p2 = p2->m_Next;
        }
    }
    *current = NULL;
    return mergedHead;
}

void splitPlatoon(TSOLDIER *src, TSOLDIER **p1, TSOLDIER **p2) {
    TSOLDIER *fast = src;
    TSOLDIER *slow = src;
    TSOLDIER *prev = NULL;

    // Use the slow and fast pointer technique
    while (fast && fast->m_Next) {
        fast = fast->m_Next->m_Next;
        prev = slow;
        slow = slow->m_Next;
    }

    // Split the list into two halves
    if (prev) {
        prev->m_Next = NULL; // End the first half
    }

    *p1 = src;  // First half starts at the original head
    *p2 = slow; // Second half starts at `slow`
}



void destroyPlatoon(TSOLDIER *src) {
    while (src) {
        TSOLDIER *next = src->m_Next;
        free(src);
        src = next;
    }
}

#ifndef __PROGTEST__
TSOLDIER         * createSoldier     ( int               id,
                                       TSOLDIER        * next )
{
  TSOLDIER * r = (TSOLDIER *) malloc ( sizeof ( *r ) );
  r -> m_PersonalID = id;
  r -> m_Next = next;
  /* r -> m_SecretRecord will be filled by someone with a higher security clearance */
  return r;  
}
int main ( void )
{
  TSOLDIER * a, *b, *c;
  a = createSoldier ( 0,
        createSoldier ( 1,
          createSoldier ( 2,
            createSoldier ( 3,
              createSoldier ( 4, NULL )))));
  b = createSoldier ( 10,
        createSoldier ( 11,
          createSoldier ( 12,
            createSoldier ( 13,
              createSoldier ( 14, NULL )))));
  c = mergePlatoons ( a, b );
  assert ( c != NULL
           && c -> m_PersonalID == 0
           && c -> m_Next != NULL
           && c -> m_Next -> m_PersonalID == 10
           && c -> m_Next -> m_Next != NULL
           && c -> m_Next -> m_Next -> m_PersonalID == 1
           && c -> m_Next -> m_Next -> m_Next != NULL
           && c -> m_Next -> m_Next -> m_Next -> m_PersonalID == 11
           && c -> m_Next -> m_Next -> m_Next -> m_Next != NULL
           && c -> m_Next -> m_Next -> m_Next -> m_Next -> m_PersonalID == 2
           && c -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next != NULL
           && c -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next -> m_PersonalID == 12
           && c -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next != NULL
           && c -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next -> m_PersonalID == 3
           && c -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next != NULL
           && c -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next -> m_PersonalID == 13
           && c -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next != NULL
           && c -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next -> m_PersonalID == 4
           && c -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next != NULL
           && c -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next -> m_PersonalID == 14
           && c -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next == NULL );
  splitPlatoon ( c, &a, &b );
  assert ( a != NULL
           && a -> m_PersonalID == 0
           && a -> m_Next != NULL
           && a -> m_Next -> m_PersonalID == 10
           && a -> m_Next -> m_Next != NULL
           && a -> m_Next -> m_Next -> m_PersonalID == 1
           && a -> m_Next -> m_Next -> m_Next != NULL
           && a -> m_Next -> m_Next -> m_Next -> m_PersonalID == 11
           && a -> m_Next -> m_Next -> m_Next -> m_Next != NULL
           && a -> m_Next -> m_Next -> m_Next -> m_Next -> m_PersonalID == 2
           && a -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next == NULL );
  assert ( b != NULL
           && b -> m_PersonalID == 12
           && b -> m_Next != NULL
           && b -> m_Next -> m_PersonalID == 3
           && b -> m_Next -> m_Next != NULL
           && b -> m_Next -> m_Next -> m_PersonalID == 13
           && b -> m_Next -> m_Next -> m_Next != NULL
           && b -> m_Next -> m_Next -> m_Next -> m_PersonalID == 4
           && b -> m_Next -> m_Next -> m_Next -> m_Next != NULL
           && b -> m_Next -> m_Next -> m_Next -> m_Next -> m_PersonalID == 14
           && b -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next == NULL );
  destroyPlatoon ( a );
  destroyPlatoon ( b );

  a = createSoldier ( 0,
        createSoldier ( 1,
          createSoldier ( 2, NULL )));
  b = createSoldier ( 10,
        createSoldier ( 11,
          createSoldier ( 12,
            createSoldier ( 13,
              createSoldier ( 14, NULL )))));
  c = mergePlatoons ( a, b );
  assert ( c != NULL
           && c -> m_PersonalID == 0
           && c -> m_Next != NULL
           && c -> m_Next -> m_PersonalID == 10
           && c -> m_Next -> m_Next != NULL
           && c -> m_Next -> m_Next -> m_PersonalID == 1
           && c -> m_Next -> m_Next -> m_Next != NULL
           && c -> m_Next -> m_Next -> m_Next -> m_PersonalID == 11
           && c -> m_Next -> m_Next -> m_Next -> m_Next != NULL
           && c -> m_Next -> m_Next -> m_Next -> m_Next -> m_PersonalID == 2
           && c -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next != NULL
           && c -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next -> m_PersonalID == 12
           && c -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next != NULL
           && c -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next -> m_PersonalID == 13
           && c -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next != NULL
           && c -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next -> m_PersonalID == 14
           && c -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next == NULL );
  splitPlatoon ( c, &a, &b );
  assert ( a != NULL
           && a -> m_PersonalID == 0
           && a -> m_Next != NULL
           && a -> m_Next -> m_PersonalID == 10
           && a -> m_Next -> m_Next != NULL
           && a -> m_Next -> m_Next -> m_PersonalID == 1
           && a -> m_Next -> m_Next -> m_Next != NULL
           && a -> m_Next -> m_Next -> m_Next -> m_PersonalID == 11
           && a -> m_Next -> m_Next -> m_Next -> m_Next == NULL );
  assert ( b != NULL
           && b -> m_PersonalID == 2
           && b -> m_Next != NULL
           && b -> m_Next -> m_PersonalID == 12
           && b -> m_Next -> m_Next != NULL
           && b -> m_Next -> m_Next -> m_PersonalID == 13
           && b -> m_Next -> m_Next -> m_Next != NULL
           && b -> m_Next -> m_Next -> m_Next -> m_PersonalID == 14
           && b -> m_Next -> m_Next -> m_Next -> m_Next == NULL );
  destroyPlatoon ( a );
  destroyPlatoon ( b );

  a = createSoldier ( 0,
        createSoldier ( 1,
          createSoldier ( 2, NULL )));
  b = createSoldier ( 10,
        createSoldier ( 11,
          createSoldier ( 12,
            createSoldier ( 13, NULL ))));
  c = mergePlatoons ( a, b );
  assert ( c != NULL
           && c -> m_PersonalID == 0
           && c -> m_Next != NULL
           && c -> m_Next -> m_PersonalID == 10
           && c -> m_Next -> m_Next != NULL
           && c -> m_Next -> m_Next -> m_PersonalID == 1
           && c -> m_Next -> m_Next -> m_Next != NULL
           && c -> m_Next -> m_Next -> m_Next -> m_PersonalID == 11
           && c -> m_Next -> m_Next -> m_Next -> m_Next != NULL
           && c -> m_Next -> m_Next -> m_Next -> m_Next -> m_PersonalID == 2
           && c -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next != NULL
           && c -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next -> m_PersonalID == 12
           && c -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next != NULL
           && c -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next -> m_PersonalID == 13
           && c -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next == NULL );
  splitPlatoon ( c, &a, &b );
  assert ( a != NULL
           && a -> m_PersonalID == 0
           && a -> m_Next != NULL
           && a -> m_Next -> m_PersonalID == 10
           && a -> m_Next -> m_Next != NULL
           && a -> m_Next -> m_Next -> m_PersonalID == 1
           && a -> m_Next -> m_Next -> m_Next == NULL );
  assert ( b != NULL
           && b -> m_PersonalID == 11
           && b -> m_Next != NULL
           && b -> m_Next -> m_PersonalID == 2
           && b -> m_Next -> m_Next != NULL
           && b -> m_Next -> m_Next -> m_PersonalID == 12
           && b -> m_Next -> m_Next -> m_Next == NULL );
  destroyPlatoon ( a );
  destroyPlatoon ( b );

  return 0;
}
#endif /* __PROGTEST__ */
