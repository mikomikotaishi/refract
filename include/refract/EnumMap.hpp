#pragma once

#include <array>
#include <format>
#include <initializer_list>
#include <iterator>
#include <meta>
#include <optional>
#include <stdexcept>
#include <type_traits>
#include <utility>
#include <vector>

#include "Details.hpp"
#include "EnumSet.hpp" // EnumMap::keySet returns EnumSet<K>

/**
 * @namespace refract
 * @brief The refract namespace, the namespace of the library.
 */
namespace refract {
    /**
     * @class EnumMap
     * @brief An array-backed map keyed by the enumerators of E.
     * Each slot is an std::optional<V>; an empty slot denotes an absent key, so V need
     * not be default-constructible (only operator[] requires that, on use).
     * @tparam K An enumeration type used as the key.
     * @tparam V The mapped value type.
     */
    template <detail::ReflectableAsEnum K, typename V>
    class [[nodiscard]] EnumMap {
    public:
        using KeyType = K;
        using MappedType = V;
        using ValueType = std::pair<const K, V>;
        using SizeType = std::size_t;
        using UnderlyingType = std::underlying_type_t<K>;

        static constexpr const std::array<K, detail::count<K>()>& KEYS = detail::ValuesPer<K>; ///< All enumerator values of K, in declaration order.
        static constexpr std::size_t CAPACITY = KEYS.size(); ///< Number of enumerators of K (the maximum number of entries).
    private:
        std::array<std::optional<V>, CAPACITY> _slots; ///< Per-enumerator value storage; an empty optional means the key is absent.
        std::size_t _occupied = 0; ///< Number of present entries.

        [[nodiscard]]
        static constexpr std::size_t indexOf(K k) noexcept {
            for (std::size_t i = 0; i < CAPACITY; ++i) {
                if (KEYS[i] == k) {
                    return i;
                }
            }
            return CAPACITY;
        }
    public:
        constexpr EnumMap() noexcept = default;

        /**
         * @brief Constructs an EnumMap with the given entries.
         * @param entries The initial entries for the map.
         */
        constexpr EnumMap(std::initializer_list<std::pair<K, V>> entries) {
            for (const auto& [key, value]: entries) {
                insertOrAssign(key, value);
            }
        }

        /**
         * @brief Builds a map from entries given as separate arguments.
         * @param entries The entries to insert, in order, each a pair<K, V> of
         * either value category. A later entry repeating a key overwrites the
         * earlier one, as with the initializer_list form.
         * @return The populated map.
         */
        [[nodiscard]]
        static constexpr EnumMap of(detail::DecaysTo<std::pair<K, V>> auto&&... entries) requires (sizeof...(entries) > 0) {
            EnumMap map;
            (map.insertOrAssign(entries.first, std::forward<decltype(entries)>(entries).second), ...);
            return map;
        }

        [[nodiscard]]
        constexpr std::size_t size() const noexcept {
            return _occupied;
        }

        [[nodiscard]]
        constexpr bool empty() const noexcept {
            return _occupied == 0;
        }

        [[nodiscard]]
        static constexpr std::size_t capacity() noexcept {
            return CAPACITY;
        }

        [[nodiscard]]
        constexpr bool contains(K key) const noexcept {
            std::size_t i = indexOf(key);
            return i < CAPACITY && _slots[i].has_value();
        }

        [[nodiscard]]
        constexpr bool containsValue(const V& value) const {
            for (std::size_t i = 0; i < CAPACITY; ++i) {
                if (_slots[i].has_value() && *_slots[i] == value) {
                    return true;
                }
            }
            return false;
        }

        /**
         * @brief Returns a pointer to the value mapped to @p key, or nullptr if absent.
         * @param key The key to look up.
         * @return A pointer to the mapped value, valid until the entry is removed; nullptr if @p key is absent.
         */
        [[nodiscard]]
        constexpr V* find(K key) noexcept {
            std::size_t i = indexOf(key);
            if (i >= CAPACITY || !_slots[i].has_value()) {
                return nullptr;
            }
            return &*_slots[i];
        }

        [[nodiscard]]
        constexpr const V* find(K key) const noexcept {
            std::size_t i = indexOf(key);
            if (i >= CAPACITY || !_slots[i].has_value()) {
                return nullptr;
            }
            return &*_slots[i];
        }

        /**
         * @brief Returns a reference to the value mapped to @p key.
         * @param key The key to look up.
         * @return A reference to the mapped value.
         * @throws out_of_range if @p key is absent.
         */
        [[nodiscard]]
        constexpr V& at(K key) {
            std::size_t i = indexOf(key);
            if (i >= CAPACITY || !_slots[i].has_value()) {
                throw std::out_of_range("no mapping for key");
            }
            return *_slots[i];
        }

        [[nodiscard]]
        constexpr const V& at(K key) const {
            std::size_t i = indexOf(key);
            if (i >= CAPACITY || !_slots[i].has_value()) {
                throw std::out_of_range("no mapping for key");
            }
            return *_slots[i];
        }

        /**
         * @brief Associates @p value with @p key, replacing any existing mapping.
         * @param key The key to associate.
         * @param value The value to store.
         * @return The previous value mapped to @p key, or an empty optional if there was none.
         */
        constexpr std::optional<V> insertOrAssign(K key, V value) {
            std::size_t i = indexOf(key);
            if (i >= CAPACITY) {
                return std::nullopt;
            }
            std::optional<V> previous = std::move(_slots[i]);
            if (!previous.has_value()) {
                ++_occupied;
            }
            _slots[i] = std::move(value);
            return previous;
        }

