// include/DashboardClientFrame.h - VERSION COMPLETE
#ifndef DASHBOARDCLIENTFRAME_H
#define DASHBOARDCLIENTFRAME_H

#include <wx/wx.h>
#include <wx/listctrl.h>
#include <vector>
#include "CompteBancaire.h"
#include "CarteBancaire.h"
#include "Pret.h"

class DashboardClientFrame : public wxFrame {
public:
    DashboardClientFrame(const wxString& title);

private:
    // Donnees
    std::vector<CompteBancaire> m_comptes;
    std::vector<CarteBancaire> m_cartes;
    std::vector<Pret> m_prets;

    // Widgets - Listes
    wxListCtrl* listComptes;
    wxListCtrl* listCartes;
    wxListCtrl* listPrets;

    // Widgets - Boutons
    wxButton* btnDepot;
    wxButton* btnRetrait;
    wxButton* btnVirement;
    wxButton* btnGererCartes;
    wxButton* btnGererPrets;

    // Methodes
    void CreerInterface();
    void ActualiserComptes();

    void OnDepot(wxCommandEvent& event);
    void OnRetrait(wxCommandEvent& event);
    void OnVirement(wxCommandEvent& event);
    void OnGererCartes(wxCommandEvent& event);
    void OnGererPrets(wxCommandEvent& event);

    wxDECLARE_EVENT_TABLE();
};

enum {
    ID_Depot = wxID_HIGHEST + 200,
    ID_Retrait,
    ID_Virement,
    ID_GererCartes,
    ID_GererPrets
};

#endif
