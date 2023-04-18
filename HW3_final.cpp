#include <iostream>
#include <cctype>
#include <cstring>
#include <fstream>

using namespace std;


// Colton Vitkoczy
// November 11, 2022
// The purpose of the program is to allow a user to store a collection of social media posts
// The user is allowed to store up to 10 social media posts containing the author, title, link,
// text of the post, the number of likes, and the number of commnets.



// Constant variables

const int AUTHOR = 25;
const int TITLE = 25;
const int LINK = 35;
const int TEXT = 45;
const int POSTS = 10;

// Structure

struct sm_posts
{
	char author[AUTHOR]; // Array for author
	char title[TITLE];   // Array for the title
	char link[LINK];     // Array for the link
	char post_text[TEXT];// Array for the text of the posr
	int number_likes;    // Int for the number of likes
	int number_comments; // Int for the number of commnets
};

// Prototype functions

void insert_a_post(sm_posts & a_post); // Allows the user to input a post
void display_a_post(sm_posts & a_post);// Displays the post the user entered
void save_post(sm_posts library[], int number_saved); //saves the post
int load(sm_posts library[]);// load items from file previuosly stored
void display_posts(sm_posts library[], int number_posts);// display all items
void read_posts(sm_posts library[], int & number_posts);// Allows the user to add multiple items
void display_menu(sm_posts library[], int & number_posts); // Puts the user in a loop and gives them a menu
void matching_author(sm_posts library[], int & number_posts); // Allows the user to search for matching authors


int main()
{
	sm_posts library[POSTS]; // Initializes a library of type struct contaning 10 elements
	int number_posts = 0;

	number_posts = load(library);// loads number of posts from library -- Step 1 - Task 4
				     
	// Step 1 in my code is task 4 in the instructions. It just seemed like this should go first
	// I dont know if this is appropriate for this assignment. 
	
	read_posts(library, number_posts); // Reads in posts from the user -- Step 2 - Task 1
	save_post(library, number_posts); // Saves posts entered -- Step 3 - Task 2
	display_posts(library, number_posts); // Displays posts in the library -- Step 4 - Task 3

	display_menu(library, number_posts);  // Displays a menu and allows the user to repeat -- Step 5 - Task 5
	matching_author(library, number_posts);// Displays any matching authors -- Step 6 - Task 6
	return 0;
}

// Allows the user to insert in a social media post.
void insert_a_post(sm_posts & a_post)
{	// Gettign input for author
	cout << "Please enter in the author: " ;
	cin.get(a_post.author, AUTHOR, '\n');
	cin.ignore(100, '\n');

	// Gettign input for title
	cout << "Please enter in the post title: " ;
	cin.get(a_post.title, TITLE, '\n');
	cin.ignore(100, '\n');
		
	// Gettign input for a link
	cout << "Please enter in a link: " ;
	cin.get(a_post.link, LINK, '\n');
	cin.ignore(100, '\n');

	// Gettign input for posts text
	cout << "Please enter in the posts text: " ;
	cin.get(a_post.post_text, TEXT, '\n');
	cin.ignore(100, '\n');

	// Gettign input for number of likes
	cout << "Please enter in the number of likes: " ;
	cin >> a_post.number_likes;
	cin.ignore(100, '\n');

	// Gettign input for number of comments
	cout << "Please enter in the number of comments: " ;
	cin >> a_post.number_comments;
	cin.ignore(100, '\n');

	cout << endl;
}

// Function that saves the user's input.. But it doesn't work.
void save_post(sm_posts library[], int number_saved)
{
	ofstream file_out; // Declares a of variable for file out

	file_out.open("sm_posts.txt");// Opens a file to file out
	if (file_out) // Checks file_out opened
	{
		for (int i = 0; i < number_saved; ++i) // Loops through and saves every post
		{
			file_out << library[i].author << '~'// seperating values with ~
				 << library[i].title << '~'
				 << library[i].link << '~'
				 << library[i].post_text << '~'
				 << library[i].number_likes << '~'
				 << library[i].number_comments << endl;
		}
		file_out.close(); // Close out the file
	}
}

