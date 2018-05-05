For Task 6, I attempted the extra credit version but had issues with the buffer incrementing without being incremented and printing twice for the agent (I made sure to confirm that only one of the processes was acting as the agent). I could not stop those errors so I decided to do the base version instead to have a working submission. I will include the extra credit version since it is almost done and would be working if not for the issues.

In both versions, I use three fork() calls to create a total of four processes. I did so by having the process which saw the pid output of the previous fork as greater than zero perform another fork. I also defined TOBACCO as 0, PAPER as 1, and MATCH as 2. This convention is used throughout the code.

In the extra credit version, I extended the ProducerConsumer.c sample by adding in another semaphore, queue, to protect the critical sector that is the curr_smoker variable which gives the index of the next smoker in the queue. Additionally, I added two more shared memory items, the queue as an array of integers and the curr_smoker pointer to the next smoker in the queue. At the start, each of the three smokers goes into a sleep state. The agent then generates a random number, either 0, 1, or 2. It puts the other two numbers that were not chosen on the buffer and, after gaining access to the queue semaphore, does a kill(smoker_pid, SIGCONT) on the next smoker in the queue to wake it up and allow it to continue.

The smoker then, after gaining the semaphore for the buffer critical sector, checks to see that the two items in the buffer are not the same as its item. If they are not the same, ie the two items it needs are on the table, it "smokes", increments the queue pointer, and does a V operation on the empty semaphore to allow the agent to restart the process. If one of the items on the table matches the smoker's item, it increments the queue pointer, does a kill(smoker_pid, SIGCONT) on the next smoker, does a V on the full to signal to awaken smoker that the buffer is still full, relinquishes its access to the buffer, and loops back to sleep. This continues until one of the three smokers gets what it needs. Unfortunately, the buffer's first value incremented with each smoker so the first smoker saw the buffer as containing a 0, ie tobacco, when it had tobacco while the subsequent smokers saw the first value of the buffer as containing a 1 and 2, respectively, telling them that their item was on the table.

In the base version, I extended the ProducerConsumer.c sample by adding three semaphores, one for each of the three smokers, all initially zero. Each of the smokers waits on their respective semaphore instead of sleeping. After generating the random number and placing the other two items on the table, the agent does a V on the semaphore of the corresponding smoker. That smoker performs a P on its semaphore, "smokes", then performs a V on the empty semaphore to allow the agent to start the same process again. I added a variable i to the agent if block to limit the number of iterations.

Both of these implementations avoid starvation since the smoker that is ready to smoke, ie the one who has the third item that is not on the table, will be able to smoke in either implementation. In the base implementation, the agent with V their semaphore and they will be able to smoke immediately. In the extra credit version, assuming that the items on the table don't change, the smoker that is able to smoke will be able to do so after waiting for the other two smokers to check the items on the table and relinquish access to it. Neither of these implementations will make a smoker that is ready to smoke wait indefinitely. I can, however, make a smoker wait indefinitely to smoke by never placing the correct items on the table.

The output is a bit messy because of the interleaving most likely. The things that happen are written out in plain text to make understanding easier. The lines that do not start with a tab are the first operation by that process, for example that the agent is about to put something on the table or that a smoker has woken up. It is followed by a few lines that are indented and indicate what that process has done, be it smoked or been unable to smoke and woken up the next process in the queue.




Basic version output:

Forking smokers (three smokers)
Starting procedure (set to perform 10 rounds)
9: Agent putting things on the table
	Agent put tobacco (item 0) on the table
	Agent put match (item 2) on the table
8: Agent putting things on the table
	Agent put tobacco (item 0) on the table
	Agent put match (item 2) on the table
Smoker with match called by agent
	Smoker with match found items 0 and 2 on table
	Smoker with match has smoked
Smoker with match called by agent
	Smoker with match found items 0 and 2 on table
	Smoker with match has smoked
7: Agent putting things on the table
	Agent put tobacco (item 0) on the table
	Agent put paper (item 1) on the table
6: Agent putting things on the table
Smoker with match called by agent
	Agent put tobacco (item 0) on the table
	Agent put paper (item 1) on the table
	Smoker with match found items 0 and 1 on table
	Smoker with match has smoked
Smoker with match called by agent
5: Agent putting things on the table
	Agent put tobacco (item 0) on the table
	Agent put match (item 2) on the table
	Smoker with match found items 0 and 2 on table
	Smoker with match has smoked
Smoker with match called by agent
4: Agent putting things on the table
	Agent put tobacco (item 0) on the table
	Agent put paper (item 1) on the table
	Smoker with match found items 0 and 1 on table
	Smoker with match has smoked
Smoker with match called by agent
3: Agent putting things on the table
	Agent put paper (item 1) on the table
	Agent put match (item 2) on the table
	Smoker with match found items 1 and 2 on table
	Smoker with match has smoked
Smoker with match called by agent
2: Agent putting things on the table
	Agent put tobacco (item 0) on the table
	Agent put paper (item 1) on the table
	Smoker with match found items 0 and 1 on table
	Smoker with match has smoked
Smoker with match called by agent
1: Agent putting things on the table
	Agent put tobacco (item 0) on the table
	Agent put paper (item 1) on the table
	Smoker with match found items 0 and 1 on table
	Smoker with match has smoked
Smoker with paper called by agent
	Smoker with paper found items 0 and 1 on table
	Smoker with paper has smoked
0: Agent putting things on the table
	Agent put tobacco (item 0) on the table
	Agent put match (item 2) on the table
Smoker with tobacco called by agent
	Smoker with tobacco found items 0 and 2 on table
	Smoker with tobacco has smoked
Smoker with tobacco called by agent




Extra Credit version output:
(Issues with printing twice from agent and buffer being incremented)

Forking smokers (three smokers)
Smoker with tobacco has awaken with item 0
Queue created: 1371,1372,1373
Agent putting things on the table
	Agent put tobacco (item 0) on the table
	Agent put match (item 2) on the table
	Agent waking up next smoker in queue: 0
Agent putting things on the table
	Agent put tobacco (item 0) on the table
	Agent put match (item 2) on the table
	Agent waking up next smoker in queue: 0
	Smoker with tobacco found items 0 and 2 on table
	Smoker with tobacco was not able to smoke
	Smoker with tobacco waking up next smoker in queue: 1
Smoker with paper has awaken with item 1
	Smoker with paper found items 1 and 2 on table
	Smoker with paper was not able to smoke
	Smoker with paper waking up next smoker in queue: 2
Smoker with match has awaken with item 2
	Smoker with match found items 2 and 2 on table
	Smoker with match was not able to smoke
	Smoker with match waking up next smoker in queue: 0
