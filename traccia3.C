#include <iostream>

void traccia3() {
  TFile *Laboratorio2 = new TFile("Laboratorio2.root", "READ");
  TCanvas *canvas[12];
  TH1F *histo[12];
  TH1F *h1 = (TH1F *)Laboratorio2->Get("h1");
  TH1F *h2 = (TH1F *)Laboratorio2->Get("h2");
  TH1F *h3 = (TH1F *)Laboratorio2->Get("h3");
  TH1F *h4 = (TH1F *)Laboratorio2->Get("h4");
  TH1F *h5 = (TH1F *)Laboratorio2->Get("h5");
  TH1F *h6 = (TH1F *)Laboratorio2->Get("h6");
  TH1F *h7 = (TH1F *)Laboratorio2->Get("h7");
  TH1F *h8 = (TH1F *)Laboratorio2->Get("h8");
  TH1F *h9 = (TH1F *)Laboratorio2->Get("h9");
  TH1F *h10 = (TH1F *)Laboratorio2->Get("h10");
  TH1F *h11 = (TH1F *)Laboratorio2->Get("h11");
  TH1F *h12 = (TH1F *)Laboratorio2->Get("h12");
  TCanvas *c1 = new TCanvas("c1", "Istogrammi fino ad ora1");
  TCanvas *c2 = new TCanvas("c2", "Istogrammi fino ad ora2");
  TCanvas *c3 = new TCanvas("c3", "Istogrammi fino ad ora3");
  TCanvas *c4 = new TCanvas("c4", "Istogrammi fino ad ora4");
  TCanvas *c5 = new TCanvas("c5", "Istogrammi fino ad ora5");
  TCanvas *c6 = new TCanvas("c6", "Istogrammi fino ad ora6");
  TCanvas *c7 = new TCanvas("c7", "Istogrammi fino ad ora7");
  TCanvas *c8 = new TCanvas("c8", "Istogrammi fino ad ora8");
  TCanvas *c9 = new TCanvas("c9", "Istogrammi fino ad ora9");
  TCanvas *c10 = new TCanvas("c10", "Istogrammi fino ad ora10");
  TCanvas *c11 = new TCanvas("c11", "Istogrammi fino ad ora11");
  TCanvas *c12 = new TCanvas("c12", "Istogrammi fino ad ora12");
  canvas[0] = c1;
  canvas[1] = c2;
  canvas[2] = c3;
  canvas[3] = c4;
  canvas[4] = c5;
  canvas[5] = c6;
  canvas[6] = c7;
  canvas[7] = c8;
  canvas[8] = c9;
  canvas[9] = c10;
  canvas[10] = c11;
  canvas[11] = c12;
  histo[0] = h1;
  histo[1] = h2;
  histo[2] = h3;
  histo[3] = h4;
  histo[4] = h5;
  histo[5] = h6;
  histo[6] = h7;
  histo[7] = h8;
  histo[8] = h9;
  histo[9] = h10;
  histo[10] = h11;
  histo[11] = h12;
  // punto 10.1
  for (int i = 0; i < 12; ++i) {
    std::cout << "Entries dell'istogramma h" << i + 1 << " = "
              << histo[i]->GetEntries() << std::endl;
  }
  // punto 10.2
  std::cout << "Pione+ generati = " << histo[0]->GetBinContent(1) << " +- "
            << histo[0]->GetBinError(1) << std::endl;
  std::cout << "Pione- generati = " << histo[0]->GetBinContent(2) << " +- "
            << histo[0]->GetBinError(2) << std::endl;
  std::cout << "Kaoni+ generati = " << histo[0]->GetBinContent(3) << " +- "
            << histo[0]->GetBinError(3) << std::endl;
  std::cout << "Kaoni- generati = " << histo[0]->GetBinContent(4) << " +- "
            << histo[0]->GetBinError(4) << std::endl;
  std::cout << "protoni+ generati = " << histo[0]->GetBinContent(5) << " +- "
            << histo[0]->GetBinError(5) << std::endl;
  std::cout << "protoni- generati = " << histo[0]->GetBinContent(6) << " +- "
            << histo[0]->GetBinError(6) << std::endl;
  std::cout << "k* generate = " << histo[0]->GetBinContent(7) << " +- "
            << histo[0]->GetBinError(7) << std::endl;
  // punto 10.3
  TF1 *f1uniform = new TF1("f1uniform", "[0]", 0, 2 * M_PI);
  TF1 *f2uniform = new TF1("f2uniform", "[0]", 0, M_PI);
  TF1 *f3expo = new TF1("f3expo", "[0] * exp(-1 *[1] * x)", 0, 7);
  f1uniform->SetParameter(0, 10000);
  f2uniform->SetParameter(0, 10000);
  f3expo->SetParameters(140000, 0);
  h2->Fit(f1uniform);
  h3->Fit(f2uniform);
  h4->Fit(f3expo);
  std::cout << "fit su h2: " << std::endl
            << "Primo parametro = " << f1uniform->GetParameter(0) << " +- "
            << f1uniform->GetParError(0) << " Chi quadro ridotto = "
            << f1uniform->GetChisquare() / f1uniform->GetNDF()
            << " Probabilità del fit = " << f1uniform->GetProb() << std::endl;
  std::cout << "fit su h3: " << std::endl
            << "Primo parametro = " << f2uniform->GetParameter(0) << " +- "
            << f2uniform->GetParError(0) << " Chi quadro ridotto = "
            << f2uniform->GetChisquare() / f2uniform->GetNDF()
            << " Probabilità del fit = " << f2uniform->GetProb() << std::endl;
  std::cout << "fit di h4: " << std::endl
            << "Primo parametro = " << f3expo->GetParameter(0) << " +- "
            << f3expo->GetParError(0)
            << " Secondo parametro = " << f3expo->GetParameter(1) << " +- "
            << f3expo->GetParError(1) << " Chi quadro ridotto = "
            << f3expo->GetChisquare() / f3expo->GetNDF()
            << " Probabilità del fit = " << f3expo->GetProb() << std::endl;
  for (int i = 0; i < 12; ++i) {
    canvas[i]->cd();
    histo[i]->Draw();
    histo[i]->DrawCopy();
  }
  c2->cd();
  f1uniform->Draw("SAME");
  c3->cd();
  f1uniform->Draw("SAME");
  c4->cd();
  f3expo->Draw("SAME");

  // punto 11
  TCanvas *c13 = new TCanvas("c13", "Istogrammi fino ad ora 13");
  TH1F *h13 = new TH1F("h13", "Sottrazione di h9 a h8", 500, 0, 5);
  h13->Add(h8, h9, 1, -1);
  c13->cd();
  h13->Draw();
  h13->DrawCopy();
  TCanvas *c14 = new TCanvas("c14", "Istogrammi fino ad ora 14");
  TH1F *h14 = new TH1F("h14", "Sottrazione di h11 a h10", 500, 0, 5);
  h14->Add(h10, h11, 1, -1);
  c14->cd();
  h14->Draw();
  h14->DrawCopy();
  TF1 *gaussian1 =
      new TF1("gaussian1", "[0]*exp((-0.5*((x-[1])/[2])*(x-[1])/[2]))");
  gaussian1->SetParameters(1000, 0.89, 0.050);
  h13->Fit("gaussian1");
  std::cout << "fit di h13: " << std::endl
            << "Primo parametro (picco della distribuzione) = "
            << gaussian1->GetParameter(0) << " +- " << gaussian1->GetParError(0)
            << " Secondo parametro (media) = " << gaussian1->GetParameter(1)
            << " +- " << gaussian1->GetParError(1)
            << " Terzo parametro (Deviazione standard) = "
            << gaussian1->GetParameter(2) << " +-" << gaussian1->GetParameter(2)
            << " Chi quadro ridotto = "
            << f3expo->GetChisquare() / f3expo->GetNDF()
            << " Probabilità del fit = " << f3expo->GetProb() << std::endl;
  c13->cd();
  gaussian1->Draw("SAME");
  h14->Fit("gaussian1");
  std::cout << "fit di h14: " << std::endl
            << "Primo parametro (picco della distribuzione) = "
            << gaussian1->GetParameter(0) << " +- " << gaussian1->GetParError(0)
            << " Secondo parametro (media) = " << gaussian1->GetParameter(1)
            << " +- " << gaussian1->GetParError(1)
            << " Terzo parametro (Deviazione standard) = "
            << gaussian1->GetParameter(2) << " +-" << gaussian1->GetParameter(2)
            << " Chi quadro ridotto = "
            << f3expo->GetChisquare() / f3expo->GetNDF()
            << " Probabilità del fit = " << f3expo->GetProb() << std::endl;
  c14->cd();
  gaussian1->Draw("SAME");

/*punto 12
  c1->Print("c1.pdf");
  c1->Print("c1.C");
  c1->Print("c1.root");
  c2->Print("c2.pdf");
  c2->Print("c2.C");
  c2->Print("c2.root");
  c3->Print("c3.pdf");
  c3->Print("c3.C");
  c3->Print("c3.root");
  c4->Print("c4.pdf");
  c4->Print("c4.C");
  c4->Print("c4.root");
  c5->Print("c5.pdf");
  c5->Print("c5.C");
  c5->Print("c5.root");
  c6->Print("c6.pdf");
  c6->Print("c6.C");
  c6->Print("c6.root");
  c7->Print("c7.pdf");
  c7->Print("c7.C");
  c7->Print("c7.root");
  c8->Print("c8.pdf");
  c8->Print("c8.C");
  c8->Print("c8.root");
  c9->Print("c9.pdf");
  c9->Print("c9.C");
  c9->Print("c9.root");
  c10->Print("c10.pdf");
  c10->Print("c10.C");
  c10->Print("c10.root");
  c11->Print("c11.pdf");
  c11->Print("c11.C");
  c11->Print("c11.root");
  c12->Print("c12.pdf");
  c12->Print("c12.C");
  c12->Print("c12.root");*/

  Laboratorio2->Close();
}