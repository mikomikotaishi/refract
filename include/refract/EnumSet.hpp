#pragma once

#include <array>
#include <bitset>
#include <concepts>
#include <cstddef>
#include <initializer_list>
#include <iterator>
#include <meta>
#include <type_traits>

#include "Details.hpp"

/**
 * @namespace refract
 * @brief The refract namespace, the namespace of the library.
 */
namespace refract {
    /**
     * @class EnumSet
     * @brief A bitset-backed set of enumerators.
     * @tparam E An enumeration type.
     */
    template <detail::ReflectableAsEnum E>
    class [[nodiscard]] EnumSet {
    public:
        using ValueType = E;
        using UnderlyingType = std::underlying_type_t<E>;
        using SizeType = std::size_t;

        static constexpr const std::array<E, detail::count<E>()>& VALUES = detail::ValuesPer<E>; ///< All enumerator values of E, in declaration order.
        static constexpr std::size_t CAPACITY = VALUES.size(); ///< Number of enumerators of E.
    private:
        std::bitset<CAPACITY> _bits; ///< Bitset storing the presence of each enumerator in VALUES.

        [[nodiscard]]
        static constexpr std::size_t indexOf(E v) noexcept {
            for (std::size_t i = 0; i < CAPACITY; ++i) {
                if (VALUES[i] == v) {
                    return i;
                }
            }
            return CAPACITY;
        }

        constexpr explicit EnumSet(std::bitset<CAPACITY> b) noexcept:
            _bits{b} {}
    public:
        constexpr EnumSet() noexcept = default;

        constexpr EnumSet(std::initializer_list<E> values) noexcept {
            for (E v: values) {
                if (std::size_t i = indexOf(v); i < CAPACITY) {
                    _bits.set(i);
                }
            }
        }

        [[nodiscard]]
        static constexpr EnumSet noneOf() noexcept {
            return EnumSet();
        }

        [[nodiscard]]
        static constexpr EnumSet allOf() noexcept {
            EnumSet s;
            s._bits.set();
            return s;
        }

        [[nodiscard]]
        static constexpr EnumSet of(std::same_as<E> auto... vals) noexcept requires (sizeof...(vals) > 0) {
            EnumSet s;
            (s.insert(vals), ...);
            return s;
        }

        [[nodiscard]]
        static constexpr EnumSet range(E from, E to) noexcept {
            EnumSet s;
            std::size_t start = indexOf(from);
            std::size_t end = indexOf(to);
            if (start == CAPACITY || end == CAPACITY) {
                return s;
            }
            if (start > end) {
                std::size_t tmp = start;
                start = end;
                end = tmp;
            }
            for (std::size_t i = start; i <= end; ++i) {
                s._bits.set(i);
            }
            return s;
        }

        [[nodiscard]]
        static constexpr EnumSet complementOf(const EnumSet& other) noexcept {
            EnumSet s = other;
            s._bits.flip();
            return s;
        }

        [[nodiscard]]
        constexpr bool contains(E v) const noexcept {
            std::size_t i = indexOf(v);
            return i < CAPACITY && _bits.test(i);
        }

        [[nodiscard]]
        constexpr bool containsAll(const EnumSet& other) const noexcept {
            return (_bits & other._bits) == other._bits;
        }

        [[nodiscard]]
        constexpr bool containsAny(const EnumSet& other) const noexcept {
            return (_bits & other._bits).any();
        }

        [[nodiscard]]
        constexpr std::size_t size() const noexcept {
            return _bits.count();
        }

        [[nodiscard]]
        constexpr bool empty() const noexcept {
            return _bits.none();
        }

        [[nodiscard]]
        constexpr bool isFull() const noexcept {
            return _bits.all();
        }

        [[nodiscard]]
        static constexpr std::size_t capacity() noexcept {
            return CAPACITY;
        }

        constexpr bool insert(E v) noexcept {
            std::size_t i = indexOf(v);
            if (i >= CAPACITY) {
                return false;
            }
            bool was_set = _bits.test(i);
            _bits.set(i);
            return !was_set;
        }

        constexpr bool erase(E v) noexcept {
            std::size_t i = indexOf(v);
            if (i >= CAPACITY) {
                return false;
            }
            bool was_set = _bits.test(i);
            _bits.reset(i);
            return was_set;
        }

        constexpr void clear() noexcept {
            _bits.reset();
        }

        constexpr bool addAll(const EnumSet& other) noexcept {
            std::bitset<CAPACITY> before = _bits;
            _bits |= other._bits;
            return _bits != before;
        }

