# refract

`refract` is a C++26 reflection library, building over `std::meta`, wrapping the standard `std::meta::info` reflection handle in a family of typed, object-oriented classes.

This library is a standalone port of [stdlibx](https://github.com/mikomikotaishi/stdlibx)'s `stdx::meta::reflect`.

## API

### Core wrapper hierarchy

- `Mirror`: Base wrapper pairing any reflected entity with the operations valid for every reflection.
  - `Type`: Wraps the reflection of a type and exposes its information: size and alignment, category tests, cv/ref/pointer manipulation, type relations, and template arguments.
    - `Class<T>`: Statically-typed wrapper for a class (non-union) type.
    - `Enum<E>`: Statically-typed wrapper for an enumeration type.
    - `Union<U>`: Statically-typed wrapper for a union type.
  - `Callback`: A free or unspecified function.
    - `Method`: A (non-special) member function.
    - `Constructor`: A constructor.
    - `Destructor`: A destructor.
  - `Field`: A non-static data member.
  - `Variable`: A variable.
  - `Parameter`: A function parameter.
  - `Base`: A direct base-class relationship.
  - `Enumerator`: A single enumerator.
  - `Namespace`: A namespace.
  - `NamespaceAlias`: A namespace alias.
  - `TypeAlias`: A type alias.
  - `Concept`: A concept.
  - `Template`: A template.
  - `Annotation`: An annotation.
  - `StructuredBinding`: A structured binding.

### Enums

- `Operators`: A wrapper over `std::meta::operators` with named constants for each overloadable operator and its symbol.
- `ReflectionOf`: The kind of entity a reflection refers to.
- `Modifier`: A specifier or modifier applied to an entity.
- `AccessFlag`: The access level of a class member.
- `CvQualifier`: A cv-qualifier.
- `RefQualifier`: The reference qualifier on a member function.
- `FunctionSpecifier`: A specifier appearing on a function, method, constructor, or destructor.
- `StorageClass`: The storage class of a variable or static data member.
- `Linkage`: The linkage of a named entity.

### Collections

- `EnumSet<E>`: A `std::bitset`-backed set of an enum's enumerators.
- `EnumMap<K, V>`: An array-backed map keyed by an enum's enumerators.
