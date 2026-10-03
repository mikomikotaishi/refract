/**
 * @module refract
 * @brief The refract module.
 */
module;

#include "refract.hpp"

export module refract;

/**
 * @namespace refract
 * @brief The refract namespace, the namespace of the library.
 */
export namespace refract {
    using refract::AccessFlag;
    using refract::Annotation;
    using refract::Base;
    using refract::Callback;
    using refract::Concept;
    using refract::Constructor;
    using refract::CvQualifier;
    using refract::Destructor;
    using refract::EnumMap;
    using refract::EnumSet;
    using refract::Enumerator;
    using refract::Field;
    using refract::FunctionSpecifier;
    using refract::Linkage;
    using refract::Method;
    using refract::Mirror;
    using refract::Modifier;
    using refract::Namespace;
    using refract::NamespaceAlias;
    using refract::Operators;
    using refract::Parameter;
    using refract::RefQualifier;
    using refract::ReflectionOf;
    using refract::StorageClass;
    using refract::Template;
    using refract::Type;
    using refract::TypeAlias;
    using refract::Variable;
} // namespace refract
