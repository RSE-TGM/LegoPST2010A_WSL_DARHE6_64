/***************************************************************************
    grafics
****************************************************************************/

#include "windows.h"
#include "resource.h"
#include "definit.h"
#include "stdio.h" 
#include "stdlib.h"
#include "string.h"
#include "math.h"

LPSTR PrgName = "Grafics";

#define SIZBUFFER 100
#define MAXCURVA  1000

char bufferqq[255];
HDC hMemoryDC;                         
BITMAP Bitmap;                         

HANDLE hAccTable;  
HANDLE hArrow;
HANDLE hHourGlass; 
HANDLE hCross;
HANDLE hSaveCursor;
HWND hwnd;         
HANDLE hInst;
HANDLE hCurva;
HANDLE hBuffer;
HANDLE hGroup;

HMENU hMenu;

HPEN hSolidBlackPen;
HPEN hSolidTBlackPen;
HPEN hSolidGridPen;
HPEN hSolidCGridPen;
HPEN hSolidRedPen;
HPEN hSolidBluePen;
HPEN hSolidGreenPen;
HPEN hSolidGrayPen;
HPEN hSolidBluMarinePen;
HPEN hSolidTGrayPen;
HPEN hSolidViolPen;
HPEN hSolidWhitePen;
HPEN hSolidTWhitePen;
HPEN hOldPen;
HBRUSH hGrayBrush;
HBRUSH hBluMarineBrush;
HBRUSH hGreenBrush;
HBRUSH hOldBrush;
HFONT hMFont, holdFont;

LPSTR pCurva;      
double *pBuffer;
#define MAXSELECT   4
double *pOrd[MAXSELECT+2];
HANDLE hOrd[MAXSELECT+1];

HANDLE hfile  = INVALID_HANDLE_VALUE;
HANDLE hGfile;

char FileName[128];
char OpenGName[128];
char DefGExt[] = ".g22";
char str[255];

int ncurve = 0;
char titolo[80];
LPSTR curva[MAXCURVA];
int ngroup = 0;
int nAgroup;

struct stGroup
{
    int nselect;
    char descr[80];
    char select[MAXSELECT][80];
    double MaxOrdM[MAXSELECT+1];
    double MinOrdM[MAXSELECT+1];
    double MaxOrdA[MAXSELECT+1];
    double MinOrdA[MAXSELECT+1];
    int Grid, Auto, Scale, Color;
}; 

struct stGroup *pGroup;

int nselect = 0;

int iselect[MAXSELECT];
char SELECT[MAXSELECT][80];

int ifind = 0;
char PSelect[128];

int XX, XX0 = 0, XX1 = 0;
int YY, YY0 = 0, YY1 = 0;

int PixelX = 440;
int PixelY = 248;  
int WsizeX = 526;
int WsizeY = 366;  
int PixelS = 5;
int retidx = 55, retidy = 62;
int Dcont = 80;

int Grid  = 1;
int Scale = 0;
int Value = 0;
int Zoom  = 0;
int Auto  = 1;
int Color = 1;

int Refresh = 0;
int Bscal;

int Rcolor[MAXSELECT] = {255,   0,   0, 255};
int Gcolor[MAXSELECT] = {255, 255, 255, 255};
int Bcolor[MAXSELECT] = {  0,   0, 255, 255};

long sizbuffer;
int npunti;

double MaxOrdM[MAXSELECT+1];
double MinOrdM[MAXSELECT+1];
double MinOM, MaxOM;
double MaxOrdA[MAXSELECT+1];
double MinOrdA[MAXSELECT+1];
double MinOA, MaxOA;
double MaxOrd[MAXSELECT+1];
double MinOrd[MAXSELECT+1];
double MinO, MaxO;
int Poini, Pofin;

int bTrack = 0;
int OrgX = 0;                               
int PrevX = 0;  
int PrevXflg = 0;                              
int X = 0, Y = 0;                           

POINT ptCursor;                             
int repeat = 1;                             
int saveGroup = 0;

int _givefile;
int _givevar;
int _givegrid;
int _givescale;
int _givecolor;
int _givecomm;
char _filename[128];
char _varname[MAXSELECT][9];

int FirstCall = 0;
char CommandLine[200];

int idTimer = -1;
int secTimer = 10;
HWND hNextWnd;

WORD GraficsFMT;
struct graficsDB
{
   int n;
   int np[MAXSELECT];
};
struct graficsDB *grafics;
LPSTR  ClipData;
HANDLE hClipData;

int xpoint, ypoint;
double temValue;
int iNumColors;
HBITMAP hBitmapBK;


/****************************************************************************

    FUNCTION: WinMain(HANDLE, HANDLE, LPSTR, int)

    PURPOSE: calls initialization function, processes message loop

****************************************************************************/

int WINAPI WinMain(hInstance, hPrevInstance, lpCmdLine, nCmdShow)
HANDLE hInstance;
HANDLE hPrevInstance;
LPSTR lpCmdLine;
int nCmdShow;
{
    MSG msg;

    if (FirstCall != 1)
    {
        FirstCall = 1;
        lstrcpy((LPSTR) CommandLine, lpCmdLine);
//MessageBox(GetFocus(), lpCmdLine, "prima", MB_OK | MB_ICONEXCLAMATION);
        DecodeCmdLine(CommandLine);
//MessageBox(GetFocus(), _filename, "decode di filename", MB_OK | MB_ICONEXCLAMATION);

    }

    if (!hPrevInstance)
        if (!InitApplication(hInstance))
            return (FALSE);

    if (!InitInstance(hInstance, nCmdShow))
        return (FALSE);

    while (GetMessage(&msg, NULL, 0, 0)) 
    {
    /* Only translate message if it is not an accelerator message */

        if (!TranslateAccelerator(hwnd, hAccTable, &msg))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg); 
        }
    }

    return (msg.wParam);
}


/****************************************************************************

    FUNCTION: InitApplication(HANDLE)

    PURPOSE: Initializes window data and registers window class

****************************************************************************/

BOOL InitApplication(hInstance)
HANDLE hInstance;
{
    WNDCLASS  wc;
	HDC hDC;
	BOOL bSuccess;
	int iRasterCaps;

    wc.style = 0;
    wc.lpfnWndProc = MainWndProc;
    wc.cbClsExtra = 0;
    wc.cbWndExtra = 0;
    wc.hInstance = hInstance;
    wc.hIcon = LoadIcon(hInstance, "Grafics");
    wc.hCursor = NULL;
    wc.hbrBackground = GetStockObject(WHITE_BRUSH); 
    wc.lpszMenuName =  "GraficsMenu";
    wc.lpszClassName = "GraficsWClass";

    hDC = GetDC(NULL);
    iRasterCaps = GetDeviceCaps(hDC, RASTERCAPS);
    iRasterCaps = (iRasterCaps & RC_PALETTE) ? TRUE : FALSE;
 
    bSuccess = RegisterClass(&wc);

    if (iRasterCaps)
	    iNumColors = GetDeviceCaps(hDC, SIZEPALETTE);
    else
	    iNumColors = GetDeviceCaps(hDC, NUMCOLORS);

    ReleaseDC(NULL, hDC);

    return (bSuccess);
}


/****************************************************************************

    FUNCTION:  InitInstance(HANDLE, int)

    PURPOSE:  Saves instance handle and creates main window

****************************************************************************/

BOOL InitInstance(hInstance, nCmdShow)
HANDLE          hInstance;
int             nCmdShow;
{
    hInst = hInstance;

    hArrow     = LoadCursor(NULL, IDC_ARROW);
    hHourGlass = LoadCursor(NULL, IDC_WAIT);
    hCross     = LoadCursor(NULL, IDC_CROSS);
    hAccTable  = LoadAccelerators(hInst, "GraficsAcc");

    hwnd = CreateWindow(
        "GraficsWClass",
        "Grafics - (no file)",
        WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, 
        CW_USEDEFAULT, 
        WsizeX, 
        WsizeY, 
        NULL,
        NULL,
        hInstance,
        NULL
    );

    if (!hwnd)
        return (FALSE);

    ShowWindow(hwnd, nCmdShow);
    UpdateWindow(hwnd);
    return (TRUE);
}

/****************************************************************************

    FUNCTION: MainWndProc(HWND, unsigned, WORD, LONG)

    PURPOSE:  Processes messages

    MESSAGES:

        WM_COMMAND    - application menu (About dialog box)
        WM_DESTROY    - destroy window

    COMMENTS:

        WM_COMMAND processing:

            IDM_OPEN - query to save current file if there is one and it
                       has been changed, open a new file.

            IDM_ABOUT - display "About" box.

****************************************************************************/