        /**
         * @brief Removes the mapping for @p key, if present.
         * @param key The key whose mapping is to be removed.
         * @return The value that was mapped to @p key, or an empty optional if there was none.
         */
        constexpr std::optional<V> erase(K key) {
            std::size_t i = indexOf(key);
            if (i >= CAPACITY || !_slots[i].has_value()) {
                return std::nullopt;
            }
            std::optional<V> previous = std::move(_slots[i]);
            _slots[i].reset();
            --_occupied;
            return previous;
        }

        /**
         * @brief Copies every entry of @p other into this map, overwriting on conflict.
         * @param other The map whose entries are to be inserted.
         */
        constexpr void putAll(const EnumMap& other) {
            for (std::size_t i = 0; i < CAPACITY; ++i) {
                if (other._slots[i].has_value()) {
                    if (!_slots[i].has_value()) {
                        ++_occupied;
                    }
                    _slots[i] = other._slots[i];
                }
            }
        }

        constexpr void clear() noexcept {
            for (std::optional<V>& slot: _slots) {
                slot.reset();
            }
            _occupied = 0;
        }

        /**
         * @brief Returns a reference to the value mapped to @p key, inserting a
         * default-constructed value first if @p key is absent.
         * @note @p key must be a declared enumerator of K, and V must be
         * default-constructible.
         * @param key The key to access.
         * @return A reference to the mapped value.
         */
        [[nodiscard]]
        constexpr V& operator[](K key) {
            std::size_t i = indexOf(key);
            if (!_slots[i].has_value()) {
                _slots[i].emplace();
                ++_occupied;
            }
            return *_slots[i];
        }

        /**
         * @brief Returns the set of keys that currently have a mapping.
         * @return An EnumSet of the present keys.
         */
        [[nodiscard]]
        constexpr EnumSet<K> keySet() const noexcept {
            EnumSet<K> keys;
            for (std::size_t i = 0; i < CAPACITY; ++i) {
                if (_slots[i].has_value()) {
                    keys.insert(KEYS[i]);
                }
            }
            return keys;
        }

        /**
         * @brief Returns the present values, in key declaration order.
         * @return A vector of the mapped values.
         */
        [[nodiscard]]
        constexpr std::vector<V> values() const {
            std::vector<V> result;
            for (std::size_t i = 0; i < CAPACITY; ++i) {
                if (_slots[i].has_value()) {
                    result.push_back(*_slots[i]);
                }
            }
            return result;
        }

        [[nodiscard]]
        constexpr bool operator==(const EnumMap&) const = default;

        class Iterator {
        private:
            friend class EnumMap;
            const EnumMap* _map;
            std::size_t _idx = 0;

            constexpr Iterator(const EnumMap* m, std::size_t i) noexcept:
                _map{m}, _idx{i} {
                advance();
            }

            constexpr void advance() noexcept {
                while (_idx < CAPACITY && !_map->_slots[_idx].has_value()) {
                    ++_idx;
                }
            }
        public:
            using IteratorCategory = std::forward_iterator_tag;
            using ValueType = std::pair<K, const V&>;
            using Reference = std::pair<K, const V&>;
            using Pointer = void;
            using DifferenceType = std::ptrdiff_t;

            constexpr Iterator() noexcept = default;

            [[nodiscard]]
            constexpr std::pair<K, const V&> operator*() const noexcept {
                return std::pair<K, const V&>(KEYS[_idx], *_map->_slots[_idx]);
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
            constexpr bool operator==(const Iterator& other) const noexcept {
                return _map == other._map && _idx == other._idx;
            }

            using value_type = ValueType;
            using reference = Reference;
            using difference_type = DifferenceType;
            using iterator_category = IteratorCategory;
        };

        using ConstIterator = Iterator;

        [[nodiscard]]
        constexpr Iterator begin() const noexcept {
            return Iterator(this, 0);
        }

        [[nodiscard]]
        constexpr Iterator end() const noexcept {
            return Iterator(this, CAPACITY);
        }

        [[nodiscard]]
        constexpr Iterator cbegin() const noexcept {
            return begin();
        }

        [[nodiscard]]
        constexpr Iterator cend() const noexcept {
            return end();
        }

        using key_type = KeyType;
        using mapped_type = MappedType;
        using value_type = ValueType;
        using size_type = SizeType;
        using iterator = Iterator;
        using const_iterator = ConstIterator;
    };
} // namespace refract

namespace std {
    template <typename K, typename V, typename Char>
    struct formatter<refract::EnumMap<K, V>, Char> {
        constexpr auto parse(format_parse_context& ctx) noexcept {
            return ctx.begin();
        }

        auto format(const refract::EnumMap<K, V>& m, format_context& ctx) const {
            auto out = ctx.out();
            out = format_to(out, "{{");
            bool first = true;
            for (std::size_t i = 0; i < refract::EnumMap<K, V>::CAPACITY; ++i) {
                if (const V* v = m.find(refract::EnumMap<K, V>::KEYS[i])) {
                    if (!first) {
                        out = format_to(out, ", ");
                    }
                    out = format_to(out, "{}={}", refract::detail::NamesPer<K>[i], *v);
                    first = false;
                }
            }
            return format_to(out, "}}");
        }
    };
} // namespace std
