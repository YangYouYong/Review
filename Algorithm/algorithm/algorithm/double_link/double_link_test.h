//
//  double_link_test.h
//  algorithm
//
//  Created by yangyouyong on 2018/4/8.
//  Copyright © 2018年 yangyouyong. All rights reserved.
//

#ifndef double_link_test_h
#define double_link_test_h

#include <stdio.h>
#include "double_link.h"

/**
 * C 语言实现的双向链表的测试程序。
 *
 * (01) int_test()
 *      演示向双向链表操作“int数据”。
 * (02) string_test()
 *      演示向双向链表操作“字符串数据”。
 * (03) object_test()
 *      演示向双向链表操作“对象”。
 * link : http://www.cnblogs.com/skywang12345/p/3561803.html
 */


static inline void int_test();
void int_test()
{
    int iarr[4] = {10, 20, 30, 40};
    
    printf("\n----%s----\n", __func__);
    create_dlink();        // 创建双向链表
    
    dlink_insert(0, &iarr[0]);    // 向双向链表的表头插入数据
    dlink_insert(0, &iarr[1]);    // 向双向链表的表头插入数据
    dlink_insert(0, &iarr[2]);    // 向双向链表的表头插入数据
    
    printf("dlink_is_empty()=%d\n", dlink_is_empty());    // 双向链表是否为空
    printf("dlink_size()=%d\n", dlink_size());            // 双向链表的大小
    
    // 打印双向链表中的全部数据
    int i;
    int *p;
    int sz = dlink_size();
    for (i=0; i<sz; i++)
    {
        p = (int *)dlink_get(i);
        printf("dlink_get(%d)=%d\n", i, *p);
    }
    
    destroy_dlink();
}
static inline void string_test();
void string_test()
{
    char* sarr[4] = {"ten", "twenty", "thirty", "forty"};
    
    printf("\n----%s----\n", __func__);
    create_dlink();        // 创建双向链表
    
    dlink_insert(0, sarr[0]);    // 向双向链表的表头插入数据
    dlink_insert(0, sarr[1]);    // 向双向链表的表头插入数据
    dlink_insert(0, sarr[2]);    // 向双向链表的表头插入数据
    
    printf("dlink_is_empty()=%d\n", dlink_is_empty());    // 双向链表是否为空
    printf("dlink_size()=%d\n", dlink_size());            // 双向链表的大小
    
    // 打印双向链表中的全部数据
    int i;
    char *p;
    int sz = dlink_size();
    for (i=0; i<sz; i++)
    {
        p = (char *)dlink_get(i);
        printf("dlink_get(%d)=%s\n", i, p);
    }
    
    destroy_dlink();
}

typedef struct tag_stu
{
    int id;
    char name[20];
}stu;

static stu arr_stu[] =
{
    {10, "sky"},
    {20, "jody"},
    {30, "vic"},
    {40, "dan"},
};
#define ARR_STU_SIZE ( (sizeof(arr_stu)) / (sizeof(arr_stu[0])) )

static inline void object_test();
void object_test()
{
    printf("\n----%s----\n", __func__);
    create_dlink();    // 创建双向链表
    
    dlink_insert(0, &arr_stu[0]);    // 向双向链表的表头插入数据
    dlink_insert(0, &arr_stu[1]);    // 向双向链表的表头插入数据
    dlink_insert(0, &arr_stu[2]);    // 向双向链表的表头插入数据
    
    printf("dlink_is_empty()=%d\n", dlink_is_empty());    // 双向链表是否为空
    printf("dlink_size()=%d\n", dlink_size());            // 双向链表的大小
    
    // 打印双向链表中的全部数据
    int i;
    int sz = dlink_size();
    stu *p;
    for (i=0; i<sz; i++)
    {
        p = (stu *)dlink_get(i);
        printf("dlink_get(%d)=[%d, %s]\n", i, p->id, p->name);
    }
    
    destroy_dlink();
}

static inline void test_double_link();
void test_double_link() {
    int_test();        // 演示向双向链表操作“int数据”。
    string_test();    // 演示向双向链表操作“字符串数据”。
    object_test();    // 演示向双向链表操作“对象”。
}

#endif /* double_link_test_h */
