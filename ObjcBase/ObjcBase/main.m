//
//  main.m
//  ObjcBase
//
//  Created by yangyouyong on 2018/3/26.
//  Copyright © 2018年 cpbee. All rights reserved.
//

#import <Foundation/Foundation.h>

int main(int argc, const char * argv[]) {
    __block int val = 10;
    void (^blk)(void) = [^{
        ++val;
    } copy];
    ++val;
    blk();
    printf("val:%d",val);
    return 0;
}
