# Character Tracker
## Description
Replacement for a previous code, Bond Tracker, a C++ Console Script.
The character tracker is used to manage the simple connections between multiple characters and groups of characters, referred to as Units.
The project consists of the four scripts shown in the table below.
<br> <br>
| Name                      | Purpose                                                                           |
|---------------------------|-----------------------------------------------------------------------------------|
| Source.cpp                | Main script, pulls necessary files and loops while the script is in use.          |
|---------------------------|-----------------------------------------------------------------------------------|
| General.h                 | Headers for General.cpp.                                                          |
| General.cpp               | Contains general modular functions that can be implemented in multiple projects.  |
|---------------------------|-----------------------------------------------------------------------------------|
| Tracker.h                 | Headers for Tracker CPP Files.                                                    |
| TrackerClassEntity.cpp    | Contains scripts for the entity class.                                            |
| TrackerClassCharacter.cpp | Contains scripts for the character class.                                         |
| TrackerClassUnit.cpp      | Contains scripts for the unit class.                                              |
| TrackerNamespaces.cpp     | Contains scripts for the tracker interactions.                                    |
|---------------------------|-----------------------------------------------------------------------------------|
| UnitTest.cpp              | Unit tests for the Classes.cpp scripts using Microsoft Unit Testing for C/C++.    |

## Current
- [ ] Improve handling of missing entities
  - [X] Disable the random pull if there are any missing entities
  - [X] Allow a missing crew to be set to multiple crews
  - [X] Allow a missing entity to be removed

## Backlog
- [ ] Print a set number of entities
- [ ] Refactor

## TBD
- [ ] Implement an improved testing system