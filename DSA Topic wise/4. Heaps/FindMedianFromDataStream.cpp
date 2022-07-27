/*

The median is the middle value in an ordered integer list. If the size of the list is even,
there is no middle value and the median is the mean of the two middle values.

For example, for arr = [2,3,4], the median is 3.
For example, for arr = [2,3], the median is (2 + 3) / 2 = 2.5.
Implement the MedianFinder class:

    - MedianFinder() initializes the MedianFinder object.
    - void addNum(int num) adds the integer num from the data stream to the data structure.
    - double findMedian() returns the median of all elements so far.

Example 1:

Input:
["MedianFinder", "addNum", "addNum", "findMedian", "addNum", "findMedian"]
[[], [1], [2], [], [3], []]
Output:
[null, null, null, 1.5, null, 2.0]

Explanation
MedianFinder medianFinder = new MedianFinder();
medianFinder.addNum(1);    // arr = [1]
medianFinder.addNum(2);    // arr = [1, 2]
medianFinder.findMedian(); // return 1.5 (i.e., (1 + 2) / 2)
medianFinder.addNum(3);    // arr[1, 2, 3]
medianFinder.findMedian(); // return 2.0

*/




/*

Idea is to maintain 2 heaps --> minHeap & maxHeap

maxHeap --> stores numbers from smallest --> median-1 / median
minHeap --> stores numbers from median / median+1 --> largest

The concept behind this strategy is:
In case #elements = even --> to get average of MaxHeap's top & MinHeap's top to get median of present array.
In case #elements = odd --> Get the top of whichever heap's size is greater at that moment.

Always maintain equal #elements in both the heaps to get the median correctly.

Adding number from stream:
    --> If minHeap is empty --> store number in maxHeap
    --> If maxHeap is empty --> store number in minHeap
    --> If both are non-empty --> Store number on the calculation basis (looking at top() of both heaps)

Getting median of current array:
    --> Before getting median, make both the heaps of equal size (even #elements) or size diff = 1 (odd #elements)
    --> If #elements = even, get the avg of tops()
    --> If #elements = odd, get the top() of element which is greater in size.

*/


class MedianFinder {
public:

    priority_queue<int> maxPQ;
    priority_queue<int, vector<int>, greater<int>> minPQ;

    MedianFinder() {


    }

    // Initially store all the elements in MaxHeap
    void addNum(int num) {

        if(minPQ.empty())
            maxPQ.push(num);

        else if(maxPQ.empty())
            minPQ.push(num);

        else
        {
            if(num <= maxPQ.top())      // would fit in the range 0 -- median
                maxPQ.push(num);

            else                        // would fit in range median+1 -- N-1
                minPQ.push(num);
        }
    }

    double findMedian() {

        int x = minPQ.size();
        int y = maxPQ.size();
        double median;

        if(x < y)
        {
            // even #elements in array
            if((x + y)% 2 == 0)
            {
                // make their sizes equal.
                while(minPQ.size() < maxPQ.size())
                {
                    minPQ.push(maxPQ.top());
                    maxPQ.pop();
                }

                median = (minPQ.top() + maxPQ.top())/2.0;
            }

            // odd #elements in array
            else
            {
                // let the size-diff = 1
                while(minPQ.size() + 1 < maxPQ.size())
                {
                    minPQ.push(maxPQ.top());
                    maxPQ.pop();
                }

                median = maxPQ.top();
            }

        }

        else if(x > y)
        {
            if((x + y)% 2 == 0)
            {
                while(maxPQ.size() < minPQ.size())
                {
                    maxPQ.push(minPQ.top());
                    minPQ.pop();
                }

                median = (minPQ.top() + maxPQ.top())/2.0;
            }

            else
            {
                while(maxPQ.size() + 1 < minPQ.size())
                {
                    maxPQ.push(minPQ.top());
                    minPQ.pop();
                }

                median = minPQ.top();
            }
        }

        else
            median = (minPQ.top() + maxPQ.top())/2.0;

        return median;
    }
};

/**
 * Your MedianFinder object will be instantiated and called as such:
 * MedianFinder* obj = new MedianFinder();
 * obj->addNum(num);
 * double param_2 = obj->findMedian();
 */
