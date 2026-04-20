# Driver,client class - "View" MCV-model controller view
# Non object-oriented 
# Try to convert to Object Oriented Design -> Notebook_app class

from Notebook import Note, Notebook

def print_menu_get_choice():
    print("Notebook application")
    print("1 - Show all notes")
    print("2 - Search Notes")
    print("3 - Add note")
    print("4 - Modify note")
    print("5 - Quit")
    choice = int(input("Enter choice (1-5): "))
    return choice

def show_all_notes(notebook):
    print("#"*20)
    print("Show all notes")
    notebook.display()
    print("#"*20)

def print_notes(notes):
    print("#" * 20)
    print("Print results:")
    if len(notes) == 0:
        print("No note found")
    else:
        for note in notes:
            note.display()
    print("#" * 20)

def search_notes(notebook):
    print("Search notes")
    filter = input("Find a note: ")
    foundNotes = notebook.search(filter)
    return foundNotes


def add_note(notebook):
    print("#"*20)
    print("Add note")
    memo = input("Enter new memo:")
    tags = input("Enter new tags:")
    notebook.new_note(memo, tags)
    print("New note added")
    print("#"*20)

def modify_note(notebook, ):
    print("#"*20)
    print("Modify note")
    id = int(input("Enter note id: "))
    note = note.find_note(id)
    if note:
        memo = input("Enter new memo: ")
        tags = input("Enter new tags: ")
        if memo:
            notebook.modify_memo(id, memo)
        if tags:
            notebook.modify_tags(id, tags)
        print("Note updated")
    else:
        print("Invalid note id")
    print("#"*20)


def main():
    notebook = Notebook()

    notebook.new_note("memo 1", "tagA")
    notebook.new_note("memo 2", "tagB")
    notebook.new_note("memo 3", "tagC")

    carryOn = True
    while carryOn:
        choice = print_menu_get_choice
        if choice == 1:
            show_all_notes()
        elif choice == 2: 
            search_notes(notebook)
        elif choice == 3:
            add_note()
        elif choice == 4:
            modify_note()
        elif choice == 5:
            carryOn = False
        else:
            print("Invalid choice")
    print("End of Notebook app")


    if __name__ == "__main__":
        main()