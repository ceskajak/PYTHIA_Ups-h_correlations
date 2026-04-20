#include <TFile.h>
#include <TH1.h>
#include <iostream>

int draw() {
    // Open the ROOT file
    TFile *file = TFile::Open("merged.root", "READ");
    if (!file || file->IsZombie()) {
        std::cerr << "Error opening file merged.root" << std::endl;
        return 1;
    }

    // Load histograms
    TH1 *h_delta_phi = dynamic_cast<TH1*>(file->Get("h_delta_phi"));
    TH1 *h_pi_phi = dynamic_cast<TH1*>(file->Get("h_pi_phi"));
    TH1 *h_Ups_phi = dynamic_cast<TH1*>(file->Get("h_Ups_phi"));

    if (!h_delta_phi || !h_pi_phi || !h_Ups_phi) {
        std::cerr << "Error loading histograms" << std::endl;
        file->Close();
        return 1;
    }

    // Get total counts in h_Ups_phi
    double total_Ups_phi = h_Ups_phi->GetEntries();
    if (total_Ups_phi == 0) {
        std::cerr << "h_Ups_phi has zero entries, cannot normalise" << std::endl;
        file->Close();
        return 1;
    }

    // Normalise h_delta_phi by counts in h_Ups_phi
    h_delta_phi->Scale(1.0 / total_Ups_phi);

    cout << fixed << "Normalised h_delta_phi by total counts in h_Ups_phi: " << total_Ups_phi << endl;

    // Modify final histogram
    h_delta_phi->SetTitle("");
    h_delta_phi->SetStats(0); // Disable statistics box
    h_delta_phi->GetXaxis()->SetTitle("#Delta#varphi (rad)");
    h_delta_phi->GetYaxis()->SetTitle("1/N_{#Upsilon} dN/d#varphi");
    h_delta_phi->GetYaxis()->SetTitleOffset(1.2);
    h_delta_phi->Rebin(2);
    h_delta_phi->Scale(1.0 / h_delta_phi->GetBinWidth(1)); // Normalise by bin width
    h_delta_phi->GetYaxis()->SetRangeUser(0.2, 0.5);
    h_delta_phi->SaveAs("fig/h_delta_phi.root");

    h_delta_phi->SetMarkerStyle(20);
    h_delta_phi->SetMarkerColor(kBlue);
    h_delta_phi->SetMarkerSize(2);
    h_delta_phi->SetLineColor(kBlue);
    h_delta_phi->SetLineWidth(2);

    // Add a legend
    TLegend *legend = new TLegend(0.1, 0.7, 0.5, 0.95);
    legend->SetHeader("");
    legend->SetTextSize(0.035);
    legend->SetBorderSize(0);
    legend->SetFillColor(0);
    legend->SetFillStyle(0);
    legend->AddEntry((TObject*)NULL, "#Upsilon-#pi^{#pm} correlations", "");
    legend->AddEntry((TObject*)NULL, "Decay electrons within acceptance", "");
    legend->AddEntry((TObject*)NULL, "p_{T}^{e_{1}} > 4.2 GeV/c, p_{T}^{e_{2}} > 3.0 GeV/c", "");
    legend->AddEntry((TObject*)NULL, "p_{T}^{#pi} > 0.5 GeV/c", "");


    // Modify h_pi_phi
    h_pi_phi->SetTitle("");
    h_pi_phi->SetStats(0); // Disable statistics box
    h_pi_phi->GetXaxis()->SetTitle("#phi (rad)");
    h_pi_phi->GetYaxis()->SetTitle("Counts [-]");
    h_pi_phi->GetYaxis()->SetTitleOffset(1.4);
    h_pi_phi->Rebin(2);

    // Modify h_Ups_phi
    h_Ups_phi->SetTitle("");
    h_Ups_phi->SetStats(0); // Disable statistics box
    h_Ups_phi->GetXaxis()->SetTitle("#phi (rad)");
    h_Ups_phi->GetYaxis()->SetTitle("Counts [-]");
    h_Ups_phi->GetYaxis()->SetTitleOffset(1.4);
    h_Ups_phi->Rebin(2);

    // Create a canvas to draw the histogram
    TCanvas * canvas = new TCanvas("canvas", "Canvas for h_delta_phi", 1600, 1200);
    canvas->SetMargin(0.10, 0.05, 0.10, 0.05);

    // Save histograms as a PNG to the fig directory
    h_delta_phi->Draw();
    legend->Draw("same");
    canvas->SaveAs("fig/h_delta_phi.png");

    h_pi_phi->Draw();
    canvas->SaveAs("fig/h_pi_phi.png");

    h_Ups_phi->Draw();
    canvas->SaveAs("fig/h_Ups_phi.png");

    // Clean up
    delete canvas;
    file->Close();
    return 0;
}
