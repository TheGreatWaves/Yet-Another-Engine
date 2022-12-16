#pragma once

#include <iostream>

#include "Component.hpp"
#include "EntityManager.hpp"
#include <utility>

template <typename T>
std::enable_if_t<std::is_base_of_v<Component, T>, T*> GetComponent(EntityManager& entityManager, Entity entity)
{
    return entityManager.GetComponent<T>(entity);
}

template <typename T>
inline std::enable_if_t<std::is_base_of_v<Component, T>, bool> HasComponent(const EntityManager& entityManager, Entity entity)
{
    return GetComponent<T>(entityManager, entity) != nullptr;
}

template <typename... Components>
constexpr bool HasComponents(const EntityManager& entityManager, Entity entity)
{
    if constexpr (sizeof...(Components) == 0)
    {
        return true;
    }
    else
    {
        bool result = true;
        (void)std::initializer_list<int>{(result &= HasComponent<Components>(entityManager, entity), 0)...};
        return result;
    }
}

template <typename... Components>
inline std::array<Component*, sizeof...(Components)> GetComponents(EntityManager& entityManager, Entity entity)
{
    return std::apply([&entityManager, entity](auto&... components) { return std::array<Component*, sizeof...(Components)>{GetComponent<std::decay_t<decltype(components)>>(entityManager, entity)...}; }, std::make_tuple(Components()...));
}

template <typename T>
inline T* CreateComponent(EntityManager& entityManager, Entity entity)
{
    static_assert(std::is_base_of_v<Component, T>, "T must derive from Component");
    return entityManager.AddComponent<T>(entity);
}

template <typename T>
inline void DestroyComponent(EntityManager& entityManager, Entity entity)
{
    static_assert(std::is_base_of_v<Component, T>, "T must derive from Component");

    T* component = entityManager.GetComponent<T>(entity);
    if (component != nullptr)
    {
        entityManager.RemoveComponent<T>(entity);
        delete component;
    }
}

template <typename T, typename Func>
inline void ForEachComponent(const EntityManager& entityManager, Func func)
{
    static_assert(std::is_base_of_v<Component, T>, "T must derive from Component");

    for (Entity entity : entityManager.GetEntities())
    {
        T* component = entityManager.GetComponent<T>(entity);
        if (component != nullptr)
        {
            func(*component);
        }
    }
}

template <typename T, typename Func>
inline void ForEachEntityWithComponent(const EntityManager& entityManager, Func func)
{
    static_assert(std::is_base_of_v<Component, T>, "T must derive from Component");

    for (Entity entity : entityManager.GetEntities())
    {
        T* component = entityManager.GetComponent<T>(entity);
        if (component != nullptr)
        {
            func(entity, *component);
        }
    }
}