#pragma once

#include <cstddef>
#include <source_location>
#include <string_view>
#include <meta>
#include <optional>
#include <vector>

#include "ForwardDecl.hpp"
#include "EnumSet.hpp"

/**
 * @namespace refract
 * @brief The refract namespace, the namespace of the library.
 */
namespace refract {
    /**
     * @class Operators
     * @brief A wrapper enum for {@code std::meta::operators}.
     */
    class [[nodiscard]] Operators final {
    public:
        using Self = std::meta::operators;

        static constexpr Self NEW = std::meta::operators::op_new; ///< operator new
        static constexpr Self DELETE = std::meta::operators::op_delete; ///< operator delete
        static constexpr Self ARRAY_NEW = std::meta::operators::op_array_new; ///< operator new[]
        static constexpr Self ARRAY_DELETE = std::meta::operators::op_array_delete; ///< operator delete[]
        static constexpr Self CO_AWAIT = std::meta::operators::op_co_await; ///< operator co_await
        static constexpr Self PARENTHESES = std::meta::operators::op_parentheses; ///< operator ()
        static constexpr Self ARROW = std::meta::operators::op_arrow; ///< operator ->
        static constexpr Self ARROW_STAR = std::meta::operators::op_arrow_star; ///< operator ->*
        static constexpr Self TILDE = std::meta::operators::op_tilde; ///< operator ~
        static constexpr Self EXCLAMATION = std::meta::operators::op_exclamation; ///< operator !
        static constexpr Self PLUS = std::meta::operators::op_plus; ///< operator +
        static constexpr Self MINUS = std::meta::operators::op_minus; ///< operator -
        static constexpr Self STAR = std::meta::operators::op_star; ///< operator *
        static constexpr Self SLASH = std::meta::operators::op_slash; ///< operator /
        static constexpr Self PERCENT = std::meta::operators::op_percent; ///< operator %
        static constexpr Self CARET = std::meta::operators::op_caret; ///< operator ^
        static constexpr Self AMPERSAND = std::meta::operators::op_ampersand; ///< operator &
        static constexpr Self EQUALS = std::meta::operators::op_equals; ///< operator =
        static constexpr Self PIPE = std::meta::operators::op_pipe; ///< operator |
        static constexpr Self PLUS_EQUALS = std::meta::operators::op_plus_equals; ///< operator +=
        static constexpr Self MINUS_EQUALS = std::meta::operators::op_minus_equals; ///< operator -=
        static constexpr Self STAR_EQUALS = std::meta::operators::op_star_equals; ///< operator *=
        static constexpr Self SLASH_EQUALS = std::meta::operators::op_slash_equals; ///< operator /=
        static constexpr Self PERCENT_EQUALS = std::meta::operators::op_percent_equals; ///< operator %=
        static constexpr Self CARET_EQUALS = std::meta::operators::op_caret_equals; ///< operator ^=
        static constexpr Self AMPERSAND_EQUALS = std::meta::operators::op_ampersand; ///< operator &=
        static constexpr Self PIPE_EQUALS = std::meta::operators::op_pipe_equals; ///< operator |=
        static constexpr Self EQUALS_EQUALS = std::meta::operators::op_equals_equals; ///< operator ==
        static constexpr Self EXCLAMATION_EQUALS = std::meta::operators::op_exclamation_equals; ///< operator !=
        static constexpr Self LESS = std::meta::operators::op_less; ///< operator <
        static constexpr Self GREATER = std::meta::operators::op_greater; ///< operator >
        static constexpr Self LESS_EQUALS = std::meta::operators::op_less_equals; ///< operator <=
        static constexpr Self GREATER_EQUALS = std::meta::operators::op_greater_equals; ///< operator >=
        static constexpr Self SPACESHIP = std::meta::operators::op_spaceship; ///< operator <=>
        static constexpr Self AMPERSAND_AMPERSAND = std::meta::operators::op_ampersand_ampersand; ///< operator &&
        static constexpr Self PIPE_PIPE = std::meta::operators::op_pipe_pipe; ///< operator ||
        static constexpr Self LESS_LESS = std::meta::operators::op_less_less; ///< operator <<
        static constexpr Self GREATER_GREATER = std::meta::operators::op_greater_greater; ///< operator >>
        static constexpr Self LESS_LESS_EQUALS = std::meta::operators::op_less_less_equals; ///< operator <<=
        static constexpr Self GREATER_GREATER_EQUALS = std::meta::operators::op_greater_greater_equals; ///< operator >>=
        static constexpr Self PLUS_PLUS = std::meta::operators::op_plus_plus; ///< operator ++
        static constexpr Self MINUS_MINUS = std::meta::operators::op_minus_minus; ///< operator --
        static constexpr Self COMMA = std::meta::operators::op_comma; ///< operator ,
    private:
        const Self value;
    public:
        constexpr Operators(Self value) noexcept:
            value{value} {}

        constexpr operator Self() const noexcept {
            return value;
        }

        [[nodiscard]]
        consteval std::string_view symbol() const noexcept {
            return std::meta::symbol_of(value);
        }

        [[nodiscard]]
        consteval std::u8string_view utf8Symbol() const noexcept {
            return std::meta::u8symbol_of(value);
        }
    };

    /**
     * @enum ReflectionOf
     * @brief The kind of entity reflected by a std::meta::info. Used for type dispatch in Mirror and its subclasses.
     */
    enum class ReflectionOf: std::uint8_t {
        NONE, ///< Null reflection
        SCALAR, ///< A value of scalar type
        STATIC_OBJECT, ///< An object of static storage duration
        VARIABLE, ///< A variable
        STRUCTURED_BINDING, ///< A structured binding
        FUNCTION, ///< A function
        FUNCTION_PARAMETER, ///< A function parameter
        ENUM, ///< An enumerator
        ANNOTATION, ///< An annotation
        TYPE_ALIAS, ///< A type alias
        TYPE, ///< A type
        MEMBER, ///< A class member
        UNNAMED_BIT_FIELD, ///< An unnamed bit-field
        CLASS_TEMPLATE, ///< A class template
        FUNCTION_TEMPLATE, ///< A function template
        VARIABLE_TEMPLATE, ///< A variable template
        ALIAS_TEMPLATE, ///< An alias template
        CONCEPT, ///< A concept
        NAMESPACE_ALIAS, ///< A namespace alias
        NAMESPACE, ///< A namespace
        BASE_CLASS, ///< A direct base class relationship
        DATA_MEMBER_DESCRIPTION, ///< A data member description
    };

    /**
     * @enum Modifier
     * @brief The kind of modifier applied to an entity.
     */
    enum class Modifier: std::uint8_t {
        ALIGNAS, ///< The entity is declared with an alignas specifier or has an alignment specified by the implementation.
        ALIGNOF, ///< The entity is declared with an alignof specifier or has an alignment specified by the implementation.
        CONST, ///< The entity is const-qualified.
        CONSTEVAL, ///< The entity is declared with the consteval specifier.
        CONSTEXPR, ///< The entity is declared with the constexpr specifier.
        CONSTINIT, ///< The entity is declared with the constinit specifier.
        EXPLICIT, ///< The entity is declared with the explicit specifier.
        EXTERN, ///< The entity is declared with the extern specifier or has external linkage.
        FINAL, ///< The entity is declared with the final specifier.
        FRIEND, ///< The entity is a friend of some class.
        INLINE, ///< The entity is declared with the inline specifier.
        MUTABLE, ///< The entity is declared with the mutable specifier.
        NOEXCEPT, ///< The entity is declared with the noexcept specifier.
        OVERRIDE, ///< The entity is declared with the override specifier.
        PRIVATE, ///< The entity is private.
        PROTECTED, ///< The entity is protected.
        PUBLIC, ///< The entity is public.
        RESTRICT, ///< The entity is declared with the restrict specifier.
        SIGNED, ///< The entity is declared with the signed specifier or is of a signed integer type.
        STATIC, ///< The entity is declared with the static specifier or has static storage duration.
        THREAD_LOCAL, ///< The entity is declared with the thread_local specifier or has thread storage duration.
        UNSIGNED, ///< The entity is declared with the unsigned specifier or is of an unsigned integer type.
        VIRTUAL, ///< The entity is declared with the virtual specifier or is a virtual member function.
        VOLATILE, ///< The entity is volatile-qualified.
    };

    /**
     * @enum AccessFlag
     * @brief Access level of a class member.
     */
    enum class AccessFlag: std::uint8_t {
        PUBLIC, ///< Public access (default for non-class-scope entities)
        PROTECTED, ///< Protected access (class members declared protected)
        PRIVATE, ///< Private access (class members declared private)
    };

