# Lab 3 
#
# File name: Lab_3.py

from datetime import datetime
from abc import ABC, abstractmethod

class Address:
    def __init__(self, unitBlock:str, street:str, city:str, state:str, postCode:str, country:str):
        self.__unit_block = unitBlock
        self.__street = street
        self.__cty = city
        self.__state = state
        self.__postcode = postCode
        self.__country = country

    # Getter Methods
    @property
    def unitBlock(self):
        return self.__unit_block

    @property
    def street(self):
        return self.__street
    
    @property
    def cty(self):
        return self.__cty
    
    @property
    def state(self):
        return self.__state
    
    @property
    def postcode(self):
        return self.__postcode
    
    @property
    def country(self):
        return self.__country
    
    
    # display
    def __str__(self):
        return f"{self.__unit_block}, {self.__street}, {self.__cty}, {self.__state},\n\t{self.__postcode}, {self.__country}"




class Employee(ABC):

    # class variable
    __number_of_empolyees = 0
    __date_string_format = "%d/%m/%Y"

    "Create Employee data"
    def __init__(self, name:str, dob:datetime, dateHired:datetime, address:Address, mobileNo:str):
        """
        Employee name, dob, date hired, address and mobile number
        date format: dd/mm/yyyy
        """
        self.__setEmplyID()
        self.__name = name  # Directly assign
        self.dob = dob      # Use Property
        self.dateHired = dateHired  # Use Property
        self.address = address      # Use Property
        self.mobileNo = mobileNo    # Use Property



    # Private methods
    def __setEmplyID(self):
        Employee.__number_of_empolyees += 1
        self.__emplyID = "2024" + str(Employee.__number_of_empolyees).zfill(4)


    # Getter Methods
    @property
    def emplyID(self):
        return self.__emplyID
    
    @property
    def name(self):
        return self.__name
    
    @property
    def dob(self):
        return self.__dob

    @property
    def dateHired(self):
        return self.__date_hired

    @property
    def address(self):
        address = str(self.__address)
        return address

    @property
    def mobileNo(self):
        return self.__mobile_no

    
    def dobStr(self):
        date = datetime.strftime(self.__date_hired, Employee.__date_string_format)
        return date

    def dateHiredStr(self):
        date = datetime.strftime(self.__date_hired, Employee.__date_string_format)
        return date


    # Setter Methods
    @dob.setter
    def dob(self, dateString):
        try:
            try:
                date = datetime.strptime(dateString, Employee.__date_string_format)
            except ValueError:
                raise ValueError("Input must be in the specified format!")
            
            if datetime.now() < date:
                raise ValueError("Invalid birth date")
            else:
                self.__dob = date

        except ValueError as e:
            print(f"Error: {e}")

    @dateHired.setter
    def dateHired(self, dateString):
        try:
            try:
                date = datetime.strptime(dateString, Employee.__date_string_format)
            except ValueError:
                raise ValueError("Input must be in the required format")
            
            # 2 ways:
            # 1) Use dateutil.relativedelta 
            # 2) calculate manually using attributes
            if date.year - self.__dob.year - ((date.month, date.day) < (self.__dob.month, self.__dob.day)) < 14:
                raise ValueError("Must be at least 14 years old")
            else:
                self.__date_hired = date

        except ValueError as e:
            print(f"Error: {e}")

    @address.setter
    def address(self, address):
        try:
            #if type(address) == Address:
            if isinstance(address, Address):
                self.__address = address
            else:
                raise TypeError("Not an Address instance")
        except TypeError as e:
            print(f"Error: {e}")

    @mobileNo.setter
    def mobileNo(self, mobile):
        try:
            if mobile.isdigit():
                self.__mobile_no = mobile
            else:
                raise ValueError("Invalid contact number")
        except ValueError as e:
            print(f"Error: {e}")
        except TypeError as e:
            print(f"Error: {e}")


    # Abstract Methods
    @abstractmethod
    def getAnnualLeave(self):
        pass


    # Calculation methods
    def getAge(self):
        today = datetime.now()
        age = today.year - self.__dob.year - ((today.month, today.day) < (self.__dob.month, self.__dob.day))
        return age

    def getCPFContriution(self):
        """Return cpf contirbution in %"""
        if self.getAge() > 60:
            return 5.0
        elif self.getAge() > 50:
            return 12.0
        else:
            return 20.0


    # Display Method
    def __str__(self):
        display = "Employee Details:\n\t"
        display += f"Employee ID: {self.__emplyID}\n\t"
        display += f"Name: {self.__name}\n\t"
        display += f"DOB: {self.__dob}\n\t"
        display += f"Date of hire: {self.__date_hired}\n\t"
        display += f"Address: {str(self.__address)}\n\t"
        display += f"Contact No: {self.__mobile_no}\n\t"
        display += f"CPF Contribution: {self.getCPFContriution()}%\n\t"
        display += f"Annual Leave: {self.getAnnualLeave()}\n\t"
        return display




