// ============================================
// include/AdminFrame.h - VERSION ULTRA-MODERNE
// ============================================
#ifndef ADMINFRAME_H
#define ADMINFRAME_H

#include <wx/wx.h>
#include <wx/listctrl.h>
#include <wx/notebook.h>
#include <vector>
#include "Client.h"
#include "CompteBancaire.h"
#include "CarteBancaire.h"
#include "Pret.h"

class AdminFrame : public wxFrame {
public:
    AdminFrame(const wxString& title);

private:
    // Donnees
    std::vector<Client> m_clients;
    std::vector<CompteBancaire> m_comptes;
    std::vector<CarteBancaire> m_cartes;
    std::vector<Pret> m_prets;

    // Widgets
    wxNotebook* notebook;
    wxListCtrl* listClients;
    wxListCtrl* listComptesAdmin;
    wxListCtrl* listCartesAdmin;
    wxListCtrl* listPretsAdmin;

    // Methodes de creation
    void CreerInterface();
    void CreerOngletClients(wxPanel* parent);
    void CreerOngletComptes(wxPanel* parent);
    void CreerOngletCartes(wxPanel* parent);
    void CreerOngletPrets(wxPanel* parent);

    // Methodes d'action
    void OnAjouterClient(wxCommandEvent& event);
    void OnSupprimerClient(wxCommandEvent& event);
    void OnModifierClient(wxCommandEvent& event);

    void OnAjouterCompte(wxCommandEvent& event);
    void OnFermerCompte(wxCommandEvent& event);

    void OnBloquerCarte(wxCommandEvent& event);
    void OnDebloquerCarte(wxCommandEvent& event);
    void OnRenouvelarCarte(wxCommandEvent& event);

    void OnValiderPret(wxCommandEvent& event);
    void OnRefuserPret(wxCommandEvent& event);

    // Methodes d'actualisation
    void ActualiserClients();
    void ActualiserComptes();
    void ActualiserCartes();
    void ActualiserPrets();

    wxDECLARE_EVENT_TABLE();
};

enum {
    ID_AjouterClient = wxID_HIGHEST + 300,
    ID_SupprimerClient,
    ID_ModifierClient,
    ID_AjouterCompte,
    ID_FermerCompte,
    ID_BloquerCarte,
    ID_DebloquerCarte,
    ID_RenouvelerCarte,
    ID_ValiderPret,
    ID_RefuserPret
};

#endif