    /**
     * @enum CvQualifier
     * @brief CV qualifiers, which apply to types, member functions, and data members.
     */
    enum class CvQualifier: std::uint8_t {
        CONST, ///< The entity is const-qualified.
        VOLATILE, ///< The entity is volatile-qualified.
    };

    /**
     * @enum RefQualifier
     * @brief Reference qualifier on a member function (&, &&, or unqualified).
     */
    enum class RefQualifier: std::uint8_t {
        NONE, ///< No reference qualifier
        LVALUE, ///< Lvalue reference qualifier (&)
        RVALUE, ///< Rvalue reference qualifier (&&)
    };

    /**
     * @enum FunctionSpecifier
     * @brief Specifiers that may appear on functions, methods, constructors, and destructors.
     *
     * Not every specifier is meaningful on every kind of entity; methods that return
     * a std::set<FunctionSpecifier> only populate the bits applicable to that entity.
     */
    enum class FunctionSpecifier: std::uint8_t {
        VIRTUAL, ///< The function is virtual.
        PURE_VIRTUAL, ///< The function is pure virtual.
        OVERRIDE, ///< The function is declared with the override specifier.
        FINAL, ///< The function is declared with the final specifier.
        EXPLICIT, ///< The function is declared with the explicit specifier (constructors only).
        NOEXCEPT, ///< The function is declared with the noexcept specifier.
        STATIC, ///< The function is declared with the static specifier (methods only) or is a static member function.
        DELETED, ///< The function is deleted.
        DEFAULTED, ///< The function is defaulted.
    };

    /**
     * @enum StorageClass
     * @brief Storage class of a variable or static data member.
     */
    enum class StorageClass: std::uint8_t {
        NONE, ///< No storage class (automatic storage duration for variables, non-static for data members)
        AUTOMATIC, ///< Automatic storage duration (local variables)
        STATIC, ///< Static storage duration (variables declared with static or data members declared with static)
        THREAD_LOCAL, ///< Thread storage duration (variables declared with thread_local or data members declared with thread_local)
    };

    /**
     * @enum Linkage
     * @brief Linkage of a named entity.
     */
    enum class Linkage: std::uint8_t {
        NONE, ///< No linkage (local variables, unnamed entities)
        INTERNAL, ///< Internal linkage (entities declared in an unnamed namespace or with the static specifier at namespace scope)
        MODULE, ///< Module linkage (entities declared in a named module interface unit or with the export specifier)
        EXTERNAL, ///< External linkage (entities declared at namespace scope that do not have internal or module linkage)
        EXTERN_C, ///< C language linkage (entities declared with extern "C")
    };

    /**
     * @class Mirror
     * @brief Base wrapper that pairs every reflection entity with the
     * operations applicable to any reflection.
     *
     * Holds a single info. Concrete subclasses (Field, Method, ...)
     * narrow the kind and add operations specific to that kind.
     */
    class Mirror {
    public:
        static const Mirror NONE; ///< The null reflection, created from a default-constructed std::meta::info primitive.

        const std::meta::info _info; ///< The underlying reflection. Public, so that the type satisfies the "structural type" rule.

        consteval Mirror() noexcept = default;

        consteval Mirror(std::meta::info i) noexcept:
            _info{i} {}

        /**
         * @brief Returns the underlying info primitive.
         * @return The underlying info primitive.
         */
        [[nodiscard]]
        consteval std::meta::info value() const noexcept {
            return _info;
        }

        [[nodiscard]]
        consteval operator std::meta::info() const noexcept {
            return _info;
        }

        /**
         * @brief The entity's identifier, or nullopt if it is unnamed
         * (anonymous structs, unnamed bit-fields, etc.).
         * @return The identifier, or nullopt if the entity is unnamed.
         */
        [[nodiscard]]
        consteval std::optional<std::string_view> name() const {
            if (!std::meta::has_identifier(_info)) {
                return std::nullopt;
            }
            return std::meta::identifier_of(_info);
        }

        /**
         * @brief UTF-8 form of name(). Returns nullopt under the same
         * conditions as name().
         * @return The UTF-8 identifier, or nullopt if the entity is unnamed.
         */
        [[nodiscard]]
        consteval std::optional<std::u8string_view> utf8Name() const {
            if (!std::meta::has_identifier(_info)) {
                return std::nullopt;
            }
            return std::meta::u8identifier_of(_info);
        }

        [[nodiscard]]
        consteval std::string_view displayName() const {
            return std::meta::display_string_of(_info);
        }

        [[nodiscard]]
        consteval std::u8string_view utf8DisplayName() const {
            return std::meta::u8display_string_of(_info);
        }

        [[nodiscard]]
        consteval std::source_location location() const {
            return std::meta::source_location_of(_info);
        }

        [[nodiscard]]
        consteval bool isType() const {
            return std::meta::is_type(_info);
        }

        [[nodiscard]]
        consteval bool isNamespace() const {
            return std::meta::is_namespace(_info);
        }

        [[nodiscard]]
        consteval bool isFunction() const {
            return std::meta::is_function(_info);
        }

        [[nodiscard]]
        consteval bool isVariable() const {
            return std::meta::is_variable(_info);
        }

        [[nodiscard]]
        consteval bool isTemplate() const {
            return std::meta::is_template(_info);
        }

        [[nodiscard]]
        consteval bool isConcept() const {
            return std::meta::is_concept(_info);
        }

        [[nodiscard]]
        consteval bool isValue() const {
            return std::meta::is_value(_info);
        }

        [[nodiscard]]
        consteval bool isObject() const {
            return std::meta::is_object(_info);
        }

        [[nodiscard]]
        consteval bool isTypeAlias() const {
            return std::meta::is_type_alias(_info);
        }

        [[nodiscard]]
        consteval bool isNamespaceAlias() const {
            return std::meta::is_namespace_alias(_info);
        }

        [[nodiscard]]
        consteval bool isAnnotation() const {
            return std::meta::is_annotation(_info);
        }

        [[nodiscard]]
        consteval bool isEnumerator() const {
            return std::meta::is_enumerator(_info);
        }

        [[nodiscard]]
        consteval bool isStructuredBinding() const {
            return std::meta::is_structured_binding(_info);
        }

        [[nodiscard]]
        consteval bool isClassMember() const {
            return std::meta::is_class_member(_info);
        }

        [[nodiscard]]
        consteval bool isNamespaceMember() const {
            return std::meta::is_namespace_member(_info);
        }

        [[nodiscard]]
        consteval bool isStaticMember() const {
            return std::meta::is_static_member(_info);
        }

        [[nodiscard]]
        consteval bool isNonstaticDataMember() const {
            return std::meta::is_nonstatic_data_member(_info);
        }

        [[nodiscard]]
        consteval bool isBase() const {
            return std::meta::is_base(_info);
        }

        /**
         * @brief The enclosing entity (the namespace, class, function, etc.
         * that this entity is declared inside), or nullopt for the global
         * namespace.
         * @return The parent entity as {@code Mirror}, or nullopt for the global namespace.
         */
        [[nodiscard]]
        consteval std::optional<Mirror> parent() const {
            if (!std::meta::has_parent(_info)) {
                return std::nullopt;
            }
            return Mirror(std::meta::parent_of(_info));
        }

        /**
         * @brief True iff this reflection is the global namespace.
         * @return Whether the reflection is of the global namespace.
         */
        [[nodiscard]]
        consteval bool isGlobalNamespace() const {
            return std::meta::is_namespace(_info) && !std::meta::has_parent(_info);
        }

        /**
         * @brief True iff this entity is declared directly at global namespace
         * scope. False for the global namespace itself.
         * @return Whether the entity is in the global namespace.
         */
        [[nodiscard]]
        consteval bool isInGlobalNamespace() const {
            if (!std::meta::has_parent(_info)) {
                return false;
            }
            const std::meta::info p = std::meta::parent_of(_info);
            return std::meta::is_namespace(p) && !std::meta::has_parent(p);
        }

        /**
         * @brief Number of enclosing entities up to (but not including) the
         * global namespace. Counts class scopes, function scopes, etc.
         * @return An unsigned integer representing the number of enclosing scopes,
         * excluding the global namespace.
         *
         * For std::chrono::duration::operator+, returns 4 (operator+ -> duration
         * -> chrono -> std -> global). For the global namespace itself, returns 0.
         */
        [[nodiscard]]
        consteval std::size_t scopeDepth() const {
            std::size_t d = 0;
            std::meta::info cur = _info;
            while (std::meta::has_parent(cur)) {
                cur = std::meta::parent_of(cur);
                ++d;
            }
            return d;
        }

