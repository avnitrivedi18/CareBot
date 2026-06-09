# CareBot
AI-Assisted Automated Medicine Dispenser and Healthcare Monitoring System

## Overview
CareBot is a microcontroller-based automated medication dispensing and health-monitoring platform designed to improve medication adherence, reduce human error, and provide continuous patient supervision. The system combines embedded electronics, IoT connectivity, computer vision, and mechanical design to create an accessible healthcare solution for home and assisted-care environments.

The platform features an automated dispensing mechanism powered by a precision stepper motor, real-time health monitoring, patient identification, and remote caregiver notifications through a connected dashboard. CareBot aims to provide a low-cost, scalable solution that enhances patient safety while reducing the burden on caregivers.

## Problem Statement

Medication non-adherence, missed doses, and accidental overdosing remain significant challenges for elderly patients, individuals with chronic illnesses, and patients requiring long-term care.

CareBot addresses these challenges by:

* Automating medicine dispensing according to prescribed schedules.
* Monitoring patient health parameters in real time.
* Providing alerts for missed medications.
* Enabling remote monitoring for caregivers and family members.
* Reducing manual intervention and medication management errors.

---

## Key Features

### Automated Medicine Dispensing

* Scheduled medicine dispensing using a precision stepper motor.
* Controlled release mechanism to prevent overdosing.
* Motorized rack-and-pinion system for reliable dispensing.
* Integrated collection ramp for easy medicine retrieval.

### Patient Identification

* Face detection using computer vision.
* Ensures medication is dispensed to the correct patient.
* Supports future expansion toward personalized healthcare assistance.

### Health Monitoring

* Heart rate monitoring.
* Body temperature monitoring.
* Real-time sensor data collection and logging.

### Smart Alert System

* Audible buzzer notifications during dispensing.
* IR break-beam sensors confirm medicine retrieval.
* Missed-dose detection and caregiver alerts.

### IoT Connectivity

* Wireless communication through ESP32.
* Remote monitoring dashboard.
* Dose history and health data logging.
* Real-time notifications for caregivers and family members.

### User Interface

* Interactive touchscreen interface.
* Mobile application for monitoring and configuration.
* Web dashboard for remote access and data visualization.

---

## System Architecture

Patient → Face Detection System

↓

ESP32 Controller

├── Real-Time Clock (RTC)

├── Heart Rate Sensor

├── Temperature Sensor

├── IR Break-Beam Sensors

├── Touchscreen Interface

├── Wi-Fi Communication Module

└── Stepper Motor Driver

↓

Automated Dispensing Mechanism

↓

Medicine Collection Ramp

↓

Patient

↓

Cloud Dashboard / Mobile App / Caregiver Monitoring

---

## Engineering Challenges Addressed

* Reliable dispensing of medicines at scheduled intervals.
* Detection and confirmation of successful medicine retrieval.
* Prevention of accidental double dispensing.
* Integration of multiple sensors into a single embedded platform.
* Low-cost implementation suitable for home healthcare applications.
* Remote monitoring while maintaining system reliability.
* Modular architecture for future feature expansion.

---

## Mechanical Design

The dispensing mechanism consists of:

* Multi-compartment medicine storage system.
* Stepper-motor-driven dispensing assembly.
* Rack-and-pinion actuation mechanism.
* Medicine delivery chute.
* Retrieval ramp for user accessibility.

Future repository updates will include:

* CAD models
* Assembly drawings
* Exploded views
* Mechanical simulations

---

## Technologies Used

### Hardware

* ESP32
* Stepper Motor
* Real-Time Clock (RTC) Module
* IR Break-Beam Sensors
* Heart Rate Sensor
* Temperature Sensor
* Touchscreen Display

### Software

* C
* Python
* OpenCV

### Design Tools

* AutoCAD
* Fusion 360

### Communication

* Wi-Fi
* IoT Dashboard

---

## Performance 

| Metric                |  Performance     |
| --------------------- | -----------------|
| Dispensing Accuracy   | >95%             |
| Missed Dose Detection | <15 seconds       |
| Cost of Prototype     | Under ₹4,000($42)|
| Remote Monitoring     | Real-Time        |
| System Availability   | 24/7 Operation   |

---

## Current Project Status

### Completed

* Literature Review
* Problem Definition
* System Architecture Design
* Feature Planning
* Mechanical Concept Development
* CAD Modeling
* Electronics Selection
* Prototype Design
* Hardware Integration
* Mobile Application Development
* IoT Dashboard Development
* Testing and Validation
### Planned
* User Trials
* Real setting testing

---

## Future Research Directions

* Machine Learning-based medication adherence prediction.
* Fall detection using computer vision.
* Voice-assisted healthcare interaction.
* AI-powered patient monitoring and analytics.
* Autonomous healthcare assistant robots.
* Multi-patient medication management systems.
* Integration with wearable health devices.

---

## Repository Contents

* CAD Models
* Circuit Diagrams
* Source Code
* Sensor Integration Documentation
* Research Notes
* Project Reports
* Testing Results
* Prototype Images and Videos

---

## Vision

CareBot is envisioned as a step toward affordable, intelligent healthcare assistance systems that combine robotics, embedded systems, computer vision, and IoT technologies to improve patient safety, independence, and quality of life.
