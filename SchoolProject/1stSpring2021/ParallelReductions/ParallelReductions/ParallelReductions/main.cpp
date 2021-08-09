//
//  main.cpp
//  ParallelReductions
//
//  Created by Garret Wasden on 4/26/21.
//

#include <iostream>
#include "Cmain.hpp"

int main(int argc, const char * argv[]) {
    int a[200];
    for(int i = 0; i < 200; i++){
        a[i] = i;
    }
    int size = sizeof(a)/sizeof(a[0]);
    
    Cmain<int> cmain;
    OpenMPC<int> openOne;
    reduOpenMPC<int> reducPart;
    
//    int sumTimeForC = cmain.parallel_sum_std(a,size,4);
//    int sumOpenPartOne = openOne.parallel_sum_std(a,size,4);
//    int sumReducPart = reducPart.parallel_sum_std(a, size, 4);
//    printf("%d-time for just c++ threads\n", sumTimeForC);
//    printf("%d-time for just OpenMP with manual reductions\n", sumOpenPartOne);
//    printf("%d-time for just OpenMP with reductions\n", sumReducPart);
    
    for (int j = 2; j< 4; j++){
        printf("\n\nnum:%d\n", j);
    int setB = 1000 *j;
    int b[setB];
    for(int i = 0; i < setB; i++){
        b[i] = i;
    }
    int sizeb = (int)sizeof(b)/sizeof(b[0]);
    
    printf("\n\npart one normal:\n");
    for(int i = 1; i < 8; i++){
        int sumTimeForC = cmain.parallel_sum_std(b,sizeb,i*j);
        printf("%d\n", sumTimeForC);
    }
    printf("\n\npart two custom:\n");
    
    for(int i = 1; i < 8; i++){
        int sumOpenPartOne = openOne.parallel_sum_std(b,sizeb,i*j);
        printf("%d\n", sumOpenPartOne);
    }
    printf("\n\npart three full:\n");
    
    for(int i = 1; i < 8; i++){
    
         int sumReducPart = reducPart.parallel_sum_std(b, sizeb, i*j);
        printf("%d\n", sumReducPart);
    }
    printf("\n\n\n");
    }
    return 0;
}
