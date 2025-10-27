#pragma once

#include "StarletScene/entity.hpp"

#include <vector>

namespace Starlet::Scene {
	class EntityManager {
	public:
		Entity createEntity() {
			Entity entity = nextEntity++;
			entities.push_back(entity);
			return entity;
		}

		const std::vector<Entity>& getEntities() const {
			return entities;
		}

	private:
		Entity nextEntity{ 0 };
		std::vector<Entity> entities;
	};
}