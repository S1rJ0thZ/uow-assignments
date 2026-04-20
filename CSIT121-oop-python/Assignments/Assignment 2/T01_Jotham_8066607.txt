# File name: T01_Jotham_8066607.txt

# import abstract base class module
from abc import ABC, abstractmethod
from datetime import datetime

class Student:
    """Class Variable"""
    __number_of_students = 0
    __enrolment_year = 2024

    """Construct Student"""
    def __init__(self, name: str):
        """Student has a name and ID number"""
        self.__name = name
        self.__createStudentID()
        

    """get methods"""
    @property
    def name(self):
        return self.__name

    @property
    def id(self):
        return self.__id


    """Private methods"""
    def __createStudentID(self):
        Student.__number_of_students += 1
        self.__id = str(Student.__enrolment_year * 10000 + Student.__number_of_students)


    """Display method"""
    def __str__(self):
        return f"Student Details\n\tName: {self.__name}\n\tID: {self.__id}\n"
    



class Course:
    """Construct Course"""
    def __init__(self, code: str, name: str, credits: int):
        """Course object contains a code, name and number of credits for a student"""
        self.__code = code
        self.__name = name 
        self.credits = credits
    
    """get methods"""
    @property
    def code(self):
        return self.__code

    @property
    def name(self):
        return self.__name
    
    @property
    def credits(self):
        return self.__credits


    """set methods"""
    @credits.setter
    def credits(self, noOfCredits):
        try:
            try:
                self.__credits = int(noOfCredits)
            except:
                raise ValueError("Credits must be an integer")
            if self.__credits <= 0:
                raise ValueError("Credits must be more than zero")            # Define Credit Exception
        except ValueError as e:
            print(f"Error: {e}")
            

    """Display methods"""
    def __str__(self):
        return f"Course details\n\tCode/Name: {self.__code} / {self.__name}\n\tCredits: {self.__credits}\n"


#===========================================================================================================


class Result(ABC):
    """Abstract Base Class"""
    def __init__(self, student, course):
        self.setStudent(student)
        self.setCourse(course)


    """get student methods"""
    def student(self):
        return self.__student

    def studentName(self):
        return self.__student.name

    def studentID(self):
        return self.__student.id


    """get course methods"""
    def course(self):
        return self.__course

    def courseName(self):
        return self.__course.name

    def courseCode(self):
        return self.__course.code

    def courseCredits(self):
        return self.__course.credits


    """set methods"""
    def setStudent(self, student):
        if isinstance(student, Student):
            self.__student = student
        else:
            self.__student = None
            print("Must be a student")

    def setCourse(self, course):
        if isinstance(course, Course):
            self.__course = course
        else:
            self.__course = None
            print("Must be a student")


    """set methods"""
    @abstractmethod
    def setScore(self):
        pass


    """Calculation method"""
    def getGrade(self):
        score = self.getOverallScore()
        if score >= 95:
            return "A"
        elif score >= 90:
            return "A-"
        elif score >= 85:
            return "B+"
        elif score >= 80:
            return "B"
        elif score >= 75:
            return "B-"
        elif score >= 70:
            return "C+"
        elif score >= 65:
            return "C"
        elif score >= 60:
            return "C-"
        elif score >= 55:
            return "D+"
        elif score >= 50:
            return "D"
        elif score >= 45:
            return "D-"
        else:
            return "F"
    
    
    def getGradePoints(self):
        grade = self.getGrade()
        if grade == 'A':
            return 4.0
        elif grade == 'A-':
            return 3.7
        elif grade == 'B+':
            return 3.3
        elif grade == 'B':
            return 3.0
        elif grade == 'B-':
            return 2.7
        elif grade == 'C+':
            return 2.3
        elif grade == 'C':
            return 2.0
        elif grade == 'C-':
            return 1.7
        elif grade == 'D+':
            return 1.3
        elif grade == 'D':
            return 1.0
        elif grade == 'D-':
            return 0.7
        else:
            return 0.0


    @abstractmethod
    def getOverallScore(self):
        pass

    """display method"""
    def __str__(self):
        # To access attributes directly use mangled name 'self._parentClassName__attribute' for private attributes
        # child class should not directly access parent class attributes
        display = f"Name: {self.studentName()}\n\t"
        display += f"ID: {self.studentID()}\n\t"
        display += f"Course Code: {self.courseCode()}\n\t"
        return display

    # Have a method to match all the results objects with same student ID
    @classmethod      
    def getGPA(cls, resultList):
        totalPoints = 0
        totalCredits = 0
        for result in resultList:
            totalPoints += result.getGradePoints() * result.courseCredits()
            totalCredits += result.courseCredits()

        gpa = totalPoints / totalCredits
        return round(gpa, 2)
        

        

