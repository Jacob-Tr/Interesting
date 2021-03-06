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

#define HUMAN_MAP_PARTS 7

const unsigned char human_skeleton_front[][HUMAN_MAP_PARTS] =
{
	{'/', ' ', '\\', '/', '|', '\\', 'o'},
	{0, 1, 2, 0, 1, 2, 1},
	{0, 0, 0, 1, 1, 1, 2}
};

int GetSkeletonConstraints(const unsigned char skeleton[3][7], int* min_x, int* min_y, int* min_z, int* max_x, int* max_y, int* max_z)
{
	*min_x = MAX_X;
	*min_y = MAX_Y;
	*min_z = MAX_Z;

	if(*min_x > *max_x || *min_y > *max_y || *min_z > *max_z) return 0;

	for(int i = 0; i < HUMAN_MAP_PARTS; i++)
	{
		if(skeleton[1][i] < *min_x) *min_x = i;
		if(skeleton[1][i] > *max_x) *max_x = i;
		if(skeleton[2][i] < *min_z) *min_z = i;
		if(skeleton[2][i] > *max_z) *max_z = i;
	}

	return 1;
}
