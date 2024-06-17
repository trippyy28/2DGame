#include "EntityManager.h"
#include "Entity.h"
EntityManager::EntityManager()
{
}

void EntityManager::update()
{
    // Add new entities to the main list
    for (auto &entity : m_entitiesToAdd)
    {
        m_entities.push_back(entity);
        m_entityMap[entity->tag()].push_back(entity);
    }
    m_entitiesToAdd.clear(); // Clear the temporary list

    // Remove dead entities from the main list
    removeDeadEntities(m_entities);

    // Remove dead entities from the map
    for (auto &[tag, entityVec] : m_entityMap)
    {
        removeDeadEntities(entityVec);
    }
}

void EntityManager::removeDeadEntities(EntityVec &vec)
{
    vec.erase(std::remove_if(vec.begin(), vec.end(),
                             [](const std::shared_ptr<Entity> &entity)
                             { return !entity->IsActive(); }),
              vec.end());
}

std::shared_ptr<Entity> EntityManager::addEntity(const std::string &tag)
{
    // create a new entity with the next available ID
    auto entity = std::shared_ptr<Entity>(new Entity(m_totalEntities++, tag));

    m_entitiesToAdd.push_back(entity);

    return entity;
}

const EntityVec &EntityManager::getEntities()
{
    return m_entities;
}

const EntityVec &EntityManager::getEntities(const std::string &tag)
{
    return m_entityMap[tag];
}