class PracticalResult(Result):

    """Construct PracticalResult"""
    def __init__(self, student:Student, course:Course, s1:float, s2:float, s3:float):
        """Practical/Coursework results"""
        super().__init__(student, course)
        self.setScore(s1,s2,s3)


    """set methods"""
    def setScore(self, *args):
        try:
            self.__practical_scores = []
            for arg in args:
                try:
                    arg = float(arg)
                except:
                    raise ValueError("Score must be a number")
                if 0 <= arg <= 100:
                    self.__practical_scores.append(arg)
                else:
                    raise ValueError("Score must be in a range of 0 to 100")
        except ValueError as e:
            print(f"Error: {e}")


    """calculation methods"""
    def getOverallScore(self):
        """Get overall score"""
        sum = 0
        for score in self.__practical_scores:
            sum += score
        average = sum/len(self.__practical_scores)
        return round(average, 2)


    """display methods"""
    def __str__(self):
        display = "Practical Results\n\t"
        display += super().__str__()
        for i in range(len(self.__practical_scores)):
            display += f"Practical {i+1}: {self.__practical_scores[i]}\n\t"
        display += f"Overall: {self.getOverallScore()}\n\t"
        display += f"Grade: {self.getGrade()}\n\t"
        return display




class CourseResult(Result):

    """Construct CourseResult"""
    def __init__(self, student:Student, course:Course, courseWorkScore:float, examScore:float):
        """Consists of Course work and Exam results"""
        super().__init__(student, course)
        self.__cw_score = self.setScore(courseWorkScore)
        self.__exam_score = self.setScore(examScore)

    '''
    def __setCourseWork(self, practical):
        if isinstance(practical, PracticalResult):
            if self.studentID() == practical.studentID() and self.courseCode() == practical.courseCode():
                return practical
            #else:
                #raise ResultException("Result does not belong to Student and Course")              # Define Exception
        else:
            raise ValueError("This object does not belong to the PracticalResult class")
    '''
        

    """set methods"""
    def setScore(self, score):
        try:
            try:
                score = float(score)
            except:
                raise ValueError("Score must be a number")

            if 0 <= score <= 100:
                return score
            else:
                raise ValueError("Score must be in a range of 0 to 100")   
        except ValueError as e:
            print(f"Error: {e}")


    """calculation methods"""
    def getOverallScore(self):
        return (self.__cw_score * 0.3) + (self.__exam_score * 0.7)

    
    """display method"""
    def __str__(self):
        display = "Course Results\n\t"
        display += super().__str__()
        display += f"Course work: {self.__cw_score}\n\t"
        display += f"Exam Score: {self.__exam_score}\n\t"
        display += f"Overall: {self.getOverallScore()}\n\t"
        display += f"Grade: {self.getGrade()}\n\t"
        return display


# AcadTerm class
# 1 student can have 2 courses --> 
# Results list can have duplicate student if course different
# Condition: student.name in list and course.code in list

