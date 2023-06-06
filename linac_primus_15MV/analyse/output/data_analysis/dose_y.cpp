void dose_y() {
    TCanvas *c1 = new TCanvas("c1", "Dose y", 800, 600);
    TGraph *gr = new TGraph();

    std::fstream data;
    data.open("dose_y.txt", std::ios::in);

    // Skip first line
    std::string line;
    std::getline(data, line);
    // Skip first line

    double dose, y, ey;

    if (data.is_open()) {
        while (std::getline(data, line)) {
            std::istringstream iss(line);
            iss >> y >> dose >> ey;
            gr->SetPoint(gr->GetN(), y, dose);
        }
        data.close();
    } else {
        std::cout << "Failed to open the file" << std::endl;
        return;
    }
    
    gr->SetTitle("Dose y");
    gr->GetXaxis()->SetTitle("y (mm)");
    gr->GetYaxis()->SetTitle("Dose (Gy)");
	gr->SetLineColor(kRed);
	gr->SetLineWidth(2);
    gr->SetMarkerColor(4);
    gr->SetMarkerStyle(21);
    gr->Draw("ALP");

    c1->Update();
}

