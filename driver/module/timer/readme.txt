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

Details:
====================

Assignment was to identify as many weaknesses or bugs in the framework.

Anything from logic errors to algorithmic limitations were fair game for identification.

I have documented the errors I encountered and provided detailed descriptions of the fixes and optimizations in a file named "timer_qnx_fixes". The updated code can be found under the name "timer_gsk.c". Additionally, I have generated a performance profile for the code, and the relevant data is stored in the "perf.data" file - you can review the performance information by running the command 'perf report' in the same directory. For more low-level information, you can run 'perf script' in the same terminal.