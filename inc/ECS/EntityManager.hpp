#pragma once

#include <iostream>
#include <unordered_map>
#include <vector>
#include "Entity.hpp"
#include "Component.hpp"

template <typename T>
constexpr ComponentType GetComponentType()
{
    static_assert(std::is_base_of_v<Component, T>, "T must derive from Component");
    static ComponentType type = T::GetType();
    return type;
}

class EntityManager
{
public:
    // Creates a new entity and returns its ID.
    Entity CreateEntity();

    // Destroys an entity and frees its ID for reuse.
    void DestroyEntity(Entity entity);

    // Attaches a component to an entity.
    template <typename T>
    void AddComponent(Entity entity, T component);

    // Attaches a component to an entity.
    template <typename T>
    T* AddComponent(Entity entity);

    // Detaches a component from an entity.
    template <typename T>
    void RemoveComponent(Entity entity);

    // Returns a pointer to the component of the specified type attached to the entity, or nullptr if the entity does not have that component.
    template <typename T>
    T* GetComponent(Entity entity);

    // Returns a bitset indicating which components are attached to the entity.
    const ComponentBitset& GetComponentBitset(Entity entity) const;

    // Returns an array of pointers to the components attached to the entity.
    const ComponentArray& GetComponentArray(Entity entity) const;

    // Returns a list of all entities.
    const std::vector<Entity>& GetEntities() const;

private:
    std::unordered_map<Entity, ComponentArray> m_Components;
    std::unordered_map<Entity, ComponentBitset> m_ComponentBitsets;
    std::vector<Entity> m_Entities;
};


inline Entity EntityManager::CreateEntity()
{
    if (m_Entities.empty())
    {
        m_Entities.push_back(m_Entities.size());
    }
    else
    {
        m_Entities.push_back(m_Entities.back() + 1);
    }

    return m_Entities.back();
}

inline void EntityManager::DestroyEntity(Entity entity)
{
    m_Components.erase(entity);
    m_ComponentBitsets.erase(entity);
    m_Entities.erase(std::remove(m_Entities.begin(), m_Entities.end(), entity), m_Entities.end());
}

template <typename T>
void EntityManager::AddComponent(Entity entity, T component)
{
    static_assert(std::is_base_of_v<Component, T>, "T must derive from Component");

    m_Components[entity][GetComponentType<T>()] = std::move(component);
    m_ComponentBitsets[entity][GetComponentType<T>()] = true;
}

template <typename T>
T* EntityManager::AddComponent(Entity entity)
{
    auto component = std::make_unique<T>();

    m_Components[entity][GetComponentType<T>()] = std::move(component);
    m_ComponentBitsets[entity][GetComponentType<T>()] = true;
   
    return static_cast<T*>(m_Components[entity][GetComponentType<T>()].get());
}

template <typename T>
void EntityManager::RemoveComponent(Entity entity)
{
    static_assert(std::is_base_of_v<Component, T>, "T must derive from Component");

    m_Components[entity][GetComponentType<T>()] = nullptr;
    m_ComponentBitsets[entity][GetComponentType<T>()] = false;
}

template <typename T>
T* EntityManager::GetComponent(Entity entity)
{
    static_assert(std::is_base_of_v<Component, T>, "T must derive from Component");
    return static_cast<T*>(m_Components[entity][GetComponentType<T>()].get());
}

inline const ComponentBitset& EntityManager::GetComponentBitset(Entity entity) const
{
    return m_ComponentBitsets.at(entity);
}

inline const ComponentArray& EntityManager::GetComponentArray(Entity entity) const
{
    return m_Components.at(entity);
}

inline const std::vector<Entity>& EntityManager::GetEntities() const
{
    return m_Entities;
}

