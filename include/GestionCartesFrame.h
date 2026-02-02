// ============================================
// include/GestionCartesFrame.h - VERSION ULTRA-MODERNE
// ============================================
#ifndef GESTIONCARTESFRAME_H
#define GESTIONCARTESFRAME_H

#include <wx/wx.h>
#include <wx/listctrl.h>
#include <vector>
#include "CarteBancaire.h"

class GestionCartesFrame : public wxFrame {
public:
    GestionCartesFrame(const wxString& title);

private:
    std::vector<CarteBancaire> m_cartes;
    wxListCtrl* listCartes;
    wxStaticText* lblNombreCartes;
    wxStaticText* lblCartesActives;

    void CreerInterface();
    void OnActiver(wxCommandEvent& event);
    void OnDesactiver(wxCommandEvent& event);
    void OnBloquer(wxCommandEvent& event);
    void OnDemanderCarte(wxCommandEvent& event);
    void OnVoirDetails(wxCommandEvent& event);
    void ActualiserCartes();
    void ActualiserStatistiques();

    wxDECLARE_EVENT_TABLE();
};

enum {
    ID_ActiverCarte = wxID_HIGHEST + 400,
    ID_DesactiverCarte,
    ID_BloquerCarte,
    ID_DemanderCarte,
    ID_VoirDetails
};

#endif
