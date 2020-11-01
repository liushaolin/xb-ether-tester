/* 
 * �����Ϊ��ѡ���Դ�����
 * ������İ�Ȩ(����Դ�뼰�����Ʒ����汾)��һ�й������С�
 * ����������ʹ�á������������
 * ��Ҳ�������κ���ʽ���κ�Ŀ��ʹ�ñ����(����Դ�뼰�����Ʒ����汾)���������κΰ�Ȩ���ơ�
 * =====================
 * ����: ������
 * ����: sunmingbao@126.com
 */
#include <windows.h>
#include "common.h"
#include "global_info.h"
#include "res.h"
#include "gui.h"

HWND    hwnd_toolbar;
int     toolbar_height;
HWND    hwnd_net_card_comb;
HWND    hwnd_net_card_text;
HWND    hwnd_capture_checkbox;
HWND    hwnd_statusbar;
int     statusbar_height;

TBBUTTON at_button[] =                
    {
        {0, IDT_TOOLBAR_STOP, TBSTATE_ENABLED, TBSTYLE_AUTOSIZE , {0}, 0, (INT_PTR)"stop TX"},
        {1, IDT_TOOLBAR_START, TBSTATE_ENABLED, TBSTYLE_AUTOSIZE , {0}, 0, (INT_PTR)"start TX"},
        {I_IMAGENONE , -1, TBSTATE_ENABLED, TBSTYLE_SEP|TBSTYLE_AUTOSIZE},
        {2, IDT_TOOLBAR_CAP_WHILE_SND, TBSTATE_ENABLED, TBSTYLE_AUTOSIZE , {0}, 0, (INT_PTR)"capture packets while TX" },
        {3, IDT_TOOLBAR_VIEW_CAPTURE, TBSTATE_ENABLED, TBSTYLE_AUTOSIZE , {0}, 0, (INT_PTR)"view packets captured" },

        {I_IMAGENONE , -1, TBSTATE_ENABLED, TBSTYLE_SEP|TBSTYLE_AUTOSIZE},
        {4, IDT_TOOLBAR_CAPTURE, TBSTATE_ENABLED, TBSTYLE_AUTOSIZE , {0}, 0, (INT_PTR)"separately capture packets" },
        {I_IMAGENONE , -1, TBSTATE_ENABLED, TBSTYLE_SEP|TBSTYLE_AUTOSIZE},
        {I_IMAGENONE , -1, TBSTATE_ENABLED, TBSTYLE_SEP|TBSTYLE_AUTOSIZE},
        {I_IMAGENONE , -1, TBSTATE_ENABLED, TBSTYLE_SEP|TBSTYLE_AUTOSIZE},
        {I_IMAGENONE , -1, TBSTATE_ENABLED, TBSTYLE_SEP|TBSTYLE_AUTOSIZE},
        {I_IMAGENONE , -1, TBSTATE_ENABLED, TBSTYLE_SEP|TBSTYLE_AUTOSIZE},
    };

HBITMAP hbmpToolbar[3];
HIMAGELIST g_hImageList;

WNDPROC old_tb_proc;
LRESULT CALLBACK my_tb_proc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
 	int cxClient, cyClient;
    RECT  rc;
    int button_width, button_height;
 	switch (message)
 	{
     	case WM_SIZE :
            cxClient = LOWORD (lParam) ;
      		cyClient = HIWORD (lParam) ;

    SendMessage(hwnd_toolbar,TB_GETITEMRECT,(WPARAM)ARRAY_SIZE(at_button)-1,(LPARAM)&rc);
    button_width = rc.right-rc.left;
    button_height = rc.bottom-rc.top;

    MoveWindow	(hwnd_net_card_text
        ,cxClient - cxChar_2*40, rc.top, cxChar_2*10, button_height, TRUE) ;

    MoveWindow	(hwnd_net_card_comb, cxClient - cxChar_2*30, rc.top, cxChar_2*30, 250, TRUE) ;


        case 	WM_COMMAND:
            if (HIWORD(wParam)==CBN_SELCHANGE)
            {
                select_if(SendMessage(hwnd_net_card_comb, (UINT) CB_GETCURSEL, 
                (WPARAM) 0, (LPARAM) 0));
               	break ;
            }
            break;
 	}

    return CallWindowProc (old_tb_proc, hwnd, message, wParam,lParam) ;
}

