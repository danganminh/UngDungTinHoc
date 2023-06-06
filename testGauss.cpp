void testGauss(){
	
	int even = 50000;
	float Pi = 3.141592654;
	double mean = 2;
	double sigma = 3;
	
	double r1, r2, gauss, x1, x2, R1, R2;
	
	srand (time(NULL));
	
	// Write data to file .txt
	fstream data;
	data.open("data.txt", ios::out);
	
	if (data.is_open()) {
		for (int i = 0; i < even; i++) {
			r1 = (double)rand()/RAND_MAX;
			r2 = (double)rand()/RAND_MAX;
			x1 = sqrt(-2.0*log(r1));
			x2 = sin(2.0*Pi*r2);
			gauss = mean + x1*x2*sigma;
			cout << x1 << "\t" << x2 << "\t" << gauss << endl;			
			data << gauss << endl;
			r1 = 0; r2 = 0; x1 = 0; x2 = 0; gauss = 0;
		}
		data.close();
	} else {
		std::cout << "Failed to open the file" << std::endl;
		return 0;
	}
	
	TCanvas *c1 = new TCanvas("c1", "Gauss", 800, 600);
	
	TH1F *hist = new TH1F("hist", "Do Thi Histogram So Den Nguon 1000", 1500, -10, 20);
	
	
	std::fstream file;
	file.open("data.txt", std::ios::in);
	
	// input data from file .txt to draw
	double value;
	if (file.is_open())	{
		while (file >> value) {
			hist->Fill(value);
		}
		file.close();
	} else {
		std::cout << "Failed to open the file" << std::endl;
		return 0;
	}
	
	hist->GetXaxis()->SetTitle("Gauss");
	hist->GetYaxis()->SetTitle("So Dem");
	
	hist->Draw();
	
	// Fit Gauss
	TF1 *mygauss = new TF1("mygauss", "gaus", -20, 20);
	mygauss->SetLineColor(kRed);
	hist->Fit(mygauss, "R");
	
	
	c1->Update();
	c1->Modified();
}