class AcadTerm:
    
    """Construct AcadTerm"""
    def __init__(self, term:str, startDate:str, endDate:str):
        """Create Academic Term
        with the Start and End Date\n
        Date objects are in the format dd/mm/yyyy
        """
        self.__term = term
        self.__start_date = self.setDate(startDate)
        self.__end_date = self.setDate(endDate)
        self.__studentIDList = []
        self.__courseCodeList = []
        self.__resultList = []

    """get methods"""
    def getStartDate(self):
        return datetime.strftime(self.__start_date, "%d %b %Y")
    
    def getEndDate(self):
        return datetime.strftime(self.__end_date, "%d %b %Y")


    """set methods"""
    def setDate(self, dateStr):
        return datetime.strptime(dateStr, "%d/%m/%Y")



    """add/remove methods"""

    def addResult(self, newResult:Result):
        try:
            if isinstance(newResult, Result):
                # Check if result to add is duplicate
                isDuplicate = False
                for r in self.__resultList:
                    if newResult.courseCode() == r.courseCode() and newResult.studentID() == r.studentID():
                        isDuplicate = True

                # If result is duplicate return False     
                if isDuplicate:
                    return False
                # or add result and ammend the Student and Course List accordingly
                else:
                    self.__resultList.append(newResult)
                    # either new student or new course, or both new
                    if newResult.courseCode() in self.__courseCodeList:
                        self.__studentIDList.append(newResult.studentID()) 
                    elif newResult.studentID() in self.__studentIDList:
                        self.__courseCodeList.append(newResult.courseCode()) 
                    else:
                        self.__courseCodeList.append(newResult.courseCode()) 
                        self.__studentIDList.append(newResult.studentID()) 
                    return True
            else:
                raise ValueError("Input must be an instance of Result")
        except ValueError as e:
            print("Error" + str(e))


    def removeResult(self, result):
        try:
            if isinstance(result, Result):
                # i = 0
                # while i < len(self.__resultList):

                # Check if result exists
                for r in self.__resultList:
                    if result.studentID() == r.studentID() and result.studentID() == r.studentID():
                        self.__resultList.remove(result)
                    
                        # Ammend student and course list respectively
                        courseMissing = True
                        studentMissing = True
                        # Check if course and student still exists in result list
                        for result in self.__resultList:
                            if result.courseCode() == r.courseCode():
                                courseMissing = False
                            if result.studentID() == r.studentID():
                                studentMissing = False

                        if studentMissing:
                            self.__studentIDList.remove(result.studentID())
                        if courseMissing:
                            self.__courseCodeList.remove(result.courseCode())       
                    else:
                        raise ValueError("The result does not exist!")      
            else:
                raise ValueError("Input must be an instance of Result")
        except ValueError as e:
            print("Error: " + str(e))



    """get result"""    # REQUIRES VALIDATION
    def getResults(self, id, courseCode = None):
        retrievedResults = []
        if courseCode == None:
            for result in self.__resultList:
                if result.studentID() == id:
                    retrievedResults.append(result)
        else:
            for result in self.__resultList:
                if result.studentID() == id and result.courseCode() == courseCode:
                    retrievedResults.append(result)
        return retrievedResults
        

        
    """Calculate passes/fails"""
    def getPasses(self):
        passes = 0
        for result in self.__resultList:
            if result.getGrade() != "F":
                passes += 1
        return passes

    def getFailures(self):
        failures = 0
        for result in self.__resultList:
            if result.getGrade() == "F":
                failures += 1
        return failures


    """display method"""
    def displayList(self, list):
        for result in list:
            print(result)


    def displayResultsList(self):
        for result in self.__resultList:
            print(result)

    def getResultsSummary(self):
        print(f"Results for {self.__term}")
        print(f"\tNumber of Passes: {self.getPasses()}")    # Number of Passes method
        print(f"\tNumber of Failures: {self.getFailures()}\n")    # Number of Failures method
        

    def __str__(self):
        display = f"Academic Term {self.__term}\n\t"
        display += f"Start date: {self.getStartDate()}\n\t"
        display += f"End date: {self.getEndDate()}\n\t"
        return display






"""Test functions"""
def main():
    # Test Student
    print("\nTest Student")
    student1 = Student("John")
    student2= Student("Nick")
    print(student1)
    print(student2)

    # Test Course
    print("\nTest Course")
    course1 = Course("CSIT121", "Object Oriented Design", 6)
    course2 = Course("CSIT128", "Web Development", 3)
    print(course1)
    print(course2)

    # Test invalid setcredits
    course1.credits = "wrong"
    print(course1)


    # Test PracticalResult
    print("\nTest Practical Result")
    # Create Practical result of same course different student
    practical1 = PracticalResult(student1, course1, 45, 40, 30)
    practical2 = PracticalResult(student2, course1, 85, 90, 90)
    duplicate = PracticalResult(student1, course1, 80, 85, 77)
    print(practical1)
    print(practical2)
     

    # Test CourseResult
    print("\nTest Course Result")
    # Create Course result of same course different student 
    courseResult1 = CourseResult(student1, course2, 85, 77)
    courseResult2 = CourseResult(student2, course2, 90, 80)
    print(courseResult1)
    print(courseResult2)


    # Test AcadTerm
    print("\nTest AcadTerm")
    term = AcadTerm("2024 Q4", "01/11/2024", "30/11/2024")
    print(term)
    term.getResultsSummary()
    term.displayResultsList()

    # Add a result
    print("\nAdd results")

    # Different Student + Same Course
    print("Different Student but same Course")
    term.addResult(practical1)
    term.addResult(practical2)
    term.getResultsSummary()
    term.displayResultsList()

    # Different Course + Same Student inside
    print("\nDifferent Course but same Student")
    term.addResult(courseResult1)
    term.addResult(courseResult2)
    term.getResultsSummary()
    term.displayResultsList()

    # Add a duplicate result
    print("\nAdd a duplicate result")
    term.addResult(duplicate)
    term.getResultsSummary()
    term.displayResultsList()

    # Remove an existing result
    print("\nRemove an existing result")
    term.removeResult(practical1)
    term.getResultsSummary()
    term.displayResultsList()

    # Remove a non-existing result
    print("\nRemove a non-existing result")
    term.removeResult(practical1)
    term.getResultsSummary()
    term.displayResultsList()


    # Test getResult
    print("\nTest getResult method")
    nickResults = term.getResults("20240002")
    nickPractical = term.getResults("20240002", "CSIT121")
    term.displayList(nickResults)
    print()
    term.displayList(nickPractical)


    # Test getGPA
    print(f"Nick's GPA: {Result.getGPA(nickResults)}")

    # REQUIRES ADDITIONAL TESTING


if __name__ == "__main__":
    main()