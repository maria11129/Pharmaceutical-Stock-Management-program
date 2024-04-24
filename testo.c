#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_INPUT_SIZE 50
#define NUM_ROOMS 7 // Adjust this based on the number of rooms in your game

typedef struct Room {
    char name[MAX_INPUT_SIZE];
    char description[MAX_INPUT_SIZE];
    int north;
    int south;
    int east;
    int west;
    int has_item;
    char item_name[MAX_INPUT_SIZE];
} Room;

// Function prototypes
void print_help();




int main() {
    Room map[NUM_ROOMS]; // Initialize your map with the appropriate number of rooms

    // Set up your rooms and connections here
    strcpy(map[0].name, "Forest");
    strcpy(map[0].description, "You find yourself in a dense forest. Sunlight filters through the leaves.");
    map[0].north = 1;
    map[0].east = 2;

    strcpy(map[1].name, "Clearing");
    strcpy(map[1].description, "A peaceful clearing with a babbling brook. Birds chirp in the distance.");
    map[1].south = 0;
    map[1].east = 3;

    strcpy(map[2].name, "Cave Entrance");
    strcpy(map[2].description, "An ominous cave entrance beckons. The air grows colder.");
    map[2].west = 0;
    map[2].south = 3;

    strcpy(map[3].name, "Dark Tunnel");
    strcpy(map[3].description, "You step into a dark tunnel. Faint echoes bounce off the walls.");
    map[3].north = 1;
    map[3].east = 4;
    map[3].west = 2;

    strcpy(map[4].name, "Treasure Chamber");
    strcpy(map[4].description, "Golden treasures glitter in this chamber. A locked door leads north.");
    map[4].north = 5;
    map[4].west = 3;
    map[4].has_item = 1;
    strcpy(map[4].item_name, "key");

    strcpy(map[5].name, "Dragon's Lair");
    strcpy(map[5].description, "A fearsome dragon guards its hoard. The exit lies to the south.");
    map[5].south = 4;

    strcpy(map[6].name, "Exit");
    strcpy(map[6].description, "You emerge into daylight. The adventure ends here.");
    map[6].west = 5;

    int current_room = 0;
    char input[MAX_INPUT_SIZE];

    printf("Welcome to the Adventure Game!\n");
    print_help();

    // Game loop
    
  // Game loop
  while (1) {
    printf("\n%s\n", map[current_room].description);
    printf("Enter a command: ");
    fgets(input, MAX_INPUT_SIZE, stdin);
    input[strcspn(input, "\n")] = 0; // Remove newline character

    // Tokenize input to get the command and argument
    char *command = strtok(input, " ");
    char *argument = strtok(NULL, " ");

    if (strcmp(command, "go") == 0) {
      // Handle movement commands
      if (argument != NULL) {
        if (strcmp(argument, "north") == 0) {
          // Check for north exit
          if (map[current_room].north != -1) {
            current_room = map[current_room].north;
          } else {
            printf("There is no exit to the north.\n");
          }
        } else if (strcmp(argument, "south") == 0) {
          if (map[current_room].south != -1) {
            current_room = map[current_room].south;
          } else {
            printf("There is no exit to the south.\n");
          }
        } else if (strcmp(argument, "east") == 0) {
          if (map[current_room].east != -1) {
            current_room = map[current_room].east;
          } else {
            printf("There is no exit to the east.\n");
          }
        } else if (strcmp(argument, "west") == 0) {
          if (map[current_room].west != -1) {
            current_room = map[current_room].west;
          } else {
            printf("There is no exit to the west.\n");
          }
        } else {
          printf("Invalid direction. Please try again.\n");
        }
      } else {
        printf("Please specify a direction.\n");
      }
    } else if (strcmp(command, "look") == 0) {
      // Handle look command (unchanged)
      printf("You look around and see: %s\n", map[current_room].description);
    } else if (strcmp(command, "take") == 0) {
      // Handle take command (unchanged)
    } else if (strcmp(command, "use") == 0) {
      // Handle use command (unchanged)
    } else if (strcmp(command, "quit") == 0) {
      // Handle quit command (unchanged)
      printf("Thank you for playing!\n");
      break;
    } else {
      printf("Unknown command. Type 'help' for a list of commands.\n");
    }
  }

  return 0;
}
   

    


// Function to display available commands
void print_help() {
    printf("Available commands: go [north|south|east|west], look, take [item], use [item], quit\n");
}






