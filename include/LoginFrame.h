#ifndef LOGINFRAME_H
#define LOGINFRAME_H

#include <wx/wx.h>

class LoginFrame : public wxFrame {
public:
    LoginFrame(const wxString& title);

private:
    wxTextCtrl* txtUser;
    wxTextCtrl* txtPassword;
    wxChoice* choiceRole;
    wxButton* btnLogin;

    void OnLogin(wxCommandEvent& event);
    wxDECLARE_EVENT_TABLE();
};

enum {
    ID_Login = wxID_HIGHEST + 100
};

#endif
