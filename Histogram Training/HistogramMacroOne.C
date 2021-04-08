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

class Histogram
{ 
    private:
        TRandom3 r1;
        vector<Double_t> x1, x2;
    public:
        Histogram () {};
        
        void OneDimensionalHistogramPlot()
        {
            for (UInt_t i = 0; i < 1000; ++i)
            {
                x1.push_back(r1.Gaus(0, 1));
            }

            TH1F *source = new TH1F("source", "source", 100, -3, 3);
            //h1 -> FillRandom("gaus", 1000);
            
            for (UInt_t i = 0; i < x1.size(); ++i)
            {
                source -> Fill(x1[i]);
            }

            TH1F *final = new TH1F("final", "final", 100, -3, 3);

            for (UInt_t i = 0; i < x1.size(); ++i)
            {
                final -> Fill(source -> GetRandom()); //the final histogram gets the statistical distribution of the source histogram
            }

            TCanvas *c1 = new TCanvas("c1", "c1", 800, 1000);
            c1 -> Divide(1, 2);
            c1 -> cd(1);
            source -> Draw();
            c1 -> cd(2);
            final -> Draw();
        }

        void TwoDimensionalHistogramPlot()
        {
            for (UInt_t i = 0; i < 10000; ++i)
            {
                x1.push_back(r1.Gaus(0, 1));
                x2.push_back(r1.Gaus(2, 1));
            }
            
            TH2F *h2 = new TH2F("h2", "h2", 100, -3, 3, 100, -3, 3);
            
            for (UInt_t i = 0; i < x1.size(); ++i)
            {
                h2 -> Fill(x1[i], x2[i]);
            }
            
            TCanvas *c2 = new TCanvas("c2", "c2", 800, 1000);
            h2 -> Draw("CONT4Z");

        }
        
        virtual ~ Histogram () {};
    
};

void HistogramMacroOne()
{
    Histogram *obj1 = new Histogram();
    obj1 -> OneDimensionalHistogramPlot();
    obj1 -> TwoDimensionalHistogramPlot();
}