//Title: Game.cpp
//Author: Humza Faraz
//Date: 3/7/19
//Section: 32
//E-mail: hfaraz1@umbc.edu
//Description: Creates game using elements of Element and Alchemist

#include <iostream>
#include <fstream>
#include "Game.h"
#include "Alchemist.h"
#include "Element.h"

using namespace std;

const int DISPLAY = -1;
const int PLACEHOLDER = 10;

/* Name: Game() Default Constructor
// Desc - Builds a new game by:
// 1. Loads all Alchemy recipes into m_elements (by making elements)
// 2. Asks user for their alchemist's name (store in m_myAlchemist as m_myNam\
e)
// 3. Adds fire, water, air, and earth to m_myElements (in m_myAlchemist)
// Preconditions - None
// Postconditions - m_elements is populated
*/
Game::Game(){
  Alchemist myAlchemist;
  m_myAlchemist = myAlchemist;
}

// Name: LoadElements
// Desc - Loads each element into m_elements from file
// Preconditions - Requires file with valid element data
// Postconditions - m_element is populated with element structs
void Game::LoadElements(){
  //loads in file
  ifstream myfile;
  myfile.open("proj2_data.txt");

  Element newElement;
  string name;
  int count = 0;
  
  if (myfile.is_open()){
    while(getline(myfile, newElement.m_name, ',')){
      if (myfile.peek() == ','){
	myfile.ignore(PLACEHOLDER, ',');
      }
      if (myfile.peek() == ','){
	newElement.m_element1 = " ";
	newElement.m_element2 = " ";
      }
      else{
	getline(myfile, newElement.m_element1, ',');

	if (myfile.peek() == ','){
	  myfile.ignore(PLACEHOLDER,',');
	}
	getline(myfile, newElement.m_element2, '\n');
      }
      m_elements[count] = newElement;
      
      string name = newElement.m_name;
      if (name == "Air" or name == "Fire" or name == "Water" or\
	  name == "Earth"){
	m_elements[count] = newElement;
	m_myAlchemist.AddElement(newElement);
	count++;
      }
      count++;
    }
    
    cout << count << " elements loaded." << endl;
      
  }
  else{
    cout << "File cannot be opened." << endl;
  }
  myfile.close();
}

// Name: StartGame()
// Desc - Manages the game itself including win conditions continually
//         calling the main menu
// Preconditions - Player is placed in game
// Postconditions - Continually checks to see if player has entered 4
void Game::StartGame(){
  GameTitle();
  LoadElements();

  //sets name of Alchemist
  string name;
  cout << "What's your name?" << endl;
  getline(cin, name);
  m_myAlchemist.SetName(name);

  //while game runs
  int choice;
  choice = MainMenu();
  while (choice != 4){
    switch(choice){
    case 1:
      DisplayElements();
      choice = MainMenu();
      break;
    case 2:
      CombineElements();
      choice = MainMenu();
      break;
    case 3:
      CalcScore();
      choice = MainMenu();
      break;
    default:
      cout << "Invalid input. Please enter 1-4." << endl;
      choice = MainMenu();
      break;
    }
  }
  cout << "Thank you for playing!" << endl;
}

// Name: DisplayMyElements()
// Desc - Displays the current elements
// Preconditions - Player has elements
// Postconditions - Displays a numbered list of elements
void Game::DisplayElements(){
  m_myAlchemist.DisplayElements();
}

// Name: MainMenu()
// Desc - Displays and manages menu
// Preconditions - Player has an Alchemist
// Postconditions - Returns number including exit
int Game::MainMenu(){
  int choice;
  cout << "What would you like to do?" << endl;
  cout << "1. Display the Alchemist's Elements" << endl;
  cout << "2. Attempt to Combine Elements" << endl;
  cout << "3. See Score" << endl;
  cout << "4. Quit" << endl;
  cin >> choice;
  //while choice is invalid
  while(choice < 1 or choice > 4){
    cout << "Invalid choice. Please enter 1-4." << endl;
    cin >> choice;
  }
		
  return choice;
}

// Name: CombineElements()
// Desc - Attempts to combine known elements
// Preconditions - Alchemist is populated with elements
// Postconditions - May add element to Alchemist's list of elements
void Game::CombineElements(){
  int choice1;
  int choice2;
  string firstName;
  string secondName;
  RequestElement(choice1);
  RequestElement(choice2);

  //Gets names of user's choice elements
  Element firstEl = m_myAlchemist.GetElement(choice1);
  Element secondEl = m_myAlchemist.GetElement(choice2);
  firstName = firstEl.m_name;
  secondName = secondEl.m_name;

  int index = SearchRecipes(firstName, secondName);
  //if combination doesn't exist
  if (index == -1){
    cout << "Nothing happens when you combine " << firstName << " and " <<
      secondName << "." << endl;
  }
  else{
    //checks if element is a repeat
    Element test = m_elements[index];
    bool check = m_myAlchemist.CheckElement(test);
    if (check == true){
      cout << "User already have this element." << endl;
      m_myAlchemist.AddRepeat();
    }
    else{
      //if element isn't a repeat and is valid
      m_myAlchemist.AddElement(test);
      cout << firstName << " and " << secondName << " creates "
	   << test.m_name << endl;
      cout << "Element successfully added." << endl;
      m_myAlchemist.AddAttempt();
    }
  }
   
}

// Name: RequestElement()
// Desc - Requests element to use to merge
// Preconditions - Alchemist has elements to try and merge
// Postconditions - Returns
void Game::RequestElement(int &choice){
  int option;
  cout << "Which elements would you like to merge?" << endl;
  cout << "To list know elements enter -1" << endl;
  cin >> option;
  
  while (option == DISPLAY){
    DisplayElements();
    cout << "Which elements would you like to merge?" << endl;
    cin >> option;
  }
  //while user's input is invaid
  while((option < 1 and option != DISPLAY) or \
	option > m_myAlchemist.GetNumElements()){
    cout << "Invalid option." << endl;
    cout << "Which elements would you like to merge." << endl;
    cin >> option;
  }
  choice = option-1;
}

// Name: SearchRecipes()
// Desc - Searches recipes for two strings
// Preconditions - m_elements is populated
// Postconditions - Returns int index of matching recipe
int Game::SearchRecipes(string choice1, string choice2){
  for (int i = 0; i < PROJ2_SIZE; i ++){
    Element check = m_elements[i];
    string element1 = check.m_element1;
    string element2 = check.m_element2;
    //if user's elements match a recipe, return index
    if ((choice1 == element1 and choice2 == element2) or \
	(choice2 == element1 and choice1 == element2)){
      return i;
    }
  }
  return -1;
}

// Name: CalcScore()
// Desc - Displays current score for Alchemist
// Preconditions - Alchemist is populated with elements
// Postconditions - None
void Game::CalcScore(){
  double numElements = m_myAlchemist.GetNumElements();
  double percent = (numElements/PROJ2_SIZE) * 100;
  //sets precision of percent to 2
  cout.setf(ios::fixed);
  cout.setf(ios::showpoint);
  cout.precision(2);
  
  cout << "**The Alchemist**" << endl;
  cout << "The Great Alchemist " << m_myAlchemist.GetName() << endl;
  cout << "The Alchemist has tried to combine " <<
    m_myAlchemist.GetAttempts() << " elements." << endl;
  cout << "The Alchemist has repeated " <<
    m_myAlchemist.GetRepeats() << " times." << endl;
  cout << "The Alchemist found " << m_myAlchemist.GetNumElements() <<
    " out of " << PROJ2_SIZE << " elements." << endl;
  cout << "You have completed " << percent << "% of the elements." << endl;
}
