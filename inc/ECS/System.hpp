#pragma once

#include "EntityManager.hpp"
#include "Component.hpp"

class System
{
public:
    System(EntityManager& entityManager);

    virtual void Update(float deltaTime) = 0;

protected:
    EntityManager& m_EntityManager;
};

template <typename... Components>
class SystemT : public System
{
public:
    SystemT(EntityManager& entityManager);

    virtual void Update(float deltaTime) override;

protected:
    std::tuple<std::add_lvalue_reference_t<Components>...> m_RequiredComponents;

private:
    virtual void UpdateEntity(Entity entity, float deltaTime, Components&... components) = 0;
};