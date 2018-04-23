//
//  MObject.h
//  ocbase
//
//  Created by yangyouyong on 2018/4/20.
//  Copyright © 2018年 yangyouyong. All rights reserved.
//

#ifndef MObject_h
#define MObject_h

#include <stdio.h>

typedef int Key;

typedef void(*function_ptr)(void);

typedef struct PropertyNode{
    Key key;
    char *propertyName;
    char *propertyData; // can use void *  and add a type keyword
    struct PropertyNode *superNode;
    struct PropertyNode *next;  // property list
    
} PropertyNode;

typedef struct MethodNode{
    Key key;
    char *methodName;
    function_ptr methodImp;
    struct PropertyNode *parmsList;  // parms list
    struct MethodNode *superNode;      // super method node
    struct MethodNode *next;        // method list
    
} MethodNode;

typedef struct MObject{
    Key key;
    struct MObject *superNode; // super
    struct PropertyNode *rootPropertyNode;  // propertylist
    struct MethodNode *rootMethodNode;      // methodlist
    struct MObject *extensionObj;           // extensionLink
    
} MObject;

PropertyNode* create_propertynode(char *name,
                                     char *value,
                                     PropertyNode *parent);

MethodNode* create_methodnode(char *name,
                             function_ptr methodImp,
                             PropertyNode *parmsList,
                             MethodNode *parent);

void add_propertynode(MObject *target,
                        PropertyNode *propertyNode);

void add_methodnode(MObject *target,
                        MethodNode *methodNode);

MObject *createObject(void);

void callMethod(MObject *target, char *methodName);

char *get_property(MObject *target, char *propertyName);


#endif /* MObject_h */
