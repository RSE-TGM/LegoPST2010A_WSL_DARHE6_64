#include "windows.h"
#include "resource.h"
#include "definit.h"
#include "stdio.h"
#include "string.h"
#include "math.h"

LPSTR PrgName;

#define MAXCURVA  1000
HANDLE hGroup;

HANDLE hGfile;
char FileName[128];
char OpenGName[128];
char DefGExt[13];
char str[255];

int ncurve;
LPSTR curva[MAXCURVA];
int ngroup;
int nAgroup;

extern int secTimer;

#define   MAXSELECT    4

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

int ifind;
char PSelect[128];

int nselect;
int nselect0;

int iselect[MAXSELECT];
char SELECT[MAXSELECT][80];

int Grid;
int Scale;
int Auto;
int Color;

double MaxOrdM[MAXSELECT+1];
double MinOrdM[MAXSELECT+1];
double MinOM, MaxOM;
double MaxOrdA[MAXSELECT+1];
double MinOrdA[MAXSELECT+1];
double MinOA, MaxOA;
double MaxOrd[MAXSELECT+1];
double MinOrd[MAXSELECT+1];
double MinO, MaxO;

int saveGroup;
char titolo[80];

void conv_minuscolo( char *, char *);

/****************************************************************************

    FUNCTION: GroupSel(HWND, unsigned, WORD, LONG)

    PURPOSE: Let user select a file, and return.  Open code not provided.

****************************************************************************/

