### 2.4. Sequence Diagram ###
Represents interactions among objects in a specific scenario.

#### 2.4.1. Lifeline ####
Represents an active object

![Class](notation/sequences/sequence-1.png)

#### 2.4.2. Interactions ####
Objects make requests and receive responses from other objects.

![Class](notation/sequences/sequence-2.png)

Objects also create or destroy other objects.

![Class](notation/sequences/sequence-3.png)

An object may act up on a signal or send a signal.

![Class](notation/sequences/sequence-4.png)

Objects may post messages to other objects or invoke call backs. A state-invariant node may annotate a lifefline.

![Class](notation/sequences/sequence-6.png)

#### 2.4.3. Fragments ####

A request may be representated as a parameterized operation with optional assignments, conditions and iterations.

Several messages might be grouped together for clarity.

Interactions like opt (if), alt(if-else), parallel, critical, iter and etc., are also represented as combined fragments.

![Class](notation/sequences/sequence-7.png)

#### 2.4.4. Illustration ####

![Class](notation/sequences/sequence-8.png)

```
class Client {
    public static void main(String[] args) {
        Service service = new Service();
        service.serve(request);
        destroy service;
    }
}

class Service {
    private Store local; 
    private Store remote;

    public Service(Store remote) {
        local = new Store();
        this.remote = remote;
    }

    public void serve(request){
        local.save(data);
        remote.save(data);
        notify("message");
    }

    public finalize() {
        destroy local;
    }

}

class Store {
    public void save(data){
        
    }
}
```