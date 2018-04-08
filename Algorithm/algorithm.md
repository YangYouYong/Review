# Algorithm

#### double link

> node

```
typedef struct node
{
    struct node *pre;
    struct node *next;
    void *data;
}node;

```

> property

```
static node *head = NULL;
static int count = 0;

// create link
int create_dlink()
{
    head = create_node(NULL);
    if (!head) return -1;
    
    count = 0;
    
    return 0;
}

```


> insert

```

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

```

> delete

```
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

```
