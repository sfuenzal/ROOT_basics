#include "TCanvas.h"
#include "TROOT.h"
#include "TGraphErrors.h"
#include "TF1.h"
#include "TH1F.h"   
#include "TLegend.h"
#include "TFile.h"  
#include "TArrow.h"
#include "TLatex.h"
#include "TMath.h"
#include "TMultiGraph.h"

#include <iostream>
#include <math.h>
#include <vector> 
#include <stdlib.h>
#include <string>

using namespace std;

class ROOTFile
{        
    protected:
        TChain *fChain = new TChain("mini");
    public:
        ROOTFile () {};

        void InputROOTFile(string path_direction, string file_name)
        {
            TString path = "/home/nicole/Desktop/Doctorado/Tercer Semestre/Tópicos Especiales de Física de Campos y Partículas I/Training/DataSet/";
            TString file = "mc_363492.llvv.2lep.root";
            fChain -> AddFile(path + file);
        }

        void ShowROOTFile(UInt_t number_of_entries)
        {
            for (UInt_t i = 0; i < number_of_entries; ++i)
            {
                fChain -> Show(i);
            }
        }

        virtual ~ ROOTFile () {};
};

class Histograms: public ROOTFile
{
    protected:
        Bool_t trigE = 0;
        Bool_t trigM = 0;
        UInt_t lep_n = 2;
        Float_t met_phi = 0;
        Float_t met_et = 0;
        
        vector<bool> *lep_isTightID = 0; 
        vector<int> *lep_charge = 0;
        vector<unsigned int> *lep_type = 0;
        vector<float> *lep_pt = 0;  
        vector<float> *lep_eta = 0;  
        vector<float> *lep_phi = 0;  
        vector<float> *lep_E   = 0;
    public:
        Histograms () {};

        void SetBranch()
        {
            fChain -> SetBranchAddress("trigE", &trigE);
            fChain -> SetBranchAddress("trigM", &trigM);
            fChain -> SetBranchAddress("lep_n", &lep_n);
            fChain -> SetBranchAddress("met_phi", &met_phi);
            fChain -> SetBranchAddress("met_et", &met_et);
        
            fChain -> SetBranchAddress("lep_isTightID", &lep_isTightID);
            fChain -> SetBranchAddress("lep_charge", &lep_charge);
            fChain -> SetBranchAddress("lep_type", &lep_type);
            fChain -> SetBranchAddress("lep_pt", &lep_pt);
            fChain -> SetBranchAddress("lep_eta", &lep_eta);
            fChain -> SetBranchAddress("lep_phi", &lep_phi);
            fChain -> SetBranchAddress("lep_E", &lep_E);
        }

        void ShowSomeBranches(UInt_t number_of_entries)
        {
            Int_t nentries = (Int_t) fChain -> GetEntries();
            
            cout << "Number of entries to analyse: " << nentries << endl;

            for (UInt_t i = 0; i < number_of_entries; ++i)
            {
                fChain -> GetEntry(i);
                for (UInt_t j = 0; j < lep_pt -> size(); ++j)
                {
                    cout << "lep_pt = " << lep_pt -> at(j) << endl;
                }
            }

            for (UInt_t i = 0; i < number_of_entries; ++i)
            {
                fChain -> GetEntry(i);
                for (UInt_t j = 0; j < lep_eta -> size(); ++j)
                {
                    cout << "lep_eta = " << lep_eta -> at(j) << endl;
                }
            }

            for (UInt_t i = 0; i < number_of_entries; ++i)
            {
                fChain -> GetEntry(i);
                for (UInt_t j = 0; j < lep_phi -> size(); ++j)
                {
                    cout << "lep_phi = " << lep_phi -> at(j) << endl;
                }
            }

            for (UInt_t i = 0; i < number_of_entries; ++i)
            {
                fChain -> GetEntry(i);
                for (UInt_t j = 0; j < lep_E -> size(); ++j)
                {
                    cout << "lep_E = " << lep_E -> at(j) << endl;
                }
            }
        }

        void CutAndHistograming(UInt_t number_of_entries)
        {
            TH1F *h_lep_pt_nf = new TH1F ("No filter lep_pt histogram", "No filter lep_pt histogram", 30, 0, 500000);
            h_lep_pt_nf -> SetMarkerSize(2.0);
            h_lep_pt_nf -> SetLineColor(kBlue);
            h_lep_pt_nf -> SetFillColor(kBlue - 10);

            TH1F *h_lep_pt_f = new TH1F ("Filter lep_pt histogram", "Filter lep_pt histogram", 30, 0, 500000);
            h_lep_pt_f -> SetMarkerSize(2.0);
            h_lep_pt_f -> SetLineColor(kBlue);
            h_lep_pt_f -> SetFillColor(kBlue - 10);

          
            for (UInt_t i = 0; i < number_of_entries; ++i)
            {
                fChain -> GetEntry(i);
                for (UInt_t j = 0; j < lep_pt -> size(); ++j)
                {
                    h_lep_pt_nf -> Fill(lep_pt -> at(j));
                }
            }
            
            for (UInt_t i = 0; i < number_of_entries; ++i)
            {
                fChain -> GetEntry(i);
                for (UInt_t j = 0; j < lep_pt -> size(); ++j)
                {
                    if (lep_pt -> at(j) < 190000 && lep_pt -> at(j) > 0)
                    {
                        h_lep_pt_f -> Fill(lep_pt -> at(j));
                    }
                }
            }
            

            TCanvas *cz1 = new TCanvas("cz1", "cz1", 10, 10, 900, 600);
            cz1 -> Divide(2, 1);
            
            cz1 -> cd(1);
            h_lep_pt_nf -> Draw();
            h_lep_pt_nf -> GetXaxis() -> SetTitle("lep_pt");
            h_lep_pt_nf -> GetYaxis() -> SetTitle("Events");
            h_lep_pt_nf -> GetXaxis() -> CenterTitle();
            h_lep_pt_nf -> GetYaxis() -> CenterTitle();
            
            cz1 -> cd(2);
            h_lep_pt_f -> Draw();
            h_lep_pt_f -> GetXaxis() -> SetTitle("lep_pt");
            h_lep_pt_f -> GetYaxis() -> SetTitle("Events");
            h_lep_pt_f -> GetXaxis() -> CenterTitle();
            h_lep_pt_f -> GetYaxis() -> CenterTitle();

        }

        ~ Histograms () {};
};


void TreeMacroOne()
{
    Histograms *obj2 = new Histograms();
    obj2 -> InputROOTFile("/home/nicole/Desktop/Doctorado/Tercer Semestre/Tópicos Especiales de Física de Campos y Partículas I/Training/DataSet/", "mc_363492.llvv.2lep.root");
    obj2 -> ShowROOTFile(1);
    obj2 -> SetBranch();
    obj2 -> ShowSomeBranches(5);
    obj2 -> CutAndHistograming(100000);
}