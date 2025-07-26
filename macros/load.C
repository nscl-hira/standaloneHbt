
// make Manager outside macro scope so we have access to all once macro is done.
class StHbtManager;
StHbtManager *TheManager;

void load() {
	gSystem->Load("StarClassLibrary/StarClassLibrary.so");
	gSystem->Load("StHbt/StHbt.so");
	gSystem->Load("HbtUserCode/HbtUserCode.so");
	cout << "Dynamic loading done" << endl;
}
