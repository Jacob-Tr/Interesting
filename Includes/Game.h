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
