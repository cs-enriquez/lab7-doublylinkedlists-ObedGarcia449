	#include "StudentList.h"

	// Define a constructor to initialize the list. The list starts with no Students
    StudentList::StudentList() 
	{
		numStudents = 0;
		head = nullptr;
		tail = nullptr;
	}

	// return the number of students currently in the list
	int StudentList::listSize() 
	{
		return numStudents;
	}

	//add a Node with a student to the front (head) of the list.
	void StudentList::addFront(Student s) 
	{
		Node *newNode = new Node(s, head, nullptr);
		if(head != nullptr)
		{
			head -> prev = newNode;
		}
		else
		{
			tail = newNode;
		}
		head = newNode;
		numStudents++;
	}

	void StudentList::addBack(Student s)
	{
		Node *newNode = new Node(s, nullptr, tail);
		if(tail != nullptr)
		{
			tail -> next = newNode;
		}
		else
		{
			head = newNode;
		}
		tail = newNode;
		numStudents++;
	}

	//Print out the names of each student in the list.
	void StudentList::printList() 
	{
		Node *temp = head;
		while(temp != nullptr)
		{
			cout << temp -> data.name << endl;
			temp = temp -> next;
		}
	}

	// Remove the Node with the student at the back (tail) of the list
	// should not fail if list is empty! Print an error message if this occurs
	// Don't forget that your head and tail pointers will be null pointers if the list is empty
	void StudentList::popBack() 
	{
		if(numStudents == 0)
		{
			cout << "ERROR - NO STUDENTS IN LIST\n";
			return;
		}

		Node *temp = tail;
		if(head == tail)
		{
			head = tail = nullptr;
		}
		else
		{
			tail = tail ->prev;
		}
		delete temp;
		numStudents--;
	}

	// Remove the Node with the student at the front (head) of the list
	// should not fail if list is empty! Print an error message if this occurs
	// Don't forget that your head and tail pointers will be null pointers if the list is empty
	void StudentList::popFront() 
	{
		if(numStudents == 0)
		{
			cout << "ERROR - NO STUDENTS IN LIST\n";
			return;
		}
		Node *temp = head;
		if(head == tail)
		{
			head = tail = nullptr;
		}
		else
		{
			head = head -> next;
			head -> prev = nullptr;
		}
		delete temp;
		numStudents--;
	}

	//insert a student at the position "index".
	// for this list, count head as index 0
	// if index is outside of current list range, 
	// print a message and insert the student at the back of the list
	// the previous Node at your target index should be moved forward. "For exampe, Node with student at index i, becomes index i+1" 
	// Remember that you already have methods that can add students to the front or back of list if needed! Don't repeat this code.
	void StudentList::insertStudent(Student s, int index) 
	{
		if(index > numStudents - 1)
		{
			cout << "Index is out of range - student will be added to the back of the list\n";
			addBack(s);
			return;
		}
		Node *newNode = new Node(s);
		
		if(index == 0)
		{
			addFront(s);
			return;
		}

		Node *temp = head;
		for(int i = 0; i < index; i++)
		{
			temp = temp -> next;
		}

		newNode -> prev = temp -> prev;
		newNode -> next = temp;

		if(temp -> prev)
		{
			temp -> prev -> next = newNode;
		}
		temp -> prev = newNode;
		numStudents++;

	}

	//find the student with the given id number and return them
	// if no student matches, print a message 
	// and create and return a dummy student object
	Student StudentList::retrieveStudent(int idNum) 
	{
		Node *temp = head;
		while(temp != nullptr)
		{
			if(temp -> data.id == idNum)
			{
				return temp -> data;
			}
			temp = temp -> next;
		}
		Student dummyStudent;
		cout << "Student was not found\n";
		return dummyStudent;

	}

	// Remove a Node with a student from the list with a given id number
	// If no student matches, print a message and do nothing
void StudentList::removeStudentById(int idNum) 
{
    if (numStudents == 0) 
    {
        cout << "NO STUDENTS IN LIST\n";
        return;
    }

    Node *temp = head;

    while (temp != nullptr) 
    {
        if (temp->data.id == idNum) 
        {
            if (temp->prev != nullptr) 
            {
                temp->prev->next = temp->next;
            } 
            else 
            {
                head = temp->next;
            }

            if (temp->next != nullptr) 
            {
                temp->next->prev = temp->prev;
            } 
            else 
            {
                tail = temp->prev;
            }

            delete temp;
            numStudents--;
            return;
        }
        temp = temp->next;
    }
    cout << "NO STUDENT FOUND\n";
}


	//Change the gpa of the student with given id number to newGPA
	void StudentList::updateGPA(int idNum, float newGPA) 
	{
		Node *temp = head;

		while(temp != nullptr)
		{
			if(temp-> data.id == idNum)
			{
				temp -> data.GPA = newGPA;
				return;
			}
			temp = temp -> next;
		}
		cout << "NO STUDENT FOUND\n";
	}

	//Add all students from otherList to this list.
	//otherlist should be empty after this operation.
	/*
	For example, if the list has 3 students:
	s1 <-> s2 <-> s3
	and otherList has 2 students
	s4 <-> s5
	then after mergeList the currently list should have all 5 students
	s1 <-> s2 <-> s3 <-> s4 <-> s5
	and otherList should be empty and have zero students.
	*/
	void StudentList::mergeList(StudentList &otherList) 
	{
		//start writing more comments!!

		if(otherList.head == nullptr)
		{
			return;
		}

		//if the current list is empty just take the other lists tail and head nodes since they are all connected
		if(head == nullptr)
		{
			head = otherList.head;
			tail = otherList.tail;
		}
		else
		{
			tail -> next = otherList.head;
			otherList.head -> prev = tail;
			tail = otherList.tail;
		}
		
		numStudents += otherList.numStudents;

		Node *temp = otherList.head;
		while(temp != nullptr)
		{
			Node *nextNode = temp -> next;
			delete temp;
			temp = nextNode;
		}

		otherList.head = otherList.tail = nullptr;
		otherList.numStudents = 0;
	}

	//create a StudentList of students whose gpa is at least minGPA.
	//Return this list.  The original (current) list should
	//not be modified (do not remove the students from the original list).
	StudentList StudentList::honorRoll(float minGPA) 
	{
		StudentList minGPAStudents;
		Node *finalTemp2 = head;
		
		while(finalTemp2 != nullptr)
		{
			if(finalTemp2 -> data.GPA >= minGPA)
			{
				minGPAStudents.addFront(finalTemp2 -> data);
			}
			finalTemp2 = finalTemp2 -> next;
		}
		return minGPAStudents;

	}
