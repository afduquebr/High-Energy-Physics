#include <iostream>
#include <string>
#include <stdio.h>

#pragma link C++ enum  myns::myenum;

void Part_45 () {

  TFile *file = TFile::Open("../Root Files/Tracks_Clusters.root");


  TTree *tree = (TTree*) file->Get("JetRecoTree");
  tree->Print();


  UInt_t npv = -1;
  Float_t mu_avg = -1;
  float evtw = -1;

  vector<float> *recojet_R4_pT = {};
  vector<float> *truthjet_R4_pT = {};
  vector<float> *trackjet_R4_pT = {};
  vector<float> *recojet_R4_JVF = {};

  tree->SetBranchAddress("NPV", &npv);
  tree->SetBranchAddress("mu_average", &mu_avg);
  tree->SetBranchAddress("EventWeight", &evtw);

  tree->SetBranchAddress("RecoJets_R4_pt", &recojet_R4_pT);
  tree->SetBranchAddress("TruthJets_R4_pt", &truthjet_R4_pT);
  tree->SetBranchAddress("TrackJets_R4_pt", &trackjet_R4_pT);
  tree->SetBranchAddress("RecoJets_R4_jvf", &recojet_R4_JVF);


  TCanvas *canvas = new TCanvas(
    "Canvas",
    "",
    1600,
    1200
  );



// With cuts
TH1F *hist_lead_reco__R4_pT_cut = new TH1F(
  "Leading Reco-jet R4 (Cut)",
  "Leading jet pT; pT (GeV);Events",
  20,
  0,
  200
);


// Without cuts
TH1F *hist_lead_reco_R4_pT = new TH1F(
  "Leading Reco-jet R$",
  "Leading jet pT; pT (GeV);Events",
  20,
  0,
  200
);

TH1F *hist_lead_truth_R4_pT = new TH1F(
  "Leading Truth-jet R4",
  "Leading jet pT; pT (GeV);Events",
  20,
  0,
  200
);

TH1F *hist_lead_track_R4_pT = new TH1F(
  "Leading Track-jet R4",
  "Leading jet pT; pT (GeV);Events",
  20,
  0,
  200
);


TProfile *prof_track_R4_pT_mu = new TProfile(
      "Profile Track-jet R4 vs. Mu Average",
      "Profile Track-jet vs. Mu Average; Mu Average; jet pT",
      50,
      1,
      90,
      0,
      200
  );


TProfile *prof_track_R4_pT_npv = new TProfile(
      "Profile Track-jet R4 vs. NPV",
      "Profile Track-jet vs. NPV; NPV; jet pT",
      50,
      1,
      50,
      0,
      200
  );


for (i = 0; i < nentries; i++) {
  nbytes = tree->GetEntry(i);
  if(recojet_R4_pT->size()!=0 && recojet_R4_pT->at(0)>20000.){
    hist_lead_reco_R4_pT->Fill(recojet_R4_pT->at(0)/1000., evtw);
    hist_lead_truth_R4_pT->Fill(truthjet_R4_pT->at(0)/1000., evtw);

    if(std::abs(recojet_R4_JVF->at(0)) > 0.5){
      hist_lead_reco__R4_pT_cut->Fill(recojet_R4_pT->at(0)/1000., evtw);
    }
  }

  if(trackjet_R4_pT->size()!=0 && trackjet_R4_pT->at(0)>20000.){
    hist_lead_track_R4_pT->Fill(trackjet_R4_pT->at(0)/1000., evtw);
    for(int j=0; j<trackjet_R4_pT->size(); j++){
      prof_track_R4_pT_mu->Fill(mu_avg,trackjet_R4_pT->at(j)/1000.,evtw);
      prof_track_R4_pT_npv->Fill(npv,trackjet_R4_pT->at(j)/1000.,evtw);
    }
  }

}

std::cout << "¡Listo!" << std::endl;

canvas->SetLogy(1);

// Comparar Truth y Reco Jets

hist_lead_reco__R4_pT_cut->SetMarkerStyle(21);
hist_lead_reco__R4_pT_cut->SetMarkerColor(kRed);
hist_lead_reco__R4_pT_cut->Draw("");

hist_lead_reco_R4_pT->SetMarkerStyle(22);
hist_lead_reco_R4_pT->SetMarkerColor(kBlue);
hist_lead_reco_R4_pT->Draw("Same");

hist_lead_truth_R4_pT->SetMarkerStyle(23);
hist_lead_truth_R4_pT->SetMarkerColor(kCyan);
hist_lead_truth_R4_pT->Draw("Same");

canvas->Print("Leading Truth and Reco jet R4 pT.pdf");
canvas->Clear();


// Comparar Track y Reco Jets

hist_lead_reco__R4_pT_cut->SetMarkerStyle(21);
hist_lead_reco__R4_pT_cut->SetMarkerColor(kRed);
hist_lead_reco__R4_pT_cut->Draw("");

hist_lead_reco_R4_pT->SetMarkerStyle(22);
hist_lead_reco_R4_pT->SetMarkerColor(kBlue);
hist_lead_reco_R4_pT->Draw("Same");

hist_lead_track_R4_pT->SetMarkerStyle(23);
hist_lead_track_R4_pT->SetMarkerColor(kCyan);
hist_lead_track_R4_pT->Draw("Same");

canvas->Print("Leading Track and Reco jet R4 pT.pdf");
canvas->Clear();

canvas->SetLogy(0);

// Track Profiles

// Profile Track-Jet R4 pT vs Mu-Average
prof_track_R4_pT_mu->SetMarkerStyle(20);
prof_track_R4_pT_mu->SetMarkerColor(4);
prof_track_R4_pT_mu->Draw();
canvas->Print("Profile Track-jet R4 pT vs. Mu Average.pdf");
canvas->Clear();

// Profile Track-Jet R4 pT vs NPV
prof_track_R4_pT_npv->SetMarkerStyle(20);
prof_track_R4_pT_npv->SetMarkerColor(4);
prof_track_R4_pT_npv->Draw();
canvas->Print("Profile Track-jet R4 pT vs. NPV.pdf");
canvas->Clear();
