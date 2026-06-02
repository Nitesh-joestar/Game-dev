#include "raylib.h"
#include <entt/entt.hpp>
#include <string>

// ==========================================
// 1. COMPONENT DEFINITIONS (The Data)
// ==========================================
// In an ECS, components are just raw data (no logic).

struct Position {
    Vector2 value;
};

struct Velocity {
    Vector2 value;
};

struct CircleShape {
    float radius;
    Color color;
};

// ==========================================
// 2. MAIN APPLICATION
// ==========================================

int main() {
    // Window initialization
    const int screenWidth = 800;
    const int screenHeight = 600;
    InitWindow(screenWidth, screenHeight, "SimmRayy: EnTT + Raylib Integration Test");
    SetTargetFPS(60); // Lock to 60 frames per second

    // Create the EnTT registry (The core database of your game)
    entt::registry registry;

    // --- Entity Spawning ---
    // Let's spawn 100 bouncing balls
    for (int i = 0; i < 100; i++) {
        // Create an empty entity ID
        const auto entity = registry.create();

        // Attach random positions, velocities, and colors
        registry.emplace<Position>(entity, Vector2{
            (float)GetRandomValue(50, screenWidth - 50),
            (float)GetRandomValue(50, screenHeight - 50)
        });

        registry.emplace<Velocity>(entity, Vector2{
            (float)GetRandomValue(-200, 200),
            (float)GetRandomValue(-200, 200)
        });

        registry.emplace<CircleShape>(entity,
            (float)GetRandomValue(10, 25), // Random radius
            Color{
                (unsigned char)GetRandomValue(50, 250),
                (unsigned char)GetRandomValue(50, 250),
                (unsigned char)GetRandomValue(50, 250),
                255
            }
        );
    }

    // ==========================================
    // 3. THE GAME LOOP
    // ==========================================
    while (!WindowShouldClose()) {

        // GetFrameTime() ensures movement is consistent regardless of framerate
        float dt = GetFrameTime();

        // --- THE PHYSICS SYSTEM (Logic) ---
        // Query the registry for ALL entities that have both a Position and a Velocity
        auto physicsView = registry.view<Position, Velocity, CircleShape>();

        for (auto [entity, pos, vel, shape] : physicsView.each()) {
            // Apply velocity to position
            pos.value.x += vel.value.x * dt;
            pos.value.y += vel.value.y * dt;

            // Simple collision logic: Bounce off the walls
            if (pos.value.x >= (screenWidth - shape.radius) || pos.value.x <= shape.radius) {
                vel.value.x *= -1.0f; // Reverse X direction
            }
            if (pos.value.y >= (screenHeight - shape.radius) || pos.value.y <= shape.radius) {
                vel.value.y *= -1.0f; // Reverse Y direction
            }
        }

        // --- THE RENDER SYSTEM (Visuals) ---
        BeginDrawing();
        ClearBackground(RAYWHITE);

        // Query the registry for ALL entities that have a Position and a Shape
        auto renderView = registry.view<const Position, const CircleShape>();

        for (auto [entity, pos, shape] : renderView.each()) {
            // Tell Raylib to draw a circle using the component data
            DrawCircleV(pos.value, shape.radius, shape.color);
        }

        // Draw UI overlays on top of everything else
        DrawFPS(10, 10);
        DrawText(TextFormat("Entities active: %d", registry.storage<entt::entity>().size()), 10, 35, 20, DARKGRAY);

        EndDrawing();
    }

    // Clean up
    CloseWindow();
    return 0;
}