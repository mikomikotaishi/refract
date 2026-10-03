#pragma once

#include "Details.hpp"

/**
 * @namespace refract
 * @brief The refract namespace, the namespace of the library.
 */
namespace refract {
    class Mirror;
    class Type;
    class Field;
    class Variable;
    class Callback;
    class Method;
    class Constructor;
    class Destructor;
    class Parameter;
    class Enumerator;
    class Base;
    class Namespace;
    class NamespaceAlias;
    class TypeAlias;
    class Concept;
    class Template;
    class Annotation;
    class StructuredBinding;

    template <detail::ReflectableAsClass T>
    class Class;

    template <detail::ReflectableAsEnum E>
    class Enum;

    template <detail::ReflectableAsUnion U>
    class Union;
} // namespace refract
