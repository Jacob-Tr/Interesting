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

unsigned char screen[MAX_X][MAX_Z];
unsigned int screen_objects = 0;

void SetScreenColor(const unsigned char console, const unsigned char text)
{
	unsigned char color_string[9] = "COLOR ";
	snprintf((char*) color_string, GetStrLen(color_string, 9) + 3, "%s%c%c", color_string, console, text);

	system((char*) color_string);
}

void InitializeScreen(void) {for(unsigned int i = 0; i < MAX_Z; i++) for(unsigned int ii = 0; ii < MAX_X; ii++) screen[ii][i] = ' ';}

void ChangePixel(const unsigned char val, const unsigned int x, const unsigned int z) {screen[x][z] = val;}

void AddStringAt(const unsigned char* string, const unsigned int coord_type, const unsigned int x, const unsigned int z)
{
    // Deprecated: Use ScreenObject.
    for(unsigned int i = 0; i < GetStrLen(string, MAX_STRING); i++)
    {
        if(coord_type == X) 
        {
            if(x + i >= MAX_X) break;
            else ChangePixel(string[i], x + i, z);
        }
        else
        {
            if(z + i >= MAX_Z) break;
            else ChangePixel(string[i], x, z + i);
        }
    }
}

void PrintScreen(void) {for(unsigned int i = MAX_Z; i >= 0; i++) for(int ii = 0; ii < MAX_X; ii++) printf("%c", screen[ii][i]);}
void ClearScreen(void) {system("cls");}

struct ScreenObject
{
	int object_id;
    int max_x, max_y, max_z, min_x, min_y, min_z;
    unsigned int pos_x, pos_y, pos_z;
    unsigned char obj[MAX_X][MAX_Z];
} INVALID_OBJECT;

struct ScreenObject* object_library[MAX_SCREEN_OBJECTS];

void InitializeScreenObject(struct ScreenObject* screen_object, const int set_min_x, const int set_min_z, const int set_max_x, const int set_max_z) 
{
    for(int i = MAX_Z - 1; i >= 0; i--) for(int ii = 0; ii < MAX_X; ii++) screen_object->obj[ii][i] = ' ';
 
    screen_object->min_x = set_min_x;
    screen_object->min_z = set_min_z;
    screen_object->max_x = set_max_x;
    screen_object->max_z = set_max_z;

	screen_object->object_id = ++screen_objects;
	object_library[screen_objects] = screen_object;
}

struct ScreenObject* GetPointerToObjectByID(unsigned int object_id) {return object_library[object_id];};
void SetObjectID(struct ScreenObject* screen_object, unsigned int object_id) {object_library[object_id] = screen_object;}

void AddScreenObjectToScreen(const struct ScreenObject screen_object)
{
	const int x = screen_object.min_x, z = screen_object.min_z;
	const int x_max = screen_object.max_x, z_max = screen_object.max_z; 

	for(int i = z_max; i > z; i--)
	{
		if(i > MAX_Z) continue;
		for(int ii = x; ii < x_max; ii++)
		{
			if(ii > MAX_X) continue;
			char new_char = screen_object.obj[OBJECT_TEMPLATE_X + ii][OBJECT_TEMPLATE_Z + i];
			if(new_char != ' ') ChangePixel(new_char, screen_object.pos_x + ii, OBJECT_TEMPLATE_Z + (z_max - i));
		}
	}
}

/*void AddScreenObjectToScreen(const struct ScreenObject screen_object)
{
    int x = screen_object.min_x, z = screen_object.min_z;
    int diff_x = (screen_object.max_x - x), diff_z = (screen_object.max_z - z);

    for(int i = z; i <= diff_z; i++) 
    {
        for(int ii = x; ii <= diff_x; ii++)
        {
			unsigned char new_char = screen_object.obj[OBJECT_TEMPLATE_X + (x + ii)][OBJECT_TEMPLATE_Z + (z + i)];
			if(new_char == ' ') continue;

			if((screen_object.pos_x + ii) < 0 || (screen_object.pos_x + ii) > MAX_X) continue;
			if(((MAX_Z - screen_object.pos_z) - i) < 0 || ((MAX_Z - screen_object.pos_z) + i) > MAX_Z) continue;
            screen[screen_object.pos_x + ii][(MAX_Z - 1) - (screen_object.pos_z + i)] = new_char;
        }
    }
}*/
