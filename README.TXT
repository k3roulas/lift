

There are the main, 1 thread for the LiftManager and 1 thread by Lift.
The request is a Man with start level and end level.
A Lift can be in state routing or devlivering.
	In mode routing, it can stop on is way.
	In mode delivering, it can stop on his way and go further, but only in the same direction.
A lift have a direction : up, down or stand by

To process a new request, the LiftManager check if there is a lift in stand by, and choose the closer one.
Else, if there is a lift in his way, it assign the request to this lift.
If there is no lift available, it add the request to the FIFO event_stand_by.
When a lift become in stand by, it check the FIFO event_stand_by and process it.

 