//
//  main.c
//  OOBase
//
//  Created by yangyouyong on 2018/4/20.
//  Copyright © 2018年 yangyouyong. All rights reserved.
//

#include <stdio.h>
#include "MObject.h"

void foo(){
    printf("foo method called \n");
}

int main(int argc, const char * argv[]) {
    
    PropertyNode *name = create_propertynode("name", "jack", NULL);
    PropertyNode *sex = create_propertynode("sex", "sex", NULL);
    MethodNode *fooMethod = create_methodnode("foo", foo, NULL, NULL);
    
    MObject *obj = createObject(NULL, NULL);
    
    add_propertynode(obj, name);
    add_propertynode(obj, sex);
    
    add_methodnode(obj, fooMethod);
    
    callMethod(obj, "foo");
    printf("property: %s \n", get_property(obj, "name"));
    // insert code here...
    printf("Hello, World!\n");
    return 0;
}
