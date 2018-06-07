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
#define  PANEL_COMMANDBUTTON              2       /* control type: command, callback function: quitsys */
#define  PANEL_CMD_DIRPOP                 3       /* control type: command, callback function: dirpopup */
#define  PANEL_CMD_YGRAPHPOPUP            4       /* control type: command, callback function: ygraphpopup */
#define  PANEL_CMD_FILESELECTPOPUP        5       /* control type: command, callback function: fileselectpopup */
#define  PANEL_CMD_GENERARICPOPUP         6       /* control type: command, callback function: genericpopup */
#define  PANEL_CMD_CONIRMPOP              7       /* control type: command, callback function: confirmpop */
#define  PANEL_CMD_FONT                   8       /* control type: command, callback function: font */
#define  PANEL_CMD_PROMPTPOPUP            9       /* control type: command, callback function: promptpopup */
#define  PANEL_CMD_MESSAGEPOP             10      /* control type: command, callback function: messagepop */
#define  PANEL_TEXTBOX                    11      /* control type: textBox, callback function: (none) */


     /* Control Arrays: */

          /* (no control arrays in the resource file) */


     /* Menu Bars, Menus, and Menu Items: */

          /* (no menu bars in the resource file) */


     /* Callback Prototypes: */

int  CVICALLBACK confirmpop(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK dirpopup(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK fileselectpopup(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK font(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK genericpopup(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK messagepop(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK promptpopup(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK quitsys(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK ygraphpopup(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);


#ifdef __cplusplus
    }
#endif
