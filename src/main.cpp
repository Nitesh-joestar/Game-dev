#include "raylib.h"
#include <entt/entt.hpp>
#include <string>

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

void spawn(entt::registry &registry, int screenWidth, int screenHeight, Vector2 mousePos) {
    entt::entity player=registry.create();
    registry.emplace<Position>(player,mousePos);
}
void updatePos(entt::registry &registry) {
    auto pos=registry.view<Position>();
    for (auto entity:pos) {
        auto &position=pos.get<Position>(entity);
        position.value.y++;
    }
}
int main() {
    const int screenWidth = 800;
    const int screenHeight = 600;
    InitWindow(screenWidth, screenHeight, "SimmRayy: EnTT + Raylib Integration Test");
    SetTargetFPS(0);
    entt::registry registry;
    spawn(registry, screenWidth, screenHeight, GetMousePosition());

    while (!WindowShouldClose()) {
        Vector2 mousePos=GetMousePosition();
        auto pos=registry.view<Position>();
        if (IsMouseButtonDown(MOUSE_LEFT_BUTTON)) {
            spawn(registry, screenWidth, screenHeight,mousePos);
            DrawText("pressed",30,10,10,BLACK);
        }
        updatePos(registry);
        BeginDrawing();
        ClearBackground(GRAY);

        for (auto entity:pos) {
            auto &position=pos.get<Position>(entity);
            DrawCircleV(position.value,5.0f,RED);
        }

        DrawFPS(10, 10);

        EndDrawing();
    }

    CloseWindow();
    return 0;
}