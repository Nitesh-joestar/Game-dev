#include <iostream>
#include <entt/entt.hpp>

// Define a simple component (just raw data)
struct Position {
    float x;
    float y;
};

struct Velocity {
    float dx;
    float dy;
};

int main() {
    // The registry is the core of EnTT, it manages all entities and components
    entt::registry registry;

    // Create a new entity
    auto entity = registry.create();

    // Attach components to the entity
    registry.emplace<Position>(entity, 0.0f, 0.0f);
    registry.emplace<Velocity>(entity, 1.5f, 1.0f);

    // Create a view to iterate over all entities that have BOTH Position and Velocity
    auto view = registry.view<Position, Velocity>();

    for(auto [entity, pos, vel] : view.each()) {
        // Update position based on velocity
        pos.x += vel.dx;
        pos.y += vel.dy;

        std::cout << "Entity moved to: (" << pos.x << ", " << pos.y << ")\n";
    }

    return 0;
}