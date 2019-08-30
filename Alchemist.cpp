//Title: Alchemist.cpp
//Author: Humza Faraz
//Date: 3/7/19
//Section: 32
//E-mail: hfaraz1@umbc.edu
//Description: Inherits functions from the header file.

#include <iostream>
#include "Alchemist.h"
#include "Element.h"
#include "Game.h"

using namespace std;

// Name: Alchemist() - Default Constructor
// Desc: Used to build a new Alchemist
// Preconditions - Requires default values
// Postconditions - Creates a new Alchemist
Alchemist::Alchemist(){
  m_attempts = 0;
  m_repeats = 0;
  m_numElements = 0;
}

// Name: Alchemist(name) - Overloaded constructor
// Desc - Used to build a new Alchemist
// Preconditions - Requires name
// Postconditions - Creates a new Alchemist
Alchemist::Alchemist(string name){
  m_myName = name;
  m_attempts = 0;
  m_repeats = 0;
  m_numElements = 0; 
}
// Name: GetName()
// Desc - Getter for Alchemist name
// Preconditions - Alchemist exists
// Postconditions - Returns the name of the Alchemist
string Alchemist::GetName(){
  return m_myName;
}

// Name: SetName(string)
// Desc - Allows the user to change the name of the Alchemist
// Preconditions - Alchemist exists
// Postconditions - Sets name of Alchemist
void Alchemist::SetName(string name){
  m_myName = name;
}

// Name: DisplayElements()
// Desc - Displays a numbered list of all elements known by the Alchemist
// Preconditions - Alchemist exist
// Postconditions - None
void Alchemist::DisplayElements(){
  for (int i = 0; i < m_numElements; i++){
    Element element = GetElement(i);
    string count = element.m_name;
    cout << i + 1 << ". " << count << endl;
  }
}

// Name: GetNumElements()
// Desc - Returns number of elements known by the Alchemist
// Preconditions - Alchemist exists
// Postconditions - None
int Alchemist::GetNumElements(){
  return m_numElements;
}

// Name: CheckElement(Element)
// Desc - Checks to see if the Alchemist has an element
// Preconditions - Alchemist already has elements
// Postconditions - Returns true if Alchemist has element else false
bool Alchemist::CheckElement(Element element){
  for (int i = 0; i < m_numElements; i++){
    Element check = GetElement(i);
    string element1 = check.m_name;
    string element2 = element.m_name;
    if (element1 == element2){
      return true;
    }
  }
  return false;
}

// Name: AddElement(Element)
// Desc - Adds element to m_myElements if not known increases numElements
// Preconditions - Alchemist exists and new element not already known
// Postconditions - Adds element to m_myElements
void Alchemist::AddElement(Element element){
  m_myElements[m_numElements] = element;
  m_numElements++;
}

// Name: GetElement(int)
// Desc - Checks to see if the alchemist has an element
// Preconditions - Alchemist already has elements
// Postconditions - Returns element at index
Element Alchemist::GetElement(int loc){
  return m_myElements[loc];
}

//Name: AddAttempt()
// Desc - Increments attempts
// Preconditions - Alchemist attempts a merge
// Postconditions - Increments every time a merge is attempted
void Alchemist::AddAttempt(){
  m_attempts++;
}

// Name: GetAttempts()
// Desc - Returns number of attempts for that Alchemist
// Preconditions - Alchemist exists
// Postconditions - Returns total number of attempts
int Alchemist::GetAttempts(){
  return m_attempts;
}

// Name: AddRepeat()
// Desc - Increments repeats for every time an element has already been found
// Preconditions - Alchemist attempts a merge
// Postconditions - Increments every time a merge yields an element
//                  already found.
void Alchemist::AddRepeat(){
  m_repeats++;
}

// Name: GetRepeats()
// Desc - Returns number of repeats for that Alchemist
// Preconditions - Alchemist exists
// Postconditions - Returns total number of repeats
int Alchemist::GetRepeats(){
  return m_repeats;
}
