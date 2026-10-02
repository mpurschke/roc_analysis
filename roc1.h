#ifndef __ROC1_H__
#define __ROC1_H__

#include <pmonitor/pmonitor.h>
#include <Event/Event.h>
#include <Event/EventTypes.h>

#include <TCanvas.h>

int process_event (Event *e); //++CINT 
void  plot(const int start = 0, const int xx=5, const int yy=0);

TCanvas * get_Canvas();
#endif /* __ROC1_H__ */
