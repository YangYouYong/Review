//
//  Cat.h
//  OOBase
//
//  Created by yangyouyong on 2018/4/23.
//  Copyright © 2018年 yangyouyong. All rights reserved.
//

#ifndef Cat_h
#define Cat_h

#include <stdio.h>
#include "MObject.h"

// cat inherit MObject

// same like MObject
typedef struct Cat{
    Key key;
    struct MObject *superNode; // super
    struct PropertyNode *rootPropertyNode;  // propertylist
    struct MethodNode *rootMethodNode;      // methodlist
    struct MObject *extensionObj;           // extensionLink
    
} Cat;

Cat *createCat();

#endif /* Cat_h */