int CALLBACK GroupSel(hDlg, message, wParam, lParam)
HWND hDlg;
unsigned message;
WPARAM wParam;
LPARAM lParam;
{
    HWND hList;
    LONG index;
    char Select[128];
    int i, j, kk;

    switch (message)
    {
        case WM_COMMAND:
            switch (LOWORD(wParam)) 
            {
                case IDOK:
                OKEY:
                    hList=GetDlgItem(hDlg, IDG_LISTBX);
					index = SendMessage(hList, LB_GETCURSEL, 0, 0); 
	                if (index == -1)
		                return(TRUE);

                    lstrcpy((LPSTR) Select, "\0");
                    DlgDirSelectEx(hDlg, (LPSTR) Select, 127, IDG_LISTBX);

                    kk=lstrlen((LPSTR) Select);
                    if (Select[kk-1] == '.')
	                Select[kk-1] = '\0';
                                   
	                for (kk=0; kk<ngroup; kk++)
	                    if (lstrcmp((LPSTR) Select, pGroup[kk].descr) == 0)
                            break;

                    for (i=0, nselect=0; i<pGroup[kk].nselect; i++)
	                    for (j=0; j<ncurve; j++)
	                        if (lstrcmp(pGroup[kk].select[i], curva[j]) == 0)
	                        {
	                            lstrcpy((LPSTR) SELECT[nselect], curva[j]);
	                            iselect[nselect] = j;
                                MinOrdA[nselect+1] = pGroup[kk].MinOrdA[i+1];
                                MaxOrdA[nselect+1] = pGroup[kk].MaxOrdA[i+1];
                                MinOrdM[nselect+1] = pGroup[kk].MinOrdM[i+1];
                                MaxOrdM[nselect+1] = pGroup[kk].MaxOrdM[i+1];
                                nselect++;
                                break;
	                        }

                    if (nselect != 0)
                    {
		                MaxOM = -1.e30;
		                MinOM =  1.e30;
	                    for (i=1; i<nselect+1; i++)
                        {
			                if (MaxOrdM[i] > MaxOM)
	                            MaxOM = MaxOrdM[i];  
							
			                if (MinOrdM[i] < MinOM)
	                            MinOM = MinOrdM[i];   
		                }

		                MaxOA = -1.e30;
		                MinOA =  1.e30;
	                    for (i=1; i<nselect+1; i++)
                        {
			                if (MaxOrdA[i] > MaxOA)
	                            MaxOA = MaxOrdA[i];   

			                if (MinOrdA[i] < MinOA)
	                            MinOA = MinOrdA[i];   
		                }
		            }                        

                    EndDialog(hDlg, kk);
                    return (TRUE);


                case IDG_DELETE:
                    hList=GetDlgItem(hDlg, IDG_LISTBX);
					index = SendMessage(hList, LB_GETCURSEL, 0, 0); 
	                if (index == -1)
		                return(TRUE);

                    lstrcpy((LPSTR) Select, "\0");
                    DlgDirSelectEx(hDlg, (LPSTR) Select, 127, IDG_LISTBX);

	                kk=lstrlen((LPSTR) Select);
                    if (Select[kk-1] == '.')
	                    Select[kk-1] = '\0';
                                   
	                for (kk=0; kk<ngroup; kk++)
	                    if (lstrcmp((LPSTR) Select, pGroup[kk].descr) == 0)
                            break;

		            for (i=kk; i<ngroup; i++)
		            {
                        pGroup[i].nselect = pGroup[i+1].nselect;
	                    lstrcpy(pGroup[i].descr, pGroup[i+1].descr);
                        for (j=0; j<pGroup[i].nselect; j++)
	                    lstrcpy(pGroup[i].select[j], pGroup[i+1].select[j]);

                        for (j=0; j<pGroup[i].nselect; j++)
                        {
                             pGroup[i].MinOrdA[j+1] = pGroup[i+1].MinOrdA[j+1];
                             pGroup[i].MaxOrdA[j+1] = pGroup[i+1].MaxOrdA[j+1];
                             pGroup[i].MinOrdM[j+1] = pGroup[i+1].MinOrdM[j+1];
                             pGroup[i].MaxOrdM[j+1] = pGroup[i+1].MaxOrdM[j+1];
			            }

                        pGroup[i].Grid  = pGroup[i+1].Grid;
                        pGroup[i].Auto  = pGroup[i+1].Auto;
                        pGroup[i].Scale = pGroup[i+1].Scale;
                        pGroup[i].Color = pGroup[i+1].Color;
                    }

		            ngroup--;

                    hList=GetDlgItem(hDlg, IDG_LISTVAR);

 	                SendMessage(hList, LB_RESETCONTENT, 0, 0); 
				              
                    hList=GetDlgItem(hDlg, IDG_LISTBX);

 	                index = SendMessage(hList, LB_DELETESTRING, kk, 
                                       (LONG) NULL);
  
		            wsprintf((LPSTR) str, "%d", ngroup);
 	                SetDlgItemText(hDlg, IDG_GROUPNUM, (LPSTR) str);
// guag dic 2003 gruppi
//                    saveGroup = 1;
					WriteG22();
// fine guag
                    return (TRUE);


                case IDG_LISTBX:
                    switch (HIWORD(wParam)) 
                    {
                        case LBN_DBLCLK:
                            goto OKEY;

                        case LBN_SELCHANGE:
                            hList=GetDlgItem(hDlg, IDG_LISTBX);
					        index = SendMessage(hList, LB_GETCURSEL, 0, 0); 
	                        if (index == -1)
		                        return(TRUE);

                            lstrcpy((LPSTR) Select, "\0");
                            DlgDirSelectEx(hDlg, (LPSTR) Select, 127, IDG_LISTBX);

	                        kk=lstrlen((LPSTR) Select);
                            if (Select[kk-1] == '.')
	                            Select[kk-1] = '\0';
                                   
	                        for (kk=0; kk<ngroup; kk++)
	                            if (lstrcmp((LPSTR) Select, pGroup[kk].descr) 
                                                                        == 0)
                                    break;

                            hList=GetDlgItem(hDlg, IDG_LISTVAR);

 	                        SendMessage(hList, LB_RESETCONTENT, 0, 0); 

	                        for (i=0; i<pGroup[kk].nselect; i++) 
 	                            index = SendMessage(hList, LB_ADDSTRING,
	                                    0, (LONG) pGroup[kk].select[i]);

                            return (TRUE);
                    }

                    return (TRUE);


                case IDCANCEL:
                    EndDialog(hDlg, -1);
                    return (TRUE);
            }
            break;

        case WM_INITDIALOG:                        /* message: initialize    */
            UpdateGroupSel(hDlg);
       	    SetFocus(GetDlgItem(hDlg, IDG_LISTBX));
            return (FALSE); /* Indicates the focus is set to a control */
    }
    return FALSE;
}

