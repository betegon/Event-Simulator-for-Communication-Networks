# Event Simulator for Communication Networks

Create an Event Simulator for Communication Networks in C programming language. First create an event simulator and then apply it to a communication system.

## Structure

The repository is divided in two exercises:

*  Event Simulator Engine  (MMinfinite folder)
	* Implement it in C programming Llanguage
	* Use linked list for inserting all events
	* Sort events in the list by execution time.
	* Process each event depending of their type.
	*  Analyze the correct operation of the event engine, for which An M/M/∞ system is used, in which the packages come according to a Poisson process, and nothing else is transmitted, assuming a time of service negative exponential.
 	* Portray in Octave the time between event arrivals and also the average time a packet stays in the system.
	
* Analysis of a finite sources and pure loss Communication system (FiniteSources folder)
	* Use of the simulator for the analysis of communication system
	* Use the simulator to estudy the behavior of a pico-cell of a mobile communication system.
	* Portray in Octave probability of loss according to the number of sources in the system
	* Portray time percentage that corresponds to all resources being occupied at the same time.
	
## Code 

Both folders containg same files names.
* `"main.c"`: Main C code.
* `"library2.h"`: Library  containing all functions and constants `"main.c"` utilize
* `"graphics.m"`: Octave Script where the calculus and representation (plots) are made.

## Exercises Guidelines

Image below shows exercises 1 and 2 guidelines.

* Ex.1

![Implementation](https://raw.githubusercontent.com/betegon/Event-Simulator-for-Communication-Networks/master/Documentation/implementation.png)

![Test](https://raw.githubusercontent.com/betegon/Event-Simulator-for-Communication-Networks/master/Documentation/proof.png)


* Ex.2

![Guidelines](https://raw.githubusercontent.com/betegon/Event-Simulator-for-Communication-Networks/master/Documentation/projectB.png)

the next image shows some examples of parameters to use for implementing the exercises solutions.

![parameters](https://raw.githubusercontent.com/betegon/Event-Simulator-for-Communication-Networks/master/Documentation/parameters.png)