LRESULT CALLBACK MainWndProc(hWnd, message, wParam, lParam)
HWND hWnd;
unsigned message;
WPARAM wParam;
LPARAM lParam;
{
    FARPROC lpProcAbout, lpVariSel, lpSetScale, lpMemoGroup, 
            lpGroupSel, lpRefrTime;
    PAINTSTRUCT ps;
    TEXTMETRIC textmetric;
    HDC hDC;
    HBITMAP hBitmap;
    HANDLE hOldBitmap;
    int i, j, k, m, hvari, hscale, hgruppi, hrefrtime;
    int xcalc, ycalc;
    int xPcalc, yPcalc;
    double divo, diva, dtem;
    double minore, maxore;
    double minz, maxz;
    int delta[MAXSELECT] = {2, 5, 8, 11};
    int XX0g, XX1g, YY0g, YY1g;
    int Xcirc, Xrect;
    int ku, ki;
    SIZE retSize;
	char name[20], descr[200];
    int lstr, Maxlstr, lunNome;
    RECT rect;

    switch (message)
    {
        case WM_COMMAND:
            switch (LOWORD(wParam)) 
            {
                case IDM_ABOUT:
                    if (idTimer != -1);
                        KillTimer(hWnd, 1);

                    lpProcAbout = MakeProcInstance(About, hInst);
                    DialogBox(hInst, "AboutBox", hWnd, lpProcAbout);
                    FreeProcInstance(lpProcAbout);
                    if (idTimer != -1);
	                idTimer = SetTimer(hWnd, 1, secTimer*1000, (FARPROC) NULL);
                    break;

                case IDM_OPEN:
                    if (idTimer != -1) 
					{
                        idTimer = -1;
                        KillTimer(hWnd, 1);
		            }

	                hMenu = GetMenu(hWnd);
                    EnableMenuItem(hMenu, IDM_VARIA, MF_GRAYED);
                    EnableMenuItem(hMenu, IDM_SETSCALE, MF_GRAYED);
                    EnableMenuItem(hMenu, IDM_MEMOGROUP, MF_GRAYED);
                    EnableMenuItem(hMenu, IDM_GROUP, MF_GRAYED);
                    EnableMenuItem(hMenu, IDM_FULLW, MF_GRAYED);

	                if (Value == 1)
                    {
                        CheckMenuItem(hMenu, IDM_VALUE, MF_UNCHECKED);
	                    Value = 0;
                    }

	            	if (hfile != INVALID_HANDLE_VALUE) 
                    {
	                	CloseHandle(hfile);
	                	CloseHandle(hGfile);
	 	        		hfile = INVALID_HANDLE_VALUE;
                        GlobalFree(hCurva);
                        GlobalFree(hGroup);
                        LocalFree(hBuffer);
	                	for (i=0; i<MAXSELECT+1; i++)
                            GlobalFree(hOrd[i]);
		    		}

                    /* Open the file and get its handle */
                    hfile = OpenGRFdlg();
                    if (hfile == INVALID_HANDLE_VALUE) 
                    {
/* GUAG                       SetWindowText(hWnd, "Grafics - (no file)");
  	                    InvalidateRect(hWnd, NULL, TRUE);  
*/                        return (0);
	                }
                    ncurve  = 0;
	                nselect = 0;

                    /* Set up a new buffer and window title */

                    sprintf(str, "Grafics - %s", FileName);
                    SetWindowText(hWnd, str);

                    hSaveCursor = SetCursor(hHourGlass);
		            if (ReadHeaderF22(hWnd) == 0)
                    {
	                    CloseHandle(hfile);
	                    CloseHandle(hGfile);
                        hfile = INVALID_HANDLE_VALUE;
                        ncurve  = 0;
                        SetWindowText(hWnd, "Grafics - (no file)");
  	                    InvalidateRect(hWnd, NULL, TRUE);  
                        SetCursor(hSaveCursor);  
	                    return(0);
	    	        }

		            if (ReadG22(hWnd) == 0)
                    {
	                    CloseHandle(hfile);
	                    CloseHandle(hGfile);
                        GlobalFree(hCurva);
                        LocalFree(hBuffer);
	                    for (i=0; i<MAXSELECT+1; i++)
                            GlobalFree(hOrd[i]);

	 	                hfile = INVALID_HANDLE_VALUE;
                        ncurve  = 0;
                        SetWindowText(hWnd, "Grafics - (no file)");
  	                    InvalidateRect(hWnd, NULL, TRUE);  
                        SetCursor(hSaveCursor);  
	                    return(0);
		            }

                    SetCursor(hSaveCursor);  

                    EnableMenuItem(hMenu, IDM_VARIA, MF_ENABLED);
                    EnableMenuItem(hMenu, IDM_GROUP, MF_ENABLED);
                    EnableMenuItem(hMenu, IDM_FULLW, MF_ENABLED);
  	                InvalidateRect(hWnd, NULL, TRUE);  
                    break;

                case IDM_COPY:
                    if (idTimer != -1)
                        KillTimer(hWnd, 1);

                    hDC = GetDC(hWnd);
	                hMemoryDC = CreateCompatibleDC(hDC);
 	                hBitmap = CreateCompatibleBitmap(hDC, WsizeX-2, WsizeY-2);
		            hOldBitmap = SelectObject(hMemoryDC, hBitmap);
		            BitBlt(hMemoryDC, 0, 0, 
                           WsizeX-2, WsizeY-2, 
	                       hDC, 1, 1, SRCCOPY);

                    for (;;)
                    {
                        if (OpenClipboard(hWnd)) 
                        {
                            EmptyClipboard();
                            SetClipboardData(CF_BITMAP, hBitmap);
                            CloseClipboard();
                            break;
                        }
                    }

		            DeleteDC(hMemoryDC);
                    ReleaseDC(hWnd, hDC);
                    if (idTimer != -1)
  	                    idTimer = SetTimer(hWnd, 1, secTimer*1000, (FARPROC) NULL);

                    break;


                case IDM_EXIT:
                    if (idTimer != -1) 
                        KillTimer(hWnd, 1);

                    /* save groups */
                    if (saveGroup)
                        if (MessageBox(hWnd, "Save GROUP file", PrgName,
                                       MB_YESNO | MB_ICONQUESTION) == IDYES)
		            WriteG22();
		
                    DestroyWindow(hWnd);
                    break;
    

                case IDM_VARIA:
                    if (idTimer != -1) 
					{
                        idTimer = -1;
                        KillTimer(hWnd, 1);
		            }

                    /* Call VariSel() to get the variables selection */
                    pCurva = GlobalLock(hCurva);

                    for (i=0; i<ncurve; i++)
                        curva[i] = pCurva + 80*i;

                    lpVariSel = MakeProcInstance((FARPROC) VariSel, hInst);

                    hvari = DialogBox(hInst, "VariSel", hWnd, lpVariSel);
                    FreeProcInstance(lpVariSel);

                    GlobalUnlock(hCurva);

	                hMenu = GetMenu(hWnd);
                    if (nselect != 0)
                    {
                        EnableMenuItem(hMenu, IDM_SETSCALE, MF_ENABLED);
                        EnableMenuItem(hMenu, IDM_MEMOGROUP, MF_ENABLED);
		            }

                    else
		            {
                        EnableMenuItem(hMenu, IDM_SETSCALE, MF_GRAYED);
                        EnableMenuItem(hMenu, IDM_MEMOGROUP, MF_GRAYED);
		            }

                    if (!hvari)
                        return (0);

		    /* read selected variables data */
                    hSaveCursor = SetCursor(hHourGlass);

		            ReadF22(hWnd);	            
	                Poini = 0;
	                Pofin = npunti;
		            MinMaxDati();

                    MaxOM = MaxO;
                    MinOM = MinO;
                    MaxOA = MaxO;
                    MinOA = MinO;
                    for (i=1; i<MAXSELECT+1; i++)
	                {
                       MinOrdM[i] = MinOrd[i];
                       MaxOrdM[i] = MaxOrd[i];
                       MinOrdA[i] = MinOrd[i];
                       MaxOrdA[i] = MaxOrd[i];
		            }

                    SetCursor(hSaveCursor);  

		         /* draw plots */
					PrevXflg = 1;
 	                InvalidateRect(hWnd, NULL, TRUE);  
	                idTimer = SetTimer(hWnd, 1, secTimer*1000, (FARPROC) NULL);
                    break;

	        /* memorize a group of variables */
                case IDM_REFRTIME:
                    /* Call MemoGroup() to get the variables selection */
                    if (idTimer != -1)
                        KillTimer(hWnd, 1);

                    lpRefrTime = MakeProcInstance((FARPROC) RefrTime, hInst);

                    hrefrtime = DialogBox(hInst, "SetRefr", hWnd, lpRefrTime);
                    FreeProcInstance(lpRefrTime);

                    if (!hrefrtime)
                    {
                        idTimer = -1;
                        return (0);
	                }


                    if (idTimer != -1)
  	                    idTimer = SetTimer(hWnd, 1, secTimer*1000, (FARPROC) NULL);

                    break;



	        /* memorize a group of variables */
                case IDM_MEMOGROUP:
                    /* Call MemoGroup() to get the variables selection */
                    if (idTimer != -1)
                        KillTimer(hWnd, 1);

                    lpMemoGroup = MakeProcInstance((FARPROC) MemoGroup, hInst);

                    hgruppi = DialogBox(hInst, "MemoGroup", hWnd, lpMemoGroup);
                    FreeProcInstance(lpMemoGroup);

                    if (!hgruppi)
                    {
                        idTimer = -1;
                        return (0);
	                }

// guag dic 2003 gruppi
//                    saveGroup = 1;
					WriteG22();
// fine guag
                    if (idTimer != -1)
  	                    idTimer = SetTimer(hWnd, 1, secTimer*1000, (FARPROC) NULL);

                    break;


	        /* select a group of variables */
                case IDM_GROUP:
                    /* Call GroupSel() to get the variables selection */
                    if (idTimer != -1) 
					{
                        idTimer = -1;
                        KillTimer(hWnd, 1);
                    }
// guag dic 2003 gruppi
					ReadG22(hWnd);
                    pGroup = (struct stGroup *) GlobalLock(hGroup);

                    pCurva = GlobalLock(hCurva);
                    for (i=0; i<ncurve; i++)
                        curva[i] = pCurva + 80*i;

                    lpGroupSel = MakeProcInstance((FARPROC) GroupSel, hInst);

                    hgruppi = DialogBox(hInst, "GroupSel", hWnd, lpGroupSel);
                    FreeProcInstance(lpGroupSel);

                    GlobalUnlock(hGroup);
                    GlobalUnlock(hCurva);

                    if (hgruppi == -1)
                        return (0);

	                hMenu = GetMenu(hWnd);
                    if (nselect != 0)
                    {
                        EnableMenuItem(hMenu, IDM_SETSCALE, MF_ENABLED);
                        EnableMenuItem(hMenu, IDM_MEMOGROUP, MF_ENABLED);
		            }

                    else
		            {
                        EnableMenuItem(hMenu, IDM_SETSCALE, MF_GRAYED);
                        EnableMenuItem(hMenu, IDM_MEMOGROUP, MF_GRAYED);
		            }

		    /* read selected variables data */
                    hSaveCursor = SetCursor(hHourGlass);

		            ReadF22(hWnd);	            
	                Poini = 0;
	                Pofin = npunti;
		            MinMaxDati();

                    MaxOA = MaxO;
                    MinOA = MinO;
                    for (i=1; i<MAXSELECT+1; i++)
	                {
                       MinOrdA[i] = MinOrd[i];
                       MaxOrdA[i] = MaxOrd[i];
		            }

	                hMenu = GetMenu(hWnd);
                    if (Color != pGroup[hgruppi].Color)
                    {
	                    if (pGroup[hgruppi].Color == 1)
                        {
                            CheckMenuItem(hMenu, IDM_COLOR, MF_CHECKED);
	                        Color = 1;
                        }

                        else
                        {
                            CheckMenuItem(hMenu, IDM_COLOR, MF_UNCHECKED);
	                        Color = 0;
                        }
		            }

                    if (Scale != pGroup[hgruppi].Scale)
                    {
	                    if (pGroup[hgruppi].Scale == 1)
                        {
                            CheckMenuItem(hMenu, IDM_SCALE, MF_CHECKED);
	                        Scale = 1;
                        }

                        else
                        {
                            CheckMenuItem(hMenu, IDM_SCALE, MF_UNCHECKED);
	                        Scale = 0;
                        }
		            }

                    if (Grid != pGroup[hgruppi].Grid)
                    {
	                    if (pGroup[hgruppi].Grid == 1)
                        {
                            CheckMenuItem(hMenu, IDM_GRID, MF_CHECKED);
	                        Grid = 1;
                        }

                        else
                        {
                            CheckMenuItem(hMenu, IDM_GRID, MF_UNCHECKED);
	                        Grid = 0;
                        }
		            }

	                if (pGroup[hgruppi].Auto == 1)
		            {
                        CheckMenuItem(hMenu, IDM_MANUAL, MF_UNCHECKED);
                        CheckMenuItem(hMenu, IDM_AUTO, MF_CHECKED);
	                    Auto = 1;

                        MinO = MinOA;
                        MaxO = MaxOA;
                        for (i=1; i<MAXSELECT+1; i++)
                        {
                           MinOrd[i] = MinOrdA[i];
                           MaxOrd[i] = MaxOrdA[i];
                        }
                    }

                    else
		            {
                        CheckMenuItem(hMenu, IDM_MANUAL, MF_CHECKED);
                        CheckMenuItem(hMenu, IDM_AUTO, MF_UNCHECKED);
	                    Auto = 0;

                        MinO = MinOM;
                        MaxO = MaxOM;
                        for (i=1; i<MAXSELECT+1; i++)
                        {
                           MinOrd[i] = MinOrdM[i];
                           MaxOrd[i] = MaxOrdM[i];
                        }
                    }

                    SetCursor(hSaveCursor);  

		    /* draw plots */
					PrevXflg = 1;
 	                InvalidateRect(hWnd, NULL, TRUE);  
	                idTimer = SetTimer(hWnd, 1, secTimer*1000, (FARPROC) NULL);
                    break;


	        /* define manual Y scale */
                case IDM_SETSCALE:
                    /* Call SetScale() to set manual Y scaling */
                    if (idTimer != -1)
                        KillTimer(hWnd, 1);

                    lpSetScale = MakeProcInstance((FARPROC) SetScale, hInst);

                    hscale = DialogBox(hInst, "SetScale", hWnd, lpSetScale);
                    FreeProcInstance(lpSetScale);

                    if (!hscale)
                    {
                        idTimer = -1;
                        return (0);
                    }

		    /* draw plots */
					PrevXflg = 1;
 	                InvalidateRect(hWnd, NULL, TRUE);  
                    if (idTimer != -1)
	                    idTimer = SetTimer(hWnd, 1, secTimer*1000, (FARPROC) NULL);

                    break;


	        /* select grid/nogrid */
                case IDM_GRID:
                    if (idTimer != -1)
                        KillTimer(hWnd, 1);

	                hMenu = GetMenu(hWnd);
	                if (Grid == 1)
                    {
                        CheckMenuItem(hMenu, IDM_GRID, MF_UNCHECKED);
	                    Grid = 0;
                    }

                    else
                    {
                        CheckMenuItem(hMenu, IDM_GRID, MF_CHECKED);
	                    Grid = 1;
                    }

		        /* redraw plots */
					PrevXflg = 1;
 	                InvalidateRect(hWnd, NULL, TRUE);  
                    if (idTimer != -1)
	                    idTimer = SetTimer(hWnd, 1, secTimer*1000, (FARPROC) NULL);

		            break;


	        /* select color B/W background */
                case IDM_COLOR:
                    if (idTimer != -1)
                        KillTimer(hWnd, 1);

	                hMenu = GetMenu(hWnd);
	                if (Color == 1)
                    {
                        CheckMenuItem(hMenu, IDM_COLOR, MF_UNCHECKED);
	                    Color = 0;
                    }

                    else
                    {
                        CheckMenuItem(hMenu, IDM_COLOR, MF_CHECKED);
	                    Color = 1;
                    }

		         /* redraw plots */
					PrevXflg = 1;
 	                InvalidateRect(hWnd, NULL, TRUE);  
                    if (idTimer != -1)
	                    idTimer = SetTimer(hWnd, 1, secTimer*1000, (FARPROC) NULL);

		            break;


	        /* select zoom */
                case IDM_ZOOM:
                    if (idTimer != -1)
                        KillTimer(hWnd, 1);

	                hMenu = GetMenu(hWnd);
	                if (Zoom == 1)
                    {
                        CheckMenuItem(hMenu, IDM_ZOOM, MF_UNCHECKED);
	                    Zoom = 0;
                        hDC = GetDC(hWnd);
                        SetROP2(hDC, R2_NOT);          
                        if (PrevX != 0)
	                    {
                            MoveToEx(hDC, PrevX, YY0, NULL);
                            LineTo(hDC, PrevX, YY1);
	                    }

                        ReleaseDC(hWnd, hDC);
	                    Zoom = 0;
                        PrevX = 0;
                        if (Value != 1)
	                        idTimer = SetTimer(hWnd, 1, secTimer*1000, (FARPROC) NULL);
                    }

                    else
                    {
                        CheckMenuItem(hMenu, IDM_ZOOM, MF_CHECKED);
						idTimer = -1;
	                    Zoom = 1;
                    }
     	            break;


	        /* select Y scaling */
                case IDM_AUTO:
                    if (idTimer != -1)
                        KillTimer(hWnd, 1);

	                hMenu = GetMenu(hWnd);
	                if (Auto == 0)
		            {
                        CheckMenuItem(hMenu, IDM_MANUAL, MF_UNCHECKED);
                        CheckMenuItem(hMenu, IDM_AUTO, MF_CHECKED);
	                    Auto = 1;

		                MinMaxDati();

                        MinOA = MinO;
                        MaxOA = MaxO;
                        for (i=1; i<MAXSELECT+1; i++)
                        {
                           MinOrdA[i] = MinOrd[i];
                           MaxOrdA[i] = MaxOrd[i];
                        }
	 	            /* redraw plots */
					    PrevXflg = 1;
 	                    InvalidateRect(hWnd, NULL, TRUE);  
                    }

                    if (idTimer != -1)
	                    idTimer = SetTimer(hWnd, 1, secTimer*1000, (FARPROC) NULL);

		            break;


	        /* select Y scaling */
                case IDM_MANUAL:
                    if (idTimer != -1)
                        KillTimer(hWnd, 1);

	                hMenu = GetMenu(hWnd);
	                if (Auto == 1)
		            {
                        CheckMenuItem(hMenu, IDM_MANUAL, MF_CHECKED);
                        CheckMenuItem(hMenu, IDM_AUTO, MF_UNCHECKED);
	                    Auto = 0;

                        MinO = MinOM;
                        MaxO = MaxOM;
                        for (i=1; i<MAXSELECT+1; i++)
                        {
                           MinOrd[i] = MinOrdM[i];
                           MaxOrd[i] = MaxOrdM[i];
                        }
	 	             /* redraw plots */
					    PrevXflg = 1;
 	                    InvalidateRect(hWnd, NULL, TRUE);  
                    }

                    if (idTimer != -1)
	                    idTimer = SetTimer(hWnd, 1, secTimer*1000, (FARPROC) NULL);

		            break;


	        /* select full wiew */
                case IDM_FULLW:
                    if (idTimer != -1)
                        KillTimer(hWnd, 1);

	                Poini = 0;
	                Pofin = npunti;
                    MinMaxDati();

                    MinOA = MinO;
                    MaxOA = MaxO;
                    for (i=1; i<MAXSELECT+1; i++)
                    {
                        MinOrdA[i] = MinOrd[i];
                        MaxOrdA[i] = MaxOrd[i];
                    }

	                if (Auto == 0)
	                {
                        MinO = MinOM;
                        MaxO = MaxOM;
                        for (i=1; i<MAXSELECT+1; i++)
                        {
                           MinOrd[i] = MinOrdM[i];
                           MaxOrd[i] = MaxOrdM[i];
                        }
		            }

		        /* redraw plots */
					PrevXflg = 1;
 	                InvalidateRect(hWnd, NULL, TRUE);  
                    if (idTimer != -1)
	                    idTimer = SetTimer(hWnd, 1, secTimer*1000, (FARPROC) NULL);

		            break;


	        /* single scale */
                case IDM_SCALE:
                    if (idTimer != -1)
                        KillTimer(hWnd, 1);

	                hMenu = GetMenu(hWnd);
	                if (Scale == 1)
                    {
                        CheckMenuItem(hMenu, IDM_SCALE, MF_UNCHECKED);
	                    Scale = 0;
                    }

                    else
                    {
                        CheckMenuItem(hMenu, IDM_SCALE, MF_CHECKED);
	                    Scale = 1;
                    }

		        /* redraw plots */
					PrevXflg = 1;
 	                InvalidateRect(hWnd, NULL, TRUE);  
                    if (idTimer != -1)
	                    idTimer = SetTimer(hWnd, 1, secTimer*1000, (FARPROC) NULL);

		            break;


	        /* display value */
                case IDM_VALUE:
                    if (idTimer != -1)
                        KillTimer(hWnd, 1);
	               
					hMenu = GetMenu(hWnd);

	                if (Value == 1)
                    {
                        CheckMenuItem(hMenu, IDM_VALUE, MF_UNCHECKED);
	                    Value = 0;

                        if (Zoom != 1)
	                        idTimer = SetTimer(hWnd, 1, secTimer*1000, (FARPROC) NULL);
							     	               
						rect.left = 3;
	    	            rect.right = WsizeX-1;
	                    rect.top = YY1 + 2;
	 	                rect.bottom = WsizeY-1;
 	                    InvalidateRect(hWnd, &rect, FALSE);
					}


                    else
                    {
                        idTimer = -1;
                        CheckMenuItem(hMenu, IDM_VALUE, MF_CHECKED);
	                    Value = 1;
                    }

		            break;
            } 
            break;

        case WM_CREATE:
			if (iNumColors == -1)
            {
                hGrayBrush = CreateSolidBrush(RGB(152, 152, 152));
                hSolidTGrayPen = CreatePen(PS_SOLID, 2, RGB(152, 152, 152));
                hSolidGrayPen = CreatePen(PS_SOLID, 1, RGB(152, 152, 152));
			}

			else
            {
                hGrayBrush = CreateSolidBrush(RGB(128, 128, 128));
                hSolidTGrayPen = CreatePen(PS_SOLID, 2, RGB(128, 128, 128));
                hSolidGrayPen = CreatePen(PS_SOLID, 1, RGB(128, 128, 128));
			}

            hBluMarineBrush = CreateSolidBrush(RGB(0, 128, 128));
            hGreenBrush = CreateSolidBrush(RGB(0, 255, 0));
            hSolidBlackPen = CreatePen(PS_SOLID, 2, RGB(0, 0, 0));
            hSolidTBlackPen = CreatePen(PS_SOLID, 1, RGB(0, 0, 0));
            hSolidGridPen = CreatePen(PS_SOLID, 1, RGB(196, 196, 196));
            hSolidCGridPen = CreatePen(PS_SOLID, 1, RGB(128, 128, 128));
            hSolidRedPen = CreatePen(PS_SOLID, 1, RGB(255, 255, 0));
            hSolidBluePen = CreatePen(PS_SOLID, 1, RGB(0, 255, 0));
            hSolidGreenPen = CreatePen(PS_SOLID, 1, RGB(0, 255, 255));
            hSolidBluMarinePen = CreatePen(PS_SOLID, 1, RGB(0, 128, 128));
            hSolidViolPen = CreatePen(PS_SOLID, 1, RGB(0, 128, 0));
            hSolidTWhitePen = CreatePen(PS_SOLID, 2, RGB(255, 255, 255));
            hSolidWhitePen = CreatePen(PS_SOLID, 1, RGB(255, 255, 255));
			GraficsFMT = RegisterClipboardFormat((LPSTR) "GRAFICS");
            EnableMenuItem(GetSystemMenu(hWnd, 0), SC_TASKLIST, 
                                               MF_GRAYED | MF_BYCOMMAND);
            hMFont = CreateFont(14, 0, 0, 0, FW_NORMAL, FALSE, FALSE, FALSE,
                                DEFAULT_CHARSET,
                                OUT_DEFAULT_PRECIS, 
                                CLIP_DEFAULT_PRECIS,
                                DEFAULT_QUALITY, 
                                DEFAULT_PITCH,
                                "Arial");

			hBitmapBK = LoadBitmap(hInst, MAKEINTRESOURCE(GRAFICA));

            if (_givegrid == 0)
	        {
	            hMenu = GetMenu(hWnd);
                CheckMenuItem(hMenu, IDM_GRID, MF_UNCHECKED);
	            Grid = 0;
            }	    

            if (_givecolor == 0)
	        {
	            hMenu = GetMenu(hWnd);
                CheckMenuItem(hMenu, IDM_COLOR, MF_UNCHECKED);
	            Color = 0;
            }	    

            if (_givescale == 1)
	        {
	            hMenu = GetMenu(hWnd);
                CheckMenuItem(hMenu, IDM_SCALE, MF_UNCHECKED);
	            Scale = 1;
            }	    

            if (_givefile != 0)
	        {
	            hMenu = GetMenu(hWnd);
                strcpy(FileName, _filename);
	            hfile = CreateFile(FileName, GENERIC_READ, 
					   	           FILE_SHARE_READ | FILE_SHARE_WRITE, 
								   (LPSECURITY_ATTRIBUTES) NULL, 
								   OPEN_EXISTING,
						           FILE_ATTRIBUTE_NORMAL, (HANDLE) NULL); 
                if (hfile == INVALID_HANDLE_VALUE)
                    break;

                /*  open group file  */
                lstrcpy((LPSTR) OpenGName, (LPSTR) FileName);
                AddGExt(OpenGName, DefGExt);

	            hGfile = CreateFile(OpenGName, GENERIC_READ | GENERIC_WRITE, 
					   	            FILE_SHARE_READ | FILE_SHARE_WRITE, (LPSECURITY_ATTRIBUTES) NULL, OPEN_EXISTING,
						            FILE_ATTRIBUTE_NORMAL, (HANDLE) NULL);                 
				if (hGfile == INVALID_HANDLE_VALUE)
	                hGfile = CreateFile(OpenGName, GENERIC_READ | GENERIC_WRITE, 
					   	                FILE_SHARE_READ | FILE_SHARE_WRITE, (LPSECURITY_ATTRIBUTES) NULL, CREATE_ALWAYS,
						                FILE_ATTRIBUTE_NORMAL, (HANDLE) NULL);

                /* Set up a new buffer and window title */
                sprintf(str, "Grafics - %s", FileName);
                SetWindowText(hWnd, str);

                hSaveCursor = SetCursor(hHourGlass);
		        if (ReadHeaderF22(hWnd) == 0)
                {
	                CloseHandle(hfile);
	                CloseHandle(hGfile);
                    hfile = INVALID_HANDLE_VALUE;
                    ncurve  = 0;
                    SetWindowText(hWnd, "Grafics - (no file)");
                    SetCursor(hSaveCursor);  
	                break;
	    	    }

		        if (ReadG22(hWnd) == 0)
                {
	                CloseHandle(hfile);
	                CloseHandle(hGfile);
                    GlobalFree(hCurva);
                    LocalFree(hBuffer);
	                for (i=0; i<MAXSELECT+1; i++)
                        GlobalFree(hOrd[i]);

	 	            hfile = INVALID_HANDLE_VALUE;
                    ncurve  = 0;
                    SetWindowText(hWnd, "Grafics - (no file)");
                    SetCursor(hSaveCursor);  
	                break;
		        }

                SetCursor(hSaveCursor);  
                EnableMenuItem(hMenu, IDM_VARIA, MF_ENABLED);
                EnableMenuItem(hMenu, IDM_GROUP, MF_ENABLED);
                EnableMenuItem(hMenu, IDM_FULLW, MF_ENABLED);
            }	    

            if (_givevar != 0)
	        {
                pCurva = GlobalLock(hCurva);

                for (i=0; i<ncurve; i++)
                    curva[i] = pCurva + 80*i;

		        for (j=0, nselect=0; j<_givevar; j++)
		            for (i=0; i<ncurve; i++)
                        if (!(strncmp(curva[i], _varname[j], 
                                                strlen(_varname[j]))))
                        {
                            iselect[nselect] = i;
                            lstrcpy((LPSTR) SELECT[nselect], curva[i]);
                            nselect++;	                    
			            }

                GlobalUnlock(hCurva);

	            hMenu = GetMenu(hWnd);
                if (nselect != 0)
                {
                    EnableMenuItem(hMenu, IDM_SETSCALE, MF_ENABLED);
                    EnableMenuItem(hMenu, IDM_MEMOGROUP, MF_ENABLED);
		        }

                else
                    break;

		/* read selected variables data */
                hSaveCursor = SetCursor(hHourGlass);

		        ReadF22(hWnd);	            
	            Poini = 0;
	            Pofin = npunti;
		        MinMaxDati();

                MaxOM = MaxO;
                MinOM = MinO;
                MaxOA = MaxO;
                MinOA = MinO;
                for (i=1; i<MAXSELECT+1; i++)
	            {
                    MinOrdM[i] = MinOrd[i];
                    MaxOrdM[i] = MaxOrd[i];
                    MinOrdA[i] = MinOrd[i];
                    MaxOrdA[i] = MaxOrd[i];
		        }

                SetCursor(hSaveCursor);  

		/* draw plots */
				PrevXflg = 1;
 	            InvalidateRect(hWnd, NULL, TRUE);  
	            idTimer = SetTimer(hWnd, 1, secTimer*1000, (FARPROC) NULL);
	        }

            if (_givecomm != 0)
	        {
                for (;;)
                {
                    if (OpenClipboard(hWnd))
                    {
                        hClipData = GetClipboardData(GraficsFMT);
	                    if (!hClipData)
                        {
                            CloseClipboard();
                            return(-1);
	                    }
 
                        ClipData = GlobalLock(hClipData);
	                    if (!ClipData)
                        {
                            MessageBox(hWnd, "Not enough memory [ClipData]",
                                              PrgName, MB_OK | MB_ICONSTOP);
    	                    CloseClipboard();
                            return(-1);
	                    }
	
                        grafics = (struct graficsDB *) ClipData;
                        nselect = grafics->n;
                        
                        pCurva = GlobalLock(hCurva);
                        for (i=0; i<ncurve; i++)
                            curva[i] = pCurva + 80*i;

	    	            for (j=0; j<nselect; j++)
                        {
                            iselect[j] = grafics->np[j];
                            lstrcpy((LPSTR) SELECT[j], curva[iselect[j]]);
                        }

                        GlobalUnlock(hCurva);
                        GlobalUnlock(hClipData);
	                    CloseClipboard();
                        hClipData = NULL;

	                    hMenu = GetMenu(hWnd);
                        if (nselect != 0)
                        {
                            EnableMenuItem(hMenu, IDM_SETSCALE, MF_ENABLED);
                            EnableMenuItem(hMenu, IDM_MEMOGROUP, MF_ENABLED);
                            EnableMenuItem(hMenu, IDM_COPY, MF_GRAYED);
	 	                }

                        else
                            break;

                     /* read selected variables data */
                        hSaveCursor = SetCursor(hHourGlass);

	  	                ReadF22(hWnd);	            
	                    Poini = 0;
	                    Pofin = npunti;
	 	                MinMaxDati();

                        MaxOM = MaxO;
                        MinOM = MinO;
                        MaxOA = MaxO;
                        MinOA = MinO;
                        for (i=1; i<MAXSELECT+1; i++)
	                    {
                            MinOrdM[i] = MinOrd[i];
                            MaxOrdM[i] = MaxOrd[i];
                            MinOrdA[i] = MinOrd[i];
                            MaxOrdA[i] = MaxOrd[i];
   	                    }

                        SetCursor(hSaveCursor);  

                     /* draw plots */
					    PrevXflg = 1;
  	                    InvalidateRect(hWnd, NULL, TRUE);  
	                    idTimer  = SetTimer(hWnd, 1, secTimer*1000, (FARPROC) NULL);
                        hNextWnd = SetClipboardViewer(hWnd);
                        break;
	                }
	            }
	        }

	        break;

        case WM_SIZE:
            WsizeX = LOWORD(lParam);  // width of client area
            WsizeY = HIWORD(lParam);  // height of client area 
	            
			hDC = GetDC(hWnd);
			holdFont = SelectObject(hDC, hMFont);
	        strcpy(str, "0.000000");
            GetTextExtentPoint32(hDC, (LPSTR) str, strlen(str), &retSize);
            SelectObject(hDC, holdFont);
			ReleaseDC(hWnd, hDC);

            PixelX = WsizeX - retSize.cx - 20;
			if (PixelX < 160) PixelX = 160;

// guag era            PixelY = WsizeY - 4*retSize.cy - 8;
            PixelY = WsizeY - 4*retSize.cy - 20;
			if (PixelY < 160) PixelY = 160;

            retidx = PixelX/8;
            retidy = PixelY/4;
            PixelX = retidx*8;
            PixelY = retidy*4;
			Dcont = retidx;

			InvalidateRect(hWnd, NULL, FALSE);  
			break;


        case WM_DRAWCLIPBOARD:
            for (;;)
            {
                if (OpenClipboard(hWnd))
                {
                    if (!IsClipboardFormatAvailable(GraficsFMT))
                    {
                        if (idTimer != -1) 
                            KillTimer(hWnd, 1);

  	                    CloseClipboard();
                        DestroyWindow(hWnd);
                        break;
                    }

                    hClipData = GetClipboardData(GraficsFMT);
	                if (!hClipData)
                    {
                        CloseClipboard();
                        return(-1);
	                }

                    ClipData = GlobalLock(hClipData);
	                if (!ClipData)
                    {
                        MessageBox(hWnd, "Not enough memory [ClipData]",
                                          PrgName, MB_OK | MB_ICONSTOP);
  	                    CloseClipboard();
                        return(-1);
	                }
	
                    grafics = (struct graficsDB *) ClipData;
                    nselect = grafics->n;

                    pCurva = GlobalLock(hCurva);
                    for (i=0; i<ncurve; i++)
                        curva[i] = pCurva + 80*i;

	   	            for (j=0; j<nselect; j++)
                    {
                        iselect[j] = grafics->np[j];
                        lstrcpy((LPSTR) SELECT[j], curva[iselect[j]]);
                    }

                    GlobalUnlock(hCurva);
                    GlobalUnlock(hClipData);
	            	CloseClipboard();
                    hClipData = NULL;

	            	hMenu = GetMenu(hWnd);
                    if (nselect != 0)
                    {
                        EnableMenuItem(hMenu, IDM_SETSCALE, MF_ENABLED);
                        EnableMenuItem(hMenu, IDM_MEMOGROUP, MF_ENABLED);
		    		}

                    else
                        break;

                 /* read selected variables data */
                    hSaveCursor = SetCursor(hHourGlass);
 
	 	            ReadF22(hWnd);	            
	                Poini = 0;
	                Pofin = npunti;
	                MinMaxDati();

                    MaxOM = MaxO;
                    MinOM = MinO;
                    MaxOA = MaxO;
                    MinOA = MinO;
                    for (i=1; i<MAXSELECT+1; i++)
	                {
                        MinOrdM[i] = MinOrd[i];
                        MaxOrdM[i] = MaxOrd[i];
                        MinOrdA[i] = MinOrd[i];
                        MaxOrdA[i] = MaxOrd[i];
  	                }

                    SetCursor(hSaveCursor);  
                 /* draw plots */
					PrevXflg = 1;
  	                InvalidateRect(hWnd, NULL, TRUE);  
                    break;
	            }
	        }
            break;


        case WM_TIMER:
            if (IsIconic(hWnd) != 0)
                break;            

	        ReadF22(hWnd);	            
	        Poini = 0;

            if (Pofin == npunti)
	            break;

         /* draw plots */
			PrevXflg = 1;
 	        InvalidateRect(hWnd, NULL, FALSE);  
            Refresh = 1;
            break;


        case WM_ACTIVATE:
            if (!GetSystemMetrics(SM_MOUSEPRESENT)) 
			{
                if (!HIWORD(wParam)) 
				{
                    if (LOWORD(wParam)) 
					{
                        SetCursor(hArrow);
                        ptCursor.x = X;
                        ptCursor.y = Y;
                        ClientToScreen(hWnd, &ptCursor);
                        SetCursorPos(ptCursor.x, ptCursor.y);
                    }

                    ShowCursor(LOWORD(wParam));
                }
            }

            break;


        case WM_KEYDOWN:
            if (nselect == 0)
                break;

            if ((int) wParam != VK_LEFT && (int) wParam != VK_RIGHT
                    && (int) wParam != VK_UP && (int) wParam != VK_DOWN)
                break;

            GetCursorPos(&ptCursor);

            /* Convert screen coordinates to client coordinates */

            ScreenToClient(hWnd, &ptCursor);
            repeat++;                           /* Increases the repeat rate */

            switch ((int) wParam) 
			{
            /* Adjust cursor position according to which key was pressed. */

                case VK_LEFT:
                    ptCursor.x -= repeat;
                    break;

                case VK_RIGHT:
                    ptCursor.x += repeat;
                    break;

                case VK_UP:
                    ptCursor.y -= repeat;
                    break;

                case VK_DOWN:
                    ptCursor.y += repeat;
                    break;

            }

            /* Do not draw outside the window's client area */

            if (ptCursor.x >= XX1)
                ptCursor.x = XX1-1;
            else if (ptCursor.x < XX0)
                ptCursor.x = XX0;
            if (ptCursor.y >= YY1)
                ptCursor.y = YY1-1;
            else if (ptCursor.y < YY0)
                ptCursor.y = YY0;

            /* Convert the coordinates to screen coordinates */

            ClientToScreen(hWnd, &ptCursor);
            SetCursorPos(ptCursor.x, ptCursor.y);
            break;


        case WM_KEYUP:
            repeat = 1;                          /* Clears the repeat count. */
            if (Zoom == 0)
		        break;
 
            if ((int) wParam == VK_F1)
            {
                GetCursorPos(&ptCursor);
                ScreenToClient(hWnd, &ptCursor);
                X = ptCursor.x;
                Y = ptCursor.y;
                goto ZOOMKEY;
            }
	        break;


        case WM_LBUTTONDOWN:
            if (Zoom == 0)
		        break;

            X = LOWORD(lParam);
            Y = HIWORD(lParam);

        ZOOMKEY:
            if (X<XX0 || X>XX1-1 || Y<YY0 || Y>YY1-1)
		        break;

            if (bTrack == 0)
	        {
                bTrack = 1;
	            OrgX = X;
	            hDC = GetDC(hWnd);
                hOldBrush = SelectObject(hDC, hSolidViolPen);
                MoveToEx(hDC, OrgX, YY0, NULL);
                LineTo(hDC, OrgX, YY1);
                SelectObject(hDC, hOldBrush);
	            ReleaseDC(hWnd, hDC);
                SetCapture(hWnd);  
                break;
            }

            if (bTrack == 1)
	        {
                if (X > OrgX)
	            {
                    for (i=0; i<MAXSELECT+1; i++) 
                        pOrd[i] = (double *) GlobalLock(hOrd[i]);

	                temValue = ((double) (OrgX - XX0))/((double) PixelX)*
                                         (MaxOrd[0] - MinOrd[0]) +MinOrd[0];

                    for (j=Poini, ki=0; j<Pofin; j++)
	                    if (pOrd[0][j] >= temValue)
                        {
                            minz = pOrd[0][j];
                            ki = j;
	   	                    break;
		                }

	                temValue = ((double) (X - XX0))/((double) PixelX)*
                                         (MaxOrd[0] - MinOrd[0]) + MinOrd[0];

                    for (j=Poini, ku=0; j<Pofin; j++)
	                     if (pOrd[0][j] >= temValue)
                         {
                             maxz = pOrd[0][j];
                             ku = j;
	 	                     break;
		                 }

                    for (i=0; i<MAXSELECT+1; i++) 
                        GlobalUnlock(hOrd[i]);

                    if (ku > ki)
                    {
		                Poini = ki;
	                    Pofin = ku+1;
		                MinOrd[0] = minz;
	 	                MaxOrd[0] = maxz;
                        if (Auto == 1)
                        {
	                        MinMaxDati();

                            MinOA = MinO;
                            MaxOA = MaxO;
                            for (i=1; i<MAXSELECT+1; i++)
                            {
                                MinOrdA[i] = MinOrd[i];
                                MaxOrdA[i] = MaxOrd[i];
                            }
 		             	}
		            }
	            }

                bTrack = 0;
                ReleaseCapture(); 
				PrevXflg = 1;
                InvalidateRect (hWnd, NULL, TRUE);
            }
	        break;


        case WM_MOUSEMOVE:
	        xpoint = LOWORD(lParam);
	        ypoint = HIWORD(lParam);
            if (xpoint < XX0 || xpoint > XX1-1 || 
                                ypoint < YY0 || ypoint > YY1-1) 
            {
                SetCursor(hArrow);   
	            break;
	        }

		    if (Zoom == 1)
                if (xpoint != PrevX)
                {
                    hDC = GetDC(hWnd);
                    SetROP2(hDC, R2_NOT);          
                    if (PrevX != 0)
		            {
                        MoveToEx(hDC, PrevX, YY0, NULL);
                        LineTo(hDC, PrevX, YY1);
	 	            }

                 /* Get the current mouse position */

                    PrevX = xpoint;
                    MoveToEx(hDC, xpoint, YY0, NULL);
                    LineTo(hDC, xpoint, YY1);
                    ReleaseDC(hWnd, hDC);
                }

			if (Value == 1)
	        {
	  	        SetCursor(hCross);
		        temValue = ((double) (xpoint - XX0))/((double) PixelX)*
                                (MaxOrd[0] - MinOrd[0]) +MinOrd[0];

	            hDC = GetDC(hWnd);
				holdFont = SelectObject(hDC, hMFont);
	            GetTextMetrics(hDC, &textmetric);
                hOldBrush = SelectObject(hDC, hGrayBrush);
                SelectObject(hDC, hSolidTBlackPen);
	            strcpy(str, "0.000000");
                GetTextExtentPoint32(hDC, (LPSTR) str, strlen(str), &retSize);
	 	        XX0g = XX1;
	        	XX1g = XX1 + (int) retSize.cx + 10;
	            YY0g = YY1 + textmetric.tmHeight + 1;  // era + 1                 
	 	        YY1g = YY1 + 4*textmetric.tmHeight + 13; // era 0                   
                SelectObject(hDC, hSolidTBlackPen);
		        Rectangle(hDC, XX0g, YY0g, XX1g, YY1g);

                for (i=0; i<MAXSELECT+1; i++) 
                    pOrd[i] = (double *) GlobalLock(hOrd[i]);

		        for (j=Poini; j<Pofin; j++)
	                if (pOrd[0][j] >= temValue)
                    {
	                    GetTextMetrics(hDC, &textmetric);
						if (iNumColors == -1)
                            SetBkColor(hDC, RGB(152, 152, 152));
						else
                            SetBkColor(hDC, RGB(128, 128, 128));

                        if (nselect == 1)
	                        YY = YY1 + 2*textmetric.tmHeight;
                        else if (nselect == 2)
	                        YY = YY1 + 2*textmetric.tmHeight - 6;
                        else if (nselect == 3)
	                        YY = YY1 + textmetric.tmHeight + 1;
                        else if (nselect == 4)      //  per Value -- in questo caso  MAXSELECT è = 4
	                        YY = YY1 + textmetric.tmHeight + 2; // era - 4 per Value

                        for (i=0; i<nselect; i++)
		                {
			                convReal(str, pOrd[i+1][j], 7, 8);
                            SetTextColor(hDC, RGB(Rcolor[i], Gcolor[i], 
                                             Bcolor[i]));
	 	                    TextOut(hDC, XX1+4, YY, str , strlen(str));
	                        YY += textmetric.tmHeight - 2;
			            }
                         
                        if (Color == 0)
                        {
                            SelectObject(hDC, hOldBrush);
                            SelectObject(hDC, hSolidTWhitePen);
		                }

			            else
                            SelectObject(hDC, hSolidBluMarinePen);

	    	            rect.left = 3;
	    	            rect.right = WsizeX-1;
	                    rect.top = YY1 + 2;
	 	                rect.bottom = YY1 + textmetric.tmHeight + 1;

						InvalidateRect(hWnd, &rect, FALSE);
                        SelectObject(hDC, hOldBrush);
			            ReleaseDC(hWnd, hDC);
                        break;
                    }

                SelectObject(hDC, holdFont);

                for (i=0; i<MAXSELECT+1; i++) 
                    GlobalUnlock(hOrd[i]);
            }

            break;


        case WM_DESTROY:
	        DeleteObject(hGrayBrush);
	        DeleteObject(hBluMarineBrush);
	        DeleteObject(hGreenBrush);
	        DeleteObject(hSolidBlackPen);
	        DeleteObject(hSolidTBlackPen);
	        DeleteObject(hSolidGridPen);
	        DeleteObject(hSolidCGridPen);
	        DeleteObject(hSolidRedPen);
	        DeleteObject(hSolidBluePen);
	        DeleteObject(hSolidGreenPen);
	        DeleteObject(hSolidGrayPen);
	        DeleteObject(hSolidTGrayPen);
	        DeleteObject(hSolidBluMarinePen);
	        DeleteObject(hSolidViolPen);
	        DeleteObject(hSolidTWhitePen);
	        DeleteObject(hSolidWhitePen);
	        DeleteObject(hMFont);
            DeleteObject(hBitmapBK);

            if (_givecomm == 1)
                ChangeClipboardChain(hWnd, hNextWnd);

            for (;;)
            {
	        	if (OpenClipboard(hWnd))
	        	{
                    if (IsClipboardFormatAvailable(GraficsFMT))
	                    EmptyClipboard();

	            	CloseClipboard();
                    break;
	        	}        
	    	}        

            if (hfile != INVALID_HANDLE_VALUE)
            {
	        	CloseHandle(hfile);
	        	CloseHandle(hGfile);
                GlobalFree(hCurva);
                GlobalFree(hGroup);
                LocalFree(hBuffer);
	        	for (i=0; i<MAXSELECT+1; i++)
                    GlobalFree(hOrd[i]);
	    	}

            PostQuitMessage(0);
            break;


        case WM_PAINT:

	        hDC = BeginPaint(hWnd, &ps);
			if (PrevXflg == 1)
				PrevX = 0;
			
			PrevXflg = 0;
            holdFont = SelectObject(hDC, hMFont);

			if (nselect != 0)
            {
	            GetTextMetrics(hDC, &textmetric);

                if (Refresh == 1)
                {
                    /* erase old graphics */

                    if (Color == 1)
		                hOldBrush = SelectObject(hDC, hSolidGrayPen);
                    else
		                hOldBrush = SelectObject(hDC, hSolidWhitePen);

		            XX0 = PixelS;
	   	            XX1 = XX0 + PixelX;
	                YY0 = XX0;                   
	  	            YY1 = YY0 + PixelY;

                    Xcirc = XX0 + Dcont;
                    Xrect = XX0 + (int) (0.5*Dcont);

                    for (i=0; i<MAXSELECT+1; i++) 
                        pOrd[i] = (double *) GlobalLock(hOrd[i]);

	                diva = PixelX/(MaxOrd[0] - MinOrd[0]);
                    for (i=0; i<nselect; i++)
                    {
                        if (Scale == 0)
		                {
                            maxore = MaxOrd[i+1];
                            minore = MinOrd[i+1];
		                }

		                else
		                {
                            maxore = MaxO;
                            minore = MinO;
		                }

	                    divo = (PixelY-2)/(maxore - minore);

	                    xcalc = XX0 + (int) ((pOrd[0][Poini] - MinOrd[0])*diva);

	                    ycalc = YY0 + 1 + (int) ((maxore - 
                                pOrd[i+1][Poini])*divo);

		                if (xcalc < XX0+1)
	                        xcalc = XX0+1;

		                if (xcalc > XX1-1)
	                        xcalc = XX1-1;

		                if (ycalc < YY0+1)
	                        ycalc = YY0+1;

		                if (ycalc > YY1-1)
	                        ycalc = YY1-1;

                        xPcalc = xcalc;
	                    yPcalc = ycalc;
                        MoveToEx(hDC, xcalc, ycalc, NULL);

		                for (j=Poini+1; j<Pofin; j++)
		                {
	                        xcalc = XX0 + (int) ((pOrd[0][j] - MinOrd[0])*diva);

	                        ycalc = YY0 + 1 + (int) ((maxore - 
                                    pOrd[i+1][j])*divo);

		                    if (xcalc < XX0+1)
	                            xcalc = XX0+1;

		                    if (xcalc > XX1-1)
	                            xcalc = XX1-1;

		                    if (ycalc < YY0+1)
	                            ycalc = YY0+1;
   
		                    if (ycalc > YY1-1)
	                            ycalc = YY1-1;

		                    if (xcalc != xPcalc || ycalc != yPcalc)
		 	                {
			                    xPcalc = xcalc;
	  		                    yPcalc = ycalc;
	                            LineTo(hDC, xcalc, ycalc);

                                if (Color == 0)
                                {
                                    if (i == 1)
                                    {
		  		                        if (xcalc > Xcirc)
                                        {
                                            Xcirc = Xcirc + Dcont;
                                            Ellipse(hDC, xcalc-3, ycalc+3, 
                                                    xcalc+3, ycalc-3);
                                        }
                                    }

                                    else if (i == 2)
                                    {
				                        if (xcalc > Xrect)
                                        {
                                            Xrect = Xrect + Dcont;
                                            MoveToEx(hDC, xcalc-3, ycalc+3, NULL);
                                            LineTo(hDC, xcalc+3, ycalc-3);
                                            MoveToEx(hDC, xcalc+3, ycalc+3, NULL);
                                            LineTo(hDC, xcalc-3, ycalc-3);
                                            MoveToEx(hDC, xcalc, ycalc, NULL);
                                        }
	                                }
			                    }
	 		                }
	 	                }    
	                }

                    for (i=0; i<MAXSELECT+1; i++) 
	                    GlobalUnlock(hOrd[i]);

   		            if (Color == 1)
                    {
                        SetTextColor(hDC, RGB(0, 128, 128));
                        SetBkColor(hDC, RGB(0, 128, 128));
                    }

                    else
                    {
                        SetTextColor(hDC, RGB(255, 255, 255));
                        SetBkColor(hDC, RGB(255, 255, 255));
		            }

                    dtem = 0.25*(MaxOrd[0] - MinOrd[0]);
					if (Value == 0)
                    {
                        for (i=0; i<5; i++)
	                    {
	                        convReal(str, MinOrd[0] +i*dtem, 4, 8);
                            GetTextExtentPoint32(hDC, (LPSTR) str, 
                                                   strlen(str), &retSize);
                            lstr  = (int) retSize.cx;
	                        if (i==0)
	    		                XX = XX0;
	                        else if (i==4)
	                            XX = XX0 + 2*i*retidx - (int) (0.7*lstr);
	                        else 
	                            XX = XX0 + 2*i*retidx - (int) (0.5*lstr);

	 	                    TextOut(hDC, XX, YY1+1, str , strlen(str));
                        }
                    }

					else
                    {
                        if (Color == 0)
                            SetBkColor(hDC, RGB(255, 255, 255));
                        else
                            SetBkColor(hDC, RGB(0, 128, 128));

                        SetTextColor(hDC, RGB(0, 0, 0));
			            convReal(str, temValue, 4, 8);
                        GetTextExtentPoint32(hDC, (LPSTR) str, strlen(str), &retSize);
                        lstr  = (int) retSize.cx;
                        XX1g = xpoint - (int) (0.3*lstr);

	                    if (XX1g < XX0)
	                        XX1g = XX0;

	                    if (XX1g > XX1 - 0.5*lstr)
	                        XX1g = XX1 - (int) (0.5*lstr);
					
				        TextOut(hDC, XX1g, YY1+1, str , strlen(str));
                    }
                    /*  draw new graphics */

		            if (Color == 1)
                    {
                        SelectObject(hDC, hSolidTBlackPen);
                        MoveToEx(hDC, XX0, YY1, NULL);
                        LineTo(hDC, XX1, YY1);
                        LineTo(hDC, XX1, YY0-2);
		            }

                    else
	                {
                        SelectObject(hDC, hSolidTGrayPen);
		                Rectangle(hDC, XX0, YY0, XX1, YY1); 
                    }

	                if (Grid == 1)
                    {
	                    if ((Color == 1) && (iNumColors == -1))
						    SelectObject(hDC, hSolidCGridPen);
						
						else
						    SelectObject(hDC, hSolidGridPen);

						XX = XX0;
	 	                YY = YY0;
		                for (i=0; i<7; i++)
	                    {
	                        XX += retidx;
	   	                    MoveToEx(hDC, XX, YY, NULL);
	                        LineTo(hDC, XX, YY1);
	  	                }    

 		                XX = XX0;
	  	                YY = YY0;
		                for (i=0; i<3; i++)
	                    {
	                       YY += retidy;
	  	                   MoveToEx(hDC, XX, YY, NULL);
	                       LineTo(hDC, XX1, YY);
		                }   
		            }

 		            XX = XX0;
	 	            YY = YY0;
	                SelectObject(hDC, hSolidBlackPen);
		            for (i=0; i<7; i++)
	                {
	                    XX += retidx;
	   	                MoveToEx(hDC, XX, YY1-2, NULL);
	                    LineTo(hDC, XX, YY1);
	  	            }    

 		            XX = XX0;
	  	            YY = YY0;
		            for (i=0; i<3; i++)
	                {
	                    YY += retidy;
	  	                MoveToEx(hDC, XX1-2, YY, NULL);
	                    LineTo(hDC, XX1, YY);
		            }

                    Pofin = npunti;
                    MinMaxDati();

                    MaxOA = MaxO;
                    MinOA = MinO;
                    for (i=1; i<MAXSELECT+1; i++)
	                {
                        MinOrdA[i] = MinOrd[i];
                        MaxOrdA[i] = MaxOrd[i];
                    }

	                if (Auto == 0)
	                {
                        MinO = MinOM;
                        MaxO = MaxOM;
                        for (i=1; i<MAXSELECT+1; i++)
                        {
                           MinOrd[i] = MinOrdM[i];
                           MaxOrd[i] = MaxOrdM[i];
                        }
		            }

                    Xcirc = XX0 + Dcont;
                    Xrect = XX0 + (int) (0.5*Dcont);

                    for (i=0; i<MAXSELECT+1; i++) 
                        pOrd[i] = (double *) GlobalLock(hOrd[i]);

	                diva = PixelX/(MaxOrd[0] - MinOrd[0]);
                    for (i=0; i<nselect; i++)
                    {
                        if (Color == 1)
		                {
                            if (i==0)
		                        SelectObject(hDC, hSolidRedPen);

                            else if (i==1)
		                        SelectObject(hDC, hSolidBluePen);

                            else if (i==2)
	 	                        SelectObject(hDC, hSolidGreenPen);

                            else if (i==3)    // vedi MAXSELECT
	 	                        SelectObject(hDC, hSolidWhitePen);
		                }

		                else
	 	                    SelectObject(hDC, hSolidTBlackPen);
	
                        if (Scale == 0)
		                {
                            maxore = MaxOrd[i+1];
                            minore = MinOrd[i+1];
		                }

		                else
		                {
                            maxore = MaxO;
                            minore = MinO;
		                }

	                    divo = (PixelY-2)/(maxore - minore);

	                    xcalc = XX0 + (int) ((pOrd[0][Poini] - MinOrd[0])*diva);

	                    ycalc = YY0 + 1 + (int) ((maxore - 
                                pOrd[i+1][Poini])*divo);

		                if (xcalc < XX0+1)
	                        xcalc = XX0+1;

		                if (xcalc > XX1-1)
	                        xcalc = XX1-1;

		                if (ycalc < YY0+1)
	                        ycalc = YY0+1;

		                if (ycalc > YY1-1)
	                        ycalc = YY1-1;

                        xPcalc = xcalc;
	                    yPcalc = ycalc;
                        MoveToEx(hDC, xcalc, ycalc, NULL);

		                for (j=Poini+1; j<Pofin; j++)
		                {
	                        xcalc = XX0 + (int) ((pOrd[0][j] - MinOrd[0])*diva);

	                        ycalc = YY0 + 1 + (int) ((maxore - 
                                    pOrd[i+1][j])*divo);

		                    if (xcalc < XX0+1)
	                            xcalc = XX0+1;

		                    if (xcalc > XX1-1)
	                            xcalc = XX1-1;

		                    if (ycalc < YY0+1)
	                            ycalc = YY0+1;

		                    if (ycalc > YY1-1)
	                            ycalc = YY1-1;

		                    if (xcalc != xPcalc || ycalc != yPcalc)
		 	                {
			                    xPcalc = xcalc;
	  		                    yPcalc = ycalc;
	                            LineTo(hDC, xcalc, ycalc);

                                if (Color == 0)
                                {
                                    if (i == 1)
                                    {
		  		                        if (xcalc > Xcirc)
                                        {
                                            Xcirc = Xcirc + Dcont;
                                            Ellipse(hDC, xcalc-3, ycalc+3, 
                                                    xcalc+3, ycalc-3);
                                        }
                                    }

                                    else if (i == 2)
                                    {
				                        if (xcalc > Xrect)
                                        {
                                            Xrect = Xrect + Dcont;
                                            MoveToEx(hDC, xcalc-3, ycalc+3, NULL);
                                            LineTo(hDC, xcalc+3, ycalc-3);
                                            MoveToEx(hDC, xcalc+3, ycalc+3, NULL);
                                            LineTo(hDC, xcalc-3, ycalc-3);
                                            MoveToEx(hDC, xcalc, ycalc, NULL);
                                        }
	                                }
			                    }
	 		                }
	 	                }    
	                }

                    SelectObject(hDC, hOldBrush);
                }

                else
                {
                    if (Color == 1)
					{
 		                hOldBrush = SelectObject(hDC, hBluMarineBrush);
                        GetClientRect(hWnd, (LPRECT) &rect);
                        PatBlt(hDC, rect.left, rect.top, rect.right - rect.left,
                                    rect.bottom - rect.top, PATCOPY);
 		                SelectObject(hDC, hOldBrush);
                    }

					else
		                Rectangle(hDC, 0, 0, WsizeX, WsizeY); 

		            XX0 = PixelS;
	   	            XX1 = XX0 + PixelX;
	                YY0 = XX0;                   
	  	            YY1 = YY0 + PixelY;

                    Xcirc = XX0 + Dcont;
                    Xrect = XX0 + (int) (0.5*Dcont);

                    SelectObject(hDC, hSolidTGrayPen);
		            if (Color == 1)
                        SelectObject(hDC, hGrayBrush);

		            Rectangle(hDC, XX0, YY0, XX1, YY1);

		            if (Color == 1)
                    {
                        SelectObject(hDC, hSolidTBlackPen);
                        MoveToEx(hDC, XX0, YY1, NULL);
                        LineTo(hDC, XX1, YY1);
                        LineTo(hDC, XX1, YY0-2);
		            }

	                if (Grid == 1)
                    {
	                    if ((Color == 1) && (iNumColors == -1))
						    SelectObject(hDC, hSolidCGridPen);
						
						else
						    SelectObject(hDC, hSolidGridPen);

 		                XX = XX0;
	 	                YY = YY0;
		                for (i=0; i<7; i++)
	                    {
	                        XX += retidx;
	   	                    MoveToEx(hDC, XX, YY, NULL);
	                        LineTo(hDC, XX, YY1);
	  	                }    

 		                XX = XX0;
	  	                YY = YY0;
		                for (i=0; i<3; i++)
	                    {
	                        YY += retidy;
	  	                    MoveToEx(hDC, XX, YY, NULL);
	                        LineTo(hDC, XX1, YY);
		                }   
		            }

 		            XX = XX0;
	 	            YY = YY0;
	                SelectObject(hDC, hSolidBlackPen);
		            for (i=0; i<7; i++)
	                {
	                    XX += retidx;
	   	                MoveToEx(hDC, XX, YY1-2, NULL);
	                    LineTo(hDC, XX, YY1);
	  	            }    

 		            XX = XX0;
	  	            YY = YY0;
		            for (i=0; i<3; i++)
	                {
	                    YY += retidy;
	  	                MoveToEx(hDC, XX1-2, YY, NULL);
	                    LineTo(hDC, XX1, YY);
		            }

                    for (i=0; i<MAXSELECT+1; i++) 
                        pOrd[i] = (double *) GlobalLock(hOrd[i]);

	                diva = PixelX/(MaxOrd[0] - MinOrd[0]);
                    for (i=0; i<nselect; i++)
                    {
                        if (Color == 1)
		                {
                            if (i==0)
		                        SelectObject(hDC, hSolidRedPen);

                            else if (i==1)
		                        SelectObject(hDC, hSolidBluePen);

                            else if (i==2)
	 	                        SelectObject(hDC, hSolidGreenPen);

                            else if (i==3)    // vedi MAXSELECT
	 	                        SelectObject(hDC, hSolidWhitePen);
		                }

		                else
	 	                    SelectObject(hDC, hSolidTBlackPen);
	
                        if (Scale == 0)
		                {
                            maxore = MaxOrd[i+1];
                            minore = MinOrd[i+1];
		                }

		                else
		                {
                            maxore = MaxO;
                            minore = MinO;
		                }

	                    divo = (PixelY-2)/(maxore - minore);

	                    xcalc = XX0 + (int) ((pOrd[0][Poini] - MinOrd[0])*diva);

	                    ycalc = YY0 + 1 + (int) ((maxore - 
                                pOrd[i+1][Poini])*divo);

		                if (xcalc < XX0+1)
	                        xcalc = XX0+1;

		                if (xcalc > XX1-1)
	                        xcalc = XX1-1;

		                if (ycalc < YY0+1)
	                        ycalc = YY0+1;

		                if (ycalc > YY1-1)
	                        ycalc = YY1-1;

                        xPcalc = xcalc;
	                    yPcalc = ycalc;
                        MoveToEx(hDC, xcalc, ycalc, NULL);

		                for (j=Poini+1; j<Pofin; j++)
		                {
	                        xcalc = XX0 + (int) ((pOrd[0][j] - MinOrd[0])*diva);

	                        ycalc = YY0 + 1 + (int) ((maxore - 
                                    pOrd[i+1][j])*divo);

		                    if (xcalc < XX0+1)
	                            xcalc = XX0+1;

		                    if (xcalc > XX1-1)
	                            xcalc = XX1-1;

		                    if (ycalc < YY0+1)
	                            ycalc = YY0+1;

		                    if (ycalc > YY1-1)
	                            ycalc = YY1-1;

		                    if (xcalc != xPcalc || ycalc != yPcalc)
		 	                {
			                    xPcalc = xcalc;
	  		                    yPcalc = ycalc;
	                            LineTo(hDC, xcalc, ycalc);

                                if (Color == 0)
                                {
                                    if (i == 1)
                                    {
		  		                        if (xcalc > Xcirc)
                                        {
                                            Xcirc = Xcirc + Dcont;
                                            Ellipse(hDC, xcalc-3, ycalc+3, 
                                                    xcalc+3, ycalc-3);
                                        }
                                    }

                                    else if (i == 2)
                                    {
				                        if (xcalc > Xrect)
                                        {
                                            Xrect = Xrect + Dcont;
                                            MoveToEx(hDC, xcalc-3, ycalc+3, NULL);
                                            LineTo(hDC, xcalc+3, ycalc-3);
                                            MoveToEx(hDC, xcalc+3, ycalc+3, NULL);
                                            LineTo(hDC, xcalc-3, ycalc-3);
                                            MoveToEx(hDC, xcalc, ycalc, NULL);
                                        }
	                                }
			                    }
	 		                }
	 	                }    
	                }
                }

                for (i=0; i<MAXSELECT+1; i++) 
	                GlobalUnlock(hOrd[i]);

		        if (Color == 1)
                {
                    SetTextColor(hDC, RGB(0, 0, 0));
                    SetBkColor(hDC, RGB(0, 128, 128));
                }

                else
                {
                    SetTextColor(hDC, RGB(0, 0, 0));
                    SetBkColor(hDC, RGB(255, 255, 255));
                }

                dtem = 0.25*(MaxOrd[0] - MinOrd[0]);
				if (Value == 0)
                {
                    for (i=0; i<5; i++)
	                {
	                    convReal(str, MinOrd[0] +i*dtem, 4, 8);
                        GetTextExtentPoint32(hDC, (LPSTR) str, strlen(str), &retSize);
                        lstr  = (int) retSize.cx;
	                    if (i==0)
	  		                XX = XX0;
	                    else if (i==4)
	                        XX = XX0 + 2*i*retidx - (int) (0.7*lstr);
	                    else 
	                        XX = XX0 + 2*i*retidx - (int) (0.5*lstr);

	 	                TextOut(hDC, XX, YY1+1, str , strlen(str));
                    }

	                strcpy(str, "(s)");
                    XX1g = (int) (0.7*XX1 +0.3*WsizeX);
	 	            TextOut(hDC, XX1g, YY1+1, str , strlen(str));
                }
				
				else
                {
                    if (Color == 0)
                        SetBkColor(hDC, RGB(255, 255, 255));
                    else
                        SetBkColor(hDC, RGB(0, 128, 128));

                    SetTextColor(hDC, RGB(0, 0, 0));
			        convReal(str, temValue, 4, 8);
                    GetTextExtentPoint32(hDC, (LPSTR) str, strlen(str), &retSize);
                    lstr  = (int) retSize.cx;
                    XX1g = xpoint - (int) (0.3*lstr);

	                if (XX1g < XX0)
	                    XX1g = XX0;

	                if (XX1g > XX1 - 0.5*lstr)
	                    XX1g = XX1 - (int) (0.5*lstr);
					
				    TextOut(hDC, XX1g, YY1+1, str , strlen(str));
                }

                if (nselect == 1)
	                YY = YY1 + 2*textmetric.tmHeight;
                else if (nselect == 2)
	                YY = YY1 + 2*textmetric.tmHeight - 6;
                else if (nselect == 3)
	                YY = YY1 + textmetric.tmHeight + 1;
                else if (nselect == 4)   // vedi MAXSELECT da manovrare
	                YY = YY1 + textmetric.tmHeight + 2;  // era  - 4

                Maxlstr = 0;
                GetTextExtentPoint32(hDC, "OOOOOOOOOO", 10, &retSize);
                lunNome = (int) retSize.cx; 

	            for (i=0; i<nselect; i++)
		        {
                    if (Color == 1)
                        SetTextColor(hDC, RGB(Rcolor[i], Gcolor[i], Bcolor[i]));

				    for (j=0, k=0, m=0; j<=(int) strlen(SELECT[i]); j++)
                    {
                        if (k==0)
                        {
                            name[j] = SELECT[i][j];
							if (name[j]=='\t')
                            { 
								k = 1;
								name[j] = '\0';
								if (strlen(name) > 8)
									name[8] = '\0';
						    }
						}
						
						else
                        {
                            descr[m] = SELECT[i][j];
							m++;
						}
	                }
						
		            TextOut(hDC, XX0+3, YY, name, strlen(name));
		            TextOut(hDC, XX0+3+lunNome, YY, descr, strlen(descr));

                    GetTextExtentPoint32(hDC, (LPSTR) descr, strlen(descr), &retSize);
                    lstr  = (int) retSize.cx + lunNome;
                    if (lstr > Maxlstr)
                        Maxlstr = lstr;

	                YY += textmetric.tmHeight - 1;
		        }

                if (Color == 0)
                {
                    if (nselect == 1)
	                    YY = YY1 + 2*textmetric.tmHeight;
                    else if (nselect == 2)
	                    YY = YY1 + 2*textmetric.tmHeight - 6;
                    else if (nselect == 3)
	                    YY = YY1 + textmetric.tmHeight + 1;
                    else if (nselect == 4)   // vedi MAXSELECT
	                    YY = YY1 + textmetric.tmHeight + 2; // era - 4;

	                for (i=0; i<nselect; i++)
		            {
                        if (i == 0)
		                    TextOut(hDC, XX0+Maxlstr+10, YY, "( -- )", 6);
                        else if (i == 1)
		                    TextOut(hDC, XX0+Maxlstr+10, YY, "( o )", 5);
                        if (i == 2)
		                     TextOut(hDC, XX0+Maxlstr+10, YY, "( x )", 5);
                        if (i == 3)
		                     TextOut(hDC, XX0+Maxlstr+10, YY, "(   )", 5);

	                    YY += textmetric.tmHeight - 1;
		            }
		        }
	
                if (Scale == 0)
		        {
		            for (i=0; i<nselect; i++)
                    {
	                    YY = YY1 - textmetric.tmHeight + 2 - 
                             (nselect - i - 1)*(textmetric.tmHeight - 3);

                        dtem = 0.25*(MaxOrd[i+1] - MinOrd[i+1]);

                        if (Color == 1)
                            SetTextColor(hDC, RGB(Rcolor[i], Gcolor[i], 
                                         Bcolor[i]));

	                    for (j=0; j<5; j++)
	  	                {
	                        convReal(str, MinOrd[i+1]+j*dtem, 4, 8);
							strcat(str,"         ");
		                    TextOut(hDC, XX1+6, YY, str, strlen(str));
	                        YY -= retidy - delta[nselect-1];///////!!!!!!!!!
		                }
	 	            }
		        }

		        else
		        {
	                YY = YY1 - textmetric.tmHeight + 2;

                    dtem = 0.25*(maxore - minore);
                    SetTextColor(hDC, RGB(0, 0, 0));

	                for (j=0; j<5; j++)
	  	            {
	                    convReal(str, minore+j*dtem, 4, 8);
		                TextOut(hDC, XX1+6, YY, str, strlen(str));
	                    YY -= retidy - delta[0];
	 	            }
	      	    }

                SelectObject(hDC, hOldBrush);
	        }

            else
	        {
		        hOldBrush = SelectObject(hDC, hBluMarineBrush);
                GetClientRect(hWnd, (LPRECT) &rect);
                PatBlt(hDC, rect.left, rect.top, 120,
                           rect.bottom - rect.top, PATCOPY);
                SelectObject(hDC, hGreenBrush);
                PatBlt(hDC, rect.left+120, rect.top, 2,
                           rect.bottom - rect.top, PATCOPY);
 		        SelectObject(hDC, hOldBrush); 

                hMemoryDC = CreateCompatibleDC(hDC);

                SelectObject(hMemoryDC, hBitmapBK);
                GetObject(hBitmapBK, sizeof(BITMAP), (LPSTR) &Bitmap);

				if (hfile == INVALID_HANDLE_VALUE)
                {
                     SetTextColor(hDC, RGB(255, 255, 255));
					 SetBkColor(hDC, RGB(0, 128, 128));
					 strcpy(str,"Open a file...");
		             TextOut(hDC, 10, 20, str, strlen(str));
                }
				else
                {
                     SetTextColor(hDC, RGB(255, 255, 255));
					 SetBkColor(hDC, RGB(0, 128, 128));
					 strcpy(str,"Select the variables");
		             TextOut(hDC, 10, 20, str, strlen(str));
					 strcpy(str,"to plot...");
		             TextOut(hDC, 10, 40, str, strlen(str));
                }

                BitBlt(hDC, rect.left, rect.top, rect.right - rect.left,
                           rect.bottom - rect.top, hMemoryDC, 
                           -150, -20, SRCCOPY);
		        DeleteDC(hMemoryDC);

	            XX0 = 0;
	            XX1 = 0;
	            YY0 = 0;
	            YY1 = 0;
	        }
			
            SelectObject(hDC, holdFont);
	        EndPaint(hWnd, &ps);
            Refresh = 0;
            break;


        case WM_SYSCOMMAND:
            if ((wParam & 0xFFF0) == SC_TASKLIST)
                break;

            else if ((wParam & 0xFFF0) == SC_CLOSE)
            {
                DestroyWindow(hWnd);
                break;
            }


        default:
            return (DefWindowProc(hWnd, message, wParam, lParam));
    }
    return (0);
}


