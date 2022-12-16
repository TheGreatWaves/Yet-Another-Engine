#pragma once

#include <cstdint>
#include <bitset>
#include <array>
#include <memory>

constexpr std::size_t kMaxComponents = 32;

using ComponentType = std::size_t;

using ComponentBitset = std::bitset<kMaxComponents>;

class Component {
public:
    virtual ~Component() = default;

    // Returns the unique type ID of the component.
    static ComponentType GetType() {
        static ComponentType type = s_next_type++;
        return type;
    }

private:
    static ComponentType s_next_type;
};

using ComponentArray = std::array<std::unique_ptr<Component>, kMaxComponents>;
