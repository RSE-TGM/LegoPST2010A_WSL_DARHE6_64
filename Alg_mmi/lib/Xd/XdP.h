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
 Privato per gli oggetti Xd (drawing obj).
*/
#ifndef XdP_h
#define XdP_h
#if NeedFunctionPrototypes
#undef NeedFunctionPrototypes
#endif

typedef Boolean (*XdMouseFunc)(
#if NeedFunctionPrototypes
	Draget dr;
	XEvent *ev;
#endif
);

typedef void (*XdProc)(
#if NeedFunctionPrototypes
    void
#endif
);

typedef void (*XdDragetProc)(
#if NeedFunctionPrototypes
	Draget dr;
#endif
);

typedef void (*XdExposeProc)(
#if NeedFunctionPrototypes
	Draget dr;
	XEvent *ev;
#endif
);


typedef Boolean (*XdPickFunc)(
#if NeedFunctionPrototypes
	Draget dr;
	XEvent *ev;
	Boolean type;
#endif
);

typedef void (*XdSelectProc)(
#if NeedFunctionPrototypes
	Draget dr;
	Boolean type;
	Boolean do_expose;
#endif
);
typedef void (*XdGetSizeProc)(
#if NeedFunctionPrototypes
	Draget dr;
        int *xmin;
        int *ymin;
        int *xmax;
        int *ymax;
#endif
);

typedef void (*XdModifyProc)(
#if NeedFunctionPrototypes
        Draget dr;
        int dx;
        int dy;
        int dw;
        int dh;
	XEvent *ev;
#endif
);

typedef void (*XdCopyProc)(
#if NeedFunctionPrototypes
        Draget drsorg;
	Draget drdest;
#endif
);

typedef Boolean (*XdReadFunc)(
#if NeedFunctionPrototypes
    Draget,
    XdGC *      /* contesto di disegno */,
    FILE *     /* args */,
#endif
);

typedef Boolean (*XdWriteFunc)(
#if NeedFunctionPrototypes
    Draget      /* draget */,
    FILE *     /* args */,
#endif
);


#endif /* XdP_h   */
