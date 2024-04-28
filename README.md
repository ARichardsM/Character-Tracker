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
- [X] General relation tags - Adds tags to relations, which are printed when printing as a markdown file.
- [X] History feature - History can be pulled from the input files and are included when printing as a markdown file.

## Backlog
- [ ] Print a set number of entities
- [ ] Improve handling of missing entities
  - [ ] Disable the random pull if there are any missing entities
  - [ ] Allow a missing crew to be set to multiple crews
  - [ ] Allow a missing entity to be removed
- [ ] Refactor

## TBD
- [ ] Implement a testing system