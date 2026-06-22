```cpp
entt::registry registry;
```
this is how you create a registry initialize it bud.

```cpp
entt::entity player=registry.create();  
registry.emplace<Position>(player,Vector2(10,12));
```
first line creates the entity
second line adds a component to the entity

compoenents are all structs, you need to create structs capiche

```cpp
auto pos=registry.view<Position>();
```

first line gets you a view of all the components with a certain component

```cpp
for (auto entity:pos) {  
    auto &position=pos.get<Position>(entity);  
    DrawCircleV(position.value,5.0f,RED);  
}
```
this is how you iterate over em
struct it was like 
struct Position {  
    Vector2 value;  
};
so you need to go entity.value to get the vector2