# Subclasses of Employee
class ProfessionalEmp(Employee):
    """
    Construct a Professional Employee
    """
    def __init__(self, name:str, dob:datetime, dateHired:datetime, address:Address, mobileNo:str, position:str, workingDays: int):
        """
        Professional employee's details and working days

        Details: name, dob, date hired, address and mobile number
        date format: dd/mm/yyyy
        """
        super().__init__(name, dob, dateHired, address, mobileNo)
        self.__prof_position = position
        self.workingDays = workingDays


    # Getter methods
    @property
    def profPosition(self):
        return self.__prof_position

    @property
    def workingDays(self):
        return self.__working_days

    
    # Setter methods
    @profPosition.setter
    def profPosition(self, position):
        self.__prof_position = position

    @workingDays.setter
    def workingDays(self, workingDays):
        try:
            if isinstance(workingDays, int):
                self.__working_days = workingDays
            else:
                raise TypeError("Working days must be an integer")
        except TypeError as e:
            print(f"Error: {e}")


    # calculation methods
    def noOfYearsEmployed(self):
        today = datetime.now()
        years = today.year - self.dateHired.year - ((today.month, today.day)<(self.dateHired.month, self.dateHired.day))
        return years


    # abstract method
    def getAnnualLeave(self):
        emplymentYears = self.noOfYearsEmployed()
        if emplymentYears < 2:
            return 15
        elif emplymentYears < 4:
            return 18
        else:
            return 21


    # display method
    def __str__(self):
        super().__str__()
        display = f"Professional Position: {self.__prof_position}\n\t"
        display += f"Working days: {self.__working_days}\n\t"
        return display


# Academic Employee Subclass
class AcademicEmp(Employee):
    """
    Construct an Academic Employee
    """
    def __init__(self, name:str, dob:datetime, dateHired:datetime, address:Address, mobileNo:str, academicPosition:str, *args:str):
        """
        Academic employee's details and research area

        Employee name, dob, date hired, address and mobile number
        date format: dd/mm/yyyy
        """
        super().__init__(name, dob, dateHired, address, mobileNo)
        self.__academic_position = academicPosition
        self.__teaching_subject = []    # list of subject taught can be added later
        self.__createResearchAreaList(args)


    # private methods
    def __createResearchAreaList(self, *args):
        self.__research_area = [arg for arg in args]


    # get method
    @property
    def academicPosition(self):
        return self.__academic_position

    @property
    def teachingSubject(self):
        return self.__teaching_subject

    @property
    def researchArea(self):
        return self.__research_area
    
    def displayTeachingSubject(self):
        for subject in self.__teaching_subject:
            print(f"{subject},", end=" ")

    def displayResearchArea(self):
        for rArea in self.__research_area:
            print(f"{rArea},", end=" ")

    # Abstract method
    def getAnnualLeave(self):
        return 14


    # add methods
    def addTeachingSubject(self, newSubject):
        try:
            for subject in self.__teaching_subject:
                if subject == newSubject:
                    raise ValueError("Duplicate Subject")
            self.__teaching_subject.append(newSubject)
        
        except ValueError as e:
            print(f"Error: {e}")

    def addResearchArea(self, newRArea):
        try:
            for rArea in self.__research_area:
                if rArea == newRArea:
                    raise ValueError("Duplicate research area")
            self.__teaching_subject.append(newRArea)
        
        except ValueError as e:
            print(f"Error: {e}")


    # remove methods
    def removeTeachingSubject(self, subject):
        try:
            if subject in self.__teaching_subject:
                self.__teaching_subject.remove(subject)
            else:
                raise ValueError("Subject not found")
        except ValueError as e:
            print(f"Error: {e}")

    def removeResearchArea(self, rArea):
        try:
            if rArea in self.__research_area:
                self.__teaching_subject.remove(rArea)
            else:
                raise ValueError("Research Area not found")
        except ValueError as e:
            print(f"Error: {e}")


    # display method
    def __str__(self):
        super().__str__()
        display = f"Academic Position: {self.__academic_position}\n\t"
        display += f"Teaching Subject: {self.displayTeachingSubject()}\n\t"
        display += f"Research Area: {self.displayResearchArea()}\n\t"
        return display




