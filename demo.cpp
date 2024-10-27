// Use this file to try out any of your code
// use "make demo" to run this code anytime
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

		head = newNode;
		numStudents++;
	}

	//add a Node with a student to the back (tail) of the list.
	void StudentList::addBack(Student s) 
	{
		Node *newNode = new Node(s, nullptr, tail);
		if(tail != nullptr)
		{
			tail -> next = newNode;
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

		else if(numStudents == 1)
		{	
			delete tail;
			tail = head = nullptr;
			numStudents--;
		}

		else
		{
			Node *temp = tail;
			tail = tail -> prev;
			delete temp;
			numStudents--;
		}
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
		if(numStudents == 1)
		{
			delete head;
			head = tail = nullptr;
			numStudents--;
			return;
		}
		else
		{	
			Node *temp = head;
			head = head -> next;
			delete temp;
			numStudents--;
			
		}
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
		Node *temp = head;
		for(int i = 0; i < index; i++)
		{
			temp = temp -> next;
		}
		temp -> prev -> next = new Node(s);
		temp -> prev -> next -> next = temp;
		numStudents++;

	}

	//find the student with the given id number and return them
	// if no student matches, print a message 
	// and create and return a dummy student object
	Student StudentList::retrieveStudent(int idNum) 
	{
		Node *temp = head;
		while(temp -> data.id != idNum)
		{
			temp = temp -> next;
			if(temp -> next == nullptr)
			{
				Student dummyStudent;
				cout << "Student was not found\n";
				return dummyStudent;
				break;
			}
		}
		return temp -> data;

	}

	// Remove a Node with a student from the list with a given id number
	// If no student matches, print a message and do nothing
	void StudentList::removeStudentById(int idNum) 
	{
		Node *temp = head;
		while(temp -> data.id != idNum)
		{
			temp = temp -> next;
			if(temp -> next == nullptr)
			{
				cout << "Student was not found\n";
				return;
			}
		}
		temp -> prev -> next = temp -> next;
		temp -> prev -> next -> prev = temp -> prev;
		delete temp;
	}

	//Change the gpa of the student with given id number to newGPA
	void StudentList::updateGPA(int idNum, float newGPA) 
	{
		Student temp = retrieveStudent(idNum);
		temp.GPA = newGPA;
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
		Node *temp = otherList.head;
		while(temp != nullptr)
		{
			addBack(temp -> data);
			Node *temp2 = temp -> next;
			delete temp;
			temp = temp2;
			
		}
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
				minGPAStudents.numStudents += 1;
			}
		}
		return minGPAStudents;

	}

int main() 
{
    StudentList first;
    Student student("nobody",1,0.0);
    Student student1("nobody",2,0.0);
    Student student2("nobody",3,0.0);
    Node *node1 = new Node(student);
    Node *node2 = new Node(student1);
    Node *node3 = new Node(student2);
    first.addBack(node1);
    first.addBack(node2);
    first.addBack(node3);
    first.printList();
}