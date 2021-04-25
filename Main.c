#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

#include "Includes\Game.h"

void ProcessMove(const short entityid, const unsigned char* input)
{
    unsigned int index = 0;
    short move_x = 0, move_y = 0, move_z = 0;
    unsigned char direction[MAX_STRING];
    strtoken((char*) direction, input, &index);
    
    if(GetStrLen(direction, MAX_STRING) > MAX_MOVE_DIRECTIONS) return;
    
    unsigned char distance[MAX_STRING];
    strtoken((char*) distance, input, &index);
    
    unsigned short dist = 0;

    if(!GetStrLen(distance, MAX_STRING) || !IsNumeric(distance, GetStrLen(distance, MAX_STRING))) dist = 1; 
    else dist = ((short) strtol((char*) distance, NULL, 0));

    for(unsigned short i = 0; i < dist; i++)
    {
        switch(input[i])
        {
			case 'e': move_z--;
            case 'w': move_y++;
            case 's': move_y--;
            case 'a': move_x--;
            case 'd': move_x++;
			case 'q': move_z++;
            default: return;
        }
    }
    
    struct Entity* entity = GetPointerToEntityByID(entityid);
 
    entity->move[X] = move_x;
    entity->move[Y] = move_y;
	entity->move[Z] = move_z;
}

void OnGameStart(void)
{
    InitializeScreen();
    InitializeEntities();

	SetScreenColor('0', '8');
}

void OnEntityMove(const unsigned short entityid)
{
	struct Entity* entity = GetPointerToEntityByID(entityid);
	short entity_speed = entity->speed;

	if(entity->speed > 0)
	{
		for(short i = 0; i < entity_speed; i++)
		{
			if(entity->move[Z] > 0 && !(entity->moved == Z && (entity->move[X] != 0 || entity->move[Y] != 0)))
			{
				entity->moved;
				entity->z++;

				continue;
			}
			else if(entity->move[X] > 0 && !(entity->moved == X && (entity->move[Z] != 0 || entity->move[Y] != 0)))
			{
				entity->moved = X;
				entity->x++;

				continue;
			}
			else if(entity->move[Y] > 0 && !(entity->moved == Y && (entity->move[X] != 0 || entity->move[Z] != 0)))
			{
				entity->moved = Y;
				entity->y++;

				continue;
			}
		}
	}
    return;
}

void OnText(const unsigned char* string)
{
    if(IsCommandDeliminator(string[0])) OnCommand(0, string);
	if(IsMovement(string[0])) ProcessMove(0, string);
}

void RunGame(void)
{
    do
    {
		InitializeScreen();

        LoadEntities();
        
        unsigned char input[MAX_STRING];
    
        fgets((char*) input, MAX_STRING, stdin);
		snprintf((char*) input, GetStrLen(input, MAX_STRING), "%s", input);

        ClearScreen();
        
		OnText(input);

        PrintScreen();
    } while(!exit_game);
}

int main(void)
{
    OnGameStart();

	struct Entity* entity_pointer = CreateEntity(((unsigned char*) "Jim"), 15, 0, 15);

	RunGame();

	free(entity_pointer);
    
    return 0;
}
