# Lab1_Circle.py

import math

class Point:

    def __init__(self, x, y):
        self.__x = x
        self.__y = y

    def getX(self):
        return self.__x
    
    def getY(self):
        return self.__y

class Circle:

    def __init__(self, center_x, center_y, radius):
        self.__center = Point(center_x, center_y)
        self.__radius = radius

    def area(self):
        area = math.pi * self.__radius **2
        return area

    def circumference(self):
        return 2 * math.pi * self.__radius
    
    # Assume angle is degree
    def point_coordinate(self, angle):
        phi = math.radians(angle)
        x = self.__radius * math.cos(phi) + self.__center.getX()
        y = self.__radius * math.sin(phi) + self.__center.getY()
        return Point(x, y)
    


def main():
    c1 = Circle(3,5,20)
    print(c1.area())
    print(c1.circumference())
    p = c1.point_coordinate(30)
    print(p.getX(), p.getY())
