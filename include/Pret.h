// ========== include/Pret.h ==========
#ifndef PRET_H
#define PRET_H

#include <wx/string.h>

class Pret {
public:
    wxString idPret;
    float montantInitial;
    float montantRestant;
    wxString etat;
    wxString idClient;

    Pret()
        : idPret(wxT("P001")),
          montantInitial(5000.0f),
          montantRestant(3500.0f),
          etat(wxT("Actif")),
          idClient(wxT("001")) {}

    Pret(const wxString& id, float initial, float restant, const wxString& e = wxT("Actif"), const wxString& client = wxT("001"))
        : idPret(id), montantInitial(initial), montantRestant(restant), etat(e), idClient(client) {}
};

#endif