        /**
         * @brief Number of enclosing namespaces up to (but not including) the
         * global namespace. Skips class and other non-namespace scopes.
         * @return An unsigned integer representing the number of enclosing namespace scopes,
         * excluding the global namespace.
         *
         * For std::chrono::duration, returns 2 (chrono, std).
         */
        [[nodiscard]]
        consteval std::size_t namespaceDepth() const {
            std::size_t d = 0;
            std::meta::info cur = _info;
            while (std::meta::has_parent(cur)) {
                cur = std::meta::parent_of(cur);
                if (std::meta::is_namespace(cur)) {
                    ++d;
                }
            }
            return d;
        }

        /**
         * @brief All enclosing scopes from outermost to innermost (excludes
         * this entity itself).
         * @return A list of enclosing scopes (as {@code Mirror}) in ascending order of scope.
         *
         * For ::std::filesystem::path, returns { ::, std, filesystem }. Empty for the global namespace.
         */
        [[nodiscard]]
        consteval std::vector<Mirror> scopeChain() const {
            std::vector<Mirror> tmp;
            std::meta::info cur = _info;
            while (std::meta::has_parent(cur)) {
                cur = std::meta::parent_of(cur);
                tmp.emplace_back(cur);
            }
            std::vector<Mirror> result;
            result.reserve(tmp.size());
            for (std::size_t i = tmp.size(); i > 0; --i) {
                result.emplace_back(tmp[i - 1]._info);
            }
            return result;
        }

        /**
         * @brief Innermost enclosing class, or nullopt if this entity is not
         * declared inside any class (e.g. namespace-scoped entities).
         * @return The innermost enclosing class.
         */
        [[nodiscard]]
        consteval std::optional<Type> enclosingClass() const;

        /**
         * @brief Innermost enclosing namespace. For the global namespace
         * itself, returns the global namespace. Walks through class scopes
         * to find the first namespace ancestor.
         * @return The innermost enclosing namespace.
         */
        [[nodiscard]]
        consteval Namespace enclosingNamespace() const;

        [[nodiscard]]
        consteval AccessFlag access() const {
            if (std::meta::is_protected(_info)) {
                return AccessFlag::PROTECTED;
            }
            if (std::meta::is_private(_info)) {
                return AccessFlag::PRIVATE;
            }
            return AccessFlag::PUBLIC;
        }

        [[nodiscard]]
        consteval EnumSet<ReflectionOf> kinds() const {
            if (_info == Mirror::NONE.value()) {
                return EnumSet<ReflectionOf>::of(ReflectionOf::NONE);
            }
            EnumSet<ReflectionOf> result;
            if (std::meta::is_value(_info)) {
                result.insert(ReflectionOf::SCALAR);
            }
            if (std::meta::is_object(_info)) {
                result.insert(ReflectionOf::STATIC_OBJECT);
            }
            if (std::meta::is_variable(_info)) {
                result.insert(ReflectionOf::VARIABLE);
            }
            if (std::meta::is_structured_binding(_info)) {
                result.insert(ReflectionOf::STRUCTURED_BINDING);
            }
            if (std::meta::is_function(_info)) {
                result.insert(ReflectionOf::FUNCTION);
            }
            if (std::meta::is_function_parameter(_info)) {
                result.insert(ReflectionOf::FUNCTION_PARAMETER);
            }
            if (std::meta::is_enumerator(_info)) {
                result.insert(ReflectionOf::ENUM);
            }
            if (std::meta::is_annotation(_info)) {
                result.insert(ReflectionOf::ANNOTATION);
            }
            if (std::meta::is_type_alias(_info)) {
                result.insert(ReflectionOf::TYPE_ALIAS);
            }
            if (std::meta::is_type(_info)) {
                result.insert(ReflectionOf::TYPE);
            }
            if (std::meta::is_class_member(_info)) {
                result.insert(ReflectionOf::MEMBER);
            }
            if (std::meta::is_bit_field(_info) && !std::meta::has_identifier(_info)) {
                result.insert(ReflectionOf::UNNAMED_BIT_FIELD);
            }
            if (std::meta::is_class_template(_info)) {
                result.insert(ReflectionOf::CLASS_TEMPLATE);
            }
            if (std::meta::is_function_template(_info)) {
                result.insert(ReflectionOf::FUNCTION_TEMPLATE);
            }
            if (std::meta::is_variable_template(_info)) {
                result.insert(ReflectionOf::VARIABLE_TEMPLATE);
            }
            if (std::meta::is_alias_template(_info)) {
                result.insert(ReflectionOf::ALIAS_TEMPLATE);
            }
            if (std::meta::is_concept(_info)) {
                result.insert(ReflectionOf::CONCEPT);
            }
            if (std::meta::is_namespace_alias(_info)) {
                result.insert(ReflectionOf::NAMESPACE_ALIAS);
            }
            if (std::meta::is_namespace(_info)) {
                result.insert(ReflectionOf::NAMESPACE);
            }
            if (std::meta::is_base(_info)) {
                result.insert(ReflectionOf::BASE_CLASS);
            }
            if (std::meta::is_data_member_spec(_info)) {
                result.insert(ReflectionOf::DATA_MEMBER_DESCRIPTION);
            }
            return result;
        }

        [[nodiscard]]
        consteval std::vector<Annotation> annotations() const;

        template <typename T>
        [[nodiscard]]
        consteval std::vector<Annotation> annotationsWithType() const;

        [[nodiscard]]
        constexpr bool operator==(const Mirror& other) const noexcept = default;
    };

    inline constexpr Mirror Mirror::NONE{std::meta::info{}};

    /**
     * @class Type
     * @brief Wraps the reflection of a type.
     * @extends Mirror
     *
     * Exposes the full battery of type traits (size, alignment, category
     * tests, qualifier removal/addition, relations). Subclassed by
     * Class<T>, Enum<E>, and Union<U> for entities whose type is
     * known statically.
     */
    class Type: public Mirror {
    public:
        consteval explicit Type(std::meta::info i):
            Mirror(i) {
            if (i != Mirror::NONE.value() && !std::meta::is_type(i)) {
                throw std::meta::exception("Provided std::meta::info is not a type", ^^Type);
            }
        }

        template <typename T>
        [[nodiscard]]
        static consteval Type of() {
            return Type(^^T);
        }

        [[nodiscard]]
        consteval std::size_t size() const {
            return std::meta::size_of(_info);
        }

        [[nodiscard]]
        consteval std::size_t alignment() const {
            return std::meta::alignment_of(_info);
        }

        [[nodiscard]]
        consteval std::size_t bitSize() const {
            return std::meta::bit_size_of(_info);
        }

        [[nodiscard]]
        consteval bool isVoid() const {
            return std::meta::is_void_type(_info);
        }

        [[nodiscard]]
        consteval bool isNullPointer() const {
            return std::meta::is_null_pointer_type(_info);
        }

        [[nodiscard]]
        consteval bool isIntegral() const {
            return std::meta::is_integral_type(_info);
        }

        [[nodiscard]]
        consteval bool isFloatingPoint() const {
            return std::meta::is_floating_point_type(_info);
        }

        [[nodiscard]]
        consteval bool isArray() const {
            return std::meta::is_array_type(_info);
        }

        [[nodiscard]]
        consteval bool isPointer() const {
            return std::meta::is_pointer_type(_info);
        }

        [[nodiscard]]
        consteval bool isReference() const {
            return std::meta::is_reference_type(_info);
        }

        [[nodiscard]]
        consteval bool isLvalueReference() const {
            return std::meta::is_lvalue_reference_type(_info);
        }

        [[nodiscard]]
        consteval bool isRvalueReference() const {
            return std::meta::is_rvalue_reference_type(_info);
        }

        [[nodiscard]]
        consteval bool isEnum() const {
            return std::meta::is_enum_type(_info);
        }

        [[nodiscard]]
        consteval bool isUnion() const {
            return std::meta::is_union_type(_info);
        }

        [[nodiscard]]
        consteval bool isClass() const {
            return std::meta::is_class_type(_info) && !std::meta::is_union_type(_info);
        }

        [[nodiscard]]
        consteval bool isRecord() const {
            return std::meta::is_class_type(_info);
        }

        [[nodiscard]]
        consteval bool isFunctionType() const {
            return std::meta::is_function_type(_info);
        }

        [[nodiscard]]
        consteval bool isMemberPointer() const {
            return std::meta::is_member_pointer_type(_info);
        }

        [[nodiscard]]
        consteval bool isMemberObjectPointer() const {
            return std::meta::is_member_object_pointer_type(_info);
        }

        [[nodiscard]]
        consteval bool isMemberFunctionPointer() const {
            return std::meta::is_member_function_pointer_type(_info);
        }

