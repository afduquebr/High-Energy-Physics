#include <iostream>
#include <string>
#include <stdio.h>

#pragma link C++ enum  myns::myenum;

void Part_3 () {

  TFile *file = TFile::Open("../Root Files/Tracks_Clusters.root");

  TTree *tree = (TTree*) file->Get("JetRecoTree");
  tree->Print();

  UInt_t npv = -1;
  Float_t mu_avg = -1;
  float evtw = -1;

  vector<float> *recojet_R4_pT = {};
  vector<float> *truthjet_R4_pT = {};

  vector<float> *recojet_R10_pT = {};
  vector<float> *recojet_R10_Trimmed_pT = {};

  vector<float> *truthjet_R10_pT = {};
  vector<float> *truthjet_R10_Trimmed_pT = {};


  tree->SetBranchAddress("NPV", &npv);
  tree->SetBranchAddress("mu_average", &mu_avg);
  tree->SetBranchAddress("EventWeight", &evtw);

  tree->SetBranchAddress("RecoJets_R4_pt", &recojet_R4_pT);
  tree->SetBranchAddress("TruthJets_R4_pt", &truthjet_R4_pT);

  tree->SetBranchAddress("RecoJets_R10_pt", &recojet_R10_pT);
  tree->SetBranchAddress("RecoJets_R10_Trimmed_pt", &recojet_R10_Trimmed_pT);

  tree->SetBranchAddress("TruthJets_R10_pt", &truthjet_R10_pT);
  tree->SetBranchAddress("TruthJets_R10_Trimmed_pt", &truthjet_R10_Trimmed_pT);


  TCanvas *canvas = new TCanvas(
    "Canvas",
    "",
    1600,
    1200
  );

// Set Histograms

// Reco-Jet R4 pT vs NPV
TH2F *hist_reco_R4_pT_npv = new TH2F(
    "Reco-jet pT vs. NPV",
    ";NPV; jet pT",
    50,
    10,
    100,
    20,
    0,
    60
  );

// Reco-Jet R4 pT vs Mu-Average
TH2F *hist_reco_R4_pT_mu = new TH2F(
    "Reco-jet pT vs. mu average",
    ";mu_avg; jet pT",
    50,
    10,
    100,
    20,
    0,
    60
  );

// Reco-Jet R10 pT vs Mu-Average
TH2F *hist_reco_R10_pT_mu = new TH2F(
      "Reco-jet vs. Mu Average",
      "; Mu Average; jet pT",
      50,
      1,
      90,
      50,
      80,
      500
  )

// Reco-Jet R10 pT vs NPV

TH2F *hist_reco_R10_pT_npv = new TH2F(
      "Reco-jet vs. NPV",
      "; NPV; jet pT",
      50,
      1,
      50,
      50,
      80,
      500
  )

// Reco-Jet R10 Trimmed pT vs Mu-Average
TH2F *hist_reco_R10_Trimmed_pT_mu = new TH2F(
      "Reco-jet vs. Mu Average",
      "; Mu Average; jet pT",
      50,
      1,
      90,
      50,
      10,
      500
  )

// Reco-Jet R10 Trimmed pT vs NPV

TH2F *hist_reco_R10_Trimmed_pT_npv = new TH2F(
      "Reco-jet vs. NPV",
      "; NPV; jet pT",
      50,
      1,
      50,
      50,
      10,
      500
  )

// Truth-Jet R4 pT vs Mu-Average
TH2F *hist_truth_R4_pT_mu = new TH2F(
      "Truth-jet vs. Mu Average",
      "; Mu Average; jet pT",
      50,
      1,
      90,
      50,
      10,
      200
  )

// Truth-Jet R4 pT vs NPV

TH2F *hist_truth_R4_pT_npv = new TH2F(
      "Truth-jet vs. NPV",
      "; NPV; jet pT",
      50,
      1,
      50,
      50,
      10,
      200
  )

// Truth-Jet R10 pT vs Mu-Average
TH2F *hist_truth_R10_pT_mu = new TH2F(
      "Truth-jet vs. Mu Average",
      "; Mu Average; jet pT",
      50,
      1,
      90,
      50,
      80,
      500
  )

// Truth-Jet R10 pT vs NPV

TH2F *hist_truth_R10_pT_npv = new TH2F(
      "Truth-jet vs. NPV",
      "; NPV; jet pT",
      50,
      1,
      50,
      50,
      80,
      500
  )

// Truth-Jet R10 Trimmed pT vs Mu-Average

TH2F *hist_truth_R10_Trimmed_pT_mu = new TH2F(
      "Truth-jet vs. Mu Average",
      "; Mu Average; jet pT",
      50,
      1,
      90,
      50,
      10,
      500
  )

// Truth-Jet R10 Trimmed pT vs NPV

TH2F *hist_truth_R10_Trimmed_pT_npv = new TH2F(
      "Truth-jet vs. NPV",
      "; NPV; jet pT",
      50,
      1,
      50,
      50,
      10,
      500
  )

// Track-Jet R4 pT vs Mu-Average
TH2F *hist_track_R4_pT_mu = new TH2F(
      "Track-jet vs. Mu Average",
      "; Mu Average; jet pT",
      50,
      1,
      90,
      50,
      10,
      200
  )

// Track-Jet R4 pT vs NPV

TH2F *hist_track_R4_pT_npv = new TH2F(
      "Track-jet vs. NPV",
      "; NPV; jet pT",
      50,
      1,
      50,
      50,
      10,
      200
  )

// Set Profiles

// Profile Reco-Jet R4 pT vs Mu-Average
TProfile *prof_reco_R4_pT_mu = new TProfile(
      "Profile Reco-jet vs. Mu Average",
      "Profile Reco-jet vs. Mu Average; Mu Average; jet pT",
      50,
      1,
      90
  )

// Profile Reco-Jet R4 pT vs NPV
TProfile *prof_reco_R4_pT_npv = new TProfile(
      "Profile Reco-jet vs. NPV",
      "Profile Reco-jet vs. NPV; NPV; jet pT",
     50,
     1,
     50
  )

// Profile Reco-Jet R10 pT vs Mu-Average
TProfile *prof_reco_R10_pT_mu = new TProfile(
      "Profile Reco-jet vs. Mu Average",
      "Profile Reco-jet vs. Mu Average; Mu Average; jet pT",
      50,
      1,
      90
  )

// Profile Reco-Jet R10 pT vs NPV
TProfile *prof_reco_R10_pT_npv = new TProfile(
      "Profile Reco-jet vs. NPV",
      "Profile Reco-jet vs. NPV; NPV; jet pT",
      50,
      1,
      50
  )

// Profile Reco-Jet R10 Trimmed pT vs Mu-Average
TProfile *prof_reco_R10_Trimmed_pT_mu = new TProfile(
      "Profile Reco-jet vs. Mu Average",
      "Profile Reco-jet vs. Mu Average; Mu Average; jet pT",
      50,
      1,
      90
  )

// Profile Reco-Jet R10 Trimmed pT vs NPV
TProfile *prof_reco_R10_Trimmed_pT_npv = new TProfile(
      "Profile Reco-jet vs. NPV",
      "Profile Reco-jet vs. NPV; NPV; jet pT",
      50,
      1,
      50
  )

// Profile Truth-Jet R4 pT vs Mu-Average
TProfile *prof_truth_R4_pT_mu = new TProfile(
      "Profile Truth-jet vs. Mu Average",
      "Profile Truth-jet vs. Mu Average; Mu Average; jet pT",
      50,
      1,
      90
  )

// Profile Truth-Jet R4 pT vs NPV
TProfile *prof_truth_R4_pT_npv = new TProfile(
      "Profile Truth-jet vs. NPV",
      "Profile Truth-jet vs. NPV; NPV; jet pT",
      50,
      1,
      50
  )

// Profile Truth-Jet R10 pT vs Mu-Average
TProfile *prof_truth_R10_pT_mu = new TProfile(
      "Profile Truth-jet vs. Mu Average",
      "Profile Truth-jet vs. Mu Average; Mu Average; jet pT",
      50,
      1,
      90
  )

// Profile Truth-Jet R10 pT vs NPV
TProfile *prof_truth_R10_pT_npv = new TProfile(
      "Profile Truth-jet vs. NPV",
      "Profile Truth-jet vs. NPV; NPV; jet pT",
      50,
      1,
      50
  )

// Profile Truth-Jet R10 Trimmed pT vs Mu-Average
TProfile *prof_truth_R10_Trimmed_pT_mu = new TProfile(
      "Profile Truth-jet vs. Mu Average",
      "Profile Truth-jet vs. Mu Average; Mu Average; jet pT",
      50,
      1,
      90
  )

// Profile Truth-Jet R10 Trimmed pT vs NPV
TProfile *prof_truth_R10_Trimmed_pT_npv = new TProfile(
      "Profile Truth-jet vs. NPV",
      "Profile Truth-jet vs. NPV; NPV; jet pT",
      50,
      1,
      50
  )



  for (i = 0; i < nentries; i++) {
    nbytes = tree->GetEntry(i);

    if(recojet_R4_pT->size()!=0 && recojet_R4_pT->at(0)>20000.){
      for(int j=0; j<recojet_R4_pT->size(); j++){
        hist_reco_R4_pT_mu->Fill(recojet_R4_pT->at(j)/1000.,npv,evtw);
        hist_reco_R4_pT_npv->Fill(recojet_R4_pT->at(j)/1000.,npv,evtw);
        prof_reco_R4_pT_mu->Fill(recojet_R4_pT->at(j)/1000.,mu_avg,evtw);
        prof_reco_R4_pT_npv->Fill(recojet_R4_pT->at(j)/1000.,mu_avg,evtw);
      }
    }

    if(recojet_R10_pT->size()!=0 && recojet_R10_pT->at(0)>20000.){
      for(int j=0; j<recojet_R10_pT->size(); j++){
        hist_reco_R10_pT_mu->Fill(recojet_R10_pT->at(j)/1000.,npv,evtw);
        hist_reco_R10_pT_npv->Fill(recojet_R10_pT->at(j)/1000.,npv,evtw);
        prof_reco_R10_pT_mu->Fill(recojet_R10_pT->at(j)/1000.,mu_avg,evtw);
        prof_reco_R10_pT_npv->Fill(recojet_R10_pT->at(j)/1000.,mu_avg,evtw);
      }
    }

    if(recojet_R10_Trimmed_pT->size()!=0 && recojet_R10_Trimmed_pT->at(0)>20000.){
      for(int j=0; j<recojet_R10_Trimmed_pT->size(); j++){
        hist_reco_R10_Trimmed_pT_mu->Fill(recojet_R10_Trimmed_pT->at(j)/1000.,npv,evtw);
        hist_reco_R10_Trimmed_pT_npv->Fill(recojet_R10_Trimmed_pT->at(j)/1000.,npv,evtw);
        prof_reco_R10_Trimmed_pT_mu->Fill(recojet_R10_Trimmed_pT->at(j)/1000.,mu_avg,evtw);
        prof_reco_R10_Trimmed_pT_npv->Fill(recojet_R10_Trimmed_pT->at(j)/1000.,mu_avg,evtw);
      }
    }

    if(truthjet_R4_pT->size()!=0 && truthjet_R4_pT->at(0)>20000.){
      for(int j=0; j<truthjet_R4_pT->size(); j++){
        hist_truth_R4_pT_mu->Fill(truthjet_R4_pT->at(j)/1000.,npv,evtw);
        hist_truth_R4_pT_npv->Fill(truthjet_R4_pT->at(j)/1000.,npv,evtw);
        prof_truth_R4_pT_mu->Fill(truthjet_R4_pT->at(j)/1000.,mu_avg,evtw);
        prof_truth_R4_pT_npv->Fill(truthjet_R4_pT->at(j)/1000.,mu_avg,evtw);
      }
    }

    if(truthjet_R10_pT->size()!=0 && truthjet_R10_pT->at(0)>20000.){
      for(int j=0; j<truthjet_R10_pT->size(); j++){
        hist_truth_R10_pT_mu->Fill(truthjet_R10_pT->at(j)/1000.,npv,evtw);
        hist_truth_R10_pT_npv->Fill(truthjet_R10_pT->at(j)/1000.,npv,evtw);
        prof_truth_R10_pT_mu->Fill(truthjet_R10_pT->at(j)/1000.,mu_avg,evtw);
        prof_truth_R10_pT_npv->Fill(truthjet_R10_pT->at(j)/1000.,mu_avg,evtw);
      }
    }

    if(truthjet_R10_Trimmed_pT->size()!=0 && truthjet_R10_Trimmed_pT->at(0)>20000.){
      for(int j=0; j<truthjet_R10_Trimmed_pT->size(); j++){
        hist_truth_R10_Trimmed_pT_mu->Fill(truthjet_R10_Trimmed_pT->at(j)/1000.,npv,evtw);
        hist_truth_R10_Trimmed_pT_npv->Fill(truthjet_R10_Trimmed_pT->at(j)/1000.,npv,evtw);
        prof_truth_R10_Trimmed_pT_mu->Fill(truthjet_R10_Trimmed_pT->at(j)/1000.,mu_avg,evtw);
        prof_truth_R10_Trimmed_pT_npv->Fill(truthjet_R10_Trimmed_pT->at(j)/1000.,mu_avg,evtw);
      }
    }
  }

  std::cout << "¡Listo!" << std::endl;

// Save Histograms

// Reco-Jet R4 pT vs Mu-Average
hist_reco_R4_pT_mu->Draw("COLZ")
canvas->Print("Reco-Jet R4 pT vs Mu-Average.pdf")
canvas->Clear()

// Reco-Jet R4 pT vs NPV
hist_reco_R4_pT_npv->Draw("COLZ")
canvas->Print("Reco-Jet R4 pT vs NPV.pdf")
canvas->Clear()

// Reco-Jet R10 pT vs Mu-Average
hist_reco_R10_pT_mu->Draw("COLZ")
canvas->Print("Reco-Jet R10 pT vs Mu-Average.pdf")
canvas->Clear()

// Reco-Jet R10 pT vs NPV
hist_reco_R10_pT_npv->Draw("COLZ")
canvas->Print("Reco-Jet R10 pT vs NPV.pdf")
canvas->Clear()

// Reco-Jet R10 Trimmed pT vs Mu-Average
hist_reco_R10_Trimmed_pT_mu->Draw("COLZ")
canvas->Print("Reco-Jet R10 Trimmed pT vs Mu-Average.pdf")
canvas->Clear()

// Reco-Jet R10 Trimmed pT vs NPV
hist_reco_R10_Trimmed_pT_npv->Draw("COLZ")
canvas->Print("Reco-Jet R10 Trimmed pT vs NPV.pdf")
canvas->Clear()

// Truth-Jet R4 pT vs Mu-Average
hist_truth_R4_pT_mu->Draw("COLZ")
canvas->Print("Truth-Jet R4 pT vs Mu-Average.pdf")
canvas->Clear()

// Truth-Jet R4 pT vs NPV
hist_truth_R4_pT_npv->Draw("COLZ")
canvas->Print("Truth-Jet R4 pT vs NPV.pdf")
canvas->Clear()

// Truth-Jet R10 pT vs Mu-Average
hist_truth_R10_pT_mu->Draw("COLZ")
canvas->Print("Truth-Jet R10 pT vs Mu-Average.pdf")
canvas->Clear()

// Truth-Jet R10 pT vs NPV
hist_truth_R10_pT_npv->Draw("COLZ")
canvas->Print("Truth-Jet R10 pT vs NPV.pdf")
canvas->Clear()

// Truth-Jet R10 Trimmed pT vs Mu-Average
hist_truth_R10_Trimmed_pT_mu->Draw("COLZ")
canvas->Print("Truth-Jet R10 Trimmed pT vs Mu-Average.pdf")
canvas->Clear()

// Truth-Jet R10 Trimmed pT vs NPV
hist_truth_R10_Trimmed_pT_npv->Draw("COLZ")
canvas->Print("Truth-Jet R10 Trimmed pT vs NPV.pdf")
canvas->Clear()

// Profile Reco-Jet R4 pT vs Mu-Average
prof_reco_R4_pT_mu->SetMarkerStyle(20)
prof_reco_R4_pT_mu->SetMarkerColor(4)
canvas->Print("Profile Reco-jet R4 pT vs. Mu Average.pdf")
canvas->Clear()

// Profile Reco-Jet R4 pT vs NPV
prof_reco_R4_pT_npv->SetMarkerStyle(20)
prof_reco_R4_pT_npv->SetMarkerColor(4)
canvas->Print("Profile Reco-jet R4 pT vs. NPV.pdf")
canvas->Clear()

// Profile Reco-Jet R10 pT vs Mu-Average
prof_reco_R10_pT_mu->SetMarkerStyle(20)
prof_reco_R10_pT_mu->SetMarkerColor(4)
canvas->Print("Profile Reco-jet R10 pT vs. Mu Average.pdf")
canvas->Clear()

// Profile Reco-Jet R10 pT vs NPV
prof_reco_R10_pT_npv->SetMarkerStyle(20)
prof_reco_R10_pT_npv->SetMarkerColor(4)
canvas->Print("Profile Reco-jet R10 pT vs. NPV.pdf")
canvas->Clear()

// Profile Reco-Jet R10 Trimmed pT vs Mu-Average
prof_reco_R10_Trimmed_pT_mu->SetMarkerStyle(20)
prof_reco_R10_Trimmed_pT_mu->SetMarkerColor(4)
canvas->Print("Profile Reco-jet R10 Trimmed pT vs. Mu Average.pdf")
canvas->Clear()

// Profile Reco-Jet R10 Trimmed pT vs NPV
prof_reco_R10_Trimmed_pT_npv->SetMarkerStyle(20)
prof_reco_R10_Trimmed_pT_npv->SetMarkerColor(4)
canvas->Print("Profile Reco-jet R10 Trimmed pT vs. NPV.pdf")
canvas->Clear()

// Profile Truth-Jet R4 pT vs Mu-Average
prof_truth_R4_pT_mu->SetMarkerStyle(20)
prof_truth_R4_pT_mu->SetMarkerColor(4)
canvas->Print("Profile Truth-jet R4 pT vs. Mu Average.pdf")
canvas->Clear()

// Profile Truth-Jet R4 pT vs NPV
prof_truth_R4_pT_npv->SetMarkerStyle(20)
prof_truth_R4_pT_npv->SetMarkerColor(4)
canvas->Print("Profile Truth-jet R4 pT vs. NPV.pdf")
canvas->Clear()

// Profile Truth-Jet R10 pT vs Mu-Average
prof_truth_R10_pT_mu->SetMarkerStyle(20)
prof_truth_R10_pT_mu->SetMarkerColor(4)
canvas->Print("Profile Truth-jet R10 pT vs. Mu Average.pdf")
canvas->Clear()

// Profile Truth-Jet R10 pT vs NPV
prof_truth_R10_pT_npv->SetMarkerStyle(20)
prof_truth_R10_pT_npv->SetMarkerColor(4)
canvas->Print("Profile Truth-jet R10 pT vs. NPV.pdf")
canvas->Clear()

// Profile Truth-Jet R10 Trimmed pT vs Mu-Average
prof_truth_R10_Trimmed_pT_mu->SetMarkerStyle(20)
prof_truth_R10_Trimmed_pT_mu->SetMarkerColor(4)
canvas->Print("Profile Truth-jet R10 Trimmed pT vs. Mu Average.pdf")
canvas->Clear()

// Profile Truth-Jet R10 Trimmed pT vs NPV
prof_truth_R10_Trimmed_pT_npv->SetMarkerStyle(20)
prof_truth_R10_Trimmed_pT_npv->SetMarkerColor(4)
canvas->Print("Profile Truth-jet R10 Trimmed pT vs. NPV.pdf")
canvas->Clear()
