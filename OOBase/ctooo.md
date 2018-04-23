# Simple C implementation OO thought

> Object use struct
> 
> method use function ptr
> 
> Inherit use single link
> 
> Duplicate use double link

#### Struct -> Simple Object

```
typedef struct MObject{
    Key key;
    struct MObject *superNode; 				// super
    struct PropertyNode *rootPropertyNode;  // propertylist
    struct MethodNode *rootMethodNode;      // methodlist
    struct MObject *extensionObj;           // extensionLink
    
} MObject;

```

#### Properties

```
typedef struct PropertyNode{
    Key key;
    char *propertyName;
    char *propertyData; // can use void *
    struct PropertyNode *superNode;
    struct PropertyNode *next;  // property list
    
} PropertyNode;

```

#### Function definition

> You can optimize this by replace parms use proerties

```

typedef void(*function_ptr)(void);

// typedef void(*function_ptr)(PropertyNode *parms);

```

#### Method

```

typedef struct MethodNode{
    Key key;
    char *methodName;
    function_ptr methodImp;
    struct PropertyNode *parmsList;  // parms list
    struct MethodNode *superNode;      // super method node
    struct MethodNode *next;        // method list
    
} MethodNode;

```

#### Creation

##### Initilize

```

MObject *createObject()
{
    MObject* obj;
    
    if ((obj = (MObject *)malloc(sizeof(MObject))) == NULL)
        return NULL;
    obj->rootPropertyNode = NULL;
    obj->rootMethodNode = NULL;
    obj->extensionObj = NULL;
    obj->superNode = obj;  //  root class parent -> self
    
    return obj;
    
}

```

##### add properties
> without override logic

```
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

```

##### add methods
> contains method override logic

```
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

```

#### Call method

##### Find
> First find in self method list
> 
> Then find from parent & parent & parent'parent ...
> 
> If not find then throw execption
> 
> self-> parent -> no implementation

```
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

```

##### Execute method

> Find method & execute implementation

```
void callMethod(MObject *target,
                char *methodName)
{
    MethodNode *methodNode = find_method(target, methodName);
    
    methodNode->methodImp();
    
}

```

##### Get property

```

char *get_property(MObject *target, char *propertyName)
{
    PropertyNode *propertyNode = find_property(target, propertyName);
    
    if (propertyNode != NULL) {
        return propertyNode->propertyData;
    }
    return NULL;
}

```

#### Example

function: 

```

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

```

creation:

```
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
    
    printf("Hello, World!\n");

    return 0;

```

result:

```
foo method called 
mobjectMethod method called 
catMethod method called 
property: jack 
method did not implementation : object
Program ended with exit code: 10

```