/****************************************************************************

    FUNCTION: ReadHeaderF22(HWND)

    PURPOSE: read F22 file header

    COMMENTS: 

****************************************************************************/

int ReadHeaderF22(hWnd)
HWND hWnd;
{
	HDC hDC;
	int i, j, k, bRead;
	int chrbuf[123];	

	/*  lettura del titolo  */
        ReadFile(hfile, titolo, 80, &bRead, (LPOVERLAPPED) NULL);
        if (bRead != 80) 
        {
            sprintf(str, "Error reading %s header", FileName);
            MessageBox(hWnd, str, PrgName, MB_OK | MB_ICONEXCLAMATION);
            return (0);
        }
	
	/* lettura numero curve */
        ReadFile(hfile, &ncurve, sizeof(int), &bRead, (LPOVERLAPPED) NULL);
        if (bRead != sizeof(int)) 
        {
            sprintf(str, "Error reading %s header", FileName);
            MessageBox(hWnd, str, PrgName, MB_OK | MB_ICONEXCLAMATION);
            return (0);
        }

        if (ncurve > MAXCURVA)
        {
            sprintf(str, "Maximum number of curves exceeded - MAX=%d current=%d", MAXCURVA,ncurve);
			MessageBox(hWnd, str, PrgName, MB_OK | MB_ICONEXCLAMATION);
            return (0);
        }

        /* Allocate edit buffer */
	    hCurva = GlobalAlloc(GMEM_MOVEABLE | GMEM_ZEROINIT, (long) 80*ncurve);

        if (!hCurva)
        {
            MessageBox(hWnd, "Not enough memory [Curva]",
                              PrgName, MB_OK | MB_ICONSTOP);
            return (0);
        }

        pCurva = GlobalLock(hCurva);

	/* lettura nomi variabili */
        for (i=0; i<ncurve; i++) 
        {
            ReadFile(hfile, str, 80, &bRead, (LPOVERLAPPED) NULL);
            if (bRead != 80) 
            {
                sprintf(str, "Error reading %s header", FileName);
                MessageBox(hWnd, str, PrgName, MB_OK | MB_ICONEXCLAMATION);
                GlobalUnlock(hCurva);
                GlobalFree(hCurva);
                return (0);
            }

            k = i*80;
            for (j=0; j<80; j++)
                 pCurva[k+j] = str[j];

            curva[i] = pCurva + 80*i;
	    }

	    hDC = GetDC(hWnd);
	    GetCharWidth(hDC, 0, 122, (LPINT) chrbuf);
	    ReleaseDC(hWnd, hDC);

        compatstr(chrbuf);

        GlobalUnlock(hCurva);

	    hBuffer = LocalAlloc(LMEM_MOVEABLE | LMEM_ZEROINIT, 
                            (ncurve+1)*sizeof(double));

        if (!hBuffer) 
        {
            MessageBox(hWnd, "Not enough memory [Buffer]",
                              PrgName, MB_OK | MB_ICONSTOP);
            GlobalFree(hCurva);
            return (0);
        }

        sizbuffer = SIZBUFFER;
        for (i=0; i<MAXSELECT+1; i++)
        {
	         hOrd[i] = GlobalAlloc(GMEM_MOVEABLE | GMEM_ZEROINIT, 
                                  (long) (sizbuffer*sizeof(double)));
             if (!hOrd[i]) 
             {
                 MessageBox(hWnd, "Not enough memory [Ord]",
                            PrgName, MB_OK | MB_ICONSTOP);
                 GlobalFree(hCurva);
                 LocalFree(hBuffer);
                 return (0);
             }
	}

	return(TRUE);
}


