
#include <string.h>
#include "edfdb.h"

void CreateKeyString ( char * KeyString ,
                       const struct Edf * Data )
  {
  memset ( KeyString ,
           0 ,
           KEYSTRINGDIM ) ;
  memcpy ( KeyString ,
           Data -> Model ,
           EDFMODELDIM ) ;
  KeyString += EDFMODELDIM ;
  memcpy ( KeyString ,
           Data -> Block ,
           EDFBLOCKDIM ) ;
  KeyString += EDFBLOCKDIM ;
  memcpy ( KeyString ,
           Data -> VarName ,
           EDFVARNAMEDIM ) ;
  }
void CreateConString ( char * ConString ,
                       const struct Edf * Data )
  {
  memset ( ConString ,
           0 ,
           CONSTRINGDIM ) ;
  memcpy ( ConString ,
           & Data -> Offset ,
           sizeof ( int ) ) ;
  ConString += sizeof ( int ) ;
  memcpy ( ConString ,
           & Data -> Type ,
           sizeof ( char ) ) ;
  ConString += sizeof ( char ) ;
  memcpy ( ConString ,
           & Data -> Tagged ,
           sizeof ( int ) ) ;
  }
void SplitConString ( const char * ConString ,
                      struct Edf * Data )
  {
  memcpy ( & Data -> Offset ,
           ConString ,
           sizeof ( int ) ) ;
  ConString += sizeof ( int ) ;
  memcpy ( & Data -> Type ,
           ConString ,
           sizeof ( char ) ) ;
  ConString += sizeof ( char ) ;
  memcpy ( & Data -> Tagged ,
           ConString ,
           sizeof ( int ) ) ;
  }
/* EOF. */