        [[nodiscard]]
        consteval bool isReflection() const {
            return std::meta::is_reflection_type(_info);
        }

        [[nodiscard]]
        consteval bool isArithmetic() const {
            return std::meta::is_arithmetic_type(_info);
        }

        [[nodiscard]]
        consteval bool isFundamental() const {
            return std::meta::is_fundamental_type(_info);
        }

        [[nodiscard]]
        consteval bool isScalar() const {
            return std::meta::is_scalar_type(_info);
        }

        [[nodiscard]]
        consteval bool isObjectType() const {
            return std::meta::is_object_type(_info);
        }

        [[nodiscard]]
        consteval bool isCompound() const {
            return std::meta::is_compound_type(_info);
        }

        [[nodiscard]]
        consteval bool isConst() const {
            return std::meta::is_const_type(_info);
        }

        [[nodiscard]]
        consteval bool isVolatile() const {
            return std::meta::is_volatile_type(_info);
        }

        [[nodiscard]]
        consteval bool isTriviallyCopyable() const {
            return std::meta::is_trivially_copyable_type(_info);
        }

        [[nodiscard]]
        consteval bool isStandardLayout() const {
            return std::meta::is_standard_layout_type(_info);
        }

        [[nodiscard]]
        consteval bool isEmpty() const {
            return std::meta::is_empty_type(_info);
        }

        [[nodiscard]]
        consteval bool isPolymorphic() const {
            return std::meta::is_polymorphic_type(_info);
        }

        [[nodiscard]]
        consteval bool isAbstract() const {
            return std::meta::is_abstract_type(_info);
        }

        [[nodiscard]]
        consteval bool isFinal() const {
            return std::meta::is_final_type(_info);
        }

        [[nodiscard]]
        consteval bool isAggregate() const {
            return std::meta::is_aggregate_type(_info);
        }

        [[nodiscard]]
        consteval bool isSigned() const {
            return std::meta::is_signed_type(_info);
        }

        [[nodiscard]]
        consteval bool isUnsigned() const {
            return std::meta::is_unsigned_type(_info);
        }

        [[nodiscard]]
        consteval bool isBoundedArray() const {
            return std::meta::is_bounded_array_type(_info);
        }

        [[nodiscard]]
        consteval bool isUnboundedArray() const {
            return std::meta::is_unbounded_array_type(_info);
        }

        [[nodiscard]]
        consteval bool isScopedEnum() const {
            return std::meta::is_scoped_enum_type(_info);
        }

        [[nodiscard]]
        consteval bool isComplete() const {
            return std::meta::is_complete_type(_info);
        }

        [[nodiscard]]
        consteval bool isEnumerable() const {
            return std::meta::is_enumerable_type(_info);
        }

        [[nodiscard]]
        consteval bool isImplicitLifetime() const {
            return std::meta::is_implicit_lifetime_type(_info);
        }

        [[nodiscard]]
        consteval bool hasVirtualDestructor() const {
            return std::meta::has_virtual_destructor(_info);
        }

        [[nodiscard]]
        consteval bool hasUniqueObjectRepresentations() const {
            return std::meta::has_unique_object_representations(_info);
        }

        [[nodiscard]]
        consteval bool isDefaultConstructible() const {
            return std::meta::is_default_constructible_type(_info);
        }

        [[nodiscard]]
        consteval bool isCopyConstructible() const {
            return std::meta::is_copy_constructible_type(_info);
        }

        [[nodiscard]]
        consteval bool isMoveConstructible() const {
            return std::meta::is_move_constructible_type(_info);
        }

        [[nodiscard]]
        consteval bool isCopyAssignable() const {
            return std::meta::is_copy_assignable_type(_info);
        }

        [[nodiscard]]
        consteval bool isMoveAssignable() const {
            return std::meta::is_move_assignable_type(_info);
        }

        [[nodiscard]]
        consteval bool isDestructible() const {
            return std::meta::is_destructible_type(_info);
        }

        [[nodiscard]]
        consteval bool isSwappable() const {
            return std::meta::is_swappable_type(_info);
        }

        [[nodiscard]]
        consteval bool isTriviallyDefaultConstructible() const {
            return std::meta::is_trivially_default_constructible_type(_info);
        }

        [[nodiscard]]
        consteval bool isTriviallyCopyConstructible() const {
            return std::meta::is_trivially_copy_constructible_type(_info);
        }

        [[nodiscard]]
        consteval bool isTriviallyMoveConstructible() const {
            return std::meta::is_trivially_move_constructible_type(_info);
        }

        [[nodiscard]]
        consteval bool isTriviallyCopyAssignable() const {
            return std::meta::is_trivially_copy_assignable_type(_info);
        }

        [[nodiscard]]
        consteval bool isTriviallyMoveAssignable() const {
            return std::meta::is_trivially_move_assignable_type(_info);
        }

        [[nodiscard]]
        consteval bool isTriviallyDestructible() const {
            return std::meta::is_trivially_destructible_type(_info);
        }

        [[nodiscard]]
        consteval bool isNothrowDefaultConstructible() const {
            return std::meta::is_nothrow_default_constructible_type(_info);
        }

        [[nodiscard]]
        consteval bool isNothrowCopyConstructible() const {
            return std::meta::is_nothrow_copy_constructible_type(_info);
        }

        [[nodiscard]]
        consteval bool isNothrowMoveConstructible() const {
            return std::meta::is_nothrow_move_constructible_type(_info);
        }

        [[nodiscard]]
        consteval bool isNothrowCopyAssignable() const {
            return std::meta::is_nothrow_copy_assignable_type(_info);
        }

        [[nodiscard]]
        consteval bool isNothrowMoveAssignable() const {
            return std::meta::is_nothrow_move_assignable_type(_info);
        }

        [[nodiscard]]
        consteval bool isNothrowDestructible() const {
            return std::meta::is_nothrow_destructible_type(_info);
        }

        [[nodiscard]]
        consteval bool isNothrowSwappable() const {
            return std::meta::is_nothrow_swappable_type(_info);
        }

        [[nodiscard]]
        consteval std::size_t rank() const {
            return std::meta::rank(_info);
        }

        [[nodiscard]]
        consteval std::size_t extent(std::size_t dim = 0uz) const {
            return std::meta::extent(_info, dim);
        }

        [[nodiscard]]
        consteval Type removeConst() const {
            return Type(std::meta::remove_const(_info));
        }

        [[nodiscard]]
        consteval Type removeVolatile() const {
            return Type(std::meta::remove_volatile(_info));
        }

        [[nodiscard]]
        consteval Type removeCv() const {
            return Type(std::meta::remove_cv(_info));
        }

        [[nodiscard]]
        consteval Type addConst() const {
            return Type(std::meta::add_const(_info));
        }

        [[nodiscard]]
        consteval Type addVolatile() const {
            return Type(std::meta::add_volatile(_info));
        }

        [[nodiscard]]
        consteval Type addCv() const {
            return Type(std::meta::add_cv(_info));
        }

        [[nodiscard]]
        consteval Type removeReference() const {
            return Type(std::meta::remove_reference(_info));
        }

        [[nodiscard]]
        consteval Type addLvalueReference() const {
            return Type(std::meta::add_lvalue_reference(_info));
        }

        [[nodiscard]]
        consteval Type addRvalueReference() const {
            return Type(std::meta::add_rvalue_reference(_info));
        }

        [[nodiscard]]
        consteval Type removePointer() const {
            return Type(std::meta::remove_pointer(_info));
        }

        [[nodiscard]]
        consteval Type addPointer() const {
            return Type(std::meta::add_pointer(_info));
        }

        [[nodiscard]]
        consteval Type removeCvRef() const {
            return Type(std::meta::remove_cvref(_info));
        }

        [[nodiscard]]
        consteval Type decay() const {
            return Type(std::meta::decay(_info));
        }

        [[nodiscard]]
        consteval Type removeExtent() const {
            return Type(std::meta::remove_extent(_info));
        }

        [[nodiscard]]
        consteval Type removeAllExtents() const {
            return Type(std::meta::remove_all_extents(_info));
        }

        [[nodiscard]]
        consteval Type makeSigned() const {
            return Type(std::meta::make_signed(_info));
        }

        [[nodiscard]]
        consteval Type makeUnsigned() const {
            return Type(std::meta::make_unsigned(_info));
        }

        [[nodiscard]]
        consteval Type underlying() const {
            return Type(std::meta::underlying_type(_info));
        }

        [[nodiscard]]
        consteval Type dealias() const {
            return Type(std::meta::dealias(_info));
        }

        [[nodiscard]]
        consteval bool sameAs(Type other) const {
            return std::meta::is_same_type(_info, other._info);
        }