// Loads in any information from the external data file
int load(sm_posts library[])
{
	ifstream file_in; // Declares a if variable for file in
	int i = 0; // Counter

	file_in.open("sm_posts.txt"); // Opens a file to file in
	
	if (file_in) // checks file_in opened
	{
		file_in.get(library[0].author, AUTHOR, '~');
		file_in.ignore(100, '~');
		// Loops through while we're not at eof and we don't exceed memory
        	while (!file_in.eof() && i < POSTS)
        	{
			file_in.get(library[i].title, TITLE, '~');
			file_in.ignore(100, '~');
	
			file_in.get(library[i].link, LINK, '~');
			file_in.ignore(100, '~');

			file_in.get(library[i].post_text, TEXT, '~');
			file_in.ignore(100, '~');

			file_in >> library[i].number_likes;
			file_in.ignore(100, '~');

	    		file_in >> library[i].number_comments;
	    		file_in.ignore(100, '\n');

	    		++i;// Increasing counter variable

            		file_in.get(library[i].author, AUTHOR, '~');
            		file_in.ignore(100, '~');
        	}	
        file_in.close();// Closes the file
	}
        return i; // Returns i the number of posts
}

// displays a post
void display_a_post(sm_posts & a_post)
{
	cout << "Author:  " << a_post.author << endl
	     << "Title: " << a_post.title << endl
	     << "Hyperlink: " << a_post.link << endl
	     << "Post Text" << a_post.post_text << endl
	     << "Number of likes: " << a_post.number_likes << endl
	     << "Number of comments: " << a_post.number_comments << endl;
	cout << endl;
}

// displays all posts in the library
void display_posts(sm_posts library[], int number_posts)
{
	cout << "Number of posts are: " << number_posts << endl;
	// Loops through and gets the function display_a_post at index i
	for (int i = 0; i < number_posts; ++i)
		display_a_post(library[i]); 
}
// Allows the user to enter in multiple posts
void read_posts(sm_posts library[], int & number_posts)
{
	int i = number_posts; // This acts as a counter from the number of posts entered
	char response = 'N';  // response vriable for the loop

	cout << "Would you like to add in a post? : " ;
	cin >> response;
	cin.ignore(100, '\n');
	// Loops through to grab the inert_a_post function allowing a user to enter in a post
	// at index i.
	while ((toupper(response)) == 'Y' && i < POSTS)
	{
		insert_a_post(library[i]);
		cout << "Another? ";
		cin >> response;
		cin.ignore(100, '\n');
		++i; // increasing the counter/number of posts
	}
	number_posts = i; // updates the number of posts

	if (number_posts == POSTS) // displays a message if memory is full.
		cout << "Memory full only 10 posts can be saved. " << endl;
}

//Function that brings up a menu and allows the user to add new items, diplay, load or quit.
void display_menu(sm_posts library[], int & number_posts) 
{
	char response = 'N';// setting a response variable
	bool flag = false; // setting a flag for the while loop

	do
	{
		cout << "Would you like to A) add a new item. B) Display all items. C) load from a file " ;
		cout << "or D) quit. Please enter your decision by the repective letter." << endl;
		cin >> response;
		cin.ignore(100, '\n');
	
		if ('A' == toupper(response))
		{	
			read_posts(library, number_posts); // Reads in any new posts
			save_post(library, number_posts); // saves the new entries
		}

		if ('B' == toupper(response))
		{
			display_posts(library, number_posts); // calls on the function to display
		}
	
		if ('C' == toupper(response))
		{
			load(library); // reloads library
		}
	
		if ('D' == toupper(response))
		{
			flag = true; // updates flag to quit
		}

	} while(!flag);
}

// Asks the user to search for any matching authors.
// For this step I wasn't sure if I was supposed to get input from the user to search by or
// automatically display any identical authors. So, I went with what was easier.
void matching_author(sm_posts library[], int & number_posts)
{
	char search_item[AUTHOR]; // establishes array to use in search
	char response = 'N';

	cout << "Would you like to search for an author's posts?" ;
	cin >> response; // gets the response variable
	cin.ignore(100, '\n');
	
	if (toupper(response) == 'Y')
	{
		cout << "Please enter an author to search for: " ;	
		cin.get(search_item, AUTHOR, '\n'); // gets the input 
		cin.ignore(100, '\n');
		cout << endl;

		for (int i = 0; i < number_posts; ++i)
		{
			if (strcmp(library[i].author, search_item) == 0) // using strcmp to match authors
				display_a_post(library[i]); // displays any matching items
		}
	}
}
