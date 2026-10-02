
#include <iostream>
#include <pmonitor/pmonitor.h>
#include "roc1.h"

#include "cmap.h"

#include <TH1.h>
#include <TH2.h>

#include<vector>

int init_done = 0;
#define  nr_channels 144

using namespace std;

TCanvas *c = 0;

TH2F *h_wf[nr_channels] = {0};   // the uncorrected waveform
TH2F *h_wf_bl[nr_channels] = {0};  // and baseline_subtracted

const int h_samples=31;


int pinit()
{

  if (init_done) return 1;
  init_done = 1;


  char id[100];
  char title[100];
  

  for ( int i = 0; i < nr_channels; i++)
    {

      sprintf (id, "h1_%02d", i );
      sprintf (title, "Waveform channel %d", i );

      h_wf[i] = new TH2F ( id,title, h_samples, -0.5, h_samples-0.5,  128, -100, 1050); 
      h_wf[i]->GetXaxis()->SetTitle("Sample");
      h_wf[i]->GetYaxis()->SetTitle("ADC");
    }

  for ( int i = 0; i < nr_channels; i++)
    {

      sprintf (id, "h1_%02d_bl", i );
      sprintf (title, "Waveform channel %d baseline subtracted", i );

      h_wf_bl[i] = new TH2F ( id,title, h_samples, -0.5, h_samples-0.5,  128, -100, 1050); 
      h_wf_bl[i]->GetXaxis()->SetTitle("Sample");
      h_wf_bl[i]->GetYaxis()->SetTitle("ADC");
    }

  
  return 0;

}

int old_runnumber =-1;

int process_event (Event * e)
{

  // when we see the begin-run, or the run number chnages, we reset the histos
  if ( e->getEvtType() == BEGRUNEVENT || e->getRunNumber() != old_runnumber)
    {
      for ( int i = 0; i < nr_channels; i++)
	{
	  h_wf[i]->Reset();
	  h_wf_bl[i]->Reset();
	}
      old_runnumber = e->getRunNumber();

    }


  

  int baseline[nr_channels] = {0};

  Packet *p = e->getPacket(12001);
  if (p)
    {

      // first we find out how many waveforms we have here
      int wf = p->iValue(0, "NR_WF");
      //cout  << " Number of Waveforms: " << e << endl;

      // now we run through them
      for ( int n = 0; n < wf; n++)
	{

          //cout << "----- Waveform " << n << " size: " << p->iValue(n, "SAMPLESIZE") << " timestamp " << p->lValue(n, 0,0) << endl;

	  // how many samples does this wf have?
	  int nr_samples = p->iValue(n,"SAMPLESIZE");
	  
	  if ( nr_samples >10)   // some minimum size
	    {

	      for ( int ch = 0; ch < nr_channels; ch++)
		{
		  
		  // calulate the baseline as the average of the first three samples, leaving out sample 0
		  baseline[ch] = 0;
		  float count = 0;
		  for ( int s = 1; s < 4; s++)
		    {
		      baseline[ch] +=  p->iValue(n, s, ch);
		      count +=1. ;
		    }
		  baseline[ch] /= count;
		  

		}

	      // now we have the baseline
	      
	      for ( int ch = 0; ch < nr_channels; ch++)
		{
		      
		  for ( int s = 0; s < nr_samples; s++)
		    {
		      double value = p->iValue(n,s,ch) - baseline[ch];
			  
		      // the uncorrected wf
		      h_wf[ch]->Fill ( s, p->iValue(n,s,ch) );
		      // and the corrected one
		      h_wf_bl[ch]->Fill ( s, value );
		      
		    }
		  
		}
	      
	    }
	  
	}
      delete p;
    }
  return 0;
}


// this will draw a simple-minded canvas with xd x yd consecutive histograms,
// starting at "start". So plot(0,5,5) will draw 25 histograms starting at channel 0.
void plot(const int start, const int xd, const int yd)
{

  int yy =yd;
  int xx =xd;

  // if we don't give the 2nd dimension we make them the same
  if ( yy == 0) yy = xx;

  c = new TCanvas("c", "c",15,56,1245,1085);
  c->Divide(xx,yy);

  // safety belt
  int m = xx*yy;
  if ( nr_channels < m) m = nr_channels;
  
  for ( int i = 0; i < m; i++)
    {
      int x = i%xx;
      int y = i/xx;
      c->cd (y*xx + x + 1);
      h_wf_bl[y*xx +x + start]->Draw("col");

    }
}



TCanvas * get_Canvas()
{
  return c;
}
