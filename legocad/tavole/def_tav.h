/**********************************************************************
*
*       C Header:               def_tav.h
*       Subsystem:              1
*       Description:
*       %created_by:    lomgr %
*       %date_created:  Wed Oct  8 17:22:06 1997 %
*
**********************************************************************/

/* file def_tav.h */

/* Contiene la definizione degli array relativi alle tavole acqua/vapore */
/* fumi, ... */

/* L'array funzioni_vapore[] di strutture Struct_toggle contiene */ 
/* attualmente 14 elementi (cioe' funzioni): 			 */

Struct_toggle funzioni_vapore[] = {
	
	{ "T(P,S)", 
	  "Calculation of temperature [^C]", 
	  2, 
	  1, 
	  {"Pressure [Bar]", "Entropy [KJ/Kg/^C]"}, 
	  {"Temperature [^C]"},
	  {"P", "S"}, 
	  {"T"},
          chiama_tavH2O,
          1 },
	
	{ "T(P,H)", 
	  "Calculation of temperature [^C]", 
	  2, 
	  1,
	  {"Pressure [Bar]", "Entalpy [KJ/Kg]"},
	  {"Temperature [^T]"},
	  {"P", "H"}, 
	  {"T"},
          chiama_tavH2O,
          2 },
	
	{ "TSAT(P)", 
	  "Calculation of saturation temperature [^C]", 
	  1, 
	  1,
	  {"Pressure [Bar]"}, 
	  {"Temperature [^C]"}, 
	  {"P"}, 
	  {"T"},
          chiama_tavH2O,
          3 },

	{ "S(P,H)", 
	  "Calculation of entropy [KJ/Kg/^C]", 
	  2, 
	  1,
	  {"Pressure [Bar]", "Entalpy [KJ/Kg]"}, 
	  {"Entropy [KJ/Kg/^C]"},
	  {"P", "H"}, 
	  {"S"},
          chiama_tavH2O,
          4 },

	{ "S(P,T,Y)", 
	  "Calculation of entropy [KJ/Kg/^C]", 
	  3, 
	  1,
	  {"Pressure [Bar]", "Temperature [^C]", "Steam ratio"}, 
	  {"Entropy [KJ/Kg/^C]"}, 
	  {"P", "T", "Y"}, 
	  {"S"},
          chiama_tavH2O,
          5 },

	{ "H(P,S)", 
	  "Calculation of entalpy [KJ/Kg]", 
	  2, 
	  1,
	  {"Pressure [Bar]", "Entropy [KJ/Kg/^C]"}, 
	  {"Entalpy [KJ/Kg]"},
	  {"P", "S"}, 
	  {"H"},
          chiama_tavH2O,
          6 },

	{ "H(P,T,Y)", 
	  "Calculation of entalpy [KJ/Kg]", 
	  3, 
	  1,
	  {"Pressure [Bar]", "Temperature [^C]", "Steam ratio"}, 
	  {"Entalpy [KJ/Kg]"}, 
	  {"P", "T", "Y"}, 
	  {"H"},
          chiama_tavH2O,
          7 },

	{ "RO(P,H)",
	  "Calculation of density RO [Kg/m3]",
	  2,
	  1,
	  {"Pressure [Bar]", "Entalpy [KJ/Kg]"},
	  {"Density RO [Kg/m3]"},
	  {"P", "H"},
	  {"RO"},
          chiama_tavH2O,
          8 },

	{ "RO(P,T,Y)",
	  "Calculation of density RO [Kg/m3]",
	  3,
	  1,
	  {"Pressure [Bar]", "Temperature [^C]", "Steam ratio"},
	  {"Density RO [Kg/m3]"},
	  {"P", "T", "Y"},
	  {"RO"},
          chiama_tavH2O,
          9 },

	{ "CP(P,T,Y)",
	  "Calculation of specific heat CP [J/Kg/^C]",
	  3,
	  1,
	  {"Pressure [Bar]", "Temperature [^C]", "Steam ratio"},
	  {"Specific heat CP [J/Kg/^C]"},
	  {"P", "T", "Y"},
	  {"CP"},
          chiama_tavH2O,
          10 },

	{ "H* H**",
	  "Calculation of entalpy of water and satured steam [KJ/Kg]",
	  1,
	  2,
	  {"Pressure [Bar]"},
	  {"Entalpy of satured water [KJ/Kg]", 
	   "Entalpy of satured steam [KJ/Kg]"},
	  {"P"},
	  {"H*", "H**"},
          chiama_tavH2O,
          11 },

	{ "S* S**",
	  "Calculation of entropy of water and satured steam",
	  1,
	  2,
	  {"Pressure [Bar]"},
	  {"Entropy of satured water [KJ/Kg/^C]",
	   "Entropy of satured steam {KJ/Kg/^C]"},
	  {"P"},
	  {"S*", "S**"},
          chiama_tavH2O,
          12 },

	{ "RO* RO**",
	  "Calculation of density of water and satured steam",
	  1,
	  2,
	  {"Pressure [Bar]"},
	  {"Density of satured water [Kg/m3]",
	   "Density of satured steam [Kg/m3]"},
	  {"P"},
	  {"RO*", "RO**"},
          chiama_tavH2O,
          13 },

	{ "Y(P,H)",
	  "Calculation of steam ratio",
	  2,
	  1,
	  {"Pressure [Bar]", "Entalpy [KJ/Kg]"},
	  {"Steam ratio"},
	  {"P" ,"H"},
	  {"Y"},
          chiama_tavH2O,
          14 }
			};

/* Numero di strutture definite in funzioni_vapore[]: */
int num_funz_vapore = sizeof(funzioni_vapore) / sizeof(funzioni_vapore[0]);

/*----------------------------------------------------------------------*/
/* L'array funzioni_gas[] di strutture Struct_toggle contiene */ 
/* attualmente 1 elemento fantoccio (cioe' funzioni):         */

Struct_toggle funzioni_gas[] = {
	
	{ "", 
	  "", 
	  0, 
	  0, 
	  {""}, 
	  {""},
	  {""}, 
	  {""},
          NULL,
          0 } 
				};
	
/* Numero di strutture definite in funzioni_gas[]: */
int num_funz_gas = sizeof(funzioni_gas) / sizeof(funzioni_gas[0]);

