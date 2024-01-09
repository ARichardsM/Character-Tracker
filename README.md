# Character Tracker
## Description
Replacement for a previous code, Bond Tracker, a C++ Console Script.
The character tracker is used to manage the simple connections between multiple characters and groups of characters, referred to as Units.
The project consists of the four scripts shown in the table below.
<br> <br>
| Name         | Purpose                                                                           |
|--------------|-----------------------------------------------------------------------------------|
| Source.cpp   | Main script, pulls necessary files and loops while the script is in use.          |
| General.cpp  | Contains general modular functions that can be implemented in multiple projects.  |
| Classes.cpp  | Contains scripts for the classes and interactions used by Source.cpp.             |
| UnitTest.cpp | Unit tests for the Classes.cpp scripts using Microsoft Unit Testing for C/C++.    |

## Current
- [ ] Improved file reading
  - [ ] String Character and Unit Constructor
  - [ ] Allow multiple delims
  - [ ] Allow markdown files

## Backlog
- [ ] General relation tags
- [ ] More unit tests
- [ ] Print a set number of entities
- [ ] Improve handling of missing entities
  - [ ] Disable the random pull if there are any missing entities
  - [ ] Allow a missing crew to be set to multiple crews
  - [ ] Allow a missing entity to be removed