//
//  stcak.c
//  algorithm
//
//  Created by yangyouyong on 2018/4/8.
//  Copyright © 2018年 yangyouyong. All rights reserved.
//

#include "stcak.h"

#include <stdio.h>
#include "stdlib.h"

/**
 * C 语言: 数组实现的栈，只能存储int数据。 -> 存储 void* 指针 void* 类型不明确, 不方便解析
 * 双向链表与数组思路同
 *
 */

// 保存数据的数组
static void **arr=NULL;
// 栈的实际大小
static int count;

// 创建“栈”，默认大小是12
static inline int create_array_stack(int capicity);
int create_array_stack(int capicity)
{
    arr = (void **)malloc(capicity*sizeof(void *));
    if (!arr)
    {
        printf("arr malloc error!");
        return -1;
    }
    
    return 0;
}

// 销毁“栈”
static inline int destroy_array_stack();
int destroy_array_stack()
{
    if (arr)
    {
        free(arr);
        arr = NULL;
    }
    
    return 0;
}

// 将val添加到栈中
static inline void push(void *val);
void push(void *val)
{
    arr[count++] = val;
}

// 返回“栈顶元素值”
static inline void * peek();
void * peek()
{
    return arr[count-1];
}

// 返回“栈顶元素值”，并删除“栈顶元素”
void * pop()
{
    void *ret = arr[count-1];
    count--;
    return ret;
}

// 返回“栈”的大小
int size()
{
    return count;
}

// 返回“栈”是否为空
int is_empty()
{
    return size()==0;
}

// 打印“栈”
void print_array_stack()
{
    if (is_empty())
    {
        printf("stack is Empty\n");
        return ;
    }
    
    printf("stack size()=%d\n", size());
    
    int i=size()-1;
    while (i>=0)
    {
        printf("%p\n", arr[i]);
        i--;
    }
}

void test_stack()
{
    void *tmp=NULL;
    
    // 创建“栈”
    create_array_stack(12);
    
    // 将10, 20, 30 , 40依次推入栈中
    int *ten = {10};
    int *tw = {20};
    int *thir = {30};
    int *fo = {40};
    push(ten);
    push(tw);
    push(thir);
    
    // 将“栈顶元素”赋值给tmp，并删除“栈顶元素”
    tmp = pop();
    printf("tmp=%p\n", tmp);
//    print_array_stack();    // 打印栈
    
    // 只将“栈顶”赋值给tmp，不删除该元素.
    tmp = peek();
    printf("tmp=%p\n", tmp);
//    print_array_stack();    // 打印栈
    
    push(fo);
    print_array_stack();    // 打印栈
    
    // 销毁栈
    destroy_array_stack();
}
