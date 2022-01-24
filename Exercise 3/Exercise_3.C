
#include <iostream>
#include <string>
#include <stdio.h>

void Exercise_3() {

  TFile *file = TFile::Open(
    "http://csandova.web.cern.ch/csandova/HEP-Ex-Course/Code/TTbarSel/Data_8TeV.root"
  );

  TTree *tree = (TTree*) file->Get("mini");
  tree->Print();

  Bool_t e_trig;
  Bool_t mu_trig;
  Bool_t good_vtx;
  UInt_t lep_n;
  UInt_t jet_n;
  Float_t MET;
  Float_t MET_phi;

  Float_t lep_pt[10];
  Float_t lep_eta[10];
  Float_t lep_phi[10];
  Float_t lep_E[10];
  Int_t lep_type[10];

  Float_t lep_ptcone30[10];
  Float_t lep_etcone20[10];

  Float_t jet_pt[10];
  Float_t jet_eta[10];
  Float_t jet_jvf[10];
  Float_t jet_mv1[10];

  tree->SetBranchAddress("trigE", &e_trig);
  tree->SetBranchAddress("trigM", &mu_trig);
  tree->SetBranchAddress("hasGoodVertex", &good_vtx);
  tree->SetBranchAddress("lep_n", &lep_n);
  tree->SetBranchAddress("jet_n", &jet_n);
  tree->SetBranchAddress("met_et", &MET);
  tree->SetBranchAddress("met_phi", &MET_phi);

  tree->SetBranchAddress("lep_pt", &lep_pt);
  tree->SetBranchAddress("lep_eta", &lep_eta);
  tree->SetBranchAddress("lep_phi", &lep_phi);
  tree->SetBranchAddress("lep_E", &lep_E);
  tree->SetBranchAddress("lep_type", &lep_type);
  tree->SetBranchAddress("lep_ptcone30", &lep_ptcone30);
  tree->SetBranchAddress("lep_etcone20", &lep_etcone20);

  tree->SetBranchAddress("jet_pt", &jet_pt);
  tree->SetBranchAddress("jet_eta", &jet_eta);
  tree->SetBranchAddress("jet_jvf", &jet_jvf);
  tree->SetBranchAddress("jet_MV1", &jet_mv1);

  TCanvas *canvas = new TCanvas("Canvas", "", 800, 600);

  // Histograms for Leptons

  // Transverse Momentum
  TH1F *hist_lepton_pt = new TH1F(
    "Leptons pT",
    "Leptons pT; pT (GeV); Events",
    50,
    0,
    1000
  );

  // Track Isolation
  TH1F *hist_lepton_pt_cone_30 = new TH1F(
    "Track Isolation",
    "Track Isolation; lep_ptcone30/lep_pt; Events",
    50,
    0,
    2
  );

  // Calorimeter Isolation
  TH1F *hist_lepton_et_cone_20 = new TH1F(
    "Calorimeter Isolation",
    "Calorimeter Isolation; lep_etcone30/lep_pt; Events",
    50,
    0,
    2
  );

  // Pseudorapidity (Eta)
  TH1F *hist_lep_eta = new TH1F(
    "Leptons eta",
    "Leptons eta; eta; Events",
    50,
    -4,
    4
  );



  // Histograms for Jets

  // Number of jets
  TH1F *hist_njets = new TH1F(
    "Number of jets",
    "Number of jets; Number of Jets; Events",
    15,
    0,
    15
  );

  // Transverse Momentum
  TH1F *hist_jets_pt = new TH1F(
    "Jets pT",
    "Jets pT; pT (GeV); Events",
    50,
    0,
    1000
  );

  // Pseudorapidity (Eta)
  TH1F *hist_jets_eta = new TH1F(
    "Jets eta",
    "Jets eta; eta; Events",
    50,
    -4,
    4
  );

  // Jet Vertex Fraction
  TH1F *hist_jets_JVF = new TH1F(
    "Jets JVF",
    "Jets JVF; JVF; Events",
    50,
    -1,
    1
  );

  // MV1 Output
  TH1F *hist_jets_MV1 = new TH1F(
    "Jets MV1",
    "Jets MV1; MV1; Events",
    50,
    0,
    1
  );

  // Number of b-Jets
  TH1F *hist_nbjets = new TH1F(
    "Number of b-jets",
    "Number of b-jets; Number of b-jets; Events",
    15,
    0,
    15
  );



  //Missing Transverse Energy
  TH1F *hist_MET = new TH1F(
    "MET",
    "MET; MET (GeV); Events",
    50,
    0,
    250
  );


  // Transverse Mass of W Boson
  TH1F *hist_mTW = new TH1F(
    "mTW", "mTW; mTW (GeV); Events",
    50,
    0,
    250
  );


  // Histogram for cutflows
  TH1F *cutflow = new TH1F(
    "Cutflow",
    "Cutflow; Cut; Events",
    10,
    0,
    10
  );

  int nentries, nbytes, i;
  nentries = (Int_t)tree->GetEntries();

  int cut_1 = 0;
  int cut_2 = 0;
  int cut_3 = 0;
  int cut_4 = 0;
  int cut_5 = 0;
  int cut_6 = 0;
  int cut_7 = 0;
  int cut_8 = 0;

  for (i = 0; i<nentries; i++) {
    nbytes = tree->GetEntry(i);

    //First cut: Good vertex
    if(!good_vtx) continue;
    cut_1++;
    cutflow->Fill(1);

    //Second cut: Trigger
    if(!e_trig && !mu_trig) continue;
    cut_2++;
    cutflow->Fill(2);

    // Preselection of good leptons
    int n_mu = 0;
    int n_el = 0;
    int n_lep = 0;
    int g_lep = 0;

    for(int j=0; j<lep_n; j++){
      hist_lepton_pt->Fill(lep_pt[j]/1000);
      hist_lepton_pt_cone_30->Fill(lep_ptcone30[j]/lep_pt[j]);
      hist_lepton_et_cone_20->Fill(lep_etcone20[j]/lep_pt[j]);
      hist_lep_eta->Fill(lep_eta[j]);

      if(lep_pt[j]<25000.0) continue;

      if(lep_ptcone30[j]/lep_pt[j]>0.15) continue;

      if(lep_etcone20[j]/lep_pt[j]>0.15) continue;

      if(lep_type[j]==13 && TMath::Abs(lep_eta[j])<2.5){
        n_mu++;
        g_lep=j;
      }

      if(lep_type[j]==11 && TMath::Abs(lep_eta[j])<2.47){
        if(TMath::Abs(lep_eta[j])<1.37 || TMath::Abs(lep_eta[j])>1.52){
          n_el++;
          g_lep=j;
        }
      }

    }
    n_lep = n_el + n_mu;

    //Third cut: Select events with one good lepton
    if(n_lep!=1) continue;
    cut_3++;
    cutflow->Fill(3);

    int n_jets = 0;
    int n_bjets = 0;

    //Fill Histogram of Number of jets
    hist_njets->Fill(jet_n);

    //Fourth cut: At least 4 jets
    if (jet_n<4) continue;
    cut_4++;
    cutflow->Fill(4);

    for (int j=0; j<jet_n; j++){
      hist_jets_pt->Fill(jet_pt[j]/1000);
      hist_jets_eta->Fill(jet_eta[j]);
      hist_jets_JVF->Fill(jet_jvf[j]);
      hist_jets_MV1->Fill(jet_mv1[j]);

      // Jet cuts
      if(jet_pt[j]<25000.) continue;

      //Eta cut
      if(jet_eta[j]>2.5) continue;

      // JVF cleaning
      if(jet_pt[j]<50000. && TMath::Abs(jet_eta[j])<2.4){
        if(jet_jvf[j]<0.5) continue;
      }

      n_jets++;

      // MV1 cut
      if (jet_mv1[j] < 0.7892) continue;

      n_bjets ++;
    }


    //Fifth cut: At least 4 good jets
    if (n_jets<4) continue;
    cut_5++;
    cutflow->Fill(5);

    hist_nbjets->Fill(n_bjets);

    //Sixth cut: at least one b-jet
    if(n_bjets<2) continue;
    cut_6++;
    cutflow->Fill(6);

    hist_MET->Fill(MET / 1000);

    //Seventh cut: MET > 30 GeV
    if (MET < 30000.) continue;
    cut_7++;
    cutflow->Fill(7);

    // TLorentzVector
    TLorentzVector Lepton  = TLorentzVector();
    TLorentzVector  MeT  = TLorentzVector();

    Lepton.SetPtEtaPhiE(
      lep_pt[g_lep],
      lep_eta[g_lep],
      lep_phi[g_lep],
      lep_E[g_lep]
    );

    MeT.SetPtEtaPhiE(
      MET,
      0,
      MET_phi,
      MET
    );

    // Determinate of the mTW
    float mTW = sqrt(2*Lepton.Pt()*MeT.Et()*(1-cos(Lepton.DeltaPhi(MeT))));

    hist_mTW->Fill(mTW / 1000);

    //Eight cut: mTW > 30 GeV
    if (mTW < 30000.) continue;
    cut_8++;
    cutflow->Fill(8);

  }

  std::cout << "All events:" << nentries << std::endl;
  std::cout << "Cut 1:" << cut_1 << std::endl;
  std::cout << "Cut 2:" << cut_2 << std::endl;
  std::cout << "Cut 3:" << cut_3 << std::endl;
  std::cout << "Cut 4:" << cut_4 << std::endl;
  std::cout << "Cut 5:" << cut_5 << std::endl;
  std::cout << "Cut 6:" << cut_6 << std::endl;
  std::cout << "Cut 7:" << cut_7 << std::endl;
  std::cout << "Cut 8:" << cut_8 << std::endl;

  canvas->SetLogy();
  cutflow->SetFillColor(kYellow);
  cutflow->Draw("");
  canvas->Print("cutflow.pdf");
  canvas->Clear();

  hist_lepton_pt->SetFillColor(kCyan);
  hist_lepton_pt->Draw();
  canvas->Print("hist_lepton_pt.pdf");
  canvas->Clear();

  hist_lepton_pt_cone_30->SetFillColor(kCyan);
  hist_lepton_pt_cone_30->Draw();
  canvas->Print("hist_lepton_pt_cone_30.pdf");
  canvas->Clear();

  hist_lepton_et_cone_20->SetFillColor(kCyan);
  hist_lepton_et_cone_20->Draw();
  canvas->Print("hist_lepton_et_cone_20.pdf");
  canvas->Clear();

  hist_lep_eta->SetFillColor(kCyan);
  hist_lep_eta->Draw();
  canvas->Print("hist_lep_eta.pdf");
  canvas->Clear();

  hist_njets->SetFillColor(kTeal);
  hist_njets->Draw();
  canvas->Print("hist_njets.pdf");
  canvas->Clear();

  hist_jets_pt->SetFillColor(kTeal);
  hist_jets_pt->Draw();
  canvas->Print("hist_jets_pt.pdf");
  canvas->Clear();

  hist_jets_eta->SetFillColor(kTeal);
  hist_jets_eta->Draw();
  canvas->Print("hist_jets_eta.pdf");
  canvas->Clear();

  hist_jets_JVF->SetFillColor(kTeal);
  hist_jets_JVF->Draw();
  canvas->Print("hist_jets_JVF.pdf");
  canvas->Clear();

  hist_jets_MV1->SetFillColor(kTeal);
  hist_jets_MV1->Draw();
  canvas->Print("hist_jets_MV1.pdf");
  canvas->Clear();

  hist_nbjets->SetFillColor(kTeal);
  hist_nbjets->Draw();
  canvas->Print("hist_nbjets.pdf");
  canvas->Clear();
  canvas->SetLogy(false);

  hist_MET->SetFillColor(kRed);
  hist_MET->Draw();
  canvas->Print("hist_MET.pdf");
  canvas->Clear();

  hist_mTW->SetFillColor(kOrange);
  hist_mTW->Draw();
  canvas->Print("hist_mTW.pdf");
  canvas->Clear();
}
