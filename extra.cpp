
/*
q.front points to the first station in the line (next to dequeue)
q.back points to the last station added to the queue

*/

/*
ok with my code i first go to the bfs function , in the bfs function i start from a1 and i want to go to a3
1. i create an emptyqueue (if imusing array method thi will be the same as initializing the array to store the nodes )
2. i mark the current station (start_station) as visited then i set its predecessor as NULL;
3. then i pass in the queue (which is like the array to it )and pass in the first station

====within enqueue====
1. i create a queue_node (queue_node consists of station and next)
2. in that new queue_node i set the station (this current station s) and next as NULL since there is nothing yet.
3. i check for q which is the so call array 
     -in the scenario that it is the first node being traversed, the front of the queue and the back of the queue is the current node being passed into the funciton
    -if its not the first node, i update the Queue_Node  then update the q.back with my current node
============================
4. while the queue is not empty ( it's checked by seeing if the front is NULL), dequeue the queue (which is the array
=======within dequeue==========
1.  it first checks if the front is NULL (redundant)
2.  create a temp Queue_Node and assign it to q.front
3. it assigns the value inside the queue_node (temp's station) to s
4. updates front to q.front -> next;
5. deletes the first node and returns s (the one being dequeued)
=========================== 
5.  back in bfs if the node being dequeued is the targeted end_station
 - print "reached
- retrace steps and print the entire route
6. so i create a for loop , the amount of connecting stations are already inserted inside the struct of Station , for each station the current station is connected to, run the loop
7. in the loop i create neighbor that goes thorugh the linked station of current ( which is the node/ station being dequed)
8. i check for the status whether it as been visited, if its not i
    - change the visit status
    - assign its predecessor as current (so that i know im traveling from this current node the dequeued node)
     - then i enqueue it
so that in this portion i enqueue the nodes to the queue so that it can keep looping till it reaches the destination node.
*/