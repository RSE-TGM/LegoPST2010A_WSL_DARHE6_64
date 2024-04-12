/**********************************************************************
*
*       C Header:               %name%
*       Subsystem:              %subsystem%
*       Description:
*       %created_by:    %
*       %date_created:  %
*
**********************************************************************/
/*
   modulo XdGeom.h
   tipo 
   release 5.1
   data 11/13/95
   reserved @(#)XdGeom.h	5.1
*/
/*
 XdGeom.h
	contiene le definizione delle routine geometriche usate
	internamente ai draget
*/
extern Region RegionIntorno(Position, Position, float);
extern Region RegionLineIntorno(Position, Position,Position, Position,float);
extern Region RegionClip(XEvent *);
extern Region RegionClipBox(Region );
extern Boolean XdIntersectRectangle(int, int, int, int,
				   int, int, int, int);