        constexpr bool removeAll(const EnumSet& other) noexcept {
            std::bitset<CAPACITY> before = _bits;
            _bits &= ~other._bits;
            return _bits != before;
        }

        constexpr bool retainAll(const EnumSet& other) noexcept {
            std::bitset<CAPACITY> before = _bits;
            _bits &= other._bits;
            return _bits != before;
        }

        constexpr EnumSet& operator|=(const EnumSet& o) noexcept {
            _bits |= o._bits;
            return *this;
        }

        constexpr EnumSet& operator&=(const EnumSet& o) noexcept {
            _bits &= o._bits;
            return *this;
        }

        constexpr EnumSet& operator^=(const EnumSet& o) noexcept {
            _bits ^= o._bits;
            return *this;
        }

        constexpr EnumSet& operator-=(const EnumSet& o) noexcept {
            _bits &= ~o._bits;
            return *this;
        }

        [[nodiscard]]
        friend constexpr EnumSet operator|(EnumSet a, const EnumSet& b) noexcept {
            a |= b;
            return a;
        }

        [[nodiscard]]
        friend constexpr EnumSet operator&(EnumSet a, const EnumSet& b) noexcept {
            a &= b;
            return a;
        }

        [[nodiscard]]
        friend constexpr EnumSet operator^(EnumSet a, const EnumSet& b) noexcept {
            a ^= b;
            return a;
        }

        [[nodiscard]]
        friend constexpr EnumSet operator-(EnumSet a, const EnumSet& b) noexcept {
            a -= b;
            return a;
        }

        [[nodiscard]]
        constexpr EnumSet operator~() const noexcept {
            return complementOf(*this);
        }

        [[nodiscard]]
        constexpr bool operator==(const EnumSet&) const noexcept = default;

        class Iterator {
        private:
            friend class EnumSet;
            const std::bitset<CAPACITY>* _bits;
            size_t _idx = 0;

            constexpr Iterator(const std::bitset<CAPACITY>* b, std::size_t i) noexcept:
                _bits{b}, _idx{i} {
                advance();
            }

            constexpr void advance() noexcept {
                while (_idx < CAPACITY && !_bits->test(_idx)) {
                    ++_idx;
                }
            }
        public:
            using IteratorCategory = std::forward_iterator_tag;
            using ValueType = E;
            using Reference = E;
            using Pointer = void;
            using DifferenceType = std::ptrdiff_t;

            constexpr Iterator() noexcept = default;

            [[nodiscard]]
            constexpr E operator*() const noexcept {
                return VALUES[_idx];
            }

            constexpr Iterator& operator++() noexcept {
                ++_idx;
                advance();
                return *this;
            }

            constexpr Iterator operator++(int _) noexcept {
                Iterator tmp = *this;
                ++*this;
                return tmp;
            }

            [[nodiscard]]
            constexpr bool operator==(const Iterator&) const noexcept = default;

            using value_type = ValueType;
            using underlying_type = UnderlyingType;
            using size_type = SizeType;
            using iterator_category = IteratorCategory;
        };

        using ConstIterator = Iterator;

        [[nodiscard]]
        constexpr Iterator begin() const noexcept {
            return Iterator(&_bits, 0);
        }
        [[nodiscard]]
        constexpr Iterator end() const noexcept {
            return Iterator(&_bits, CAPACITY);
        }

        [[nodiscard]]
        constexpr Iterator cbegin() const noexcept {
            return begin();
        }

        [[nodiscard]]
        constexpr Iterator cend() const noexcept {
            return end();
        }

        using iterator = Iterator;
        using const_iterator = ConstIterator;
    };
} // namespace refract

namespace std {
    template <typename T, typename Char>
    struct formatter<refract::EnumSet<T>, Char> {
        constexpr auto parse(format_parse_context& ctx) noexcept {
            return ctx.begin();
        }

        auto format(const refract::EnumSet<T>& s, format_context& ctx) const {
            auto out = ctx.out();
            out = format_to(out, "{{");
            bool first = true;
            for (std::size_t i = 0; i < refract::EnumSet<T>::CAPACITY; ++i) {
                if (s.contains(refract::EnumSet<T>::VALUES[i])) {
                    if (!first) {
                        out = format_to(out, ", ");
                    }
                    out = format_to(out, "{}", refract::detail::NamesPer<T>[i]);
                    first = false;
                }
            }
            return format_to(out, "}}");
        }
    };
} // namespace std
