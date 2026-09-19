# 🚌 Interactive 2D Bus Journey Simulation

An interactive 2D computer graphics project developed in **C++** using **OpenGL** and **GLUT**. The application simulates a complete, five-stage urban commuter journey across distinct environments—from waiting curbside to riding through traffic and arriving at the final destination.

---

## 🌟 Project Overview

This project models an end-to-end urban transit journey divided into five sequential scenarios:
* **Scene 1: Waiting at the Bus Stop** — Metropolitan roadside featuring multi-story buildings, pedestrians, sidewalk vegetation, and cruising commuter buses.
* **Scene 2: Bus Arrival & Boarding** — Highway corridor with an 8-tower high-rise complex, continuous dual-lane vehicular traffic, and perspective-scaled passenger boarding routines.
* **Scene 3: Highway Transit & Traffic Signal Stop** — Urban intersection with a functional 3-state traffic signal (Green, Yellow, Red) where buses yield to crossing pedestrians[cite: 19].
* **Scene 4: Destination Arrival & Disembarking** — Campus terminal with arriving buses, passenger drop-offs, flowerbeds, and an overhead commercial flight pass[cite: 19].
* **Scene 5: Indoor Destination & Room Scene** — Detailed interior room featuring an interactive ceiling fan, wall clock synchronized with real system time, an animated character, and a blinking banner[cite: 19].

---

## 🎮 Controls & Interactions

### Global Navigation
| Key | Action |
| :---: | :--- |
| `1` | Switch directly to **Scene 1**[cite: 13] |
| `2` | Switch directly to **Scene 2**[cite: 13] |
| `3` | Switch directly to **Scene 3**[cite: 13] |
| `4` | Switch directly to **Scene 4**[cite: 13] |
| `5` | Switch directly to **Scene 5**[cite: 13] |
| `ESC` | Exit Application[cite: 13] |

### Scene-Specific Hotkeys
* **Scene 2 (Boarding Transit):**
  * `S` — Start highway car traffic[cite: 15, 19]
  * `E` — Stop/hide car traffic[cite: 15, 19]
  * `B` — Call bus to approach and stop at the station[cite: 15, 19]
  * `M` — Trigger commuters to board the bus[cite: 15, 19]
  * `G` — Depart bus towards the exit[cite: 15, 19]
* **Scene 3 (Traffic Control):**
  * Fully automated traffic light sequence (`BUS_APPROACHING` $\rightarrow$ `BUS_STOPPING` $\rightarrow$ `PEDESTRIAN_CROSSING` $\rightarrow$ `BUS_DEPARTURE` $\rightarrow$ `SCENE_DONE`)[cite: 16]
* **Scene 4 (Campus Terminal):**
  * `W` — Dispatch bus into campus stop[cite: 17, 19]
  * `E` — Disembark passengers to walk onto campus[cite: 17, 19]
  * `L` — Depart bus while passengers remain[cite: 17, 19]
* **Scene 5 (Destination Interior):**
  * `F` — Toggle ceiling fan ON/OFF[cite: 18, 19]
  * `+` / `-` — Increase / decrease fan speed[cite: 18, 19]
  * `W` — Toggle character arm waving[cite: 18, 19]
  * `B` — Toggle "THANK YOU" banner blinking[cite: 18, 19]
  * `R` — Reset room animation states[cite: 18, 19]

---

## 📂 Project Structure

```text
├── main.cpp          # Master controller, GLUT setup & keyboard router[cite: 13]
├── scenario1st.cpp   # Scene 1: Waiting at the Bus Stop[cite: 14]
├── scenario2nd.cpp   # Scene 2: Bus Arrival & Boarding (Tonmoy)[cite: 15]
├── scenario3rd.cpp   # Scene 3: Traffic Signal & Zebra Crossing[cite: 16]
├── scenario4th.cpp   # Scene 4: Campus Disembarking[cite: 17]
└── scenario5th.cpp   # Scene 5: Interior Destination Room[cite: 18]
