# Notebook_Application.py

from Lab_2_Notebook import Notebook

class  NotebookApp:
    def __init__(self):
        self.__notebook = Notebook()

    def printUserMenu_getChoice(self):
        print("Notebook application\n")
        print("1. Show all Notes")
        print("2. Search Notes")
        print("3. Add Note")
        print("4. Modify")
        print("5. Quit\n")
        choice = int(input("Enter an option (1-5): "))
        return choice

    def userSelection(self, choice):
        if choice == "1":
            self.showAllNotes()
        elif choice == "2":
            self.searchNotebook()
        elif choice == "3":
            self.addNote()
        elif choice == "4":
            self.modifyNote()
        elif choice == "5":
            self.quit()
        else:
            print("Invalid Selection")

    


def main():
    notebook1 = NotebookApp()

    # Print User Menu
    choice = notebook1.printUserMenu_getChoice()

if __name__ == "__main__":
    main()