void dose_z() {
	TCanvas *c1 = new TCanvas("c1", "Dose z", 800, 600);
	TGraph *gr = new TGraph();
	
	std::fstream data;
	data.open("dose_z.txt", std::ios::in);
	
	// Skip first line
	std::string line;
	std::getline(data, line);
	// Skip first line
	
	double dose, z, ey;
	
	if (data.is_open()) {
		while (std::getline(data, line)) {
			std::istringstream iss(line);
			iss >> z >> dose >> ey;
			gr->SetPoint(gr->GetN(), z, dose);
		}
		data.close();
	} else {
		std::cout << "Failed to open the file" << std::endl;
		return;
	}
	
	gr->SetTitle("Dose z");
	gr->GetXaxis()->SetTitle("z (mm)");
	gr->GetYaxis()->SetTitle("Dose (Gy)");
	gr->SetLineColor(kRed);
	gr->SetLineWidth(2);
	gr->SetMarkerColor(4);
	gr->SetMarkerStyle(21);
	gr->Draw("APL");
	
	c1->Update();
}