        [[nodiscard]]
        consteval bool baseOf(Type other) const {
            return std::meta::is_base_of_type(_info, other._info);
        }

        [[nodiscard]]
        consteval bool virtualBaseOf(Type other) const {
            return std::meta::is_virtual_base_of_type(_info, other._info);
        }

        [[nodiscard]]
        consteval bool convertibleTo(Type other) const {
            return std::meta::is_convertible_type(_info, other._info);
        }

        [[nodiscard]]
        consteval bool nothrowConvertibleTo(Type other) const {
            return std::meta::is_nothrow_convertible_type(_info, other._info);
        }

        [[nodiscard]]
        consteval bool layoutCompatibleWith(Type other) const {
            return std::meta::is_layout_compatible_type(_info, other._info);
        }

        [[nodiscard]]
        consteval bool pointerInterconvertibleBaseOf(Type other) const {
            return std::meta::is_pointer_interconvertible_base_of_type(_info, other._info);
        }

        [[nodiscard]]
        consteval bool hasTemplateArguments() const {
            return std::meta::has_template_arguments(_info);
        }

        [[nodiscard]]
        consteval std::vector<Mirror> templateArguments() const {
            std::vector<Mirror> result;
            for (std::meta::info a: std::meta::template_arguments_of(_info)) {
                result.emplace_back(a);
            }
            return result;
        }

        [[nodiscard]]
        consteval EnumSet<CvQualifier> cvQualifiers() const {
            EnumSet<CvQualifier> result;
            if (std::meta::is_const_type(_info)) {
                result.insert(CvQualifier::CONST);
            }
            if (std::meta::is_volatile_type(_info)) {
                result.insert(CvQualifier::VOLATILE);
            }
            return result;
        }

        [[nodiscard]]
        consteval Template templateOf() const;
    };

    /**
     * @class Parameter
     * @brief A parameter of a function.
     * @extends Mirror
     */
    class Parameter: public Mirror {
    public:
        consteval explicit Parameter(std::meta::info i):
            Mirror(i) {
            if (i != Mirror::NONE.value() && !std::meta::is_function_parameter(i)) {
                throw std::meta::exception("Provided std::meta::info is not a function parameter", ^^Parameter);
            }
        }

        [[nodiscard]]
        consteval Type type() const {
            return Type(std::meta::type_of(_info));
        }

        [[nodiscard]]
        consteval bool hasDefault() const {
            return std::meta::has_default_argument(_info);
        }

        [[nodiscard]]
        consteval bool isExplicitObject() const {
            return std::meta::is_explicit_object_parameter(_info);
        }

        [[nodiscard]]
        consteval bool isFunctionParameter() const {
            return std::meta::is_function_parameter(_info);
        }
    };

    /**
     * @class Callback
     * @brief A free or unspecified function. Member functions are
     * represented by Method, constructors/destructors by their
     * own wrappers.
     * @extends Mirror
     */
    class Callback: public Mirror {
    public:
        consteval explicit Callback(std::meta::info i):
            Mirror(i) {
            if (i != Mirror::NONE.value() && !std::meta::is_function(i)) {
                throw std::meta::exception("Provided std::meta::info is not a function", ^^Callback);
            }
        }

        [[nodiscard]]
        consteval Type returnType() const {
            return Type(std::meta::return_type_of(_info));
        }

        [[nodiscard]]
        consteval std::vector<Parameter> parameters() const {
            std::vector<Parameter> result;
            for (std::meta::info p: std::meta::parameters_of(_info)) {
                result.emplace_back(p);
            }
            return result;
        }

        [[nodiscard]]
        consteval bool isNoexcept() const {
            return std::meta::is_noexcept(_info);
        }

        [[nodiscard]]
        consteval bool isDeleted() const {
            return std::meta::is_deleted(_info);
        }

        [[nodiscard]]
        consteval bool isDefaulted() const {
            return std::meta::is_defaulted(_info);
        }

        [[nodiscard]]
        consteval bool isExplicit() const {
            return std::meta::is_explicit(_info);
        }

        [[nodiscard]]
        consteval bool isUserProvided() const {
            return std::meta::is_user_provided(_info);
        }

        [[nodiscard]]
        consteval bool isUserDeclared() const {
            return std::meta::is_user_declared(_info);
        }

        [[nodiscard]]
        consteval bool isVararg() const {
            return std::meta::is_vararg_function(_info);
        }

        [[nodiscard]]
        consteval bool isConversion() const {
            return std::meta::is_conversion_function(_info);
        }

        [[nodiscard]]
        consteval bool isOperator() const {
            return std::meta::is_operator_function(_info);
        }

        [[nodiscard]]
        consteval bool isLiteralOperator() const {
            return std::meta::is_literal_operator(_info);
        }

        [[nodiscard]]
        consteval std::string_view operatorSymbol() const {
            return std::meta::symbol_of(std::meta::operator_of(_info));
        }

        [[nodiscard]]
        consteval std::u8string_view utf8OperatorSymbol() const {
            return std::meta::u8symbol_of(std::meta::operator_of(_info));
        }
    };

    /**
     * @class Method
     * @brief A method of a class.
     * @extends Callback
     */
    class Method: public Callback {
    public:
        consteval explicit Method(std::meta::info i):
            Callback(i) {
            if (i != Mirror::NONE.value() &&
                (!std::meta::is_class_member(i) || std::meta::is_constructor(i) || std::meta::is_destructor(i)))
            {
                throw std::meta::exception("Provided std::meta::info is not a (non-special) class member function", ^^Method);
            }
        }

        [[nodiscard]]
        consteval Type declaringClass() const {
            return Type(std::meta::parent_of(_info));
        }

        [[nodiscard]]
        consteval bool isPublic() const {
            return std::meta::is_public(_info);
        }

        [[nodiscard]]
        consteval bool isProtected() const {
            return std::meta::is_protected(_info);
        }

        [[nodiscard]]
        consteval bool isPrivate() const {
            return std::meta::is_private(_info);
        }

        [[nodiscard]]
        consteval bool isVirtual() const {
            return std::meta::is_virtual(_info);
        }

        [[nodiscard]]
        consteval bool isPureVirtual() const {
            return std::meta::is_pure_virtual(_info);
        }

        [[nodiscard]]
        consteval bool isOverride() const {
            return std::meta::is_override(_info);
        }

        [[nodiscard]]
        consteval bool isFinal() const {
            return std::meta::is_final(_info);
        }

        [[nodiscard]]
        consteval bool isStatic() const {
            return std::meta::is_static_member(_info);
        }

        [[nodiscard]]
        consteval bool isConst() const {
            return std::meta::is_const(_info);
        }

        [[nodiscard]]
        consteval bool isVolatile() const {
            return std::meta::is_volatile(_info);
        }

        [[nodiscard]]
        consteval bool isLvalueRefQualified() const {
            return std::meta::is_lvalue_reference_qualified(_info);
        }

        [[nodiscard]]
        consteval bool isRvalueRefQualified() const {
            return std::meta::is_rvalue_reference_qualified(_info);
        }

        [[nodiscard]]
        consteval bool isSpecialMember() const {
            return std::meta::is_special_member_function(_info);
        }

        [[nodiscard]]
        consteval bool isAssignment() const {
            return std::meta::is_assignment(_info);
        }

        [[nodiscard]]
        consteval bool isCopyAssignment() const {
            return std::meta::is_copy_assignment(_info);
        }

        [[nodiscard]]
        consteval bool isMoveAssignment() const {
            return std::meta::is_move_assignment(_info);
        }

        [[nodiscard]]
        consteval EnumSet<CvQualifier> cvQualifiers() const {
            EnumSet<CvQualifier> result;
            if (std::meta::is_const(_info)) {
                result.insert(CvQualifier::CONST);
            }
            if (std::meta::is_volatile(_info)) {
                result.insert(CvQualifier::VOLATILE);
            }
            return result;
        }

        [[nodiscard]]
        consteval RefQualifier refQualifier() const {
            if (std::meta::is_lvalue_reference_qualified(_info)) {
                return RefQualifier::LVALUE;
            }
            if (std::meta::is_rvalue_reference_qualified(_info)) {
                return RefQualifier::RVALUE;
            }
            return RefQualifier::NONE;
        }

