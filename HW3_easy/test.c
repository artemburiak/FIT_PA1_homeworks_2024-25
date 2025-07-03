#ifndef __PROGTEST__
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <assert.h>
#include <stdbool.h>
#endif /* __PROGTEST__ */

int zerosAtEnd(long long x, long long base) {
    int zeroCount = 0;
    while (x % base == 0) {
        zeroCount++;
        x /= base;
    }
    return zeroCount;
}

long long findRadix(long long x) {
    if (x < 2) return -1;
    
    long long bestRadix = 2;
    int maxZeros = zerosAtEnd(x, 2);
    
    for (long long base = 3; base <= x; base++) {
        int zeroCount = zerosAtEnd(x, base);
        if (zeroCount > maxZeros || (zeroCount == maxZeros && base > bestRadix)) {
            maxZeros = zeroCount;
            bestRadix = base;
        }
    }
    return bestRadix;
}

int countZeros(long long x) {
    if (x < 2) return -1;
    
    int maxZeros = zerosAtEnd(x, 2);
    
    for (long long base = 3; base <= x; base++) {
        int zeroCount = zerosAtEnd(x, base);
        if (zeroCount > maxZeros) {
            maxZeros = zeroCount;
        }
    }
    return maxZeros;
}

bool findRadixZeros(long long x, long long * radix, int * zeros) {
    if (x < 2) return false;
    
    *radix = 2;
    *zeros = zerosAtEnd(x, 2);
    
    for (long long base = 3; base <= x; base++) {
        int zeroCount = zerosAtEnd(x, base);
        if (zeroCount > *zeros || (zeroCount == *zeros && base > *radix)) {
            *zeros = zeroCount;
            *radix = base;
        }
    }
    return true;
}

#ifndef __PROGTEST__
int main() {
    long long radix;
    int zeros;
    assert ( findRadix ( 2 ) == 2 );
    assert ( countZeros ( 2 ) == 1 );
    assert ( findRadixZeros ( 2, &radix, &zeros )
             && radix == 2
             && zeros == 1 );
    assert ( findRadix ( 16 ) == 2 );
    assert ( countZeros ( 16 ) == 4 );
    assert ( findRadixZeros ( 16, &radix, &zeros )
             && radix == 2
             && zeros == 4 );
    assert ( findRadix ( 17 ) == 17 );
    assert ( countZeros ( 17 ) == 1 );
    assert ( findRadixZeros ( 17, &radix, &zeros )
             && radix == 17
             && zeros == 1 );
    assert ( findRadix ( 36 ) == 6 );
    assert ( countZeros ( 36 ) == 2 );
    assert ( findRadixZeros ( 36, &radix, &zeros )
             && radix == 6
             && zeros == 2 );
    assert ( findRadix ( 100 ) == 10 );
    assert ( countZeros ( 100 ) == 2 );
    assert ( findRadixZeros ( 100, &radix, &zeros )
             && radix == 10
             && zeros == 2 );
    assert ( findRadix ( 216 ) == 6 );
    assert ( countZeros ( 216 ) == 3 );
    assert ( findRadixZeros ( 216, &radix, &zeros )
             && radix == 6
             && zeros == 3 );
    assert ( findRadix ( 343 ) == 7 );
    assert ( countZeros ( 343 ) == 3 );
    assert ( findRadixZeros ( 343, &radix, &zeros )
             && radix == 7
             && zeros == 3 );
    assert ( findRadix ( 1024 ) == 2 );
    assert ( countZeros ( 1024 ) == 10 );
    assert ( findRadixZeros ( 1024, &radix, &zeros )
             && radix == 2
             && zeros == 10 );
    assert ( findRadix ( 1296 ) == 6 );
    assert ( countZeros ( 1296 ) == 4 );
    assert ( findRadixZeros ( 1296, &radix, &zeros )
             && radix == 6
             && zeros == 4 );
    assert ( findRadix ( -8 ) == -1 );
    assert ( countZeros ( -8 ) == -1 );
    assert ( ! findRadixZeros ( -8, &radix, &zeros ) );
    return EXIT_SUCCESS;
}
#endif /* __PROGTEST__ */
