#include <iostream>
using namespace std;
/*
unable :
Station *next_station = a;
Station *previous_station = b

=======================================
int station_count;
Station *linked_station[station_count];
-system needs to know size before compile to allocate sufficient bytes 
*/
/*
main requries Station station_name = {};
wereas other only need Station *station_name
one requires pointer because its storing adress of pointer/ pointer one is initializing it;

do they know why some uses -> and why some is only .

*/
struct Station
{
	string station_name;
	string station_line;
	bool visited_status;
	int station_count;
	Station *linked_station[6];
	Station *predecessor; //onlu purpose if for tracking to be printed later
};

struct Queue_Node
{
	Station *station;
	Queue_Node *next;
};

struct Queue
{
	Queue_Node *front;
	Queue_Node *back;
};

/*where storing comes into place
#define SIZE = 10;
station traversed_station=[SIZE];
-then store it inside , just like tutorial

use linked list instead
*/

//Queue *q to pass by reference 
//new is stored in the heap
void enqueue(Queue &q, Station *s)
{
	//s is the start station
	Queue_Node *Node = new Queue_Node;
	Node -> station = s;
	Node -> next = NULL;
	//in missbridget's class we first check if queue is full, but not needed here since using linked list
	//check
	if (q.back == NULL)
		q.front = q.back = Node; //huh
	else 
	{
		q.back -> next = Node;
		q.back = Node;
	}
}
//returns a Station value to process to get to the next station
//why using &q nd not *q (elaborate later)
Station  *dequeue(Queue &q)
{
	/*in missbridget's class deque function consists of:
	-moving the values foward in a while loop
	-check if the array is empty

	here :
	-check if queue is empty (if front is NULL)
	-just move the ront node to the next node then delete the used node
	therefore much more efficient as no shifting is involved

	here the steps are similar to the linked-lst exercises in the first few classes
	*/
	
	//check if queue is empty
	if (q.front == NULL)
		return (NULL);
	/*
	basically whats being done here is dequeue then update the front
	-first store whats infornt of q in a temp var
	-return the station of q.front (this is whats being dequed)
	-update q.front as the next station by getting it from q.front -> next
	-delete temp since we only created that to store q.front to temp to assign temp to s
	*/
	Queue_Node *temp = q.front;
	Station *s = temp -> station; //returning value (create a temp station?)
	q.front = q.front -> next;

	delete temp;
	return (s);

}

//write function to show nodes traversed
/*
whenever a node is visitied it queues the adjacent nodes
to prevent a node to be visited 
*/
bool isEmpty(Queue &q)
{
	return q.front == NULL;
}
void bfs(Station *start_station, Station *end_station)
{
	Queue queue;//create an empty queue

	start_station -> visited_status = 1; //mark the current station as visited
	start_station -> predecessor = NULL; //mark NUll since its the first
	
	enqueue (queue, start_station);
	//loop start to search this part is just going through the list until it find the path
	while (!isEmpty(queue)) // while q is not empty,is_empty is a function
	{
		Station *current = dequeue(queue); //remember deque returns a Station
		cout << "Visiting" << current -> station_name << endl;

			if (current == end_station)
			{
				cout << "\n Reached :" << end_station -> station_name << endl;
				//traceback from source to end and print out
				cout << "route :";
				Station *path_node = end_station;
				while (path_node != NULL)
				{
					cout << path_node -> station_name;
					path_node = path_node -> predecessor;
					if (path_node != NULL)
						cout << "<-";
				}
				cout << endl;
				return;
			}

		for (int i = 0; i < current -> station_count; i++)
		{
			Station *neighbor = current -> linked_station[i]; //station neighbour are adjecent nodes
			if (!neighbor -> visited_status) //if the station hasn't been visited do the following 
			{
				neighbor->visited_status = 1;
                neighbor->predecessor = current;  // Save path
                enqueue(queue, neighbor);
			}
		}
	}

    // If the queue is empty and we didn't find the destination
    cout << "\nNo path found.\n";

}

int main()
{
	//unable to insert station immediately in case stations are not initialized yet
	Station a1 = {"a1","KELANA JAYA", 0, {}};
	Station a2 = {"a2","KELANA JAYA", 0, {}};
	Station a3 = {"a3","KELANA JAYA", 0, {}};
	Station b1 = {"b1"," SUBANG", 0, {}};
	Station b2 = {"b2"," SUBANG", 0, {}};
	Station b3 = {"b3"," SUABNG", 0, {}};
	
	a1.linked_station[a1.station_count++] = &a2;

    a2.linked_station[a2.station_count++] = &a1;
    a2.linked_station[a2.station_count++] = &a3;
	a2.linked_station[a2.station_count++] = &b3;

    a3.linked_station[a3.station_count++] = &a2;

    b1.linked_station[b1.station_count++] = &b2;

    b2.linked_station[b2.station_count++] = &b1;
    b2.linked_station[b2.station_count++] = &b3;
	b2.linked_station[b2.station_count++] = &a2;

    b3.linked_station[b3.station_count++] = &b2;

	bfs(&a1, &a3);
}
//need to tink of resetting 
/*
note: vectors are used beause the amount of nodes travesed will grow dynamically
-stores adjecent lists dynamically
-store queue for bfs
-sotre visited status
*/