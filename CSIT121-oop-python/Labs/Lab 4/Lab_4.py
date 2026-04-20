# Lab 4: File I/O
#
# File name: Lab_4.py

import csv

class TestResultException(Exception):
    def __init__(self, message):
        self.__message = message

    @property
    def message(self):
        return self.__message



class TestResult:
    """
    Construct a Test Result with a name and scores
    """
    def __init__(self, name):
        self.__name = name
        self.__scores = {}

    # private methods
    def load(self, csvFile):
        line_number = 0
        try:
            with open(csvFile, "r") as scores, open("errorLog.txt", "w") as error:
            
                # Return lines of Dictionaries
                reader = csv.DictReader(scores, fieldnames=["candidate_ID", "marks"])

                # Loop through the lines and add to dictionary
                for row in reader:
                    line_number += 1
                    try:
                        try:
                            marks = int(row["marks"])
                        except:
                            raise ValueError("Marks must be a digit")
                        if 0 <= marks <= 100:
                            self.__scores[row["candidate_ID"]] = marks
                        else:
                            raise TestResultException("Marks must inside range of 1-100")
                    except ValueError as e:
                        error.write(f"Line {line_number}: {e}: {row['marks']}\n")
                    except TestResultException as e:
                        error.write(f"Line {line_number}: {e}: {row['marks']}\n")
        except FileNotFoundError as e:
            print(f"File {csvFile} is not found")

    
    # Update Scores
    def update_score(self, id: str, marks:int):
        try:
            try:
                marks = int(marks)
            except:
                raise ValueError("Marks must be an integer")
            if 0 <= marks <= 100:
                self.__scores[id] = marks
            else:
                raise TestResultException("Marks must be inside range of 1 - 100")
        except ValueError as e:
            print(f"Error: {e}")
        except TestResultException as e:
            print(f"Error: {e}")


    # Get stats
    def get_basic_stats(self):
        #lowest = min(self.__scores.values())
        #highest = max(self.__scores.values())
        #sum = sum(self.__scores.values())
        highest = 0
        lowest = 0
        sum = 0
        for score in self.__scores.values():
            if score > highest:
                highest = score
            if score < lowest:
                lowest = score
            sum += score
        average = sum / len(self.__scores.values())
        return f"Highest: {highest}\nLowest: {lowest}\nAverage: {average:.2f}\n"
    

    # get candidates who failed the test (need to retake)
    def get_retest_list(self):
        with open("retests.txt", 'w') as retests:
            retests.write(f"{self.__name} retests\n\n")
            retests.write(f"{'Candidate ID':<15}{'Marks':>6}\n")
            for id, mark in self.__scores.items():
                if mark < 50:
                    retests.write(f"{id:<15}{mark:>6}\n")

    # get passes
    def get_passes(self):
        passes = 0
        for score in self.__scores.values():
            if score >= 50:
                passes += 1
        return passes

    # Str method
    def __str__(self):
        display = f"{self.__name}\n"
        display += f"Number of passes: {self.get_passes()}"
        return display



def main():
    # Construct TestResult 
    results = TestResult("Math Test 2023")

    # Load results
    results.load("Math Test 2023.csv")

    # Test get_basic_stats
    results.get_basic_stats()

    # Test get_retest_list
    results.get_retest_list()

    # Test str method
    print(results)



if __name__ == "__main__":
    main()