# School class
class School:
    """
    Construct School class
    """
    def __init__(self, name:str):
        "School name and List of Employees"
        self.__name = name
        self.__employees = []
    

    # get methods
    @property
    def name(self):
        return self.__name

    @property
    def employees(self):
        return self.__employees


    # add/remove employees
    def addEmployee(self, employee):
        try:
            if isinstance(employee, Employee):
                for emp in self.__employees:
                    if emp.emplyID == employee.emplyID:
                        raise ValueError("Employee already exists!")
                self.__employees.append(employee)
                return True
            else:
                raise TypeError("Must be an employee")
        except TypeError as e:
            print(f"Error: {e}")
            return False
        except ValueError as e:
            print(f"Error: {e}")
            return False

    def removeEmployee(self, employeeID):
        try:
            emply = self.findEmply(employeeID)
            if emply:
                self.__employees.remove(emply)
                return True
            else:
                raise ValueError("Employee does not exist")
        except ValueError as e:
            print(f"Error: {e}")
            return False


    # find method
    def findEmply(self, employeeID):
        try:
            if isinstance(employeeID, str):
                for emp in self.__employees:
                    if emp.emplyID == employeeID:
                        return emp
                return None
            else:
                raise TypeError("Employee ID must be a string")
        except TypeError as e:
            print(f"Error: {e}")


    # search method
    def searchAcademicEmployees(self, subject):
        acadEmplyList = []
        for emp in self.__employees:
            if isinstance(emp, AcademicEmp):
                acadEmplyList.append(emp)
        try:
            if isinstance(subject, str):
                foundEmplys = []
                for emp in acadEmplyList:
                    if subject in emp.teachingSubject:
                        foundEmplys.append(emp)
                return foundEmplys
            else:
                raise TypeError("Subject must be a string")
        except TypeError as e:
            print(f"Error: {e}")
            
    
#--------------------------------------------------------------------------------------

# functions for test
def test():
    # Test Address
    address1 = Address("Blk 50 #03-01", "Acacia Rd", "Batangas", "San Antonio", "746291", "Phillipines")
    print(address1)

    # create more addresses
    address2 = Address("Blk 50 #03-01", "Acacia Rd", "Batangas", "San Antonio", "746291", "Phillipines")
    address3 = Address("Blk 38 #03-01", "Elorde Street", "Manila", "Varga", "71726", "Phillipines")
    address4 = Address("Blk 50 #03-01", "Acacia Rd", "Batangas", "San Antonio", "746291", "Phillipines")
    address5 = Address("Blk 50 #03-01", "Acacia Rd", "Batangas", "San Antonio", "746291", "Phillipines")
    address6 = Address("Blk 50 #03-01", "Acacia Rd", "Batangas", "San Antonio", "746291", "Phillipines")

    # Test Employee
    employee1 = ProfessionalEmp("Kyle", "01/10/1986", "25/06/2015", address1, "99129910", "Operations Manager", 6)
    employee2 = ProfessionalEmp("James", "01/10/1979", "25/06/2005", address2, "27461191", "IT Manager", 6)
    employee3 = ProfessionalEmp("Kyle", "01/10/1986", "25/06/2015", address3, "99129910", "Operations Manager", 6)
    employee4 = AcademicEmp("Clarisse", "22/01/1990", "25/07/2024", address4, "27771021", "Professor", "Marketting", "Mass communications")
    employee5 = AcademicEmp("Yung blud", "23/12/2010", "14/11/2024", address5, "91749120", "Teaching Assistant", "Engineering", "Math")
    employee6 = AcademicEmp("Jane", "31/10/1990", "25/05/2024", address6, "27771021", "Professor", "Marketting", "Mass communications")


    # Test School

def main():
    test()

if __name__ == "__main__":
    main()