/****************************************************************************

    FUNCTION: MemoGroup(HWND, unsigned, WORD, LONG)

    PURPOSE: Let user select a file, and return.  Open code not provided.

****************************************************************************/

int CALLBACK MemoGroup(hDlg, message, wParam, lParam)
HWND hDlg;
unsigned message;
WPARAM wParam;
LPARAM lParam;
{
    char Select[128];
    int i;

    switch (message)
    {
        case WM_COMMAND:
            switch (LOWORD(wParam)) 
            {
                case IDOK:
                    GetDlgItemText(hDlg, IDG_DESCR, (LPSTR) Select, 128);
                    if (lstrlen((LPSTR) Select) == 0)
                        break;                    

	                Select[80] = '\0';

                    /* REAllocate buffer */
		            if (ngroup == nAgroup)
	                {
                        nAgroup = ngroup + 10;
			            GlobalUnlock(hGroup);
                        hGroup = GlobalReAlloc(hGroup, 
                                 (long) (nAgroup*sizeof(struct stGroup)), 
                                 GMEM_MOVEABLE | GMEM_ZEROINIT);

                        if (!hGroup)
	                    {
                            MessageBox(hDlg, "Not enough memory [Group]",
                                       PrgName, MB_OK | MB_ICONSTOP);
                            return (0);
	                    }

                        pGroup = (struct stGroup *) GlobalLock(hGroup);
                    }

                    lstrcpy(pGroup[ngroup].descr, (LPSTR) Select);
                    pGroup[ngroup].nselect = nselect;
	                for (i=0; i<nselect; i++)
                    {                    
			            lstrcpy(pGroup[ngroup].select[i], (LPSTR) SELECT[i]);
                        pGroup[ngroup].MaxOrdM[i+1] = MaxOrdM[i+1];
                        pGroup[ngroup].MinOrdM[i+1] = MinOrdM[i+1];
                        pGroup[ngroup].MaxOrdA[i+1] = MaxOrdA[i+1];
                        pGroup[ngroup].MinOrdA[i+1] = MinOrdA[i+1];
		            }

                    pGroup[ngroup].Auto  = Auto;
                    pGroup[ngroup].Scale = Scale;
                    pGroup[ngroup].Grid  = Grid;
                    pGroup[ngroup].Color = Color;

                    ngroup++;  

                    EndDialog(hDlg, 1);
                    return (TRUE);


                case IDCANCEL:
                    EndDialog(hDlg, 0);
                    return (TRUE);
            }
            break;

        case WM_INITDIALOG:                        /* message: initialize    */
            wsprintf((LPSTR) str, "%d", ngroup);
 	        SetDlgItemText(hDlg, IDG_GROUPNUM, (LPSTR) str);
       	    SetFocus(GetDlgItem(hDlg, IDG_DESCR));
            return (FALSE); /* Indicates the focus is set to a control */
    }
    return FALSE;
}


/****************************************************************************

    FUNCTION: RefrTime(HWND, unsigned, WORD, LONG)

    PURPOSE: Let user change refresh time.  Open code not provided.

****************************************************************************/

int CALLBACK RefrTime(hDlg, message, wParam, lParam)
HWND hDlg;
unsigned message;
WPARAM wParam;
LPARAM lParam;
{
    char timetxt[10];

    switch (message)
    {
        case WM_COMMAND:
            switch (LOWORD(wParam)) 
            {
                case IDOK:
                    GetDlgItemText(hDlg, IDG_REFRNEW, (LPSTR) timetxt, 10);
                    if (lstrlen((LPSTR) timetxt) == 0)
                        break;                    
					
					sscanf(timetxt,"%d", &secTimer);

                    EndDialog(hDlg, 1);
                    return (TRUE);


                case IDCANCEL:
                    EndDialog(hDlg, 1);
                    return (TRUE);
            }
            break;

        case WM_INITDIALOG:                        /* message: initialize    */
            wsprintf((LPSTR) str, "%d", secTimer);
 	        SetDlgItemText(hDlg, IDG_REFRCORR, (LPSTR) str);
       	    SetFocus(GetDlgItem(hDlg, IDG_DESCR));
            return (FALSE); /* Indicates the focus is set to a control */
    }
    return FALSE;
}


