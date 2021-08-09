import std.stdio;
import std.math;
import std.algorithm;
import std.range;

import common;

struct KdTreeKNN(size_t Dim)
{
    alias Bucket = Point!Dim[];
    Node!0 root;

    this(Point!Dim[] points){
        root = new Node!0(points);
    }


    Point!Dim[] rangeQuery(Point!Dim p, float r)
    {
        Point!Dim[] ret;
        void recurse(NodeType)(NodeType n)
        {
            if ( distance(n.splitPoint, p) < r){
                ret ~= n.splitPoint;
            }
            if (n.left !is null &&((p[n.thisLevel]-r) < n.splitPoint[n.thisLevel])) {
                recurse(n.left);
            }
            if (n.right !is null && ((p[n.thisLevel]+r) > n.splitPoint[n.thisLevel])) {
                recurse(n.right);
            }
        }
        recurse(root);
        return ret;
    }

    Point!Dim[] knnQuery(Point!Dim p, int k){
        auto pq = makePriorityQueue(p);

        void recurse(size_t splitDimension, size_t Dim)(Node!splitDimension n, AABB!Dim aabb){
            if(pq.length < k){
                pq.insert(n.splitPoint);
            } else if (pq.front.distance(p) > n.splitPoint.distance(p)){
                pq.popFront;
                pq.insert(n.splitPoint);
            }

            AABB!Dim leftAabb;
            AABB!Dim rightAabb;
            leftAabb.min = aabb.min.dup;
            rightAabb.min = aabb.min.dup;
            leftAabb.max = aabb.max.dup;
            rightAabb.max = aabb.max.dup;
            leftAabb.max[splitDimension] = n.splitPoint[splitDimension];
            rightAabb.min[splitDimension] = n.splitPoint[splitDimension];
            
            if (n.left !is null && (pq.length < k || distance(closest(leftAabb,p),p)< pq.front.distance(p))){
                recurse(n.left,leftAabb);
            }

            if (n.right !is null && (pq.length < k || distance(closest(rightAabb, p),p)< pq.front.distance(p))){
                recurse(n.right,rightAabb);
            }
        }

        AABB!Dim rootAABB = AABB!Dim();
        rootAABB.min[] = -float.infinity;
        rootAABB.max[] = float.infinity;
        recurse(root,rootAABB);
        return pq.release;

        // AABB!0 aabb;
        // aabb.max[] = float.infinity;
        // aabb.min[] = -float.infinity;
        // return root.knn(p,k,aabb);
    }

    class Node(size_t splitDimension)
    {
        Point!Dim splitPoint;
        AABB!thisLevel aabb;
        //if this is an x node, the next level is "y"
        //if this is a y node, the next level is "z", etc
        enum thisLevel = splitDimension; //this lets you refer to a node's split level with theNode.thisLevel
        enum nextLevel = (splitDimension + 1) % Dim;
        Node!nextLevel left, right;//child nodes split by the next level

        this(Point!Dim[] points)
        {
                // find the median based on the split demension x,y,z,...
                points.medianByDimension!thisLevel;
                int medianIndex = cast(int)(points.length/2);
                splitPoint = points[medianIndex];

                Point!Dim[] leftPoints = points[0 .. medianIndex];
                Point!Dim[] rightPoints = points[medianIndex+1 .. $];

                // smaller on left bigger on right
                // store median here
            
                if (leftPoints.length > 0){
                    left = new Node!nextLevel(leftPoints);
                }
                if (rightPoints.length > 0){
                    right = new Node!nextLevel(rightPoints);
                }
        }
    }

}


unittest{
    auto kdnn = KdTreeKNN!2([Point!2([.5, .5]), Point!2([1, 1]),
                    Point!2([0.75, 0.4]), Point!2([0.4, 0.74])]);
    
    writeln(kdnn);
    writeln("kdtree range query");
    foreach(p; kdnn.rangeQuery(Point!2([1,1]), .7)){
        writeln(p);
    }
    writeln("kdtree knn");
    foreach(p; kdnn.knnQuery(Point!2([1,1]), 3)){
        writeln(p);
    }
}