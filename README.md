# Cyro-Crisis
GADE7222 POE
## About the Game
Cyro Crisis is a tense and action-packed 3D first-person shooter set aboard a high-tech spaceship overrun by terrifying mutants. You play as a lone crew member who must navigate dark corridors, secure key areas, and fend off the growing infestation with a futuristic arsenal.

This project was my first experience working in Unreal Engine and coding entirely in C++. I designed and developed the entire game by myself, with a strong focus on implementing clean, maintainable architecture following SOLID principles and design patterns.
## Project Background
This was my second-year academic project aimed at exploring software architecture in game development, emphasising:
 - **SOLID principles**: Single Responsibility, Open/Closed, Liskov Substitution, Interface Segregation, Dependency Inversion
 - **Design patterns**: Factory, Strategy, Observer, State
I chose to code everything in C++ instead of Unreal’s Blueprint system to challenge myself and deepen my understanding of C++.
## Design and Development Highlights
**Map and Visuals**
- The entire map was modeled in Blender, providing a customised environment tailored to the game’s narrative and gameplay.
- Lighting was created from scratch in Unreal Engine to evoke a moody, suspenseful atmosphere fitting for the sci-fi horror setting.
- UI elements were designed manually, though the focus remained primarily on implementing core gameplay mechanics rather than polish.

**AI System**
- This was my first project to implement AI in a game. Enemies spawn randomly at designated points and patrol the map.
- When detecting the player, enemies engage by shooting and following the player, creating tense encounters.
- Enemies can pick up a secondary weapon, die when shot, and respawn.
- Challenges remain: enemies occasionally get stuck on stairs, and I was unable to implement AI shooting at each other or health pickup functionality.
- Despite these limitations, the AI system is mostly functional and taught me invaluable lessons about Unreal’s AI framework and C++ programming.

**Coding Architecture & Patterns**
- **Single Responsibility Principle**: I separated functionality across classes so each has a clear purpose (e.g., weapon firing vs. reloading).
- **Open/Closed Principle**: Weapons are designed for easy extension with new types without modifying existing character logic.
- **Liskov Substitution Principle**: Weapon subclasses implement shared interfaces, allowing interchangeable use without breaking code.
- **Interface Segregation**: Specialised interfaces handle different gameplay interactions such as ammo pickups, keeping code modular.
- **Dependency Inversion**: High-level modules interact with abstractions, decoupling character and weapon systems for easier maintenance and expansion.
- **Factory Pattern**: Dynamically creates game states for smooth transitions (e.g., gameplay, match over) without tight coupling.
- **Observer Pattern**: Manages health, ammo, and projectile events to decouple game systems and enable easy expansion.
- **State Pattern**: Controls game state transitions, encapsulating logic for different modes cleanly and extensibly.
## What I Learned
- Navigating my first Unreal Engine project, learning the engine’s pipeline alongside C++ coding.
- How to implement AI with patrol, detection, combat, and respawn mechanics, gaining practical experience with game AI systems.
- Applying SOLID principles and design patterns in a real-world game context to build modular, maintainable code.
- Creating custom lighting and atmosphere to support narrative and gameplay tone.
- Managing trade-offs between gameplay polish (e.g., UI refinement) and core mechanic implementation within project time constraints.
## Future Improvements
- Improve AI robustness and behaviours, fixing pathfinding issues like getting stuck and expanding combat interactions (e.g., AI shooting each other, health pickups).
- Polish and enhance UI for better player feedback and immersion.
- Expand gameplay with additional enemy types, weaponry, and game modes to increase depth and replayability.
- Optimise performance and add multiplayer functionality as a long-term goal.
