//
//  MObject.c
//  ocbase
//
//  Created by yangyouyong on 2018/4/20.
//  Copyright © 2018年 yangyouyong. All rights reserved.
//

#include "MObject.h"
#include "stdlib.h"

PropertyNode* create_propertynode(char *name,
                                         char *value,
                                         PropertyNode *parent)
{
    PropertyNode* p;
    
    if ((p = (PropertyNode *)malloc(sizeof(PropertyNode))) == NULL)
        return NULL;
    
    p->propertyName = name;
    p->propertyData = value;
    p->superNode = NULL;
    p->next = NULL;
    
    return p;
}

MethodNode* create_methodnode(char *name,
                                     function_ptr methodImp,
                                     PropertyNode *parmsList,
                                     MethodNode *parent)
{
    MethodNode* m;
    
    if ((m = (MethodNode *)malloc(sizeof(MethodNode))) == NULL)
        return NULL;
    
    m->methodName = name;
    m->methodImp = methodImp;
    m->parmsList = parmsList;
    m->superNode = NULL;
    m->next = NULL;
    
    return m;
}

MethodNode* find_method(MObject *target,
                               char *methodName)
{
    MethodNode *node = target->rootMethodNode;
    
    while (node != NULL) {
        if (node->methodName == methodName) {
            break;
        }
        node = node->next;
    }
    
    // inherit logic
    if (node == NULL) {
        MObject *parent = target->superNode;
        MObject *currentInherritNode = target;
        
        while (parent != NULL && parent != currentInherritNode) {
            
            MethodNode *targetNode = find_method(parent, methodName);
            if (targetNode != NULL) {
                node = targetNode;
                break;
            }
        }
        if (node == NULL) {
            printf("method did not implementation : %s\n",methodName);
            // throws exception here
            exit(10);
        }
    }
    
    return node;
}

PropertyNode* find_property(MObject *target,
                            char *propertyName)
{
    PropertyNode *node = target->rootPropertyNode;
    if (node == NULL) {
        return node;
    }
    while (node != NULL) {
        if (node->propertyName == propertyName) {
            break;
        }
        printf("find:::%s",node->propertyName);
        node = node->next;
    }
    
    return node;
}

void add_propertynode(MObject *target,
                             PropertyNode *propertyNode)
{
    if (target->rootPropertyNode == NULL) {
        target->rootPropertyNode = propertyNode;
        return;
    }
    
    PropertyNode *rootNode = target->rootPropertyNode->next;
    if (rootNode == NULL) {
        target->rootPropertyNode->next = propertyNode;
        return;
    }
    while (rootNode != NULL) {
        rootNode = rootNode->next;
    }
    
    rootNode->next = propertyNode;
}

void add_methodnode(MObject *target,
                        MethodNode *methodNode)
{
    if (target->rootMethodNode == NULL) {
        target->rootMethodNode = methodNode;
        return;
    }
    
    MethodNode *existMethodNode = NULL;
    
    MethodNode *rootNode = target->rootMethodNode->next;
    if (rootNode == NULL) {
        target->rootMethodNode->next = methodNode;
        
        // exist method logic
        if (target->rootMethodNode->methodName == methodNode->methodName) {
            existMethodNode = target->rootMethodNode;
        }
        // replace
        target->rootMethodNode = methodNode;
        
        free(existMethodNode);
        return;
    }
    
    while (rootNode != NULL) {
        if (rootNode->methodName == methodNode->methodName) {
            existMethodNode = rootNode;
        }
        rootNode = rootNode->next;
    }
    if (rootNode->methodName == methodNode->methodName) {
        existMethodNode = rootNode;
    }
    
    // TODO: replace method list datastructure with double link
    if (existMethodNode != NULL) {
        
    }
    
    rootNode->next = methodNode;
}

MObject *createObject(PropertyNode *propertyNode,
                      MethodNode *method)
{
    MObject* obj;
    
    if ((obj = (MObject *)malloc(sizeof(MObject))) == NULL)
        return NULL;
    obj->rootPropertyNode = propertyNode;
    obj->rootMethodNode = method;
    obj->extensionObj = NULL;
    obj->superNode = obj;  //  base class parent -> self
    
    return obj;
    
}
void callMethod(MObject *target,
                char *methodName)
{
    MethodNode *methodNode = find_method(target, methodName);
    
    methodNode->methodImp();
    
}

char *get_property(MObject *target, char *propertyName)
{
    PropertyNode *propertyNode = find_property(target, propertyName);
    
    if (propertyNode != NULL) {
        return propertyNode->propertyData;
    }
    return NULL;
}




