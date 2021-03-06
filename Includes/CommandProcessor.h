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

#define CMD:%0(%1)\
	void %0(%1)

int SendCommand(const char* command_text)
{
	if(command_text == NULL || GetStrLen((unsigned char*) command_text, MAX_STRING) == 0) return 0;

	unsigned char command[MAX_COMMAND_TEXT];

	if(command_text[0] != '/') snprintf((char*) command, MAX_STRING, "/%s", command_text);
	else snprintf((char*) command, MAX_STRING, "%s", command_text);

	OnCommand(SERVER_ID, command);
	return 1;
}

void OnCommand(const unsigned int issuer, const unsigned char* string)
{
    unsigned char command_text[MAX_COMMAND_TEXT] = "";
    unsigned int index = 0;

    strtoken((char*) command_text, string, &index);

    if(strncmp((char*) command_text, "/quit", MAX_COMMAND_TEXT) == 0) exit_game = 1;
	if(strncmp((char*) command_text, "/q", MAX_COMMAND_TEXT) == 0) SendCommand("quit");
    if(strncmp((char*) command_text, "/controlentity", MAX_COMMAND_TEXT) == 0)
    {
		return;
    }
    if(strncmp((char*) command_text, "/printtext", MAX_COMMAND_TEXT) == 0)
    {
		unsigned char params[MAX_COMMAND_TEXT] = "";
		for(unsigned int i = index; i < GetStrLen(string, MAX_COMMAND_TEXT); i++) {snprintf((char*) params, GetStrLen(string, MAX_COMMAND_TEXT), "%s%c", params, string[i]);}

        AddStringAt(params, Y, 25, 5);
		return;
    }
}
