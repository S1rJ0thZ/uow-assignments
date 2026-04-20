# File name: Notebook.py

import datetime

class Note:

    """class variable"""
    __Next_ID = 1

    """Constructor"""
    def __init__(self, memo, tags):
        self.__memo = memo
        self.__tags = tags
        self.__id = Note.__Next_ID
        Note.__Next_ID += 1
        self.__creation_date = datetime.date.today()

    """setter/getter"""
    def getMemo(self):
        return str(self.__memo)
    
    def getID(self):
        return self.__id
    
    def setTags(self, tags):
        self.__tags = tags

    def setMemo(self, memo):
        self.__memo = memo


    """Match function"""
    def match(self, filter):
        """Determine if this note matches the filter text
        Return True if match found, else False
        Match is case sensitive, match both memo and tags
        """
        return filter in self.__memo or filter in self.__tags


    """display methods"""
    def display(self):
        print(self)     # call self.__str__()

    def __str__(self):
        display = f"{self.__id} {self.__tags}\n"
        display += f"Memo: {self.__memo}\n"
        display += f"Date: {self.__creation_date}\n"
        return display


# Container class
class Notebook:
    """"""
    def __init__(self):
        self.__notes = []

    def new_note(self, memo, tags):
        """Create a new note and add to the list"""
        note = Note(memo, tags)
        self.__notes.append(note)


    """display methods"""
    def display(self):
        for note in self.__notes:
            note.display()

    def __str__(self):
        """Return all the notes __str__"""
        text = ""
        for note in self.__notes:
            # text += f"{str(note)}\n"
            text += note.__str__() + "\n"
        return text
    
    def find_note(self, id):
        """Return the note with id, return None if id not found"""
        for note in self.__notes:
            if note.getID() == id:
                return note
        return None

    def modify_memo(self,id,memo):
        """
        Find the note with id, set the new memo
        Return True if id found and new memo set, else False
        """
        note = self.find_note(id)
        if note:
            note.setMemo(memo)
            return True
        else:
            return False
        
    def modify_tags(self, id, tags):
        note = self.find_note(id)
        if note:
            note.setTags(tags)
            return True
        else:
            return False
        
    def search(self, keyword):
        # Returns a list of notes that matches the filter
        notes = [note for note in self.__notes if note.match(keyword)]
        return notes

def print_notes(notes):
    print("#" * 20)
    print("Print all notes")
    for note in notes:
        note.display()
    print("#" * 20)


def test_notebook():
    notebook = Notebook()
    notebook.new_note("memo 1", "tagA")
    notebook.new_note("memo 2", "tagB")
    notebook.new_note("memo 3", "tagC")
    notebook.display()
    print(notebook)

    # test find_note
    note = notebook.find_note(2)
    print(note)
    
    note = notebook.find_note(5)
    print(note)

    # test modify memo
    r = notebook.modify_memo(1, "new memo")
    print(r)
    note = notebook.find_note(1)
    note.display()  # check memo updated
    r = notebook.modify_memo(5, "new memo")
    print(r)    # False

    # test search
    print()
    notes = notebook.search("memo")
    print_notes(notes)  # id 1 2 3
    notes = notebook.search("A")
    print_notes(notes)  # id 1 2
    notes = notebook.search("Python")
    print_notes(notes)  # nothing




def test_note():
    note1 = Note("Complete Assignment 1", "UOW Python Study")
    note2 = Note("Revise for exam", "UOW EXAM")
    note1.display()
    note2.display()

    print(note1)

    # Test match
    # test match memo - positive case
    print(note1.match("Assignment 1"))
    print(note2.match("EXAM")) #true

    # test match memo - negative case
    print(note1.match("EXAM"))  #False
    print(note2.match("Assigment 1"))  #False
    
    # test match tags - positive case
    print(note1.match("UOW"))
    print(note2.match("UOW"))

    # test match tags - negative case
    print(note1.match("Apple"))
    print(note2.match("Orange"))

if __name__ == "__main__":
    test_note()
    test_notebook()

    