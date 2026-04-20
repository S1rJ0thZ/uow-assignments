# Lab 5 
#
# File name: Lab_5.py

from abc import ABC,abstractmethod
from datetime import datetime

# Define Course class
class Course:
    def __init__(self, code:str, name:str, cost:float):
        """
        Construct a Course with code, name & cost
        """
        self.__code = code
        self.__name = name
        self.cost = cost

    
    # Get methods
    @property
    def code(self):
        return self.__code
    
    @property
    def name(self):
        return self.__name
    
    @property
    def cost(self):
        return self.__cost
    

    # Set methods
    @cost.setter
    def cost(self, cost):
        try:
            try:
                cost = float(cost)
            except:
                raise ValueError("Cost must be an integer")
            if cost < 0:
                raise ValueError("Cost must be a positive number")
            else:
                self.__cost = cost
        except ValueError as e:
            print(f"Error: {e}")


    # Display methods
    def __str__(self):
        return f"\tCourse: {self.__code}\tName: {self.__name}"
    



# Define TeaachingStaff class
class TeachingStaff:

    # class variable
    __year = str(datetime.now().year)
    __number_of_students = 0

    # Construct Teaching Staff
    def __init__(self, name:str, ratePerDay:float):
        self.__createStaffID(self)
        self.__name = name
        self.rate_per_day = ratePerDay

    
    # Get methods
    @property
    def staff_id(self):
        return self.__staff_id
    
    @property
    def name(self):
        return self.__name
    
    @property
    def rate_per_day(self):
        return self.__rate_per_day
    

    # Setter methods
    def __createStaffID(self):
        TeachingStaff.__number_of_students += 1
        self.__staff_id = f"{TeachingStaff.__year}{TeachingStaff.__number_of_students}"

    @rate_per_day.setter
    def rate_per_day(self, rate):
        try:
            try:
                rate = float(rate)
            except:
                raise ValueError("Rate per day must be an integer")
            if rate < 0:
                raise ValueError("Rate per day must be a positive number")
            else:
                self.__rate_per_day = rate
        except ValueError as e:
            print(f"Error: {e}")


    # Display method
    def __str__(self):
        return f"\tStaff ID: {self.__staff_id}\tName: {self.__name}"
    



# Define CourseOffering class
class CourseOffering:

    # class variables
    __sch_id = 1

    """
    Construct Course Offering
    """
    def __init__(self, course:Course, startDate, days, *instructors:TeachingStaff):
        """
        Add a course, startdate(dd/mm/yyyy), days & instructors
        """
        self.course = course
        self.__createScheduleID()
        self.start_date = startDate
        self.days = days
        self.__createInstructorList(instructors)

    
    # Getter methods
    @property 
    def course(self):
        return self.__course
    
    @property
    def schedule_id(self):
        return self.__schedule_id
    
    @property
    def start_date(self):
        return self.__start_date
    
    @property
    def days(self):
        return self.__days

    @property
    def instructors(self):
        return self.__instructors
    

    # Setter methods
    def __createScheduleID(self):
        self.__schedule_id = f"{self.__course.code}_{CourseOffering.__sch_id}"
        CourseOffering.__sch_id += 1

    @course.setter
    def course(self, course):
        try:
            if isinstance(course, Course):
                self.__course = course
            else:
                raise TypeError("Must be a Course Instance")
        except TypeError as e:
            print(f"Error: {e}")
    
    @start_date.setter
    def start_date(self, dateString):
        try:
            self.__start_date = datetime.strptime(dateString, "%d/%m/%Y")
        except ValueError as e:
            print(f"{e}: Start date must follow dd/mm/yyy format")

    @days.setter
    def days(self, days):
        try: 
            self.__days = int(days)
        except ValueError as e:
            print(f"{e}: Days must be an integer")

    def __createInstructorList(self, *instructors):
        self.__instructors = []
        for inst in instructors:
            try:
                if isinstance(inst, TeachingStaff):
                    self.__instructors.append(inst)
                else:
                    raise TypeError("Must be a TeachingStaff instance")
            except TypeError as e:
                print(f"Error: {e}")

    
    # class method
    @classmethod
    def change_sch_id(cls, new_id):
        try:
            try:
                new_id = int(new_id)
            except:
                raise ValueError("sch_id must be an integer")
            if new_id > 0:
                cls.__sch_id = new_id
            else:
                raise("sch_id must be positive and not zero")
        except ValueError as e:
            print(f"Error: {e}")

    
    # calculation methods
    def get_course_fee(self):
        instructorFees = [inst.rate_per_day for inst in self.__instructors]
        fees = sum(instructorFees) * self.__days + self.course.code
        return fees 

    
    # display method
    def __str__(self):
        display = f"Schedule ID: {self.__schedule_id:<14}Start Date: {datetime.strftime(self.__start_date, "%d/%m/%Y"):<13}\tDuration: {self.__days}\n"
        display += f"Course: {self.__course.code:<12}Name: {self.__course.name}\n"
        for inst in self.__instructors:
            display += f"StaffID: {inst.staff_id:<10}Name: {inst.name}\n"
        display += f"Basic Cost: ${self.get_course_fee():.2f}"




# Define Abstract Base Class Customer
class Customer(ABC):
    """
    Define Customer instance
    """
    def __init__(self, email, name):
        self.__email = email
        self.__name = name

        
            



    

    

