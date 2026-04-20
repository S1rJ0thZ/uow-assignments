# File name: Lab_2_Notebook.py

from datetime import datetime

class Note:

    """Class Variable"""
    __no_Of_Notes = 0
    __note_creation_date = datetime.now()


    """Create Note"""
    def __init__(self, tag, memo):
        self.__createNoteID()
        self.setTag(tag)
        self.setMemo(memo)


    """Private methods"""
    def __createNoteID(self):
        Note.__no_Of_Notes += 1
        self.__ID = str(Note.__no_Of_Notes)


    """Getter methods"""
    def getID(self):
        return self.__ID
    
    def getTag(self):
        return self.__tag
    
    def getMemo(self):
        return self.__memo
    

    """Setter methods"""
    def setTag(self, tag):
        self.__tag = str(tag)

    def setMemo(self, memo):
        self.__memo = str(memo)

    #*
    """Find keyword method"""           # Compare external keyword with object attributes
    def matchKeyword(self, keyword):
        return keyword in self.__tag or keyword in self.__memo      # Return a Boolean
    #*


    """Display method"""
    def __str__(self):
        return f"{self.__ID}: {self.__tag}\n{self.__memo}\n"
    
    def display(self):
        print(self)
    



class Notebook:
    
    """Create notebook"""
    def __init__(self):
        # self.__title = title
        self.__noteList = []


    """Add/Modify note methods"""
    def createNote(self, tag, memo):
        newNote = Note(tag, memo)
        self.__noteList.append(newNote)


    # Have one for modifying tags and another for modifying memo
    '''def modifyNote(self, noteID, tag, memo):
        for note in self.__noteList:
            if note.getID() == noteID:
                note.setTag(tag)
                note.setMemo(memo)
                return True         # further validation
    '''
            
    def modifyNoteTag(self, id, tag):
        note = self.findNoteByID(id)
        if note:
            note.setTag(tag)
            return True
        else:
            return False
        
    def modifyNoteMemo(self, id, memo):
        note = self.findNoteByID(id)
        if note:
            note.setMemo(memo)
            return True
        else:
            return False


    """Search methods"""
    #*
    def findNoteByID(self, noteID):
        for note in self.__noteList:
            if note.getID() == noteID:
                return note
        return None
    
    """Search by tags and memos"""
    def searchNoteList(self, keyword):
        foundNotes = [note for note in self.__noteList if note.matchKeyword(keyword)]
        return foundNotes   #--> List
    #*

    '''def searchForNote(self, tag):
        for note in self.__noteList:
            if note.getTag() == tag:
                return note         # further validation
    '''


    """Display methods"""
    def __str__(self):
        display = ""
        for note in self.__noteList:
           display += f"{note}\n"
        return display
    

    """Additional Methods"""
    '''def selectAction(self, userInput):
        if userInput == '1':
            print(f"{self}\n")
        elif userInput == '2':
            return
    '''
def displayNotes(notesList):
        for note in notesList:
            print(note)


"""Test functions"""   
def testNote():
    note1 = Note("UOW Python Study", "Do Assignment 1")
    note2 = Note("UOW Object Oriented Study", "Read lecture notes")
    note1.display()
    print(note1)

    # Test matchKeyword method
    # both positive case
    print(note1.matchKeyword("UOW"))
    print(note2.matchKeyword("UOW"))

    # both negative case
    print(note1.matchKeyword("Object"))
    print(note2.matchKeyword("Python"))

    # 1 postive 1 negative
    print(note1.matchKeyword("Python"))
    print(note2.matchKeyword("Python"))
    print()


def testNotebook():
    print("Test notebook")
    notebook1 = Notebook()

    # Add notes into Notebook
    notebook1.createNote("UOW Python Study", "Do Assignment 1")
    notebook1.createNote("UOW OOP", "Read lecture 4")
    notebook1.createNote("Stationary restock", "Buy 3 blue pens")
    print(notebook1)
    print()

    # test findNoteByID()
    print("Test find note method")
    note = notebook1.findNoteByID('3')
    print(note)
    print()

    # test modify Note by Tag and memo
    print("Change note 1 tag")
    notebook1.modifyNoteTag("1", "CSIT121 Study")
    print(notebook1)
    print("\nChange note 3 memo")
    notebook1.modifyNoteMemo("3", "Buy Erasers")
    print(notebook1)
    print()

    # test search
    print("Search for note using keyword")
    results = notebook1.searchNoteList("UOW")
    displayNotes(results)



if __name__ == "__main__":
    #testNote()
    testNotebook()
    """Display"""
    #print("Notebook Menu\n\n")

    """"""