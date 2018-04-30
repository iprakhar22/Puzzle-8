/* Do the good stuff, Mr.Computer */

// Structure definition of a game state aka seed
struct seed 
{
	int mat[3][3];
	int cost;
	int moves;
	int seedhole[2];
};

/*
   * Implementation of a priority-queue using min binary heap and cost function used is hamming/mahattan distance.
   * PQ calling functions are made public while the heap inner functions are inaccessable.
*/
class PriorityQueue
{
private:
	// Min Heap array implementation
	vector<seed> heap;

public:
	// Initialize the heap with the current seed
	PriorityQueue()
	{
		//totalmoves = 0;

		int d = (!ManORHam)? manhattan(grid) : hamming(grid) ;

		heap.pb( newNode(grid, 0, hole) );

		maxsize = 1;

	}

	// De-allocate memory of all the used components
	~PriorityQueue()
	{
		//debug();
		heap.clear();
		heap.resize(0);
		maxsize = 0;
	}

private:
	// Return manhattan distance between the goal and the current seed
	int manhattan(int curr[3][3])
	{
		int pos1[9][2],pos2[9][2];
		int d = 0, i, j ;

		for(i=0;i<3;++i){
			for(j=0;j<3;++j){
				pos1[ goal[i][j] ][0] = i;
				pos2[ curr[i][j] ][0] = i;

				pos1[ goal[i][j] ][1] = j;
				pos2[ curr[i][j] ][1] = j;
			}
		}

		for(i=0;i<9;++i)
			d += abs(pos1[i][0] - pos2[i][0]) + abs(pos1[i][1]-pos2[i][1]);

		return d;
	}
	// Return hamming distance between the goal and the current seed
	int hamming(int curr[3][3])
	{
		int d = 0, i, j ;
		
		for(i=0;i<3;++i)
			for(j=0;j<3;++j){
				if(goal[i][j]!=curr[i][j])
					d++;
				//trace(curr[i][j],grid[i][j],goal[i][j],d);
			}

		return d;
	}

	seed newNode(int curr[][3], int m, int h[])
	{
		int d = (!ManORHam)? manhattan(curr) : hamming(curr) ;
		seed temp;
		for(int i=0;i<3;++i)
			for(int j=0;j<3;++j)
				temp.mat[i][j] = curr[i][j];
		temp.seedhole[0] = h[0];
		temp.seedhole[1] = h[1];
		temp.cost = d;
		temp.moves = m;

		return temp;
	}

	// Insert a new node in heap and adjust nodes
	void insert(int curr[3][3], int m)
	{
		int i, j, currhole[2];

		for(i=0;i<3;++i)
			for(j=0;j<3;++j)
				if(!curr[i][j])
					currhole[0]=i,currhole[1]=j;

		heap.pb( newNode(curr,m,currhole) );

		i = heap.size()-1;

		while(i && heap[(i-1)/2].cost + heap[(i-1)/2].moves > heap[i].cost + heap[i].moves)
		{
			swap(heap[(i-1)/2], heap[i]);
			i = (i-1)/2;
		}

		maxsize = max(maxsize, (int)heap.size());
	}

	// Adjust the nodes according to properties of the min heap
	void heapify( int i )
	{
		int l = 2*i+1;
		int r = 2*i+2;
		int smallest = i;

		if(l<heap.size() && heap[l].cost + heap[l].moves > heap[i].cost + heap[i].moves)
			smallest = l;
		if(r<heap.size() && heap[r].cost + heap[r].moves > heap[smallest].cost + heap[smallest].moves)
			smallest = r;

		if(smallest != i)
		{
			swap(heap[i], heap[smallest]);
			heapify(smallest);
		}

		return;
	}

	// Delete the top(min) element from the heap
	bool deleteTop()
	{
		if(!heap.size())
			return 0;

		if(heap.size()==1)
		{
			heap.erase(heap.begin());
			return true;
		}

		seed root = heap[heap.size()-1];
		heapify(0);
		heap.erase(prev(heap.end()));
		return true;
	}

	void debug()
	{
		cout<<"******************\n";
		for(int l=0;l<heap.size();++l)
		{
			for(int k=2;k>=0;--k){
			/*for(int k=0;k<3;++k){*/
				for(int p=0;p<3;++p)
					cout<<heap[l].mat[p][k]<<" ";
				cout<<"\n";
			}

			cout<<heap[l].moves<<" "<<heap[l].cost;
			cout<<"\n";
		}
		cout<<"******************\n";
	}

public:

	// Contains wrapper functions to match queue terminology

	// Maximum size of the PQ reached ever
	int maxsize;

	// Enqueue
	void push( int curr[3][3] , int m)
	{
		insert(curr,m);
		debug();
	}

	// Dequeue
	bool pop()
	{
		bool res = deleteTop();
		debug();
		return (res) ? true : false;
	}

	// Return top
	seed top()
	{
		if(heap.size()) return heap[0];
	}

	// Self-explanatory
	bool isEmpty()
	{
		return (!heap.size()) ? true : false ;
	}

};

void solve()
{
	PriorityQueue pq;

	int x[3][3] = 
	{
		{7,6,3},
		{8,5,2}, 
		{0,4,1}
	};
	pq.push(x,1);
	int x1[3][3] = 
	{
		{7,6,3},
		{8,5,2}, 
		{0,4,1}
	};
	pq.push(x1,311);

	int y[3][3] = 
	{
		{7,6,1},
		{8,5,2}, 
		{0,4,3}
	};
	pq.push(y,1312);

	//debug();

	pq.pop();
	pq.pop();
	pq.pop();
	cout<< pq.isEmpty()<<"\n";
	pq.pop();
	cout<< pq.isEmpty()<<"\n";

	//debug();

	seed xx = pq.top();

}
int iii = 0;
bool printflag = false;
int p[3][3][3] =
{
	{
	{7,6,3},
	{8,5,2}, 
	{0,4,1}
	},

	{
	{7,6,3},
	{8,5,2}, 
	{0,4,1}
	},

	{
	{7,6,1},
	{8,5,2}, 
	{0,4,3}
	}

};

void printt()
{
	int j,k;

	for(j=0;j<3;++j)
	{
		for(k=0;k<3;++k)
		{
			grid[j][k]=p[iii][j][k];
		}
	}
}