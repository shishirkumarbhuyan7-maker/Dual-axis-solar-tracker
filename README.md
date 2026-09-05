# Dual-Axis Solar Tracking and PV Power Monitoring System

An Arduino-based dual-axis solar tracking system designed to orient a photovoltaic (PV) source toward the direction of maximum incident light while monitoring its electrical output under different load conditions.

## Project Overview

This project implements an automatic dual-axis solar tracking system using an Arduino Uno, four LDR sensors, and two servo motors.

Four LDR sensors detect the relative light intensity from the left, right, top, and bottom directions. The Arduino compares these readings and independently controls two servo motors to adjust the horizontal and vertical orientation of the solar panel.

The system also includes photovoltaic voltage monitoring using a 10 kΩ–10 kΩ voltage divider. The measured voltage is used to estimate load current and output power for a known resistive load.

The complete system was designed and simulated using Tinkercad Circuits.

## Objectives

- Implement automatic dual-axis solar tracking.
- Detect the direction of stronger incident light using four LDR sensors.
- Control horizontal and vertical positioning using servo motors.
- Monitor photovoltaic voltage using Arduino.
- Estimate load current and output power.
- Characterize PV output under different resistive load conditions.

## Components Used

- Arduino Uno R3
- 4 × LDR / Photoresistors
- 4 × 10 kΩ resistors for LDR voltage dividers
- 2 × Micro Servo Motors
- Solar Cell
- 2 × 10 kΩ resistors for voltage sensing
- Resistive load
- 2 × Multimeters
- Breadboard
- Jumper wires

## Pin Configuration

| Component | Arduino Pin |
|---|---|
| Left LDR | A0 |
| Right LDR | A1 |
| Top LDR | A2 |
| Bottom LDR | A3 |
| Solar Voltage Sensor | A4 |
| Horizontal Servo | D9 |
| Vertical Servo | D10 |

## Circuit Description

### LDR Sensor Network

Each LDR is connected as a voltage divider with a 10 kΩ resistor.

The four sensor outputs are connected to:

- A0 → Left LDR
- A1 → Right LDR
- A2 → Top LDR
- A3 → Bottom LDR

The Arduino continuously reads the four analog values.

### Servo Motor Control

Two servo motors are used for positioning:

- D9 → Horizontal servo
- D10 → Vertical servo

The horizontal servo controls the left-right movement, while the vertical servo controls the up-down movement.

### PV Voltage Measurement

A 10 kΩ–10 kΩ voltage divider is connected to the solar-cell output.

Since both resistors have equal resistance:

V_A4 = V_PV / 2

Therefore:

V_PV = 2 × V_A4

The Arduino uses this relationship to calculate the actual solar-cell voltage.

## Working Principle

### 1. Light Detection

The four LDR sensors detect light intensity from different directions.

The Arduino reads the sensor values using its analog input channels.

### 2. Tracking Error Calculation

The horizontal and vertical tracking errors are calculated as:

Horizontal Error = Left LDR − Right LDR

Vertical Error = Top LDR − Bottom LDR

A threshold is used to prevent unnecessary servo movement caused by small differences in sensor readings.

### 3. Horizontal Tracking

If the horizontal error exceeds the threshold, the horizontal servo is moved by a small angular step.

The servo position is continuously adjusted until the difference between the left and right sensor readings becomes sufficiently small.

### 4. Vertical Tracking

The same principle is applied to the top and bottom LDRs.

The vertical servo adjusts the panel position until the top-bottom difference falls within the defined threshold.

### 5. Servo Position Limiting

Both servo angles are constrained between 0° and 180°.

## PV Power Calculation

The active resistive load used in the integrated simulation is:

R = 82 Ω

The load current is estimated using Ohm's law:

I = V / R

The output power is then calculated as:

P = V × I

The Arduino displays the calculated voltage, current, and power through the Serial Monitor.

## PV Load Characterization

The solar cell was tested using different resistive loads to study the relationship between load resistance, voltage, current, and output power.

| Load Resistance | Voltage | Current | Power |
|---:|---:|---:|---:|
| 100 Ω | 4.70 V | 47.0 mA | 220.9 mW |
| 150 Ω | 4.81 V | 32.0 mA | 153.9 mW |
| 220 Ω | 4.87 V | 22.1 mA | 107.6 mW |
| 330 Ω | 4.88 V | 14.8 mA | 72.2 mW |
| 470 Ω | 4.95 V | 10.5 mA | 52.0 mW |
| 66.6 Ω | 4.53 V | 66.6 mA | 301.7 mW |
| 82 Ω | 4.52 V | 56.3 mA | 254.5 mW |

The highest measured output power among the tested load conditions was approximately:

Power ≈ 301.7 mW
Voltage ≈ 4.53 V
Current ≈ 66.6 mA
Load ≈ 66.6 Ω

This represents the maximum measured power point among the tested resistive loads under the simulated condition.

Note: This project does not implement a true MPPT algorithm. The load sweep is used for basic PV output characterization.

## Integrated Simulation Result

With the 82 Ω load connected, the Arduino-based monitoring system produced approximately:

Solar Voltage ≈ 4.61 V
Current ≈ 56.27 mA
Power ≈ 259.61 mW

The dual-axis tracking system also responded to changes in LDR illumination by independently adjusting the horizontal and vertical servo positions.

## Sample Serial Monitor Output

L=54 R=54 T=54 B=54 | H=90 V=90 | Solar Voltage=4.61 V | Current=56.27 mA | Power=259.61 mW

When the light direction is changed, the LDR readings become different and the corresponding servo angle changes.

## Control Algorithm

Start

↓
Read four LDR values

↓
Calculate horizontal error and vertical error

↓
Compare errors with threshold

↓
Move horizontal servo if required

↓
Move vertical servo if required

↓
Read PV voltage

↓
Calculate current using I = V/R

↓
Calculate power using P = V × I

↓
Display values on Serial Monitor

↓
Repeat

## Software and Simulation Tools

- Arduino C/C++
- Arduino Servo Library
- Tinkercad Circuits

## Features

- Automatic dual-axis solar tracking
- Four-channel light sensing
- Independent horizontal and vertical servo control
- Threshold-based tracking control
- PV voltage monitoring
- Resistive-load power calculation
- PV load characterization
- Real-time Serial Monitor output
- Tinkercad-based circuit simulation

## Project Structure

Dual-axis-solar-tracker/
│
├── Dual_axis_solar_tracker.ino
│
└── README.md

## Future Improvements

- Implement a dedicated MPPT control algorithm.
- Add a current sensor for direct current measurement.
- Add an LCD or OLED display for real-time monitoring.
- Add voltage and current data logging.
- Compare fixed-panel and tracking-panel output under identical conditions.
- Develop a physical hardware prototype.
- Analyze tracking accuracy and power improvement experimentally.

## Project Status

Completed Simulation

The dual-axis tracking, PV voltage monitoring, load-current estimation, and power calculation have been successfully tested in Tinkercad Circuits.

## Author

Electrical Engineering Student
National Institute of Technology, Rourkela

## Repository

Arduino source code and project documentation are available in this repository.
