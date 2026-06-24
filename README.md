# Swarm Simulator

A 2D agent-based swarm simulation in C++ using Box2D for physics, built with
two teammates.

## What it does

- Each agent is built from a C++ `Agent` class hierarchy backed by Box2D
  rigid-body physics.
- Agents use sensor-driven attraction and repulsion fields, accumulating
  per-agent forces that push them toward designated target zones — this
  produces emergent swarm behavior rather than scripted movement.
- The simulation runs on a fixed-timestep loop with delta-time
  accumulation, decoupling physics updates from render rate so behavior
  stays consistent regardless of frame rate.
- Dear ImGui is integrated for real-time parameter tuning and live Box2D
  diagnostics while the simulation is running.
- Velocity-based color mapping visualizes kinetic-energy distribution
  live across swarms of up to 500 agents, making emergent behavior easier
  to spot while debugging.

## Team

Built with a 3-person team.
- @Eywu (Team-lead)
- @retreatawaloss (Physics Engine & Visualization)
- @5abah (Agent Architecture & Interactivity)

## Build

```bash
cmake -G Ninja -B build
ninja -C build
```

*(Update this if your actual CMake setup differs — fill in any
dependencies Box2D/Dear ImGui need that aren't vendored in the repo.)*

## Usage

```bash
./SwarmSimulator
```

Use the Dear ImGui panel to adjust simulation parameters (agent count,
attraction/repulsion strength, etc.) live while it's running.
