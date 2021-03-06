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

inline void OnGameStart(void);
inline void OnCommand(unsigned int issuer, const unsigned char* string);
inline void OnEntityMove(const unsigned short entityid);
inline void OnText(const unsigned char* string);

int exit_game = 0;

#include "Includes\Defines.h"
#include "Includes\Utilities.h"
#include "Includes\FileHandler.h"
#include "Includes\Screen.h"
#include "Includes\Entities.h"
#include "Includes\CommandProcessor.h"
