#include "System.hpp"

System::System(EntityManager& entityManager)
    : m_EntityManager(entityManager)
{
}

template <typename... Components>
SystemT<Components...>::SystemT(EntityManager& entityManager)
    : System(entityManager)
{
}

template <typename... Components>
void SystemT<Components...>::Update(float deltaTime)
{
    for (Entity entity : m_EntityManager.GetEntities())
    {
        if (std::apply([&](auto&&... components) { return (m_EntityManager.GetComponent<Components>(entity) && ...); }, m_RequiredComponents))
        {
            UpdateEntity(entity, deltaTime, *m_EntityManager.GetComponent<Components>(entity)...);
        }
    }
}