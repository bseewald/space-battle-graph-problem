struct node
{
    int vertex;
    struct node *next;
};

struct Graph
{
    int numVertex;
    int *visited;
    int *timeDiscovery;
    int *timeClose;
    struct node **adjLists;
};

struct node* createNode(int);
struct Graph* createGraph(int vertex);
void addEdge(struct Graph *graph, int src, int dest);
void printGraph(struct Graph *graph);