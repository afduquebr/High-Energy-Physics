#include <iostream>
#include <string>
#include <stdio.h>

#pragma link C++ enum  myns::myenum;

void Part_7 () {

  TFile *file = TFile::Open("../Root Files/Tracks_Clusters.root");


  TTree *tree = (TTree*) file->Get("JetRecoTree");
  tree->Print();


  UInt_t npv = -1;
  Float_t mu_avg = -1;
  float evtw = -1;
  vector<float> *recojet_R4_pT = {};
  vector<float> *truthjet_R4_pT = {};
  vector<float> *trackjet_R4_pT = {};

  vector<float> *recojet_R4_eta = {};
  vector<float> *recojet_R4_phi = {};
  vector<float> *recojet_R4_m = {};

  vector<float> *truthjet_R4_eta = {};
  vector<float> *truthjet_R4_phi = {};
  vector<float> *truthjet_R4_m = {};

  vector<float> *trackjet_R4_eta = {};
  vector<float> *trackjet_R4_phi = {};
  vector<float> *trackjet_R4_m = {};



  tree->SetBranchAddress("EventWeight", &evtw);

  tree->SetBranchAddress("RecoJets_R4_pt", &recojet_R4_pT);
  tree->SetBranchAddress("TruthJets_R4_pt", &truthjet_R4_pT);
  tree->SetBranchAddress("TrackJets_R4_pt", &trackjet_R4_pT);

  tree->SetBranchAddress("RecoJets_R4_eta", &recojet_R4_eta);
  tree->SetBranchAddress("RecoJets_R4_phi", &recojet_R4_phi);
  tree->SetBranchAddress("RecoJets_R4_m", &recojet_R4_m);

  tree->SetBranchAddress("TruthJets_R4_eta", &truthjet_R4_eta);
  tree->SetBranchAddress("TruthJets_R4_phi", &truthjet_R4_phi);
  tree->SetBranchAddress("TruthJets_R4_m", &truthjet_R4_m);

  tree->SetBranchAddress("TrackJets_R4_eta", &trackjet_R4_eta);
  tree->SetBranchAddress("TrackJets_R4_phi", &trackjet_R4_phi);
  tree->SetBranchAddress("TrackJets_R4_m", &trackjet_R4_m);


  TCanvas *canvas = new TCanvas(
    "Canvas",
    "",
    1600,
    1200
  );




TH1F *hist_matched_reco_truth_pT_20 = new TH1F(
    "Matched Delta R Reco-Truth Jets > 20 GeV",
    "Matched Delta R; pTreco/pTtruth; Events",
    20,
    0,
    5
  );

  TH1F *hist_matched_reco_truth__pT_100 = new TH1F(
    "Matched Delta R Reco-Truth Jets > 100 GeV",
    "Matched Delta R; pTreco/pTtruth; Events",
    20,
    0,
    5
  );

  TH1F *hist_matched_reco_truth_pT_500 = new TH1F(
    "Matched Delta R Reco-Truth Jets > 500 GeV",
    "Matched Delta R; pTreco/pTtruth; Events",
    20,
    0,
    5
  );

  TH1F *hist_matched_track_truth_pT_20 = new TH1F(
    "Matched Delta R Track-Truth > 20 GeV",
    "Matched Delta R; pTtrack/pTtruth; Events",
    20,
    0,
    5
  );

  TH1F *hist_matched_track_truth_pT_100 = new TH1F(
    "Matched Delta R Track-Truth > 100 GeV",
    "Matched Delta R; pTtrack/pTtruth; Events",
    20,
    0,
    5
  );

  TH1F *hist_matched_track_truth_pT_500 = new TH1F(
    "Matched Delta R Track-Truth > 500 GeV",
    "Matched Delta R; pTtrack/pTtruth; Events",
    20,
    0,
    5
  );

  int nentries, nbytes, i;
  nentries = (Int_t)tree->GetEntries();

  for (i = 0; i < nentries; i++) {
    nbytes = tree->GetEntry(i);

    if(truthjet_R4_pT->size()!=0){
      TLorentzVector truthjet;
      truthjet.SetPtEtaPhiM(truthjet_R4_pT->at(0),truthjet_R4_eta->at(0),truthjet_R4_phi->at(0),truthjet_R4_m->at(0));

      if(recojet_R4_pT->size() != 0){
        TLorentzVector recojet;
        recojet.SetPtEtaPhiM(recojet_R4_pT->at(0),recojet_R4_eta->at(0),recojet_R4_phi->at(0),recojet_R4_m->at(0));

        if (truthjet.DeltaR(recojet) < 0.3) {
          if (truthjet_R4_pT->at(0) > 20000.) {
            hist_matched_reco_truth_pT_20->Fill(truthjet_R4_pT->at(0)/recojet_R4_pT->at(0),evtw);
          }

          if (truthjet_R4_pT->at(0) > 100000.) {
            hist_matched_reco_truth__pT_100->Fill(truthjet_R4_pT->at(0)/recojet_R4_pT->at(0),evtw);
          }

          if (truthjet_R4_pT->at(0) > 500000.) {
            hist_matched_reco_truth_pT_500->Fill(truthjet_R4_pT->at(0)/recojet_R4_pT->at(0),evtw);
          }
        }
      }

      if(trackjet_R4_pT->size() != 0){
        TLorentzVector trackJet;
        trackJet.SetPtEtaPhiM(trackjet_R4_pT->at(0),trackjet_R4_eta->at(0),trackjet_R4_phi->at(0),trackjet_R4_m->at(0));

        if (truthjet.DeltaR(trackJet) < 0.3) {
          if (truthjet_R4_pT->at(0)>20000.) {
            hist_matched_track_truth_pT_20->Fill(truthjet_R4_pT->at(0)/trackjet_R4_pT->at(0),evtw);
          }

          if (truthjet_R4_pT->at(0)>100000.) {
            hist_matched_track_truth_pT_100->Fill(truthjet_R4_pT->at(0)/trackjet_R4_pT->at(0),evtw);
          }

          if (truthjet_R4_pT->at(0)>500000.) {
            hist_matched_track_truth_pT_500->Fill(truthjet_R4_pT->at(0)/trackjet_R4_pT->at(0),evtw);
          }
        }
      }

    }
  }

  std::cout << "¡Listo!" << std::endl;

  canvas->SetLogy(1);

  hist_matched_reco_truth_pT_20->SetMarkerStyle(21);
  hist_matched_reco_truth_pT_20->SetMarkerColor(kRed);
  hist_matched_reco_truth_pT_20->Draw("");
  hist_matched_reco_truth__pT_100->SetMarkerStyle(22);
  hist_matched_reco_truth__pT_100->SetMarkerColor(kBlue);
  hist_matched_reco_truth__pT_100->Draw("Same");
  hist_matched_reco_truth_pT_500->SetMarkerStyle(23);
  hist_matched_reco_truth_pT_500->SetMarkerColor(kCyan);
  hist_matched_reco_truth_pT_500->Draw("Same");
  canvas->Print("Matched Reco and Truth Jets.pdf");
  canvas->Clear();

  hist_matched_track_truth_pT_20->SetMarkerStyle(21);
  hist_matched_track_truth_pT_20->SetMarkerColor(kRed);
  hist_matched_track_truth_pT_20->Draw("");
  hist_matched_track_truth_pT_100->SetMarkerStyle(22);
  hist_matched_track_truth_pT_100->SetMarkerColor(kBlue);
  hist_matched_track_truth_pT_100->Draw("Same");
  hist_matched_track_truth_pT_500->SetMarkerStyle(23);
  hist_matched_track_truth_pT_500->SetMarkerColor(kCyan);
  hist_matched_track_truth_pT_500->Draw("Same");
  canvas->Print("Matched Track and Truth Jets.pdf");
  canvas->Clear();

}
