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

#define  PANEL                            1
#define  PANEL_LISTBOX                    2       /* control type: listBox, callback function: (none) */
#define  PANEL_TREE                       3       /* control type: tree, callback function: (none) */
#define  PANEL_TEXTBOX                    4       /* control type: textBox, callback function: (none) */
#define  PANEL_COMMANDBUTTON_QUIT         5       /* control type: command, callback function: quit */
#define  PANEL_COMMANDBUTTON_DELETE       6       /* control type: command, callback function: delete */
#define  PANEL_COMMANDBUTTON_INSERT       7       /* control type: command, callback function: insert */
#define  PANEL_COMMANDBUTTON_TRANS        8       /* control type: command, callback function: transfer */
#define  PANEL_COMMANDBUTTON_CLEAR        9       /* control type: command, callback function: clear */
#define  PANEL_STRING_DELETE              10      /* control type: string, callback function: (none) */
#define  PANEL_STRING_INSERT              11      /* control type: string, callback function: (none) */


     /* Control Arrays: */

          /* (no control arrays in the resource file) */


     /* Menu Bars, Menus, and Menu Items: */

          /* (no menu bars in the resource file) */


     /* Callback Prototypes: */

int  CVICALLBACK clear(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK delete(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK insert(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK quit(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK transfer(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);


#ifdef __cplusplus
    }
#endif
