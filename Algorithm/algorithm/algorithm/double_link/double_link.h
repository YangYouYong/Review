//
//  double_link.h
//  algorithm
//
//  Created by yangyouyong on 2018/4/8.
//  Copyright © 2018年 yangyouyong. All rights reserved.
//

#ifndef double_link_h
#define double_link_h

#include <stdio.h>

extern int create_dlink();
extern int destroy_dlink();
extern int dlink_is_empty();
extern int dlink_size();

extern void* dlink_get(int index);
extern void* dlink_get_first();
extern void* dlink_get_last();

extern int dlink_insert(int index, void *pval);
extern int dlink_insert_first(void *pval);
extern int dlink_append_last(void *pval);

extern int dlink_delete(int index);
extern int dlink_delete_first();
extern int dlink_delete_last();

#endif /* double_link_h */
