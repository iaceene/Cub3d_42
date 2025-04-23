
## 📋 Cub3D Project Board

### 🟦 To Do
#### Setup & Learning
- [X] Install MLX and test example code
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

## Links

- Minilibx: [hsmits MiniLibX documentation](https://harm-smits.github.io/42docs/libs/minilibx)
- Minilibx: [gontjarow's MiniLibX tutorial](https://gontjarow.github.io/MiniLibX/)
- Xlib (for MLX events): [The Xlib Manual](https://tronche.com/gui/x/xlib/)
- Raycasting: [Lode's Computer Graphics Tutorial - Raycasting](https://lodev.org/cgtutor/raycasting.html)
- Raycasting: [Permadi's Raycasting tutorial](https://permadi.com/1996/05/ray-casting-tutorial-table-of-contents/)
- Movement: [Calculating heading in 2d games: Using trigonometric functions part 1](http://gamecodeschool.com/essentials/calculating-heading-in-2d-games-using-trigonometric-functions-part-1/)