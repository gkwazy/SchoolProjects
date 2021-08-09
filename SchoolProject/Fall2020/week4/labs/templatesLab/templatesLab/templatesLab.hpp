//
//  templatesLab.hpp
//  templatesLab
//
//  Created by Garret Wasden on 9/20/20.
//

#ifndef templatesLab_hpp
#define templatesLab_hpp

#include <stdio.h>
#include <vector>


template <typename T>
struct Triple {
    T a;
    T b;
    T c;
};

template <typename T>
T addTemplate(Triple <T> type){
    return type.a + type.b + type.c;
}

#endif /* templatesLab_hpp */