/****************************************************************************

    FUNCTION: UpdateGroupSel(HWND);

    PURPOSE: Update the list box of GroupSel

****************************************************************************/

void UpdateGroupSel(hDlg)
HWND hDlg;
{
    HWND hList;
    LONG index;
    int i;

    hList=GetDlgItem(hDlg, IDG_LISTBX);

    for (i=0; i<ngroup; i++)
	    index = SendMessage(hList, LB_ADDSTRING, 0, (LONG) pGroup[i].descr);

    wsprintf((LPSTR) str, "%d", ngroup);
    SetDlgItemText(hDlg, IDG_GROUPNUM, (LPSTR) str);
}


/****************************************************************************

    FUNCTION: VariSel(HWND, unsigned, WORD, LONG)

    PURPOSE: Let user select a file, and return.  Open code not provided.

****************************************************************************/

int CALLBACK VariSel(hDlg, message, wParam, lParam)
HWND hDlg;
unsigned message;
WPARAM wParam;
LPARAM lParam;
{
    HWND hList;
    LONG index;
    char Select[128], Selectlower[128];
    int i, j, kk;
    int tabstops;
    int trovato;

    switch (message)
    {
        case WM_COMMAND:
            switch (LOWORD(wParam)) 
            {
                case IDS_SELECT:
                    hList=GetDlgItem(hDlg, IDS_LISTBX2);
					index = SendMessage(hList, LB_GETCURSEL, 0, 0); 
	                if (index == -1)
		                return(TRUE);

                    lstrcpy((LPSTR) Select, "\0");
                    DlgDirSelectEx(hDlg, (LPSTR) Select, 127, IDS_LISTBX2);
	                if (nselect0 != MAXSELECT)
	                {
	                    nselect0++;

	                    for (kk=0; kk<ncurve; kk++)
	                        if (lstrncmp((LPSTR) Select, curva[kk], 8) == 0)
	                        {
	                            iselect[nselect0-1] = kk;
                                    break;
	                        }

	                    lstrcpy((LPSTR) SELECT[nselect0-1], curva[iselect[nselect0-1]]);
                        hList=GetDlgItem(hDlg, IDS_LISTBX1);
 	                    index = SendMessage(hList, LB_ADDSTRING, 0, 
	                                 (LONG) (LPSTR) SELECT[nselect0-1]);

	 	      	        wsprintf((LPSTR) str, "%d", nselect0);
 	                    SetDlgItemText(hDlg, IDS_NUMBER, (LPSTR) str);
                    }

                    return (TRUE);


                case IDS_DELETE:
                    hList=GetDlgItem(hDlg, IDS_LISTBX1);
					index = SendMessage(hList, LB_GETCURSEL, 0, 0); 
	                if (index == -1)
		                return(TRUE);

                    lstrcpy((LPSTR) Select, "\0");
                    DlgDirSelectEx(hDlg, (LPSTR) Select, 127, IDS_LISTBX1);
                     
					kk = lstrlen((LPSTR) Select);
                    if (Select[kk-1] == '.')
	                    Select[kk-1] = '\0';
                                   
	                for (kk=0; kk<nselect0; kk++)
	                    if (lstrncmp((LPSTR) Select, (LPSTR) SELECT[kk], 8) == 0)
	                        break;

 	                SendMessage(hList, LB_RESETCONTENT, 0, 0);

	                for (i=0, j=0; i<nselect0; i++) 
	                    if (i != kk)
                        {
                            lstrcpy((LPSTR) SELECT[j], (LPSTR) SELECT[i]);
                            iselect[j] = iselect[i];

 	                        index = SendMessage(hList, LB_ADDSTRING,
	                                0, (LONG) (LPSTR) SELECT[j]);

		                    j++;
			            }

	                nselect0--;
		            wsprintf((LPSTR) str, "%d", nselect0);
 	                SetDlgItemText(hDlg, IDS_NUMBER, (LPSTR) str);
                    return (TRUE);


                case IDS_LISTBX1:
                    switch (HIWORD(wParam)) 
                    {
                        case LBN_DBLCLK:

                            DlgDirSelectEx(hDlg, (LPSTR) Select, 127, IDS_LISTBX1);

	                        kk = lstrlen((LPSTR) Select);
                            if (Select[kk-1] == '.')
	                            Select[kk-1] = '\0';
                                   
	                        for (kk=0; kk<nselect0; kk++)
	                            if (lstrncmp((LPSTR) Select, (LPSTR) SELECT[kk], 8) == 0)
	                                break;

                            hList=GetDlgItem(hDlg, IDS_LISTBX1);

 	                        SendMessage(hList, LB_RESETCONTENT, 0, 0);

	                        for (i=0, j=0; i<nselect0; i++) 
	                            if (i != kk)
                                {
                                    lstrcpy((LPSTR) SELECT[j], (LPSTR) SELECT[i]);
                                    iselect[j] = iselect[i];

 	                                index = SendMessage(hList, LB_ADDSTRING,
	                                        0, (LONG) (LPSTR) SELECT[j]);

				                    j++;
			                    }

	                        nselect0--;
		   	                wsprintf((LPSTR) str, "%d", nselect0);
 	                        SetDlgItemText(hDlg, IDS_NUMBER, (LPSTR) str);

                    }

                    return (TRUE);

                case IDS_LISTBX2:
                    switch (HIWORD(wParam)) 
                    {
                        case LBN_DBLCLK:
                            DlgDirSelectEx(hDlg, (LPSTR) Select, 127, IDS_LISTBX2);
	                        if (nselect0 != MAXSELECT )
	                        {
	                            nselect0++;

	                            kk = lstrlen((LPSTR) Select);
                                if (Select[kk-1] == '.')
	                                Select[kk-1] = '\0';
                                   
	                            for (kk=0; kk<ncurve; kk++)
	                                if (lstrncmp((LPSTR) Select, curva[kk], 8) == 0)
	                                {
	                                    iselect[nselect0-1] = kk;
                                        break;
	                                }

	                            lstrcpy((LPSTR) SELECT[nselect0-1], 
                                        curva[iselect[nselect0-1]]);

                                hList=GetDlgItem(hDlg, IDS_LISTBX1);

 	                            index = SendMessage(hList, LB_ADDSTRING, 0, 
	                                    (LONG) (LPSTR) SELECT[nselect0-1]);

	 	    	                wsprintf((LPSTR) str, "%d", nselect0);
 	                            SetDlgItemText(hDlg, IDS_NUMBER, (LPSTR) str);
	                        }

	                        break;
                    }

                    return (TRUE);


                case IDS_CLEAR:
                    hList=GetDlgItem(hDlg, IDS_LISTBX1);
 	                SendMessage(hList, LB_RESETCONTENT, 0, 0);
		            nselect0 = 0;

		            wsprintf((LPSTR) str, "%d", nselect0);
 	                SetDlgItemText(hDlg, IDS_NUMBER, (LPSTR) str);
                    return (TRUE);


                case IDS_FIND:
                    GetDlgItemText(hDlg, IDS_EDITFND, (LPSTR) Select, 128);
                    hList=GetDlgItem(hDlg, IDS_LISTBX2);

                    if (lstrlen((LPSTR) Select) != 0) 
                    {
                        if (lstrcmp((LPSTR) Select, (LPSTR) PSelect) != 0)
                        {
	                        ifind = 0;
	                        lstrcpy((LPSTR) PSelect, (LPSTR) Select);
	                    }    

	                    trovato = 0;
						conv_minuscolo(Select,Selectlower);
		                for(i=ifind; i<ncurve; i++) 
                        {
// GUAG feb 2004                          lstrcpy((LPSTR) str, curva[i]);
							conv_minuscolo(curva[i], str);
			               if (strstr(str, Selectlower) != NULL) 
                           {
                               ifind = i+1;
                               trovato = 1;
    	                       index = SendMessage(hList, LB_SELECTSTRING,
                                       i-1, (LONG) curva[i]);
			                   break;	
		                   }
		                }
		       
	                    if (trovato == 0)
		                    for(i=0; i<ifind; i++) 
                            {
// GUAG feb 2004                            lstrcpy((LPSTR) str, (LPSTR)curva[i]);
								conv_minuscolo(curva[i], str);
	 		                   if (strstr(str, Selectlower) != 
                                                                         NULL) 
                               {
	                               ifind = i+1;
                                   trovato = 1;
    	                           index = SendMessage(hList, LB_SELECTSTRING,
                                           i-1, (LONG) curva[i]);
			                       break;	
			                   }	
		                    }

	                    if (trovato == 0)
                            MessageBox(hDlg, "String not found", PrgName, 
                                       MB_OK | MB_ICONEXCLAMATION);

	                }

                    return (TRUE);


                case IDOK:
                    EndDialog(hDlg, 1);
					nselect = nselect0;
                    return (TRUE);


                case IDCANCEL:
                    EndDialog(hDlg, 0);
					nselect = nselect0;
                    return (TRUE);
            }
            break;

        case WM_INITDIALOG:                        /* message: initialize    */
            nselect0 = nselect;
			tabstops = 12;
            hList=GetDlgItem(hDlg, IDS_LISTBX2);
  	    	SendMessage(hList, LB_SETTABSTOPS, 1, (long) (LPINT) &tabstops);
            UpdateVariSel(hDlg);
            SetWindowText(hDlg, titolo);
       	    SetFocus(GetDlgItem(hDlg, IDS_LISTBX2));
            return (FALSE); /* Indicates the focus is set to a control */
    }
    return FALSE;
}


