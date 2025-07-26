# standaloneHbt
Package for analyzing two-particle correlation function, derived from STAR collaboration. 

## **Table of Content**
 - [Starter](#1-get-started)
 - [Directory Structure](#2-directory-structure)
 - [Usage](#3-usage)
 - [Instruction](#4-Instruction)

### 1. Get Started
The only dependency of the repository is ROOT. To start, clone the repository `git clone https://github.com/nscl-hira/standaloneHbt.git` and `source ${your_ROOT}/bin/thisroot.sh`.


### 2. Directory Structure
- [**`database`**](database/) : contain all metadata and input for HiRA analysis.
- [**`StarClassLibrary`**](StarClassLibrary/) : A outdated library for utilities and physics functions. Thoguh not extensively used, they are kept to avoid change in compilation.
- [**`StHbt`**](StHbt/) : source codes for the analysis of two-particle correlation function
- [**`HbtUserCode`**](HbtUserCode/) : source code HbtUserCodeized to read and analyze data of a particular experiment. 
- [**`macros`**](macros/) : contain driver codes 

### 3. Usage
To compile all required libraries, simply navigate to the directories and make in the order:
```
cd StarClassLibrary
make 
cd ../StHbt
make 
cd ../HbtUserCode
make
```
Then, you should be able to run the analysis macro in the root directory of the project:
```
root macros/load.C macros/analHiRA.C
```

### 4. Instruction
To develop the source code for reading and analyzing CF, users need to write the codes in the directories [HbtUserCode](./HbtUserCode/). These classes in `./HbtUserCode` are mostly derived from those the base classes in `StHbt`.

- [HbtUserCode](./HbtUserCode/) : construct classes derived from those in [StHbt](./StHbt/)
    - [Reader](./HbtUserCode/Reader/): an event reader according to the format of data. 
    - [Cut](./HbtUserCode/Cut/): set up gates to veto unwanted entity
    - [CorrFctn](./HbtUserCode/CorrFctn/): define the correlation function based on the pair information.

