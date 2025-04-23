
## 📋 Cub3D Project Board (Trello-style)

### 🟦 To Do
#### Setup & Learning
- [ ] Install MLX and test example code
- [ ] Learn raycasting basics (watch YouTube videos or read guides)
- [ ] Understand X and Y axis math (angle, sin/cos, grid units)

#### Map Parsing
- [ ] Implement `.cub` file parser
- [ ] Parse resolution, floor & ceiling colors
- [ ] Parse texture paths (if required)
- [ ] Parse and validate map layout
- [ ] Find and validate player start position
- [ ] Create 2D array map representation

#### Rendering Prep
- [ ] Set up MLX window
- [ ] Draw background with two colors (ceiling/floor)
- [ ] Draw minimap (top-down map)
- [ ] Add player movement & rotation

---

### 🟨 In Progress
- [ ] Implement basic raycasting (vertical wall rendering)
- [ ] Fix fish-eye distortion
- [ ] Add collision detection for player
- [ ] Clean up input handling

---

### 🟩 Done
(This column will grow over time!)

---

### ⭐ Bonus
- [ ] Add texture rendering for walls
- [ ] Add door mechanic (open/close on keypress)
- [ ] Add minimap with player orientation
- [ ] Add basic sprites (e.g. health or items)
- [ ] Add mouse support (look direction)
- [ ] BMP screenshot saving

---

## ✅ Suggested Task Division (Example)

| Task | Student 1 | Student 2 |
|------|-----------|-----------|
| MLX Init & Window | ✔️ |  |
| Parser (config, map) | ✔️ | ✔️ |
| Player movement | ✔️ |  |
| Raycasting (core logic) |  | ✔️ |
| Drawing 3D scene |  | ✔️ |
| Drawing minimap | ✔️ |  |
| Textures |  | ✔️ |
| Final cleanup | ✔️ | ✔️ |
