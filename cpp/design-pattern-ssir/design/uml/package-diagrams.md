### 1.2. Package Diagram ###
Represents logical grouping of classes.

#### 1.2.1. Package ####
A package consists of classes and sub-packages that are logically close to each other.

![Class](notation/packages/package-1.png)

Various languages implement a pacakge as a modules, a namespaces and etc.,

![Class](notation/packages/package-2.png)

#### 1.2.2. Package Relations ####
A package may import/depend on other package.

![Class](notation/packages/package-use-1.png)

Illustration: 

```
package com.glarimy.client;

import com.glarimy.api;
....

```

![Class](notation/packages/package-use-2.png)

A package may include another package.

![Class](notation/packages/package-contain-1.png)

Illustration: 
```
    namespace com.glarimy.api {
        namespace exceptions {
            ...
        }
        ...
    }
```

![Class](notation/packages/package-contain-2.png)

#### 1.2.3. Package Diagram Illustration ####

Illustration-1: 

![Class](notation/packages/package-classes.png)

Illustration-2:

![Class](notation/packages/package-illustration.png)