int CreateToolbar()
{
    HIMAGELIST h0, h1;
    HICON hiconItem; 
    RECT rc; 

    hwnd_toolbar = CreateWindowEx(0, TOOLBARCLASSNAME, NULL, 
                    WS_CHILD | WS_VISIBLE | WS_BORDER |  TBSTYLE_TOOLTIPS | TBSTYLE_LIST  
                    , 0, 0, 0, 0, hwnd_frame, (HMENU)NULL, g_hInstance, NULL);
    SendMessage(hwnd_toolbar, TB_SETEXTENDEDSTYLE, 0,  TBSTYLE_EX_MIXEDBUTTONS );

    if(hwnd_toolbar == NULL)
    {
        MessageBox (NULL, TEXT ("CreateToolbar failed!"), szAppName, MB_ICONERROR);
          
        return FAIL;
     }


    h0 = ImageList_Create(32,32,ILC_MASK|ILC_COLORDDB,4,0);
    hiconItem = LoadIcon(g_hInstance, TEXT("icon_stop"));
    ImageList_AddIcon(h0, hiconItem);
    DestroyIcon(hiconItem);
    hiconItem = LoadIcon(g_hInstance, TEXT("icon_start"));
    ImageList_AddIcon(h0, hiconItem);
    DestroyIcon(hiconItem);
    

    hiconItem = LoadIcon(g_hInstance, TEXT("icon_capture_snd"));
    ImageList_AddIcon(h0, hiconItem);
    DestroyIcon(hiconItem);

    hiconItem = LoadIcon(g_hInstance, TEXT("icon_view_capture"));
    ImageList_AddIcon(h0, hiconItem);
    DestroyIcon(hiconItem);

    hiconItem = LoadIcon(g_hInstance, TEXT("icon_capture"));
    ImageList_AddIcon(h0, hiconItem);
    DestroyIcon(hiconItem);

    SendMessage(hwnd_toolbar,TB_SETIMAGELIST,0,(LPARAM)h0);

    h1 = ImageList_Create(32,32,ILC_COLORDDB,4,0);

    hiconItem = LoadIcon(g_hInstance, TEXT("icon_stop"));
    ImageList_AddIcon(h1, hiconItem);
    DestroyIcon(hiconItem);
    hiconItem = LoadIcon(g_hInstance, TEXT("icon_start"));
    ImageList_AddIcon(h1, hiconItem);
    DestroyIcon(hiconItem);
    

    hiconItem = LoadIcon(g_hInstance, TEXT("icon_capture_snd_dis"));
    ImageList_AddIcon(h1, hiconItem);
    DestroyIcon(hiconItem);

    hiconItem = LoadIcon(g_hInstance, TEXT("icon_view_capture_dis"));
    ImageList_AddIcon(h1, hiconItem);
    DestroyIcon(hiconItem);

    hiconItem = LoadIcon(g_hInstance, TEXT("icon_capture_dis"));
    ImageList_AddIcon(h1, hiconItem);
    DestroyIcon(hiconItem);

    SendMessage(hwnd_toolbar,TB_SETDISABLEDIMAGELIST,0,(LPARAM)h1);


    //����ť�빤��������
    SendMessage(hwnd_toolbar, TB_BUTTONSTRUCTSIZE, (WPARAM)sizeof(TBBUTTON), 0);
    SendMessage(hwnd_toolbar, TB_ADDBUTTONS, ARRAY_SIZE(at_button), (LPARAM)at_button);
    SendMessage(hwnd_toolbar, TB_SETMAXTEXTROWS, 0, 0);
    // Resize the toolbar, and then show it.
    SendMessage(hwnd_toolbar, TB_AUTOSIZE, 0, 0); 
    ShowWindow(hwnd_toolbar,  TRUE);
    toolbar_height = win_height(hwnd_toolbar);

    SendMessage(hwnd_toolbar,TB_GETITEMRECT,(WPARAM)8,(LPARAM)&rc); 
    hwnd_net_card_text=CreateWindowEx(0, TEXT("static"), TEXT("NIC")
        , WS_CHILD | WS_VISIBLE | SS_CENTER | SS_CENTERIMAGE
        , rc.left, rc.top, 2*(rc.right-rc.left), rc.bottom-rc.top,
            hwnd_toolbar, (HMENU)NULL, g_hInstance, NULL);

    hwnd_net_card_comb = CreateWindowEx(WS_EX_LEFT, TEXT("COMBOBOX"), NULL
        , WS_CHILD | WS_VISIBLE | CBS_DROPDOWNLIST|CBS_DISABLENOSCROLL|WS_VSCROLL
        , rc.left+2*(rc.right-rc.left)+8, rc.top, (rc.right-rc.left)*6, 250,
            hwnd_toolbar, (HMENU)NULL, g_hInstance, NULL);
    SendMessage(hwnd_net_card_text, WM_SETFONT, (WPARAM)char_font_2, 0);
    SendMessage(hwnd_net_card_comb, WM_SETFONT, (WPARAM)char_font_2, 0);

    rx_tx_init();
    init_net_card_combbox(hwnd_net_card_comb);

    old_tb_proc = (WNDPROC) SetWindowLong (hwnd_toolbar, 
                                 	GWLP_WNDPROC, (LONG) my_tb_proc) ;

    return SUCCESS;
}

