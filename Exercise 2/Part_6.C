#include <iostream>
#include <string>
#include <stdio.h>

#pragma link C++ enum  myns::myenum;

void Part_6 () {

  TFile *file = TFile::Open("../Root Files/Tracks_Clusters.root");


  TTree *tree = (TTree*) file->Get("JetRecoTree");
  tree->Print();


  float evtw = -1;

  vector<float> *recojet_R4_pT = {};
  vector<float> *truthjet_R4_pT = {};
  vector<float> *trackjet_R4_pT = {};
  vector<float> *recojet_R4_JVF = {};

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

  tree->SetBranchAddress("RecoJets_R4_jvf", &recojet_R4_JVF);

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

  TH1F *hist_reco_truth_R4_DR = new TH1F(
      "Delta R Reco - Truth",
      "Delta R; #Delta R; Events",
      20,
      0,
      2
    );

    TH1F *hist_reco_truth_R4_DR_cut = new TH1F(
      "Delta R Reco - Truth (Cuts)",
      "Delta R; #Delta R; Events",
      20,
      0,
      2
    );

    TH1F *hist_track_truth_R4_DR = new TH1F(
      "Delta R Track - Truth",
      "Delta R; #Delta R; Events",
      20,
      0,
      2
    );


    int nentries, nbytes, i;
    nentries = (Int_t)tree->GetEntries();

    for (i = 0; i < nentries; i++) {
      nbytes = tree->GetEntry(i);

      if(truthjet_R4_pT->size()!=0 && truthjet_R4_pT->at(0)>20000.){
        TLorentzVector truthjet;
        truthjet.SetPtEtaPhiM(
          truthjet_R4_pT->at(0),
          truthjet_R4_eta->at(0),
          truthjet_R4_phi->at(0),
          truthjet_R4_m->at(0)
        );

        if(recojet_R4_pT->size()!=0 && fabs(recojet_R4_JVF->at(0))>0.5){
          TLorentzVector recojet;
          recojet.SetPtEtaPhiM(
            recojet_R4_pT->at(0),
            recojet_R4_eta->at(0),
            recojet_R4_phi->at(0),
            recojet_R4_m->at(0)
          );

          hist_reco_truth_R4_DR_cut->Fill(truthjet.DeltaR(recojet),evtw);
        }

        if(recojet_R4_pT->size()!=0){
          TLorentzVector recojet;
          recojet.SetPtEtaPhiM(
            recojet_R4_pT->at(0),
            recojet_R4_eta->at(0),
            recojet_R4_phi->at(0),
            recojet_R4_m->at(0)
          );

          hist_reco_truth_R4_DR->Fill(truthjet.DeltaR(recojet),evtw);
        }

        if(trackjet_R4_pT->size()!=0){
          TLorentzVector trackjet;
          trackjet.SetPtEtaPhiM(
            trackjet_R4_pT->at(0),
            trackjet_R4_eta->at(0),
            trackjet_R4_phi->at(0),
            trackjet_R4_m->at(0)
          );

          hist_track_truth_R4_DR->Fill(truthjet.DeltaR(trackjet),evtw);
        }
      }
    }

    std::cout << "¡Listo!" << std::endl;

    hist_reco_truth_R4_DR->SetMarkerStyle(21);
    hist_reco_truth_R4_DR->SetMarkerColor(kRed);
    hist_reco_truth_R4_DR->Scale(1/hist_reco_truth_R4_DR->Integral());
    hist_reco_truth_R4_DR->DrawNormalized(" ");
    hist_reco_truth_R4_DR_cut->SetMarkerStyle(22);
    hist_reco_truth_R4_DR_cut->SetMarkerColor(kBlue);
    hist_reco_truth_R4_DR_cut->Scale(1/hist_reco_truth_R4_DR_cut->Integral());
    hist_reco_truth_R4_DR_cut->DrawNormalized("Same");
    hist_track_truth_R4_DR->SetMarkerStyle(23);
    hist_track_truth_R4_DR->SetMarkerColor(kCyan);
    hist_track_truth_R4_DR->Scale(1/hist_track_truth_R4_DR->Integral());
    hist_track_truth_R4_DR->DrawNormalized("Same");
    canvas->Print("Delta R.pdf");
    canvas->Clear();


}
