# Character Tracker
## Description
The Character Tracker is a C++ console application designed to manage relationships between individual characters and groups (currently referred to as Units).
It serves as an updated iteration of the earlier "Bond Tracker" codebase, with improved structure and expanded functionality.
The project is organized into multiple scripts, each handling a different aspect of the program, as detailed in the table below.

| File Name                        | Description                                                                              |
|----------------------------------|------------------------------------------------------------------------------------------|
| Source.cpp                       | The main script that coordinates program flow and loads the required files.              |
|----------------------------------|------------------------------------------------------------------------------------------|
| General.h                        | Header file for *General.cpp*.                                                           |
| General.cpp                      | Contains reusable modular functions that can be implemented in multiple projects.        |
|----------------------------------|------------------------------------------------------------------------------------------|
| Tracker.h                        | Header file for the Character Tracker scripts.                                           |
| Tracker-Class-Entity.cpp         | Implements the entity class.                                                             |
| Tracker-Class-Character.cpp      | Implements the character class.                                                          |
| Tracker-Class-Unit.cpp           | Implements the unit class.                                                               |
| Tracker-Namespaces-Interact.cpp  | Handles interactions between units and characters.                                       |
| Tracker-Namespaces-IO.cpp        | Manages input and output operations.                                                     |
| Tracker-Namespaces-Missing.cpp   | Handles missing characters and units.                                                    |
| Tracker-Namespaces-Relations.cpp | Handles connections between units and characters.                                        |
| Tracker-Namespaces-Support.cpp   | Extends *General.cpp* functionality with rule-based exclusions and additional features.  |
|----------------------------------|------------------------------------------------------------------------------------------|
| UnitTest.cpp                     | Unit tests for the class scripts using Microsoft Unit Testing for C/C++.                 |


## Current
- [ ] General Input Parameter Document
	- [ ] Improve initial read and verification processes.
	- [ ] Develop classes for managing Character and Unit lists.
		- [X] Implemented a Struct for managing the lists.
	- [ ] Implement a switch-case during entity feature creation.

## Backlog
- [ ] Make Unit Relations a composite of Character Relations
- [ ] Enable Output via Connection for improved data flow.
- [ ] Create Relation Alteration features.

# To Be Decided (TBD)
- [ ] Additional features and priorities will be determined as development progresses.