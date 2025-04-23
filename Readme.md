## 🎯 Objective of Cub3D

Recreate a basic 3D game engine using **raycasting** (like Wolfenstein 3D) using the **MiniLibX** library. You’ll handle:
- Parsing a map file
- Rendering a 3D scene from a 2D map
- Handling player movement
- (Bonus) Adding textures, sprites, a minimap, mouse support, doors, etc.

---

## 🧠 What You Should Learn First

### 🔧 Prerequisites
| Topic                    | Resources & Notes |
|--------------------------|-------------------|
| **C graphics basics**    | Learn how MLX works (open a window, draw pixels, events). |
| **Raycasting**           | Core of Cub3D. Understand how it simulates 3D in a 2D map. |
| **Math (trig)**          | Understand `sin`, `cos`, angles, and how rays hit walls. |
| **Map parsing**          | How to read/validate a 2D map (walls, player pos, spaces). |
| **Game loop & input**    | Keyboard events, constant loop rendering. |
| **Code organization**    | Structs, file separation, and good architecture. |

---

## 🛠️ Roadmap & Task Breakdown (Team of 2)

> Each stage contains individual + collaborative work.

---

### **Stage 1: Setup & Research** ✅

**Time**: 1–2 days  
**Goal**: Both understand the basics, set up MLX and start small.

#### 🧑‍💻 Both:
- Install & compile MLX
- Create a window and draw a colored screen
- Play with key events

#### ✅ Deliverable:
- A running window that changes color with key press

---

### **Stage 2: Map Parsing & Validation**

**Time**: 3–5 days  
**Goal**: Read and validate the `.cub` map file

#### 👤 Teammate A:
- Handle file parsing
- Extract player spawn, direction, resolution, colors

#### 👤 Teammate B:
- Validate the map (closed walls, valid characters, etc.)
- Prepare map to be used for raycasting (2D array)

#### ✅ Deliverable:
- A parser that prints config and a validated map

---

### **Stage 3: Drawing the 2D Map (Top-Down View)**

**Time**: 1–2 days  
**Goal**: Draw the map in 2D to test positions and debugging

#### 👤 Teammate A:
- Draw grid blocks (like minimap)

#### 👤 Teammate B:
- Draw player, facing direction, and basic movement

#### ✅ Deliverable:
- A 2D debug window with movement & turning

---

### **Stage 4: Raycasting Core** 🚀

**Time**: 5–7 days  
**Goal**: Render a 3D scene with raycasting

#### 👤 Teammate A:
- Implement raycasting for vertical wall slices
- Handle distance correction (fish-eye fix)

#### 👤 Teammate B:
- Draw ceiling and floor
- Add player movement with collision detection

#### ✅ Deliverable:
- Working 3D engine showing a simple world

---

### **Stage 5: Code Refactoring & Structuring**

**Time**: 1–2 days  
**Goal**: Clean code, split files, improve structs

#### 👥 Together:
- Group functions into separate files: `parser.c`, `raycast.c`, `player.c`, `draw.c`
- Create proper structs: `t_map`, `t_player`, `t_ray`, etc.

---

### **Stage 6: Basic Bonus — Textures & Minimap**

**Time**: 3–5 days  
**Goal**: Make it nice-looking and improve features

#### 👤 Teammate A:
- Add textures to walls (load `.xpm` or `.png`)
- Implement texture mapping with rays

#### 👤 Teammate B:
- Draw a real-time minimap
- Add sprite support (optional)

---

### **Stage 7: Final Touches & Testing**

**Time**: 2–3 days  
**Goal**: Handle edge cases, leaks, crash scenarios

#### 👥 Together:
- Test invalid maps, weird movements
- Use `valgrind` to check leaks
- Clean and polish code

---

## 🧩 Optional Advanced Bonus

- Add doors (open/close)
- Add mouse support
- Add gun or enemy sprites
- Save screenshot to BMP
- Skybox and shading

---

## 🧠 Tips for Success

- **Commit often** and tag each other’s PRs if using GitHub
- Debug with a top-down view when your 3D breaks
- Stick to your roles but help each other — raycasting especially can be tricky
- Ask me for help with math or visuals when stuck

---