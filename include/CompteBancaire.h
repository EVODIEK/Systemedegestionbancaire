// ========== include/CompteBancaire.h ==========
#ifndef COMPTEBANCAIRE_H
#define COMPTEBANCAIRE_H

#include <wx/string.h>
#include <string>

class CompteBancaire {
public:
    wxString numeroCompte;
    wxString typeCompte;
    float solde;
    wxString idClient;

    CompteBancaire()
        : numeroCompte(wxT("000123456")),
          typeCompte(wxT("Courant")),
          solde(1000.0f),
          idClient(wxT("001")) {}

    CompteBancaire(const wxString& num, const wxString& type, float s, const wxString& client = wxT("001"))
        : numeroCompte(num), typeCompte(type), solde(s), idClient(client) {}

    void deposer(float montant) { solde += montant; }
    void retirer(float montant) { if(solde >= montant) solde -= montant; }
};

#endif
