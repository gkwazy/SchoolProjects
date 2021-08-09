import std.stdio;
import std.math;
import std.algorithm;
import std.range;

import common;

struct QuadTreeKNN
{
    alias P2 = Point!2;
    alias Bucket = P2[];
    Node root;

    this(P2[] points)
    {
        auto aabb = boundingBox(points);
        root = new Node(points, aabb);
    }

    P2[] rangeQuery(P2 p, float r)
    {
        P2[] ret;
        void recurse(Node n){
          if (n.isLeaf){
                foreach(point;n.bucket){
                    if (distance(point, p) < r)
                        ret ~= point;
                }
            }
            else {
                foreach(child;n.childeren){
                    if (distance(closest(child.aabb, p),p) <= r){
                        recurse(child);
                    }
                }
            }
        }
        recurse(root);
        return ret;
    }

    P2[] knnQuery(P2 p, int k){
        //can use makePriorityQueue to check for farthest point
        auto pq = makePriorityQueue(p);
        void recurse(Node n){
            if (n.isLeaf){
                foreach(point;n.bucket){
                    if (pq.length < k){
                        pq.insert(point);
                    }
                    else if (pq.front.distance(p) > point.distance(p)){
                        pq.popFront;
                        pq.insert(point);
                    }    
                }
            } 
            else{
                foreach(child;n.childeren){
                    if ( pq.length < k || distance(closest(child.aabb, p),p) < pq.front.distance(p)){
                        recurse(child);
                    }
                }
            }
        }
        recurse(root);
        return pq.release;
    }



    class Node
    {
        bool isLeaf;
        Node[4] childeren;
        AABB!2 aabb;
        Bucket bucket;

        this(P2[] points, AABB!2 oldBox)
        {
            if ( points.length < 64){
                isLeaf = true; 
                bucket = points.dup;
                aabb = oldBox;
            }else {
                AABB!2 NWBox, NEBox, SEBox, SWBox;

                isLeaf = false;

                P2 splitPoint = (oldBox.max + oldBox.min)/2;

                auto rightPoints = points.partitionByDimension!0(splitPoint[0]);
                auto leftPoints = points[0 .. $ - rightPoints.length];

                auto NE = rightPoints.partitionByDimension!1(splitPoint[1]);
                auto SE = rightPoints[0 .. $ - NE.length];

                auto NW = leftPoints.partitionByDimension!1(splitPoint[1]);
                auto SW = leftPoints[0 .. $ - NW.length];

                NEBox.min = splitPoint.dup;
                NEBox.max = oldBox.max.dup;

                SEBox.min = P2([splitPoint[0], oldBox.min[1]]);
                SEBox.max = P2([oldBox.max[0], splitPoint[1]]);

                NWBox.min = P2([oldBox.min[0], splitPoint[1]]);
                NWBox.max = P2([splitPoint[0], oldBox.max[1]]);

                SWBox.min = P2([oldBox.min[0], oldBox.min[1]]);
                SWBox.max = splitPoint.dup;

               

                childeren[0] = new Node(NW, NWBox);
                childeren[1] = new Node(NE, NEBox);
                childeren[2] = new Node(SW, SWBox);
                childeren[3] = new Node(SE, SEBox);
            }
            
            // aabb  = boundingBox(points);
            // // max.x - ((max.x - min.x)/2)
            // if (points.length > 64)
            // {
            //     auto xMed = aabb.max[0] - ((aabb.max[0] - aabb.min[0])/2);
            //     auto yMed = aabb.max[1] - ((aabb.max[1] - aabb.min[1])/2);
            //     auto rightHalf = points.partitionByDimension!0(xMed);
            //     auto leftHalf = points[0 .. $ - rightHalf.length];

            //     NEPoints = rightHalf.partitionByDimension!1(yMed);
            //     SEPoints = rightHalf[0 .. $ - NEPoints.length];

            //     NWPoints = leftHalf.partitionByDimension!1(yMed);
            //     SWPoints = leftHalf[0 .. $ - NWPoints.length];

            //     this.childeren[0] = new Node(NWPoints);
            //     this.childeren[1] = new Node(NEPoints);
            //     this.childeren[2] = new Node(SWPoints);
            //     this.childeren[3] = new Node(SEPoints);
            //     isLeaf = false;
            // }
            // else
            // {
            //     this.childeren[0] = null;
            //     this.childeren[1] = null;
            //     this.childeren[2] = null;
            //     this.childeren[3] = null;
            //     isLeaf = true;
            //     bucket = points;
            // }

        }
    }
}

unittest{
    auto qtnn = QuadTreeKNN([Point!2([.5, .5]), Point!2([1, 1]),
                   Point!2([0.75, 0.4]), Point!2([0.4, 0.74])]);
    
    writeln(qtnn);
    writeln("quadtree range query");
    foreach(p; qtnn.rangeQuery(Point!2([1,1]), .7)){
        writeln(p);
    }
    writeln("quadtree knn");
    foreach(p; qtnn.knnQuery(Point!2([1,1]), 3)){
        writeln(p);
    }
}