/****************************************************************************

    FUNCTION: ReadG22(HWND)

    PURPOSE: read G22 file 

    COMMENTS: 

****************************************************************************/
int ReadG22(hWnd)
HWND hWnd;
{
        struct stGroup rGroup;
		int i, j, bRead;
//guag dic 2003 gruppi
/* rewind file */
		SetFilePointer(hGfile, 0, (PLONG) NULL, FILE_BEGIN); 	
	/* lettura numero dei gruppi */
		ReadFile(hGfile, &ngroup, sizeof(int), &bRead, (LPOVERLAPPED) NULL);
        if (bRead == 0) 
	        ngroup = 0;

        /* Allocate buffer */
        nAgroup = ngroup + 10;
	    hGroup = GlobalAlloc(GMEM_MOVEABLE | GMEM_ZEROINIT, 
                            (long) (nAgroup*sizeof(struct stGroup)));
        if (!hGroup)
        {
            MessageBox(hWnd, "Not enough memory [Group]",
                       PrgName, MB_OK | MB_ICONSTOP);
            return (0);
        }

        pGroup = (struct stGroup *) GlobalLock(hGroup);

 	 /* lettura gruppi */
        for (i=0; i<ngroup; i++) 
        {
		    ReadFile(hGfile, &rGroup, sizeof(struct stGroup), &bRead, (LPOVERLAPPED) NULL);
            if (bRead != sizeof(struct stGroup)) 
            {
                sprintf(str, "Error reading %s groups", OpenGName);
                MessageBox(hWnd, str, PrgName, MB_OK | MB_ICONEXCLAMATION);
                GlobalUnlock(hGroup);
                GlobalFree(hGroup);
                return (0);
            }

	        pGroup[i].nselect = rGroup.nselect;

            lstrcpy(pGroup[i].descr, (LPSTR) rGroup.descr);

            for (j=0; j<MAXSELECT; j++)
            {
                lstrcpy(pGroup[i].select[j], (LPSTR) rGroup.select[j]);
	            pGroup[i].MaxOrdM[j+1] = rGroup.MaxOrdM[j+1];
	            pGroup[i].MinOrdM[j+1] = rGroup.MinOrdM[j+1];
	            pGroup[i].MaxOrdA[j+1] = rGroup.MaxOrdA[j+1];
	            pGroup[i].MinOrdA[j+1] = rGroup.MinOrdA[j+1];

	        }

	        pGroup[i].Grid  = rGroup.Grid;
	        pGroup[i].Auto  = rGroup.Auto;
	        pGroup[i].Scale = rGroup.Scale;
	        pGroup[i].Color = rGroup.Color;
	    }

        GlobalUnlock(hGroup);
	    return(TRUE);
}


