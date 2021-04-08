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
            TString path = path_direction;
            TString file = file_name;
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
        vector<float> *lep_pt = 0;
        vector<float> *lep_eta = 0;
    public:
        Histograms () {};

        void SetBrach()
        {
            fChain -> SetBranchAddress("lep_pt", &lep_pt);
            fChain -> SetBranchAddress("lep_eta", &lep_eta);
        }

        void HistogramPlots(UInt_t number_of_entries)
        {
            TCanvas *c1 = new TCanvas("c1", "c1", 10, 10, 900, 600);
            TProfile *hprof_one = new TProfile("hprof_one", "lep_pt vs lep_eta", 100, -TMath::Pi(), TMath::Pi(), 0, 1000000);

            for (UInt_t i = 0; i < number_of_entries; ++i)
            {
                fChain -> GetEntry(i);
                for (UInt_t j = 0; j < lep_pt -> size(); ++j)
                {
                    hprof_one -> Fill(lep_eta -> at(j), lep_pt -> at(j));
                }
            }

            TH2F *h_2d_one = new TH2F("h_one", "lep_pt vs lep_eta", 100, -TMath::Pi(), TMath::Pi(), 100, 0, 1000000);

            for (UInt_t i = 0; i < number_of_entries; ++i)
            {
                fChain -> GetEntry(i);
                for (UInt_t j = 0; j < lep_pt -> size(); ++j)
                {
                    h_2d_one -> Fill(lep_eta -> at(j), lep_pt -> at(j));
                }
            }

            c1 -> Divide(2, 1);
            c1 -> cd(1);
            hprof_one -> Draw();
            hprof_one -> GetXaxis() -> SetTitle("#eta");
            hprof_one -> GetXaxis() -> CenterTitle();
            hprof_one -> GetYaxis() -> SetTitle("p_{T}"); 
            hprof_one -> GetYaxis() -> CenterTitle();
            c1 -> cd(2);
            h_2d_one -> Draw("LEGO");
            h_2d_one -> GetXaxis() -> SetTitle("#eta");
            h_2d_one -> GetXaxis() -> CenterTitle();
            h_2d_one -> GetYaxis() -> SetTitle("p_{T}");
            h_2d_one -> GetYaxis() -> CenterTitle(); 
        }

        ~ Histograms () {};
};

void HistogramMacroTwo()
{
    Histograms *obj1 = new Histograms();
    obj1 -> InputROOTFile("/home/nicole/Desktop/Doctorado/Tercer Semestre/Tópicos Especiales de Física de Campos y Partículas I/Training/DataSet/", "mc_363492.llvv.2lep.root");
    obj1 -> ShowROOTFile(1);
    obj1 -> SetBrach();
    obj1 -> HistogramPlots(100000);
}