//
//  double_link.c
//  algorithm
//
//  Created by yangyouyong on 2018/4/8.
//  Copyright © 2018年 yangyouyong. All rights reserved.
//

#include "double_link.h"
#include "stdlib.h"


typedef struct node
{
    struct node *pre;
    struct node *next;
    void *data;
}node;

static node *head = NULL;
static int count = 0;


/**
 constructor node

 @param data data
 @return node
 */
static node* create_node(void *data)
{
    node *pnode=NULL;
    pnode = (node *)malloc(sizeof(node));
    if (!pnode)
    {
        printf("create node error!\n");
        return NULL;
    }
    pnode->pre = pnode->next = pnode;
    pnode->data = data;
    
    return pnode;
}

// create link
int create_dlink()
{
    head = create_node(NULL);
    if (!head) return -1;
    
    count = 0;
    
    return 0;
}

int dlink_is_empty()
{
    return count == 0;
}

int dlink_size() {
    return count;
}

static node* get_node(int index)
{
    if (index<0 || index>=count)
    {
        printf("%s failed! index out of bound!\n", __func__);
        return NULL;
    }
    
    if (index <= (count/2))
    {
        int i = 0;
        node *pnode = head->next;
        while ((i++) < index)
            pnode = pnode->next;
        
        return pnode;
    }
    
    int j=0;
    int rindex = count - index - 1;
    node *rnode = head->pre;
    while ((j++) < rindex) {
        rnode = rnode->pre;
    }
    
    return rnode;
}

static node* get_first_node()
{
    return get_node(0);
}

static node* get_last_node()
{
    return get_node(count-1);
}

void* dlink_get(int index)
{
    node *pindex = get_node(index);
    if (!pindex)
    {
        printf("%s failed!\n", __func__);
        return NULL;
    }
    
    return pindex->data;
    
}

void* dlink_get_first()
{
    return dlink_get(0);
}

void* dlink_get_last()
{
    return dlink_get(count-1);
}

int dlink_insert(int index, void* data)
{
    if (index==0)
        return dlink_insert_first(data);
    
    node *pindex = get_node(index);
    if (!pindex)
        return -1;
    
    node *pnode=create_node(data);
    if (!pnode)
        return -1;
    
    pnode->pre = pindex->pre;
    pnode->next = pindex;
    pindex->pre->next = pnode;
    pindex->pre = pnode;
    
    count++;
    
    return 0;
}

int dlink_insert_first(void *data)
{
    node *pnode=create_node(data);
    if (!pnode)
        return -1;
    
    pnode->pre = head;
    pnode->next = head->next;
    head->next->pre = pnode;
    head->next = pnode;
    count++;
    return 0;
}

int dlink_append_last(void *data)
{
    node *pnode=create_node(data);
    if (!pnode)
        return -1;
    
    pnode->next = head;
    pnode->pre = head->pre;
    head->pre->next = pnode;
    head->pre = pnode;
    count++;
    return 0;
}

int dlink_delete(int index)
{
    node *pindex=get_node(index);
    if (!pindex)
    {
        printf("%s failed! the index in out of bound!\n", __func__);
        return -1;
    }
    
    pindex->next->pre = pindex->pre;
    pindex->pre->next = pindex->next;
    free(pindex);
    count--;
    
    return 0;
}

int dlink_delete_first()
{
    return dlink_delete(0);
}

int dlink_delete_last()
{
    return dlink_delete(count-1);
}

int destroy_dlink()
{
    if (!head)
    {
        printf("%s failed! dlink is null!\n", __func__);
        return -1;
    }
    
    node *pnode=head->next;
    node *ptmp=NULL;
    while(pnode != head)
    {
        ptmp = pnode;
        pnode = pnode->next;
        free(ptmp);
    }
    
    free(head);
    head = NULL;
    count = 0;
    
    return 0;
}