        [[nodiscard]]
        consteval EnumSet<FunctionSpecifier> specifiers() const {
            EnumSet<FunctionSpecifier> result;
            if (std::meta::is_virtual(_info)) {
                result.insert(FunctionSpecifier::VIRTUAL);
            }
            if (std::meta::is_pure_virtual(_info)) {
                result.insert(FunctionSpecifier::PURE_VIRTUAL);
            }
            if (std::meta::is_override(_info)) {
                result.insert(FunctionSpecifier::OVERRIDE);
            }
            if (std::meta::is_final(_info)) {
                result.insert(FunctionSpecifier::FINAL);
            }
            if (std::meta::is_explicit(_info)) {
                result.insert(FunctionSpecifier::EXPLICIT);
            }
            if (std::meta::is_noexcept(_info)) {
                result.insert(FunctionSpecifier::NOEXCEPT);
            }
            if (std::meta::is_static_member(_info)) {
                result.insert(FunctionSpecifier::STATIC);
            }
            if (std::meta::is_deleted(_info)) {
                result.insert(FunctionSpecifier::DELETED);
            }
            if (std::meta::is_defaulted(_info)) {
                result.insert(FunctionSpecifier::DEFAULTED);
            }
            return result;
        }
    };

    /**
     * @class Field
     * @brief A field of a class.
     * @extends Mirror
     */
    class Field: public Mirror {
    public:
        consteval explicit Field(std::meta::info i):
            Mirror(i) {
            if (i != Mirror::NONE.value() && !std::meta::is_nonstatic_data_member(i)) {
                throw std::meta::exception("Provided std::meta::info is not a non-static data member", ^^Field);
            }
        }

        [[nodiscard]]
        consteval Type type() const {
            return Type(std::meta::type_of(_info));
        }

        [[nodiscard]]
        consteval Type declaringClass() const {
            return Type(std::meta::parent_of(_info));
        }

        [[nodiscard]]
        consteval bool isPublic() const {
            return std::meta::is_public(_info);
        }

        [[nodiscard]]
        consteval bool isProtected() const {
            return std::meta::is_protected(_info);
        }

        [[nodiscard]]
        consteval bool isPrivate() const {
            return std::meta::is_private(_info);
        }

        [[nodiscard]]
        consteval bool isMutable() const {
            return std::meta::is_mutable_member(_info);
        }

        [[nodiscard]]
        consteval bool isBitField() const {
            return std::meta::is_bit_field(_info);
        }

        [[nodiscard]]
        consteval bool hasDefaultInitializer() const {
            return std::meta::has_default_member_initializer(_info);
        }

        [[nodiscard]]
        consteval std::meta::member_offset offset() const {
            return std::meta::offset_of(_info);
        }

        [[nodiscard]]
        consteval std::size_t bitSize() const {
            return std::meta::bit_size_of(_info);
        }

        [[nodiscard]]
        consteval EnumSet<CvQualifier> cvQualifiers() const {
            return Type(std::meta::type_of(_info)).cvQualifiers();
        }
    };

    /**
     * @class Variable
     * @brief A variable.
     * @extends Mirror
     */
    class Variable: public Mirror {
    public:
        consteval explicit Variable(std::meta::info i):
            Mirror(i) {
            if (i != Mirror::NONE.value() && !std::meta::is_variable(i)) {
                throw std::meta::exception("Provided std::meta::info is not a variable", ^^Variable);
            }
        }

        [[nodiscard]]
        consteval Type type() const {
            return Type(std::meta::type_of(_info));
        }

        [[nodiscard]]
        consteval bool isConst() const {
            return std::meta::is_const(_info);
        }

        [[nodiscard]]
        consteval bool isVolatile() const {
            return std::meta::is_volatile(_info);
        }

        [[nodiscard]]
        consteval bool hasStaticStorage() const {
            return std::meta::has_static_storage_duration(_info);
        }

        [[nodiscard]]
        consteval bool hasThreadStorage() const {
            return std::meta::has_thread_storage_duration(_info);
        }

        [[nodiscard]]
        consteval bool hasAutomaticStorage() const {
            return std::meta::has_automatic_storage_duration(_info);
        }

        [[nodiscard]]
        consteval bool hasInternalLinkage() const {
            return std::meta::has_internal_linkage(_info);
        }

        [[nodiscard]]
        consteval bool hasModuleLinkage() const {
            return std::meta::has_module_linkage(_info);
        }

        [[nodiscard]]
        consteval bool hasExternalLinkage() const {
            return std::meta::has_external_linkage(_info);
        }

        [[nodiscard]]
        consteval bool hasCLanguageLinkage() const {
            return std::meta::has_c_language_linkage(_info);
        }

        [[nodiscard]]
        consteval bool hasLinkage() const {
            return std::meta::has_linkage(_info);
        }

        [[nodiscard]]
        consteval bool isPublic() const {
            return std::meta::is_public(_info);
        }

        [[nodiscard]]
        consteval bool isProtected() const {
            return std::meta::is_protected(_info);
        }

        [[nodiscard]]
        consteval bool isPrivate() const {
            return std::meta::is_private(_info);
        }

        [[nodiscard]]
        consteval EnumSet<CvQualifier> cvQualifiers() const {
            return Type(std::meta::type_of(_info)).cvQualifiers();
        }

        [[nodiscard]]
        consteval StorageClass storageClass() const {
            if (std::meta::has_thread_storage_duration(_info)) {
                return StorageClass::THREAD_LOCAL;
            }
            if (std::meta::has_static_storage_duration(_info)) {
                return StorageClass::STATIC;
            }
            if (std::meta::has_automatic_storage_duration(_info)) {
                return StorageClass::AUTOMATIC;
            }
            return StorageClass::NONE;
        }

        [[nodiscard]]
        consteval Linkage linkage() const {
            if (std::meta::has_c_language_linkage(_info)) {
                return Linkage::EXTERN_C;
            }
            if (std::meta::has_external_linkage(_info)) {
                return Linkage::EXTERNAL;
            }
            if (std::meta::has_module_linkage(_info)) {
                return Linkage::MODULE;
            }
            if (std::meta::has_internal_linkage(_info)) {
                return Linkage::INTERNAL;
            }
            return Linkage::NONE;
        }
    };

    /**
     * @class Constructor
     * @brief Represents a constructor in the reflection system.
     * @extends Callback
     */
    class Constructor: public Callback {
    public:
        consteval explicit Constructor(std::meta::info i):
            Callback(i) {
            if (i != Mirror::NONE.value() && !std::meta::is_constructor(i)) {
                throw std::meta::exception("Provided std::meta::info is not a constructor", ^^Constructor);
            }
        }

        [[nodiscard]]
        consteval Type declaringClass() const {
            return Type(std::meta::parent_of(_info));
        }

        [[nodiscard]]
        consteval bool isDefault() const {
            return std::meta::is_default_constructor(_info);
        }

        [[nodiscard]]
        consteval bool isCopy() const {
            return std::meta::is_copy_constructor(_info);
        }

        [[nodiscard]]
        consteval bool isMove() const {
            return std::meta::is_move_constructor(_info);
        }

        [[nodiscard]]
        consteval bool isPublic() const {
            return std::meta::is_public(_info);
        }

        [[nodiscard]]
        consteval bool isProtected() const {
            return std::meta::is_protected(_info);
        }

        [[nodiscard]]
        consteval bool isPrivate() const {
            return std::meta::is_private(_info);
        }

        [[nodiscard]]
        consteval EnumSet<FunctionSpecifier> specifiers() const {
            EnumSet<FunctionSpecifier> result;
            if (std::meta::is_explicit(_info)) {
                result.insert(FunctionSpecifier::EXPLICIT);
            }
            if (std::meta::is_noexcept(_info)) {
                result.insert(FunctionSpecifier::NOEXCEPT);
            }
            if (std::meta::is_deleted(_info)) {
                result.insert(FunctionSpecifier::DELETED);
            }
            if (std::meta::is_defaulted(_info)) {
                result.insert(FunctionSpecifier::DEFAULTED);
            }
            return result;
        }
    };

    /**
     * @class Destructor
     * @brief Represents a destructor in the reflection system.
     * @extends Callback
     */
    class Destructor: public Callback {
    public:
        consteval explicit Destructor(std::meta::info i):
            Callback(i) {
            if (i != Mirror::NONE.value() && !std::meta::is_destructor(i)) {
                throw std::meta::exception("Provided std::meta::info is not a destructor", ^^Destructor);
            }
        }

        [[nodiscard]]
        consteval Type declaringClass() const {
            return Type(std::meta::parent_of(_info));
        }

        [[nodiscard]]
        consteval bool isVirtual() const {
            return std::meta::is_virtual(_info);
        }

        [[nodiscard]]
        consteval bool isPureVirtual() const {
            return std::meta::is_pure_virtual(_info);
        }

        [[nodiscard]]
        consteval bool isPublic() const {
            return std::meta::is_public(_info);
        }

