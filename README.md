# Process Scheduler calculator

[![N|Solid](https://cldup.com/dTxpPi9lDf.thumb.png)](https://nodesource.com/products/nsolid)

[![Build Status](https://travis-ci.org/joemccann/dillinger.svg?branch=master)](https://travis-ci.org/joemccann/dillinger)


This repository is a simple example that calculate some metrics from different types of schedulers.


## Clone Project

```bash
$ git clone https://github.com/MichaelBittencourt/ProcessSchedulerCalculator.git
$ cd RedirectPipeExamples
```

## Running

```bash
$ make run
```

## Examples Input and output

The number of process is the first value
The next values are the momment where the process arrive to scheduler and the cpu times that it will spend.
 
 ```
 N
 arrival_1 duration_1
 arrival_2 duration_2
 ...
 arrival_N duration_N
 ```

 The output should show a string with the algorithm and the average of values separated by a space.

 ```
 FCFS finishTimeAverage responseTimeAverage waitTimeAverage
 ```

### Input 1

```
4
0 20
0 10
4 6
4 8
```

### Output 1

```
FCFS 30.5 19.5 19.5
```

### Input 2

```
4
2 20
2 10
4 6
4 8
```

### Output 2

```
FCFS 31.5 20.5 20.5
```

### Input 3

```
11
0 20
1 10
4 6
4 8
5 10
5 5
6 100
7 10
8 2
9 2
10 2
```

### Output 3

```
FCFS 93.7 77.8 77.8
```
