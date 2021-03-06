/*
    Copyright (C) 2021  TRACEY, Jacob

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU Affero General Public License as
    published by the Free Software Foundation, either version 3 of the
    License, or any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU Affero General Public License for more details.

    You should have received a copy of the GNU Affero General Public License
    along with this program.  If not, see <https://www.gnu.org/licenses/>.
*/﻿

#include "Includes\EntityMaps.h"

struct Entity
{
    unsigned char name[MAX_X / 2];
    unsigned short id;

	struct UserFile player_data_file;
    
    int x, y, z;
    unsigned int controllable, move[COORDS], moved, speed;
    
    struct ScreenObject entity_obj;
    struct ScreenObject entity_name_obj;
} INVALID_ENTITY;

unsigned short entities_loaded = 0;

struct Entity* entities[MAX_ENTITIES];

struct Entity* GetPointerToEntityByID(const unsigned short entityid) {return (entityid < MAX_ENTITIES) ? entities[entityid] : &INVALID_ENTITY;}

unsigned short IsEntityMoving(const short entityid)
{
    struct Entity* entity = GetPointerToEntityByID(entityid);

    if(entity->move[X] != 0 || entity->move[Y] != 0 || entity->move[Z] != 0) return 1;
    return 0;
}
unsigned short IsAnyEntityMoving(short fromid = 1) 
{
	for(int i = fromid; i < MAX_ENTITIES; i++) {for(int ii = 0; ii < COORDS; ii++) if(entities[i]->move[ii] > 0) return i;}
	return 0;
}

void InitializeEntities(void) {for(unsigned int i = 1; i < MAX_ENTITIES; i++) entities[i] = &INVALID_ENTITY;}

void AddEntityToScreen(const struct Entity* entity)
{
    AddScreenObjectToScreen(entity->entity_obj);
    AddScreenObjectToScreen(entity->entity_name_obj);
}

void SetEntityPos(struct Entity* entity, const unsigned int set_x, const unsigned int set_y, const unsigned int set_z)
{
    entity->x = set_x;
    entity->y = set_y;
	entity->z = set_z;
}

struct Entity* CreateEntity(const unsigned char* e_name, unsigned int pos_x, unsigned int pos_y, unsigned int pos_z)
{
	struct Entity* entity = malloc(sizeof(struct Entity));
    if(entities_loaded >= MAX_ENTITIES) *entity = INVALID_ENTITY;
    
    entity->id = ++entities_loaded;
    snprintf((char*) entity->name, MAX_X, "%s", (char*) e_name);
    entity->controllable = 0;
    
    SetEntityPos(entity, pos_x, pos_y, pos_z);

	entity->speed = 5;
	entity->moved = 0;
    
    entity->move[X] = 0;
    entity->move[Y] = 0;
	entity->move[Z] = 0;
    
    entities[entity->id] = entity;

	return entity;
}

void GetEntityScreenTagName(unsigned char* string, const struct Entity entity) {snprintf((char*) string, MAX_X, "%d: %s", entity.id, entity.name);}

void LoadEntityNameTag(struct Entity* entity, struct ScreenObject* entity_name_object)
{
    unsigned char name_tag[MAX_X];
    GetEntityScreenTagName(name_tag, *entity);

    const int start_x = 0 - (GetStrLen(name_tag, MAX_X) / 2) + 1;
    
    InitializeScreenObject(entity_name_object, start_x, -2, (GetStrLen(name_tag, MAX_X) / 2), -2);
       
    entity_name_object->pos_x = entity->x + start_x;
    entity_name_object->pos_z = entity->entity_obj.max_z + 1;

    for(int i = 0; (i < GetStrLenAsInt(name_tag, MAX_X) && (start_x + i) < MAX_X); i++) entity_name_object->obj[OBJECT_TEMPLATE_X + (start_x + i)][OBJECT_TEMPLATE_Z - 2] = name_tag[i];
}

void LoadHumanEntity(struct Entity* entity)
{
    InitializeScreenObject(&entity->entity_obj, 0, 0, 2, 2);

    if(entity->x < 0 || entity->z < 0) return;
    if(entity->x > MAX_X || entity->z > MAX_Z) return;
    
    entity->entity_obj.pos_x = entity->x;
    entity->entity_obj.pos_z = entity->z;

    entity->entity_obj.obj[OBJECT_TEMPLATE_X][OBJECT_TEMPLATE_Z] = '/';
    entity->entity_obj.obj[OBJECT_TEMPLATE_X + 2][OBJECT_TEMPLATE_Z] = '\\';
    
    entity->entity_obj.obj[OBJECT_TEMPLATE_X + 1][OBJECT_TEMPLATE_Z] = '|';
    entity->entity_obj.obj[OBJECT_TEMPLATE_X][OBJECT_TEMPLATE_Z] = '/';
    entity->entity_obj.obj[OBJECT_TEMPLATE_X + 2][OBJECT_TEMPLATE_Z + 1] = '\\';
    
    entity->entity_obj.obj[OBJECT_TEMPLATE_X + 1][OBJECT_TEMPLATE_Z] = 'o';

	GetSkeletonConstraints(human_skeleton_front, &entity->entity_obj.min_x, &entity->entity_obj.min_y, &entity->entity_obj.min_z, &entity->entity_obj.max_x, &entity->entity_obj.max_y, &entity->entity_obj.max_z);

	/*for(int i = 0; i < HUMAN_MAP_PARTS; i++) 
	{
		int x = human_skeleton_front[1][i];
		int z = human_skeleton_front[2][i];
		entity->entity_obj.obj[OBJECT_TEMPLATE_X + x][OBJECT_TEMPLATE_Z + z] = human_skeleton_front[0][i]; 
 	}  */
    LoadEntityNameTag(entity, &entity->entity_name_obj);
        
    AddEntityToScreen(entity);
}

void LoadEntities(void) 
{
    for(unsigned short i = 1; i < MAX_ENTITIES; i++)
    {
        struct Entity* current_entity;
        current_entity = GetPointerToEntityByID(i);
        if(current_entity != &INVALID_ENTITY) LoadHumanEntity(current_entity);
    }
}
