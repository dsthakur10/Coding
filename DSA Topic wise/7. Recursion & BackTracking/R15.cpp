
// Josephus problem


int josephus(int n, int k, vector<int>& circle, int pos)
{
    if(circle.size() == 1)
        return circle[0];

    //  int index = (pos+k-1)%circle.size();
    //  circle.erase(circle.begin() + index);
    //  pos = (index)%circle.size();

    //  return josephus(n, k, circle, pos);

    int index = (pos+k-1)%circle.size();
    circle.erase(circle.begin() + index);

    return josephus(n, k, circle, index);

}


int safePos(int n, int k) {

    vector<int> circle(n,0);

    for(int i=0; i<n; i++)
        circle[i] = i+1;

    return josephus(n, k, circle, 0);

}
