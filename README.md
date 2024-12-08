# Character Tracker
## Description
The Character Tracker is a C++ console application designed to manage relationships between individual characters and groups, referred to as Units.
It serves as an updated version of the previous "Bond Tracker" code. 
The project is structured around several scripts that handle different aspects of functionality, as outlined in the table below:


| Name                             | Purpose                                                                                                           |
|----------------------------------|-------------------------------------------------------------------------------------------------------------------|
| Source.cpp                       | Main script, coordinates the program and loads the files for use.                                                 |
|----------------------------------|-------------------------------------------------------------------------------------------------------------------|
| General.h                        | Headers for General.cpp.                                                                                          |
| General.cpp                      | Contains reusable modular functions that can be implemented in multiple projects.                                 |
|----------------------------------|-------------------------------------------------------------------------------------------------------------------|
| Tracker.h                        | Headers for Character Tracker specific scripts.                                                                   |
| Tracker-Class-Entity.cpp         | Contains scripts for the entity class.                                                                            |
| Tracker-Class-Character.cpp      | Contains scripts for the character class.                                                                         |
| Tracker-Class-Unit.cpp           | Contains scripts for the unit class.                                                                              |
| Tracker-Namespaces-Interact.cpp  | Contains scripts for the interaction scripts, which handle general interactions between the units and characters. |
| Tracker-Namespaces-IO.cpp        | Contains scripts for input and output, which read in and print out data.                                          |
| Tracker-Namespaces-Missing.cpp   | Contains scripts for handling missing characters and units.                                                       |
| Tracker-Namespaces-Support.cpp   | Contains scripts for rule-based exclusion and extensions of General scripts.                                      |
|----------------------------------|-------------------------------------------------------------------------------------------------------------------|
| UnitTest.cpp                     | Unit tests for the class scripts using Microsoft Unit Testing for C/C++.                                          |


## Current
- [ ] General Input Parameter Document
	- [ ] Entity Feature Switch Case

## Backlog
- [ ] Character and Unit List Classes
- [ ] Output Via Connection
- [ ] Alter Relations
- [ ] Implement an improved testing system
- [ ] Improved initial read and verify

## TBD
