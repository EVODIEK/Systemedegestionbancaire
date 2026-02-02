// include/GestionComptesFrame.h
#ifndef GESTIONCOMPTESFRAME_H
#define GESTIONCOMPTESFRAME_H

#include <wx/wx.h>
#include <wx/listctrl.h>
#include <vector>
#include "CompteBancaire.h"

class GestionComptesFrame : public wxFrame {
public:
    GestionComptesFrame(const wxString& title);

private:
    std::vector<CompteBancaire> m_comptes;
    wxListCtrl* listComptes;

    void CreerInterface();
    void OnDepot(wxCommandEvent& event);
    void OnRetrait(wxCommandEvent& event);
    void OnVirement(wxCommandEvent& event);
    void OnCreerCompte(wxCommandEvent& event);
    void ActualiserComptes();

    wxDECLARE_EVENT_TABLE();
};

enum {
    ID_DepotCompte = wxID_HIGHEST + 600,
    ID_RetraitCompte,
    ID_VirementCompte,
    ID_CreerCompte
};

#endif