/****************************************************************************

    FUNCTION: WriteG22()

    PURPOSE: Write G22 file 

    COMMENTS: 

****************************************************************************/
int WriteG22()

{
        struct stGroup rGroup;
		int i, j, bWrite;
		
	/* rewind file */
		SetFilePointer(hGfile, 0, (PLONG) NULL, FILE_BEGIN); 

	/* scrittura del numero dei gruppi */
        WriteFile(hGfile, &ngroup, sizeof(int), &bWrite, (LPOVERLAPPED) NULL);

	/* scrittura dei gruppi */
        pGroup = (struct stGroup *) GlobalLock(hGroup);

        for (i=0; i<ngroup; i++) 
        {
	        rGroup.nselect = pGroup[i].nselect;

            lstrcpy((LPSTR) rGroup.descr, pGroup[i].descr);

            for (j=0; j<MAXSELECT; j++)
            {
                lstrcpy((LPSTR) rGroup.select[j], pGroup[i].select[j]);
	            rGroup.MaxOrdM[j+1] = pGroup[i].MaxOrdM[j+1];
	            rGroup.MinOrdM[j+1] = pGroup[i].MinOrdM[j+1];
	            rGroup.MaxOrdA[j+1] = pGroup[i].MaxOrdA[j+1];
	            rGroup.MinOrdA[j+1] = pGroup[i].MinOrdA[j+1];

	        }

	        rGroup.Grid  = pGroup[i].Grid;
	        rGroup.Auto  = pGroup[i].Auto;
	        rGroup.Scale = pGroup[i].Scale;
	        rGroup.Color = pGroup[i].Color;

            WriteFile(hGfile, &rGroup, sizeof(struct stGroup), &bWrite, (LPOVERLAPPED) NULL);
	    }

        GlobalUnlock(hGroup);
        return(0);
}               