/****************************************************************************

    FUNCTION: UpdateVariSel(HWND);

    PURPOSE: Update the list box of VariSel

****************************************************************************/

void UpdateVariSel(hDlg)
HWND hDlg;
{
    HWND hList;
    LONG index;
    int i;

    hList=GetDlgItem(hDlg, IDS_LISTBX2);

    for (i=0; i<ncurve; i++)
	    index = SendMessage(hList, LB_ADDSTRING, 0, (LONG) curva[i]);

    hList=GetDlgItem(hDlg, IDS_LISTBX1);

    for (i=0; i<nselect0; i++)
	    index = SendMessage(hList, LB_ADDSTRING, 0, 
	                       (LONG) (LPSTR) SELECT[i]);

    wsprintf((LPSTR) str, "%d", nselect0);
    SetDlgItemText(hDlg, IDS_NUMBER, (LPSTR) str);
}


/****************************************************************************

    FUNCTION: About(HWND, unsigned, WORD, LONG)

    PURPOSE:  Processes messages for "About" dialog box

    MESSAGES:

        WM_INITDIALOG - initialize dialog box
        WM_COMMAND    - Input received

****************************************************************************/

BOOL CALLBACK About(hDlg, message, wParam, lParam)
HWND hDlg;
unsigned message;
WPARAM wParam;
LPARAM lParam;
{
    switch (message) 
    {
        case WM_INITDIALOG:
            return (TRUE);

        case WM_COMMAND:
	        if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL) 
            {
                EndDialog(hDlg, TRUE);
                return (TRUE);
            }
            break;
    }
    return (FALSE);
}


