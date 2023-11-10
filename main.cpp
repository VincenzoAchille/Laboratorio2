#include <cmath>
#include <iostream>

#include "particle.hpp"
#include <ctime>

void traccia2() {
  srand(time(NULL));
  gRandom->SetSeed();
  Particle::AddParticleType("pioni+", 0.13957, 1);
  Particle::AddParticleType("pioni-", 0.13957, -1);
  Particle::AddParticleType("kaoni+", 0.49367, 1);
  Particle::AddParticleType("kaoni-", 0.49367, -1);
  Particle::AddParticleType("protoni+", 0.93827, 1);
  Particle::AddParticleType("protoni-", 0.93827, -1);
  Particle::AddParticleType("k*", 0.89166, 0, 0.050);
  Particle::PrintArray();

  const int N = 120;
  Particle EventParticles[N];
  int eventParticlesSize;
  int decaycounter;

  // TCanvas *prova = new TCanvas("prova", "Istogrammi fino ad ora");
  // prova->Divide(3, 4);

  TH1F *h1 = new TH1F("h1", "Tipi di particelle generate", 7, 0, 7);
  TH1F *h2 =
      new TH1F("h2", "Distribuzione angolo azimutale", 1000, 0, 2 * M_PI);
  TH1F *h3 = new TH1F("h3", "Distribuzione angolo polare", 1000, 0, M_PI);
  TH1F *h4 = new TH1F("h4", "Distribuzione impulso", 500, 0, 7);
  TH1F *h5 = new TH1F("h5", "Distribuzione impulso trasverso", 500, 0, 4.5);
  TH1F *h6 =
      new TH1F("h6", "Distribuzione della energia delle particelle", 500, 0, 6);
  TH1F *h7 = new TH1F("h7", "Massa invariante fra tutte le particelle generate",
                      1000, 0, 6);  // range e numero bin da decidere
  TH1F *h8 = new TH1F("h8", "Massa invariante particelle segno discorde", 500,
                      0, 6);  // range e numero bin da decidere
  h8->Sumw2();
  TH1F *h9 = new TH1F("h9", "Massa invariante particelle segno concorde", 500,
                      0, 6);  // range e numero bin da decidere
  h9->Sumw2();
  TH1F *h10 = new TH1F("h10", "Massa invariante pioni kaoni segno discorde",
                       500, 0, 6);  // range e numero bin da decidere
  h10->Sumw2();
  TH1F *h11 = new TH1F("h11", "Massa invariante pioni kaoni segno concorde",
                       500, 0, 6);  // range e numero bin da decidere
  h11->Sumw2();
  TH1F *h12 = new TH1F("h12", "Massa invariante per k*", 500, 0.6, 1.2);
  for (int j = 0; j < 1e5; ++j) {
    eventParticlesSize = 0;
    int i = 0;
    decaycounter = 0;
    for (i = 0; i < 100; ++i) {
      ++eventParticlesSize;
      Double_t type = gRandom->Rndm();
      Double_t phi = gRandom->Uniform(0, 2 * M_PI);
      Double_t theta = gRandom->Uniform(0, M_PI);
      Double_t p = gRandom->Exp(1);
      if (type < 0.4)  // pioni+
      {
        EventParticles[i].SetIndex(0);
      } else if (type < 0.8)  // pioni-
      {
        EventParticles[i].SetIndex(1);
      }

      else if (type < 0.85)  // kaoni+
      {
        EventParticles[i].SetIndex(2);
      } else if (type < 0.9)  // kaoni-
      {
        EventParticles[i].SetIndex(3);
      } else if (type < 0.945)  // protoni+
      {
        EventParticles[i].SetIndex(4);
      } else if (type < 0.99)  // protoni-
      {
        EventParticles[i].SetIndex(5);
      } else  // k*
      {
        EventParticles[i].SetIndex(6);
        ++eventParticlesSize;
        ++eventParticlesSize;
        if (gRandom->Rndm() < 0.5) {
          EventParticles[100 + decaycounter].SetIndex(0);
          EventParticles[101 + decaycounter].SetIndex(3);
        } else {
          EventParticles[100 + decaycounter].SetIndex(1);
          EventParticles[101 + decaycounter].SetIndex(2);
        }
        EventParticles[i].Decay2body(EventParticles[100 + decaycounter],
                                     EventParticles[101 + decaycounter]);
        h12->Fill(EventParticles[100 + decaycounter].InvMass(
            EventParticles[101 + decaycounter]));
        ++decaycounter;
        ++decaycounter;

      }
      EventParticles[i].SetP(p * sin(theta) * cos(phi),
                             p * sin(theta) * sin(phi), p * cos(theta));
      h1->Fill(EventParticles[i].GetIndex());
      h2->Fill(phi);
      h3->Fill(theta);
      h4->Fill(p);
      h5->Fill(p * sin(theta));
      h6->Fill(EventParticles[i].GetEnergy());
    }
    for (i = 0; i < eventParticlesSize; ++i) {
      if (EventParticles[i].GetIndex() != 6) {
        for (int k = 0; k < i; ++k)

        {
          if (EventParticles[k].GetIndex() != 6) {
            h7->Fill(EventParticles[i].InvMass(EventParticles[k]));
            if ((EventParticles[i].GetIndex() % 2 == 1 &&
                 EventParticles[k].GetIndex() % 2 == 0) ||
                (EventParticles[i].GetIndex() % 2 == 0 &&
                 EventParticles[k].GetIndex() % 2 == 1))

            {
              h8->Fill(EventParticles[i].InvMass(EventParticles[k]));
              if (EventParticles[i].GetIndex() <= 3 &&
                  EventParticles[k].GetIndex() <= 3 &&
                  EventParticles[i].GetMass() != EventParticles[k].GetMass())

                h10->Fill(EventParticles[i].InvMass(EventParticles[k]));
            } else if ((EventParticles[i].GetIndex() % 2 == 0 &&
                        EventParticles[k].GetIndex() % 2 == 0) ||
                       (EventParticles[i].GetIndex() % 2 == 1 &&
                        EventParticles[k].GetIndex() % 2 == 1))

            {
              h9->Fill(EventParticles[i].InvMass(EventParticles[k]));
              if (EventParticles[i].GetIndex() <= 3 &&
                  EventParticles[k].GetIndex() <= 3 &&
                  EventParticles[i].GetMass() != EventParticles[k].GetMass())

                h11->Fill(EventParticles[i].InvMass(EventParticles[k]));
            }
          }
        }
      }
    }
    //std::cout << eventParticlesSize << std::endl;
  }

  TFile *Laboratorio2 = new TFile("Laboratorio2.root", "RECREATE");
  h1->Write();
  h2->Write();
  h3->Write();
  h4->Write();
  h5->Write();
  h6->Write();
  h7->Write();
  h8->Write();
  h9->Write();
  h10->Write();
  h11->Write();
  h12->Write();
  Laboratorio2->Close();
}