/****************************************************************************

    FUNCTION: SetScale(HWND, unsigned, WORD, LONG)

    PURPOSE: Let user select a file, and return.  Open code not provided.

****************************************************************************/

int CALLBACK SetScale(hDlg, message, wParam, lParam)
HWND hDlg;
unsigned message;
WPARAM wParam;
LPARAM lParam;
{
    HWND hList;
    LONG index;
    char valstr[20];
    int i;

    switch (message)
    {
        case WM_COMMAND:
            switch (LOWORD(wParam)) 
            {
                case IDY_BUTT1:
                    switch (HIWORD(wParam)) 
                    {
                        case BN_CLICKED:
			                ;
                        case BN_DOUBLECLICKED:
			                if (Bscal == 2)
			                {
		                        GetDlgItemText(hDlg, IDY_MAXVALUE, 
                                              (LPSTR) valstr, 20);
		                        MaxOrdM[2] = atof(valstr);		    

		                        GetDlgItemText(hDlg, IDY_MINVALUE, 
                                              (LPSTR) valstr, 20);
		                        MinOrdM[2] = atof(valstr);		    

                                hList=GetDlgItem(hDlg, IDY_BUTT2);
                                index = SendMessage(hList, BM_SETCHECK, 0, 0);
			                }

			                else if (Bscal == 3)
			                {
		                        GetDlgItemText(hDlg, IDY_MAXVALUE, 
                                              (LPSTR) valstr, 20);
		                        MaxOrdM[3] = atof(valstr);		    

		                        GetDlgItemText(hDlg, IDY_MINVALUE, 
                                               (LPSTR) valstr, 20);
		                        MinOrdM[3] = atof(valstr);		    

                                hList=GetDlgItem(hDlg, IDY_BUTT3);
                                index = SendMessage(hList, BM_SETCHECK, 0, 0);
			                }
			                else if (Bscal == 4)
			                {
		                        GetDlgItemText(hDlg, IDY_MAXVALUE, 
                                              (LPSTR) valstr, 20);
		                        MaxOrdM[4] = atof(valstr);		    

		                        GetDlgItemText(hDlg, IDY_MINVALUE, 
                                               (LPSTR) valstr, 20);
		                        MinOrdM[4] = atof(valstr);		    

                                hList=GetDlgItem(hDlg, IDY_BUTT4);
                                index = SendMessage(hList, BM_SETCHECK, 0, 0);
			                }

		                    Bscal = 1;
                            hList=GetDlgItem(hDlg, IDY_BUTT1);
                            index = SendMessage(hList, BM_SETCHECK, 1, 0);

                            convReal(str, MaxOrdA[1], 7, 8);
  	                        SetDlgItemText(hDlg, IDY_MAXAUTO, (LPSTR) str);

                            convReal(str, MinOrdA[1], 7, 8);
 	                        SetDlgItemText(hDlg, IDY_MINAUTO, (LPSTR) str);

                            convReal(str, MaxOrdM[1], 7, 8);
 	                        SetDlgItemText(hDlg, IDY_MAXVALUE, (LPSTR) str);

                            convReal(str, MinOrdM[1], 7, 8);
 	                        SetDlgItemText(hDlg, IDY_MINVALUE, (LPSTR) str);
                        }
		                return (FALSE);

                case IDY_BUTT2:
                    switch (HIWORD(wParam)) 
                    {
                        case BN_CLICKED:
			                ;
                        case BN_DOUBLECLICKED:
                            if (nselect >= 2)
                            {
			                    if (Bscal == 1)
			                    {
		                            GetDlgItemText(hDlg, IDY_MAXVALUE, 
                                                  (LPSTR) valstr, 20);
		                            MaxOrdM[1] = atof(valstr);		    

		                            GetDlgItemText(hDlg, IDY_MINVALUE, 
                                                  (LPSTR) valstr, 20);
		                            MinOrdM[1] = atof(valstr);		    

                                    hList=GetDlgItem(hDlg, IDY_BUTT1);
                                    index = SendMessage(hList, BM_SETCHECK, 0, 0);
			                    }

			                    else if (Bscal == 3)
			                    {
		                            GetDlgItemText(hDlg, IDY_MAXVALUE, 
                                                  (LPSTR) valstr, 20);
		                            MaxOrdM[3] = atof(valstr);		    

		                            GetDlgItemText(hDlg, IDY_MINVALUE, 
                                                   (LPSTR) valstr, 20);
		                            MinOrdM[3] = atof(valstr);		    

                                    hList=GetDlgItem(hDlg, IDY_BUTT3);
                                    index = SendMessage(hList, BM_SETCHECK, 0, 0);
                             
			                    }
								 else if (Bscal == 4)
								{
									 GetDlgItemText(hDlg, IDY_MAXVALUE, 
                                              (LPSTR) valstr, 20);
									 MaxOrdM[4] = atof(valstr);		    

									 GetDlgItemText(hDlg, IDY_MINVALUE, 
                                               (LPSTR) valstr, 20);
		                             MinOrdM[4] = atof(valstr);		    

                                     hList=GetDlgItem(hDlg, IDY_BUTT4);
                                     index = SendMessage(hList, BM_SETCHECK, 0, 0);
								}

		                        Bscal = 2;
                                hList=GetDlgItem(hDlg, IDY_BUTT2);
                                index = SendMessage(hList, BM_SETCHECK, 1, 0); 
                                convReal(str, MaxOrdA[2], 7, 8);
  	                            SetDlgItemText(hDlg, IDY_MAXAUTO, (LPSTR) str);

                                convReal(str, MinOrdA[2], 7, 8);
 	                            SetDlgItemText(hDlg, IDY_MINAUTO, (LPSTR) str);

                                convReal(str, MaxOrdM[2], 7, 8);
 	                            SetDlgItemText(hDlg, IDY_MAXVALUE, (LPSTR) str);

                                convReal(str, MinOrdM[2], 7, 8);
 	                            SetDlgItemText(hDlg, IDY_MINVALUE, (LPSTR) str);

		                    }

		                    else
                            {
                                hList=GetDlgItem(hDlg, IDY_BUTT2);
                                index = SendMessage(hList, BM_SETCHECK, 0, 0); 
                                if (Bscal == 1)
                                {
                                    hList=GetDlgItem(hDlg, IDY_BUTT1);
                                    index = SendMessage(hList, BM_SETCHECK, 1, 0);
                                }

                                else if (Bscal == 3)
                                {
                                    hList=GetDlgItem(hDlg, IDY_BUTT3);
                                    index = SendMessage(hList, BM_SETCHECK, 1, 0);
                                }
                                else if (Bscal == 4)
                                {
                                    hList=GetDlgItem(hDlg, IDY_BUTT4);
                                    index = SendMessage(hList, BM_SETCHECK, 1, 0);
                                }
		                    }
                        }
	 	                return (FALSE);

                case IDY_BUTT3:
                    switch (HIWORD(wParam)) 
                    {
                        case BN_CLICKED:
			                 ;
                        case BN_DOUBLECLICKED:
                            if (nselect >= 3)
                            {
			                    if (Bscal == 1)
			                    {
		                            GetDlgItemText(hDlg, IDY_MAXVALUE, 
                                                  (LPSTR) valstr, 20);
		                            MaxOrdM[1] = atof(valstr);		    

		                            GetDlgItemText(hDlg, IDY_MINVALUE, 
                                                  (LPSTR) valstr, 20);
		                            MinOrdM[1] = atof(valstr);		    

                                    hList=GetDlgItem(hDlg, IDY_BUTT1);
                                    index = SendMessage(hList, BM_SETCHECK, 0, 0);
			                    }

			                    else if (Bscal == 2)
			                    {
		                            GetDlgItemText(hDlg, IDY_MAXVALUE, 
                                                  (LPSTR) valstr, 20);
		                            MaxOrdM[2] = atof(valstr);		    

		                            GetDlgItemText(hDlg, IDY_MINVALUE, 
                                                  (LPSTR) valstr, 20);
		                            MinOrdM[2] = atof(valstr);		    

                                    hList=GetDlgItem(hDlg, IDY_BUTT2);
                                    index = SendMessage(hList, BM_SETCHECK, 0, 0);
			                    }
								 else if (Bscal == 4)
								{
									 GetDlgItemText(hDlg, IDY_MAXVALUE, 
                                              (LPSTR) valstr, 20);
									 MaxOrdM[4] = atof(valstr);		    

									 GetDlgItemText(hDlg, IDY_MINVALUE, 
                                               (LPSTR) valstr, 20);
		                             MinOrdM[4] = atof(valstr);		    

                                     hList=GetDlgItem(hDlg, IDY_BUTT4);
                                     index = SendMessage(hList, BM_SETCHECK, 0, 0);
								}

		                        Bscal = 3;
                                hList=GetDlgItem(hDlg, IDY_BUTT3);
                                index = SendMessage(hList, BM_SETCHECK, 1, 0); 
                                convReal(str, MaxOrdA[3], 7, 8);
  	                            SetDlgItemText(hDlg, IDY_MAXAUTO, (LPSTR) str);

                                convReal(str, MinOrdA[3], 7, 8);
 	                            SetDlgItemText(hDlg, IDY_MINAUTO, (LPSTR) str);

                                convReal(str, MaxOrdM[3], 7, 8);
 	                            SetDlgItemText(hDlg, IDY_MAXVALUE, (LPSTR) str);

                                convReal(str, MinOrdM[3], 7, 8);
 	                            SetDlgItemText(hDlg, IDY_MINVALUE, (LPSTR) str);
		                    }

		                    else
                            {
                                hList=GetDlgItem(hDlg, IDY_BUTT3);
                                index = SendMessage(hList, BM_SETCHECK, 0, 0);
                                if (Bscal == 1)
                                {
                                    hList=GetDlgItem(hDlg, IDY_BUTT1);
                                    index = SendMessage(hList, BM_SETCHECK, 1, 0);
	 		                    }

                                else if (Bscal == 2)
                                {
                                    hList=GetDlgItem(hDlg, IDY_BUTT2);
                                    index = SendMessage(hList, BM_SETCHECK, 1, 0);
	 		                    }
                                else if (Bscal == 4)
                                {
                                    hList=GetDlgItem(hDlg, IDY_BUTT4);
                                    index = SendMessage(hList, BM_SETCHECK, 1, 0);
	 		                    }
		                    }
		                }
		                return (FALSE);

					case IDY_BUTT4:    // vedi MAXSELECT
                    switch (HIWORD(wParam)) 
                    {
                        case BN_CLICKED:
			                 ;
                        case BN_DOUBLECLICKED:
                            if (nselect >= 4)
                            {
			                    if (Bscal == 1)
			                    {
		                            GetDlgItemText(hDlg, IDY_MAXVALUE, 
                                                  (LPSTR) valstr, 20);
		                            MaxOrdM[1] = atof(valstr);		    

		                            GetDlgItemText(hDlg, IDY_MINVALUE, 
                                                  (LPSTR) valstr, 20);
		                            MinOrdM[1] = atof(valstr);		    

                                    hList=GetDlgItem(hDlg, IDY_BUTT1);
                                    index = SendMessage(hList, BM_SETCHECK, 0, 0);
			                    }

			                    else if (Bscal == 2)
			                    {
		                            GetDlgItemText(hDlg, IDY_MAXVALUE, 
                                                  (LPSTR) valstr, 20);
		                            MaxOrdM[2] = atof(valstr);		    

		                            GetDlgItemText(hDlg, IDY_MINVALUE, 
                                                  (LPSTR) valstr, 20);
		                            MinOrdM[2] = atof(valstr);		    

                                    hList=GetDlgItem(hDlg, IDY_BUTT2);
                                    index = SendMessage(hList, BM_SETCHECK, 0, 0);
			                    }
			                    else if (Bscal == 3)
			                    {
		                            GetDlgItemText(hDlg, IDY_MAXVALUE, 
                                                  (LPSTR) valstr, 20);
		                            MaxOrdM[3] = atof(valstr);		    

		                            GetDlgItemText(hDlg, IDY_MINVALUE, 
                                                   (LPSTR) valstr, 20);
		                            MinOrdM[3] = atof(valstr);		    

                                    hList=GetDlgItem(hDlg, IDY_BUTT3);
                                    index = SendMessage(hList, BM_SETCHECK, 0, 0);
                             
			                    }

		                        Bscal = 4;
                                hList=GetDlgItem(hDlg, IDY_BUTT4);
                                index = SendMessage(hList, BM_SETCHECK, 1, 0); 
                                convReal(str, MaxOrdA[4], 7, 8);
  	                            SetDlgItemText(hDlg, IDY_MAXAUTO, (LPSTR) str);

                                convReal(str, MinOrdA[4], 7, 8);
 	                            SetDlgItemText(hDlg, IDY_MINAUTO, (LPSTR) str);

                                convReal(str, MaxOrdM[4], 7, 8);
 	                            SetDlgItemText(hDlg, IDY_MAXVALUE, (LPSTR) str);

                                convReal(str, MinOrdM[4], 7, 8);
 	                            SetDlgItemText(hDlg, IDY_MINVALUE, (LPSTR) str);
		                    }

		                    else
                            {
                                hList=GetDlgItem(hDlg, IDY_BUTT3);
                                index = SendMessage(hList, BM_SETCHECK, 0, 0);
                                if (Bscal == 1)
                                {
                                    hList=GetDlgItem(hDlg, IDY_BUTT1);
                                    index = SendMessage(hList, BM_SETCHECK, 1, 0);
	 		                    }

                                else if (Bscal == 2)
                                {
                                    hList=GetDlgItem(hDlg, IDY_BUTT2);
                                    index = SendMessage(hList, BM_SETCHECK, 1, 0);
	 		                    }
	                            else if (Bscal == 3)
                                {
                                    hList=GetDlgItem(hDlg, IDY_BUTT3);
                                    index = SendMessage(hList, BM_SETCHECK, 1, 0);
	 		                    }
		                    }
		                }
		                return (FALSE);

                case IDOK:
		            GetDlgItemText(hDlg, IDY_MAXVALUE, (LPSTR) valstr, 20);
		            MaxOrdM[Bscal] = atof(valstr);

		            GetDlgItemText(hDlg, IDY_MINVALUE, (LPSTR) valstr, 20);
		            MinOrdM[Bscal] = atof(valstr);

		            MaxOM = -1.e30;
		            MinOM =  1.e30;
	                for (i=1; i<nselect+1; i++)
                    {
			            if (MaxOrdM[i] > MaxOM)
	                        MaxOM = MaxOrdM[i];   

			            if (MinOrdM[i] < MinOM)
	                        MinOM = MinOrdM[i];   
		            }

                    if (Auto == 0)
                    {
                        MinO = MinOM;
                        MaxO = MaxOM;

			            for (i=1; i<MAXSELECT+1; i++)
                        {
	                        MaxOrd[i] = MaxOrdM[i];   
	                        MinOrd[i] = MinOrdM[i];   
		                }

	                }

                    EndDialog(hDlg, 1);
                    return (TRUE);

                case IDCANCEL:
                    EndDialog(hDlg, 0);
                    return (TRUE);
            }
            break;

        case WM_INITDIALOG:                        /* message: initialize    */
            UpdateSetScale(hDlg);
       	    SetFocus(GetDlgItem(hDlg, IDY_MAXVALUE));
            return (FALSE); /* Indicates the focus is set to a control */
    }
    return (FALSE);
}