void update_statusbar()
{
    TCHAR info[32];
    _stprintf (	info, TEXT("flows : %d/%d"), GetSelCnt(hwnd_lv), nr_cur_stream) ;
    SendMessage(hwnd_statusbar, SB_SETTEXT,1, (LPARAM)info); 

    if (gt_fc_cfg.speed_type==SPEED_TYPE_FASTEST)
        _stprintf (	info, TEXT("TX rate : Max Speed")) ;
    else if (gt_fc_cfg.speed_type==SPEED_TYPE_HIGH)
    _stprintf (	info, TEXT("TX rate : %d times/S"), gt_fc_cfg.speed_value) ;
    else
        _stprintf (	info, TEXT("TX rate : 1 time/%d us"), gt_fc_cfg.speed_value) ;
    SendMessage(hwnd_statusbar, SB_SETTEXT,2, (LPARAM)info);

    if (!need_capture)
        _stprintf(info, TEXT("capture while TX: %s"),TEXT("disabled")) ;
    else
        _stprintf(info, TEXT("capture while TX: enabled(captue mode:%s)"), 
    gt_pkt_cap_cfg.need_save_capture?TEXT("save packets"):TEXT("statistic only")) ;
    SendMessage(hwnd_statusbar, SB_SETTEXT,3, (LPARAM)info);

}

int CreateStatusBar()
{
    int d[] = {150*WIDTH_COEFFICIENT
        , 300*WIDTH_COEFFICIENT
        , 650*WIDTH_COEFFICIENT
        ,-1};
    hwnd_statusbar = CreateWindow(STATUSCLASSNAME, NULL,
        SBARS_SIZEGRIP | WS_CHILD | WS_VISIBLE|WS_BORDER,0,0,0,0, hwnd_frame, NULL, g_hInstance, NULL);
    ShowWindow(hwnd_statusbar,  TRUE);
    statusbar_height = win_height(hwnd_statusbar);
    SendMessage(hwnd_statusbar, SB_SETPARTS, (WPARAM)ARRAY_SIZE(d), (LPARAM)d);
    update_statusbar();
    return 0;
}


