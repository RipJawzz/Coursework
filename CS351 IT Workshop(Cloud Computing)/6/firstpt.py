from typing import Callable, List
import math
#DO NOT MAKE UNNECESSARY CHANGES
class DistanceFuncs:
    def calc_distance(self, point_a: List[float], point_b: List[float], dist_func: Callable,/)->float:
        """ Calculates distance between two points using the passed dist_func """
        return dist_func(point_a, point_b)
    @staticmethod
    def euclidean(point_a: List[float], point_b: List[float],/)->float:
        """
        Calculates Euclidean Distance between two points Example:
        >>> DistanceFuncs.euclidean([1,1],[1,1])
        0.0
        """
        return math.dist(point_a, point_b)
    @staticmethod
    def manhattan_distance(point_a: List[float], point_b: List[float],/): 
        """Compute the manhattan_distance between two points""" 
        return sum(abs(point_a[i]-point_b[i]) for i in range(len(point_a)))
    @staticmethod
    def jaccard_distance(point_a: List[float], point_b: List[float],/): 
        """Compute the jaccard_distance between two points""" 
        intersection=len(set(point_a).intersection(point_b))
        return 1.0-(intersection/(len(point_b)+len(point_b)-intersection))
def main():
    """Demonstrate the usage of DistanceFuncs """
    point_a=[1,2,3,4,5]
    point_b=[3,4,5,6,7]
    ob=DistanceFuncs()
    print('Jaccard func',ob.calc_distance(point_a,point_b,DistanceFuncs.jaccard_distance))
    print('Manhattan func',ob.calc_distance(point_a,point_b,DistanceFuncs.manhattan_distance))
    print('Eucledian func',ob.calc_distance(point_a,point_b,DistanceFuncs.euclidean))

main()
if __name__ ==" main ":
    main()