/****************************************************************************

    FUNCTION: UpdateSetScale(HWND);

    PURPOSE: Update the list box of SetScale

****************************************************************************/

void UpdateSetScale(hDlg)
HWND hDlg;
{
    HWND hList;
    LONG index;

    Bscal = 1;
    if (nselect >= 1)	
    {
        strcpy(str, SELECT[0]);
        str[8] = '\0';
        SetDlgItemText(hDlg, IDY_BUTT1, (LPSTR) str);

        hList=GetDlgItem(hDlg, IDY_BUTT1);
        index = SendMessage(hList, BM_SETCHECK, 1, 0);

        convReal(str, MaxOrdA[1], 7, 8);
 	    SetDlgItemText(hDlg, IDY_MAXAUTO, (LPSTR) str);

        convReal(str, MinOrdA[1], 7, 8);
 	    SetDlgItemText(hDlg, IDY_MINAUTO, (LPSTR) str);

        convReal(str, MaxOrdM[1], 7, 8);
 	    SetDlgItemText(hDlg, IDY_MAXVALUE, (LPSTR) str);

        convReal(str, MinOrdM[1], 7, 8);
 	    SetDlgItemText(hDlg, IDY_MINVALUE, (LPSTR) str);
    }
	
    if (nselect >= 2)	
    {
        strcpy(str, SELECT[1]);
        str[8] = '\0';
 	    SetDlgItemText(hDlg, IDY_BUTT2, (LPSTR) str);
    }

    else
 	    SetDlgItemText(hDlg, IDY_BUTT2, "-");

    if (nselect >= 3)	
    {
        strcpy(str, SELECT[2]);
        str[8] = '\0';
 	    SetDlgItemText(hDlg, IDY_BUTT3, (LPSTR) str);
    }
    else
 	    SetDlgItemText(hDlg, IDY_BUTT3, "-");

    if (nselect == 4)	// vedi MAXSELECT
    {
        strcpy(str, SELECT[3]);
        str[8] = '\0';
 	    SetDlgItemText(hDlg, IDY_BUTT4, (LPSTR) str);
    }

    else
 	    SetDlgItemText(hDlg, IDY_BUTT4, "-");
}


