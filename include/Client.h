// ========== include/Client.h ==========
#ifndef CLIENT_H
#define CLIENT_H

#include <wx/string.h>

class Client {
public:
    wxString idClient;
    wxString nom;
    wxString prenom;
    wxString email;

    Client()
        : idClient(wxT("001")),
          nom(wxT("Evodie")),
          prenom(wxT("Kpodégbé")),
          email(wxT("evodie@bank.com")) {}

    Client(const wxString& id, const wxString& n, const wxString& p, const wxString& e = wxT(""))
        : idClient(id), nom(n), prenom(p), email(e) {}
};

#endif
