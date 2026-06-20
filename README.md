# PID Control System Simulations (C & Python)

This repository contains 4 different physical system simulations designed to understand, implement, and optimize PID (Proportional-Integral-Derivative) control loops. The core mathematical models and control algorithms are written from scratch in **C**, and the simulated data is dynamically visualized using **Python (Matplotlib)**.

## 📁 Project Structure

- **`01-Aircraft-Autopilot/`**: Altitude control loop simulation for an aircraft trying to reach and maintain a target altitude.
- **`02-Adaptive-Cruise-Control/`**: Autonomous vehicle safety tracking system. Adjusts gas and brake inputs based on the leading vehicle's sudden velocity changes.
- **`03-Battery-Management-System/`**: Thermal control loop for EV batteries. Monitors and regulates charging current and cooling power to prevent overheating during fast charging.
- **`04-Smart-Thermostat/`**: Indoor climate control simulation that counters external environmental heat losses using integral gain to eliminate steady-state error.

## 🛠️ How It Works

1. Each project directory contains a core **C file** (`.c`) that handles the PID algorithms ($K_P, K_I, K_D$) and the physical state space equations.
2. Running the compiled C application generates a structured text data file (`.txt`).
3. The **Python script** (`.py`) reads this generated data in real-time to plot performance graphics, making it easy to analyze overshoots, settling times, and system stability.

## 💻 Technical Highlights

- Manual PID Parameter Tuning & Optimization
- Handling Steady-State Error and Overshoots
- State-space data streaming via file I/O operations
- C & Python Integration for Embedded Systems Engineering
