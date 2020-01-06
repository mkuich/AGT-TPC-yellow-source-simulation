/*
 *  To do:
 *          - add xy smearing
 *          - add time calculation
 */
#include "sourceMC.h"
#include <TString.h>
#include <TH1D.h>
#include <TCanvas.h>
#include <TStyle.h>
#include <TColor.h>
#include <TH1F.h>
#include <TF1.h>

int main(){
    std::vector<double> range_Am241_sim, range_Am243_sim, range_Cm243_sim;
    int it = 100000;
    int nbins = 50;
    double vd = 2.552;//mm/us
    std::vector<int> activity = activity_ratio();
    
//     if(activity.size()){
//         std::cout<<"dupa";
//         return 1;}
    
    if(read_sim_range(200.0, range_Am241_sim, range_Am243_sim, range_Cm243_sim)){
        TH1D *zsmear_Am241 = new TH1D("zsmear_Am241", "", nbins,  range_Am241_sim.at(0)-30, range_Am241_sim.at(0)+30);
        zsmear_Am241->SetLineColor(kRed+2);
        TH1D *zsmear_Am243 = new TH1D("zsmear_Am243", "", nbins,  range_Am243_sim.at(0)-30, range_Am243_sim.at(0)+30);
        zsmear_Am243->SetLineColor(kBlue+2);
        TH1D *zsmear_Cm243 = new TH1D("zsmear_Cm243", "", nbins,  range_Cm243_sim.at(0)-30, range_Cm243_sim.at(0)+30);
        zsmear_Cm243->SetLineColor(kGreen+2);
        
        TH1D *zsmear_Am241_2 = new TH1D("zsmear_Am241_2", "", nbins,  range_Am241_sim.at(0)-30, range_Am241_sim.at(0)+30);
        zsmear_Am241_2->SetLineColor(kRed+2);
        TH1D *zsmear_Am243_2 = new TH1D("zsmear_Am243_2", "", nbins,  range_Am243_sim.at(0)-30, range_Am243_sim.at(0)+30);
        zsmear_Am243_2->SetLineColor(kBlue+2);
        TH1D *zsmear_Cm243_2 = new TH1D("zsmear_Cm243_2", "", nbins,  range_Cm243_sim.at(0)-30, range_Cm243_sim.at(0)+30);
        zsmear_Cm243_2->SetLineColor(kGreen+2);
        
        TH1D *zsmear_Am241_3 = new TH1D("zsmear_Am241_3", "", nbins,  range_Am241_sim.at(0)-30, range_Am241_sim.at(0)+30);
        zsmear_Am241_3->SetLineColor(kRed+2);
        TH1D *zsmear_Am243_3 = new TH1D("zsmear_Am243_3", "", nbins,  range_Am243_sim.at(0)-30, range_Am243_sim.at(0)+30);
        zsmear_Am243_3->SetLineColor(kBlue+2);
        TH1D *zsmear_Cm243_3 = new TH1D("zsmear_Cm243_3", "", nbins,  range_Cm243_sim.at(0)-30, range_Cm243_sim.at(0)+30);
        zsmear_Cm243_3->SetLineColor(kGreen+2);

        for(int i=0; i<it; i++){
//             zsmear_Am241->Fill(smear_z_range(smear_z_range_by_source(range_Am241_sim.at(0)), range_Am241_sim));
//             zsmear_Am241->Fill(smear_z_range_by_source(smear_z_range(range_Am241_sim.at(0), range_Am241_sim)));
            zsmear_Am243->Fill(smear_z_range(range_Am243_sim.at(0), range_Am243_sim));
            zsmear_Am243_2->Fill(smear_z_range(range_Am243_sim.at(0), range_Am243_sim));
            zsmear_Am243_3->Fill(smear_z_range_by_source(range_Am243_sim.at(0)));
            if(!(i%13)){
                zsmear_Am241->Fill(smear_z_range(range_Am241_sim.at(0), range_Am241_sim));
                zsmear_Am241_2->Fill(smear_z_range(range_Am241_sim.at(0), range_Am241_sim));
                zsmear_Am241_3->Fill(smear_z_range_by_source(range_Am241_sim.at(0)));
            }
            if(!(i%22)){
                zsmear_Cm243->Fill(smear_z_range(range_Cm243_sim.at(0), range_Cm243_sim));
                zsmear_Cm243_2->Fill(smear_z_range(range_Cm243_sim.at(0), range_Cm243_sim));
                zsmear_Cm243_3->Fill(smear_z_range_by_source(range_Cm243_sim.at(0)));
            }
            std::this_thread::sleep_for(std::chrono::milliseconds(1));
        }
        TCanvas *window = new TCanvas();
        gStyle->SetOptStat(0);
        
        TH1F *frame = window->DrawFrame(range_Am243_sim.at(0)-30, 0, range_Cm243_sim.at(0)+30, it);
        frame->GetYaxis()->SetTitle("entries");
        frame->GetXaxis()->SetTitle("range [mm]");

         frame->GetYaxis()->SetRangeUser(0., zsmear_Am243->GetBinContent(zsmear_Am243->GetMaximumBin())+zsmear_Am243->GetBinContent(zsmear_Am243->GetMaximumBin())*0.2);
        frame->Draw();
        zsmear_Am241->Draw("same hist");
//         gAm241->Draw("same L");
        zsmear_Am243->Draw("same hist");
        zsmear_Cm243->Draw("same hist");
        window->Print("../all.pdf");
        
        std::cout<<zsmear_Am243->GetMean()<<"   "<<zsmear_Am243->GetRMS()<<std::endl;
        std::cout<<zsmear_Am241->GetMean()<<"   "<<zsmear_Am241->GetRMS()<<std::endl;
        std::cout<<zsmear_Cm243->GetMean()<<"   "<<zsmear_Cm243->GetRMS()<<std::endl;
        std::cout<<((zsmear_Am241->GetMean()-zsmear_Am243->GetMean())/vd)<<"    "<<((zsmear_Cm243->GetMean()-zsmear_Am243->GetMean())/vd)<<std::endl;
        
        frame->GetYaxis()->SetRangeUser(0., zsmear_Am243_2->GetBinContent(zsmear_Am243_2->GetMaximumBin())+zsmear_Am243_2->GetBinContent(zsmear_Am243_2->GetMaximumBin())*0.2);
        frame->Draw();
        zsmear_Am241_2->Draw("same hist");
        zsmear_Am243_2->Draw("same hist");
        zsmear_Cm243_2->Draw("same hist");
        window->Print("../struggling.pdf");
        frame->GetYaxis()->SetRangeUser(1., zsmear_Am243_3->GetBinContent(zsmear_Am243_3->GetMaximumBin())+zsmear_Am243_3->GetBinContent(zsmear_Am243_3->GetMaximumBin())*0.2);
        gPad->SetLogy();
        frame->Draw();
        zsmear_Am243_3->Draw("same hist");
        zsmear_Am241_3->Draw("same hist");
        zsmear_Cm243_3->Draw("same hist");
        window->Print("../collimator.pdf");
        
//         std::cout<<vd<<std::endl;
        TH1D *zsmear_Am241_4 = new TH1D("zsmear_Am241_4", "", nbins,  (range_Am241_sim.at(0)-30)/vd, (range_Am241_sim.at(0)+30)/vd);
        zsmear_Am241_4->SetLineColor(kRed+2);
        TH1D *zsmear_Am243_4 = new TH1D("zsmear_Am243_4", "", nbins,  (range_Am243_sim.at(0)-30)/vd, (range_Am243_sim.at(0)+30)/vd);
        zsmear_Am243_4->SetLineColor(kBlue+2);
        TH1D *zsmear_Cm243_4 = new TH1D("zsmear_Cm243_4", "", nbins,  (range_Cm243_sim.at(0)-30)/vd, (range_Cm243_sim.at(0)+30)/vd);
        zsmear_Cm243_4->SetLineColor(kGreen+2);
        for(int iv=1; iv<=zsmear_Am241->GetNbinsX(); iv++){
            zsmear_Am241_4->SetBinContent(iv, zsmear_Am241->GetBinContent(iv)/vd);
            zsmear_Am243_4->SetBinContent(iv, zsmear_Am243->GetBinContent(iv)/vd);
            zsmear_Cm243_4->SetBinContent(iv, zsmear_Cm243->GetBinContent(iv)/vd);
        }
        gPad->SetLogy(0);
        zsmear_Am243_4->GetXaxis()->SetTitle("time [us]");
        zsmear_Am243_4->GetYaxis()->SetTitle("entries");
        zsmear_Am243_4->Draw("hist");
        zsmear_Am241_4->Draw("same hist");
        zsmear_Cm243_4->Draw("same hist");
        window->Print("../time.pdf");
        
        std::cout<<zsmear_Am243_4->GetMean()<<"   "<<zsmear_Am243_4->GetRMS()<<std::endl;
        std::cout<<zsmear_Am241_4->GetMean()<<"   "<<zsmear_Am241_4->GetRMS()<<std::endl;
        std::cout<<zsmear_Cm243_4->GetMean()<<"   "<<zsmear_Cm243_4->GetRMS()<<std::endl;
        std::cout<<((zsmear_Am241_4->GetMean()-zsmear_Am243_4->GetMean()))<<"   "<<((zsmear_Cm243_4->GetMean()-zsmear_Am243_4->GetMean()))<<std::endl;
    }
    else
        std::cout<<"Nope"<<std::endl;
    return 0;
}
