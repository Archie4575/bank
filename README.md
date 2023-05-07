# `bank`
Bank Tellers simulation for COMP2006 Operating Systems

## Installation
Please install using the following set of commands:
```
git clone https://github.com/Archie4575/bank
cd bank
make
```
Installation assumes requisite Linux build environment, namely `git`, `make`, `gcc`, etc.

## Usage
```
./cq queue_length customer_interval withdrawal_duration deposit_duration information_duration
```
All parameters should be integers, with all durations measured in seconds. As example usage is as follows:
```
./cq 15 3 6 4 2
```
The above would simulate a queue length of 15, with customers arriving every 3 seconds, where the durations of withdrawals, despoits, and asking information are 6, 4, and 2, respectively.
