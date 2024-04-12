# ifndef EDFDB_H
# define EDFDB_H
# define EDFMODELDIM 10
# define EDFBLOCKDIM 10
# define EDFVARNAMEDIM 10
# define KEYSTRINGDIM ( EDFMODELDIM + EDFBLOCKDIM + EDFVARNAMEDIM )
# define CONSTRINGDIM ( sizeof ( int ) + sizeof ( char ) + sizeof ( int ) )
struct Edf
  {
  char Model [ EDFMODELDIM ] ;
  char Block [ EDFBLOCKDIM ] ;
  char VarName [ EDFVARNAMEDIM ] ;
  int Offset ;
  char Type ;
  int Tagged ;
  } ;
void CreateKeyString ( char * KeyString ,
                       const struct Edf * Data ) ;
void CreateConString ( char * ConString ,
                       const struct Edf * Data ) ;
void SplitConString ( const char * ConString ,
                      struct Edf * Data ) ;
# endif
