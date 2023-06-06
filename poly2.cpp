void poly2(){
	
	// Change value in here
	double range_i = -3;
	double range_f = 3;
	//---------------
	
	double x, Y, y, ran1, ran2;
	int Range = 50000;
	srand (time(NULL));
	
	// Out put data
	std::fstream OUT;
	OUT.open("poly2.txt", std::ios::out);
	if (OUT.is_open()) {
		for(int i = 1; i <= Range; i++){
			ran1 = (double)rand()/RAND_MAX;
			ran2 = (double)rand()/RAND_MAX;
			x = ran1*(2*range_f)-range_f;
			Y = ran2*range_f*range_f;
			y = x*x - 3;
			if (Y < y) {
				std::cout << x << std::endl;
				OUT << x << std::endl;
			}
		}
		OUT.close();
	}	
	//----------------------------
	
	
	TCanvas *c1 = new TCanvas("c1", "Poly2", 800, 600);
	TH1F *hist = new TH1F("hist", "Do thi poly2", 1000, range_i-3, range_f+3);
	
	// In put data
	double value;
	std::fstream IN;
	IN.open("poly2.txt", std::ios::in);
	if (IN.is_open()) {
		while (IN >> value) {
			hist->Fill(value);
		}
		IN.close();
	}
	
	hist->GetXaxis()->SetTitle("x");
	hist->GetYaxis()->SetTitle("Tan Suat");
	hist->Draw();

	// Fit poly2
	TF1 *myfitpoly2 = new TF1("poly2 fit", "pol2", range_i, range_f);
	myfitpoly2->SetLineColor(kRed);
	hist->Fit(myfitpoly2, "R", "same");
	
	myfitpoly2->SetParameter(4,0);
	
	c1->Update();
	c1->Modified();
}
