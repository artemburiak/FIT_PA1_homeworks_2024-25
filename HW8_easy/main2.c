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

void printLL(TSOLDIER* src) {
    TSOLDIER* tmp = src;
    while (tmp != NULL) {
        printf("%d", tmp->m_PersonalID);
        tmp = tmp->m_Next;
        if (tmp != NULL) printf(" -> ");
    }
    printf("\n");
}

void append(TSOLDIER** src, int value) {
    TSOLDIER* newNode = (TSOLDIER*)malloc(sizeof(TSOLDIER));
    newNode->m_PersonalID = value;
    newNode->m_Next = NULL;

    if (*src == NULL) {
        *src = newNode;
    }
    else {
        TSOLDIER* tmp = *src;
        while (tmp->m_Next != NULL) {
            tmp = tmp->m_Next;
        }
        tmp->m_Next = newNode;
    }
}

long long countElements(TSOLDIER* src) {
    long long res = 0;
    while (src != NULL) {
        TSOLDIER* tmp = src->m_Next;
        res++;
        src = tmp;
    }
    return res;
}

TSOLDIER* mergePlatoons(TSOLDIER* p1, TSOLDIER* p2) {
	TSOLDIER* res = NULL;
    while (p1 != NULL || p2 != NULL) {
        if (p1 != NULL) {
            append(&res, p1->m_PersonalID);
            p1 = p1->m_Next;
        }
        if (p2 != NULL) {
            append(&res, p2->m_PersonalID);
            p2 = p2->m_Next;
        }
    }
    return res;
}

void splitPlatoon(TSOLDIER* src, TSOLDIER** p1, TSOLDIER** p2) {
	*p1 = NULL;
	*p2 = NULL;
	long long count = countElements(src)/2;
    TSOLDIER* tmp = src;
    for (int i = 0; i<2; i++) {
        for (long long j = 0; j<count; j++) {
            if (i==0) append(p1, tmp->m_PersonalID);
            else append(p2, tmp->m_PersonalID);
            tmp = tmp->m_Next;
        }
    }
}

void destroyPlatoon(TSOLDIER* src) {
	while (src != NULL) {
        TSOLDIER* tmp = src->m_Next;
        free(src);
        src = tmp;
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
