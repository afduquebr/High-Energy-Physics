#include <iostream>
#include <string>
#include <stdio.h>

#pragma link C++ enum  myns::myenum;

void Part_8 () {

  TFile *file = TFile::Open("../Root Files/Tracks_Clusters.root");


  TTree *tree = (TTree*) file->Get("JetRecoTree");
  tree->Print();


  float evtw = -1;

  vector<float> *recojet_R10_m = {};
  vector<float> *recojet_R10_Trimmed_m = {};

  vector<float> *truthjet_R10_m = {};
  vector<float> *truthjet_R10_Trimmed_m = {};


  tree->SetBranchAddress("EventWeight", &evtw);

  tree->SetBranchAddress("RecoJets_R10_m", &recojet_R10_m);
  tree->SetBranchAddress("RecoJets_R10_Trimmed_m", &recojet_R10_Trimmed_m);

  tree->SetBranchAddress("TruthJets_R10_m", &truthjet_R10_m);
  tree->SetBranchAddress("TruthJets_R10_Trimmed_m", &truthjet_R10_Trimmed_m);


  TCanvas *canvas = new TCanvas(
    "Canvas",
    "",
    1600,
    1200
  );


  TH1F *hist_reco_R10_mass = new TH1F(
   "Leading Reco-Jet R10 Mass",
   "Leading Reco-Jet R10 Mass; Mass; Events",
   20,
   0,
   2000
 );

 TH1F *hist_reco_R10_Trimmed_mass = new TH1F(
   "Leading Reco-Jet R10 Trimmed Mass",
   "Leading Reco-Jet R10 Mass; Mass; Events",
   20,
   0,
   2000
 );

 TH1F *hist_truth_R10_mass = new TH1F(
   "Leading Truth-Jet R10 Mass",
   "Leading Truth-Jet R10 Mass; Mass; Events",
   20,
   0,
   2000
 );

 TH1F *hist_truth_R10_Trimmed_mass = new TH1F(
   "Leading Truth-Jet R10 Trimmed Mass",
   "Leading Truth-Jet R10 Mass; Mass; Events",
   20,
   0,
   2000
 );


 int nentries, nbytes, i;
 nentries = (Int_t)tree->GetEntries();

 for (i = 0; i < nentries; i++) {
    nbytes = tree->GetEntry(i);

    if(recojet_R10_m->size() > 0){
      hist_reco_R10_mass->Fill(recojet_R10_m->at(0)/1000., evtw);
      hist_reco_R10_Trimmed_mass->Fill(recojet_R10_Trimmed_m->at(0)/1000., evtw);
    }

    if (truthjet_R10_m->size() > 0) {
      hist_truth_R10_mass->Fill(truthjet_R10_m->at(0)/1000., evtw);
      hist_truth_R10_Trimmed_mass->Fill(truthjet_R10_Trimmed_m->at(0)/1000., evtw);
    }
  }

  std::cout << "¡Listo!" << std::endl;

  hist_reco_R10_mass->SetMarkerStyle(21);
  hist_reco_R10_mass->SetMarkerColor(kRed);
  hist_reco_R10_mass->Draw("");
  hist_reco_R10_Trimmed_mass->SetMarkerStyle(22);
  hist_reco_R10_Trimmed_mass->SetMarkerColor(kBlue);
  hist_reco_R10_Trimmed_mass->Draw("Same");
  canvas->Print("Reco-Jet R10 and R10 Trimmed Mass.pdf");
  canvas->Clear();

  hist_truth_R10_mass->SetMarkerStyle(21);
  hist_truth_R10_mass->SetMarkerColor(kRed);
  hist_truth_R10_mass->Draw("");
  hist_truth_R10_Trimmed_mass->SetMarkerStyle(22);
  hist_truth_R10_Trimmed_mass->SetMarkerColor(kBlue);
  hist_truth_R10_Trimmed_mass->Draw("Same");
  canvas->Print("Truth-Jet R10 and R10 Trimmed Mass.pdf");
}