        [[nodiscard]]
        consteval bool isProtected() const {
            return std::meta::is_protected(_info);
        }

        [[nodiscard]]
        consteval bool isPrivate() const {
            return std::meta::is_private(_info);
        }

        [[nodiscard]]
        consteval EnumSet<FunctionSpecifier> specifiers() const {
            EnumSet<FunctionSpecifier> result;
            if (std::meta::is_virtual(_info)) {
                result.insert(FunctionSpecifier::VIRTUAL);
            }
            if (std::meta::is_pure_virtual(_info)) {
                result.insert(FunctionSpecifier::PURE_VIRTUAL);
            }
            if (std::meta::is_noexcept(_info)) {
                result.insert(FunctionSpecifier::NOEXCEPT);
            }
            if (std::meta::is_deleted(_info)) {
                result.insert(FunctionSpecifier::DELETED);
            }
            if (std::meta::is_defaulted(_info)) {
                result.insert(FunctionSpecifier::DEFAULTED);
            }
            return result;
        }
    };

    /**
     * @class Base
     * @brief Represents a base class in the reflection system.
     * @extends Mirror
     */
    class Base: public Mirror {
    public:
        consteval explicit Base(std::meta::info i):
            Mirror(i) {
            if (i != Mirror::NONE.value() && !std::meta::is_base(i)) {
                throw std::meta::exception("Provided std::meta::info is not a base class", ^^Base);
            }
        }

        [[nodiscard]]
        consteval Type type() const {
            return Type(std::meta::type_of(_info));
        }

        [[nodiscard]]
        consteval bool isVirtual() const {
            return std::meta::is_virtual(_info);
        }

        [[nodiscard]]
        consteval bool isPublic() const {
            return std::meta::is_public(_info);
        }

        [[nodiscard]]
        consteval bool isProtected() const {
            return std::meta::is_protected(_info);
        }

        [[nodiscard]]
        consteval bool isPrivate() const {
            return std::meta::is_private(_info);
        }
    };

    /**
     * @class Enumerator
     * @brief Represents an enumerator in the reflection system.
     * @extends Mirror
     */
    class Enumerator: public Mirror {
    public:
        consteval explicit Enumerator(std::meta::info i):
            Mirror(i) {
            if (i != Mirror::NONE.value() && !std::meta::is_enumerator(i)) {
                throw std::meta::exception("Provided std::meta::info is not an enumerator", ^^Enumerator);
            }
        }

        [[nodiscard]]
        consteval Type type() const {
            return Type(std::meta::type_of(_info));
        }

        template <typename T>
        [[nodiscard]]
        consteval T as() const {
            return std::meta::extract<T>(_info);
        }
    };

    /**
     * @class Namespace
     * @brief Represents a namespace in the reflection system.
     * @extends Mirror
     */
    class Namespace: public Mirror {
    public:
        static const Namespace GLOBAL; ///< The global namespace.

        consteval explicit Namespace(std::meta::info i = ^^::):
            Mirror(i) {
            if (i != Mirror::NONE.value() && !std::meta::is_namespace(i)) {
                throw std::meta::exception("Provided std::meta::info is not a namespace", ^^Namespace);
            }
        }

        /**
         * @brief Distance from the global namespace. The global namespace
         * itself has depth 0; top-level namespaces have depth 1; etc.
         */
        [[nodiscard]]
        consteval std::size_t depth() const {
            return scopeDepth();
        }

        [[nodiscard]]
        consteval std::vector<Mirror> members(std::meta::access_context ctx = std::meta::access_context::unchecked()) const {
            std::vector<Mirror> result;
            for (std::meta::info m: std::meta::members_of(_info, ctx)) {
                result.emplace_back(m);
            }
            return result;
        }
    };

    inline constexpr Namespace Namespace::GLOBAL{^^::};

    /**
     * @class NamespaceAlias
     * @brief Represents a namespace alias in the reflection system.
     * @extends Mirror
     */
    class NamespaceAlias: public Mirror {
    public:
        consteval explicit NamespaceAlias(std::meta::info i):
            Mirror(i) {
            if (i != Mirror::NONE.value() && !std::meta::is_namespace_alias(i)) {
                throw std::meta::exception("Provided std::meta::info is not a namespace alias", ^^NamespaceAlias);
            }
        }

        [[nodiscard]]
        consteval Namespace target() const {
            return Namespace(std::meta::dealias(_info));
        }
    };

    /**
     * @class TypeAlias
     * @brief Represents a type alias in the reflection system.
     * @extends Mirror
     */
    class TypeAlias: public Mirror {
    public:
        consteval explicit TypeAlias(std::meta::info i):
            Mirror(i) {
            if (i != Mirror::NONE.value() && !std::meta::is_type_alias(i)) {
                throw std::meta::exception("Provided std::meta::info is not a type alias", ^^TypeAlias);
            }
        }

        [[nodiscard]]
        consteval Type target() const {
            return Type(std::meta::dealias(_info));
        }

        [[nodiscard]]
        consteval Type type() const {
            return Type(std::meta::dealias(_info));
        }
    };

    /**
     * @class Concept
     * @brief Represents a concept in the reflection system.
     * @extends Mirror
     */
    class Concept: public Mirror {
    public:
        consteval explicit Concept(std::meta::info i):
            Mirror(i) {
            if (i != Mirror::NONE.value() && !std::meta::is_concept(i)) {
                throw std::meta::exception("Provided std::meta::info is not a concept", ^^Concept);
            }
        }

        template <typename... Args>
        [[nodiscard]]
        consteval bool canSubstitute() const {
            return std::meta::can_substitute(_info, std::vector<std::meta::info>{^^Args...});
        }

        template <typename... Args>
        [[nodiscard]]
        consteval std::meta::info substitute() const {
            return std::meta::substitute(_info, std::vector<std::meta::info>{^^Args...});
        }

        [[nodiscard]]
        consteval std::vector<Mirror> templateArguments() const {
            std::vector<Mirror> result;
            for (std::meta::info a: std::meta::template_arguments_of(_info)) {
                result.emplace_back(a);
            }
            return result;
        }

        [[nodiscard]]
        consteval Template templateOf() const;
    };

    /**
     * @class Template
     * @brief Represents a template in the reflection system.
     * @extends Mirror
     */
    class Template: public Mirror {
    public:
        consteval explicit Template(std::meta::info i):
            Mirror(i) {
            if (i != Mirror::NONE.value() && !std::meta::is_template(i)) {
                throw std::meta::exception("Provided std::meta::info is not a template", ^^Template);
            }
        }

        [[nodiscard]]
        consteval bool isClassTemplate() const {
            return std::meta::is_class_template(_info);
        }

        [[nodiscard]]
        consteval bool isFunctionTemplate() const {
            return std::meta::is_function_template(_info);
        }

        [[nodiscard]]
        consteval bool isVariableTemplate() const {
            return std::meta::is_variable_template(_info);
        }

        [[nodiscard]]
        consteval bool isAliasTemplate() const {
            return std::meta::is_alias_template(_info);
        }

        [[nodiscard]]
        consteval bool isConstructorTemplate() const {
            return std::meta::is_constructor_template(_info);
        }

        [[nodiscard]]
        consteval bool isConversionFunctionTemplate() const {
            return std::meta::is_conversion_function_template(_info);
        }

        [[nodiscard]]
        consteval bool isOperatorFunctionTemplate() const {
            return std::meta::is_operator_function_template(_info);
        }

        [[nodiscard]]
        consteval bool isLiteralOperatorTemplate() const {
            return std::meta::is_literal_operator_template(_info);
        }

        template <typename... Args>
        [[nodiscard]]
        consteval bool canSubstitute() const {
            return std::meta::can_substitute(_info, std::vector<std::meta::info>{^^Args...});
        }

        template <typename... Args>
        [[nodiscard]]
        consteval std::meta::info substitute() const {
            return std::meta::substitute(_info, std::vector<std::meta::info>{^^Args...});
        }
    };

    /**
     * @class Annotation
     * @brief Represents an annotation in the reflection system.
     * @extends Mirror
     */
    class Annotation: public Mirror {
    public:
        consteval explicit Annotation(std::meta::info i):
            Mirror(i) {
            if (i != Mirror::NONE.value() && !std::meta::is_annotation(i)) {
                throw std::meta::exception("Provided std::meta::info is not an annotation", ^^Annotation);
            }
        }

        [[nodiscard]]
        consteval Type type() const {
            return Type(std::meta::type_of(_info));
        }

        template <typename T>
        [[nodiscard]]
        consteval T as() const {
            return std::meta::extract<T>(_info);
        }
    };

