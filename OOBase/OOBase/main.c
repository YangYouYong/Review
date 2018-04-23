//
//  main.c
//  OOBase
//
//  Created by yangyouyong on 2018/4/20.
//  Copyright © 2018年 yangyouyong. All rights reserved.
//

#include <stdio.h>
#include "MObject.h"
#include "Cat.h"

void foo(){
    printf("foo method called \n");
}

// as root method
void mobject_method(){
    printf("mobjectMethod method called \n");
}

// as override method
void cat_method(){
    printf("catMethod method called \n");
}

int main(int argc, const char * argv[]) {
    
    
    PropertyNode *name = create_propertynode("name", "jack", NULL);
    PropertyNode *sex = create_propertynode("sex", "sex", NULL);
    MethodNode *fooMethod = create_methodnode("foo", foo, NULL, NULL);
    
    MObject *obj = createObject();
    
    add_propertynode(obj, name);
    add_propertynode(obj, sex);
    
    add_methodnode(obj, fooMethod);
    
    callMethod(obj, "foo");
    
    MethodNode *objectMethod = create_methodnode("object", mobject_method, NULL, NULL);
    MethodNode *catObjectMethod = create_methodnode("object", cat_method, NULL, NULL);
    
    Cat *catWithNoMethodImpl = createCat();
    
    Cat *catWithParentMethod = createCat();
    add_methodnode((MObject *)catWithParentMethod, objectMethod);
    
    Cat *catWithOverrideMethod = createCat();
    
    add_methodnode((MObject *)catWithOverrideMethod, objectMethod);
    add_methodnode((MObject *)catWithOverrideMethod, catObjectMethod);
    
    callMethod((MObject *)catWithParentMethod, "object");
    callMethod((MObject *)catWithOverrideMethod, "object");
    
    printf("property: %s \n", get_property(obj, "name"));
    callMethod((MObject *)catWithNoMethodImpl, "object");

    // insert code here...
    printf("Hello, World!\n");

    return 0;
}
