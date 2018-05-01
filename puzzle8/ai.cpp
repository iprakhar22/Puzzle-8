/* Do the good stuff, Mr.Computer */

/*
   * Implementation of a priority-queue using min binary heap and the cost function
   * used is hamming/mahattan distance.
   * PQ calling functions are made public while the heap inner functions are inaccessable.
*/
class PriorityQueue
{
private:
	// Min Heap array implementation
	vector<seed*> heap;

public:
	// Initialize the heap with the current seed
	PriorityQueue()
	{
		int d = (!ManORHam)? manhattan(grid) : hamming(grid) ;
		maxsize = 0;
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
				if(goal[i][j]!=curr[i][j] && curr[i][j])
					d++;
				//trace(curr[i][j],grid[i][j],goal[i][j],d);
			}

		return d;
	}

	seed* newNode(int curr[][3], int m, int h[], seed* p)
	{
		int d = (!ManORHam)? manhattan(curr) : hamming(curr) ;
		seed* temp = new seed;
		for(int i=0;i<3;++i)
			for(int j=0;j<3;++j)
				temp->mat[i][j] = curr[i][j];

		temp->seedhole[0] = h[0];
		temp->seedhole[1] = h[1];
		temp->cost = d;
		temp->moves = m;
		temp->parent = p;

		return temp;
	}

	// Insert a new node in heap and adjust nodes
	void insert(int curr[3][3], int m, seed* p)
	{
		int i, j, currhole[2];

		for(i=0;i<3;++i)
			for(j=0;j<3;++j)
				if(!curr[i][j])
					currhole[0]=i,currhole[1]=j;

		heap.pb( newNode(curr,m,currhole,p) );

		i = heap.size()-1;

		while(i && heap[(i-1)/2]->cost + heap[(i-1)/2]->moves > heap[i]->cost + heap[i]->moves)
		{
			swap(heap[(i-1)/2], heap[i]);
			i = (i-1)/2;
		}

		maxsize = max(maxsize, (int)heap.size());
		//debug();
	}

	// Adjust the nodes according to properties of the min heap
	void heapify( int i )
	{
		int l = 2*i+1;
		int r = 2*i+2;
		int smallest = i;

		if(l<heap.size() && heap[l]->cost + heap[l]->moves < heap[i]->cost + heap[i]->moves)
			smallest = l;
		if(r<heap.size() && heap[r]->cost + heap[r]->moves < heap[smallest]->cost + heap[smallest]->moves)
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

		heap[0]=heap[heap.size()-1];
		heapify(0);
		heap.erase(prev(heap.end()));
		return true;
	}

	void debug()
	{
		cout<<"----- DEBUG -----\n";
		for(int l=0;l<heap.size();++l)
		{
			for(int k=2;k>=0;--k){
			/*for(int k=0;k<3;++k){*/
				for(int p=0;p<3;++p)
					cout<<heap[l]->mat[p][k]<<" ";
				cout<<"\n";
			}

			cout<<heap[l]->moves<<" "<<heap[l]->cost;
			cout<<"\n";
		}
		cout<<"-----------------\n";
	}

public:

	/* Contains wrapper functions to match queue terminology */

	// Maximum size of the PQ reached ever
	int maxsize;

	// Enqueue
	void push( int curr[3][3] , int m, seed* p)
	{
		insert(curr,m,p);
		//cout<<"PUSHED\n"; debug();
	}

	// Dequeue
	bool pop()
	{
		bool res = deleteTop();
		//cout<<"POPPED\n"; debug();
		return (res) ? true : false;
	}

	// Return top
	seed* top()
	{
		if(heap.size()) return heap[0];
	}

	// Self-explanatory
	bool isEmpty()
	{
		return (!heap.size()) ? true : false ;
	}

};

// Returns true if the position is in the bounds
int swappable( int x, int y )
{
	return (x >= 0 && x < 3 && y >= 0 && y < 3);
}

// Direction vectors
int dx[] = { 1, 0, -1, 0 };
int dy[] = { 0, -1, 0, 1 };


// A* search algorithm or better-known as Best-First Search.
void AStar()
{
	int i, j, k;
	PriorityQueue pq;

	int totalmoves = 0;
	
	/*int test[3][3] =
	{
		{7,5,1},
		{8,6,2}, 
		{4,0,3}
	};

	memcpy(grid,test,sizeof grid);
	hole[0]=2; hole[1]=1;*/

	pq.push(grid,totalmoves,0);

	while(!pq.isEmpty())
	{
		seed* top = pq.top();
		seed* par = top->parent;
		pq.pop();

		//cerr<<"popped:\n"; for(j=2;j>=0;--j) { for(k=0;k<3;++k) cerr<<top->mat[k][j]<<" "; cerr<<"\n"; } trace(top->moves,top->cost); cerr<<"\n";

		// Final position is reached
		if(top->cost == 0)
		{
			final = top;
			pushGrids(final);
			printflag = true;
			cerr<<"Maximum elements in queue at any state = " << pq.maxsize;
			cerr<<"\nTotal moves used to solve the puzzle = " << totalmoves<<"\n";
			return;
		}

		totalmoves++;

		int topmat[3][3];
		memcpy(topmat,top->mat,sizeof topmat);

		// Enqueue all the seeds reacheable from the current seed
		for(i=0;i<4;++i)
		{
			int h[2];
			h[0] = top->seedhole[0];
			h[1] = top->seedhole[1];
			if(swappable(h[0]+dx[i],h[1]+dy[i]))
			{
				if(par && ( h[0]+dx[i]==par->seedhole[0] && h[1]+dy[i]==par->seedhole[1] ))
					continue;

				swap( topmat[h[0]][h[1]] , topmat[h[0]+dx[i]][h[1]+dy[i]] );

				//cerr<<"pushed:\n"; for(j=2;j>=0;--j) { for(k=0;k<3;++k) cerr<<topmat[k][j]<<" "; cerr<<"\n"; } cerr<<"\n";
				
				pq.push(topmat, totalmoves, top );
				swap( topmat[h[0]][h[1]] , topmat[h[0]+dx[i]][h[1]+dy[i]] );
			}
		}

	}

}