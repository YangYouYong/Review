//
//  main.c
//  algorithm
//
//  Created by yangyouyong on 2018/4/8.
//  Copyright © 2018年 yangyouyong. All rights reserved.
//

#include <stdio.h>
#include "double_link_test.h"
#include "stcak.h"
#include "BTree.h"

static int run_test = 1;

int main(int argc, const char * argv[]) {
    
    if (run_test) {
        test_stack();
        test_double_link();
        test_btree();
    }
    
    
    return 0;
}
