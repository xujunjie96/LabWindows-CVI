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
#define  PANEL_GRAPH3D                    2       /* control type: activeX, callback function: (none) */
#define  PANEL_RING_PROJECT               3       /* control type: ring, callback function: projection */
#define  PANEL_RING_LINE                  4       /* control type: ring, callback function: drawline */
#define  PANEL_CMD_GEN                    5       /* control type: command, callback function: generatewave */
#define  PANEL_NUMERICSLIDE               6       /* control type: scale, callback function: trans */
#define  PANEL_QUITBUTTON                 7       /* control type: command, callback function: quitsys */
#define  PANEL_CMD_CLEAR                  8       /* control type: command, callback function: clearwave */


     /* Control Arrays: */

          /* (no control arrays in the resource file) */


     /* Menu Bars, Menus, and Menu Items: */

          /* (no menu bars in the resource file) */


     /* Callback Prototypes: */

int  CVICALLBACK clearwave(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK drawline(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK generatewave(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK projection(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK quitsys(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK trans(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);


#ifdef __cplusplus
    }
#endif
