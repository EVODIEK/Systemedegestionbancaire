
// ========== include/CarteBancaire.h ==========
#ifndef CARTEBANCAIRE_H
#define CARTEBANCAIRE_H

#include <wx/string.h>

class CarteBancaire {
public:
    wxString numeroCarte;
    wxString type;
    wxString etat;
    wxString numeroCompte;

    CarteBancaire()
        : numeroCarte(wxT("1111-2222-3333-4444")),
          type(wxT("Visa")),
          etat(wxT("Active")),
          numeroCompte(wxT("000123456")) {}

    CarteBancaire(const wxString& num, const wxString& t, const wxString& e, const wxString& compte)
        : numeroCarte(num), type(t), etat(e), numeroCompte(compte) {}
};

#endif
