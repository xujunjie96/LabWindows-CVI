/**************************************************************************/
/* LabWindows/CVI User Interface Resource (UIR) Include File              */
/*                                                                        */
/* WARNING: Do not add to, delete from, or otherwise modify the contents  */
/*          of this include file.                                         */
/**************************************************************************/

#include <userint.h>

#ifdef __cplusplus
    extern "C" {
#endif

     /* Panels and Controls: */

#define  PANEL                            1       /* callback function: panelcb */


     /* Control Arrays: */

          /* (no control arrays in the resource file) */


     /* Menu Bars, Menus, and Menu Items: */

#define  MENUBAR                          1
#define  MENUBAR_EDIT                     2
#define  MENUBAR_EDIT_EDITCOPY            3       /* callback function: editcopy */
#define  MENUBAR_EDIT_SEPARATOR           4
#define  MENUBAR_EDIT_EDITALWAYSTOP       5       /* callback function: editalwaystop */
#define  MENUBAR_EDIT_SEPARATOR_2         6
#define  MENUBAR_EDIT_EDITEXIT            7       /* callback function: editexit */
#define  MENUBAR_HELP                     8
#define  MENUBAR_HELP_HELPABOUT           9       /* callback function: helpabout */


     /* Callback Prototypes: */

void CVICALLBACK editalwaystop(int menubar, int menuItem, void *callbackData, int panel);
void CVICALLBACK editcopy(int menubar, int menuItem, void *callbackData, int panel);
void CVICALLBACK editexit(int menubar, int menuItem, void *callbackData, int panel);
void CVICALLBACK helpabout(int menubar, int menuItem, void *callbackData, int panel);
int  CVICALLBACK panelcb(int panel, int event, void *callbackData, int eventData1, int eventData2);


#ifdef __cplusplus
    }
#endif
