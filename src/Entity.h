#pragma once

#include "Components.h"
#include <vector>
#include <memory>

class Entity
{

    friend class EntityManager;

    bool m_active = true;
    size_t m_id = 0;
    std::string m_tag = "deafult";

    Entity(const size_t id, const std::string &tag);

public:
    std::shared_ptr<CTransform> cTransform;
    std::shared_ptr<CShape> cShape;
    std::shared_ptr<CCollider> cCollider;
    std::shared_ptr<CInput> cInput;
    std::shared_ptr<CScore> cScore;
    std::shared_ptr<CLifespan> cLifespan;

    bool IsActive() const;
    const std::string &tag() const;
    const size_t id() const;
    void destroy();
};