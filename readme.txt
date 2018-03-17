How to run the program
----------------------

1. Open zip file and extract the files to a directory

2. Open the terminal

3. cd to the directory containing the these files
   eg. cd '/home/user/Documents/SIM-A2-CSCI203-2012S3-TanShiTerngLeon'

4. Type "make" in the terminal and enter

5. Type "./Assignment2.exe" and enter to run the program


------------------------- Task Requirements -------------------------

Queues are commonly used in network systems. For example, e-mail is placed
in queues while it is waiting to be sent and after it arrives at the recipient’s
mailbox. A problem occurs, however, if the outgoing mail processor cannot
send one or more of the messages in the queue. For example, a message
might not be sent because the recipient’s system is no available.
Write an e-mail simulator that processes mail at an average of 40 messages
per minute. As messages are received, they are placed in a queue. For the
simulation, assume that the messages arrive at an average rate of 30
messages per minute. Remember, the messages must arrive randomly, so you
will need to use a random number generator to determine when messages are
received.

Each minute, you can dequeue up to 40 messages and send them. Assume
that 25% of the messages in the queue cannot be sent in any processing cycle.
Again, you will need to use a random number to determine whether a given
message can be sent. If it cannot be sent, put it back at the end of the queue
or enqueue it.

Run the simulator for 10 to 15 minutes, tracking the number of times each
message had to be requeued. At the end of the simulation, print the statistics
that show:
1. The total messages processed
2. The average arrival rate
3. The average number of messages sent per minute
4. The average number of messages in the queue in a minute
5. The number of messages sent on the first attempt, the number sent on
the second attempt, and so forth
The average number of times messages had to be requeued (do not include
the messages sent the first time in this average.)