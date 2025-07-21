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
struct Station;

struct Connection
{
    Station* neighbor;
    int duration;
    double cost;
};


struct Station
{   
    string station_code;
	string station_name;
	string station_line;
	bool visited_status;
	int station_count;
	Connection *linked_station[9]; 
	Station *predecessor; //onlu purpose if for tracking to be printed later
	
	Station(string code,string name, string line)
		: station_code(code),station_name(name), station_line(line), visited_status(false), station_count(0), predecessor(nullptr) {
		for (int i = 0; i < 9; ++i)
			linked_station[i] = nullptr;
	}
};


struct Queue_Node
{
	Station *station;
	Queue_Node *next;
};

struct Queue
{
	Queue_Node *front=NULL;
	Queue_Node *back=NULL;

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
		return NULL;
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

	//delete temp;
	if (q.front == NULL)
       q.back = NULL;
       
    delete temp;
	return s;

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

void resetVisited(Station *stations[], int count)
{
	for (int i = 0; i < count; i++)
	{
		stations[i]->visited_status = 0 ;
		stations[i]->predecessor = NULL;
	}
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
		cout << "Visiting " << current -> station_code<< "("<<current -> station_name<<")" << endl;

			if (current == end_station)
			{
			    cout << "\nReached: " << end_station->station_code << " (" << end_station->station_name << ")" << endl;
                cout << "Route: ";

                int total_time = 0;
                double total_cost = 0.00;
                Station* path_node = end_station;
				
			while(path_node != NULL){
			    cout << path_node->station_code << "("<<path_node->station_name << ")" << endl;
                if (path_node->predecessor != NULL) {
                    // Find the connection that led here
                    for (int i = 0; i < path_node->predecessor->station_count; i++) {
                        if (path_node->predecessor->linked_station[i]->neighbor == path_node) {
                            total_time += path_node->predecessor->linked_station[i]->duration;
                            total_cost += path_node->predecessor->linked_station[i]->cost;
                            break;
                        }
                    }
                    cout << " <- ";
                }
                path_node = path_node->predecessor;
            }

            cout << "\nTotal Time: " << total_time << " minutes" << endl;
            cout << "Total Cost: RM" << total_cost << endl;
            return;
			}

		for (int i = 0; i < current -> station_count; i++)
		{
			Station *neighbor = current -> linked_station[i]->neighbor; //station neighbour are adjecent nodes
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

Station* findStation(Station* stations[], int count,string& code) {
    for (int i = 0; i < count; ++i) {
        if (stations[i]->station_code == code)
            return stations[i];
    }
    return nullptr;
}

int main()
{
	// Proper initialization with all struct members
	Station a1 = {"a1","MID VALLEY", "KELANA JAYA"};
	Station a2 = {"a2","KLCC", "KELANA JAYA"};
	Station a3 = {"a3","PASAR SENI", "KELANA JAYA" };

	Station b1 = {"b1","TRX", "SUBANG"};
	Station b2 = {"b2","PAVILLION", "SUBANG" };
	Station b3 = {"b3","SUNWAY PYRAMID", "SUBANG"};

	Station c1 = {"c1","SUNWAY VELOCITY", "PJ" };
	Station c2 = {"c2","LALAPORT", "PJ" };
	Station c3 = {"c3","OLD KLANG ROAD", "PJ" };

	// Build connections step by step
    
    // Line A: MID VALLEY <-> KLCC <-> PASAR SENI
    a1.linked_station[0] =new Connection {&a2, 3 , 0.30};    // MID VALLEY -> KLCC
    a1.station_count = 1;
    
    a2.linked_station[0] =new Connection {&a1, 3 , 0.30};    // KLCC -> MID VALLEY
    a2.linked_station[1] =new Connection {&a3, 4 , 0.40};    // KLCC -> PASAR SENI
    a2.station_count = 2;
    
    a3.linked_station[0] =new Connection{&a2, 4 , 0.40};    // PASAR SENI -> KLCC
    a3.station_count = 1;
    
    // Line B: TRX <-> PAVILLION <-> SUNWAY PYRAMID
    b1.linked_station[0] =new Connection {&b2, 2 , 0.20};    // TRX -> PAVILLION
    b1.station_count = 1;
    
    b2.linked_station[0] =new Connection {&b1, 2 , 0.20};    // PAVILLION -> TRX
    b2.linked_station[1] =new Connection {&b3, 5 ,0.60};    // PAVILLION -> SUNWAY PYRAMID
    b2.station_count = 2;
    
    b3.linked_station[0] =new Connection {&b2, 5 , 0.60};    // SUNWAY PYRAMID -> PAVILLION
    b3.station_count = 1;
    
    // Line C: SUNWAY VELOCITY <-> LALAPORT <-> OLD KLANG ROAD
    c1.linked_station[0] =new Connection {&c2, 4 , 0.50};    // SUNWAY VELOCITY -> LALAPORT
    c1.station_count = 1;
    
    c2.linked_station[0] =new Connection {&c1, 4 , 0.50};    // LALAPORT -> SUNWAY VELOCITY
    c2.linked_station[1] =new Connection {&c3, 6 , 0.90};    // LALAPORT -> OLD KLANG ROAD
    c2.station_count = 2;
    
    c3.linked_station[0] =new Connection {&c2, 6,0.90};    // OLD KLANG ROAD -> LALAPORT
    c3.station_count = 1;
    
    // Transfer connections between lines
    // KLCC (a2) <-> SUNWAY PYRAMID (b3)
    a2.linked_station[a2.station_count++] =new Connection {&b3, 5 , 1.00};
    b3.linked_station[b3.station_count++] =new Connection {&a2, 5 , 1.00};
    
    // PAVILLION (b2) <-> SUNWAY VELOCITY (c1)
    b2.linked_station[b2.station_count++] =new Connection {&c1, 4 , 0.80};
    c1.linked_station[c1.station_count++] =new Connection{&b2, 4 , 0.80};
    
    //Display Line
    cout << "Network connections:" << endl;
    Station* all_stations[] = {&a1,&a2,&a3,&b1,&b2,&b3,&c1,&c2,&c3};
    const int N = sizeof(all_stations)/sizeof(all_stations[0]);

    int choice;
    do {
        cout << "\n=== Metro Navigator ===\n"
             << "1. Show network connections\n"
             << "2. Find path between stations\n"
             << "3. Exit\n"
             << "Select an option (1-3): ";
        
         cin >> choice;

        switch (choice) {
            case 1: {
                cout << "\nNetwork connections:\n";
                for (int i = 0; i < N; ++i) {
                    cout << all_stations[i]->station_code
                         << " (" << all_stations[i]->station_name << ") -> ";
                    for (int j = 0; j < all_stations[i]->station_count; ++j) {
                        cout << all_stations[i]->linked_station[j]->neighbor->station_code;
                        if (j + 1 < all_stations[i]->station_count) cout << ", ";
                    }
                    cout << "\n";
                }
                break;
            }

            case 2: {
                string startCode, endCode;
                cout << "Enter start station code: ";
                cin >> startCode;
                cout << "Enter end station code: ";
                cin >> endCode;

                Station* start = findStation(all_stations, N, startCode);
                Station* end   = findStation(all_stations, N, endCode);

                if (!start || !end) {
                    cout << "One or both station codes not found. Try again.\n";
                } else {
                    resetVisited(all_stations, N);
                    cout << "\nSearching from "
                         << start->station_code << " to " << end->station_code << "...\n";
                    bfs(start, end);
                }
                break;
            }

            case 3:
                cout << "Goodbye!\n";
                break;

            default:
                cout << "Invalid option. Please choose 1, 2, or 3.\n";
        }
    } while (choice != 3);

    return 0;
}
//need to tink of resetting 
/*
note: vectors are used beause the amount of nodes travesed will grow dynamically
-stores adjecent lists dynamically
-store queue for bfs
-sotre visited status
*/