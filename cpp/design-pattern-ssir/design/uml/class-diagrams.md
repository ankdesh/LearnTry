### 1.1. Class Diagram ###

Class diagram presents the classes of the objects and their relationships.

#### 1.1.1. Class ####
Consists of three compartments: Name, State and Behavior.

![Class](notation/classes/class-1.png)

State is a set of attributes and behavior is a set of operations.

![Class](notation/classes/class-2.png)

```
    class Book {
        private:
            int isbn;
            string title;
            Set<string> authors;
            boolean available = false;
            double value = 0;
            double discount = 0;
            double price = 0;
        public:
            Book() {

            }

            void print() {

            }
    }
```

#### 1.1.2. Association ####

Association represents "uses and leaves" relationship. 

![Class](notation/classes/association-1.png)

Can be bi-directional as well.

![Class](notation/classes/association-2.png)

Objects in a relation play a role and the cardinality can be one-to-one, one-to-many and etc., 

![Class](notation/classes/association-3.png)

An illustration:

```
class Security {
    private CredentialStore store;
    ....
}
```

![Class](notation/classes/association-4.png)

#### 1.1.3. Aggregation ####

Represents "owns and share" relationship.

![Class](notation/classes/aggregation-1.png)

Illustration: A connection pool is manages 5 connections for its clients. 

```
class ConnectionPool {
    private Connection[5] connections;
    ...
}
```

![Class](notation/classes/aggregation-2.png)

#### 1.1.4. Composition ####

Represents "part-of" relationship. The part is destroyed along with the whole. 

![Class](notation/classes/composition-1.png)

Illustration: The TitleBar is part of a Window.

![Class](notation/classes/composition-2.png)

#### 1.1.5. Dependency ####

Represents "uses and throws" relationship. 

![Class](notation/classes/dependency.png)

#### 1.1.6. Association Class ####

Represents the details of an association.

![Class](notation/classes/association-class.png)

#### 1.1.7. Generalization ####

Represents "is-a" relation. The derived object "is-a" special kind of base object.

![Class](notation/classes/generalization-1.png)

#### 1.1.8. Interface ####

Represents service contract. 

![Class](notation/classes/interface-1.png)

Illustration:

![Class](notation/classes/interface-2.png)

#### 1.1.9. Realization ####

Represents implementation of a contract. 

![Class](notation/classes/realization-1.png)

Illustration: 

![Class](notation/classes/realization-2.png)

#### 1.1.10. Class Diagram Illustration ####

![Class](notation/classes/class-diagram.png)

```
class Connection {
    private int timeout = 1000;
    public void insert(string query){
        ...
    }
}

interface ConnectionPool {
    public abstract Connection get(string key);
}

class FixedConnectionPool implements ConnectionPool {
    private List<Connection> connections;
    public Connection get(string key){
        ...
    }
}

class ConnectionPoolFactory {
    public static ConnectionPool get(string key){
        ...
    }
}

class Client {
    private ConnectionPool pool;
    private Connection connection

    public static void main(String[] args) {
        pool = ConnectionPoolFactory.get("fixed");
        connection = pool.get("mysql");
        connection.insert("insert into employees value asdfasfdasdf");
    }
}
```