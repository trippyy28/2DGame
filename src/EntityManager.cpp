#include "EntityManager.h"

EntityManager::EntityManager()
{
}

void EntityManager::update()
{
    // TODO: add entities from m_entitedToAdd to the proper location(s)
    // - add them to the vector of all entities
    // - add them to the vector inside the map, with the tag as a key

    // remove dead entities from the vector of all entities
    removeDeadEntities(m_entities);

    // remove dead entities from each vector in the entity map
    for (auto &[tag, entityVec] : m_entityMap)
    {
        removeDeadEntities(entityVec);
    }
}

void EntityManager::removeDeadEntities(EntityVec &vec)
{
    // TODO: Implement logic to remove dead entities
}

std::shared_ptr<Entity> EntityManager::addEntity(const std::string &tag)
{
    // create a new entity with the next available ID
    auto entity = std::shared_ptr<Entity>(new Entity(m_totalEntities++, tag));

    m_entitedToAdd.push_back(entity);

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
