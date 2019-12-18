# Software Engineering
- **Modularity:**
    Code is decomposed in one or more independent units, called modules, such that
    when the codes has an anomaly, ideally only one module is afflicted.

- **Cohesion:**
    Measure of relation between two modules. High cohesion usually implies high readability.

- **Coupling:**
    Interconnections between two modules. Low interconnections = High independence.

### OOD Principles: SOLID
- **Single Responsibility Principle:**
    An object (*class*) should have only a single reason to change.

- **Open Closed Principle:**
    Class should be open for extensions and closed for modifications

- **Liskov Substitution Principle:**
    Subclasses should be able to substitute the parent class without changing their expected behavior.

- **Interface Segregation Principle:**
Break up large interface classes: Don't force subclasses to implement methods that will not be used.

- **Dependency Inversion Principle:**
    De-couple a class from its dependencies. Think two times before using the `new` keyword inside a method.


# Design Patterns
#### Factory Method
```python
class TreeFactory:
    def __init__(self, seed):
        self.randomizer = random.Random(seed)

    def random_tree(self):
        return self.randomizer.choice([Oak(), Birch(), Elm()])
```
When you don't know the type of object beforehand.

#### Abstract Factory method
```python
class ZooFactory(abc.ABC):
    @abstractmethod
    def new_tree():
        pass

    @abstractmethod
    def new_animal():
        pass
```
Generalization for factories for objects that make sense together

```python
class AmericanZoo(ZooFactory):
    def new_tree():
        return random.choice([Maple(), Ash()]

    def new_animal():
        return random.choice([Grizzly(), Moose()])

class AfricanZoo(ZooFactory):
    def new_tree():
        return random.choice([Baobab(), Acacia()])

    def new_animal():
        return random.choice([Lion(), Gorilla()])
```


#### Builder Pattern
```python
class User:
    def __init__(self, id, name):
        self.id = id
        self.name = name

    @staticmethod
    def from_json(json):
        user_id = json["id"]
        user_name = json["name"]

        return User(user_id, user_name)
```
Avoid boilerplates for specific object creation

#### Singleton
```java
class Database {
    private Database() {};

    private static Database instance = null;
    public static Database getInstance() {
        if (instance == null)
            instance = new Database();
        return instance;
    }
}
```
Force only one instance of the class.

#### Adapter vs Proxy vs Facade vs Decorator vs Bridge
- **Decorator:**
    Change or extend the behaviour of a class or another decorator, preserving its interface.

- **Facade:**
    Simpler interface for a complex subsystem or multiple interfaces.

- **Adapter:**
    Adapts two incompatible interfaces.
    Does not change the behaviour of those interfaces.

- **Proxy**
    Surrogate or placeholder for another object in order to _control access_ over it, changing it's implementation but preserving the interface.

    Differs from the *Decorator*, because it's common use is for single composability.
    Change the implementation, not the interface

- **Bridge**
    Abstraction of the *Adapter*, for two families of interfaces, where one or both of the families requires the other in order to work.

#### Composite Pattern
Group of object that behaves like a single object. (Ex. Binary Trees)

#### Flyweight Pattern
Encapsulates the resources or configurations, avoiding multiple instantiations

#### Command Pattern
Command interface, usually with an `execute` or `run` method, could have an `undo` operation too.

#### Chain of Responsibility Pattern
Chain of objects that checks if they could perform an action, if they can't the action is delegated to the next object in the chain.

#### Interpreter Pattern
Pattern applied to recognize sentences or the syntax of a language.

#### Iterator Pattern
Iterator interface, composed by a `begin`, `next` and a way to recognize the end of the iteration.
Exposes the elements contained in an object (Usually [Composite Pattern](#composite-pattern)). Without exposing its structure.


#### Observer Pattern
Requires an `Observable` object and an `observer`. The `observer` register itself to the `Observable` and the `Observable` when changes notifies the `observer`
```python
class Observable:
    def __init__(self):
        self.observers = set()

    def update(self):
        for observer in self.observers:
            observer.notify()

    def register(self, observer):
        self.observers.add(observer)

class Observer:
    def __init__(self, name):
        self.name = name

    def notify(self):
        print(f"{self.name}: Look! has changed")
```

#### Strategy Pattern
Specifies how something should be done, it's plugged into a larger object or method to provide a specific algorithm. (Ex. A sorting algorithm)

#### Visitor Pattern
Encapsulates an operation to apply to an iterator. (Ex. The map function)

#### Client-Server Architecture
- **Thin Client:** strongly dependent from the server
- **Fat Client:** Almost server independent
- **Three tier Architecture** Client connected to the server. The server is connected with the database

#### Pipe and filter Architecture
Series of component (filters) that process an input stream and produces an output stream.
Component are connected together with a pipe.
```sh
echo "DCBA\n4321" | tac | rev
```

### Model View Controller
- Model contains the data
- User interacts with the controller and changes the data
- View displays the content of the Model to the user


