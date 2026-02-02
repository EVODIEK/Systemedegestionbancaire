/***************************************************************
 * Name:      BanqueAppApp.cpp
 * Purpose:   Code for Application Class
 * Author:    EVODIE (evodiekpodegbe@gmail.com)
 * Created:   2026-01-09
 * Copyright: EVODIE ()
 * License:
 **************************************************************/

#include "BanqueAppApp.h"

//(*AppHeaders
#include "BanqueAppMain.h"
#include <wx/image.h>
//*)

IMPLEMENT_APP(BanqueAppApp);

bool BanqueAppApp::OnInit()
{
    //(*AppInitialize
    bool wxsOK = true;
    wxInitAllImageHandlers();
    if ( wxsOK )
    {
    	BanqueAppFrame* Frame = new BanqueAppFrame(0);
    	Frame->Show();
    	SetTopWindow(Frame);
    }
    //*)
    return wxsOK;

}
