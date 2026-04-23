# Programming-Lab-C-Modular
🌿 GreenTrack - Community Garden Management System
This project was developed for the Programming Laboratory course (Unit 21178 - E-fólio A). The core challenge involved stabilizing a monolithic C application by identifying logical errors and refactoring the codebase into a clean, modular architecture.

🎯 Project Objectives
As specified in the official course requirements, this project focuses on:

Bug Detection & Resolution: Identifying and fixing over 10 critical issues, including memory leaks, array boundary errors, file handling logic (fscanf vs feof), and string security.

Code Modularization: Transitioning from a single-file structure to a multi-module architecture using Header (.h) and Source (.c) files.

Data Persistence: Implementing robust CSV parsing for real-time data storage and retrieval.

🌟 Key Features
Plant Database: Register, list, and manage botanical species with persistent storage in plantas.csv.

Irrigation Control: Monitor water requirements and maintain history in regas.csv.

Task Management: Schedule and track garden maintenance tasks (e.g., pruning, fertilizing) via tarefas.csv.

Automated Recovery: The system automatically loads all data upon startup and saves it upon exit.

🛠️ Technical Specifications
Language: C (ISO/IEC 9899 standard).

Architecture: Modular (Modules: Plantas, Regas, Tarefas, and Tipos).

Data Structures: Struct arrays with dynamic ID assignment and boundary checking (MAX_PLANTAS, MAX_REGAS).

Security & Stability: Improved data input safety using strncpy and pointer validation to prevent crashes.

📂 File Structure
plantas.c / .h – Botanical management module.

regas.c / .h – Irrigation logic and alerts.

tarefas.c / .h – Maintenance scheduling system.

tipos.h – Centralized definition of constants and structs.

main.c – Main entry point and CLI menu.

*.csv – Database files.

🚀 Compilation and Execution
To compile the project using GCC:

Bash
gcc -Wall main.c plantas.c regas.c tarefas.c -o greentrack
To run the application:

Bash
./greentrack
💡 Why this project stands out
This repository showcases the ability to audit third-party code, implement security fixes, and organize software using professional engineering principles (Separation of Concerns). The implementation specifically addresses common C pitfalls like incorrect loop conditions and improper file stream management.

Topics (Tags):
c-programming software-refactoring bug-fixing modular-programming data-persistence cli-application programming-laboratory

👨‍💻 Author
Luis Moura
Computer Engineering Student
