//
// Created by siebe on 12/12/2025.
//

#ifndef ENTITYVIEW_H
#define ENTITYVIEW_H

#include <SFML/Graphics.hpp>
#include "Observer.h"
#include "../entities/Entity.h"

class EntityView : public Observer {
	protected:
		Entity* entity; // Raw pointer to the entity we're observing
		sf::Sprite sprite;
		sf::Texture texture;
		float lastFrameTime = 0.0f;
		float frameCooldown = 0.1f;
		bool mouthOpen = false;

	public:
		explicit EntityView(Entity* e) : entity(e) {}

		virtual ~EntityView() = default;

		// Observer interface
		void update() {
			// Base implementation - subclasses can override
		}
		void onNotify() {
			update();
		}
		// Common functionality
		virtual void updateTexture(float time) = 0;

		sf::Sprite& getSprite() { return sprite; }
		Entity* getEntity() const { return entity; }

	protected:
		bool readyFrame(float currentTime) const {
			return (currentTime - lastFrameTime) >= frameCooldown;
		}

		void recordFrameTime(float currentTime) {
			lastFrameTime = currentTime;
		}
};

#endif // ENTITYVIEW_H