int lstrncmp(st1, st2, len)
LPSTR st1, st2;
int len;
{
     int i;

     for (i=0; i<len; i++)
         if (st1[i] != st2[i])
             return (1);

     return (0);
}

  
HANDLE OpenGRFdlg()
{
    OPENFILENAME    ofn;
    char            szFile[256], szFileTitle[256];
    static char     *szFilter;
    HANDLE          hTfile;

    szFilter = "F22 files (*.f22)\0*.f22\0\0";
    strcpy(szFile, "*.f22\0");

    ofn.lStructSize = sizeof(OPENFILENAME);
    ofn.hwndOwner = GetFocus();
    ofn.lpstrFilter = szFilter;
    ofn.lpstrCustomFilter = (LPSTR) NULL;
    ofn.nMaxCustFilter = 0L;
    ofn.nFilterIndex = 1;
    ofn.lpstrFile = szFile;
    ofn.nMaxFile = sizeof(szFile);
    ofn.lpstrFileTitle = szFileTitle;
    ofn.nMaxFileTitle = sizeof(szFileTitle);
    ofn.lpstrInitialDir = (LPSTR) NULL;
    ofn.lpstrTitle = (LPSTR) NULL;
    ofn.Flags = 0L;
    ofn.nFileOffset = 0;
    ofn.nFileExtension = 0;
    ofn.lpstrDefExt = "F22";

    if (!GetOpenFileName(&ofn)) 
        return(INVALID_HANDLE_VALUE);

	hTfile = CreateFile(szFile, GENERIC_READ, 
		                FILE_SHARE_READ | FILE_SHARE_WRITE,
					   	(LPSECURITY_ATTRIBUTES) NULL, 
						OPEN_EXISTING,
						FILE_ATTRIBUTE_NORMAL, (HANDLE) NULL); 	 
	
	if (hTfile == INVALID_HANDLE_VALUE)
    {
        sprintf(str,"Error opening file %s", FileName);
        MessageBox(GetFocus(), (LPSTR) str, NULL, MB_OK | MB_ICONHAND);
        return(hTfile);
    }

	else
		strcpy(FileName, szFile);

 /* open group variables file */
    lstrcpy((LPSTR) OpenGName, (LPSTR) FileName);
    AddGExt(OpenGName, DefGExt);
	  
	hGfile = CreateFile(OpenGName, GENERIC_READ | GENERIC_WRITE, 
					   	FILE_SHARE_READ | FILE_SHARE_WRITE, (LPSECURITY_ATTRIBUTES) NULL, OPEN_EXISTING,
						FILE_ATTRIBUTE_NORMAL, (HANDLE) NULL); 
    if (hGfile == INVALID_HANDLE_VALUE)
	{
		hGfile = CreateFile(OpenGName, GENERIC_READ | GENERIC_WRITE, 
					   	    FILE_SHARE_READ | FILE_SHARE_WRITE, (LPSECURITY_ATTRIBUTES) NULL, CREATE_ALWAYS,
						    FILE_ATTRIBUTE_NORMAL, (HANDLE) NULL); 
        if (hGfile == INVALID_HANDLE_VALUE)
		{
            wsprintf((LPSTR) str, "Error creating %s", (LPSTR) OpenGName);
            MessageBox(GetFocus(), (LPSTR) str, PrgName, MB_OK | MB_ICONEXCLAMATION);
	    }
    }

	return(hTfile);
}

/****************************************************************************

    FUNCTION: AddGExt(PSTR, PSTR);

    PURPOSE: Add default extension

/***************************************************************************/

void AddGExt(Name, Ext)
PSTR Name, Ext;
{
    PSTR pTptr;
    int i;

    pTptr = Name;

    i = 0;
    while (*pTptr && *pTptr != '.')
    {	
	    i++;
        pTptr++;
    }

    if (*pTptr != '.')
        lstrcat((LPSTR) Name, (LPSTR) Ext);

    else
    {
        Name[i] = '\0';
        lstrcat((LPSTR) Name, (LPSTR) Ext);
    }            
}

void conv_minuscolo( char *msg, char *buff)
{
    char *p;
	strcpy(buff, msg);
	for( p = buff; p < buff + strlen( buff ); p++,buff++)
   {
      if( isupper( *p ) )
         *buff=tolower( *p );
      else
         *buff=*p;
   }

}
