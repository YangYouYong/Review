//
//  Cat.c
//  OOBase
//
//  Created by yangyouyong on 2018/4/23.
//  Copyright © 2018年 yangyouyong. All rights reserved.
//

#include "Cat.h"
#include "stdio.h"

Cat *createCat()
{
    MObject* obj;
    
    if ((obj = (MObject *)malloc(sizeof(MObject))) == NULL)
        return NULL;
    obj->rootPropertyNode = NULL;
    obj->rootMethodNode = NULL;
    obj->extensionObj = NULL;
    obj->superNode = obj;  //  base class parent -> self
    
    
    Cat* ct;
    if ((ct = (Cat *)malloc(sizeof(Cat))) == NULL)
        return NULL;
    
    ct->rootPropertyNode = NULL;
    ct->rootMethodNode = NULL;
    ct->extensionObj = NULL;
    ct->superNode = obj;  // inherit
    
    return ct;
    
}

// method find
// property find
