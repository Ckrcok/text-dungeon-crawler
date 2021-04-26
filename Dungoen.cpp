#include "Dungoen.h"
#include "Player.h"
#include <iostream>

using namespace std;
Dungeon::Dungeon(Player p)
{
    player = p;
}

void Dungeon::printActions(int numActions, string actions[]){
    cout << " Choose an action : \n";
    for (int i = 0; i < numActions; i++){
        cout<< actions[i]<<"\n";
    }

}



void Dungeon::handleFightActions (GameCharacter * enemy){
        string actions[] = {
        "A. Attack" ,
        "B. Retreat",
        };
    while(true){
        printActions(2, actions);
        string input;
        cin >> input;
        //handle player action
         if  (input == "A"){
           //attack
           int damage = enemy->takeDamage(player.attack);
           cout << " you attack does " << damage<< "damage \n";
        }else if (input == "B") { 
            player.changeRooms(player.previousRoom);
            enterRoom(player.currentRoom);
            return;
        }
         else  { 
            cout << "incorrect choice.\n";
        }
        //check if enemy is dead
        if(enemy ->checkIsDead ()){
         cout << " you WIN you have defeted " << enemy->name<< "\n";
         player.increaseStats(10, 5, 5);
         player.currentRoom->clearEnemies();
         return;
        }
        //handle enemy actions
        int damage = player.takeDamage(enemy->attack);
        cout << enemy->name << "'s attack does " << damage<< "damage \n";
        cout << " you now have have " << player.currentHealth << "\n";
        if (player.checkIsDead()){
        return;
        }

    }
}

void Dungeon::handleRoomWithEnemy(Room * room){
    GameCharacter enemy = room->enemies.front();
cout << " You Enter the room and see a "<< enemy.name << "\n";
    string actions[] = {
        "A. Fight the" + enemy.name,
        "B. Go back to previos room",
        };
    while(true){
        printActions(2, actions);
        string input;
        cin >> input;
         if  (input == "A"){
           //fight
           handleFightActions(&enemy);
            return;
        }else if (input == "B") { 
            player.changeRooms(player.previousRoom);
            enterRoom(player.currentRoom);
            return;
        }
         else  { 
            cout << "incorrect choice.\n";
        }
    }
    
}

void Dungeon::handleEmptyRoom(Room * room){
    cout << " You Enter the room but it is empty. \n";
    string actions[] = {"A. Move to another room"};
    while(true){
        printActions(1, actions);
        string input;
        cin >> input;
        if (input == "A"){
            //move actions
            return; 
        }else { 
            cout << "incorrect choice.\n";
        }
    }
}





void Dungeon::handleLootActions(Room * room){
    Item item = room->items.front();
    int size = room->items.size();
    player.lootRoom(room);
    room -> clearLoot();
    for (int i = 0; i < size;  i++) {
    cout << "You open the chest and find a " << item.name << ".\n";
    cout << "Your health is now " << player.currentHealth << ", your attack is now "<< player.attack << ", and your defence " << player.defence << "\n"; 
    }
        
}

void Dungeon::handleRoomWithChest(Room * room){
cout << " You Enter the room and see a large chest in the middle. \n";
    string actions[] = {
        "A. loot the chest",
        "B. Move to another room",
        };
    while(true){
        printActions(2, actions);
        string input;
        cin >> input;
         if  (input == "A"){
            handleLootActions(room);
            return;
        }else if (input == "B") { 
            return;
        }
         else  { 
            cout << "incorrect choice.\n";
        }
    }
    
}



void Dungeon::enterRoom(Room * room){
    if (room ->enemies.size() !=0 ){
        //handle room with enemy
        handleRoomWithEnemy(room);
    }else if (room -> items.size() != 0){
        //handle room with chest
        handleRoomWithChest(room);
    }else {
        //handle empty room
        handleEmptyRoom(room);
    }
}
            
 void  Dungeon::handleMovementActions(Room * room ) {
     while (true){
    if (room->pos == 0){
            string actions[]= {"A.Move Right", "B. Move down"};
            printActions(2, actions);
            string input;
            cin >> input;
            if(input =="A"){
             player.changeRooms(&rooms[1]);
            } else if (input == "B") {
             player.changeRooms(&rooms[2]);
             return;
            } else{
                cout << "incorrect choice.\n";
            }
        } else if (room->pos == 1){
             string actions[]= {"A.Move Left"};
         printActions(1, actions);
         string input;
         cin >> input;
            if(input =="A"){
             player.changeRooms(&rooms[0]);
            } else{
                cout << "incorrect choice.\n";
            }
        } else if (room->pos == 2){
            string actions[]= {"A.Move up", "B. Move Right"};
            printActions(2, actions);
            string input;
            cin >> input;
            if(input =="A"){
             player.changeRooms(&rooms[0]);
            } else if (input == "B") {
             player.changeRooms(&rooms[3]);
             return;
            } else{
                cout << "incorrect choice.\n";
            }
        } else {
            string actions[]= {"A.Move Left"};
            printActions(1, actions);
            string input;
            cin >> input;
            if(input =="A"){
            player.changeRooms(&rooms[2]);
            } else {
              cout << "incorrect choice.\n";
            }
        }

    }

     
 }

 int Dungeon::performEndGameLogic(){
    string actions[] = {"A. Yes", "B.No"};
    while(true){
    printActions(2, actions);
    string input;
    cin >> input;
    if(input == "A"){
        return 1; 
    }else if (input == "B"){
        return 0 ;
    } else {
        cout << "incorrect choice.\n";
    }
    
    }
 }

int Dungeon::runDungeon() {
    cout << " Welcome to the dungeon! Inside you will find there chest and enemies  \n";
    // present actions 
    player.currentRoom = &rooms[0];
    player.previousRoom = &rooms[0];
while(true){
    // enter the room
    enterRoom(player.currentRoom);
    if (player.checkIsDead()){
        //lose the game
        cout << "Game Over! Try agian? \n";
        return performEndGameLogic();
    } else {
        if (player.currentRoom->isExit){
            if(player.currentRoom->enemies.size() == 0){
                //win the game
                cout << "You Win! Try agian? \n";
                return performEndGameLogic();
            }
        }
    }
    // take action - enter sequence
    // check if dead
    // movment options
    handleMovementActions(player.currentRoom);

}

}