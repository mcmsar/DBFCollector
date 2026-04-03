#include "emsDBFtypes.h"
#include "HGTQueueTS.h"
#include "DataProcessor.h"
#include <stddef.h>

int main(){
	CEMSQueue<DBFTrackingData> tempQueue; // Create temporary queue and reference to satisfy constructor
	// Add any necessary tracking data here
	CEMSQueue<DBFTrackingData>& dbfVectorList = tempQueue; 

	int n_Process = 0; // Update to reflect processes in TestDBFProcessor

	CDigitalBeamFormer* DBFObj = new CDigitalBeamFormer(dbfVectorList);
	DBFObj->TestDBFprocessor(n_Process);
}