    /**
     * @class StructuredBinding
     * @brief Represents a structured binding in the reflection system.
     * @extends Mirror
     */
    class StructuredBinding: public Mirror {
    public:
        consteval explicit StructuredBinding(std::meta::info i):
            Mirror(i) {
            if (i != Mirror::NONE.value() && !std::meta::is_structured_binding(i)) {
                throw std::meta::exception("Provided std::meta::info is not a structured binding", ^^StructuredBinding);
            }
        }

        [[nodiscard]]
        consteval Type type() const {
            return Type(std::meta::type_of(_info));
        }
    };

    /**
     * @class Class
     * @brief Statically-typed wrapper for class (non-union) types.
     * @extends Type
     * @tparam T The class type being reflected.
     */
    template <detail::ReflectableAsClass T>
    class Class: public Type {
    public:
        using Of = T;
        static constexpr std::meta::info VALUE = ^^T;

        consteval Class() noexcept:
            Type(^^T) {}

        consteval explicit Class(std::meta::info i) noexcept:
            Type(i) {
            if (i != ^^T) {
                throw std::meta::exception("Provided Type does not match Class type", i);
            }
        }

        [[nodiscard]]
        consteval std::vector<Field> fields(std::meta::access_context ctx = std::meta::access_context::unchecked()) const {
            std::vector<Field> result;
            for (std::meta::info m: std::meta::nonstatic_data_members_of(^^T, ctx)) {
                result.emplace_back(m);
            }
            return result;
        }

        [[nodiscard]]
        consteval std::vector<Variable> staticFields(std::meta::access_context ctx = std::meta::access_context::unchecked()) const {
            std::vector<Variable> result;
            for (std::meta::info m: std::meta::static_data_members_of(^^T, ctx)) {
                result.emplace_back(m);
            }
            return result;
        }

        [[nodiscard]]
        consteval std::vector<Method> methods(std::meta::access_context ctx = std::meta::access_context::unchecked()) const {
            std::vector<Method> result;
            for (std::meta::info m: std::meta::members_of(^^T, ctx)) {
                if (std::meta::is_function(m)
                    && std::meta::is_class_member(m)
                    && !std::meta::is_constructor(m)
                    && !std::meta::is_destructor(m))
                {
                    result.emplace_back(m);
                }
            }
            return result;
        }

        [[nodiscard]]
        consteval std::vector<Constructor> constructors(std::meta::access_context ctx = std::meta::access_context::unchecked()) const {
            std::vector<Constructor> result;
            for (std::meta::info m: std::meta::members_of(^^T, ctx)) {
                if (std::meta::is_constructor(m)) {
                    result.emplace_back(m);
                }
            }
            return result;
        }

        /**
         * @brief Finds T's destructor.
         * @param ctx The access context.
         * @return The destructor, or nullopt if {@p ctx} cannot find it.
         *
         * Every complete class type has exactly one destructor. A destructor that
         * is explicitly deleted still returns a destructor, but reports
         * {@code Destructor::isDeleted()} to true.
         */
        [[nodiscard]]
        consteval std::optional<Destructor> destructor(std::meta::access_context ctx = std::meta::access_context::unchecked()) const {
            for (std::meta::info m: std::meta::members_of(^^T, ctx)) {
                if (std::meta::is_destructor(m)) {
                    return Destructor(m);
                }
            }
            return std::nullopt;
        }

        [[nodiscard]]
        consteval std::vector<Base> bases(std::meta::access_context ctx = std::meta::access_context::unchecked()) const {
            std::vector<Base> result;
            for (std::meta::info b: std::meta::bases_of(^^T, ctx)) {
                result.emplace_back(b);
            }
            return result;
        }

        [[nodiscard]]
        consteval std::vector<Mirror> subobjects(std::meta::access_context ctx = std::meta::access_context::unchecked()) const {
            std::vector<Mirror> result;
            for (std::meta::info s: std::meta::subobjects_of(^^T, ctx)) {
                result.emplace_back(s);
            }
            return result;
        }

        [[nodiscard]]
        consteval std::vector<Mirror> members(std::meta::access_context ctx = std::meta::access_context::unchecked()) const {
            std::vector<Mirror> result;
            for (std::meta::info m: std::meta::members_of(^^T, ctx)) {
                result.emplace_back(m);
            }
            return result;
        }

        [[nodiscard]]
        consteval bool hasInaccessibleBases(std::meta::access_context ctx = std::meta::access_context::unchecked()) const {
            return std::meta::has_inaccessible_bases(^^T, ctx);
        }

        [[nodiscard]]
        consteval bool hasInaccessibleNonstaticDataMembers(std::meta::access_context ctx = std::meta::access_context::unchecked()) const {
            return std::meta::has_inaccessible_nonstatic_data_members(^^T, ctx);
        }

        [[nodiscard]]
        consteval bool hasInaccessibleSubobjects(std::meta::access_context ctx = std::meta::access_context::unchecked()) const {
            return std::meta::has_inaccessible_subobjects(^^T, ctx);
        }
    };

    /**
     * @class Enum
     * @brief Represents an enum in the reflection system.
     * @extends Type
     * @tparam E The enum type being reflected.
     */
    template <detail::ReflectableAsEnum E>
    class Enum: public Type {
    public:
        using Of = E;
        static constexpr std::meta::info VALUE = ^^E;

        consteval Enum() noexcept:
            Type(^^E) {}

        consteval explicit Enum(std::meta::info i) noexcept:
            Type(i) {
            if (i != ^^E) {
                throw std::meta::exception("Provided Type does not match Class type", i);
            }
        }

        [[nodiscard]]
        consteval std::vector<Enumerator> enumerators() const {
            std::vector<Enumerator> result;
            for (std::meta::info e: std::meta::enumerators_of(^^E)) {
                result.emplace_back(e);
            }
            return result;
        }

        [[nodiscard]]
        consteval Type underlying() const {
            return Type(std::meta::underlying_type(^^E));
        }

        [[nodiscard]]
        consteval bool isScoped() const {
            return std::meta::is_scoped_enum_type(^^E);
        }
    };

    /**
     * @class Union
     * @brief Represents a union in the reflection system.
     * @extends Type
     * @tparam U The union type being reflected.
     */
    template <detail::ReflectableAsUnion U>
    class Union: public Type {
    public:
        using Of = U;
        static constexpr std::meta::info VALUE = ^^U;

        consteval Union() noexcept:
            Type(^^U) {}

        consteval explicit Union(std::meta::info i) noexcept:
            Type(i) {
            if (i != ^^U) {
                throw std::meta::exception("Provided Type does not match Class type", i);
            }
        }

        [[nodiscard]]
        consteval std::vector<Field> fields(std::meta::access_context ctx = std::meta::access_context::unchecked()) const {
            std::vector<Field> result;
            for (std::meta::info m: std::meta::nonstatic_data_members_of(^^U, ctx)) {
                result.emplace_back(m);
            }
            return result;
        }

        [[nodiscard]]
        consteval std::vector<Mirror> members(std::meta::access_context ctx = std::meta::access_context::unchecked()) const {
            std::vector<Mirror> result;
            for (std::meta::info m: std::meta::members_of(^^U, ctx)) {
                result.emplace_back(m);
            }
            return result;
        }
    };

    consteval std::vector<Annotation> Mirror::annotations() const {
        std::vector<Annotation> result;
        for (std::meta::info a: std::meta::annotations_of(_info)) {
            result.emplace_back(a);
        }
        return result;
    }

    template <typename T>
    consteval std::vector<Annotation> Mirror::annotationsWithType() const {
        std::vector<Annotation> result;
        for (std::meta::info a: std::meta::annotations_of_with_type(_info, ^^T)) {
            result.emplace_back(a);
        }
        return result;
    }

    consteval Template Type::templateOf() const {
        return Template(std::meta::template_of(_info));
    }

    consteval Template Concept::templateOf() const {
        return Template(std::meta::template_of(_info));
    }

    consteval std::optional<Type> Mirror::enclosingClass() const {
        std::meta::info cur = _info;
        while (std::meta::has_parent(cur)) {
            cur = std::meta::parent_of(cur);
            if (std::meta::is_class_type(cur) && !std::meta::is_union_type(cur)) {
                return Type(cur);
            }
        }
        return std::nullopt;
    }

    consteval Namespace Mirror::enclosingNamespace() const {
        if (std::meta::is_namespace(_info) && !std::meta::has_parent(_info)) {
            return Namespace(_info);
        }
        std::meta::info cur = _info;
        while (std::meta::has_parent(cur)) {
            cur = std::meta::parent_of(cur);
            if (std::meta::is_namespace(cur)) {
                return Namespace(cur);
            }
        }
        return Namespace(_info);
    }
} // namespace refract
