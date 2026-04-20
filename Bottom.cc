#include "Pythia8/Pythia.h"

#include "TInterpreter.h"
#include "TTree.h"
#include "TFile.h"
#include "Math/Vector4D.h"
#include "TH1.h"

#include <vector>

using namespace std;
using namespace Pythia8;
using namespace ROOT::Math;

int main(int argc, char** argv)
{
	// create Pythia instance
	Pythia pythia;
	
	// static settings
	Settings& settings = pythia.settings;
	//Info& info = pythia.info;

	// load settings
	pythia.readFile("Bottom.cmnd");

	//  define parameters from runcard
	int maxNumberOfEvents = settings.mode("Main:numberOfEvents");
	int maxErrors = settings.mode("Main:timesAllowErrors");

	// initialize Pythia
	pythia.init();

	// define histograms
	TH1D * h_Ups_phi = new TH1D("h_Ups_phi", "Upsilon phi", 100, -3.14, 3.14);
	TH1D * h_pi_phi = new TH1D("h_pi_phi", "pion phi", 100, -3.14, 3.14);
	TH1D * h_delta_phi = new TH1D("h_delta_phi", "delta phi", 70, -2, 5);

	// define ROOT TTree
	//TTree *tree = new TTree("tree", "tree");

	// define parameters to save
	Double_t Ups_phi;
	Double_t delta_phi;
	vector<Double_t> pi_phi;

	// create TTree branches
	//tree->Branch("pi_phi", "std::vector<Double_t>", &pi_phi);


	// Define temporary Particle and her mothers and daughters
	Particle particle;
	Particle mother1;
	Particle mother2;
	Particle daughter1;
	Particle daughter2;

	vector<Int_t> p_index;
	Bool_t unique;

	// loop over all events (run loop)
	for (int i = 0; i < maxNumberOfEvents; i++)
	{
		if (!pythia.next())
			continue;
		
		// init. parameters for new loop
		p_index.clear();
		
		pi_phi.clear();

		// single event loop (event loop)
		for (int j = 0; j < pythia.event.size(); j++)
		{
			// Set current particle
			particle = pythia.event[j];
			mother1 = pythia.event[particle.mother1()];
			mother2 = pythia.event[particle.mother2()];
			daughter1 = pythia.event[particle.daughter1()];
			daughter2 = pythia.event[particle.daughter2()];

			unique = 1;

			// Pion finder
			if (particle.isFinal() && particle.isCharged())
				if (particle.pT() >= .50 && abs(particle.eta()) < 1.0)
					if (abs(particle.id() == 211))
						pi_phi.push_back(particle.phi());

			// Find and save unique "final state" Upsilons
			if (particle.id() == 553)
			{
				while (daughter1.id() == 553)
				{
					particle = daughter1;
					daughter1 = pythia.event[particle.daughter1()];
					daughter2 = pythia.event[particle.daughter2()];
					mother1 = pythia.event[particle.mother1()];
					mother2 = pythia.event[particle.mother2()];
				}

				if (abs(daughter1.eta()) > 1.0 || abs(daughter2.eta()) > 1.0)
					continue;

				if ((daughter1.pT() < 4.2 && daughter2.pT() < 3.0) || 
					(daughter1.pT() < 3.0 && daughter2.pT() < 4.2))
					continue;

				for (Int_t k = 0; k < p_index.size(); k++)
					if (particle.daughter1() == p_index[k])
						unique = 0;
							
				if (unique)
				{
					Ups_phi = particle.phi();

					p_index.push_back(particle.daughter1());
				}
			}
		}	// end event loop

		/*
		if (Ups != 0)
			tree->Fill();
		*/

		if (p_index.size() == 0)
			continue;
		h_Ups_phi->Fill(Ups_phi);
		
		for (Int_t k = 0; k < pi_phi.size(); k++)
		{
			h_pi_phi->Fill(pi_phi[k]);

			delta_phi = pi_phi[k] - Ups_phi;

			if (delta_phi < 4.71 && delta_phi > -1.57)
			{
				h_delta_phi->Fill(delta_phi);
			}
			else if (delta_phi > 4.71)
			{
				delta_phi = delta_phi - 2 * 3.14;
				h_delta_phi->Fill(delta_phi);
			}
			else if (delta_phi < -1.57)
			{
				delta_phi = delta_phi + 2 * 3.14;
				h_delta_phi->Fill(delta_phi);
			}
		}
	} // end run loop

	// statistics
	//pythia.stat();
	
	// select output file
	string out_str = string("output/files/") + argv[1] + ".root";
	const char * out_char = out_str.c_str();
	TFile out(out_char, "recreate");

	h_pi_phi->Write();
	h_Ups_phi->Write();
	h_delta_phi->Write();

	// write tree
	//tree->Write();

	// done
	return 0;
}
