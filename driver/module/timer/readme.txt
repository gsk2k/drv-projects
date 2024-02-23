Timers (tick tock, tick tock)
=============================

Introduction to the problem:
============================

The timers.c file represents a very simple timer framework which allows you to
setup event handling based on a timeout.  The basic primitives allow the
programmer to:

	-allocate or free timers

	-arm/disarm timers

	-set attributes and timeout for a timer

Currently, the self contained example will create timers up to the maximum
(currently defined as 10) with random timeout values from up to 20 seconds. 
Each timer will eventually expire and the associated call-back function executed.

Mandatory questions:
====================

The assignment is to identify as many weaknesses or bugs in the framework as you 
can find. You are welcome to identify any type of issue you feel is relevant.

Anything from logic errors to algorithmic limitations are fair game for
 identification.  

Optional questions:
====================

Each issue identified should have an illustrative text description 
of the problem and a proposed fix with code.

 Once you've identified the issues, you'll need to generate a performance profile 
for the code, identify the performance hotspots that could be further optimised and 
provide the optimisation in source to at least one of your identified areas.

If you have any issues building the source or running the example, please do not
hesitate to contact us.

