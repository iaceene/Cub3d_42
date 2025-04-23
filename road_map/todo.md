# 🕹️ Cub3D Project Board

## 🟦 To Do

### 🔧 Setup & Learning
- [ ] Install MLX and test example code
- [ ] Learn raycasting basics (YouTube/tutorials)
- [ ] Understand X and Y axis math (angles, sin/cos, grid units)

### 🗺️ Map Parsing
- [ ] Implement `.cub` file parser
- [ ] Parse resolution, floor & ceiling colors
- [ ] Parse texture paths
- [ ] Parse and validate map layout (check closed walls)
- [ ] Detect and validate player start position
- [ ] Convert map into 2D array structure

### 🖼️ Rendering Prep
- [ ] Set up MLX window and loop
- [ ] Draw floor and ceiling (solid colors)
- [ ] Draw minimap grid (top-down map)
- [ ] Add basic player movement and rotation logic

---

## 🟨 In Progress

- [ ] Implement basic raycasting (wall detection and vertical rendering)
- [ ] Fix fish-eye distortion using perpendicular wall distance
- [ ] Add collision detection when moving into walls
- [ ] Improve keyboard input handling and key state

---

## 🟩 Done

- [ ] *(Leave this empty until you start completing tasks)*

---

## ⭐ Bonus Ideas

- [ ] Add texture rendering for walls (XPM image files)
- [ ] Implement doors that open/close on key press
- [ ] Draw live-updating minimap with player icon
- [ ] Add sprites (items, enemies)
- [ ] Add mouse support for player look direction
- [ ] Implement BMP screenshot saving (for eval bonus)
- [ ] Add weapon animation (e.g. gun image in hand)

---

## 👥 Task Distribution

| Task                          | Yassine | Teammate |
|-------------------------------|---------|----------|
| MLX Init & Window             | ✅      |          |
| Parser (config, map)          | ✅      | ✅       |
| Player movement               | ✅      |          |
| Raycasting (core logic)       |         | ✅       |
| Drawing 3D scene              |         | ✅       |
| Drawing minimap               | ✅      |          |
| Textures                      |         | ✅       |
| Final cleanup & polishing     | ✅      | ✅       |

