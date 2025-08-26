# 🚀 Space Grid Shooter

## 📖 Overview

**Space Grid Shooter** is a minimalistic 2D **lane-based shooter game** built in **C++**.  
The player controls a spaceship fixed on the **left side of the screen**, while enemies (`^`) and obstacles (`*`) spawn from the right and scroll leftwards. The player must **shoot destructible enemies** and **dodge indestructible obstacles** to survive.

The current version is **engine-agnostic** — it is implemented as a pure C++ framework with all objects, managers, and logic separated. A rendering/input layer (e.g., **SFML**, **SDL**, or console output) can be added later.

---

## 🎮 Game Design

### Grid / Lane Layout
- The game world is divided into **3 vertical lanes**.
- The **spaceship** is fixed on the X-axis, but can move **up and down between lanes**.
- Enemies and obstacles spawn in lanes and move leftwards.

### Objects
- **`^` Enemy (Destructible)**
  - Destroyed by a single bullet.
  - Increases score when destroyed.
- **`*` Obstacle (Indestructible)**
  - Cannot be destroyed.
  - Must be dodged.

### Controls
- **Move Up / Down** → Switch lanes.
- **Shoot** → Fire a bullet to destroy enemies.
- **Pause / Resume / Restart** → Game state management.

---

## 🛠 Features (Implemented in Code)

- **Lane-based movement system** (`PlayerController`).
- **Shooting with cooldown** (`Shooter` + `Bullet`).
- **Scrolling world speed** (`ScrollSystem`).
- **Obstacle/enemy spawning with safe lane guarantee** (`SpawnManager`).
- **Collision handling** (`Bullet ↔ Enemy`, `Player ↔ Obstacle`).
- **Scoring system** (`ScoreSystem`).
- **Game state management** (`GameManager`).

---

## 📂 Project Structure

```
SpaceGridShooter/
│── src/
│   ├── main.cpp            # Entry point
│   ├── GameManager.cpp     # Game state & orchestration
│   ├── PlayerController.cpp
│   ├── Shooter.cpp
│   ├── Bullet.cpp
│   ├── Obstacle.cpp
│   ├── SpawnManager.cpp
│   ├── ScrollSystem.cpp
│   ├── InputRouter.cpp
│   ├── ScoreSystem.cpp
│   ├── Pool.cpp
│   ├── Vector3.h           # Basic vector math helper
│── README.md
```

---

## 🔑 Core Classes & Responsibilities

### **GameManager**
- Singleton that controls the game flow (`Ready`, `Playing`, `Paused`, `GameOver`).
- Holds references to all major systems:
  - `SpawnManager` (spawning obstacles)
  - `ScoreSystem` (tracking score)
  - `PlayerController` (player logic)
  - `ScrollSystem` (speed scaling)

### **PlayerController**
- Handles lane switching.
- Requests shooting from `Shooter`.
- Stores current lane, target position, and movement smoothing.

### **Shooter**
- Controls bullet firing with cooldown.
- Spawns new `Bullet` objects.

### **Bullet**
- Moves rightwards with velocity.
- Has limited lifetime.
- Handles collisions with `Obstacle`.

### **Obstacle**
- Base obstacle class:
  - `destructible` enemies (`^`)
  - `indestructible` obstacles (`*`).
- Moves leftwards.
- Handles damage & destruction.

### **SpawnManager**
- Spawns new obstacles/enemies at timed intervals.
- Ensures **at least one safe lane** for the player.

### **ScrollSystem**
- Controls global scroll speed.
- Increases difficulty by ramping up speed over time.

### **InputRouter**
- Handles input mapping (e.g., keyboard, touch, etc.).
- Sends input commands to the player.

### **ScoreSystem**
- Singleton tracker for score.
- Adds points for kills and survival time.

### **Pool**
- Object pooling for reusing bullets/obstacles.

---

## 🧑‍💻 How to Build & Run

### Build (Console Test Version)
```bash
g++ -std=c++17 src/*.cpp -o game
./game
```

(Currently, this version only demonstrates **logic** and **console debugging output**.)

---

## 🚀 Future Improvements

- **Integrate rendering engine** (e.g., SFML, SDL, Raylib).
- Add **sprites and animations**.
- Add **sound effects** and background music.
- Expand scoring & difficulty scaling.
- Add **power-ups** (multi-shot, shield, etc.).

---

## 🎯 Goal of the Project

This project demonstrates:
- **Object-Oriented Game Architecture in C++**.
- **Game state management**.
- **Decoupled game logic** (independent of rendering/input backend).
- A **foundation** for building real-time 2D games.
