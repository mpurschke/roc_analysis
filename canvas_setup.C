{
  TCanvas *c1 = new TCanvas("c1", "c1",13,56,1400,700);
  c1->Divide(4,3);

  int row = 0;
  c1->cd(row+1)->SetLogy();
  h1_2->Draw();
  c1->cd(row+2)->SetLogy();
  h1_10->Draw();
  c1->cd(row+3)->SetLogy();
  h1_29->Draw();
  c1->cd(row+4)->SetLogy();
  h1_31->Draw();

  row = 4;
  c1->cd(row+1)->SetLogy();
  htoa1_2->Draw();
  c1->cd(row+2)->SetLogy();
  htoa1_10->Draw();
  c1->cd(row+3)->SetLogy();
  htoa1_29->Draw();
  c1->cd(row+4)->SetLogy();
  htoa1_31->Draw();

  row = 8;
  c1->cd(row+1)->SetLogy();
  htot1_2->Draw();
  c1->cd(row+2)->SetLogy();
  htot1_10->Draw();
  c1->cd(row+3)->SetLogy();
  htot1_29->Draw();
  c1->cd(row+4)->SetLogy();
  htot1_31->Draw();

  pupdate(c1, 60);

  TCanvas *c1_n2 = new TCanvas("c1_n2", "c1_n2",13,705,1400,500);
  c1_n2->Divide(3,1);

  c1_n2->cd(1);
  h2_bl->Draw("lego2");

  c1_n2->cd(2);
  htoa2->Draw("lego2");

  c1_n2->cd(3);
  htot2->Draw("lego2");

  pupdate(c1_n2, 180);
}

