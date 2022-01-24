#include <iostream>
#include <string>
#include <stdio.h>

void Exercise_4 () {

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









  TFile *file_MC = TFile::Open(
    "http://csandova.web.cern.ch/csandova/HEP-Ex-Course/Code/TTbarSel/ttbar_8TeV.root"
  );

  // Get the Tree from the Root File
  TTree *tree_MC = (TTree*) file_MC->Get("mini");
  tree_MC->Print();

  Bool_t e_trig_MC;
  Bool_t mu_trig_MC;
  Bool_t good_vtx_MC;
  UInt_t lep_n_MC;
  UInt_t jet_n_MC;
  Float_t MET_MC;
  Float_t MET_phi_MC;

  Float_t scalef_pileup;
  Float_t scalef_e;
  Float_t scalef_mu;
  Float_t scalef_btag;
  Float_t scalef_trigger;
  Float_t scalef_jvfsf;
  Float_t scalef_zvertex;

  Float_t lep_pt_MC[10];
  Float_t lep_eta_MC[10];
  Float_t lep_phi_MC[10];
  Float_t lep_E_MC[10];
  Int_t lep_type_MC[10];
  Float_t lep_ptcone30_MC[10];
  Float_t lep_etcone20_MC[10];

  Float_t jet_pt_MC[10];
  Float_t jet_eta_MC[10];
  Float_t jet_jvf_MC[10];
  Float_t jet_mv1_MC[10];

  tree_MC->SetBranchAddress("trigE", &e_trig_MC);
  tree_MC->SetBranchAddress("trigM", &mu_trig_MC);
  tree_MC->SetBranchAddress("hasGoodVertex", &good_vtx_MC);
  tree_MC->SetBranchAddress("lep_n", &lep_n_MC);
  tree_MC->SetBranchAddress("jet_n", &jet_n_MC);
  tree_MC->SetBranchAddress("met_et", &MET_MC);
  tree_MC->SetBranchAddress("met_phi", &MET_phi_MC);

  tree_MC->SetBranchAddress("scaleFactor_PILEUP", &scalef_pileup);
  tree_MC->SetBranchAddress("scaleFactor_ELE", &scalef_e);
  tree_MC->SetBranchAddress("scaleFactor_MUON", &scalef_mu);
  tree_MC->SetBranchAddress("scaleFactor_BTAG", &scalef_btag);
  tree_MC->SetBranchAddress("scaleFactor_TRIGGER", &scalef_trigger);
  tree_MC->SetBranchAddress("scaleFactor_JVFSF", &scalef_jvfsf);
  tree_MC->SetBranchAddress("scaleFactor_ZVERTEX", &scalef_zvertex);

  tree_MC->SetBranchAddress("lep_pt", &lep_pt_MC);
  tree_MC->SetBranchAddress("lep_eta", &lep_eta_MC);
  tree_MC->SetBranchAddress("lep_phi", &lep_phi_MC);
  tree_MC->SetBranchAddress("lep_E", &lep_E_MC);
  tree_MC->SetBranchAddress("lep_type", &lep_type_MC);
  tree_MC->SetBranchAddress("lep_ptcone30", &lep_ptcone30_MC);
  tree_MC->SetBranchAddress("lep_etcone20", &lep_etcone20_MC);

  tree_MC->SetBranchAddress("jet_pt", &jet_pt_MC);
  tree_MC->SetBranchAddress("jet_eta", &jet_eta_MC);
  tree_MC->SetBranchAddress("jet_jvf", &jet_jvf_MC);
  tree_MC->SetBranchAddress("jet_MV1", &jet_mv1_MC);

  // Histograms for Leptons
  TH1F *hist_lep_pt_MC = new TH1F(
    "Leptons pT", "Leptons pT; pT (GeV); Events",
    50, 0, 1000
  );

  TH1F *hist_lep_pt_cone_30_MC = new TH1F(
    "Track isolation", "Track isolation; lep_ptcone30/lep_pt; Events",
    50, 0, 0.2
  );

  TH1F *hist_lep_et_cone_20_MC = new TH1F(
    "Calorimeter isolation",
    "Calorimeter isolation; lep_etcone30/lep_pt; Events",
    50, 0, 0.2
  );

  TH1F *hist_lep_eta_MC = new TH1F(
    "Leptons eta", "Leptons eta; eta; Events",
    50, -5, 5
  );

  // Histograms for Jets
  TH1F *hist_njets_MC = new TH1F(
    "Number of jets", "n-jets; Jet multiplicity; Events",
    10,0,10
  );

  TH1F *hist_jet_pt_MC = new TH1F(
    "Jets pT", "Jets pT; pT (GeV); Events",
    50, 0, 1000
  );

  TH1F *hist_jet_eta_MC = new TH1F(
    "Jets eta", "Jets eta; eta; Events",
    50, -5, 5
  );

  TH1F *hist_jet_JVF_MC = new TH1F(
    "Jets JVF", "Jets JVF; JVF; Events",
    50, 0, 1
  );

  TH1F *hist_jet_MV1_MC = new TH1F(
    "Jets MV1", "Jets MV1; MV1; Events",
    50, 0.5, 1
  );

  // Histogram for bJets
  TH1F *hist_nbjets_MC = new TH1F(
    "Number of b-jets", "n-bjets; b-Jet multiplicity; Events",
    50, 0, 6
  );

  // Histogram for MET
  TH1F *hist_MET_MC = new TH1F(
    "MET", "MET; MET (GeV); Events",
    50, 0, 200
  );

  // Histogram for mTW
  TH1F *hist_mTW_MC = new TH1F(
    "mTW", "mTW; mTW (GeV); Events",
    50, 0, 200
  );

  // Histogram for cuts
  TH1F *cutflow_MC = new TH1F("Cutflow","Cutflow; Cut; Events",10,0,10);

  int nentries_MC, nbytes_MC;
  nentries_MC = (Int_t)tree_MC->GetEntries();

  int cut_1_MC = 0;
  int cut_2_MC = 0;
  int cut_3_MC = 0;
  int cut_4_MC = 0;
  int cut_5_MC = 0;
  int cut_6_MC = 0;
  int cut_7_MC = 0;
  int cut_8_MC = 0;

  for (i = 0; i < nentries_MC; i++) {
    nbytes_MC = tree_MC->GetEntry(i);

    // Weight scale for MC
    Float_t N_MC_evt = 49761200.21;
    Float_t filter = 0.072212854;
    Float_t sigma = 137.29749; // pb^-1

    Float_t L_MC = N_MC_evt * filter / sigma;

    Float_t Weight_MC = 1000 / L_MC;

    Float_t sf = scalef_pileup * scalef_e * scalef_mu * scalef_btag;
    sf *= scalef_trigger * scalef_jvfsf * scalef_zvertex;

    Float_t evt_wt = sf * Weight_MC;

    //First cut: Good vertex
    if(!good_vtx_MC) continue;
    cut_1_MC++;
    cutflow_MC->Fill(1, evt_wt);

    //Second cut: Trigger
    if(!e_trig_MC && !mu_trig_MC) continue;
    cut_2_MC++;
    cutflow_MC->Fill(2, evt_wt);

    // Preselection of good leptons
    int n_mu = 0;
    int n_el = 0;
    int n_lep = 0;
    int g_lep = 0;

    //Loop over leptons
    for (int j=0; j < lep_n_MC; j++) {

      if( lep_pt_MC[j] < 25000.0) continue;
      hist_lep_pt_MC->Fill(lep_pt_MC[j] / 1000, evt_wt);

      if( lep_ptcone30_MC[j]/lep_pt_MC[j] > 0.15 ) continue;
      hist_lep_pt_cone_30_MC->Fill(lep_ptcone30_MC[j] / lep_pt_MC[j], evt_wt);

      if( lep_etcone20_MC[j]/lep_pt_MC[j] > 0.15 ) continue;
      hist_lep_et_cone_20_MC->Fill(lep_etcone20_MC[j] / lep_pt_MC[j], evt_wt);

      if(lep_type_MC[j] == 13 && TMath::Abs(lep_eta_MC[j]) < 2.5){
        n_mu++;
        g_lep = j;
        hist_lep_eta_MC->Fill(lep_eta_MC[j], evt_wt);
      }

      if (lep_type_MC[j]==11 && TMath::Abs(lep_eta_MC[j]) < 2.47){
        if (TMath::Abs(lep_eta_MC[j]) < 1.37 || TMath::Abs(lep_eta_MC[j]) > 1.52) {
          n_el++;
          g_lep = j;
          hist_lep_eta_MC->Fill(lep_eta_MC[j], evt_wt);
        }
      }

    }
    n_lep = n_el + n_mu;

    //Select events with only 1 good lepton and fill the cutflow_MC histogram
    if (n_lep != 1) continue;
    cutflow_MC->Fill(3, evt_wt);
    cut_3_MC++;


    int n_jets = 0;
    int n_bjets = 0;

    //Fourth cut: At least 4 jets
    if (jet_n_MC < 4) continue;
    cutflow_MC->Fill(4, evt_wt);
    cut_4_MC++;

    //Number of jets distribution
    hist_njets_MC->Fill(jet_n_MC, evt_wt);

    for (int j=0; j < jet_n_MC; j++){
      // To complete: apply jet cuts to find the good jets
      if (jet_pt_MC[j] < 25000.) continue;
      hist_jet_pt_MC->Fill(jet_pt_MC[j] / 1000, evt_wt);

      //Eta cut
      if (jet_eta_MC[j] > 2.5) continue;
      hist_jet_eta_MC->Fill(jet_eta_MC[j], evt_wt);
      // JVF cleaning
      if (jet_pt_MC[j] < 50000. && TMath::Abs(jet_eta_MC[j]) < 2.4) {
        if (jet_jvf_MC[j] < 0.5) continue;
      }
      hist_jet_JVF_MC->Fill(jet_jvf_MC[j], evt_wt);

      n_jets ++;

      // cut on 0.7892 MV1 and count the number of b-jets
      if (jet_mv1_MC[j] < 0.7892) continue;

      n_bjets ++;
      hist_jet_MV1_MC->Fill(jet_mv1_MC[j], evt_wt);
    }


    //Fifth cut: At least 4 good jets
    if (n_jets < 4) continue;
    cutflow_MC->Fill(5, evt_wt);
    cut_5_MC++;

    //Sixth cut: at least one b-jet
    if (n_bjets < 2) continue;
    cutflow_MC->Fill(6, evt_wt);
    cut_6_MC++;
    hist_nbjets_MC->Fill(n_bjets, evt_wt);

    //Seventh cut: MET > 30 GeV
    if (MET_MC < 30000.) continue;
    cutflow_MC->Fill(7, evt_wt);
    cut_7_MC++;
    hist_MET_MC->Fill(MET_MC / 1000, evt_wt);

    // TLorentzVector definitions
    TLorentzVector Lepton  = TLorentzVector();
    TLorentzVector  MeT  = TLorentzVector();

    //To complete: Lorentz vectors for the lepton and MET. Use SetPtEtaPhiE().
    Lepton.SetPtEtaPhiE(
      lep_pt_MC[g_lep],
      lep_eta_MC[g_lep],
      lep_phi_MC[g_lep],
      lep_E_MC[g_lep]
    );

    MeT.SetPtEtaPhiE(
      MET_MC,
      0,
      MET_phi_MC,
      MET_MC
    );

    //Calculation of the mTW using TLorentz vectors
    float mTW = sqrt(2*Lepton.Pt()*MeT.Et()*(1-cos(Lepton.DeltaPhi(MeT))));

    //Eight cut: mTW > 30 GeV
    if (mTW < 30000.) continue;
    cutflow_MC->Fill(8, evt_wt);
    cut_8_MC++;
    hist_mTW_MC->Fill(mTW / 1000, evt_wt);
  }

  std::cout << "Done!" << std::endl;
  std::cout << "All events:" << nentries_MC << std::endl;
  std::cout << "Cut1:" << cut_1_MC << std::endl;
  std::cout << "Cut2:" << cut_2_MC << std::endl;
  std::cout << "Cut3:" << cut_3_MC << std::endl;
  std::cout << "Cut4:" << cut_4_MC << std::endl;
  std::cout << "Cut5:" << cut_5_MC << std::endl;
  std::cout << "Cut6:" << cut_6_MC << std::endl;
  std::cout << "Cut7:" << cut_7_MC << std::endl;
  std::cout << "Cut8:" << cut_8_MC << std::endl;

  std::cout << '\n';

  std::cout << '\n';
  std::cout << "Saving Histograms" << '\n';
  std::cout << '\n';

  std::cout << '\n';
  std::cout << "Histogram for Cuts" << '\n';
  std::cout << '\n';

  canvas->SetLogy();
  cutflow->SetMarkerStyle(21);
  cutflow->SetMarkerColor(kTeal);
  cutflow->Draw("E");
  cutflow_MC->SetFillColor(kYellow);
  cutflow_MC->Draw("SAMEH");
  canvas->Print("MonteCarloVSData/cutflow.pdf");
  canvas->Clear();

  std::cout << '\n';
  std::cout << "Histogram for Leptons" << '\n';
  std::cout << '\n';

  hist_lep_pt_MC->SetFillColor(kCyan);
  hist_lep_pt_MC->Draw("HIST");
  hist_lepton_pt->SetMarkerStyle(21);
  hist_lepton_pt->SetMarkerColor(kTeal);
  hist_lepton_pt->Draw("SAME");
  canvas->Print("MonteCarloVSData/hist_lep_pt.pdf");
  canvas->Clear();

  hist_lep_pt_cone_30_MC->SetFillColor(kCyan);
  hist_lep_pt_cone_30_MC->Draw("HIST");
  hist_lepton_pt_cone_30->SetMarkerStyle(21);
  hist_lepton_pt_cone_30->SetMarkerColor(kTeal);
  hist_lepton_pt_cone_30->Draw("SAME");
  canvas->Print("MonteCarloVSData/hist_lep_pt_cone_30.pdf");
  canvas->Clear();

  hist_lep_et_cone_20_MC->SetFillColor(kCyan);
  hist_lep_et_cone_20_MC->Draw("HIST");
  hist_lepton_et_cone_20->SetMarkerStyle(21);
  hist_lepton_et_cone_20->SetMarkerColor(kTeal);
  hist_lepton_et_cone_20->Draw("SAME");
  canvas->Print("MonteCarloVSData/hist_lep_et_cone_20.pdf");
  canvas->Clear();

  hist_lep_eta_MC->SetFillColor(kTeal);
  hist_lep_eta_MC->Draw("HIST");
  hist_lep_eta->SetMarkerStyle(21);
  hist_lep_eta->SetMarkerColor(kTeal);
  hist_lep_eta->Draw("SAME");
  canvas->Print("MonteCarloVSData/hist_lep_eta.pdf");
  canvas->Clear();

  std::cout << '\n';
  std::cout << "Histogram for Jets" << '\n';
  std::cout << '\n';

  hist_njets_MC->SetFillColor(kBlue);
  hist_njets_MC->Draw("HIST");
  hist_njets->SetMarkerStyle(21);
  hist_njets->SetMarkerColor(kTeal);
  hist_njets->Draw("SAME");
  canvas->Print("MonteCarloVSData/hist_njets.pdf");
  canvas->Clear();


  hist_jet_pt_MC->SetFillColor(kBlue);
  hist_jet_pt_MC->Draw("HIST");
  hist_jets_pt->SetMarkerStyle(21);
  hist_jets_pt->SetMarkerColor(kTeal);
  hist_jets_pt->Draw("SAME");
  canvas->Print("MonteCarloVSData/hist_jet_pt.pdf");
  canvas->Clear();


  hist_jet_eta_MC->SetFillColor(kBlue);
  hist_jet_eta_MC->Draw("HIST");
  hist_jets_eta->SetMarkerStyle(21);
  hist_jets_eta->SetMarkerColor(kTeal);
  hist_jets_eta->Draw("SAME");
  canvas->Print("MonteCarloVSData/hist_jet_eta.pdf");
  canvas->Clear();

  hist_jet_JVF_MC->SetFillColor(kBlue);
  hist_jet_JVF_MC->Draw("HIST");
  hist_jets_JVF->SetMarkerStyle(21);
  hist_jets_JVF->SetMarkerColor(kTeal);
  hist_jets_JVF->Draw("SAME");
  canvas->Print("MonteCarloVSData/hist_jet_JVF.pdf");
  canvas->Clear();

  hist_jet_MV1_MC->SetFillColor(kBlue);
  hist_jet_MV1_MC->Draw("HIST");
  hist_jets_MV1->SetMarkerStyle(21);
  hist_jets_MV1->SetMarkerColor(kTeal);
  hist_jets_MV1->Draw("SAME");
  canvas->Print("MonteCarloVSData/hist_jet_MV1.pdf");
  canvas->Clear();

  std::cout << '\n';
  std::cout << "Histogram for b-Jets" << '\n';
  std::cout << '\n';

  hist_nbjets_MC->SetFillColor(kRed);
  hist_nbjets_MC->Draw("HIST");
  hist_nbjets->SetMarkerStyle(21);
  hist_nbjets->SetMarkerColor(kTeal);
  hist_nbjets->Draw("SAME");
  canvas->Print("MonteCarloVSData/hist_nbjets.pdf");
  canvas->Clear();
  canvas->SetLogy(false);

  std::cout << '\n';
  std::cout << "Histogram for MET" << '\n';
  std::cout << '\n';

  hist_MET_MC->SetFillColor(kGreen);
  hist_MET_MC->Draw("HIST");
  hist_MET->SetMarkerStyle(21);
  hist_MET->SetMarkerColor(kTeal);
  hist_MET->Draw("SAME");
  canvas->Print("MonteCarloVSData/hist_MET.pdf");
  canvas->Clear();

  std::cout << '\n';
  std::cout << "Histogram for mTW" << '\n';
  std::cout << '\n';

  hist_mTW_MC->SetFillColor(kAzure);
  hist_mTW_MC->Draw();
  hist_mTW->SetMarkerStyle(21);
  hist_mTW->SetMarkerColor(kTeal);
  hist_mTW->Draw("SAME");
  canvas->Print("MonteCarloVSData/hist_mTW.pdf");
  canvas->Clear();

  std::cout << '\n';
  std::cout << '\n';
  std::cout << "Done" << '\n';
}
