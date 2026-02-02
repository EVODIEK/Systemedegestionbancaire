// src/App.cpp
#include "App.h"
#include "LoginFrame.h"

wxIMPLEMENT_APP(BanqueApp);

bool BanqueApp::OnInit()
{
    LoginFrame* login = new LoginFrame("EvoBank - Connexion");
    login->Show(true);
    return true;
}
