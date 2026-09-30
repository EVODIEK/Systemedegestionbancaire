/***************************************************************
 * Name:      BanqueAppMain.h
 * Purpose:   Defines Application Frame
 * Author:    EVODIE (evodiekpodegbe@gmail.com)
 * Created:   2026-01-09
 * Copyright: EVODIE ()
 * License:
 **************************************************************/

#ifndef BANQUEAPPMAIN_H
#define BANQUEAPPMAIN_H

//(*Headers(BanqueAppFrame)
#include <wx/frame.h>
#include <wx/menu.h>
#include <wx/statusbr.h>
//*)

class BanqueAppFrame: public wxFrame
{
    public:

        BanqueAppFrame(wxWindow* parent,wxWindowID id = -1);
        virtual ~BanqueAppFrame();

    private:

        //(*Handlers(BanqueAppFrame)
        void OnQuit(wxCommandEvent& event);
        void OnAbout(wxCommandEvent& event);
        //*)

        //(*Identifiers(BanqueAppFrame)
        static const long idMenuQuit;
        static const long idMenuAbout;
        static const long ID_STATUSBAR1;
        //*)

        //(*Declarations(BanqueAppFrame)
        wxStatusBar* StatusBar1;
        //*)

        DECLARE_EVENT_TABLE()
};

#endif // BANQUEAPPMAIN_H
