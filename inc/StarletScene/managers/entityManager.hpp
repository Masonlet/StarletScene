#pragma once

#include "StarletScene/entity.hpp"

#include <vector>

class EntityManager {
public:
	StarEntity createEntity() {
		StarEntity entity = nextEntity++;
		entities.push_back(entity);
		return entity;
	}

	const std::vector<StarEntity>& getEntities() const {
		return entities;
	}

private:
	StarEntity nextEntity{ 0 };
	std::vector<StarEntity> entities;
};