import functools
import random
from typing import List, Dict, Any, Callable, Union


# Problem 1
def breakdown(broken_string: str) -> List[str]:
    """Breaks the string into list of character
    doctests:
    >>> breakdown("abc")
    ['a', 'b', 'c']
    >>> breakdown("Hoo")
    ['H', 'o', 'o']
    """
    return [char for char in broken_string]


# Problem 2
def join(input_list: List[str]) -> str:
    """Joins a list of characters to form a string
   doctests:
    >>> join(['a','b','c'])
    'abc'
    >>> join(['1','2','!'])
    '12!'
    """
    s = ""
    for i in input_list:
        s += i
    return s


# Problem 3

def randomgenerator(n: int) -> List[int]:
    """This function generates a list of n random number
    >>> randomgenerator(7)
    [6, 6, 0, 4, 8, 7, 6]
    >>> randomgenerator(12)
    [6, 6, 0, 4, 8, 7, 6, 4, 7, 5, 9, 3]
    """
    randomlist = []
    random.seed(0)
    for i in range(n):
        j = random.randint(0, 10)
        randomlist.append(j)
    return randomlist


# Problem 4
def sort_desc(input_list: list) -> list:
    """Sorts a list of integers in ascending order
    >>> sort_desc([4, 3, 2, 1])
    [4, 3, 2, 1]
    >>> sort_desc([1, 7, 4, 6, 2])
    [7, 6, 4, 2, 1]
    """
    input_list.sort(reverse=True)
    return input_list


# Problem 5
def frequency(numberlist: List[int]) -> Dict:
    """This program gives the frequency of the number in list
    doctest :
    >>> frequency([1,1,3,2,3,2,3,2,2])
    {1: 2, 3: 3, 2: 4}
    >>> frequency([1,1,3,2,3,3,2,2])
    {1: 2, 3: 3, 2: 3}
    """
    freq = {}
    for item in numberlist:
        if item in freq:
            freq[item] += 1
        else:
            freq[item] = 1
    return freq


# 6
def unique(input_list: list) -> list:
    """Removes repeated elements from a set
    >>> unique([1,2,1,3,5,6,2])
    [1, 2, 3, 5, 6]
    >>> unique(['hello','ok','ok','!','1','2','3','2','!'])
    ['!', '1', '2', '3', 'hello', 'ok']
    """
    s = set()
    for i in input_list:
        s.add(i)
    return sorted(s)


# Problem 7
def first_repeating(input_list: list) -> str:
    """ Function to find first repeating element in list
    >>> first_repeating([1,2,3,1,2,3])
    1
    >>> first_repeating([1,2,3,4])
    'all unique'
    """
    s = set()
    for i in input_list:
        if i in s:
            return i
        else:
            s.add(i)
    return 'all unique'


# 8
def dict_sq_cube(n: int) -> dict:
    """Creates a dictionary that stores squares and cubes of all numbers from 0 to input number(inclusive)
    >>> dict_sq_cube(4)
    {0: (0, 0), 1: (1, 1), 2: (4, 8), 3: (9, 27), 4: (16, 64)}
    >>> dict_sq_cube(10)
    {0: (0, 0), 1: (1, 1), 2: (4, 8), 3: (9, 27), 4: (16, 64), 5: (25, 125), 6: (36, 216), 7: (49, 343), 8: (64, 512), 9: (81, 729), 10: (100, 1000)}
    """
    d = dict()
    for i in range(0, n + 1):
        d[i] = i ** 2, i ** 3
    return d


# Problem 9

def firstrepeating(ip1: list, ip2: list) -> list:
    """
    Checks which element repeats first time with the help of sets
    doctest:
    >>> print(firstrepeating(['a','b','c'],[1,'a',4]))
    [('a', 1), ('b', 'a'), ('c', 4)]
    >>> print(firstrepeating(['b', 'b', 'c'],[4,2,1]))
    [('b', 4), ('b', 2), ('c', 1)]
     """
    result = zip(ip1, ip2)
    return list(result)


# 10
def list_of_squares(n: int) -> list:
    """Returns a list of squares of each number between 0 and input num(inclusive)
    >>> list_of_squares(2)
    [0, 1, 4]
    >>> list_of_squares(5)
    [0, 1, 4, 9, 16, 25]
    """
    l = [i ** 2 for i in range(0, n + 1)]
    return l


# Problem 11
def generatemapping(n: int) -> Dict:
    """This is a function to generate mapping using list comprehension
    doctests:
    >>> generatemapping(5)
    {0: 0, 1: 1, 2: 4, 3: 9, 4: 16, 5: 25}

    >>> generatemapping(6)
    {0: 0, 1: 1, 2: 4, 3: 9, 4: 16, 5: 25, 6: 36}

    """
    myDict = {i: i ** 2 for i in range(n + 1)}
    return myDict


# 12


class ApplyLambda:
    """The class containing function 'apply', used to apply provided lambda function/predefined function to given
    value(s) The lambda/function should perform operation on individual elements only!
    >>> ApplyLambda([1,3,5,2,4]).apply(list_of_squares)
    [[0, 1], [0, 1, 4, 9], [0, 1, 4, 9, 16, 25], [0, 1, 4], [0, 1, 4, 9, 16]]
    >>> ApplyLambda([1,3,5,2,4]).apply(lambda x:x*2)
    [2, 6, 10, 4, 8]
    >>> ApplyLambda([1.1,2.4,3.0]).apply(list_of_squares)
    Some Error occurred!
    >>> lo = ApplyLambda(4)
    Input should be list!
    """
    ip = []

    def __init__(self, ip: list):
        try:
            if type(ip) != list:
                raise ValueError
            self.ip = ip
        except ValueError:
            print("Input should be list!")

    def apply(self, func):
        try:
            return list(map(func, self.ip.copy()))
        except TypeError:
            print("Some Error occurred!")


# Problem 13

def uppercase(Listofwords: List[str]) -> List[str]:
    """This function takes the list of words as input and Uppercase them
    doctests:
    >>> uppercase(['aa','bb','cd','e'])
    ['AA', 'BB', 'CD', 'E']
    >>> uppercase(['b','c'])
    ['B', 'C']
    """

    def upper(word):
        return word.upper()

    y = map(upper, Listofwords)
    return list(y)


# 14
def product_all(ip_list: list) -> float:
    """Returns the product of all numbers present in a list
    >>> product_all([-1,10,-121,45])
    54450
    >>> product_all([1.02,101,-1020,17.290])
    -1816840.116
    """
    return functools.reduce(lambda a, b: a * b, ip_list)


if __name__ == "__main__":
    import doctest
    doctest.testmod()
