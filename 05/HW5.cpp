#include <iostream>
#include <vector>
#include <cmath>
#include <queue>
#include <list>

template<typename T>
class PriorityQueue {
private:
  std::vector<T> heap;

    static int leftChildIndex( int index )
    { return index * 2 + 1; }
    //
    static int rightChildIndex( int index )
    { return index * 2 + 2; }
    //
    static int parentIndex( int index )
    { return (index - 1) / 2; }

public:
    PriorityQueue(){}
    template<typename InputIt>
    PriorityQueue(InputIt first, InputIt last):heap(first, last){} // O(N)

  inline bool empty() const{
        return heap.empty();
    } // O(1)

  inline size_t size() const{
        return heap.size();
    } // O(1)


    void sift_up(int index){
        int par_index;
        while(index >0 && heap[(par_index = (parentIndex(index)))] < heap[index]  ){
            std::swap(heap[index], heap[par_index]);
            index = par_index;
}   }
  void sift_down(int index){
      while ( true ) {
          const int leftIndex = leftChildIndex( index ),
                  rightIndex = rightChildIndex( index );

          int nextIndex;
          if ( leftIndex >= size() )
              return;
          else if ( rightIndex == size() )
              nextIndex = leftIndex;
          else
              nextIndex = heap[ leftIndex ] > heap[ rightIndex ]
                          ? leftIndex
                          : rightIndex;

          if ( heap[ index ] < heap[ nextIndex ] ) {
              std::swap( heap[ index ], heap[ nextIndex ] );
              index = nextIndex;
          }
          else
              return;
      }
    }

  void push(const T &value){
        heap.push_back(value);
        sift_up(size()-1);
    } // O(log(N))

  void pop(){
        std::swap(heap[0], heap[size()-1]);
        heap.pop_back();
      sift_down(0);
    } // O(log(N))

  inline const T &top() const{
  return heap[0];
  } // O(1)

};


/// TASK 1
    int minStoneSum(std::vector<int>& piles, int k) {

        std::ios_base::sync_with_stdio(false);
        std::cin.tie(0);
        std::cout.tie(0);

        PriorityQueue<int> q;

        for(auto x: piles)
            q.push(x);

        while(k-->0){
            int temp = q.top();
            q.pop();

            if(temp%2 == 0)
                q.push((temp/2));
            else
                q.push((temp/2) +1);
        }

        int sum = 0;

        while(!q.empty()){
            sum += q.top();
            q.pop();
        }

        return sum;
    }


///   TASK 2

struct Point {
    int x{};
    int y{};

    double dist() const {
        return std::sqrt(x * x + y * y);
    }

    friend bool operator>(const Point &lhs, const Point &rhs) {
        return lhs.dist() > rhs.dist();
    }
    friend bool operator<(const Point &lhs, const Point &rhs) {
        return lhs.dist() < rhs.dist();
    }
};

void Solution2() {
    unsigned N,k;
    std::cin>>N>>k;
    std::vector<Point> vec(N);

    for(int i =0;i<N;++i)
        std::cin>>vec[i].x>>vec[i].y;

    PriorityQueue<Point> pqr;// In this Solution min heap is required for solution, but our realization does not have comparator template

    for(int i =0; i<k; ++i)
        pqr.push(vec[i]);

    for(int i =k; i<N; ++i) {
        if(vec[i] < pqr.top())
        {
            pqr.pop();
            pqr.push(vec[i]);
        }
    }

    for(int i=0 ; i<k ; i++){
        std::cout<<pqr.top().x<<" "<<pqr.top().y<<std::endl;
        pqr.pop();
    }
}


/// TASK 3

void Solution3(){
    int N, bricks, ladders;
    std::cin>>N;

    std::vector<int> heights(N);
    for(int i = 0; i< N; ++i)
        std::cin>>heights[i];
    std::cin>>bricks>>ladders;

    std::priority_queue<int, std::vector<int>, std::greater<int>> max_heap;//Same here, had to use min heap for Solution

    for (int i = 0; i < heights.size() - 1; ++i) {
        int diff = heights[i + 1] - heights[i];

        if (diff > 0) {
            max_heap.push(diff);

            if (max_heap.size() > ladders) {
                bricks -= max_heap.top();
                max_heap.pop();

                if (bricks < 0) {
                    std::cout<< i<<std::endl;
                    return;
                }
            }
        }
    }
    std::cout<<heights.size()-1<<std::endl;

}


/// Task 4

struct CompareNodes {
    bool operator()(const std::list<int>& a, const std::list<int>& b) const {
        return a.front() > b.front();
    }
};

std::list<int> mergeKLists(const std::vector<std::list<int>>& lists) {
    std::priority_queue<std::list<int>, std::vector<std::list<int>>, CompareNodes> minHeap;


    for (const auto& list : lists) {
        if (!list.empty()) {
            minHeap.push(list);
        }
    }

    // Dummy head for the result list
    std::list<int> result;

    while (!minHeap.empty()) {
        std::list<int> minList = minHeap.top();
        minHeap.pop();

        result.push_back(minList.front());
        minList.pop_front();

        if (!minList.empty()) {
            minHeap.push(minList);
        }
    }

    return result;
}

int main() {
//Solution2();
//Solution3();

}
