from Lab1_Circle import Point
from Lab1_Circle import Circle

def main():
    center_x = float(input("Enter x: "))
    center_y = float(input("Enter y: "))
    radius = float(input("Enter radius: "))
    angle = float(input("Enter angle: "))\
    

    circle = Circle(center_x, center_y, radius)

    print(circle.area())
    print(circle.circumference())
    p = circle.point_coordinate(angle)
    print(p.getX(), p.getY())


if __name__ == "__main__":
    main()