/*************************************************************************

		      compattazione liste di stringhe  

**************************************************************************/
void compatstr(chrbuf)
int chrbuf[];
{
	int i, j, k, klen;

	for (i=0, klen=0; i<ncurve; i++)
	{
	   for (j=0, k=0; j<8; j++)
	      k = k + chrbuf[curva[i][j]];

	   if (klen < k)
	      klen = k;
	}


	for (i=0; i<ncurve; i++)
	{
	   for (j=0, k=0; j<8; j++)
	      k = k + chrbuf[curva[i][j]];

	   while (k+2 < klen)
	   {
	      for (j=lstrlen(curva[i]); j>7; j--)
	           curva[i][j+1] = curva[i][j];	         	      
	      curva[i][8] = ' ';
	      k = k + chrbuf[32];
	   }
	}
}


/****************************************************************************
    FUNCTION: ReadF22(HWND)

    PURPOSE: read F22 file data

    COMMENTS: 
****************************************************************************/
int ReadF22(hWnd)
HWND hWnd;
{
	int i, j, bRead;

        pBuffer = (double *) LocalLock(hBuffer);
        for (i=0; i<MAXSELECT+1; i++) 
            pOrd[i] = (double *) GlobalLock(hOrd[i]);
//GUAG 16/07/2001
//        CloseHandle(hfile);
//		hfile = CreateFile(FileName, GENERIC_READ, 
//					   	   FILE_SHARE_READ | FILE_SHARE_WRITE,
//						   (LPSECURITY_ATTRIBUTES) NULL,
//						   OPEN_EXISTING,
//						   FILE_ATTRIBUTE_NORMAL, (HANDLE) NULL);
		SetFilePointer(hfile, 80 + sizeof(int) + 80*ncurve, (PLONG) NULL, FILE_BEGIN);

        j = 0;

		for(;;)
        {
            ReadFile(hfile, pBuffer, (ncurve+1)*sizeof(double), &bRead, (LPOVERLAPPED) NULL);
			if (bRead != (int) ((ncurve+1)*sizeof(double)))
				break;

			pOrd[0][j] = pBuffer[0];                

            for (i=0; i<nselect; i++)
                pOrd[i+1][j] = pBuffer[iselect[i] + 1];

            j++;

	        if (j == sizbuffer)
			{
                for (i=0; i<MAXSELECT+1; i++) 
	            GlobalUnlock(hOrd[i]);

                sizbuffer = sizbuffer + SIZBUFFER;

                for (i=0; i<MAXSELECT+1; i++)
	            {
                    hOrd[i] = GlobalReAlloc(hOrd[i], 
                              (long) (sizbuffer*sizeof(double)), 
                              GMEM_MOVEABLE | GMEM_ZEROINIT);

                    if (!hOrd[i])
	                {
                        MessageBox(hWnd, "Not enough memory [Ord]",
                                   PrgName, MB_OK | MB_ICONSTOP);
                        return (0);
	                }
                }

                for (i=0; i<MAXSELECT+1; i++) 
                    pOrd[i] = (double *) GlobalLock(hOrd[i]);
            }
        }

        npunti = j;

        LocalUnlock(hBuffer);

        for (i=0; i<MAXSELECT+1; i++) 
	        GlobalUnlock(hOrd[i]);

	return(TRUE);
}



/****************************************************************************
    FUNCTION: MinMaxDati()

    PURPOSE: calculate min max 

    COMMENTS: 
****************************************************************************/
int MinMaxDati()
{
	int i, j;
	double deltax;

        for (i=0; i<MAXSELECT+1; i++) 
             pOrd[i] = (double *) GlobalLock(hOrd[i]);
 
        for (i=0; i<nselect+1; i++) 
        {
            MinOrd[i] =  1.e30;
            MaxOrd[i] = -1.e30;
            for (j=Poini; j<Pofin; j++) 
            {
                if (pOrd[i][j] < MinOrd[i])
		            MinOrd[i] = pOrd[i][j];
	
                if (pOrd[i][j] > MaxOrd[i])
		            MaxOrd[i] = pOrd[i][j];
	        }
	    }

        for (i=0; i<MAXSELECT+1; i++) 
	        GlobalUnlock(hOrd[i]);

        for (i=1; i<nselect+1; i++) 
            if (MinOrd[i] == MaxOrd[i])
	        {
		        deltax = 0.0005*(MinOrd[i] + MaxOrd[i]);
	            if (deltax == 0.)
                    deltax = 0.001;

	            MinOrd[i] = MinOrd[i] - deltax;
	            MaxOrd[i] = MaxOrd[i] + deltax;
            }

        MinO =  1.e30;
        MaxO = -1.e30;
        for (i=1; i<nselect+1; i++) 
        {
            if (MinOrd[i] < MinO)
		        MinO = MinOrd[i];
	
            if (MaxOrd[i] > MaxO)
		        MaxO = MaxOrd[i];
	    }

	    return(TRUE);
}



/***************************************************************************
 converte un double "aa" in  una  stringa "stringa"  con  formato  floating o
 exp a  seconda del valore di "aa" : "stringa" e' lunga al massimo "lunreale"
 caratteri. I numeri significativi sono al massimo "mantissa".
*****************************************************************************/
void convReal(stringa, aa, mantissa, lunreale)
char *stringa;
double aa;
int mantissa, lunreale;
{
	char ss[300], mant[300];
	char esp[5];
	int espi, msig;
	int i, j, k;

	sprintf(ss, "%-.8e", aa);

	for (i=lstrlen((LPSTR) ss)-4, k=0; i<lstrlen((LPSTR) ss); i++, k++)
	    esp[k] = ss[i];

	esp[k] = '\0';

	espi = atoi(esp);
	j = atoi(&esp[1]);
	sprintf(esp, "%-d", j);

    if (aa >= 0)
        msig = 0;
	else
	    msig = 1;

    mant[0] = ss[msig];
	for (i=msig+2, k=1; i<lstrlen((LPSTR) ss)-6; i++, k++)
	    mant[k] = ss[i];

	mant[k] = '\0';

/* FLOATING  numero > 0 con esponente > 0 */
	if (msig==0 && (espi>=0 && espi<=mantissa-1))
    {
        if (mantissa > lunreale-1)
	        mantissa = lunreale-1;

        stringa[0] = mant[0];
	    for (i=1, k=1; k<mantissa+1; i++, k++)
        {
            if (espi+1 == i)
	        {
	            stringa[k] = '.';
	            k++;
	        }
	        stringa[k] = mant[i];
	    }
	    stringa[mantissa+1] = '\0';

        for (i=mantissa; i>0; i--)
	        if (stringa[i] == '0')
	            stringa[i] = '\0';
	        else
	            break;
	}

/* FLOATING  numero < 0 con esponente > 0 */
	else if (msig==1 && (espi>=0 && espi<=mantissa-1))
    {
        if (mantissa > lunreale-2)
	        mantissa = lunreale-2;

        stringa[0] = '-';
        stringa[1] = mant[0];
	    for (i=1, k=2; k<mantissa+2; i++, k++)
        {
            if (espi+1 == i)
	        {
	            stringa[k] = '.';
	            k++;
	        }
	        stringa[k] = mant[i];
	    }
	    stringa[mantissa+2] = '\0';

        for (i=mantissa+1; i>0; i--)
	        if (stringa[i] == '0')
	            stringa[i] = '\0';
	        else
	            break;
	}

/* FLOATING  numero > 0 con esponente < 0 */
	if (msig==0 && (espi>=-mantissa+2 && espi<0))
    {
        if (mantissa > lunreale-1+espi)
	        mantissa = lunreale-1+espi;

        stringa[0] = '0';
        stringa[1] = '.';
	    for (i=espi+1, k=2; i<0; i++, k++)
	        stringa[k] = '0';

	    for (i=0; i<mantissa; i++, k++)
	        stringa[k] = mant[i];
	    stringa[k] = '\0';

        for (i=k-1; i>0; i--)
	        if (stringa[i] == '0')
	            stringa[i] = '\0';
            else
                break;
	}


/* FLOATING  numero < 0 con esponente < 0 */
	if (msig==1 && (espi>=-mantissa+2 && espi<0))
    {
        if (mantissa > lunreale-2+espi)
	        mantissa = lunreale-2+espi;

        stringa[0] = '-';
        stringa[1] = '0';
        stringa[2] = '.';
	    for (i=espi+1, k=3; i<0; i++, k++)
	        stringa[k] = '0';

	    for (i=0; i<mantissa; i++, k++)
	        stringa[k] = mant[i];
	    stringa[k] = '\0';

        for (i=k-1; i>0; i--)
	        if (stringa[i] == '0')
	            stringa[i] = '\0';
            else
                break;
	}


/* EXPONENTIAL numero < 0 con esponente > 0 */
	if (msig==1 && espi>mantissa-1)
    {
        stringa[0] = '-';
        stringa[1] = mant[0];
        stringa[2] = '.';

	    for (i=1, k=3; i<mantissa; i++, k++)
        {
            if (k == lunreale-lstrlen((LPSTR) esp)-1)
               break;

	        stringa[k] = mant[i];
	    }
	    stringa[k] = '\0';

        for (i=k-1; i>0; i--)
	        if (stringa[i] == '0')
	            stringa[i] = '\0';
            else
                break;

	    strcat(stringa, "e");
	    strcat(stringa, esp);
	}


/* EXPONENTIAL numero > 0 con esponente > 0 */
	if (msig==0 && espi>mantissa-1)
    {
        stringa[0] = mant[0];
        stringa[1] = '.';

	    for (i=1, k=2; i<mantissa; i++, k++)
        {
            if (k == lunreale-lstrlen((LPSTR) esp)-1)
                break;

	        stringa[k] = mant[i];
	    }
	    stringa[k] = '\0';

        for (i=k-1; i>0; i--)
	        if (stringa[i] == '0')
	            stringa[i] = '\0';
            else
               break;

	    strcat(stringa, "e");
	    strcat(stringa, esp);
	}


/* EXPONENTIAL numero > 0 con esponente < 0 */
	if (msig==0 && espi<-mantissa+2)
    {
        stringa[0] = mant[0];
        stringa[1] = '.';

	    for (i=1, k=2; i<mantissa; i++, k++)
        {
            if (k == lunreale-lstrlen((LPSTR) esp)-2)
                break;

	        stringa[k] = mant[i];
	    }
	    stringa[k] = '\0';

        for (i=k-1; i>0; i--)
	        if (stringa[i] == '0')
	            stringa[i] = '\0';
            else
                break;

	    strcat(stringa, "e-");
	    strcat(stringa, esp);
	}


/* EXPONENTIAL numero < 0 con esponente < 0 */
	if (msig==1 && espi<-mantissa+2)
    {
        stringa[0] = '-';
        stringa[1] = mant[0];
        stringa[2] = '.';

	    for (i=1, k=3; i<mantissa; i++, k++)
        {
            if (k == lunreale-lstrlen((LPSTR) esp)-2)
                break;

	       stringa[k] = mant[i];
	    }
	    stringa[k] = '\0';

        for (i=k-1; i>0; i--)
	        if (stringa[i] == '0')
	            stringa[i] = '\0';
            else
                break;

	    strcat(stringa, "e-");
	    strcat(stringa, esp);
	}
}

/*******************************************************************
		command line decode
 *******************************************************************/
int DecodeCmdLine(command)
char command[];
{
	    int i, j;
        char ppp[200];        

        _givefile  = 0;
        _givevar   = 0;
        _givegrid  = 1;
        _givescale = 0;
        _givecolor = 1;
        _givecomm  = 0;

        ppp[0] = '\0';

	    for (i=0, j=0; i<=lstrlen((LPSTR) command); i++)
        {	
	        if (command[i] == ' ' || command[i] == '\0')
	        {
                if (j != 0)
		        {
                    ppp[j] = '\0';

                    if (ppp[0] != '/' && ppp[0] != '-')
		            {
                        strcpy(_filename, ppp);
                        _givefile = 1;
						return(0);
		            }
			            
 
                    if (!(strncmp(&ppp[1], "FILE=", 5)) ||
                        !(strncmp(&ppp[1], "file=", 5)))
		            {
                        strcpy(_filename, &ppp[6]);
                        _givefile = 1;
		            }

                    else if (!(strncmp(&ppp[1], "V=", 2)) ||
                             !(strncmp(&ppp[1], "v=", 2)))
		            {
                        strcpy(_varname[_givevar], &ppp[3]);
                        _givevar++;
		            }
					else if (!(strncmp(&ppp[1], "R=", 2)) ||
                             !(strncmp(&ppp[1], "r=", 2)))
		            {
                        sscanf(&ppp[3],"%d", &secTimer);
		            }
                    else if (!(strncmp(&ppp[1], "NG", 2)) ||
                             !(strncmp(&ppp[1], "ng", 2)))
                        _givegrid = 0;

                    else if (!(strncmp(&ppp[1], "G", 1)) ||
                             !(strncmp(&ppp[1], "g", 1)))
                        _givegrid = 1;

                    else if (!(strncmp(&ppp[1], "NA", 2)) ||
                             !(strncmp(&ppp[1], "na", 2)))
                        _givecomm = 0;

                    else if (!(strncmp(&ppp[1], "A", 1)) ||
                             !(strncmp(&ppp[1], "a", 1)))
                        _givecomm = 1;

                    else if (!(strncmp(&ppp[1], "SY", 2)) ||
                             !(strncmp(&ppp[1], "sy", 2)))
                        _givescale = 1;

                    else if (!(strncmp(&ppp[1], "NSY", 3)) ||
                             !(strncmp(&ppp[1], "nsy", 3)))
                        _givescale = 0;

                    else if (!(strncmp(&ppp[1], "NC", 2)) ||
                             !(strncmp(&ppp[1], "nc", 2)))
                        _givecolor = 0;

                    else if (!(strncmp(&ppp[1], "C", 1)) ||
                             !(strncmp(&ppp[1], "c", 1)))
                        _givecolor = 1;

                    else 
			            return(0);

	                ppp[0] = '\0';
                }
                j = 0;

	            continue;
            }

	        ppp[j] = command[i];   
            j++;
	    }

        if (_givefile == 0)
	        _givevar = 0;

	    return(1);
}
