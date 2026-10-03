#pragma once

#include <array>
#include <concepts>
#include <cstddef>
#include <meta>
#include <string_view>
#include <type_traits>

/**
 * @internal
 * @namespace refract::detail
 * @brief Implementation details of the refract library
 */
namespace refract::detail {
    /**
     * @concept DecaysTo
     * @brief Whether From and To name the same type once both are cvref-stripped.
     * @tparam From The (deduced) source type.
     * @tparam To The target type.
     */
    template <typename From, typename To>
    concept DecaysTo = std::same_as<std::remove_cvref_t<From>, std::remove_cvref_t<To>>;

    /**
     * @concept ReflectableAsClass
     * @brief A class type that can be reflected on. Excludes unions.
     * @tparam T A type to test for reflectability as a class.
     */
    template <typename T>
    concept ReflectableAsClass = std::meta::is_class_type(^^T) && !std::meta::is_union_type(^^T);

    /**
     * @concept ReflectableAsEnum
     * @brief An enumeration type that can be reflected on.
     * @tparam T A type to test for reflectability as an enum.
     */
    template <typename T>
    concept ReflectableAsEnum = std::meta::is_enum_type(^^T);

    /**
     * @concept ReflectableAsUnion
     * @brief A union type that can be reflected on.
     * @tparam T A type to test for reflectability as a union.
     */
    template <typename T>
    concept ReflectableAsUnion = std::meta::is_union_type(^^T);

    template <ReflectableAsEnum E>
    [[nodiscard]]
    consteval std::size_t count() {
        return std::meta::enumerators_of(^^E).size();
    }

    template <ReflectableAsEnum E>
    [[nodiscard]]
    consteval std::array<E, count<E>()> values_impl() {
        std::array<E, count<E>()> result;
        std::size_t i = 0;
        for (std::meta::info e: std::meta::enumerators_of(^^E)) {
            result[i++] = std::meta::extract<E>(e);
        }
        return result;
    }

    template <ReflectableAsEnum E>
    inline constexpr std::array<E, count<E>()> ValuesPer = values_impl<E>();

    template <ReflectableAsEnum E>
    [[nodiscard]]
    consteval std::array<std::string_view, count<E>()> names_impl() {
        std::array<std::string_view, count<E>()> result;
        std::size_t i = 0;
        for (std::meta::info e: std::meta::enumerators_of(^^E)) {
            result[i++] = std::meta::identifier_of(e);
        }
        return result;
    }

    template <ReflectableAsEnum E>
    inline constexpr std::array<std::string_view, count<E>()> NamesPer = names_impl<E>();
} // namespace refract::detail
